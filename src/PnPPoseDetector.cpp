#include "PnPPoseDetector.h"

#include <cmath>

#include "PoseTransformation.h"

const cv::Mat PnPPoseDetector::DefaultTranslationVector = (cv::Mat_<double>(1, 3) << 0., 0., 500.);

const cv::Mat PnPPoseDetector::DefaultRotationVector = { cv::Mat(1, 3, CV_64FC1, { 0., 0., 0. }) };

void PnPPoseDetector::DetectPose(
    const FaceLandmarks& faceLandmarks,
    PoseTransformation& pose,
    const std::vector<cv::Point3d>& modelPoints,
    const std::vector<int>& modelPointsIndices)
{
    if (faceLandmarks.empty())
    {
        return;
    }

    // Prepare face points for perspective solve.
    std::vector<cv::Point2d> imagePoints;
    imagePoints.reserve(modelPointsIndices.size());

    for (const auto& index : modelPointsIndices)
    {
        imagePoints.push_back({ faceLandmarks[index].x, faceLandmarks[index].y });
    }

    if (pose.TranslationVector.empty() || std::abs(pose.TransformationMatrix.at<double>(0, 3)) > InvalidTranslation ||
        std::abs(pose.TransformationMatrix.at<double>(1, 3)) > InvalidTranslation ||
        std::abs(pose.TransformationMatrix.at<double>(2, 3)) > InvalidTranslation)
    {
        pose.RotationVector = DefaultRotationVector.clone();
        pose.TranslationVector = DefaultTranslationVector.clone();
    }

    // Find head pose based on 3D points in head model coordinate system and their observations in the image.
    // Use previous observation as initial guess for the optimization.
    cv::solvePnP(
        modelPoints,
        imagePoints,
        m_cameraCalibration.GetCameraMatrix(),
        m_cameraCalibration.GetDistortionCoefficients(),
        pose.RotationVector,
        pose.TranslationVector,
        true);

    const auto objectPoint = std::vector<cv::Point3d>{ { 0., 0., 0 } };
    std::vector<cv::Point2d> projectedObjectPoint;

    cv::projectPoints(
        objectPoint,
        pose.RotationVector,
        pose.TranslationVector,
        m_cameraCalibration.GetCameraMatrix(),
        m_cameraCalibration.GetDistortionCoefficients(),
        projectedObjectPoint);

    // Save pose.
    pose.TransformationMatrix = PoseTransformation::CalculateTransformationMatrix(pose.RotationVector, pose.TranslationVector);
}
