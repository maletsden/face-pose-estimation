#pragma once

#include <memory>
#include <vector>

#include <opencv2/core/types.hpp>

#include "CameraCalibration.h"
#include "CustomOptional.h"
#include "Face.h"
#include "FaceStorage.h"
#include "IFaceDetector.h"
#include "IFaceLandmarksDetector.h"
#include "IFaceSelector.h"
#include "IJawPoseDetector.h"
#include "IPoseDetector.h"
#include "IdentityTracker.h"
#include "Storage.h"

class FaceTrackerBase
{
public:
    virtual optional<Face> DetectFace(const cv::Mat& image);

    virtual ~FaceTrackerBase() = default;

protected:
    explicit FaceTrackerBase(const CameraCalibration& cameraCalibration);

    std::unique_ptr<IFaceDetector> m_faceDetector;
    std::unique_ptr<IFaceLandmarksDetector> m_faceLandmarkDetector;
    std::unique_ptr<IJawPoseDetector> m_jawsPosesDetector;
    std::unique_ptr<IFaceSelector> m_faceSelector;
    std::unique_ptr<Storage<Face, FaceStorageObjectInfo>> m_storage;

    IdentityTracker<Face> m_identityTracker;
    CameraCalibration m_cameraCalibration;
};
