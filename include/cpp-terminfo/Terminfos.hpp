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
  Terminfos(const std::vector<std::reference_wrapper<Terminfo>>& term) : m_terminfos(term) {};
  const Terminfo* getTerminfo(const std::string& term) const
  {
    for(std::size_t i = 0; i != m_terminfos.size(); ++i)
    {
      if(m_terminfos[i].get().getType().isAlias(term)) { return &m_terminfos[i].get(); }
    }
    return nullptr;
  }

private:
  std::vector<std::reference_wrapper<Terminfo>> m_terminfos;
};
}  // namespace Terminfo
