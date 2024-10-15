add_library(terminfo STATIC Capabilities.cpp Terminfo.cpp Parser.cpp Print.cpp)
target_include_directories(terminfo PUBLIC "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>" "$<INSTALL_INTERFACE:cpp-terminal>")

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

add_custom_command(OUTPUT ${TERMINAL_FILES} "${PROJECT_BINARY_DIR}/generated/Get.cpp"  COMMAND parser "${CMAKE_BINARY_DIR}/terminfo.src" Get
                   WORKING_DIRECTORY "${PROJECT_BINARY_DIR}/generated"
                   COMMENT "Generate Get.cpp")
#add_custom_target(data DEPENDS ${TERMINAL_FILES} "${PROJECT_BINARY_DIR}/generated/Data.cpp")
add_library(terminfo-data SHARED "${PROJECT_BINARY_DIR}/generated/Get.cpp" "${TERMINAL_FILES}")
target_compile_definitions(terminfo PRIVATE BUILDING_DLL)
target_include_directories(terminfo-data PUBLIC $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/generated/include> $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>)
target_link_libraries(terminfo-data PRIVATE terminfo)

add_library(cpp-terminfo INTERFACE)
target_link_libraries(cpp-terminfo INTERFACE terminfo terminfo-data)
add_library(cpp-terminfo::cpp-terminfo ALIAS cpp-terminfo)
install(FILES
        "${PROJECT_SOURCE_DIR}/include/cpp-terminfo/Boolean.hpp"
        "${PROJECT_SOURCE_DIR}/include/cpp-terminfo/Capabilities.hpp"
        "${PROJECT_SOURCE_DIR}/include/cpp-terminfo/Capability.hpp"
        "${PROJECT_SOURCE_DIR}/include/cpp-terminfo/Integer.hpp"
        "${PROJECT_SOURCE_DIR}/include/cpp-terminfo/Parser.hpp"
        "${PROJECT_SOURCE_DIR}/include/cpp-terminfo/Print.hpp"
        "${PROJECT_SOURCE_DIR}/include/cpp-terminfo/String.hpp"
        "${PROJECT_SOURCE_DIR}/include/cpp-terminfo/Terminfo.hpp"
        "${PROJECT_SOURCE_DIR}/include/cpp-terminfo/Terminfos.hpp"
        "${PROJECT_SOURCE_DIR}/include/cpp-terminfo/Type.hpp"
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/cpp-terminfo")
install(TARGETS terminfo terminfo-data cpp-terminfo
        EXPORT cpp-terminfoTargets
        LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
        INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")
install(EXPORT cpp-terminfoTargets
        FILE cpp-terminfoTargets.cmake
        NAMESPACE cpp-terminfo::
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/cpp-terminfo")

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)
configure_package_config_file("${PROJECT_SOURCE_DIR}/cmake/cpp-terminfoConfig.cmake.in"
                              "${PROJECT_BINARY_DIR}/cmake/cpp-terminfoConfig.cmake"
                              INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/cpp-terminfo"
                              PATH_VARS)
write_basic_package_version_file("${PROJECT_BINARY_DIR}/cpp-terminfoConfigVersion.cmake" COMPATIBILITY SameMajorVersion )
install(FILES "${PROJECT_BINARY_DIR}/cmake/cpp-terminfoConfig.cmake"
              "${PROJECT_BINARY_DIR}/cpp-terminfoConfigVersion.cmake"
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/cpp-terminfo")
