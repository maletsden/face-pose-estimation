#pragma once

#include <chrono>
#include <vector>

#include "IMatchable.h"
#include "PoseTransformation.h"
#include "Types.h"
#include "Matcher.h"

class Face : public IMatchable
{
public:
    uint32_t Id;
    cv::Rect BoundingBox;
    FaceLandmarks Landmarks;
    PoseTransformation UpperJawPose;
    PoseTransformation LowerJawPose;

private:
    friend class Matcher;

    double Cost(const IMatchable& type) const override;
};