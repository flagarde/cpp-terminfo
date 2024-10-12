/*
 * cpp-terminfo
 * C++ standalone library for terminal terminfo capabilities.
 *
 * SPDX-FileCopyrightText: 2023-2024 cpp-terminfo
 *
 * SPDX-License-Identifier: MIT
 */

#include "cpp-terminfo/Terminfos.hpp"

namespace Terminfo
{
extern std::vector<std::reference_wrapper<Terminfo>> m_inf;
inline const Terminfo*                               get(const std::string& term)
{
  static Terminfos m_terminfos(m_inf);
  return m_terminfos.getTerminfo(term);
}
}  // namespace Terminfo
