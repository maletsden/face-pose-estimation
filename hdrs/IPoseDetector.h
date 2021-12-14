#pragma once

#include <vector>

#include <opencv2/core/types.hpp>

#include "Types.h"
#include "PoseTransformation.h"

class IPoseDetector
{
public:
    virtual ~IPoseDetector() = default;

    virtual void DetectPose(
        const FaceLandmarks& faceLandmarks,
        PoseTransformation& pose,
        const std::vector<cv::Point3d>& modelPoints,
        const std::vector<int>& modelPointsIndices) = 0;
};
