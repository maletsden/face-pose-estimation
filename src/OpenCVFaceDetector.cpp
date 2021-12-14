#include "OpenCVFaceDetector.h"

#include <limits>

float OpenCVFaceDetector::s_scaledImageWidth = 200.f;

OpenCVFaceDetector::OpenCVFaceDetector(const HaarCascade cascade, const CameraCalibration& cameraCalibration, std::string assetsPath)
    : m_cameraCalibration(cameraCalibration)
{
    switch (cascade)
    {
        case HaarCascade::FrontalfaceDefault:
            m_faceDetector = cv::CascadeClassifier(assetsPath + "/HaarCascades/haarcascade_frontalface_default.xml");
            break;
        case HaarCascade::FrontalfaceAlt:
            m_faceDetector = cv::CascadeClassifier(assetsPath + "/HaarCascades/haarcascade_frontalface_alt.xml");
            break;
        case HaarCascade::FrontalfaceAlt2:
            m_faceDetector = cv::CascadeClassifier(assetsPath + "/HaarCascades/haarcascade_frontalface_alt2.xml");
            break;
        case HaarCascade::FrontalfaceAltTree:
            m_faceDetector = cv::CascadeClassifier(assetsPath + "/HaarCascades/haarcascade_frontalface_alt_tree.xml");
            break;
        default:
            throw std::runtime_error("ERROR: Used unknown HaarCascade for class initialization.");
    }
}

void OpenCVFaceDetector::DetectBoundingBoxes(const cv::Mat& image, std::vector<Face>& faces)
{
    std::vector<cv::Rect> detectedBoundingBoxes;
    const auto scaleFactorForFaceDetection = static_cast<float>(m_cameraCalibration.GetFrameWidth()) / s_scaledImageWidth;

    // Downscaling an image to increase performance.
    cv::Mat resizedFrame(cvRound(image.rows / scaleFactorForFaceDetection), cvRound(image.cols / scaleFactorForFaceDetection), CV_8UC1);
    cv::resize(image, resizedFrame, resizedFrame.size());

    // Detect faces.
    m_faceDetector.detectMultiScale(
        resizedFrame,             // Image.
        detectedBoundingBoxes,    // Vector of faces.
        1.3,                      // Scale factor.
        3,                        // Minimum posible neighbours of each candidate face rectangle.
        cv::CASCADE_SCALE_IMAGE,  // Flag parameter. It is not used for a new cascade.
        cv::Size(30, 30));        // Minimum possible face size.

    faces.resize(detectedBoundingBoxes.size());
    for (int i = 0; i < detectedBoundingBoxes.size(); ++i)
    {
        faces[i].BoundingBox = {
            cvRound(detectedBoundingBoxes[i].x * scaleFactorForFaceDetection),
            cvRound(detectedBoundingBoxes[i].y * scaleFactorForFaceDetection),
            int(floor(detectedBoundingBoxes[i].width * scaleFactorForFaceDetection)),
            int(floor(detectedBoundingBoxes[i].height * scaleFactorForFaceDetection)) };
    }
}

void OpenCVFaceDetector::SetScaledImageWidth(int width)
{
    s_scaledImageWidth = static_cast<float>(width);
}
