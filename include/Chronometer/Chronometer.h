#pragma once

#include <chrono>
#include <deque>
#include <string>

class Chronometer {
  public:
    Chronometer(std::string name, bool automatic);
    virtual ~Chronometer();
    Chronometer(const Chronometer& other) = default;
    Chronometer(Chronometer&& other) noexcept = default;
    Chronometer& operator=(const Chronometer& other) = default;
    Chronometer& operator=(Chronometer&& other) noexcept = default;

    enum class State { PAUSED = 0, RUNNING = 1 };
    using Tick = std::chrono::time_point<std::chrono::system_clock>;
    using Ticks = std::deque<Tick>;
    using Duration = std::chrono::microseconds;
    using Durations = std::deque<Duration>;

    std::string name() const;
    bool automatic() const;
    State state() const;
    Ticks ticks() const;
    Durations durations() const;
    Duration duration() const;
    std::string text() const;

    Tick tick();
    Tick pause();
    Tick resume();
    void reset();
    void terminate();

    void log() const;

  protected:
    static Tick now();

  private:
    std::string _name;
    bool _automatic{false};
    State _state{State::PAUSED};
    Ticks _ticks;
    Durations _durations;
    Duration _duration;
};
