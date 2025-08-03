#include <common/basic_definitions.h>
#include <curl/curl.h>

#include "curl_util.h"
#include "logger.h"
#include "string_util.h"

extern logical debug;

static size_t write_callback(const void *contents, const size_t size, const size_t nmemb, void *userp)
{
    const size_t total_size = size * nmemb;
    strncat_s(userp, sizeof(userp), contents, total_size);
    return total_size;
}

int CURL_UTIL_post(const char *url, const char *body, char **response)
{
    int rcode = ITK_ok;

    CURL *curl = NULL;

    struct curl_slist *headers = NULL;

    char *msg = NULL;

    size_t msg_len = 0;

    curl = curl_easy_init();
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
        curl_easy_setopt(curl, CURLOPT_URL, url);
        LOGGER_INFO("request url: %s", url);
        LOGGER_INFO("request body:\n%s", body);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body);
        headers = curl_slist_append(headers, "Content-Type: application/json");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        char buf[2048] = {0};
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, buf);

        const CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK)
        {
            STRING_UTIL_append(&msg, &msg_len, "curl_easy_perform() failed: ");
            STRING_UTIL_append(&msg, &msg_len, curl_easy_strerror(res));
            LOGGER_ERROR_GOTO(msg, ERRORCODE_MESSAGE);
        }
        LOGGER_CST_GOTO(STRING_UTIL_duplicate(buf, response));
        LOGGER_INFO("response:\n%s", *response);

        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    }

CLEANUP:
    return rcode;
}
