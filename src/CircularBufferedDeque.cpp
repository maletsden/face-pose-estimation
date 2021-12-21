#include "CircularBufferedDeque.h"

#include <opencv2/core/mat.hpp>

template<class T>
CircularBufferedDeque<T>::CircularBufferedDeque(): CircularBufferedDeque(1) {
}

template<class T>
CircularBufferedDeque<T>::CircularBufferedDeque(const std::size_t size)
    : capacity_(std::max(size, 1ul)), buffer(std::make_unique<T[]>(std::max(size, 1ul))) {
}


template<class T>
std::size_t CircularBufferedDeque<T>::Capacity() const noexcept {
  return capacity_;
}

template<class T>
std::size_t CircularBufferedDeque<T>::Size() const noexcept {
  return size_;
}

template<class T>
bool CircularBufferedDeque<T>::IsEmpty() const noexcept {
  return size_ == 0ul;
}

template<class T>
bool CircularBufferedDeque<T>::IsFull() const noexcept {
  return capacity_ == size_;
}

template<class T>
bool CircularBufferedDeque<T>::AddFirst(const T &val) noexcept {
  if (IsFull()) return false;
  if (size_++) start = (start + capacity_ - 1) % capacity_;
  buffer[start] = val;
  return true;
}

template<class T>
bool CircularBufferedDeque<T>::AddLast(const T &val) noexcept {
  if (IsFull()) return false;
  if (size_++) end = (end + 1) % capacity_;
  buffer[end] = val;
  return true;
}

template<class T>
void CircularBufferedDeque<T>::PopFirst() noexcept {
  if (--size_) start = (start + 1) % capacity_;
}

template<class T>
void CircularBufferedDeque<T>::PopLast() noexcept {
  if (--size_) end = (end + capacity_ - 1) % capacity_;
}

template<class T>
const T &CircularBufferedDeque<T>::GetFirst() const noexcept {
  return buffer[start];
}

template<class T>
T &CircularBufferedDeque<T>::GetFirst() noexcept {
  return buffer[start];
}

template<class T>
const T &CircularBufferedDeque<T>::GetLast() const noexcept {
  return buffer[end];
}

template<class T>
T &CircularBufferedDeque<T>::GetLast() noexcept {
  return buffer[end];
}

template<class T>
const T &CircularBufferedDeque<T>::operator[](std::size_t idx) const noexcept {
  return buffer[(start + idx) % capacity_];
}

template<class T>
T &CircularBufferedDeque<T>::operator[](std::size_t idx) noexcept {
  return buffer[(start + idx) % capacity_];
}

template
class CircularBufferedDeque<cv::Mat>;
