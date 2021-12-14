#pragma once

#include <vector>

#include "CustomOptional.h"
#include "Face.h"

class IFaceSelector
{
public:
    virtual optional<Face> SelectTargetFace(
        const std::vector<Face>& faces,
        const std::vector<Face>& storageFaces) = 0;
};