#pragma once
#include <utility>

// This file is from a worked example by Kevin Stone

template <typename T, typename Parameter>
class named_type
{
public:
    constexpr explicit named_type(T const &value) noexcept : value_(value) {}
    constexpr explicit named_type(T &&value) noexcept : value_(std::move(value)) {}

    T &get() { return value_; }
    T const &get() const { return value_; }

    // We need operator< so we can use this as a map key, so may as well define all operators!
    auto operator<=>(const named_type &) const = default;

private:
    T value_{};
};