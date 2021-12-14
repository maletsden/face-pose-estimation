#pragma once

#include <type_traits>
#include <vector>
#include <chrono>

#include "IMatchable.h"

template<class MatchableType, class = std::enable_if_t<std::is_base_of<IMatchable, MatchableType>::value>>
class IdentityTracker
{
public:
    void Track(const std::vector<MatchableType>& previousObjects, std::vector<MatchableType>& currentFrameObjects);

private:

    // Counter for object id.
    static uint32_t AvailableId;
};
