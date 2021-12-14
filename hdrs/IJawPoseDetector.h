#pragma once

#include <vector>

#include "Face.h"

class IJawPoseDetector
{
public:
    virtual ~IJawPoseDetector() = default;

    virtual void DetectJawsPoses(std::vector<Face>& faces) = 0;
};
