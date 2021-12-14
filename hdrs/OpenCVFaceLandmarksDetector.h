#pragma once

#include <opencv2/face.hpp>

#include "FacemarkModels.h"
#include "IFaceLandmarksDetector.h"
#include "Types.h"

class OpenCVFaceLandmarksDetector : public IFaceLandmarksDetector
{
public:
    explicit OpenCVFaceLandmarksDetector(const FacemarkModel facemarkModel, std::string assetsPath = "./resources");

    void DetectLandmarks(const cv::Mat& image, std::vector<Face>& faces) override;

private:

    cv::Ptr<cv::face::Facemark> m_facemark;
};
