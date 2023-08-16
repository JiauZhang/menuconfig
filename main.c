// SPDX-License-Identifier: GPL-2.0
// Copyright (C) 2023 JiauZhang <https://github.com/JiauZhang/menuconfig>

#include <signal.h>
#include <string.h>
#include "lkc.h"
#include "lxdialog/dialog.h"

extern void sig_handler_api(int signo);
extern void set_config_filename_api(const char *config_filename);
extern void conf_message_callback_api(const char *s);
extern void conf_api(struct menu *menu, struct menu *active_menu);
extern int handle_exit_api(void);

extern int *silent_api;
extern int *single_menu_mode_api;

int main(int ac, char **av)
{
    char *mode;
    int res;

    signal(SIGINT, sig_handler_api);

    if (ac > 1 && strcmp(av[1], "-s") == 0)
    {
        *silent_api = 1;
        /* Silence conf_read() until the real callback is set up */
        conf_set_message_callback(NULL);
        av++;
    }
    conf_parse(av[1]);
    conf_read(NULL);

    mode = getenv("MENUCONFIG_MODE");
    if (mode)
    {
        if (!strcasecmp(mode, "single_menu"))
            *single_menu_mode_api = 1;
    }

    if (init_dialog(NULL))
    {
        fprintf(stderr, "Your display is too small to run Menuconfig!\n");
        fprintf(stderr, "It must be at least 19 lines by 80 columns.\n");
        return 1;
    }

    set_config_filename_api(conf_get_configname());
    conf_set_message_callback(conf_message_callback_api);
    do
    {
        conf_api(&rootmenu, NULL);
        res = handle_exit_api();
    } while (res == KEY_ESC);

    return res;
}