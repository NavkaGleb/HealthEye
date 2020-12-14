#include "Application.hpp"

#include <iostream>
#include <chrono>

#include <imgui-SFML.h>

namespace Hey {

    // constructor / destructor
    Application::Application(unsigned int width, unsigned int height, const char* title)
        : ::Ng::Engine::Application(width, height, title, sf::Style::Close),
          m_Colors({ 0.0f, 0.0f, 0.0f }),
          m_Font(nullptr),
          m_Visible(true),
          m_WorkTime{ { "25", "30", "35", "40" }, 0 },
          m_SleepTime{ { "2", "3", "4", "5" }, 0 },
          m_BigSleepTime{ { "10", "20" }, 0 },
          m_WorkTimeCount{ { "6", "7" }, 0 },
          m_Timer(std::chrono::seconds(5)) {

        InitWindow();
        InitFonts();
        InitShortcuts();
    }

    // member methods
    void Application::InitWindow() {
        // TODO: Set to context and enable auto update in RenderWindow
        m_RenderWindow.setVerticalSyncEnabled(true);
        m_RenderWindow.setFramerateLimit(60u);
        m_RenderWindow.setKeyRepeatEnabled(false);
    }

    void Application::InitFonts() {
        ImGuiIO& io = ImGui::GetIO();
        m_Font = io.Fonts->AddFontFromFileTTF("../../HealthEye/media/Fonts/Baloo2-Medium.ttf", 30.0f);

        ImGui::SFML::UpdateFontTexture();
    }

    void Application::InitShortcuts() {
        m_Shortcuts[ShortcutType::Visible] = {
            sf::Keyboard::LControl,
            sf::Keyboard::LSystem,
            sf::Keyboard::H
        };

        m_Shortcuts[ShortcutType::Kill] = {
            sf::Keyboard::LAlt,
            sf::Keyboard::LSystem,
            sf::Keyboard::K,
        };
    }

    void Application::HideWindow() {
        m_Visible = false;
        m_RenderWindow.setVisible(m_Visible);
    }

    void Application::ShowWindow() {
        m_Visible = true;
        m_RenderWindow.setVisible(m_Visible);
    }

    void Application::Kill() {
        m_RenderWindow.close();
    }

    void Application::OnPollEvent() {
        sf::Event event{};

        while (m_RenderWindow.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);

            if (event.type == sf::Event::Closed)
                HideWindow();
        }
    }

    void Application::OnUpdate() {
        // update shortcuts
        for (auto& [type, shortcut] : m_Shortcuts)
            shortcut.OnUpdate();

        if (m_Shortcuts[ShortcutType::Visible].IsActive())
            m_Visible ? HideWindow() : ShowWindow();

        if (m_Shortcuts[ShortcutType::Kill].IsActive())
            Kill();

        // begin ImGui
        ImGui::PushFont(m_Font);
        ImGui::SetNextWindowPos(sf::Vector2f(0.0f, 0.0f));
        ImGui::SetNextWindowSize(sf::Vector2f(700.0f, 500.0f));
        ImGui::SetNextWindowBgAlpha(0.7f);
        ImGui::Begin(
            "m_RenderWindow",
            nullptr,
            ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse
        );

        if (ImGui::ColorEdit3("Background color", m_Colors.Data.begin())) {
            m_Colors.Current.r = static_cast<sf::Uint8>(m_Colors.Data[0] * 255.0f);
            m_Colors.Current.g = static_cast<sf::Uint8>(m_Colors.Data[1] * 255.0f);
            m_Colors.Current.b = static_cast<sf::Uint8>(m_Colors.Data[2] * 255.0f);
        }

        ImGui::TextUnformatted(("FPS: " + std::to_string(1.0f / m_ElapsedTime.asSeconds())).c_str());
        ImGui::Combo("Work Time",       &m_WorkTime.Current,      m_WorkTime.Data.cbegin(),      m_WorkTime.Data.size()     );
        ImGui::Combo("Sleep Time",      &m_SleepTime.Current,     m_SleepTime.Data.cbegin(),     m_SleepTime.Data.size()    );
        ImGui::Combo("Big Sleep Time",  &m_BigSleepTime.Current,  m_BigSleepTime.Data.cbegin(),  m_BigSleepTime.Data.size() );
        ImGui::Combo("Work Time Count", &m_WorkTimeCount.Current, m_WorkTimeCount.Data.cbegin(), m_WorkTimeCount.Data.size());

        if (ImGui::Button("Start"))
            m_Timer.Start();

        ImGui::NewLine();

        if (ImGui::Button("Hide Window"))
            HideWindow();

        if (ImGui::Button("Kill Application :("))
            Kill();

        ImGui::End();
        ImGui::PopFont();
    }

    void Application::OnRender() {
        m_RenderWindow.clear(m_Colors.Current);

        ImGui::SFML::Render(m_RenderWindow);
        m_RenderWindow.display();
    }

} // namespace Hey