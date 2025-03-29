#include <UI.h>
#include <Styles.h>
#include <GlobalVars.h>

void UI::DrawStyleSelector(std::string label) {
    if (ImGui::BeginCombo(label.c_str(), GlobalVars::ActiveStyle.c_str())) {
        std::string selectedStyle; // Store the selection separately

        for (const auto& style : Styles::Styles) {
            bool isSelected = (GlobalVars::ActiveStyle == style.first);
            if (ImGui::Selectable(style.first.c_str(), isSelected)) {
                selectedStyle = style.first; // Store selection for later
            }
            if (isSelected) {
                ImGui::SetItemDefaultFocus();
            }
        }

        ImGui::EndCombo();

        // Apply the style **after** ImGui UI operations are done
        if (!selectedStyle.empty() && selectedStyle != GlobalVars::ActiveStyle) {
            GlobalVars::ActiveStyle = selectedStyle;
        }
    }
}
