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

#include <ostream>

std::ostream& Terminfo::operator<<(std::ostream& os, const Terminfo& term)
{
  static const Capabilities cap;
  os << term.getType().name() << ": " << term.getType().description() << '\n';
  if(term.getType().hasAlias())
  {
    os << "  *aliases: ";
    for(std::size_t i = 0; i != term.getType().aliases().size(); ++i) os << term.getType().aliases()[i] << " ";
    os << '\n';
  }
  const Terminfo::Terminfo::BooleansContainer bools = term.getBooleans();
  os << "  *booleans:\n";
  for(Terminfo::Terminfo::BooleansContainer::const_iterator it = bools.cbegin(); it != bools.cend(); ++it)
  {
    os << "    " << cap.get(*it).name() << "\n";
    os << "      (" << cap.get(*it).description() << ")\n";
  }
  const Terminfo::Terminfo::IntegersContainer integers = term.getIntegers();
  os << "  *integers:\n";
  for(Terminfo::Terminfo::IntegersContainer::const_iterator it = integers.cbegin(); it != integers.cend(); ++it)
  {
    os << "    " << cap.get(it->first).name() << ": " << it->second << "\n";
    os << "      (" << cap.get(it->first).description() << ")\n";
  }
  const Terminfo::Terminfo::StringsContainer strings = term.getStrings();
  os << "   *strings:\n";
  for(Terminfo::Terminfo::StringsContainer::const_iterator it = strings.cbegin(); it != strings.cend(); ++it)
  {
    os << "    " << cap.get(it->first).name() << ": " << it->second << "\n";
    os << "      (" << cap.get(it->first).description() << ")\n";
  }
  return os;
}