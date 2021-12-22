#pragma once

#include <memory>

#include "FaceTrackerBase.h"
#include "FaceTrackerTypes.h"
#include "IPoseDetector.h"
#include "Types.h"
#include "IJawPoseDetector.h"
#include "IFaceSelector.h"

template<FaceTrackerTypes FaceTrackerType>
class FaceTracker : public FaceTrackerBase
{
public:
    explicit FaceTracker(const CameraCalibration& cameraCalibration, const std::string& assetsPath = "../../resources");
};

template<>
class FaceTracker<FaceTrackerTypes::Custom> : public FaceTrackerBase
{
public:
    explicit FaceTracker(const CameraCalibration& cameraCalibration);
    void SetFaceDetector(std::unique_ptr<IFaceDetector>&& faceDetector) noexcept;
    void SetFaceLandmarksDetector(std::unique_ptr<IFaceLandmarksDetector>&& faceLandmarkDetector) noexcept;
    void SetJawsPosesDetector(std::unique_ptr<IJawPoseDetector>&& jawsPosesDetector) noexcept;
    void SetFaceSelector(std::unique_ptr<IFaceSelector>&& faceSelector) noexcept;
};
