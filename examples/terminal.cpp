/*
 * cpp-terminfo
 * C++ standalone library for terminal terminfo capabilities.
 *
 * SPDX-FileCopyrightText: 2023-2024 cpp-terminfo
 *
 * SPDX-License-Identifier: MIT
 */

#include "cpp-terminfo/Get.hpp"
#include "cpp-terminfo/Print.hpp"

#include <iostream>

int main(int argc, char* argv[])
{
  std::string name{};
  std::cout << "Insert a terminal name " << std::endl;
  while(std::cin >> name)
  {
    try
    {
      const Terminfo::Terminfo& terminfo = Terminfo::Get::terminfo(name);
      std::cout << terminfo;
      std::cout << "Insert a terminal name " << std::endl;
    }
    catch(const std::out_of_range& e)
    {
      std::cout << "!!! " << e.what() << " !!!" << std::endl;
      std::cout << "Insert a terminal name " << std::endl;
    }
  };
}