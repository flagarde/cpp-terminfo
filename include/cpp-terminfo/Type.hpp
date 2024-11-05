/*
 * cpp-terminfo
 * C++ standalone library for terminal terminfo capabilities.
 *
 * SPDX-FileCopyrightText: 2023-2024 cpp-terminfo
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <algorithm>
#include <string>
#include <vector>

namespace Terminfo
{
class Type
{
public:
  Type() = default;
  Type(const std::vector<std::string>& aliases, const std::string& description) : m_description(description), m_aliases(aliases)
  {
    m_description.shrink_to_fit();
    for(std::vector<std::string>::iterator it = m_aliases.begin(); it != m_aliases.end(); ++it) it->shrink_to_fit();
  }
  std::string              description() const noexcept { return m_description; }
  std::string              name() const noexcept { return m_aliases[0]; }
  bool                     hasAlias() const noexcept { return m_aliases.size() - 1 != 0; }
  std::vector<std::string> aliases()
  {
    std::vector<std::string> ret{m_aliases};
    ret.erase(ret.begin());
    return ret;
  }
  bool isAlias(const std::string& str) const noexcept { return std::find(m_aliases.begin(), m_aliases.end(), str) != m_aliases.end(); }

private:
  std::string              m_description;
  std::vector<std::string> m_aliases;
};
}  // namespace Terminfo