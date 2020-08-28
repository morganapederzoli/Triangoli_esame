# SPDX-FileCopyrightText: 2019-2020 INFN
# SPDX-License-Identifier: EUPL-1.2

cmake_minimum_required(VERSION 3.10)

project(triangoli)

set(CMAKE_CXX_STANDARD          17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS        OFF)

add_executable(triangoli triangoli.cpp)
target_compile_options(triangoli PRIVATE -Wall -Wextra -fsanitize=address)
target_include_directories(triangoli PRIVATE ${SFML_INCLUDE_DIR})
target_link_options(triangoli PRIVATE -fsanitize=address)
target_link_libraries(triangoli PRIVATE ${SFML_LIBRARIES})
