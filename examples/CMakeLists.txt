add_executable(terminal.example terminal.cpp)
target_link_libraries(terminal.example PRIVATE cpp-terminfo::cpp-terminfo)
