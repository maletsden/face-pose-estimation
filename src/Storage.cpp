#include "Storage.h"

#include "Face.h"
#include "FaceStorageObjectInfo.h"

template<class Type, class ObjectInfo, class Enable>
Storage<Type, ObjectInfo, Enable>::~Storage() = default;

template<class Type, class ObjectInfo, class Enable>
void Storage<Type, ObjectInfo, Enable>::Update(
    const std::vector<Type>& objects,
    std::chrono::high_resolution_clock::time_point currentTimestamp)
{
    for (const auto& object : objects)
    {
        const auto currentObjectId = object.Id;

        if (HasObject(currentObjectId))
        {
            const auto currentObjectIndex = m_map[currentObjectId].DataIndex;
            UpdateObjectInfo(object, currentTimestamp);
            m_data[currentObjectIndex] = object;
        }
        else
        {
            m_map[currentObjectId] = ObjectInfo{ static_cast<uint16_t>(m_data.size()), currentTimestamp, object };
            m_data.push_back(object);
        }
    }

    Clear(currentTimestamp);
}

template<class Type, class ObjectInfo, class Enable>
void Storage<Type, ObjectInfo, Enable>::SmoothObjects(std::vector<Type>& objects)
{
    for (auto& object : objects)
    {
        if (!HasObject(object.Id))
        {
            continue;
        }

        SmoothObject(object);
    }
}

template<class Type, class ObjectInfo, class Enable>
void Storage<Type, ObjectInfo, Enable>::UpdateObjectInfo(const Type& object, std::chrono::high_resolution_clock::time_point currentTimestamp)
{
    m_map[object.Id].Timestamp = currentTimestamp;
}

template<class Type, class ObjectInfo, class Enable>
const std::vector<Type>& Storage<Type, ObjectInfo, Enable>::GetObjects() const noexcept
{
    return m_data;
}

template<class Type, class ObjectInfo, class Enable>
bool Storage<Type, ObjectInfo, Enable>::HasObject(uint32_t id) const noexcept
{
    return m_map.find(id) != m_map.end();
}

template<class Type, class ObjectInfo, class Enable>
ObjectInfo& Storage<Type, ObjectInfo, Enable>::GetObjectInfo(uint32_t id)
{
    return m_map.at(id);
}
template<class Type, class ObjectInfo, class Enable>
const ObjectInfo& Storage<Type, ObjectInfo, Enable>::GetObjectInfo(uint32_t id) const
{
    return m_map.at(id);
}

template<class Type, class ObjectInfo, class Enable>
optional<Type> Storage<Type, ObjectInfo, Enable>::GetObject(uint32_t id)
{
    return HasObject(id) ? optional<Type>{ m_data[m_map.at(id).DataIndex] } : nullopt;
}

template<class Type, class ObjectInfo, class Enable>
void Storage<Type, ObjectInfo, Enable>::Clear(std::chrono::high_resolution_clock::time_point currentTimestamp)
{
    // Delete old faces which don't appear at least for a second.
    for (auto i = 0; i < m_data.size(); ++i)
    {
        if (std::chrono::duration_cast<std::chrono::milliseconds>(currentTimestamp - m_map[m_data[i].Id].Timestamp) > MaxAbsenceTime)
        {
            // Delete from map.
            const auto removedObjectId = m_data[i].Id;
            m_map.erase(removedObjectId);
            const auto lastObjectId = m_data.back().Id;
            m_map[lastObjectId].DataIndex = i;

            // Delete from vector.
            std::iter_swap(m_data.begin() + i, m_data.end() - 1);
            m_data.pop_back();
            --i;
        }
    }
}

template class Storage<Face, FaceStorageObjectInfo>;