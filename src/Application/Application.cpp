#include "Application.hpp"

#include <iostream>

#include <imgui-SFML.h>

namespace Hey {

    // constructor / destructor
    Application::Application(unsigned int width, unsigned int height, const char* title)
        : m_Colors{ 0.0f, 0.0f, 0.0f },
          m_Font(nullptr),
          m_Visible(true) {

        InitWindow(width, height, title);
        InitFonts();
        InitShortcuts();
    }

    Application::~Application() {
        ImGui::SFML::Shutdown();
    }

    // public methods
    void Application::Run() {
        while (m_Window.isOpen()) {
            OnPollEvent();
            OnUpdate();
            OnRender();
        }
    }

    // member methods
    void Application::InitWindow(unsigned int width, unsigned int height, const char* title) {
        // init SFML RenderWindow
        m_Window.create(sf::VideoMode(width, height), title);
        m_Window.setVerticalSyncEnabled(true);
        m_Window.setFramerateLimit(60u);
        m_Window.setKeyRepeatEnabled(false);

        // hide Windows console window
        HWND__* consoleWindow = GetConsoleWindow();
        ::ShowWindow(consoleWindow, SW_HIDE);

        // init ImGui
        ImGui::SFML::Init(m_Window);
    }

    void Application::InitFonts() {
        ImGuiIO &io = ImGui::GetIO();
        m_Font = io.Fonts->AddFontFromFileTTF("../media/Fonts/Baloo2-Medium.ttf", 30.0f);

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
        m_Window.setVisible(m_Visible);
    }

    void Application::ShowWindow() {
        m_Visible = true;
        m_Window.setVisible(m_Visible);
    }

    void Application::Kill() {
        m_Window.close();
    }

    void Application::OnPollEvent() {
        sf::Event event{};

        while (m_Window.pollEvent(event)) {
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

        // update ImGui
        sf::Time elapsedTime = m_Clock.restart();
        ImGui::SFML::Update(m_Window, elapsedTime);

        // begin ImGui
        ImGui::PushFont(m_Font);
        ImGui::SetNextWindowPos(sf::Vector2f(0.0f, 0.0f));
        ImGui::SetNextWindowSize(sf::Vector2f(700.0f, 400.0f));
        ImGui::SetNextWindowBgAlpha(0.7f);
        ImGui::Begin(
            "m_Window",
            nullptr,
            ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse
        );

        if (ImGui::ColorEdit3("Background color", m_Colors)) {
            m_BackgroundColor.r = static_cast<sf::Uint8>(m_Colors[0] * 255.0f);
            m_BackgroundColor.g = static_cast<sf::Uint8>(m_Colors[1] * 255.0f);
            m_BackgroundColor.b = static_cast<sf::Uint8>(m_Colors[2] * 255.0f);
        }

        ImGui::TextUnformatted(("FPS: " + std::to_string(1.0f / elapsedTime.asSeconds())).c_str());

        if (ImGui::Button("Hide Window"))
            HideWindow();

        if (ImGui::Button("Kill Application :("))
            Kill();

        ImGui::End();
        ImGui::PopFont();
    }

    void Application::OnRender() {
        m_Window.clear(m_BackgroundColor);

        ImGui::SFML::Render(m_Window);
        m_Window.display();
    }

} // namespace Hey