// SPDX-License-Identifier: GPL-2.0
// Copyright (C) 2023 JiauZhang <https://github.com/JiauZhang/menuconfig>

extern "C" {
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
}

#include <filesystem>
#include "argparse.hpp"

namespace fs = std::filesystem;

int main(int argc, char **argv)
{
    argparse::ArgumentParser parser("menuconfig options");

    parser.add_argument("-s")
        .help("change output verbosity")
        .default_value(false)
        .implicit_value(true);
    parser.add_argument("--kconfig")
        .help("specify the Kconfig file");

    try {
        parser.parse_args(argc, argv);
    } catch (const std::runtime_error& err) {
        std::cout << "runtime error:\n";
        std::cerr << err.what() << std::endl;
        std::cerr << parser;
        std::exit(1);
    }

    signal(SIGINT, sig_handler_api);

    if (parser["-s"] == true) {
        *silent_api = 1;
        /* Silence conf_read() until the real callback is set up */
        conf_set_message_callback(NULL);
    }

    std::string kconfig("./Kconfig");

    if (parser.is_used("--kconfig"))
        kconfig = parser.get<std::string>("--kconfig");

    fs::file_status file_status(fs::status(kconfig));

    if (file_status.type() != fs::file_type::regular) {
        std::cerr << "Runtime Error:\n";
        std::cerr << "\tKconfig file: " << kconfig
            << " is not a regular file!" << std::endl;
        std::exit(1);
    }

    fs::path fs_path(kconfig);
    auto dirname = fs_path.parent_path();
    auto filename = fs_path.filename();

    fs::current_path(dirname);
    kconfig = filename;
    conf_parse(kconfig.c_str());
    conf_read(NULL);

    int res;
    char *mode = getenv("MENUCONFIG_MODE");

    if (mode) {
        if (!strcasecmp(mode, "single_menu"))
            *single_menu_mode_api = 1;
    }

    if (init_dialog(NULL)) {
        fprintf(stderr, "Your display is too small to run Menuconfig!\n");
        fprintf(stderr, "It must be at least 19 lines by 80 columns.\n");
        return 1;
    }

    set_config_filename_api(conf_get_configname());
    conf_set_message_callback(conf_message_callback_api);
    do {
        conf_api(&rootmenu, NULL);
        res = handle_exit_api();
    } while (res == KEY_ESC);

    return res;
}