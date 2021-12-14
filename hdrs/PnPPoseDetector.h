#pragma once

#include <vector>

#include <opencv2/calib3d.hpp>

#include "CameraCalibration.h"
#include "IPoseDetector.h"
#include "Types.h"
#include "CameraCalibration.h"
#include "Face.h"

class PnPPoseDetector : public IPoseDetector
{
public:
    PnPPoseDetector(const CameraCalibration& cameraCalibration)
        : m_cameraCalibration(cameraCalibration)
    {
    }

    void DetectPose(
        const FaceLandmarks& faceLandmarks,
        PoseTransformation& pose,
        const std::vector<cv::Point3d>& modelPoints,
        const std::vector<int>& modelPointsIndices) override;

    static const cv::Mat DefaultRotationVector;
    static const cv::Mat DefaultTranslationVector;

private:
    const CameraCalibration& m_cameraCalibration;

    static constexpr double InvalidTranslation = 2000;
};
