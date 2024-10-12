/*
 * cpp-terminfo
 * C++ library for terminal terminfo capacities.
 *
 * SPDX-FileCopyrightText: 2019-2024 cpp-terminal
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once
#include <iosfwd>

namespace Terminfo {

class Terminfo;

std::ostream &operator<<(std::ostream &os, const Terminfo *iss);

} // namespace Terminfo