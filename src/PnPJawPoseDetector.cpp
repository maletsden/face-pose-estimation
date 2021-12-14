#include "PnPJawPoseDetector.h"
#include "PnPPoseDetector.h"

PnPJawPoseDetector::PnPJawPoseDetector(const CameraCalibration& cameraCalibration)
    : m_cameraCalibration(cameraCalibration)
{
    m_upperJawModelPoints = {
        // 3D face model (millimiters)
        cv::Point3d{ -56.99060822, -67.78783607, -48.37906647 }, cv::Point3d{ -11.01952076, -68.78061867, -84.57347107 },
        cv::Point3d{ 11.01952076, -68.78061867, -84.57347107 },  cv::Point3d{ 56.99060822, -67.78783607, -48.37906647 },
        cv::Point3d{ 0.0, -55.69339943, -85.5603714 },           cv::Point3d{ 0.0, -43.32499504, -94.6967926 },
        cv::Point3d{ 0.0, -30.45712662, -102.5819397 },          cv::Point3d{ 0.0, -18.0, -110.0 },
        cv::Point3d{ -11.97193623, -9.73350233, -86.59844208 },  cv::Point3d{ 0.0, -6.94376898, -92.48444366 },
        cv::Point3d{ 11.97193623, -9.73350233, -86.59844208 },   cv::Point3d{ -37.58148193, -55.01866341, -63.82002258 },
        cv::Point3d{ -15.61013508, -53.88035774, -65.42218018 }, cv::Point3d{ 15.61013508, -53.88035774, -65.42218018 },
        cv::Point3d{ 37.58148193, -55.01866341, -63.82002258 },
    };

    m_upperJawModelPointsIndices = { 17, 21, 22, 26, 27, 28, 29, 30, 31, 33, 35, 36, 39, 42, 45 };

    m_lowerJawModelPoints = {
        // 3D face model (millimiters)
        cv::Point3d{ -59.50613785, 26.93589973, -17.50991201 }, cv::Point3d{ -46.16640854, 41.40571022, -38.98358727 },
        cv::Point3d{ -32.44851303, 53.94389153, -59.23150635 }, cv::Point3d{ -17.10820198, 58.26189232, -71.25484847999999 },
        cv::Point3d{ 0.0, 60.10648918, -73.94098282 },          cv::Point3d{ 17.10820198, 58.26189232, -71.25484847999999 },
        cv::Point3d{ 32.44851303, 53.94389153, -59.00138855 },  cv::Point3d{ 46.16640854, 41.40571022, -38.21890831 },
        cv::Point3d{ 59.50613785, 26.93589973, -17.8536911 },   cv::Point3d{ 8.98734093, 21.23594284, -86.13957977 },
        cv::Point3d{ 0.0, 22.325082780000002, -85.1705246 },    cv::Point3d{ -8.98734093, 21.23594284, -86.13957977 }
    };

    m_lowerJawModelPointsIndices = { 4, 5, 6, 7, 8, 9, 10, 11, 12, 56, 57, 58 };

    m_poseDetector = std::make_unique<PnPPoseDetector>(m_cameraCalibration);
}

void PnPJawPoseDetector::DetectJawsPoses(std::vector<Face>& faces)
{
    for (auto& face : faces)
    {
        m_poseDetector->DetectPose(face.Landmarks, face.UpperJawPose, m_upperJawModelPoints, m_upperJawModelPointsIndices);
        m_poseDetector->DetectPose(face.Landmarks, face.LowerJawPose, m_lowerJawModelPoints, m_lowerJawModelPointsIndices);
    }
}
