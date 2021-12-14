#include <algorithm>
#include <numeric>

#include "Face.h"
#include "Matcher.h"

template<class MatchableType, class Enable>
std::vector<uint8_t> Matcher::Match(
    const std::vector<MatchableType>& newFrameObjects,
    const std::vector<MatchableType>& previousFrameObjects)
{
    if (previousFrameObjects.empty())
    {
        return std::vector<uint8_t>(newFrameObjects.size(), NewObjectLabel);
    }

    // Vector of matches:
    // (index is object index in current frame) - (matches[i] value is object index in previous frame or -1 if new object).
    std::vector<uint8_t> matches(newFrameObjects.size(), NewObjectLabel);
    // Vector of matched objects mask:
    // (index is object index in previos frame) - (previousObjectsMatchMask[i] tells whether match is found for this object).
    std::vector<uint8_t> previousObjectsMatchMask(previousFrameObjects.size(), UnmatchedObjectLabel);

    std::vector<ObjectCorrespondenceCost> objectCosts;

    objectCosts.reserve(newFrameObjects.size() * previousFrameObjects.size());

    // Fill the vector of costs and correspondences.
    for (uint8_t i = 0; i < newFrameObjects.size(); ++i)
    {
        for (uint8_t j = 0; j < previousFrameObjects.size(); ++j)
        {
            const auto currentObjectCost = newFrameObjects[i].Cost(previousFrameObjects[j]);
            if (currentObjectCost > MinCostThreshold)
            {
                objectCosts.push_back({ currentObjectCost, i, j });
            }
        }
    }

    // Sort the vector of costs and correspondences in descending order.
    std::sort(
        objectCosts.begin(),
        objectCosts.end(),
        [](const auto& a, const auto& b) noexcept -> bool { return a.Value > b.Value; });

    // Go throught the vector of costs and correspondences and fill our matches.
    for (const auto& objectCost : objectCosts)
    {
        if ((matches[objectCost.FirstCollectionIndex] == NewObjectLabel) &&
            (previousObjectsMatchMask[objectCost.SecondCollectionIndex] == UnmatchedObjectLabel))
        {
            matches[objectCost.FirstCollectionIndex] = objectCost.SecondCollectionIndex;
            previousObjectsMatchMask[objectCost.SecondCollectionIndex] = MatchedObjectLabel;
        }
    }

    return matches;
}

template std::vector<uint8_t> Matcher::Match<Face>(const std::vector<Face>& newFrameObjects, const std::vector<Face>& previousFrameObjects);