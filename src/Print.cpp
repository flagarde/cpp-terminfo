/*
 * cpp-terminfo
 * C++ standalone library for terminal terminfo capabilities.
 *
 * SPDX-FileCopyrightText: 2023-2024 cpp-terminfo
 *
 * SPDX-License-Identifier: MIT
 */

#include "cpp-terminfo/Print.hpp"

#include "cpp-terminfo/Capabilities.hpp"
#include "cpp-terminfo/Terminfo.hpp"

std::ostream& Terminfo::operator<<(std::ostream& os, const Terminfo* term)
{
  static const Capabilities cap{};
  os << term->getType().name() << ": " << term->getType().description() << '\n';
  if(term->getType().hasAlias())
  {
    os << "  aliases : ";
    for(std::size_t i = 0; i != term->getType().aliases().size(); ++i) os << term->getType().aliases()[i] << " ";
    os << '\n';
  }
  const std::set<Boolean> bools = term->getBooleans();
  os << "  booleans : \n";
  for(std::set<Boolean>::const_iterator it = bools.cbegin(); it != bools.cend(); ++it) { os << "    " << cap.get(*it).name() << '\n'; }
  const std::map<Integer, std::uint16_t> integers = term->getIntegers();
  os << "  integers : \n";
  for(std::map<Integer, std::uint16_t>::const_iterator it = integers.cbegin(); it != integers.cend(); ++it) { os << "    " << cap.get(it->first).name() << " : " << it->second << '\n'; }
  const std::map<String, std::string> strings = term->getStrings();
  os << "  strings : \n";
  for(std::map<String, std::string>::const_iterator it = strings.cbegin(); it != strings.cend(); ++it) { os << "    " << cap.get(it->first).name() << " : " << it->second << '\n'; }
  return os;
}