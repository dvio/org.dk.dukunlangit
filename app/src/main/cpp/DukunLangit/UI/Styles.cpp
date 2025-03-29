#include "Styles.h"
#include <GlobalVars.h>

namespace Styles {
    std::map<std::string, StyleConfig> Styles;

    // Track number of pushed colors/vars
    static int PushedColors = 0;
    static int PushedVars = 0;

    void ApplyStyle()
    {
//        if (GlobalVars::ActiveStyle == name) return; // Already applied
        if (Styles.find(GlobalVars::ActiveStyle) == Styles.end()) return; // Style not found

        ImGuiStyle& style = ImGui::GetStyle();
        const StyleConfig& config = Styles[GlobalVars::ActiveStyle];

        // Reset before applying new style
//        ResetStyle();

        // Track actual pushes
        PushedColors = 0;
        for (ImGuiCol col : config.colorPreset) {
            auto it = config.colors.find(col);
            if (it != config.colors.end()) {
                ImGui::PushStyleColor(col, it->second);
                PushedColors++; // Count only pushed colors
            }
        }

        PushedVars = 0;
        for (ImGuiStyleVar var : config.sizePreset) {
            auto it = config.sizes.find(var);
            if (it != config.sizes.end()) {
                ImGui::PushStyleVar(var, it->second);
                PushedVars++; // Count only pushed vars
            }
        }

//        GlobalVars::ActiveStyle = name;
    }

    void ResetStyle()
    {
        if (PushedColors > 0) {
            ImGui::PopStyleColor(PushedColors);
            PushedColors = 0;
        }
        if (PushedVars > 0) {
            ImGui::PopStyleVar(PushedVars);
            PushedVars = 0;
        }

//        GlobalVars::ActiveStyle.clear();
    }

}