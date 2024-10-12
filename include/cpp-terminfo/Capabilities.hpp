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
public:
  Boolean                 getBoolean(const std::string& str);
  Integer                 getInteger(const std::string& str);
  String                  getString(const std::string& str);
  Capability              get(const Boolean& boolean) const { return m_booleans[static_cast<std::size_t>(boolean)]; }
  Capability              get(const Integer& integer) const { return m_integers[static_cast<std::size_t>(integer)]; }
  Capability              get(const String& string) const { return m_strings[static_cast<std::size_t>(string)]; }
  inline bool             know(const std::string& name) const noexcept { return std::find(m_booleans.begin(), m_booleans.end(), name) != m_booleans.end() || std::find(m_integers.begin(), m_integers.end(), name) != m_integers.end() || std::find(m_strings.begin(), m_strings.end(), name) != m_strings.end(); }
  inline Capability::Type type(const std::string& name)
  {
    if(std::find(m_booleans.begin(), m_booleans.end(), name) != m_booleans.end()) return Capability::Type::boolean;
    else if(std::find(m_integers.begin(), m_integers.end(), name) != m_integers.end())
      return Capability::Type::integer;
    else if(std::find(m_strings.begin(), m_strings.end(), name) != m_strings.end())
      return Capability::Type::string;
    else
      return Capability::Type::not_yet;
  }

private:
  static const constexpr std::size_t                    m_booleans_size{37};
  static const std::array<Capability, m_booleans_size>  m_booleans;
  static const constexpr std::size_t                    m_intergers_size{33};
  static const std::array<Capability, m_intergers_size> m_integers;
  static const constexpr std::size_t                    m_strings_size{405};
  static const std::array<Capability, m_strings_size>   m_strings;
};
}  // namespace Terminfo