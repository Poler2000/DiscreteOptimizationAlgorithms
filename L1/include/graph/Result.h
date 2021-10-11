//
// Created by Pawel Polerowicz
//

#ifndef AOD_RESULT_H
#define AOD_RESULT_H

#include "../utils/Timer.h"

template <typename T>
struct Result {
    T value;
    long time;
    int comparisons;
};

#endif //AOD_RESULT_H
