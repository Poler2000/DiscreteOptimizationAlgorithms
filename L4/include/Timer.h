//
// Created by pawel on 09.12.2021.
//

#ifndef L3_TIMER_H
#define L3_TIMER_H

#include <chrono>

struct Timer {
public:
    Timer() {
        t0 = std::chrono::high_resolution_clock::now();
    };

    auto getTimeInMicroseconds() {
        t1 = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0);
        return duration;
    }

    auto getTimeInNanoseconds() {
        t1 = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(t1 - t0);
        return duration;
    }
private:
    std::chrono::high_resolution_clock::time_point t0;
    std::chrono::high_resolution_clock::time_point t1;
};

#endif //L3_TIMER_H
