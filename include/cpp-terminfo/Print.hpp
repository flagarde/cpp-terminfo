/*
 * cpp-terminfo
 * C++ standalone library for terminal terminfo capabilities.
 *
 * SPDX-FileCopyrightText: 2023-2024 cpp-terminfo
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once
#include <iosfwd>

namespace Terminfo
{

class Terminfo;

std::ostream& operator<<(std::ostream& os, const Terminfo* iss);

}  // namespace Terminfo