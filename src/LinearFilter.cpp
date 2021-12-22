#include "LinearFilter.h"

#include <numeric>

LinearFilter::LinearFilter(const cv::Mat &a, const cv::Mat &b)
    : m_y(a.cols), m_x(b.cols), m_a(a.clone()), m_b(b.clone()) {

  for (int i = 0; i < a.cols - 1; ++i) {
    m_y.AddLast(cv::Mat::zeros(cv::Size{1, a.rows}, a.type()));
  }

  for (int i = 0; i < b.cols; ++i) {
    m_x.AddLast(cv::Mat::zeros(cv::Size{1, b.rows}, b.type()));
  }

}

cv::Mat LinearFilter::Filter(const cv::Mat &xn, std::chrono::high_resolution_clock::time_point timestamp) {
  m_x.PopLast();
  m_x.AddFirst(xn.clone());

  cv::Mat yn = cv::Mat::zeros(xn.size(), xn.type());

  for (int i = 0; i < m_b.cols; ++i) {
    yn += m_x[i].mul(m_b.col(i));
  }

  for (int i = 1; i < m_a.cols; ++i) {
    yn -= m_y[i - 1].mul(m_a.col(i));
  }

  yn = yn.mul(m_a.col(0));

  m_y.PopLast();
  m_y.AddFirst(yn.clone());

  return yn;
}

cv::Mat LinearFilter::GetCorrectedState() const noexcept {
  return m_y.GetFirst();
}

template<class T>
LinearFilter LinearFilterFactory::MakeMovingAverageFilter(const std::vector<T> &window, int measurmentNum) {
  cv::Mat a(measurmentNum, 1, IFilter::DataOpenCvType, static_cast<IFilter::DataType>(1));
  cv::Mat b(measurmentNum, window.size(), IFilter::DataOpenCvType);

  const auto windowSum = static_cast<IFilter::DataType>(std::accumulate(window.cbegin(), window.cend(), T(0)));

  for (int i = 0; i < static_cast<int>(window.size()); ++i) {
    b.at<IFilter::DataType>(0, i) = static_cast<IFilter::DataType>(window[i]) / windowSum;
  }

  for (int i = 1; i < static_cast<int>(measurmentNum); ++i) {
    b.row(0).copyTo(b.row(i));
  }

  return {a, b};
}

template LinearFilter LinearFilterFactory::MakeMovingAverageFilter<double>(const std::vector<double> &, int);
template LinearFilter LinearFilterFactory::MakeMovingAverageFilter<float>(const std::vector<float> &, int);
template LinearFilter LinearFilterFactory::MakeMovingAverageFilter<int>(const std::vector<int> &, int);
template LinearFilter LinearFilterFactory::MakeMovingAverageFilter<std::size_t>(const std::vector<std::size_t> &, int);
