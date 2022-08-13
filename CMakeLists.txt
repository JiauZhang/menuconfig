# SPDX-License-Identifier: GPL-2.0
# Copyright (C) 2022 JiauZhang <https://github.com/JiauZhang/menuconfig>

cmake_minimum_required(VERSION 3.10)

project(menuconfig)

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

add_executable(
    menuconfig
    confdata.c expr.c mconf.c
    menu.c preprocess.c symbol.c util.c
    lxdialog/checklist.c lxdialog/inputbox.c
    lxdialog/menubox.c lxdialog/textbox.c
    lxdialog/util.c lxdialog/yesno.c
    ${BISON_PARSER_OUTPUTS}
    ${FLEX_LEXER_OUTPUTS}
)
target_link_libraries(
    menuconfig
    ${FLEX_LIBRARIES} ${BISON_LIBRARIES} ${CURSES_LIBRARY}
)
