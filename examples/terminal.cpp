/*
 * cpp-terminfo
 * C++ library for terminal terminfo capacities.
 *
 * SPDX-FileCopyrightText: 2019-2024 cpp-terminal
 *
 * SPDX-License-Identifier: MIT
 */

#include "cpp-terminfo/Data.hpp"
#include "cpp-terminfo/Print.hpp"
#include <iostream>

int main(int argc, char *argv[]) {
  std::string name{};
  do {
    std::cout << "Insert a terminal name " << std::endl;
    const Terminfo::Terminfo *terminfo = Terminfo::get(name);
    if (terminfo)
      std::cout << terminfo << std::endl;
  } while (std::cin >> name);
}