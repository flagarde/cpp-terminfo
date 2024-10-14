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

#include <functional>

namespace Terminfo
{

class Terminfos
{
public:
  Terminfos() = default;
  const Terminfo* getTerminfo(const std::string& term) const
  {
    for(std::size_t i = 0; i != m_terminfos.size(); ++i)
    {
      if(m_terminfos[i].get().getType().isAlias(term)) { return &m_terminfos[i].get(); }
    }
    return nullptr;
  }

private:
  static const std::vector<std::reference_wrapper<Terminfo>> m_terminfos;
};

inline const Terminfo* get(const std::string& term)
{
  static Terminfos m_terminfos{};
  return m_terminfos.getTerminfo(term);
}

}  // namespace Terminfo
