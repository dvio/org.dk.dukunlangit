#include <imgui.h>
#include <map>
#include <vector>
#include <string>

namespace Styles {
    struct StyleConfig {
        std::vector<std::pair<ImGuiCol, ImVec4>> colors;
        std::vector<std::pair<ImGuiStyleVar, float>> vars;
    };

    static std::map<std::string, StyleConfig> Styles;
    static std::string ActiveStyle = "";

    extern void ApplyStyle(const std::string& name);
    extern void ResetStyle();
    extern void InitStyles();


}
