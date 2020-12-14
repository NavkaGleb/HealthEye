#include "Application.hpp"

#include <windows.h>

#include <imgui-SFML.h>

#include "States/State.hpp"

namespace Ng::Engine {

    // constructor / destructor
    Application::Application(unsigned int width, unsigned int height, const char* title, uint32_t style) {
        // init SFML RenderWindow
        m_RenderWindow.create(sf::VideoMode(width, height), title, style);
        State::GetContext().RenderWindow = &m_RenderWindow;

        // hide Windows console window
        HWND__* consoleWindow = GetConsoleWindow();
        ::ShowWindow(consoleWindow, SW_HIDE);

        // init ImGui
        ImGui::SFML::Init(m_RenderWindow);
    }

    Application::~Application() {
        ImGui::SFML::Shutdown();
    }

    // public methods
    void Application::OnPollEvent() {
        sf::Event event{};

        while (m_RenderWindow.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);

            if (event.type == sf::Event::Closed)
                m_RenderWindow.close();

            if (event.type == sf::Event::MouseMoved)
                State::GetStateStack().OnMouseMoved(event);

            if (event.type == sf::Event::MouseButtonPressed)
                State::GetStateStack().OnMouseButtonPressed(event);

            if (event.type == sf::Event::MouseButtonReleased)
                State::GetStateStack().OnMouseButtonReleased(event);

            if (event.type == sf::Event::KeyPressed)
                State::GetStateStack().OnKeyPressed(event);
        }
    }

    void Application::Run() {
        while (m_RenderWindow.isOpen()) {
            OnPollEvent();
            OnImGuiUpdate();
            OnUpdate();
            OnRender();
        }
    }

    // private methods
    void Application::OnImGuiUpdate() {
        m_ElapsedTime = m_Clock.restart();
        ImGui::SFML::Update(m_RenderWindow, m_ElapsedTime);
    }

} // namespace Ng::Engine
