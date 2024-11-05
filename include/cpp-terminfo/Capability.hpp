/*
 * cpp-terminfo
 * C++ standalone library for terminal terminfo capabilities.
 *
 * SPDX-FileCopyrightText: 2023-2024 cpp-terminfo
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once
#include "cpp-terminfo/BooleanId.hpp"
#include "cpp-terminfo/IntegerId.hpp"
#include "cpp-terminfo/StringId.hpp"

#include <string>

namespace Terminfo
{

template<typename type_id> class Capability
{
public:
  Capability() = default;
  inline explicit Capability(const type_id& id, const std::string& name, const std::string& description) : m_id(id), m_name(name), m_description(description)
  {
    m_name.shrink_to_fit();
    m_description.shrink_to_fit();
  };
  inline std::string description() const noexcept { return m_description; }
  inline std::string name() const noexcept { return m_name; }
  inline type_id     id() const noexcept { return m_id; }
  inline bool        operator==(const std::string& str) const noexcept { return m_name == str; }

private:
  std::string m_name;
  std::string m_description;
  type_id     m_id;
};

using BooleanCapability = Capability<BooleanId>;
using IntegerCapability = Capability<IntegerId>;
using StringCapability  = Capability<StringId>;

}  // namespace Terminfo