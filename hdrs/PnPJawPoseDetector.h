#pragma once

#include <memory>

#include "IJawPoseDetector.h"
#include "IPoseDetector.h"
#include "CameraCalibration.h"

class PnPJawPoseDetector : public IJawPoseDetector
{
public:
    PnPJawPoseDetector(const CameraCalibration& cameraCalibration);

    void DetectJawsPoses(std::vector<Face>& faces) override;

protected:
    std::vector<cv::Point3d> m_upperJawModelPoints;
    std::vector<int> m_upperJawModelPointsIndices;
    std::vector<cv::Point3d> m_lowerJawModelPoints;
    std::vector<int> m_lowerJawModelPointsIndices;

private:
    const CameraCalibration& m_cameraCalibration;
    std::unique_ptr<IPoseDetector> m_poseDetector;
};
