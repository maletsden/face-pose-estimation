#pragma once

#if defined(__ANDROID__)
#include <experimental/optional>
template<class T>
using optional = std::experimental::optional<T>;
inline constexpr auto nullopt = std::experimental::nullopt;
#else
#include <optional>
template<class T>
using optional = std::optional<T>;
inline constexpr auto nullopt = std::nullopt;
#endif

// In IOS lib optional::value() doesn't work, so we use optional::operator*() and operator->() to access members.
// In Android lib optional::has_value doesn't work, so we use optional::operator bool() to check whether a member is set.
// For example: if (optional) {}  instead of  if (optional.has_value()) {} .