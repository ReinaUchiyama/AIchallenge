"""Unit tests for V2XVehicleTracker (pure Python, no rclpy)."""

from dataclasses import dataclass
from typing import List

import pytest

from multi_purpose_mpc_ros.v2x_vehicle_tracker import V2XVehicleTracker, is_sample_fresh


# Lightweight stand-ins for v2x_msgs / std_msgs / geometry_msgs so tests
# do not require the ROS message DLLs to be importable.
@dataclass
class _Stamp:
    sec: int
    nanosec: int


@dataclass
class _Header:
    stamp: _Stamp


@dataclass
class _Point:
    x: float
    y: float
    z: float = 0.0


@dataclass
class _V2XVehiclePosition:
    header: _Header
    vehicle_id: str
    position: _Point


@dataclass
class _V2XVehiclePositionArray:
    header: _Header
    vehicles: List[_V2XVehiclePosition]


def _msg(stamp_sec: float, vehicles):
    """Build a fake V2XVehiclePositionArray with the given (vehicle_id, x, y)."""
    sec = int(stamp_sec)
    nanosec = int((stamp_sec - sec) * 1e9)
    array_header = _Header(_Stamp(sec, nanosec))
    out = []
    for vid, x, y in vehicles:
        out.append(_V2XVehiclePosition(
            header=_Header(_Stamp(sec, nanosec)),
            vehicle_id=vid,
            position=_Point(x=x, y=y),
        ))
    return _V2XVehiclePositionArray(header=array_header, vehicles=out)


def test_two_samples_constant_velocity_yields_finite_difference():
    tracker = V2XVehicleTracker(v_max_safety=30.0, position_jump_threshold=20.0)

    tracker.update(_msg(0.0, [("d2", 0.0, 0.0)]))
    tracker.update(_msg(0.5, [("d2", 5.0, 2.5)]))

    vx, vy = tracker.velocity("d2")
    assert vx == pytest.approx(10.0)
    assert vy == pytest.approx(5.0)


def test_single_sample_yields_zero_velocity():
    tracker = V2XVehicleTracker(v_max_safety=30.0, position_jump_threshold=5.0)

    tracker.update(_msg(0.0, [("d2", 1.0, 2.0)]))

    assert tracker.velocity("d2") == (0.0, 0.0)
    assert tracker.has_velocity_estimate("d2") is False


def test_unknown_vehicle_velocity_is_zero():
    tracker = V2XVehicleTracker(v_max_safety=30.0, position_jump_threshold=5.0)
    assert tracker.velocity("d9") == (0.0, 0.0)


def test_predict_positions_constant_velocity():
    tracker = V2XVehicleTracker(v_max_safety=30.0, position_jump_threshold=20.0)
    tracker.update(_msg(0.0, [("d2", 0.0, 0.0)]))
    tracker.update(_msg(0.5, [("d2", 5.0, 2.5)]))  # vx=10, vy=5, latest (5,2.5)

    points = tracker.predict_positions("d2", [0.0, 0.5, 1.0])

    assert points[0] == pytest.approx((5.0, 2.5))
    assert points[1] == pytest.approx((10.0, 5.0))
    assert points[2] == pytest.approx((15.0, 7.5))


def test_position_jump_resets_velocity_and_drops_old_sample():
    tracker = V2XVehicleTracker(v_max_safety=30.0, position_jump_threshold=5.0)
    tracker.update(_msg(0.0, [("d2", 0.0, 0.0)]))
    tracker.update(_msg(0.1, [("d2", 100.0, 0.0)]))  # 100 m jump > 5 m

    assert tracker.velocity("d2") == (0.0, 0.0)
    # Predictions should anchor at the *new* position with zero velocity.
    points = tracker.predict_positions("d2", [0.0, 0.5])
    assert points[0] == pytest.approx((100.0, 0.0))
    assert points[1] == pytest.approx((100.0, 0.0))


def test_velocity_above_safety_cap_is_zeroed():
    # 50 m / 0.05 s = 1000 m/s, well above v_max_safety=30
    tracker = V2XVehicleTracker(v_max_safety=30.0, position_jump_threshold=200.0)
    tracker.update(_msg(0.0, [("d2", 0.0, 0.0)]))
    tracker.update(_msg(0.05, [("d2", 50.0, 0.0)]))

    assert tracker.velocity("d2") == (0.0, 0.0)


def test_two_vehicles_tracked_independently():
    tracker = V2XVehicleTracker(v_max_safety=30.0, position_jump_threshold=20.0)
    tracker.update(_msg(0.0, [("d2", 0.0, 0.0), ("d3", 10.0, 10.0)]))
    tracker.update(_msg(0.5, [("d2", 5.0, 0.0), ("d3", 10.0, 11.1)]))

    assert tracker.velocity("d2") == pytest.approx((10.0, 0.0))
    assert tracker.velocity("d3") == pytest.approx((0.0, 5.0))
    assert tracker.has_velocity_estimate("d2") is True
    assert tracker.has_velocity_estimate("d3") is True


def test_active_ids_reflect_latest_message_only():
    tracker = V2XVehicleTracker(v_max_safety=30.0, position_jump_threshold=20.0)
    tracker.update(_msg(0.0, [("d2", 0.0, 0.0), ("d3", 10.0, 10.0)]))
    tracker.update(_msg(0.5, [("d2", 5.0, 0.0)]))  # d3 dropped this tick

    assert tracker.active_vehicle_ids() == ["d2"]
    # d3 is still in the internal state but not reported as active.
    assert tracker.velocity("d3") == pytest.approx((0.0, 0.0))


def test_predict_all_returns_only_active_vehicles():
    tracker = V2XVehicleTracker(v_max_safety=30.0, position_jump_threshold=20.0)
    tracker.update(_msg(0.0, [("d2", 0.0, 0.0), ("d3", 10.0, 10.0)]))
    tracker.update(_msg(0.5, [("d2", 5.0, 0.0)]))  # d3 dropped

    out = tracker.predict_all([0.0, 1.0])
    assert set(out.keys()) == {"d2"}
    assert out["d2"][0] == pytest.approx((5.0, 0.0))
    assert out["d2"][1] == pytest.approx((15.0, 0.0))


@dataclass
class _StubObstacle:
    cx: float
    cy: float
    radius: float


def test_predictions_to_obstacles_flattens_with_radius():
    from multi_purpose_mpc_ros.v2x_vehicle_tracker import predictions_to_obstacles

    predictions = {
        "d2": [(1.0, 2.0), (3.0, 4.0)],
        "d3": [(5.0, 6.0)],
    }
    obstacles = predictions_to_obstacles(
        predictions, vehicle_radius=0.5, obstacle_cls=_StubObstacle)

    centers = sorted((o.cx, o.cy, o.radius) for o in obstacles)
    assert centers == sorted([
        (1.0, 2.0, 0.5),
        (3.0, 4.0, 0.5),
        (5.0, 6.0, 0.5),
    ])


def test_predictions_to_obstacles_empty_input():
    from multi_purpose_mpc_ros.v2x_vehicle_tracker import predictions_to_obstacles
    assert predictions_to_obstacles(
        {}, vehicle_radius=0.5, obstacle_cls=_StubObstacle) == []


def test_position_jump_invokes_warn_callback():
    msgs = []
    tracker = V2XVehicleTracker(
        v_max_safety=30.0,
        position_jump_threshold=5.0,
        warn_callback=msgs.append,
    )
    tracker.update(_msg(0.0, [("d2", 0.0, 0.0)]))
    tracker.update(_msg(0.1, [("d2", 100.0, 0.0)]))

    assert any("position jump" in m for m in msgs)
    assert any("d2" in m for m in msgs)


def test_velocity_cap_invokes_warn_callback():
    msgs = []
    tracker = V2XVehicleTracker(
        v_max_safety=30.0,
        position_jump_threshold=200.0,
        warn_callback=msgs.append,
    )
    tracker.update(_msg(0.0, [("d2", 0.0, 0.0)]))
    tracker.update(_msg(0.05, [("d2", 50.0, 0.0)]))

    assert any("velocity" in m for m in msgs)
    assert any("d2" in m for m in msgs)


def test_warn_callback_optional_default_is_silent():
    # Construct without a callback; clamp fires must not raise.
    tracker = V2XVehicleTracker(v_max_safety=30.0, position_jump_threshold=5.0)
    tracker.update(_msg(0.0, [("d2", 0.0, 0.0)]))
    tracker.update(_msg(0.1, [("d2", 100.0, 0.0)]))  # would warn if a callback existed

    assert tracker.velocity("d2") == (0.0, 0.0)  # clamp still fires


# --- V2X sample freshness / stale-vehicle purge -----------------------------


def test_is_sample_fresh_within_window():
    assert is_sample_fresh(last_seen=10.0, now=10.4, sample_freshness_sec=1.0) is True


def test_is_sample_fresh_exactly_at_boundary_is_fresh():
    assert is_sample_fresh(last_seen=10.0, now=11.0, sample_freshness_sec=1.0) is True


def test_is_sample_fresh_past_window_is_stale():
    assert is_sample_fresh(last_seen=10.0, now=11.1, sample_freshness_sec=1.0) is False


def test_is_sample_fresh_never_received_is_never_fresh():
    assert is_sample_fresh(last_seen=None, now=100.0, sample_freshness_sec=1.0) is False


def test_update_records_local_reception_time_not_payload_stamp():
    # The message's own stamp is far in the past (t=0.0); the caller-supplied
    # reception time ("now") is what must be recorded, since a stalled V2X
    # topic never re-invokes update() to refresh anything derived from the
    # payload stamp.
    tracker = V2XVehicleTracker(v_max_safety=30.0, position_jump_threshold=20.0)
    tracker.update(_msg(0.0, [("d2", 0.0, 0.0)]), now=123.0)

    assert tracker.last_seen("d2") == pytest.approx(123.0)


def test_last_seen_unknown_vehicle_is_none():
    tracker = V2XVehicleTracker(v_max_safety=30.0, position_jump_threshold=20.0)
    assert tracker.last_seen("ghost") is None


def test_is_fresh_reflects_elapsed_time_since_last_update():
    tracker = V2XVehicleTracker(v_max_safety=30.0, position_jump_threshold=20.0)
    tracker.update(_msg(0.0, [("d2", 0.0, 0.0)]), now=100.0)

    assert tracker.is_fresh("d2", now=100.5, sample_freshness_sec=1.0) is True
    assert tracker.is_fresh("d2", now=101.5, sample_freshness_sec=1.0) is False


def test_is_active_and_fresh_requires_both_conditions():
    tracker = V2XVehicleTracker(v_max_safety=30.0, position_jump_threshold=20.0)
    tracker.update(_msg(0.0, [("d2", 0.0, 0.0), ("d3", 1.0, 1.0)]), now=100.0)
    tracker.update(_msg(0.5, [("d2", 1.0, 0.0)]), now=100.5)  # d3 dropped from latest msg

    # d2: active and within freshness window.
    assert tracker.is_active_and_fresh("d2", now=100.6, sample_freshness_sec=1.0) is True
    # d3: has a last_seen time, but is no longer in the active list.
    assert tracker.is_active_and_fresh("d3", now=100.6, sample_freshness_sec=1.0) is False
    # d2, but past the freshness window.
    assert tracker.is_active_and_fresh("d2", now=102.0, sample_freshness_sec=1.0) is False
    # Never-seen vehicle.
    assert tracker.is_active_and_fresh("ghost", now=100.6, sample_freshness_sec=1.0) is False


def test_purge_stale_drops_only_expired_vehicles():
    # Both vehicles are reported in every message they appear in, so a
    # vehicle missing from a later message is already dropped from
    # active_vehicle_ids() immediately by update() itself (see
    # test_active_ids_reflect_latest_message_only). purge_stale's distinct
    # job is the total-dropout case: it still must not touch a vehicle that
    # keeps getting fresh updates while a sibling vehicle's feed stalls.
    tracker = V2XVehicleTracker(v_max_safety=30.0, position_jump_threshold=20.0)
    tracker.update(_msg(0.0, [("d2", 0.0, 0.0), ("d3", 10.0, 10.0)]), now=100.0)
    tracker.update(_msg(0.1, [("d2", 0.1, 0.0), ("d3", 10.0, 10.0)]), now=100.9)

    purged = tracker.purge_stale(now=100.95, sample_freshness_sec=1.0)
    assert purged == []
    assert set(tracker.active_vehicle_ids()) == {"d2", "d3"}

    # Now the whole topic stalls: no further update() calls at all.
    purged = tracker.purge_stale(now=102.0, sample_freshness_sec=1.0)

    assert purged == ["d2", "d3"]
    assert tracker.active_vehicle_ids() == []
    assert tracker.last_seen("d2") is None
    assert tracker.velocity("d2") == (0.0, 0.0)
    assert tracker.has_velocity_estimate("d2") is False


def test_purge_stale_clears_dynamic_obstacle_predictions():
    # Simulates a V2X communication dropout: no message arrives at all, but
    # the periodic control loop must still notice the sample is too old and
    # stop reporting predictions for it.
    tracker = V2XVehicleTracker(v_max_safety=30.0, position_jump_threshold=20.0)
    tracker.update(_msg(0.0, [("d2", 0.0, 0.0)]), now=100.0)
    tracker.update(_msg(0.5, [("d2", 5.0, 2.5)]), now=100.5)

    tracker.purge_stale(now=102.0, sample_freshness_sec=1.0)

    assert tracker.predict_all([0.0, 1.0]) == {}
    assert tracker.predict_positions("d2", [0.0, 1.0]) == []


def test_purge_stale_returns_empty_list_when_nothing_expired():
    tracker = V2XVehicleTracker(v_max_safety=30.0, position_jump_threshold=20.0)
    tracker.update(_msg(0.0, [("d2", 0.0, 0.0)]), now=100.0)

    assert tracker.purge_stale(now=100.5, sample_freshness_sec=1.0) == []
    assert tracker.active_vehicle_ids() == ["d2"]


def test_purge_stale_is_idempotent():
    tracker = V2XVehicleTracker(v_max_safety=30.0, position_jump_threshold=20.0)
    tracker.update(_msg(0.0, [("d2", 0.0, 0.0)]), now=100.0)

    first = tracker.purge_stale(now=200.0, sample_freshness_sec=1.0)
    second = tracker.purge_stale(now=201.0, sample_freshness_sec=1.0)

    assert first == ["d2"]
    assert second == []
