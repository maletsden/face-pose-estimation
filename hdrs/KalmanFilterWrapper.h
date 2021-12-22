#pragma once

#include <vector>
#include <chrono>

#include <opencv2/video/tracking.hpp>

#include "IFilter.h"
#include "Types.h"
#include "PoseTransformation.h"

class KalmanFilterWrapper : public IFilter
{
public:
    KalmanFilterWrapper() = default;

    KalmanFilterWrapper(
        std::chrono::high_resolution_clock::time_point timestamp,
        const PoseTransformation& pose,
        const int numberOfDynamicParameters = 12,
        const int numberOfMeasureParameters = 6);

    cv::Mat Filter(const cv::Mat& measurment, std::chrono::high_resolution_clock::time_point timestamp) override;
    cv::Mat GetCorrectedState() const noexcept;

private:
    cv::Mat ComputeTransitionMatrix(const DataType dt) const noexcept;

    cv::KalmanFilter m_kalmanFilter;

    int m_numberOfDynamicParameters;
    int m_numberOfMeasureParameters;
    std::chrono::high_resolution_clock::time_point m_lastTimestamp;
};