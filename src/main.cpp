#include <iostream>

#include <SFML/Graphics.hpp>

#include <imgui.h>
#include <imgui-SFML.h>

int main() {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML + ImGui = <3", sf::Style::Close);
    sf::Clock clock;
    sf::Color backgroundColor;
    float color[3] = { 0.f, 0.f, 0.f };

    bool checkBox = true;
    float sliderValue = 0.0f;

    const char* items[] = { "Apple", "Banana", "Orange" };
    int selectedItem = 0;

    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60u);

    ImGui::SFML::Init(window);
    ImGui::GetStyle();

    ImGuiIO& io = ImGui::GetIO();
    ImFont* font = io.Fonts->AddFontFromFileTTF("../media/Fonts/Baloo2-Medium.ttf", 30.0f);
    ImGui::SFML::UpdateFontTexture();

    while (window.isOpen()) {
        sf::Event event{};

        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);

            if (event.type == sf::Event::Closed)
                window.close();
        }

        /// update
        // update ImGui
        sf::Time elapsedTime = clock.restart();
        ImGui::SFML::Update(window, elapsedTime);

        // begin ImGui
        ImGui::PushFont(font);
        ImGui::SetNextWindowPos(sf::Vector2f(0.0f, 0.0f));
        ImGui::SetNextWindowSize(sf::Vector2f(700.0f, 400.0f));
        ImGui::SetNextWindowBgAlpha(0.7f);
        ImGui::Begin(
            "Window",
            nullptr,
            ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse
        );

        // background color
        if (ImGui::ColorEdit3("Background color", color)) {
            backgroundColor.r = static_cast<sf::Uint8>(color[0] * 255.0f);
            backgroundColor.g = static_cast<sf::Uint8>(color[1] * 255.0f);
            backgroundColor.b = static_cast<sf::Uint8>(color[2] * 255.0f);
        }

        ImGui::TextUnformatted(("FPS: " + std::to_string(1.0f / elapsedTime.asSeconds())).c_str());
        ImGui::Checkbox("Toggle", &checkBox);
        ImGui::SliderFloat("Slider", &sliderValue, 0.0f, 10.0f, "%.1f");
        ImGui::NewLine();
        ImGui::ListBox("ListBox", &selectedItem, items, IM_ARRAYSIZE(items), 2);
        ImGui::Combo("Combo", &selectedItem, items, IM_ARRAYSIZE(items));

        if (ImGui::Button("Push Button"))
            std::cout << "fuck this shit" << std::endl;

        ImGui::End();
        ImGui::PopFont();

        /// render
        window.clear(backgroundColor);
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
}