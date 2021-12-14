#include "Face.h"

double Face::Cost(const IMatchable& type) const
{
    const auto& firstFaceBoundingBox = this->BoundingBox;
    const auto& secondFaceBoundingBox = dynamic_cast<const Face&>(type).BoundingBox;
    if (firstFaceBoundingBox.empty() || secondFaceBoundingBox.empty())
    {
        return 0;
    }
    const auto intersectionArea = (firstFaceBoundingBox & secondFaceBoundingBox).area();
    const auto unionArea = firstFaceBoundingBox.area() + secondFaceBoundingBox.area() - intersectionArea;
    return static_cast<double>(intersectionArea) / unionArea;
}