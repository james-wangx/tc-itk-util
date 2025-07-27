#include <fclasses/tc_string.h>
#include <gtest/gtest.h>
#include <tcinit/tcinit.h>

#include "logger.h"

constexpr int WRONG_USAGE = 100001;

logical debug = false;
char *user = nullptr;

int ITK_user_main(int argc, char **argv)
{
    int rcode = ITK_ok;
    int gtest_rcode = 0;

    // Get args
    const char *usr = ITK_ask_cli_argument("-u=");
    const char *upw = ITK_ask_cli_argument("-p=");
    const char *ugp = ITK_ask_cli_argument("-g=");
    const char *dbg = ITK_ask_cli_argument("-d=");
    const char *help = ITK_ask_cli_argument("-h=");

    if (!usr || !upw || !ugp || help)
    {
        LOGGER_ERROR("USAGE: utility -u=user -p=password -g=group");
        return WRONG_USAGE;
    }

    if (tc_strcmp(dbg, "true") == 0)
    {
        debug = true;
    }

    // Login
    LOGGER_ITK_GOTO(ITK_initialize_text_services(0));
    LOGGER_ITK_GOTO(ITK_init_module(usr, upw, ugp));
    LOGGER_INFO("Login to Teamcenter success as %s", usr);

    user = _strdup(usr);

    // Test
    testing::InitGoogleTest(&argc, argv);
    gtest_rcode = RUN_ALL_TESTS();
    LOGGER_INFO("gtest rcode = %d", gtest_rcode);

CLEANUP:
    MEM_UTIL_FREE_CST(user);
    LOGGER_ITK_PASS(ITK_exit_module(false));
    return rcode;
}
