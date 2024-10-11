#pragma once
#include <iosfwd>

namespace Terminfo
{

class Terminfo;

std::ostream& operator<<(std::ostream& os,const Terminfo* iss);

}