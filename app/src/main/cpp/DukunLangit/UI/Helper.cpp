#include <UI.h>

#include <unordered_map>

bool UI::BeginScrollingChild(const char* str_id, const ImVec2& size, ImGuiChildFlags childFlags, ImGuiWindowFlags flags) {
    ImGui::BeginChild(str_id, size, childFlags, flags);

    static std::unordered_map<std::string, float> scroll_positions;
    static std::unordered_map<std::string, bool> is_scrolling_map;
    static std::unordered_map<std::string, ImVec2> touch_start_map;
    static std::unordered_map<std::string, float> scroll_start_map;

    float& scroll_y = scroll_positions[str_id];
    bool& is_scrolling = is_scrolling_map[str_id];
    ImVec2& touch_start = touch_start_map[str_id];
    float& scroll_start = scroll_start_map[str_id];

    // Detect touch start
    if (ImGui::IsWindowHovered() && ImGui::IsMouseClicked(0)) {
        touch_start = ImGui::GetIO().MousePos;
        scroll_start = ImGui::GetScrollY();
        is_scrolling = true;
    }

    // Handle dragging
    if (is_scrolling && ImGui::IsMouseDragging(0)) {
        float scroll_speed = 1.5f;
        float delta_y = (ImGui::GetIO().MousePos.y - touch_start.y) * scroll_speed;
        scroll_y = scroll_start - delta_y;  // Maintain offset
    }

    // Stop scrolling when released
    if (ImGui::IsMouseReleased(0)) {
        is_scrolling = false;
    }

    ImGui::SetScrollY(scroll_y);  // Apply smooth scrolling

    return true;
}

void UI::EndScrollingChild() {
    ImGui::EndChild();
}