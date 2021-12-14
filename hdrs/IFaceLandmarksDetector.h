#pragma once

#include <vector>

#include <opencv2/core/types.hpp>

#include "Types.h"
#include "Face.h"

class IFaceLandmarksDetector
{
public:
    virtual ~IFaceLandmarksDetector() = default;

    virtual void DetectLandmarks(const cv::Mat& image, std::vector<Face>& faces) = 0;
};