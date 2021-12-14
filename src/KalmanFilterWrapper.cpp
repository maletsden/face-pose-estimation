#include "KalmanFilterWrapper.h"

KalmanFilterWrapper::KalmanFilterWrapper(
    std::chrono::high_resolution_clock::time_point timestamp,
    const PoseTransformation& pose,
    const int numberOfDynamicParameters,
    const int numberOfMeasureParameters)
    : m_lastTimestamp(timestamp)
    , m_numberOfDynamicParameters(numberOfDynamicParameters)
    , m_numberOfMeasureParameters(numberOfMeasureParameters)

{
    m_kalmanFilter = cv::KalmanFilter(numberOfDynamicParameters, numberOfMeasureParameters, 0, DataOpenCvType);

    m_kalmanFilter.transitionMatrix = cv::Mat::eye({ numberOfDynamicParameters, numberOfDynamicParameters }, DataOpenCvType);

    m_kalmanFilter.measurementMatrix = cv::Mat::eye({ numberOfDynamicParameters, numberOfMeasureParameters }, DataOpenCvType);

    m_kalmanFilter.processNoiseCov =
        static_cast<DataType>(7e-7) * cv ::Mat::eye({ numberOfDynamicParameters, numberOfDynamicParameters }, DataOpenCvType);

    m_kalmanFilter.measurementNoiseCov = cv::Mat::eye({ numberOfMeasureParameters, numberOfMeasureParameters }, DataOpenCvType);
    m_kalmanFilter.measurementNoiseCov.at<DataType>(0, 0) = static_cast<DataType>(0.4);
    m_kalmanFilter.measurementNoiseCov.at<DataType>(1, 1) = static_cast<DataType>(0.4);
    m_kalmanFilter.measurementNoiseCov.at<DataType>(2, 2) = static_cast<DataType>(1);
    m_kalmanFilter.measurementNoiseCov.at<DataType>(3, 3) = static_cast<DataType>(0.06);
    m_kalmanFilter.measurementNoiseCov.at<DataType>(4, 4) = static_cast<DataType>(0.06);
    m_kalmanFilter.measurementNoiseCov.at<DataType>(5, 5) = static_cast<DataType>(0.2);

    m_kalmanFilter.errorCovPre =
        static_cast<DataType>(10) * cv::Mat::eye({ numberOfDynamicParameters, numberOfDynamicParameters }, DataOpenCvType);

    m_kalmanFilter.statePost.at<DataType>(0, 0) = static_cast<DataType>(pose.RotationVector.at<DataType>(0, 0));
    m_kalmanFilter.statePost.at<DataType>(1, 0) = static_cast<DataType>(pose.RotationVector.at<DataType>(0, 1));
    m_kalmanFilter.statePost.at<DataType>(2, 0) = static_cast<DataType>(pose.RotationVector.at<DataType>(0, 2));
    m_kalmanFilter.statePost.at<DataType>(3, 0) = static_cast<DataType>(pose.TranslationVector.at<DataType>(0, 0));
    m_kalmanFilter.statePost.at<DataType>(4, 0) = static_cast<DataType>(pose.TranslationVector.at<DataType>(0, 1));
    m_kalmanFilter.statePost.at<DataType>(5, 0) = static_cast<DataType>(pose.TranslationVector.at<DataType>(0, 2));

    m_kalmanFilter.statePost.at<DataType>(6, 0) = static_cast<DataType>(1e-6);
    m_kalmanFilter.statePost.at<DataType>(7, 0) = static_cast<DataType>(1e-6);
    m_kalmanFilter.statePost.at<DataType>(8, 0) = static_cast<DataType>(1e-6);
    m_kalmanFilter.statePost.at<DataType>(9, 0) = static_cast<DataType>(1e-4);
    m_kalmanFilter.statePost.at<DataType>(10, 0) = static_cast<DataType>(1e-4);
    m_kalmanFilter.statePost.at<DataType>(11, 0) = static_cast<DataType>(1e-4);
}

cv::Mat KalmanFilterWrapper::ComputeTransitionMatrix(const DataType dt) const noexcept
{
    cv::Mat transitionMatrix = cv::Mat::eye({ m_numberOfDynamicParameters, m_numberOfDynamicParameters }, DataOpenCvType);

    for (auto i = 0; i < m_numberOfMeasureParameters; ++i)
    {
        transitionMatrix.at<DataType>(i, i + m_numberOfMeasureParameters) = dt;
    }
    return transitionMatrix;
}

cv::Mat KalmanFilterWrapper::Filter(const cv::Mat& measurment, std::chrono::high_resolution_clock::time_point timestamp)
{
    const auto dt = std::chrono::duration_cast<std::chrono::milliseconds>(timestamp - m_lastTimestamp).count();

    m_kalmanFilter.transitionMatrix = ComputeTransitionMatrix(static_cast<DataType>(dt));

    m_lastTimestamp = timestamp;

    m_kalmanFilter.predict();

    return m_kalmanFilter.correct(measurment);
}

cv::Mat KalmanFilterWrapper::GetCorrectedState() const noexcept
{
    return m_kalmanFilter.statePost;
}
