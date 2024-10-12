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

#include <fstream>
#include <iostream>
#include <string>

class Writer
{
public:
  Writer() = default;
  Writer(const std::string& filename) : m_filename(filename) {}
  void setTerminfos(const std::vector<Terminfo::Terminfo>& info) { m_infos = info; }
  void write()
  {
    writeCPP();
    writeHeader();
  };

private:
  void                            writeCPP();
  void                            writeHeader();
  std::string                     m_cpp_path{"./"};
  std::string                     m_header_path{"./include/cpp-terminfo/"};
  std::string                     m_filename;
  std::vector<Terminfo::Terminfo> m_infos;
};

void Writer::writeHeader()
{
  // std::ofstream outfile (m_header_path+m_filename+".hpp");
  // outfile<< R"(#include "cpp-terminfo/Terminfos.hpp")";
  // outfile<<"\nnamespace Terminfo {\n";
  // outfile<<"extern std::vector<std::reference_wrapper<Terminfo>> m_inf;\n";
  // outfile<<"inline const Terminfo* get(const std::string& term){\n";
  // outfile<<"static Terminfos m_terminfos(m_inf);\n";
  // outfile<<"  return m_terminfos.getTerminfo(term);\n";
  // outfile<<"}";
  // outfile<<"}\n";
  // outfile.close();
}

void Writer::writeCPP()
{
  std::vector<std::string>           ignore{"9term"};
  std::map<std::string, std::string> replace{{"Eterm", "mEterm"}};
  for(int i = 0; i != m_infos.size(); ++i)
  {
    if(m_infos[i].getType().name().find('+') != std::string::npos || std::find(ignore.begin(), ignore.end(), m_infos[i].getType().name()) != ignore.end()) continue;
    std::string name = m_infos[i].getType().name();
    if(replace.find(name) != replace.end())
    {
      name = replace.find(name)->second;
      std::cout << name << std::endl;
    }
    std::ofstream outfile(m_cpp_path + "terminals/" + name + ".cpp");
    std::ofstream header(m_cpp_path + "include/cpp-terminfo/" + name + ".hpp");
    outfile << "// terminal : " << m_infos[i].getType().name() << "\n";
    outfile << "#include \"cpp-terminfo/Terminfo.hpp\"\n";
    outfile << "#include \"cpp-terminfo/" << name << ".hpp\"\n";

    std::string description = m_infos[i].getType().description();
    std::string aliases     = "\"" + m_infos[i].getType().name() + "\"";
    for(std::size_t j = 0; j != m_infos[i].getType().aliases().size(); ++j) { aliases += ",\"" + m_infos[i].getType().aliases()[j] + "\""; }
    std::string                       booleans = "{";
    const std::set<Terminfo::Boolean> bools    = m_infos[i].getBooleans();
    for(std::set<Terminfo::Boolean>::const_iterator it = bools.cbegin(); it != bools.cend(); ++it)
    {
      booleans += "Terminfo::Boolean(";
      booleans += std::to_string(static_cast<std::uint8_t>(*it));
      booleans += "),";
    }
    if(booleans.size() > 1) booleans.pop_back();
    booleans += "}";
    std::string                                      inte     = "{";
    // outfile<<"const static std::map<Integer,std::uint16_t>
    // i"<<std::to_string(i)<<"{";
    const std::map<Terminfo::Integer, std::uint16_t> integers = m_infos[i].getIntegers();
    for(std::map<Terminfo::Integer, std::uint16_t>::const_iterator it = integers.cbegin(); it != integers.cend(); ++it)
    {
      inte += "{Terminfo::Integer(";
      inte += std::to_string(static_cast<std::uint8_t>(it->first));
      inte += "),";
      inte += std::to_string(it->second);
      inte += "},";
    }
    if(inte.size() > 1) inte.pop_back();
    inte += "}";
    // outfile<<"const static std::map<String,std::string>
    // s"<<std::to_string(i)<<"{";
    const std::map<Terminfo::String, std::string> strings = m_infos[i].getStrings();
    std::string                                   str     = "{";
    for(std::map<Terminfo::String, std::string>::const_iterator it = strings.cbegin(); it != strings.cend(); ++it)
    {
      str += "{Terminfo::String(";
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

    header << "#pragma once\n#include \"cpp-terminfo/Terminfo.hpp\"\nextern "
              "Terminfo::Terminfo t"
           << std::to_string(i + 1) << ";";
    outfile.close();
    header.close();
  }

  std::ofstream outfile(m_cpp_path + m_filename + ".cpp");
  outfile << "#include \"cpp-terminfo/Data.hpp\"\n";
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
  outfile << "std::vector<std::reference_wrapper<Terminfo::Terminfo>> "
             "Terminfo::m_inf{"
          << term_list << "};\n";
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
    for(std::map<std::string, Terminfo::Capability::Type>::const_iterator it = parser.getUnknown().cbegin(); it != parser.getUnknown().cend(); ++it)
    {
      switch(it->second)
      {
        case Terminfo::Capability::Type::boolean:
        {
          std::cout << "boolean capability " << it->first << " unknown !" << std::endl;
          break;
        }
        case Terminfo::Capability::Type::integer:
        {
          std::cout << "integer capability " << it->first << " unknown !" << std::endl;
          break;
        }
        case Terminfo::Capability::Type::string:
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