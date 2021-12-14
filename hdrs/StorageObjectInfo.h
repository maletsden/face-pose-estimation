#pragma once

#include <chrono>
#include <utility>

template <class T>
struct StorageObjectInfo
{
    StorageObjectInfo() = default;

    StorageObjectInfo(
        const uint16_t dataIndex,
        const std::chrono::high_resolution_clock::time_point timestamp,
        [[maybe_unused]] const T& object)
        : DataIndex(dataIndex)
        , Timestamp(timestamp)
    {
    }

    uint16_t DataIndex;
    std::chrono::high_resolution_clock::time_point Timestamp;
};
