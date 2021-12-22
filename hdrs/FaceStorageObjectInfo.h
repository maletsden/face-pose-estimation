#pragma once

#include "Face.h"
#include "StorageObjectInfo.h"
#include "LinearFilter.h"

struct FaceStorageObjectInfo : public StorageObjectInfo<Face> {
  FaceStorageObjectInfo() = default;

  FaceStorageObjectInfo(const uint16_t dataIndex, const std::chrono::high_resolution_clock::time_point timestamp,
                        const Face &face)
      : StorageObjectInfo(dataIndex, timestamp, face),
        UpperJawFilter(LinearFilterFactory::MakeMovingAverageFilter(std::vector<double>{1, 3, 5, 3, 1}, 6)),
        LowerJawFilter(LinearFilterFactory::MakeMovingAverageFilter(std::vector<double>{1, 3, 5, 3, 1}, 6)) {
  }

  LinearFilter UpperJawFilter;
  LinearFilter LowerJawFilter;
};
