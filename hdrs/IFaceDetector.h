#pragma once

#include <vector>

#include <opencv2/objdetect.hpp>
#include <opencv2/opencv.hpp>

#include "Face.h"

class IFaceDetector
{
public:
    virtual ~IFaceDetector() = default;

    virtual void DetectBoundingBoxes(const cv::Mat& image, std::vector<Face>& faces) = 0;
};
