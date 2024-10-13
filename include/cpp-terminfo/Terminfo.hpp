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
#include "cpp-terminfo/Type.hpp"

#include <cstdint>
#include <iostream>
#include <map>
#include <set>
namespace Terminfo
{
class Terminfo
{
public:
  Terminfo() {}
  Terminfo(const Type& type) : m_type(type) {}
  Terminfo(const Type& type, const std::set<Boolean>& booleans, const std::map<Integer, std::uint16_t>& integers, const std::map<String, std::string>& strings) : m_type(type), m_booleans(booleans), m_integers(integers), m_strings(strings) {}
  Type                             getType() const { return m_type; }
  void                             addBoolean(const Boolean& boolean) { m_booleans.insert(boolean); }
  void                             addInteger(const Integer& integer, const std::uint16_t& value) { m_integers[integer] = {value}; }
  void                             addString(const String& string, const std::string& value) { m_strings[string] = {value}; }
  void                             add(const Terminfo& rhs);
  void                             remove(const Boolean& boolean) { m_booleans.erase(boolean); }
  void                             remove(const Integer& integer) { m_integers.erase(integer); }
  void                             remove(const String& string) { m_strings.erase(string); }
  bool                             get(const Boolean& boolean) { return m_booleans.find(boolean) != m_booleans.end(); }
  std::uint16_t                    get(const Integer& integer) { return m_integers[integer]; }
  std::string                      get(const String& string) { return m_strings[string]; }
  std::set<Boolean>                getBooleans() const { return m_booleans; }
  std::map<Integer, std::uint16_t> getIntegers() const { return m_integers; }
  std::map<String, std::string>    getStrings() const { return m_strings; }

private:
  std::set<Boolean>                m_booleans;
  std::map<Integer, std::uint16_t> m_integers;
  std::map<String, std::string>    m_strings;
  Type                             m_type;
};
}  // namespace Terminfo
