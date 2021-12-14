#pragma once

#include <algorithm>
#include <cstdint>
#include <vector>

#include "IMatchable.h"

class Matcher
{
public:
    template<class MatchableType, class = std::enable_if_t<std::is_base_of<IMatchable, MatchableType>::value>>
    static std::vector<uint8_t> Match(
        const std::vector<MatchableType>& currentFrameObjects,
        const std::vector<MatchableType>& previousFrameObjects);

    // Objects that are new will be labeled with this value.
    static constexpr uint8_t NewObjectLabel = std::numeric_limits<uint8_t>::max();

private:

    // Minumum intersection over a union of face bounding boxes (minimum 50% intersection).
    static constexpr double MinCostThreshold = 0.5;
    static constexpr bool UnmatchedObjectLabel = false;
    static constexpr bool MatchedObjectLabel = true;

    struct ObjectCorrespondenceCost
    {
        double Value;
        uint8_t FirstCollectionIndex;
        uint8_t SecondCollectionIndex;
    };
};