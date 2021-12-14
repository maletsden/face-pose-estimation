#pragma once

#include <vector>

#include "CustomOptional.h"
#include "CameraCalibration.h"
#include "Face.h"
#include "IFaceSelector.h"

class FaceSelector : public IFaceSelector
{
public:
    explicit FaceSelector(const CameraCalibration& cameraCalibration);
    optional<Face> SelectTargetFace(
        const std::vector<Face>& faces,
        const std::vector<Face>& storageFaces) override;

private:
    static constexpr float s_faceBoundingBoxMinAreaPercent{ 3.f };
    static constexpr uint32_t InvalidId = std::numeric_limits<uint32_t>::max();

    uint32_t m_id{ InvalidId };

    const float m_faceBoundingBoxMinArea;
    const cv::Point2f m_frameCenter;
};
