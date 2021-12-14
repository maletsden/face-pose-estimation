#pragma once

#include <vector>

#include <opencv2/objdetect.hpp>
#include <opencv2/opencv.hpp>

#include "HaarCascades.h"
#include "IFaceDetector.h"
#include "CameraCalibration.h"
#include "Face.h"

class OpenCVFaceDetector : public IFaceDetector
{
public:
    OpenCVFaceDetector(const HaarCascade cascade, const CameraCalibration& cameraCalibration, std::string assetsPath = "./resources");

    static void SetScaledImageWidth(int width);

    void DetectBoundingBoxes(const cv::Mat& image, std::vector<Face>& faces) override;

private:
    static float s_scaledImageWidth;

    cv::CascadeClassifier m_faceDetector;
    const CameraCalibration& m_cameraCalibration;
};
