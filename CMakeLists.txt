# SPDX-License-Identifier: GPL-2.0
# Copyright (C) 2023 JiauZhang <https://github.com/JiauZhang/menuconfig>

cmake_minimum_required(VERSION 3.10)

project(menuconfig)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -s")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INSTALL_LIBDIR /usr/lib)
set(CMAKE_INSTALL_BINDIR /usr/bin)

find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)
find_package(Curses REQUIRED)

BISON_TARGET(
    PARSER parser.y
    ${CMAKE_CURRENT_BINARY_DIR}/parser.tab.c
    DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/parser.tab.h
)
FLEX_TARGET(LEXER lexer.l ${CMAKE_CURRENT_BINARY_DIR}/lexer.c)

include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/lxdialog
)
add_definitions(-DYYDEBUG=1)

add_library(
    conf-objs
    SHARED
    confdata.c expr.c api.c mnconf-common.c
    menu.c preprocess.c symbol.c util.c
    lxdialog/checklist.c lxdialog/inputbox.c
    lxdialog/menubox.c lxdialog/textbox.c
    lxdialog/util.c lxdialog/yesno.c
    ${BISON_PARSER_OUTPUTS}
    ${FLEX_LEXER_OUTPUTS}
)
target_link_libraries(
    conf-objs
    ${FLEX_LIBRARIES} ${BISON_LIBRARIES} ${CURSES_LIBRARY}
)

add_executable(menuconfig main.cpp)
target_link_libraries(menuconfig conf-objs)

add_executable(menuconfig-conf conf.c)
target_link_libraries(menuconfig-conf conf-objs)

install(TARGETS menuconfig menuconfig-conf conf-objs)
