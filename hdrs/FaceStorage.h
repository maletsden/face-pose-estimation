#pragma once

#include <utility>

#include "Face.h"
#include "FaceStorageObjectInfo.h"
#include "Storage.h"

class FaceStorage : public Storage<Face, FaceStorageObjectInfo>
{
private:
    void SmoothObject(Face& face) override;
    void UpdateObjectInfo(const Face& face, std::chrono::high_resolution_clock::time_point currentTimestamp) override;
};
