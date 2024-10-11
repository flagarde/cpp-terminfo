#include "cpp-terminfo/Terminfo.hpp"

void Terminfo::Terminfo::add(const Terminfo& rhs)
{
    this->m_booleans.insert(rhs.m_booleans.begin(),rhs.m_booleans.end());
    this->m_integers.insert(rhs.m_integers.begin(),rhs.m_integers.end());
    this->m_strings.insert(rhs.m_strings.begin(),rhs.m_strings.end());
}