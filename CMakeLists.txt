
cmake_minimum_required ( VERSION 2.8 )

# common staticlibs setup
if ( NOT DEFINED STATICLIB_PARENT_DIR )
    set ( STATICLIB_TOOLCHAIN amd64_linux_clang CACHE STRING "toolchain triplet" )
    set ( STATICLIB_PARENT_DIR ${CMAKE_CURRENT_LIST_DIR}/../ CACHE INTERNAL "parent dir" )
    include ( ${STATICLIB_PARENT_DIR}/staticlib_util_cmake/CMakeLists_common.cmake )
    staticlib_set_toolchain ( ${STATICLIB_PARENT_DIR} ${STATICLIB_TOOLCHAIN} )
endif ( )

# project header
project ( staticlib_util_stdlib CXX )
set ( ${PROJECT_NAME}_VERSION_MAJOR 0 )
set ( ${PROJECT_NAME}_VERSION_MINOR 1 )
set ( ${PROJECT_NAME}_VERSION_MICRO 0 )

# header-only boost is the only dependency
staticlib_add_dependency ( staticlib_ext_boost )

# build steps
include_directories ( ${CMAKE_CURRENT_LIST_DIR}/include )
file ( GLOB_RECURSE ${PROJECT_NAME}_SRC ${CMAKE_CURRENT_LIST_DIR}/src/*.cpp )
add_library ( ${PROJECT_NAME} STATIC ${${PROJECT_NAME}_SRC} )

# tests
set ( ${PROJECT_NAME}_TEST_LIBS ${PROJECT_NAME} )
staticlib_enable_testing ( ${PROJECT_NAME}_TEST_LIBS )
staticlib_enable_docs ( )

# headers export
set ( ${PROJECT_NAME}_INCLUDES 
        ${CMAKE_CURRENT_LIST_DIR}/include 
        ${staticlib_ext_boost_INCLUDES} )
list( REMOVE_DUPLICATES ${PROJECT_NAME}_INCLUDES )
set ( ${PROJECT_NAME}_INCLUDES "${${PROJECT_NAME}_INCLUDES}" CACHE INTERNAL ${PROJECT_NAME}_INCLUDES )
