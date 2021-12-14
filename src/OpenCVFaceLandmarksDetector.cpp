#include "OpenCVFaceLandmarksDetector.h"

OpenCVFaceLandmarksDetector::OpenCVFaceLandmarksDetector(const FacemarkModel facemarkModel, std::string assetsPath)
{
    m_facemark = cv::face::FacemarkLBF::create();

    switch (facemarkModel)
    {
        case FacemarkModel::LocalBinaryFeatures:
            m_facemark->loadModel(assetsPath + "/FacemarkModels/lbfmodel.xml");
            break;
        case FacemarkModel::ActiveAppearanceModel:
            m_facemark->loadModel(assetsPath + "/FacemarkModels/aammodel.yaml");
            break;
        default:
            throw std::runtime_error("ERROR: Used unknown FacemarkModel for class initialization.");
    }
}

void OpenCVFaceLandmarksDetector::DetectLandmarks(const cv::Mat& image, std::vector<Face>& faces)
{
    std::vector<FaceLandmarks> openCvLandmarks;
    std::vector<cv::Rect> boundingBox(1);

    for (auto& face : faces)
    {
        boundingBox[0] = face.BoundingBox;

        m_facemark->fit(image, boundingBox, openCvLandmarks);

        face.Landmarks = std::move(openCvLandmarks[0]);
    }
}
