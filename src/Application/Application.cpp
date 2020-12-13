#include "Application.hpp"

#include <iostream>
#include <chrono>
#include <thread>

#include <imgui.h>
#include <imgui-SFML.h>

#include <SFML/Window/Event.hpp>

namespace Hey {     // healthy eye

    // constructor / destructor
    Application::Application(unsigned int width, unsigned int height, const char* title)
        : m_VideoMode(width, height),
          m_Title(title) {

        m_WINWindow = GetConsoleWindow();
        ShowWindow(m_WINWindow, SW_HIDE);

    }

    Application::~Application() {
        ImGui::SFML::Shutdown();
    }

    // public methods
    void Application::Run() {
        OpenWindow();

        sf::Clock clock;
        sf::Color backgroundColor;
        float color[3] = {0.f, 0.f, 0.f};

        bool checkBox = true;
        float sliderValue = 0.0f;

        const char *items[] = {"Apple", "Banana", "Orange"};
        int selectedItem = 0;

        ImGui::SFML::Init(m_SFMLWindow);
        ImGui::GetStyle();

        ImGuiIO &io = ImGui::GetIO();
        ImFont *font = io.Fonts->AddFontFromFileTTF("../media/Fonts/Baloo2-Medium.ttf", 30.0f);
        ImGui::SFML::UpdateFontTexture();

        std::chrono::time_point<std::chrono::steady_clock> start = std::chrono::steady_clock::now();

        while (m_SFMLWindow.isOpen()) {
            decltype(start) end = std::chrono::steady_clock::now();

            sf::Event event{};

            while (m_SFMLWindow.pollEvent(event)) {
                ImGui::SFML::ProcessEvent(event);

                if (event.type == sf::Event::Closed)
                    m_SFMLWindow.setVisible(false);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) &&
                sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt) &&
                sf::Keyboard::isKeyPressed(sf::Keyboard::O))
                std::cout << "fuck this shit" << std::endl;


            OnUpdate();
            OnRender();
        }
    }

    // member methods
    void Application::OpenWindow() {
        m_SFMLWindow.create(m_VideoMode, m_Title, sf::Style::Close);
        m_SFMLWindow.setVerticalSyncEnabled(true);
        m_SFMLWindow.setFramerateLimit(60u);
    }

    void Application::CloseWindow() {
        m_SFMLWindow.close();
    }

    void Application::OnUpdate() {
        if (std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() >= 2000) {
//                CloseWindow();
//                m_SFMLWindow.setVisible(false);
            std::this_thread::sleep_for(std::chrono::milliseconds(2000));
//                OpenWindow();
//                m_SFMLWindow.setVisible(true);
            start = std::chrono::steady_clock::now();
            end = std::chrono::steady_clock::now();
        }

        /// update
        // update ImGui
        sf::Time elapsedTime = clock.restart();
        ImGui::SFML::Update(m_SFMLWindow, elapsedTime);

        // begin ImGui
        ImGui::PushFont(font);
        ImGui::SetNextWindowPos(sf::Vector2f(0.0f, 0.0f));
        ImGui::SetNextWindowSize(sf::Vector2f(700.0f, 400.0f));
        ImGui::SetNextWindowBgAlpha(0.7f);
        ImGui::Begin(
            "m_SFMLWindow",
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
        ImGui::TextUnformatted(std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()).c_str());
        ImGui::Checkbox("Toggle", &checkBox);
        ImGui::SliderFloat("Slider", &sliderValue, 0.0f, 10.0f, "%.1f");
        ImGui::NewLine();
        ImGui::ListBox("ListBox", &selectedItem, items, IM_ARRAYSIZE(items), 2);
        ImGui::Combo("Combo", &selectedItem, items, IM_ARRAYSIZE(items));

        if (ImGui::Button("Push Button"))
            std::cout << "fuck this shit" << std::endl;

        ImGui::End();
        ImGui::PopFont();
    }

    void Application::OnRender() {
        m_SFMLWindow.clear(backgroundColor);
        ImGui::SFML::Render(m_SFMLWindow);
        m_SFMLWindow.display();
    }

} // namespace Hey