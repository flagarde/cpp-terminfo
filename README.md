# cpp-terminfo

C++11 standalone (not database needed), cross-platform terminfo parser and library to access terminal capabilities.

```cpp
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

      std::cout<< "Number of lines: "<<terminfo.get(Terminfo::Integer::columns)<<std::endl;
      std::cout<< "Has automatic margins: "<<terminfo.get(Terminfo::Boolean::auto_right_margin)<<std::endl;
      std::cout<< "Terminal description: "<<terminfo.getType().description()<<std::endl;
    }
    catch(const std::out_of_range& e)
    {
      std::cout << "!!! " << e.what() << " !!!" << std::endl;
      std::cout << "Insert a terminal name " << std::endl;
    }
  };
}
```

```shell
Insert a terminal name 
dumb
dumb: 80-column dumb tty
  *booleans:
    am
      (terminal has automatic margins)
  *integers:
    cols: 80
      (number of columns in a line)
   *strings:
    bel: ^G
      (audible signal (bell) (P))
    cr: \r
      (carriage return (P*) (P*))
    cud1: \n
      (down one line)
    ind: \n
      (scroll text up (P))
Insert a terminal name 
Number of lines: 80
Has automatic margins: 1
Terminal description: 80-column dumb tty
```
