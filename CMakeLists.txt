cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project(cpp-terminfo VERSION "0.0.1" DESCRIPTION "C++ terminfo library" HOMEPAGE_URL "https://github.com/flagarde/cpp-terminfo" LANGUAGES CXX)

if(NOT EXISTS "${CMAKE_CURRENT_BINARY_DIR}/terminfo.src")
  file(DOWNLOAD https://raw.githubusercontent.com/ThomasDickey/ncurses-snapshots/refs/heads/master/misc/terminfo.src "${CMAKE_CURRENT_BINARY_DIR}/terminfo.src" SHOW_PROGRESS)
endif()

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)

add_subdirectory(src)

add_subdirectory(apps)

add_subdirectory(examples)
