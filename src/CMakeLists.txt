add_library(terminfo SHARED Capabilities.cpp Terminfo.cpp Parser.cpp Print.cpp)
target_include_directories(terminfo PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>)

file(MAKE_DIRECTORY "${PROJECT_BINARY_DIR}/generated/include/cpp-terminfo")
file(MAKE_DIRECTORY "${PROJECT_BINARY_DIR}/generated/terminals")

file(STRINGS "${CMAKE_BINARY_DIR}/terminfo.src" LINES REGEX "^[a-zA-Z]")
string(REPLACE "[" "" LINES "${LINES}")
foreach(TERM IN LISTS LINES)
  string(FIND "${TERM}" "|" FOUND)
  string(SUBSTRING "${TERM}" 0 ${FOUND} X)
  string(FIND "${TERM}" "+" FOUND)
  if(FOUND STREQUAL "-1")
    list(APPEND TERMINAL_FILES "${PROJECT_BINARY_DIR}/generated/terminals/${TERM}.cpp")
  endif()
endforeach()
list(REMOVE_ITEM TERMINAL_FILES "${PROJECT_BINARY_DIR}/generated/terminals/9term.cpp")

add_custom_command(OUTPUT "${PROJECT_BINARY_DIR}/generated/Data.cpp"
                   BYPRODUCTS ${TERMINAL_FILES} COMMAND parser "${CMAKE_BINARY_DIR}/terminfo.src" Data
                   DEPENDS parser
                   WORKING_DIRECTORY "${PROJECT_BINARY_DIR}/generated"
                   COMMENT "Parsing and generating Data.cpp Data.hpp")
add_library(terminfo-data SHARED "${PROJECT_BINARY_DIR}/generated/Data.cpp" ${TERMINAL_FILES})
target_include_directories(terminfo-data PUBLIC $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/generated/include> $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>)

add_library(cpp-terminfo INTERFACE)
target_link_libraries(cpp-terminfo INTERFACE terminfo terminfo-data)
add_library(cpp-terminfo::cpp-terminfo ALIAS cpp-terminfo)
