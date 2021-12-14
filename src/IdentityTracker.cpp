#include "IdentityTracker.h"

#include <algorithm>
#include <utility>

#include "Face.h"
#include "Matcher.h"
#include "Types.h"

template<class MatchableType, class Enable>
uint32_t IdentityTracker<MatchableType, Enable>::AvailableId = 0;

template<class MatchableType, class Enable>
void IdentityTracker<MatchableType, Enable>::Track(
    const std::vector<MatchableType>& previousObjects,
    std::vector<MatchableType>& currentFrameObjects)
{
    // Update our storage with new frame.
    const auto matches = Matcher::Match<MatchableType>(currentFrameObjects, previousObjects);
    for (auto i = 0; i < matches.size(); i++)
    {
        if (matches[i] == Matcher::NewObjectLabel)
        {
            currentFrameObjects[i].Id = ++AvailableId;
        }
        else
        {
            currentFrameObjects[i].Id = previousObjects[matches[i]].Id;
            currentFrameObjects[i].UpperJawPose = previousObjects[matches[i]].UpperJawPose;
            currentFrameObjects[i].LowerJawPose = previousObjects[matches[i]].LowerJawPose;
        }
    }
}

template class IdentityTracker<Face>;