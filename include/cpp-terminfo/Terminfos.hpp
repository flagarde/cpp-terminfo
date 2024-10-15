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

#ifdef _WIN32
  #ifdef BUILDING_DLL
    #define DLL_EXPORT __declspec(dllexport)
  #else
    #define DLL_EXPORT __declspec(dllimport)
  #endif
#else
  #define DLL_EXPORT
#endif

namespace Terminfo
{

class DLL_EXPORT Terminfos
{
public:
  Terminfos() = default;
  static const Terminfo* getTerminfo(const std::string& term);

private:
  static const std::vector<std::reference_wrapper<Terminfo>> m_terminfos;
};

inline const Terminfo* get(const std::string& term)
{
  static Terminfos m_terminfos{};
  return m_terminfos.getTerminfo(term);
}

}  // namespace Terminfo
