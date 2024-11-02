/*
 * cpp-terminfo
 * C++ standalone library for terminal terminfo capabilities.
 *
 * SPDX-FileCopyrightText: 2023-2024 cpp-terminfo
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once
#include "cpp-terminfo/Bool.hpp"
#include "cpp-terminfo/BooleanId.hpp"
#include "cpp-terminfo/IntegerId.hpp"
#include "cpp-terminfo/StringId.hpp"
#include "cpp-terminfo/Type.hpp"

#include <cstdint>
#include <map>
#include <set>

namespace Terminfo
{

class Terminfo
{
public:
  using BooleansContainer = std::set<BooleanId>;
  using IntegersContainer = std::map<IntegerId, std::uint16_t>;
  using StringsContainer  = std::map<StringId, std::string>;
  Terminfo() {}
  explicit Terminfo(const Type& type) : m_type(type) {}
  Terminfo(const Type& type, const BooleansContainer& booleans, const IntegersContainer& integers, const StringsContainer& strings) : m_booleans(booleans), m_integers(integers), m_strings(strings), m_type(type) {}
  Type                 getType() const { return m_type; }
  void                 add(const BooleanId& id) { m_booleans.insert(id); }
  void                 add(const IntegerId& id, const std::uint16_t& value) { m_integers[id] = {value}; }
  void                 add(const StringId& id, const std::string& value) { m_strings[id] = {value}; }
  void                 add(const Terminfo& rhs);
  void                 remove(const BooleanId& id) { m_booleans.erase(id); }
  void                 remove(const IntegerId& id) { m_integers.erase(id); }
  void                 remove(const StringId& id) { m_strings.erase(id); }
  Bool                 get(const BooleanId& id) const { return m_booleans.find(id) != m_booleans.end(); }
  const std::uint16_t& get(const IntegerId& id) const { return m_integers.at(id); }
  const std::string&   get(const StringId& id) const { return m_strings.at(id); }
  BooleansContainer    getBooleans() const { return m_booleans; }
  IntegersContainer    getIntegers() const { return m_integers; }
  StringsContainer     getStrings() const { return m_strings; }

private:
  BooleansContainer m_booleans;
  IntegersContainer m_integers;
  StringsContainer  m_strings;
  Type              m_type;
};

}  // namespace Terminfo
