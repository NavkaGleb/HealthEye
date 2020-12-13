#include "Application.hpp"

#include <iostream>
#include <thread>

#include <imgui-SFML.h>

#include <SFML/Window/Event.hpp>

namespace Hey {

    // constructor / destructor
    Application::Application(unsigned int width, unsigned int height, const char* title)
        : m_Window(sf::VideoMode(width, height), title),
          m_Colors{ 0.0f, 0.0f, 0.0f },
          m_Visible(true) {

        HWND__* windowsConsoleWindow = GetConsoleWindow();
        ShowWindow(windowsConsoleWindow, SW_HIDE);

        ImGui::SFML::Init(m_Window);

        ImGuiIO &io = ImGui::GetIO();
        m_Font = io.Fonts->AddFontFromFileTTF("../media/Fonts/Baloo2-Medium.ttf", 30.0f);
        ImGui::SFML::UpdateFontTexture();

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

    Application::~Application() {
        ImGui::SFML::Shutdown();
    }

    // public methods
    void Application::Run() {
        m_Start = std::chrono::steady_clock::now();

        while (m_Window.isOpen()) {
            sf::Event event{};

            while (m_Window.pollEvent(event)) {
                ImGui::SFML::ProcessEvent(event);

                if (event.type == sf::Event::Closed) {
                    m_Visible = false;
                    m_Window.setVisible(m_Visible);
                }

            }

            OnUpdate();
            OnRender();
        }
    }

    // member methods
    void Application::OpenWindow() {
        m_Window.create(m_VideoMode, m_Title, sf::Style::Close);
        m_Window.setVerticalSyncEnabled(true);
        m_Window.setFramerateLimit(60u);
        m_Window.setKeyRepeatEnabled(false);
    }

    void Application::CloseWindow() {
        m_Window.close();
    }

    void Application::OnUpdate() {
        for (auto& [type, shortcut] : m_Shortcuts)
            shortcut.OnUpdate();

        if (m_Shortcuts[ShortcutType::Visible].IsActive()) {
            m_Visible = !m_Visible;
            m_Window.setVisible(m_Visible);
        }

        if (m_Shortcuts[ShortcutType::Kill].IsActive()) {
            m_Window.close();
        }

        m_End = std::chrono::steady_clock::now();

//        if (std::chrono::duration_cast<std::chrono::milliseconds>(m_End - m_Start).count() >= 2000) {
////                CloseWindow();
////                m_Window.setVisible(false);
//            std::this_thread::sleep_for(std::chrono::milliseconds(2000));
////                OpenWindow();
////                m_Window.setVisible(true);
//            m_Start = std::chrono::steady_clock::now();
//            m_End = std::chrono::steady_clock::now();
//        }

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
        ImGui::TextUnformatted(std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(m_End - m_Start).count()).c_str());

        if (ImGui::Button("Push Button"))
            std::cout << "fuck this shit" << std::endl;

        ImGui::End();
        ImGui::PopFont();
    }

    void Application::OnRender() {
        m_Window.clear(m_BackgroundColor);
        ImGui::SFML::Render(m_Window);
        m_Window.display();
    }

} // namespace Hey