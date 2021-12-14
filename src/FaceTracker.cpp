#include "FaceTracker.h"

#include "CameraCalibration.h"
#include "OpenCVFaceDetector.h"
#include "OpenCVFaceLandmarksDetector.h"
#include "PnPJawPoseDetector.h"
#include "FaceSelector.h"

template<>
FaceTracker<FaceTrackerTypes::OpenCv>::FaceTracker(const CameraCalibration& cameraCalibration, const std::string& assetsPath)
    : FaceTrackerBase(cameraCalibration)
{
    m_faceDetector = std::make_unique<OpenCVFaceDetector>(HaarCascade::FrontalfaceAlt2, m_cameraCalibration, assetsPath);
    m_faceLandmarkDetector = std::make_unique<OpenCVFaceLandmarksDetector>(FacemarkModel::LocalBinaryFeatures, assetsPath);
    m_jawsPosesDetector = std::make_unique<PnPJawPoseDetector>(m_cameraCalibration);
    m_faceSelector = std::make_unique<FaceSelector>(m_cameraCalibration);
}

FaceTracker<FaceTrackerTypes::Custom>::FaceTracker(const CameraCalibration& cameraCalibration)
    : FaceTrackerBase(cameraCalibration)
{
}

void FaceTracker<FaceTrackerTypes::Custom>::SetFaceDatector(std::unique_ptr<IFaceDetector>&& faceDetector) noexcept
{
    m_faceDetector = std::move_if_noexcept(faceDetector);
}

void FaceTracker<FaceTrackerTypes::Custom>::SetFaceLandmarksDetector(std::unique_ptr<IFaceLandmarksDetector>&& faceLandmarkDetector) noexcept
{
    m_faceLandmarkDetector = std::move_if_noexcept(faceLandmarkDetector);
}

void FaceTracker<FaceTrackerTypes::Custom>::SetJawsPosesDetector(std::unique_ptr<IJawPoseDetector>&& jawsPosesDetector) noexcept
{
    m_jawsPosesDetector = std::move_if_noexcept(jawsPosesDetector);
}

void FaceTracker<FaceTrackerTypes::Custom>::SetFaceSelector(std::unique_ptr<IFaceSelector>&& faceSelector) noexcept
{
    m_faceSelector = std::move_if_noexcept(faceSelector);
}

// Explicit (full) class template specialization.

template class FaceTracker<FaceTrackerTypes::OpenCv>;

