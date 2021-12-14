#pragma once

#include <array>
#include <opencv2/opencv.hpp>

#include "Types.h"

struct PoseTransformation
{
    cv::Mat RotationVector;
    cv::Mat TranslationVector;
    Pose TransformationMatrix;

    static Pose CalculateTransformationMatrix(const cv::Mat& rotationVector, const cv::Mat& translationVector);
};
