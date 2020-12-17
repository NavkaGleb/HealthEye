#include "Application.hpp"

#include <imgui-SFML.h>

#include "States/InitState.hpp"

namespace Hey {

    // constructor / destructor
    Application::Application()
        : Ng::Engine::Application(
              1080, 720,
              "SFML + ImGui = <3",
              sf::Style::Close,
              sf::ContextSettings(0, 0, 8, 1, 1, sf::ContextSettings::Attribute::Default, false)
          ) {

        // init RenderWindow context
        Ng::Engine::Application::GetContext().SetFramerateLimit(60u);
        Ng::Engine::Application::GetContext().SetVerticalSyncEnabled(true);
        Ng::Engine::Application::GetContext().SetKeyRepeatEnabled(false);

        // init ImGui
        ImGui::SFML::Init(m_RenderWindow);

        // init states
        Ng::Engine::Application::GetStateStack().Push(std::make_unique<Hey::InitState>());
    }

    Application::~Application() {
        ImGui::SFML::Shutdown();
    }

    // member methods
    void Application::OnPollEvent() {
        sf::Event event{};

        while (m_RenderWindow.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);

            if (event.type == sf::Event::Closed)
                Ng::Engine::Application::GetContext().SetVisible(false);
        }
    }

    void Application::OnUpdate() {
        // update ImGui::SFML
        ImGui::SFML::Update(m_RenderWindow, m_ElapsedTime);

        // update top state
        Ng::Engine::Application::GetStateStack().OnUpdate(m_ElapsedTime.asSeconds());
    }

    void Application::OnRender() {
//        m_RenderWindow.clear(m_Colors.Current);
        m_RenderWindow.clear();

        Ng::Engine::Application::GetStateStack().OnRender(m_RenderWindow);

        ImGui::SFML::Render(m_RenderWindow);
        m_RenderWindow.display();
    }

} // namespace Hey