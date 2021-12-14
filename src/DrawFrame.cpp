#include "DrawFrame.h"

#include <sstream>

#include "CameraCalibration.h"
#include "Constants.h"

const auto GroundTruthColor = cv::Scalar(255, 200, 0);
const auto DetectedColor = cv::Scalar(0, 200, 255);

const std::string DrawFrame::FaceFileNameSuffix = "Face";
const std::string DrawFrame::LandmarksFileNameSuffix = "Landmarks";
const std::string DrawFrame::MouthFileNameSuffix = "Mouth";
const std::string DrawFrame::HeadPoseFileNameSuffix = "HeadPose";

void DrawFrame::DrawPolyline(
    cv::Mat& im,
    const std::vector<cv::Point2f>& landmarks,
    const int start,
    const int end,
    const cv::Scalar& color,
    bool isClosed = false)
{
    // Gather all points between the start and end indices.
    std::vector<cv::Point> points;
    points.reserve(end - start + 1);
    for (int i = start; i <= end; ++i)
    {
        points.emplace_back(static_cast<int>(landmarks[i].x), static_cast<int>(landmarks[i].y));
    }

    // Draw polylines.
    polylines(im, points, isClosed, color, 2, 16);
}

cv::Mat DrawFrame::DrawFaceBoundingBox(const cv::Mat& frame, const std::vector<Face>& faces)
{
    cv::Mat frameFace;
    frame.copyTo(frameFace);

    for (const auto& face : faces)
    {
        cv::rectangle(frameFace, face.BoundingBox, cv::Scalar(0, 255, 0), 3);
    }
    return frameFace;
}

void DrawFrame::DrawLandmarks(cv::Mat& im, const std::vector<cv::Point2f>& landmarks, const cv::Scalar& color)
{
    // Draw face for the 72-point model.
    if (landmarks.size() == Constants::FaceLandmarksNum)
    {
        DrawPolyline(im, landmarks, Constants::JawLineLandmarks::Begin, Constants::JawLineLandmarks::End - 1, color);  // Jaw line
        DrawPolyline(
            im,
            landmarks,
            Constants::EyebrowLandmarks::LeftBegin,
            Constants::EyebrowLandmarks::LeftEnd - 1,
            color);  // Left eyebrow
        DrawPolyline(
            im,
            landmarks,
            Constants::EyebrowLandmarks::RightBegin,
            Constants::EyebrowLandmarks::RightEnd - 1,
            color);  // Right eyebrow
        DrawPolyline(im, landmarks, Constants::NoseLandmarks::BridgeBegin, Constants::NoseLandmarks::BridgeEnd - 1, color);  // Nose bridge
        DrawPolyline(
            im,
            landmarks,
            Constants::NoseLandmarks::LowerBegin - 1,
            Constants::NoseLandmarks::LowerEnd - 1,
            color,
            true);  // Lower nose
        DrawPolyline(im, landmarks, Constants::EyeLandmarks::LeftBegin, Constants::EyeLandmarks::LeftEnd - 1, color, true);  // Left eye
        DrawPolyline(im, landmarks, Constants::EyeLandmarks::RightBegin, Constants::EyeLandmarks::RightEnd - 1, color, true);  // Right Eye
        DrawPolyline(
            im,
            landmarks,
            Constants::LipsLandmarks::OuterBegin,
            Constants::LipsLandmarks::OuterEnd - 1,
            color,
            true);  // Outer lip
        DrawPolyline(
            im,
            landmarks,
            Constants::LipsLandmarks::InnerBegin,
            Constants::LipsLandmarks::InnerEnd - 1,
            color,
            true);  // Inner lip
    }
    else
    {
        // If the number of points is not 68, we do not know which
        // points correspond to which facial features. So, we draw
        // one dot per landamrk.
        for (const auto& landmark : landmarks)
        {
            circle(im, landmark, 3, color, cv::FILLED);
        }
    }
}

cv::Mat DrawFrame::DrawEachFaceLandmarks(
    const cv::Mat& frame,
    const std::vector<Face>& faces,
    const std::vector<std::vector<cv::Point2f>>& groundTruthLandmarks)
{
    cv::Mat frameLandmarks;
    frame.copyTo(frameLandmarks);

    // Draw ground truth landmarks if available.
    if (!groundTruthLandmarks.empty())
    {
        for (const auto& groundTruthLandmark : groundTruthLandmarks)
        {
            DrawLandmarks(frameLandmarks, groundTruthLandmark, GroundTruthColor);
        }
    }

    // Draw detected landmarks.
    for (const auto& face : faces)
    {
        DrawLandmarks(frameLandmarks, face.Landmarks, DetectedColor);
    }
    return frameLandmarks;
}

cv::Mat DrawFrame::DrawPose(const cv::Mat& frame, const std::vector<Face>& faces, const CameraCalibration& cameraCalibration)
{
    cv::Mat framePose;
    frame.copyTo(framePose);

    if (faces.empty())
    {
        return framePose;
    }

    const auto noseIndex = 30;

    const auto& cameraMatrix = cameraCalibration.GetCameraMatrix();
    const auto& distortionCoefficients = cameraCalibration.GetDistortionCoefficients();
    for (size_t i = 0; i < faces.size(); ++i)
    {
        const auto poseTransformation = faces[i].UpperJawPose.TransformationMatrix;
        cv::Mat rotationVector;
        cv::Rodrigues(poseTransformation(cv::Rect(0, 0, 3, 3)), rotationVector);
        const auto translationVector = cv::Mat(poseTransformation(cv::Rect(3, 0, 1, 3)));

        // Obtain nose tip direction for later visualization (in future can be moved to visualization side).
        const auto detectedFaceLandmarks = faces[i].Landmarks;
        const auto pointAtInfinityZ = std::vector<cv::Point3d>{ cv::Point3d(0., 0., 100.0) };
        std::vector<cv::Point2d> directionZ;
        cv::projectPoints(pointAtInfinityZ, rotationVector, translationVector, cameraMatrix, distortionCoefficients, directionZ);
        cv::arrowedLine(framePose, detectedFaceLandmarks[noseIndex], directionZ[0], cv::Scalar(255, 0, 0), 2);

        const auto pointAtInfinityY = std::vector<cv::Point3d>{ cv::Point3d(0., 100., 0.) };
        std::vector<cv::Point2d> directionY;
        cv::projectPoints(pointAtInfinityY, rotationVector, translationVector, cameraMatrix, distortionCoefficients, directionY);
        cv::arrowedLine(framePose, detectedFaceLandmarks[noseIndex], directionY[0], cv::Scalar(0, 255, 0), 2);

        const auto pointAtInfinityX = std::vector<cv::Point3d>{ cv::Point3d(100., 0., 0.) };
        std::vector<cv::Point2d> directionX;
        cv::projectPoints(pointAtInfinityX, rotationVector, translationVector, cameraMatrix, distortionCoefficients, directionX);
        cv::arrowedLine(framePose, detectedFaceLandmarks[noseIndex], directionX[0], cv::Scalar(0, 0, 255), 2);
    }
    return framePose;
}

cv::Mat DrawFrame::DrawFrameRate(const cv::Mat& frame, const std::chrono::milliseconds& duration)
{
    cv::Mat result(frame.clone());
    cv::putText(
        result,
        cv::format("Processing time %d milliseconds", duration),
        cv::Point(20, 20),
        cv::FONT_HERSHEY_SIMPLEX,
        0.6,
        cv::Scalar(0, 0, 255));
    return result;
}

void DrawFrame::WriteImage(const std::string& filePath, const cv::Mat& image, const std::string& fileNameEnding)
{
    const auto outputFolder = "output\\";
    const auto imgName = filePath.substr(0, filePath.find('.'));
    const auto imgExtention = filePath.substr(filePath.find('.'), filePath.size());

    std::stringstream imagePath;
    imagePath << outputFolder << imgName << fileNameEnding << imgExtention;

    cv::imwrite(imagePath.str(), image);
}
