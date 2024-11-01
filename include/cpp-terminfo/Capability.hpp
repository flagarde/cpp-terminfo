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

#include <string>

namespace Terminfo
{

template<typename type_id> class Capability
{
public:
  Capability() = default;
  inline explicit Capability(const type_id& id, const std::string& name, const std::string& description) : m_id(id), m_name(name), m_description(description) {};
  inline std::string description() const noexcept { return m_description; }
  inline std::string name() const noexcept { return m_name; }
  inline type_id     id() const noexcept { return m_id; }
  inline bool        operator==(const std::string& str) const noexcept { return m_name == str; }

private:
  std::string m_name;
  std::string m_description;
  type_id     m_id;
};

using BooleanCapability = Capability<Boolean>;
using IntegerCapability = Capability<Integer>;
using StringCapability  = Capability<String>;

}  // namespace Terminfo