#include <fclasses/tc_string.h>
#include <tcinit/tcinit.h>
#include <gtest/gtest.h>

#include "logger.hpp"

constexpr int WRONG_USAGE = 100001;

logical debug = false;

int ITK_user_main(int argc, char **argv) {
    int rcode = ITK_ok;

    // Get args
    const char *usr = ITK_ask_cli_argument("-u=");
    const char *upw = ITK_ask_cli_argument("-p=");
    const char *ugp = ITK_ask_cli_argument("-g=");
    const char *dbg = ITK_ask_cli_argument("-d=");
    const char *help = ITK_ask_cli_argument("-h=");

    if (!usr || !upw || !ugp || help) {
        LOGGER_INFO("USAGE: utility -u=user -p=password -g=group");
        return WRONG_USAGE;
    }

    if (tc_strcmp(dbg, "true") == 0) {
        debug = true;
    }

    // Login
    LOGGER_ITK_GOTO(ITK_initialize_text_services(0));
    LOGGER_ITK_GOTO(ITK_init_module(usr, upw, ugp));
    LOGGER_INFO("Login to Teamcenter success as %s", usr);

    ::testing::InitGoogleTest(&argc, argv);
    RUN_ALL_TESTS();

CLEANUP:
    LOGGER_ITK_PASS(ITK_exit_module(false));
    return rcode;
}
