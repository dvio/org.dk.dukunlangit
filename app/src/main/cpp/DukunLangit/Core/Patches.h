#pragma once
#include <string>
#include <vector>
#include <unordered_map>

#include "Utils/MemoryTools.h"
#include "MemoryPatch.hpp"

namespace Patches {
    struct ScanParameters {
        std::string pattern;  // IDA-style pattern
        int scanOffset;       // Offset from scan result
        bool usePointerCalc;  // Whether to use getPointerImm
        int pointerOffset;    // Offset for getPointerImm

        ScanParameters(const std::string& pat, int offset, bool usePtrCalc, int ptrOffset)
                : pattern(pat), scanOffset(offset), usePointerCalc(usePtrCalc), pointerOffset(ptrOffset) {}
    };

    struct Patch {
        MemoryPatch patch;
        std::vector<uint8_t> originalBytes;  // Expected original memory bytes
        std::vector<uint8_t> patchedBytes;   // Modified bytes for the patch
        ScanParameters scanParams;           // Scanning parameters
        bool isApplied = false;
        bool isValid = false;
        uintptr_t address = 0;               // Final patched address (set dynamically)

        Patch(const ScanParameters& scan, std::vector<uint8_t> original, std::vector<uint8_t> patched)
                : scanParams(scan), originalBytes(original), patchedBytes(patched) {}

        bool findAndValidate() {
            //fix this : Find pattern here
            uintptr_t scanResult = 0; //findPattern(scanParams.pattern);

            if (!scanResult) return false;

            address = scanResult + scanParams.scanOffset;

            if (scanParams.usePointerCalc) {
                address = MemoryTools::getPointerImm(address, scanParams.pointerOffset);
            }

            std::vector<uint8_t> currentValue(originalBytes.size());
            KittyMemory::memRead(reinterpret_cast<void*>(address), currentValue.data(), currentValue.size());
            isValid = (currentValue == originalBytes);

            if (isValid) {
                //fix this
//                patch = MemoryPatch::createWithBytes("libgame.so", address, patchedBytes);
            }

            return isValid;
        }

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

    extern std::unordered_map<std::string, std::vector<Patch>> Patches;
}