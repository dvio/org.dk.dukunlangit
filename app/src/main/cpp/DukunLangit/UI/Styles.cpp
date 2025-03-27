#include "Styles.h"

namespace Styles {
    void ApplyStyle(const std::string& name)
    {
        if (Styles.find(name) == Styles.end()) return; // Style not found

        ImGuiStyle& style = ImGui::GetStyle();
        const StyleConfig& config = Styles[name];

        // Reset before applying new style
        ResetStyle();

        // Apply colors
        for (const auto& [col, value] : config.colors) {
            ImGui::PushStyleColor(col, value);
        }

        // Apply style vars
        for (const auto& [var, value] : config.vars) {
            ImGui::PushStyleVar(var, value);
        }

        ActiveStyle = name;
    }

    void ResetStyle()
    {
        if (ActiveStyle.empty()) return;

        ImGui::PopStyleColor(static_cast<int>(Styles[ActiveStyle].colors.size()));
        ImGui::PopStyleVar(static_cast<int>(Styles[ActiveStyle].vars.size()));

        ActiveStyle.clear();
    }

    void InitStyles()
    {
        Styles["TransparentNeon"] = {
                {
                        { ImGuiCol_WindowBg,       ImVec4(0, 0, 0, 0.3f) },
                        { ImGuiCol_Border,         ImVec4(0.8f, 1.0f, 1.0f, 0.6f) },
                        { ImGuiCol_Button,         ImVec4(0.1f, 0.1f, 0.1f, 0.5f) },
                        { ImGuiCol_ButtonHovered,  ImVec4(0.2f, 0.8f, 1.0f, 0.6f) },
                        { ImGuiCol_ButtonActive,   ImVec4(0.2f, 0.9f, 1.0f, 1.0f) },
                },
                {
                        { ImGuiStyleVar_WindowBorderSize, 2.0f },
                        { ImGuiStyleVar_FrameBorderSize,  1.5f },
                        { ImGuiStyleVar_WindowRounding,   10.0f },
                        { ImGuiStyleVar_FrameRounding,    5.0f },
                }
        };

        Styles["DarkMode"] = {
                {
                        { ImGuiCol_WindowBg,      ImVec4(0.1f, 0.1f, 0.1f, 1.0f) },
                        { ImGuiCol_Border,        ImVec4(0.2f, 0.2f, 0.2f, 1.0f) },
                        { ImGuiCol_Button,        ImVec4(0.3f, 0.3f, 0.3f, 1.0f) },
                        { ImGuiCol_ButtonHovered, ImVec4(0.4f, 0.4f, 0.4f, 1.0f) },
                        { ImGuiCol_ButtonActive,  ImVec4(0.5f, 0.5f, 0.5f, 1.0f) },
                },
                {
                        { ImGuiStyleVar_WindowBorderSize, 1.0f },
                        { ImGuiStyleVar_FrameBorderSize,  1.0f },
                        { ImGuiStyleVar_WindowRounding,   5.0f },
                        { ImGuiStyleVar_FrameRounding,    3.0f },
                }
        };

        Styles["LightMode"] = {
                {
                        { ImGuiCol_WindowBg,      ImVec4(0.9f, 0.9f, 0.9f, 1.0f) },
                        { ImGuiCol_Border,        ImVec4(0.7f, 0.7f, 0.7f, 1.0f) },
                        { ImGuiCol_Button,        ImVec4(0.8f, 0.8f, 0.8f, 1.0f) },
                        { ImGuiCol_ButtonHovered, ImVec4(0.7f, 0.7f, 0.7f, 1.0f) },
                        { ImGuiCol_ButtonActive,  ImVec4(0.6f, 0.6f, 0.6f, 1.0f) },
                },
                {
                        { ImGuiStyleVar_WindowBorderSize, 1.0f },
                        { ImGuiStyleVar_FrameBorderSize,  1.0f },
                        { ImGuiStyleVar_WindowRounding,   5.0f },
                        { ImGuiStyleVar_FrameRounding,    3.0f },
                }
        };
    }
}