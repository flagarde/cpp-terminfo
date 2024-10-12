/*
 * cpp-terminfo
 * C++ standalone library for terminal terminfo capabilities.
 *
 * SPDX-FileCopyrightText: 2023-2024 cpp-terminfo
 *
 * SPDX-License-Identifier: MIT
 */

#include "cpp-terminfo/Data.hpp"
#include "cpp-terminfo/Print.hpp"

#include <iostream>

int main(int argc, char* argv[])
{
  std::string name{};
  do {
    std::cout << "Insert a terminal name " << std::endl;
    const Terminfo::Terminfo* terminfo = Terminfo::get(name);
    if(terminfo) std::cout << terminfo << std::endl;
  } while(std::cin >> name);
}