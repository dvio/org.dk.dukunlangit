#include "OnlineUpdate.h"
#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "httplib.h"
#include <iostream>

#define PATCH_URL "https://yourserver.com/latest_patch"

bool OnlineUpdate::FetchLatestPatch(std::string& encryptedData) {
    httplib::Client cli("https://yourserver.com");
    auto res = cli.Get("/latest_patch");

    if (res && res->status == 200) {
        encryptedData = res->body;
        return true;
    }
    std::cerr << "Failed to fetch patch: " << (res ? res->status : -1) << std::endl;
    return false;
}
