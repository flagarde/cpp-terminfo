/*
 * cpp-terminfo
 * C++ standalone library for terminal terminfo capabilities.
 *
 * SPDX-FileCopyrightText: 2023-2024 cpp-terminfo
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once
#include "cpp-terminfo/Boolean.hpp"
#include "cpp-terminfo/Integer.hpp"
#include "cpp-terminfo/String.hpp"

#include <cstdint>
#include <string>

namespace Terminfo
{
class Capability
{
public:
  enum class Type : std::uint8_t
  {
    boolean,
    integer,
    string,
    not_yet  // ##FIXME
  };
  Capability() = default;
  inline explicit Capability(const Boolean& val, const std::string& name, const std::string& desc) : m_name(name), m_description(desc), m_type(Type::boolean), m_value(static_cast<std::uint8_t>(val)) {};
  inline explicit Capability(const Integer& val, const std::string& name, const std::string& desc) : m_name(name), m_description(desc), m_type(Type::integer), m_value(static_cast<std::uint8_t>(val)) {};
  inline explicit Capability(const String& val, const std::string& name, const std::string& desc) : m_name(name), m_description(desc), m_type(Type::string), m_value(static_cast<std::uint16_t>(val)) {};
  inline std::string  description() const noexcept { return m_description; }
  inline std::string  name() const noexcept { return m_name; }
  inline std::uint8_t value() const noexcept { return m_value; }
  inline Type         type() const noexcept { return m_type; }
  inline bool         operator==(const std::string& str) const noexcept
  {
    if(m_name == str) return true;
    else
      return false;
  }

private:
  std::string   m_name;
  std::string   m_description;
  Type          m_type;
  std::uint16_t m_value;
};
}  // namespace Terminfo