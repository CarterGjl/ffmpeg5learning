//
// Created by gaojinliang on 2022/7/18.
//
#include "sys/time.h"

int64_t GetCurMsTime() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    int64_t ts = (int64_t)tv.tv_sec * 1000 + tv.tv_usec / 1000;
    return ts;
}

