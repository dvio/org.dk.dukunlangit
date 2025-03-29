#include "Patches.h"

std::string Patches::GetPatchesJson(int gameType) {
    std::string androidPatchesJson = R"(
    {
        "version": 1,
        "Patches": {
            "God Mode": [
                {
                    "address": "0x12345678",
                    "originalBytes": "89 50 60 70",
                    "patchedBytes": "00 00 00 00",
                    "isValid": false,
                    "scanOnInvalid": false,
                    "addressOffset": 0
                    "scanParams": {
                        "pattern": "12 34 56 78 ?? AB CD EF",
                        "scanOffset": 0,
                        "usePointerCalc": true,
                        "pointerOffset": 4
                    },
                }
            ]
        }
    })";

    std::string betaPatchesJson = R"(
    {
        "version": 1,
        "Patches": {
            "God Mode": [
                {
                    "address": "0x12345678",
                    "originalBytes": "89 50 60 70",
                    "patchedBytes": "00 00 00 00",
                    "isValid": false,
                    "scanOnInvalid": false,
                    "addressOffset": 0
                    "scanParams": {
                        "pattern": "12 34 56 78 ?? AB CD EF",
                        "scanOffset": 0,
                        "usePointerCalc": true,
                        "pointerOffset": 4
                    },
                }
            ]
        }
    })";

    std::string huaweiPatchesJson = R"(
    {
        "version": 1,
        "Patches": {
            "God Mode": [
                {
                    "address": "0x12345678",
                    "originalBytes": "89 50 60 70",
                    "patchedBytes": "00 00 00 00",
                    "isValid": false,
                    "scanOnInvalid": false,
                    "addressOffset": 0
                    "scanParams": {
                        "pattern": "12 34 56 78 ?? AB CD EF",
                        "scanOffset": 0,
                        "usePointerCalc": true,
                        "pointerOffset": 4
                    },
                }
            ]
        }
    })";

    // Select JSON based on game type
    switch (gameType) {
        case 0: return androidPatchesJson;
        case 1: return betaPatchesJson;
        case 2: return huaweiPatchesJson;
        default: return "{}"; // Return empty JSON if invalid gameType
    }
}