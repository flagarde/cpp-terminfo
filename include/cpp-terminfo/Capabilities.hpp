/*
 * cpp-terminfo
 * C++ standalone library for terminal terminfo capabilities.
 *
 * SPDX-FileCopyrightText: 2023-2024 cpp-terminfo
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once
#include "cpp-terminfo/Capability.hpp"

#include <algorithm>
#include <array>
#include <iostream>
#include <string>
#include <vector>

namespace Terminfo
{
class Capabilities
{
private:
  static const constexpr std::size_t                           m_booleans_size{37};
  static const std::array<BooleanCapability, m_booleans_size>  m_booleans;
  static const constexpr std::size_t                           m_intergers_size{33};
  static const std::array<IntegerCapability, m_intergers_size> m_integers;
  static const constexpr std::size_t                           m_strings_size{405};
  static const std::array<StringCapability, m_strings_size>    m_strings;

public:
  using boolean_const_iterator = std::array<BooleanCapability, m_booleans_size>::const_iterator;
  using integer_const_iterator = std::array<IntegerCapability, m_intergers_size>::const_iterator;
  using string_const_iterator  = std::array<StringCapability, m_strings_size>::const_iterator;
  bool              isBoolean(const std::string& name) const noexcept { return std::find(m_booleans.begin(), m_booleans.end(), name) != m_booleans.end(); }
  bool              isInteger(const std::string& name) const noexcept { return std::find(m_integers.begin(), m_integers.end(), name) != m_integers.end(); }
  bool              isString(const std::string& name) const noexcept { return std::find(m_strings.begin(), m_strings.end(), name) != m_strings.end(); }
  Boolean           getBoolean(const std::string& str);
  Integer           getInteger(const std::string& str);
  String            getString(const std::string& str);
  BooleanCapability get(const Boolean& boolean) const { return m_booleans[static_cast<std::size_t>(boolean)]; }
  IntegerCapability get(const Integer& integer) const { return m_integers[static_cast<std::size_t>(integer)]; }
  StringCapability  get(const String& string) const { return m_strings[static_cast<std::size_t>(string)]; }
  inline bool       know(const std::string& name) const noexcept { return isBoolean(name) || isInteger(name) || isString(name); }
};

}  // namespace Terminfo