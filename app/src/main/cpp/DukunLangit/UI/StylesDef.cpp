#include <Styles.h>
#include "GlobalVars.h"

void Styles::InitStyles() {
    Styles["RedNeon"] = {
            // Colors
            {
                    { ImGuiCol_WindowBg,       ImVec4(0, 0, 0, 0.3f) },
                    { ImGuiCol_Border,         ImVec4(1.0f, 0.2f, 0.2f, 0.6f) },
                    { ImGuiCol_Button,         ImVec4(0.2f, 0.0f, 0.0f, 0.5f) },
                    { ImGuiCol_ButtonHovered,  ImVec4(1.0f, 0.2f, 0.2f, 0.6f) },
                    { ImGuiCol_ButtonActive,   ImVec4(1.0f, 0.1f, 0.1f, 1.0f) },
                    { ImGuiCol_FrameBg,        ImVec4(0.2f, 0.0f, 0.0f, 0.5f) },
                    { ImGuiCol_FrameBgHovered, ImVec4(1.0f, 0.2f, 0.2f, 0.6f) },
                    { ImGuiCol_FrameBgActive,  ImVec4(1.0f, 0.1f, 0.1f, 1.0f) },
            },
            // Sizes
            {
                    { ImGuiStyleVar_WindowBorderSize, 0.0f },
                    { ImGuiStyleVar_FrameBorderSize,  1.5f },
                    { ImGuiStyleVar_WindowRounding,   20.0f },
                    { ImGuiStyleVar_FrameRounding,    10.0f },
                    { ImGuiStyleVar_ScrollbarSize,    4.0f },
            },
            // Color preset
            {
                    ImGuiCol_WindowBg,
                    ImGuiCol_Border,
                    ImGuiCol_Button,
                    ImGuiCol_ButtonHovered,
                    ImGuiCol_ButtonActive,
                    ImGuiCol_FrameBg,
                    ImGuiCol_FrameBgHovered,
                    ImGuiCol_FrameBgActive
            },
            // Size preset
            {
                    ImGuiStyleVar_WindowBorderSize,
                    ImGuiStyleVar_FrameBorderSize,
                    ImGuiStyleVar_WindowRounding,
                    ImGuiStyleVar_FrameRounding,
                    ImGuiStyleVar_ScrollbarSize
            }
    };

    Styles["BlueNeon"] = {
            // Colors
            {
                    { ImGuiCol_WindowBg,       ImVec4(0, 0, 0, 0.3f) },
                    { ImGuiCol_Border,         ImVec4(0.8f, 1.0f, 1.0f, 0.6f) },
                    { ImGuiCol_Button,         ImVec4(0.1f, 0.1f, 0.1f, 0.5f) },
                    { ImGuiCol_ButtonHovered,  ImVec4(0.2f, 0.8f, 1.0f, 0.6f) },
                    { ImGuiCol_ButtonActive,   ImVec4(0.2f, 0.9f, 1.0f, 1.0f) },
                    { ImGuiCol_FrameBg,        ImVec4(0.1f, 0.1f, 0.1f, 0.5f) },
                    { ImGuiCol_FrameBgHovered, ImVec4(0.2f, 0.8f, 1.0f, 0.6f) },
                    { ImGuiCol_FrameBgActive,  ImVec4(0.2f, 0.9f, 1.0f, 1.0f) },
            },
            // Sizes
            {
                    { ImGuiStyleVar_WindowBorderSize, 0.0f },
                    { ImGuiStyleVar_FrameBorderSize,  1.5f },
                    { ImGuiStyleVar_WindowRounding,   20.0f },
                    { ImGuiStyleVar_FrameRounding,    10.0f },
                    { ImGuiStyleVar_ScrollbarSize,    4.0f },
            },
            // Color preset
            {
                    ImGuiCol_WindowBg,
                    ImGuiCol_Border,
                    ImGuiCol_Button,
                    ImGuiCol_ButtonHovered,
                    ImGuiCol_ButtonActive,
                    ImGuiCol_FrameBg,
                    ImGuiCol_FrameBgHovered,
                    ImGuiCol_FrameBgActive
            },
            // Size preset
            {
                    ImGuiStyleVar_WindowBorderSize,
                    ImGuiStyleVar_FrameBorderSize,
                    ImGuiStyleVar_WindowRounding,
                    ImGuiStyleVar_FrameRounding,
                    ImGuiStyleVar_ScrollbarSize,

            }
    };

    Styles["DarkMode"] = {
            // Colors
            {
                    { ImGuiCol_WindowBg,       ImVec4(0.1f, 0.1f, 0.1f, 1.0f) },
                    { ImGuiCol_Text,           ImVec4(1.0f, 1.0f, 1.0f, 1.0f) },
                    { ImGuiCol_Border,         ImVec4(0.5f, 0.5f, 0.5f, 0.7f) },
                    { ImGuiCol_Button,         ImVec4(0.2f, 0.2f, 0.2f, 1.0f) },
                    { ImGuiCol_ButtonHovered,  ImVec4(0.4f, 0.4f, 0.4f, 1.0f) },
                    { ImGuiCol_ButtonActive,   ImVec4(0.6f, 0.6f, 0.6f, 1.0f) },
                    { ImGuiCol_FrameBg,        ImVec4(0.15f, 0.15f, 0.15f, 1.0f) },
                    { ImGuiCol_FrameBgHovered, ImVec4(0.3f, 0.3f, 0.3f, 1.0f) },
                    { ImGuiCol_FrameBgActive,  ImVec4(0.45f, 0.45f, 0.45f, 1.0f) },
            },
            // Sizes
            {
                    { ImGuiStyleVar_WindowBorderSize, 1.0f },
                    { ImGuiStyleVar_FrameBorderSize,  1.0f },
                    { ImGuiStyleVar_WindowRounding,   5.0f },
                    { ImGuiStyleVar_FrameRounding,    3.0f },
                    { ImGuiStyleVar_ScrollbarSize,    4.0f },
            },
            // Color preset
            {
                    ImGuiCol_WindowBg,
                    ImGuiCol_Text,
                    ImGuiCol_Border,
                    ImGuiCol_Button,
                    ImGuiCol_ButtonHovered,
                    ImGuiCol_ButtonActive,
                    ImGuiCol_FrameBg,
                    ImGuiCol_FrameBgHovered,
                    ImGuiCol_FrameBgActive
            },
            // Size preset
            {
                    ImGuiStyleVar_WindowBorderSize,
                    ImGuiStyleVar_FrameBorderSize,
                    ImGuiStyleVar_WindowRounding,
                    ImGuiStyleVar_FrameRounding,
                    ImGuiStyleVar_ScrollbarSize
            }
    };

    Styles["LightMode"] = {
            // Colors
            {
                    { ImGuiCol_WindowBg,       ImVec4(1.0f, 1.0f, 1.0f, 1.0f) },
                    { ImGuiCol_Text,           ImVec4(0.0f, 0.0f, 0.0f, 1.0f) },
                    { ImGuiCol_Border,         ImVec4(0.8f, 0.8f, 0.8f, 1.0f) },
                    { ImGuiCol_Button,         ImVec4(0.9f, 0.9f, 0.9f, 1.0f) },
                    { ImGuiCol_ButtonHovered,  ImVec4(0.7f, 0.7f, 0.7f, 1.0f) },
                    { ImGuiCol_ButtonActive,   ImVec4(0.6f, 0.6f, 0.6f, 1.0f) },
                    { ImGuiCol_FrameBg,        ImVec4(0.95f, 0.95f, 0.95f, 1.0f) },
                    { ImGuiCol_FrameBgHovered, ImVec4(0.85f, 0.85f, 0.85f, 1.0f) },
                    { ImGuiCol_FrameBgActive,  ImVec4(0.75f, 0.75f, 0.75f, 1.0f) },
            },
            // Sizes
            {
                    { ImGuiStyleVar_WindowBorderSize, 1.0f },
                    { ImGuiStyleVar_FrameBorderSize,  1.0f },
                    { ImGuiStyleVar_WindowRounding,   3.0f },
                    { ImGuiStyleVar_FrameRounding,    2.0f },
                    { ImGuiStyleVar_ScrollbarSize,    4.0f },
            },
            // Color preset
            {
                    ImGuiCol_WindowBg,
                    ImGuiCol_Text,
                    ImGuiCol_Border,
                    ImGuiCol_Button,
                    ImGuiCol_ButtonHovered,
                    ImGuiCol_ButtonActive,
                    ImGuiCol_FrameBg,
                    ImGuiCol_FrameBgHovered,
                    ImGuiCol_FrameBgActive
            },
            // Size preset
            {
                    ImGuiStyleVar_WindowBorderSize,
                    ImGuiStyleVar_FrameBorderSize,
                    ImGuiStyleVar_WindowRounding,
                    ImGuiStyleVar_FrameRounding,
                    ImGuiStyleVar_ScrollbarSize
            }
    };


}
