/*
 * cpp-terminfo
 * C++ standalone library for terminal terminfo capabilities.
 *
 * SPDX-FileCopyrightText: 2023-2024 cpp-terminfo
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "cpp-terminfo/Terminfo.hpp"

#include <map>
#include <stdexcept>
#include <string>

namespace Terminfo
{

class Parser
{
public:
  enum class Type : std::uint8_t
  {
    Boolean,
    Integer,
    String,
  };
  Parser() { m_infos.reserve(2 << 10); }  // 1833 but use 2^x
  explicit Parser(const std::string& file) : m_file(file) {};
  void                               parse();
  std::vector<Terminfo>              getTerminfos() { return m_infos; }
  bool                               hasUnknown() { return !m_unknown.empty(); }
  const std::map<std::string, Type>& getUnknown() const noexcept { return m_unknown; };

private:
  void        parseType(const std::string& line);
  void        parseCapabilities(std::string& line);
  void        parseCapability(const std::string& line);
  std::size_t getTerminfo(const std::string& str)
  {
    for(std::size_t i = 0; i != m_infos.size(); ++i)
      if(m_infos[i].getType().isAlias(str)) return i;
    throw std::out_of_range(str);
  }
  void                                            resolveUses();
  void                                            resolveDeletes();
  std::string                                     m_file;
  std::map<std::string, std::vector<std::string>> m_need_reparse;
  std::map<std::string, std::vector<std::string>> m_need_delete;
  std::vector<Terminfo>                           m_infos;
  std::map<std::string, Type>                     m_unknown;
};
}  // namespace Terminfo