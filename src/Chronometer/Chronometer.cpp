#include "Chronometer/Chronometer.h"

#include <iostream>
#include <sstream>

Chronometer::Chronometer(std::string name, bool automatic) : _name(std::move(name)), _automatic(automatic) { reset(); }

Chronometer::~Chronometer() { terminate(); }

std::string Chronometer::name() const { return _name; }

bool Chronometer::automatic() const { return _automatic; }

Chronometer::State Chronometer::state() const { return _state; }

Chronometer::Ticks Chronometer::ticks() const { return _ticks; }

Chronometer::Durations Chronometer::durations() const { return _durations; }

Chronometer::Duration Chronometer::duration() const { return _duration; }

std::string Chronometer::text() const {
    std::stringstream ss;
    ss << std::fixed;
    ss << "Chronometer '" << name() << "':" << std::endl;
    ss << "  - Ticks:";
    for (const auto& tick : ticks()) {
        ss << " " << std::chrono::duration_cast<Duration>(tick.time_since_epoch()).count() / 1000000.0L;
    }
    ss << std::endl;
    ss << "  - Durations:";
    for (const auto& duration : durations()) {
        ss << " " << duration.count();
    }
    ss << std::endl;
    ss << "  - Duration: " << duration().count() << std::endl;
    return ss.str();
}

Chronometer::Tick Chronometer::tick() {
    Tick tick = now();
    Duration duration = _state == State::PAUSED || _ticks.empty() ? std::chrono::microseconds(0) : std::chrono::duration_cast<Duration>(tick - _ticks.back());
    _ticks.push_back(tick);
    _durations.push_back(duration);
    _duration += duration;
    return tick;
}

Chronometer::Tick Chronometer::pause() {
    Tick tick_ = tick();
    _state = State::PAUSED;
    return tick_;
}

Chronometer::Tick Chronometer::resume() {
    Tick tick_ = tick();
    _state = State::RUNNING;
    return tick_;
}

void Chronometer::reset() {
    _state = _automatic ? State::RUNNING : State::PAUSED;
    _ticks.clear();
    _durations.clear();
    _duration = std::chrono::microseconds(0);
    if (_automatic) {
        tick();
    }
}

void Chronometer::terminate() {
    if (_automatic) {
        tick();
        log();
    }
}

void Chronometer::log() const { std::cout << text() << std::endl; }

Chronometer::Tick Chronometer::now() { return std::chrono::system_clock::now(); }
