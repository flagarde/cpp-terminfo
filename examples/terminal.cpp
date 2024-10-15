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

      std::cout << "Number of lines: " << terminfo.get(Terminfo::Integer::columns) << std::endl;
      std::cout << "Has automatic margins: " << terminfo.get(Terminfo::Boolean::auto_right_margin) << std::endl;
      std::cout << "Terminal description: " << terminfo.getType().description() << std::endl;
    }
    catch(const std::out_of_range& e)
    {
      std::cout << "!!! " << e.what() << " !!!" << std::endl;
      std::cout << "Insert a terminal name " << std::endl;
    }
  };
}