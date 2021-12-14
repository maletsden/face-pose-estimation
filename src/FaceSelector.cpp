#include "FaceSelector.h"

FaceSelector::FaceSelector(const CameraCalibration& cameraCalibration)
    : m_faceBoundingBoxMinArea(
          s_faceBoundingBoxMinAreaPercent / 100.f * static_cast<float>(cameraCalibration.GetFrameWidth()) *
          static_cast<float>(cameraCalibration.GetFrameWidth()))
    , m_frameCenter(cv::Point2f(
          static_cast<float>(cameraCalibration.GetFrameWidth() >> 1),
          static_cast<float>(cameraCalibration.GetFrameHeight() >> 1)))
{
}

optional<Face> FaceSelector::SelectTargetFace(
    const std::vector<Face>& faces,
    const std::vector<Face>& storageFaces)
{
    if (faces.empty())
    {
        return nullopt;
    }

    // Find the face we were tracking before by its id.
    const auto targetFace = std::find_if(faces.cbegin(), faces.cend(), [id = m_id](const auto& a) noexcept -> bool { return a.Id == id; });
    if (targetFace != faces.end())
    {
        return optional<Face>{ *targetFace };
    }

    // If we don't find needed face in current frame then find this face in storage.
    // If we do, the previously tracked face might still re-appear.
    // In this case skip looking for a new face to track and return empty face for current frame.
    const auto storageTargetFace =
        std::find_if(storageFaces.cbegin(), storageFaces.cend(), [id = m_id](const auto& a) noexcept -> bool { return a.Id == id; });
    if (storageTargetFace != storageFaces.end())
    {
        return nullopt;
    }

    auto minDistanceToFrameCenter = std::numeric_limits<double>::max();
    size_t selectedFaceIdx = InvalidId;
    for (size_t i = 0; i < faces.size(); ++i)
    {
        const auto& faceBoundingBox = faces[i].BoundingBox;
        const auto faceBoundingBoxArea = static_cast<float>(faceBoundingBox.area());

        // Impose min bounding box area constraint to filter out far away faces and false positives.
        if (faceBoundingBoxArea <= m_faceBoundingBoxMinArea)
        {
            continue;
        }

        const cv::Point2f faceCenter{
            static_cast<float>(faceBoundingBox.x + (faceBoundingBox.width >> 1)),
            static_cast<float>(faceBoundingBox.y + (faceBoundingBox.height >> 1)) };

        // Select face witch is closest to the center.
        const auto distanceToFrameCenter = cv::norm(m_frameCenter - faceCenter) / faceBoundingBoxArea;
        if (minDistanceToFrameCenter > distanceToFrameCenter)
        {
            minDistanceToFrameCenter = distanceToFrameCenter;
            selectedFaceIdx = i;
        }
    }
    m_id = faces[selectedFaceIdx].Id;

    return optional<Face>{ faces[selectedFaceIdx] };
}