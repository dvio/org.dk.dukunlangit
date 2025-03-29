#include <imgui.h>
#include <map>
#include <vector>
#include <string>

namespace Styles {
    struct StyleConfig {
        std::map<ImGuiCol, ImVec4> colors;  // All defined colors for the style
        std::map<ImGuiStyleVar, float> sizes;  // All defined sizes for the style
        std::vector<ImGuiCol> colorPreset; // Determines which colors to apply
        std::vector<ImGuiStyleVar> sizePreset; // Determines which sizes to apply
    };

    extern std::map<std::string, StyleConfig> Styles;

    void ApplyStyle();
    void ResetStyle();
    void InitStyles();
}

