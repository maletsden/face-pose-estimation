#pragma once

#include <string>
#include <vector>

#include <opencv2/face.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>

#include "Face.h"
#include "Types.h"

class CameraCalibration;

class DrawFrame
{
public:
    static cv::Mat DrawFaceBoundingBox(const cv::Mat& frame, const std::vector<Face>& faces);
    static cv::Mat DrawEachFaceLandmarks(
        const cv::Mat& frame,
        const std::vector<Face>& faces,
        const std::vector<std::vector<cv::Point2f>>& groundTruthLandmarks = {});
    static cv::Mat DrawFrameRate(const cv::Mat& frame, const std::chrono::milliseconds& duration);
    static cv::Mat DrawPose(const cv::Mat& frame, const std::vector<Face>& faces, const CameraCalibration& cameraCalibration);
    static void WriteImage(const std::string& filePath, const cv::Mat& image, const std::string& fileNameEnding);

    static const std::string FaceFileNameSuffix;
    static const std::string LandmarksFileNameSuffix;
    static const std::string MouthFileNameSuffix;
    static const std::string HeadPoseFileNameSuffix;

private:
    // Draws a poly line by joining
    // successive points between the start and end indices.
    static void DrawPolyline(
        cv::Mat& im,
        const std::vector<cv::Point2f>& landmarks,
        const int start,
        const int end,
        const cv::Scalar& color,
        bool isClosed);
    static void DrawLandmarks(cv::Mat& im, const std::vector<cv::Point2f>& landmarks, const cv::Scalar& color);
};
