#include "CameraCalibration.h"

CameraCalibration::CameraCalibration() = default;

CameraCalibration::CameraCalibration(const int frameWidth, const int frameHeight)
    : CameraCalibration::CameraCalibration(CameraIntrinsics{ frameWidth,
                                                             frameHeight,
                                                             static_cast<double>(frameWidth),
                                                             static_cast<double>(frameWidth),
                                                             static_cast<double>(frameWidth) / 2,
                                                             static_cast<double>(frameHeight) / 2 })

{
}

CameraCalibration::CameraCalibration(const int frameWidth, const int frameHeight, cv::Mat&& cameraMatrix, cv::Mat&& distortionCoefficients)
    : m_cameraMatrix(std::move(cameraMatrix))
    , m_distortionCoefficients(std::move(distortionCoefficients))
{
    m_cameraIntrinsics.FrameWidth = frameWidth;
    m_cameraIntrinsics.FrameHeight = frameHeight;
    m_cameraIntrinsics.Fx = m_cameraMatrix.at<double>(0, 0);
    m_cameraIntrinsics.Fy = m_cameraMatrix.at<double>(1, 1);
    m_cameraIntrinsics.Cx = m_cameraMatrix.at<double>(0, 3);
    m_cameraIntrinsics.Cy = m_cameraMatrix.at<double>(1, 3);
}

CameraCalibration::CameraCalibration(const CameraIntrinsics& cameraIntrinsics)
{
    m_cameraIntrinsics = cameraIntrinsics;
    m_cameraMatrix =
        (cv::Mat_<double>(3, 3) << cameraIntrinsics.Fx, 0., cameraIntrinsics.Cx, 0., cameraIntrinsics.Fy, cameraIntrinsics.Cy, 0., 0., 1.);

    m_distortionCoefficients = cv::Mat(5, 1, CV_64F, cv::Scalar(0));
}

int CameraCalibration::GetFrameWidth() const noexcept
{
    return m_cameraIntrinsics.FrameWidth;
}

int CameraCalibration::GetFrameHeight() const noexcept
{
    return m_cameraIntrinsics.FrameHeight;
}
double CameraCalibration::GetFx() const noexcept
{
    return m_cameraIntrinsics.Fx;
}

double CameraCalibration::GetFy() const noexcept
{
    return m_cameraIntrinsics.Fy;
}

double CameraCalibration::GetCx() const noexcept
{
    return m_cameraIntrinsics.Cx;
}

double CameraCalibration::GetCy() const noexcept
{
    return m_cameraIntrinsics.Cy;
}

const cv::Mat& CameraCalibration::GetCameraMatrix() const noexcept
{
    return m_cameraMatrix;
}

const cv::Mat& CameraCalibration::GetDistortionCoefficients() const noexcept
{
    return m_distortionCoefficients;
}
