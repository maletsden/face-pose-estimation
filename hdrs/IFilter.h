#pragma once

#include <chrono>

#include <opencv2/core/types.hpp>

class IFilter
{
public:
    virtual ~IFilter() = default;

    virtual cv::Mat Filter(const cv::Mat& measurement, std::chrono::high_resolution_clock::time_point timestamp) = 0;
};