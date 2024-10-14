/*
 * cpp-terminfo
 * C++ standalone library for terminal terminfo capabilities.
 *
 * SPDX-FileCopyrightText: 2023-2024 cpp-terminfo
 *
 * SPDX-License-Identifier: MIT
 */

#include "cpp-terminfo/Print.hpp"
#include "cpp-terminfo/Terminfos.hpp"

#include <iostream>

int main(int argc, char* argv[])
{
  std::string name{};
  std::cout << "Insert a terminal name " << std::endl;
  while(std::cin >> name)
  {
    const Terminfo::Terminfo* terminfo = Terminfo::get(name);
    if(terminfo) std::cout << terminfo;
    else
      std::cout << name << " not in terminfo database !" << std::endl;
    std::cout << "Insert a terminal name " << std::endl;
  };
}