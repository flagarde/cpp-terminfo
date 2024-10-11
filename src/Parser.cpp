#include "cpp-terminfo/Parser.hpp"
#include <fstream>
#include <limits>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "cpp-terminfo/Capabilities.hpp"
#include "cpp-terminfo/Capability.hpp"

static std::vector<std::string> split(const std::string& s, const char& delimiter, const char& annuler='\\') 
{
    if(s.empty()) return {};
    std::vector<std::string> tokens;
    std::size_t pos_begin{0};
    std::size_t pos_last{0};
    std::size_t skip{0};
    while((pos_last = s.find(delimiter,skip)) != std::string::npos)
    {
        if(pos_last-1>=0 && s[pos_last-1]!=annuler)
        { 
            tokens.push_back(s.substr(pos_begin, pos_last-pos_begin));
            pos_begin=pos_last+1;
            skip=pos_last+1;
        }
        else if(pos_last==0) tokens.push_back("");
        else ++skip;
    }
    if(pos_last!=s.size()-1)tokens.push_back(s.substr(pos_begin,s.size()-pos_begin));
    return tokens;
}

void Terminfo::Parser::parse()
{
    std::ifstream fs;
    std::string capabilities_lines;
    capabilities_lines.reserve(592);
    try
    {
        fs.exceptions(std::ifstream::failbit | std::ifstream::badbit );
        fs.open(m_file);
        while(!fs.eof())
        {
            switch(fs.peek())
            {
                case '#':
                case '\n':
                {
                    fs.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    break;
                }
                case '\t':
                {
                    std::string line(5000,'\0');
                    std::getline (fs,line);
                    capabilities_lines+=line;
                    break;
                }
                default:
                {
                    std::string line(5000,'\0');
                    std::getline (fs,line);
                    parseCapabilities(capabilities_lines);
                    parseType(line);
                    break;
                }
            };
        }
        fs.close();
    }
    catch(const std::ifstream::failure& e)
    {
        if(fs.is_open()) fs.close();
        if(!capabilities_lines.empty())parseCapabilities(capabilities_lines);
    }
    
    while(!m_need_reparse.empty())
    {
        resolveUses();
    }
    resolveDeletes();
}

void Terminfo::Parser::parseType(const std::string& line)
{
    std::vector<std::string> tokens=split(line,'|');
    std::string description{tokens[tokens.size()-1]}; // Description
    description=description.substr(0,description.size()-1); // Supress the ,
    tokens.pop_back();
    m_infos.push_back(Terminfo({tokens,description}));
}

void Terminfo::Parser::parseCapabilities(std::string& line)
{
  if(line.empty()) return;
  std::string::iterator end = std::remove(line.begin(), line.end(), '\t');
  line.erase(end,line.end());
  end = std::remove(line.begin(), line.end(), ' ');
  line.erase(end,line.end());
  line=line.substr(0,line.size()-1); // Supress the ,
  const std::vector<std::string> capabilities=split(line,',','\\');
  for(std::size_t i=0; i!=capabilities.size();++i) parseCapability(capabilities[i]);
  line.clear();
}

void Terminfo::Parser::parseCapability(const std::string& line)
{
    if(line[0]=='.') return; // commented capability
    if(line[0]=='O'&& line[1]=='T') return; //obsolete capability
    try
    {
    
    static Capabilities capabilities;
    std::vector<std::string> m_to_remove;
    std::size_t pos = line.find('=');
    if(pos!=std::string::npos) // is a string
    {
        std::string key=line.substr(0,pos);
        std::string value=line.substr(pos+1,line.size());
        if(key=="use")
        {
            m_need_reparse[m_infos[m_infos.size()-1].getType().name()].push_back(value);
            return;
        }
        if(capabilities.know(key))
        {
            String string = capabilities.getString(key);
            m_infos[m_infos.size()-1].addString(string,value);
        }
        else  m_unknown[key]=Capability::Type::string;
        return;
    }
    pos = line.find('#');
    if(pos!=std::string::npos) // is an integer
    {
        std::string key=line.substr(0,pos);
        if(capabilities.know(key))
        {
            std::string value=line.substr(pos+1,line.size());
            Integer integer=capabilities.getInteger(key);
            m_infos[m_infos.size()-1].addInteger(integer,stoi(value));
        }
        else m_unknown[key]=Capability::Type::integer;
        return;
    }
    pos = line.find('@'); // is a removed capability
    if(pos!=std::string::npos)
    {
        m_need_delete[m_infos[m_infos.size()-1].getType().name()].push_back(line.substr(0,line.size()-1));
        return;
    }
    // is a boolean
    if(capabilities.know(line)) m_infos[m_infos.size()-1].addBoolean(capabilities.getBoolean(line));
    else m_unknown[line]=Capability::Type::string;
    }
    catch(const std::out_of_range& exception)
    {
        std::cout<<exception.what()<<std::endl;
    }
    catch(const std::string& str)
    {
        std::cout<<"****"<<str<<"*****"<<std::endl;
    }
}

void Terminfo::Parser::resolveUses()
{
    std::vector<std::map<std::string,std::vector<std::string>>::iterator> to_remove;
    for(std::map<std::string,std::vector<std::string>>::iterator it=m_need_reparse.begin();it!=m_need_reparse.end();++it)
    {
        for(std::vector<std::string>::reverse_iterator itt=it->second.rbegin();itt!=it->second.rend();++itt)
        {
            if(m_need_reparse.find(*itt)==m_need_reparse.end())
            {
                m_infos[getTerminfo(it->first)].add(m_infos[getTerminfo(*itt)]);
                it->second.erase((itt + 1).base());
            }
        }
        if(it->second.empty()) to_remove.push_back(it);
    }
    for(std::size_t i=0;i!=to_remove.size();++i) m_need_reparse.erase(to_remove[i]);
}

void Terminfo::Parser::resolveDeletes()
{
    static Capabilities capabilities;
    for(std::size_t i=0;i!=m_infos.size();++i)
    {
        std::map<std::string,std::vector<std::string>>::const_iterator find= m_need_delete.find(m_infos[i].getType().name());
        if(find!=m_need_delete.end())
        {
            for(std::size_t j=0;j!=find->second.size();++j)
            {
                switch (capabilities.type(find->second[j]))
                {
                    case Capability::Type::boolean:
                    {
                        m_infos[i].remove(capabilities.getBoolean(find->second[j]));
                        break;
                    }
                    case Capability::Type::integer:
                    {
                        m_infos[i].remove(capabilities.getInteger(find->second[j]));
                        break;
                    }
                    case Capability::Type::string:
                    {
                        m_infos[i].remove(capabilities.getString(find->second[j]));
                        break;
                    }
                    default:
                        break;
                        
                }
            }
        }
    }
}