#pragma once

#include "Face.h"
#include "KalmanFilterWrapper.h"
#include "StorageObjectInfo.h"

struct FaceStorageObjectInfo : public StorageObjectInfo<Face>
{
    FaceStorageObjectInfo() = default;
    FaceStorageObjectInfo(const uint16_t dataIndex, const std::chrono::high_resolution_clock::time_point timestamp, const Face& face)
        : StorageObjectInfo(dataIndex, timestamp, face)
        , KalmanFilterUpperJaw(timestamp, face.UpperJawPose)
        , KalmanFilterLowerJaw(timestamp, face.LowerJawPose)
    {
    }

    KalmanFilterWrapper KalmanFilterUpperJaw;
    KalmanFilterWrapper KalmanFilterLowerJaw;
};
