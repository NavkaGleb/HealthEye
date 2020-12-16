#include "Application.hpp"

#include <windows.h>

namespace Ng::Engine {

    // constructor / destructor
    Application::Application(unsigned int width, unsigned int height,
                             const char* title, uint32_t style, const sf::ContextSettings& contextSettings) {
        // init SFML RenderWindow
        m_RenderWindow.create(sf::VideoMode(width, height), title, style, contextSettings);
        State::GetContext().m_RenderWindow = &m_RenderWindow;

        // hide Windows console window
        HWND__* consoleWindow = GetConsoleWindow();
        ::ShowWindow(consoleWindow, SW_HIDE);
    }

    // public methods
    void Application::OnPollEvent() {
        sf::Event event{};

        while (m_RenderWindow.pollEvent(event)) {
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
            OnUpdateElapsedTime();
            OnPollEvent();
            OnUpdate();
            OnRender();
        }
    }

    // member methods
    void Application::OnUpdateElapsedTime() {
        m_ElapsedTime = m_Clock.restart();
    }

} // namespace Ng::Engine
