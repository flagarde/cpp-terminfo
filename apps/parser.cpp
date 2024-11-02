/*
 * cpp-terminfo
 * C++ standalone library for terminal terminfo capabilities.
 *
 * SPDX-FileCopyrightText: 2023-2024 cpp-terminfo
 *
 * SPDX-License-Identifier: MIT
 */

#include "cpp-terminfo/Parser.hpp"

#include "cpp-terminfo/Print.hpp"
#include "cpp-terminfo/Terminfo.hpp"

#include <fstream>
#include <iostream>
#include <string>

class Writer
{
public:
  Writer() = default;
  Writer(const std::string& filename) : m_filename(filename) {}
  void setTerminfos(const std::vector<Terminfo::Terminfo>& info) { m_infos = info; }
  void write() { writeCPP(); };

private:
  void                            writeCPP();
  std::string                     m_cpp_path{"./"};
  std::string                     m_header_path{"./include/cpp-terminfo/"};
  std::string                     m_filename;
  std::vector<Terminfo::Terminfo> m_infos;
};

void Writer::writeCPP()
{
  std::vector<std::string>           ignore{""};
  std::map<std::string, std::string> replace{{"Eterm", "mEterm"}, {"9term", "nineterm"}};
  for(int i = 0; i != m_infos.size(); ++i)
  {
    if(m_infos[i].getType().name().find('+') != std::string::npos || std::find(ignore.begin(), ignore.end(), m_infos[i].getType().name()) != ignore.end()) continue;
    std::string name = m_infos[i].getType().name();
    if(replace.find(name) != replace.end()) { name = replace.find(name)->second; }
    std::ofstream outfile(m_cpp_path + "terminals/" + name + ".cpp");
    std::ofstream header(m_cpp_path + "include/cpp-terminfo/" + name + ".hpp");
    outfile << "// terminal : " << m_infos[i].getType().name() << "\n";
    outfile << "#include \"cpp-terminfo/Terminfo.hpp\"\n";
    outfile << "#include \"cpp-terminfo/" << name << ".hpp\"\n";

    std::string description = m_infos[i].getType().description();
    std::string aliases     = "\"" + m_infos[i].getType().name() + "\"";
    for(std::size_t j = 0; j != m_infos[i].getType().aliases().size(); ++j) { aliases += ",\"" + m_infos[i].getType().aliases()[j] + "\""; }
    std::string                                 booleans = "{";
    const Terminfo::Terminfo::BooleansContainer bools    = m_infos[i].getBooleans();
    for(Terminfo::Terminfo::BooleansContainer::const_iterator it = bools.cbegin(); it != bools.cend(); ++it)
    {
      booleans += "Terminfo::BooleanId(";
      booleans += std::to_string(static_cast<std::uint8_t>(*it));
      booleans += "),";
    }
    if(booleans.size() > 1) booleans.pop_back();
    booleans += "}";
    std::string                                 inte     = "{";
    const Terminfo::Terminfo::IntegersContainer integers = m_infos[i].getIntegers();
    for(Terminfo::Terminfo::IntegersContainer::const_iterator it = integers.cbegin(); it != integers.cend(); ++it)
    {
      inte += "{Terminfo::IntegerId(";
      inte += std::to_string(static_cast<std::uint8_t>(it->first));
      inte += "),";
      inte += std::to_string(it->second);
      inte += "},";
    }
    if(inte.size() > 1) inte.pop_back();
    inte += "}";
    const Terminfo::Terminfo::StringsContainer strings = m_infos[i].getStrings();
    std::string                                str     = "{";
    for(Terminfo::Terminfo::StringsContainer::const_iterator it = strings.cbegin(); it != strings.cend(); ++it)
    {
      str += "{Terminfo::StringId(";
      str += std::to_string(static_cast<std::uint16_t>(it->first));
      str += "),R\"(";
      str += it->second;
      str += ")\"},";
    }
    if(str.size() > 1) str.pop_back();
    str += "}";
    outfile << "Terminfo::Terminfo t" << std::to_string(i + 1) << "(\n"
            << "{{" << aliases << "},R\"(" << description << ")\"},\n"
            << booleans << ",\n"
            << inte << ",\n"
            << str << "\n);";

    header << "#pragma once\nextern Terminfo::Terminfo t" << std::to_string(i + 1) << ";";
    outfile.close();
    header.close();
  }

  std::ofstream outfile(m_cpp_path + m_filename + ".cpp");
  outfile << "#include \"cpp-terminfo/Get.hpp\"\n";
  outfile << "#include <stdexcept>\n";
  std::string term_list;
  for(int i = 0; i != m_infos.size(); ++i)
  {
    if(m_infos[i].getType().name().find('+') != std::string::npos || std::find(ignore.begin(), ignore.end(), m_infos[i].getType().name()) != ignore.end()) continue;
    std::string name = m_infos[i].getType().name();
    if(replace.find(name) != replace.end()) name = replace.find(name)->second;
    outfile << "#include \"cpp-terminfo/" << name << ".hpp\"\n";
    term_list += "t";
    term_list += std::to_string(i + 1);
    term_list += ",";
  }
  if(term_list.size() > 1) term_list.pop_back();
  outfile << "const Terminfo::Terminfo& Terminfo::Get::terminfo(const std::string& term)\n{";
  outfile << "static std::vector<std::reference_wrapper<Terminfo>> m_terminfos{" << term_list << "};\n";
  outfile << "for(std::size_t i = 0; i != m_terminfos.size(); ++i)\n{\nif(m_terminfos[i].get().getType().isAlias(term)) return m_terminfos[i].get();\n}\nthrow std::out_of_range(term+\" not known\");\n}\n";
  outfile.close();
}

int main(int argc, char* argv[])
{
  if(argc != 3)
  {
    std::cout << "parser need the terminfo.src file and filename" << std::endl;
    std::exit(1);
  }
  std::string      file{argv[1]};
  Terminfo::Parser parser{file};
  parser.parse();

  if(parser.hasUnknown())
  {
    for(std::map<std::string, Terminfo::Parser::Type>::const_iterator it = parser.getUnknown().cbegin(); it != parser.getUnknown().cend(); ++it)
    {
      switch(it->second)
      {
        case Terminfo::Parser::Type::Boolean:
        {
          std::cout << "boolean capability " << it->first << " unknown !" << std::endl;
          break;
        }
        case Terminfo::Parser::Type::Integer:
        {
          std::cout << "integer capability " << it->first << " unknown !" << std::endl;
          break;
        }
        case Terminfo::Parser::Type::String:
        {
          std::cout << "string capability " << it->first << " unknown !" << std::endl;
          break;
        }
        default: break;
      }
    }
  }
  std::string filename{argv[2]};
  Writer      writer(filename);
  writer.setTerminfos(parser.getTerminfos());
  writer.write();
}