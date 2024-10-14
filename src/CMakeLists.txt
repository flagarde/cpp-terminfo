add_library(terminfo STATIC Capabilities.cpp Terminfo.cpp Parser.cpp Print.cpp)
target_include_directories(terminfo PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>)

file(MAKE_DIRECTORY "${PROJECT_BINARY_DIR}/generated/include/cpp-terminfo")
file(MAKE_DIRECTORY "${PROJECT_BINARY_DIR}/generated/terminals")

file(STRINGS "${CMAKE_BINARY_DIR}/terminfo.src" LINES REGEX "^[a-zA-Z]")
string(REPLACE "[" "" LINES "${LINES}")
foreach(TERMINAL IN LISTS LINES)
  string(FIND "${TERMINAL}" "|" FOUND)
  string(SUBSTRING "${TERMINAL}" 0 ${FOUND} TERMINAL)
  string(FIND "${TERMINAL}" "+" FOUND)
  if(FOUND STREQUAL "-1")
    list(APPEND TERMINAL_FILES "${PROJECT_BINARY_DIR}/generated/terminals/${TERMINAL}.cpp")
  endif()
endforeach()
list(REMOVE_ITEM TERMINAL_FILES "${PROJECT_BINARY_DIR}/generated/terminals/9term.cpp")
# Because eterm and Eterm exist so in system with uncase filesystem there is a mess
list(REMOVE_ITEM TERMINAL_FILES "${PROJECT_BINARY_DIR}/generated/terminals/Eterm.cpp")
list(APPEND TERMINAL_FILES "${PROJECT_BINARY_DIR}/generated/terminals/mEterm.cpp")
list(SORT TERMINAL_FILES CASE INSENSITIVE)

add_custom_command(OUTPUT ${TERMINAL_FILES} "${PROJECT_BINARY_DIR}/generated/Data.cpp"  COMMAND parser "${CMAKE_BINARY_DIR}/terminfo.src" Data
                   WORKING_DIRECTORY "${PROJECT_BINARY_DIR}/generated"
                   COMMENT "Parsing and generating Data.cpp Data.hpp")
#add_custom_target(data DEPENDS ${TERMINAL_FILES} "${PROJECT_BINARY_DIR}/generated/Data.cpp")
add_library(terminfo-data SHARED "${PROJECT_BINARY_DIR}/generated/Data.cpp" "${TERMINAL_FILES}")
target_include_directories(terminfo-data PUBLIC $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/generated/include> $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>)
target_compile_definitions(terminfo-data INTERFACE CPP_TERMINFO_DECLSPEC)

add_library(cpp-terminfo INTERFACE)
target_link_libraries(cpp-terminfo INTERFACE terminfo terminfo-data)
add_library(cpp-terminfo::cpp-terminfo ALIAS cpp-terminfo)
