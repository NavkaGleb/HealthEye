#include <iostream>
#include <string>
#include <windows.h>

#include <SFML/Graphics.hpp>

#include <imgui.h>
#include <imgui-SFML.h>

int main() {
    sf::RenderWindow window(sf::VideoMode(500, 500), "", sf::Style::Close);
    sf::Clock clock;
    sf::Color backgroundColor;
    float color[3] = { 0.f, 0.f, 0.f };
    std::string windowTitle = "SFML + ImGui = <3";

    window.setVerticalSyncEnabled(true);
    window.setTitle(windowTitle);
    ImGui::SFML::Init(window);

    while (window.isOpen()) {
        sf::Event event{};

        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);

            if (event.type == sf::Event::Closed)
                window.close();
        }

        ImGui::SFML::Update(window, clock.restart());

        ImGui::Begin("Sample Window");

        if (ImGui::ColorEdit3("Background color", color)) {
            backgroundColor.r = static_cast<sf::Uint8>(color[0] * 255.f);
            backgroundColor.g = static_cast<sf::Uint8>(color[1] * 255.f);
            backgroundColor.b = static_cast<sf::Uint8>(color[2] * 255.f);
        }

        ImGui::InputText("Window title", (char*)windowTitle.c_str(), 255);

        if (ImGui::Button("Update window title"))
            window.setTitle(windowTitle);

        ImGui::End();

        window.clear(backgroundColor);
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
}