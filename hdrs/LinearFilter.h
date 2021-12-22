#ifndef FACE_POSE_ESTIMATION_LINEAR_FILTER_H
#define FACE_POSE_ESTIMATION_LINEAR_FILTER_H

#include <opencv2/core/mat.hpp>

#include "IFilter.h"
#include "CircularBufferedDeque.h"

class LinearFilter: public IFilter
{
public:
  LinearFilter() = default;
  LinearFilter(const cv::Mat& a, const cv::Mat& b);

  cv::Mat Filter(const cv::Mat& measurement, std::chrono::high_resolution_clock::time_point timestamp) override;
  [[nodiscard]] cv::Mat GetCorrectedState() const noexcept override;

private:
  CircularBufferedDeque<cv::Mat> m_y;
  CircularBufferedDeque<cv::Mat> m_x;
  cv::Mat m_a;
  cv::Mat m_b;
};

class LinearFilterFactory {
public:
  template<class T>
  static LinearFilter MakeMovingAverageFilter(const std::vector<T>& window, int measurmentNum);
};

#endif //FACE_POSE_ESTIMATION_LINEAR_FILTER_H
