//
// Created by Pawel Polerowicz
//

#ifndef AOD_TIMER_H
#define AOD_TIMER_H

#include <chrono>

class Timer {
public:
    Timer() {
        t0_ = std::chrono::high_resolution_clock::now();
    }

    [[nodiscard]] long getTimeInSeconds() const {
        auto t1 = std::chrono::high_resolution_clock::now();
        return std::chrono::duration_cast<std::chrono::seconds>(t1 - t0_).count();
    }

    [[nodiscard]] long getTimeInMilliseconds() const {
        auto t1 = std::chrono::high_resolution_clock::now();
        return std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0_).count();
    }

    [[nodiscard]] long getTimeInMicroseconds() const {
        auto t1 = std::chrono::high_resolution_clock::now();
        return std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0_).count();
    }

    [[nodiscard]] long getTimeInNanoseconds() const {
        auto t1 = std::chrono::high_resolution_clock::now();
        return std::chrono::duration_cast<std::chrono::nanoseconds>(t1 - t0_).count();
    }
private:
    std::chrono::high_resolution_clock::time_point t0_;
};

#endif //AOD_TIMER_H
