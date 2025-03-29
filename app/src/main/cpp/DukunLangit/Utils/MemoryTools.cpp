#include "MemoryTools.h"

#include <cstring>
#include <iostream>

namespace MemoryTools {

// Function to calculate the final pointer from ADRP + LDR/STR/ADD/SUB
    uintptr_t getPointerImm(uintptr_t adrp_address, int32_t offset) {
        uint8_t memory[1024] = {};

        // Read ADRP instruction
        uint32_t adrp_instr = *reinterpret_cast<uint32_t*>(adrp_address);
        memcpy(&memory[100], &adrp_instr, sizeof(adrp_instr));

        // Compute the address of the second instruction (LDR, ADD, SUB, etc.)
        uintptr_t next_instr_address = adrp_address + offset;
        uint32_t next_instr = *reinterpret_cast<uint32_t*>(next_instr_address);
        memcpy(&memory[104], &next_instr, sizeof(next_instr));

        // Ensure it's an ADRP instruction
        if ((adrp_instr & 0x9F000000) != 0x90000000) {
            return 0; // Not a valid ADRP instruction
        }

        // Extract immhi and immlo, then reconstruct the immediate value
        int64_t imm = ((adrp_instr >> 5) & 0x7FFFF) << 12; // immhi
        imm |= (adrp_instr >> 29) & 0x3; // immlo

        // Sign-extend the 21-bit immediate value
        if (imm & (1LL << 20)) {
            imm |= ~((1LL << 21) - 1);
        }

        // Calculate the base address from ADRP
        uintptr_t base_address = (adrp_address & ~0xFFF) + imm;

        // Decode the second instruction
        if ((next_instr & 0xFFC00000) == 0x91000000) {
            // ADD immediate: 10010001 (25-bit mask)
            uint32_t imm12 = (next_instr >> 10) & 0xFFF; // Extract 12-bit immediate
            uint32_t shift = (next_instr >> 22) & 0x1;   // Shift bit
            uintptr_t add_offset = shift ? (imm12 << 12) : imm12;
            return base_address + add_offset;

        } else if ((next_instr & 0xFFC00000) == 0xD1000000) {
            // SUB immediate: 11010001 (25-bit mask)
            uint32_t imm12 = (next_instr >> 10) & 0xFFF; // Extract 12-bit immediate
            uint32_t shift = (next_instr >> 22) & 0x1;   // Shift bit
            uintptr_t sub_offset = shift ? (imm12 << 12) : imm12;
            return base_address - sub_offset;

        } else if ((next_instr & 0x3B000000) == 0x39000000) {
            // LDRB, LDR, STR (12-bit signed offset)
            int32_t ldr_offset = (next_instr >> 10) & 0xFFF; // Extract 12-bit offset
            if (ldr_offset & 0x800) { // Sign extension for negative offsets
                ldr_offset |= ~((1 << 12) - 1);
            }
            ldr_offset <<= (next_instr >> 30) & 0x3; // Scale offset
            return base_address + ldr_offset;
        }

        return 0; // Unsupported instruction
    }
}

// Example usage
//int main() {
//    uintptr_t final_address = getPointerImm(0x24CBFC0, 0x8);
//    std::cout << "Final Address: 0x" << std::hex << final_address << std::endl;
//    return 0;
//}
