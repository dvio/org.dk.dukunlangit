#pragma once
#include <string>
#include <vector>
#include <unordered_map>

#include "MemoryPatch.hpp"
#include <nlohmann/json.hpp>

namespace Patches {
    struct ScanParameters {
        std::string pattern;  // IDA-style pattern
        int scanOffset;       // Offset from scan result
        bool usePointerCalc;  // Whether to use getPointerImm
        int pointerOffset;    // Offset for getPointerImm

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(ScanParameters, pattern, scanOffset, usePointerCalc, pointerOffset)
    };

    struct Patch {
        uintptr_t address = 0; // Final patched address (set dynamically)
        int32_t addressOffset = 0; // Offset from the address
        std::vector<uint8_t> originalBytes;  // Expected original memory bytes
        std::vector<uint8_t> patchedBytes;   // Modified bytes for the patch
        ScanParameters scanParams;           // Scanning parameters
        bool isApplied = false;
        bool isValid = false;
        bool scanOnInvalid = false;
        MemoryPatch patch;

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(Patch, address, originalBytes, patchedBytes, scanParams, isApplied, isValid, scanOnInvalid, addressOffset)

//        bool findAndValidate() {
//
//            uintptr_t scanResult = 0; //findPattern(scanParams.pattern);
//
//            //fix this : Find pattern here
//
//            if (!scanResult) return false;
//
//            address = scanResult + scanParams.scanOffset;
//
//            if (scanParams.usePointerCalc) {
//                address = MemoryTools::getPointerImm(address, scanParams.pointerOffset);
//            }
//
//            std::vector<uint8_t> currentValue(originalBytes.size());
//            KittyMemory::memRead(reinterpret_cast<void*>(address), currentValue.data(), currentValue.size());
//            isValid = (currentValue == originalBytes);
//
//            if (isValid) {
//                patch = MemoryPatch::createWithBytes(reinterpret_cast<void*>(absoluteAddress), patchedBytes);
//                //fix this
////                patch = MemoryPatch::createWithBytes("libgame.so", address, patchedBytes);
//            }
//
//            return isValid;
//        }

        void apply() {
            if (isValid) {
                patch.Modify();
                isApplied = true;
            }
        }

        void restore() {
            patch.Restore();
            isApplied = false;
        }
    };

    extern std::unordered_map<std::string, std::vector<Patch>> patches;
    extern int version;

    void Init(int gameType);
    void LoadFromJson(const std::string& jsonData);
    bool CheckForUpdates();
    bool ApplyUpdate(const std::string& encryptedData);
    std::string GetPatchesJson(int gameType);

//    extern std::unordered_map<std::string, std::vector<Patch>> Patches;
//
//    std::string GetPatchesJson(int gameType);
//    void Init(int gameType);
}