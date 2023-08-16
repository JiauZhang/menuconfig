// SPDX-License-Identifier: GPL-2.0
// Copyright (C) 2023 JiauZhang <https://github.com/JiauZhang/menuconfig>

#include "mconf.c"

void sig_handler_api(int signo) {
    sig_handler(signo);
}

void set_config_filename_api(const char *config_filename) {
    set_config_filename(config_filename);
}

void conf_message_callback_api(const char *s) {
    conf_message_callback(s);
}

void conf_api(struct menu *menu, struct menu *active_menu) {
    conf(menu, active_menu);
}

int handle_exit_api(void) {
    return handle_exit();
}

int *silent_api = &silent;
int *single_menu_mode_api = &single_menu_mode;
