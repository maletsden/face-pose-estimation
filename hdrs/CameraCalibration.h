#pragma once

#include "opencv2/core/mat.hpp"

class CameraCalibration
{
public:
    struct CameraIntrinsics
    {
        int FrameWidth;
        int FrameHeight;
        double Fx, Fy;
        double Cx, Cy;
    };

    CameraCalibration();
    CameraCalibration(const int frameWidth, const int frameHeight);
    CameraCalibration(const int frameWidth, const int frameHeight, cv::Mat&& cameraMatrix, cv::Mat&& distortionCoefficients);
    explicit CameraCalibration(const CameraIntrinsics& cameraIntrinsics);

    int GetFrameWidth() const noexcept;
    int GetFrameHeight() const noexcept;
    double GetFx() const noexcept;
    double GetFy() const noexcept;
    double GetCx() const noexcept;
    double GetCy() const noexcept;
    const cv::Mat& GetCameraMatrix() const noexcept;
    const cv::Mat& GetDistortionCoefficients() const noexcept;

private:
    CameraIntrinsics m_cameraIntrinsics;
    cv::Mat m_cameraMatrix;
    cv::Mat m_distortionCoefficients;
};
