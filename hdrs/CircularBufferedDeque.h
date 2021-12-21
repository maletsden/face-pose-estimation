#ifndef FACE_POSE_ESTIMATION_CIRCULAR_BUFFERED_DEQUE_H
#define FACE_POSE_ESTIMATION_CIRCULAR_BUFFERED_DEQUE_H

#include <memory>

template <class T>
class CircularBufferedDeque {
public:
  CircularBufferedDeque();
  explicit CircularBufferedDeque(std::size_t size);

  [[nodiscard]] std::size_t Capacity() const noexcept;
  [[nodiscard]] std::size_t Size() const noexcept;
  [[nodiscard]] bool IsEmpty() const noexcept;
  [[nodiscard]] bool IsFull() const noexcept;

  bool AddFirst(const T &val) noexcept;
  bool AddLast(const T& val) noexcept;
  void PopFirst() noexcept;
  void PopLast() noexcept;

  const T& GetFirst() const noexcept;
  T& GetFirst() noexcept;
  const T& GetLast() const noexcept;
  T& GetLast() noexcept;

  const T& operator[](std::size_t idx) const noexcept;
  T& operator[](std::size_t idx) noexcept;

private:
  std::size_t capacity_ = 0;
  std::size_t size_ = 0;
  std::size_t start = 0;
  std::size_t end = 0;
  std::unique_ptr<T[]> buffer;
};

#endif //FACE_POSE_ESTIMATION_CIRCULAR_BUFFERED_DEQUE_H
