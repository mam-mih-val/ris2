project(RISOVALKA2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE debug)

cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

find_package(ROOT REQUIRED)
find_package(QnTools REQUIRED)

include_directories( ${CMAKE_SOURCE_DIR} ${ROOT_INCLUDE_DIRS} ${QnTools_INCLUDE_DIR}/QnTools )

set( CALC_INCLUDE_PATH ${CMAKE_SOURCE_DIR}/src )
set( QnTools_LIB_PATH QnTools::Base )
set( QnTools_INCLUDE_PATH ${QnTools_INCLUDE_DIR}/QnTools )
configure_file(src/main.cc.in ${CMAKE_SOURCE_DIR}/src/main.cc @ONLY)

configure_file(docs/Doxyfile.in ${CMAKE_SOURCE_DIR}/docs/Doxyfile @ONLY)

add_executable(draw src/main.cc)
target_link_libraries(draw PRIVATE QnTools::Base ROOT::Tree ROOT::RIO ROOT::MathMore )