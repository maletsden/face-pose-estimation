#pragma once

#include <chrono>
#include <unordered_map>
#include <vector>

#include "CustomOptional.h"
#include "StorageObjectInfo.h"

template<class Type, class ObjectInfo, class = std::enable_if_t<std::is_base_of<StorageObjectInfo<Type>, ObjectInfo>::value>>
class Storage
{
public:
    virtual ~Storage();

    void Update(const std::vector<Type>& objects, std::chrono::high_resolution_clock::time_point currentTimestamp);
    void SmoothObjects(std::vector<Type>& objects);

    const std::vector<Type>& GetObjects() const noexcept;
    optional<Type> GetObject(uint32_t id);
    bool HasObject(uint32_t id) const noexcept;
    const ObjectInfo& GetObjectInfo(uint32_t id) const;

protected:
    virtual void SmoothObject(Type& object) = 0;
    virtual void Clear(std::chrono::high_resolution_clock::time_point currentTimestamp);
    virtual void UpdateObjectInfo(const Type& object, std::chrono::high_resolution_clock::time_point currentTimestamp);

    ObjectInfo& GetObjectInfo(uint32_t id);

    // If object don't appear for 100ms then it will be deleted
    static constexpr auto MaxAbsenceTime = std::chrono::milliseconds(100);

    std::unordered_map<uint32_t, ObjectInfo> m_map;
    std::vector<Type> m_data;
};
