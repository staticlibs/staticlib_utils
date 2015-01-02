
cmake_minimum_required ( VERSION 2.8 )

# common staticlibs setup
set ( STATICLIB_TOOLCHAIN x86_64_linux_clang CACHE STRING "toolchain triplet" )
set ( STATICLIB_PARENT_DIR ${CMAKE_CURRENT_LIST_DIR}/../ )
include ( ${STATICLIB_PARENT_DIR}/staticlib_util_cmake/CMakeLists_common.cmake )
staticlib_set_toolchain ( ${STATICLIB_PARENT_DIR} ${STATICLIB_TOOLCHAIN} )

# project header
project ( staticlib_util_stdlib CXX )
set ( ${PROJECT_NAME}_VERSION_MAJOR 0 )
set ( ${PROJECT_NAME}_VERSION_MINOR 1 )
set ( ${PROJECT_NAME}_VERSION_MICRO 0 )

# build steps
staticlib_collect_all_sources ( )
#add_library ( ${PROJECT_NAME} STATIC ${${PROJECT_NAME}_SRC} )
set ( ${PROJECT_NAME}_TEST_LIBS "" )
staticlib_enable_testing ( ${PROJECT_NAME}_TEST_LIBS )

# headers export
staticlib_set_in_parent_scope ( ${PROJECT_NAME}_INCLUDES ${CMAKE_CURRENT_LIST_DIR}/include )
