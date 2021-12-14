#include "FaceTrackerBase.h"

FaceTrackerBase::FaceTrackerBase(const CameraCalibration& cameraCalibration)
    : m_cameraCalibration(cameraCalibration)
    , m_storage(std::make_unique<FaceStorage>())
{
}

optional<Face> FaceTrackerBase::DetectFace(const cv::Mat& image)
{
    const auto currentTimestamp = std::chrono::high_resolution_clock::now();

    std::vector<Face> faces;
    if (m_faceDetector == nullptr || m_faceLandmarkDetector == nullptr || m_jawsPosesDetector == nullptr)
    {
        throw std::runtime_error("ERROR: FaceTracker was not fully configured.");
    }
    m_faceDetector->DetectBoundingBoxes(image, faces);

    m_faceLandmarkDetector->DetectLandmarks(image, faces);

    m_identityTracker.Track(m_storage->GetObjects(), faces);

    m_jawsPosesDetector->DetectJawsPoses(faces);

    m_storage->Update(faces, currentTimestamp);

    m_storage->SmoothObjects(faces);

    auto face = m_faceSelector->SelectTargetFace(faces, m_storage->GetObjects());

    return face;
}
