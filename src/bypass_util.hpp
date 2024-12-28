#ifndef BYPASS_UTIL_HPP
#define BYPASS_UTIL_HPP

#include <unidefs.h>

extern "C"
{
    int POM_AM__ask_application_bypass(logical* has_bypass);

    int POM_AM__set_application_bypass(logical bypass);

    int AM__set_application_bypass(logical bypass);

    int RIL_applic_protection(logical bypass);
}

#endif // !BYPASS_UTIL_HPP
