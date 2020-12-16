#pragma once

#include <cstdint>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/ContextSettings.hpp>

#include "../States/State.hpp"

namespace Ng::Engine {

    class Application {
    public:
        // constructor / destructor
        Application(unsigned int width, unsigned int height,
                    const char* title,
                    uint32_t style = sf::Style::Default,
                    const sf::ContextSettings& contextSettings = sf::ContextSettings());
        virtual ~Application() = default;

        // public methods
        void Run();

    public:
        // subsidiaries static methods
        static inline State::Context& GetContext() { return State::GetContext(); }
        static inline StateStack& GetStateStack() { return State::GetStateStack(); }

        // subsidiaries methods
        virtual void OnPollEvent();
        virtual void OnUpdate() = 0;
        virtual void OnRender() = 0;

        // subsidiaries data
        sf::RenderWindow m_RenderWindow;
        sf::Time         m_ElapsedTime;
        sf::Clock        m_Clock;

    private:
        // member methods
        void OnUpdateElapsedTime();

    }; // Application

} // namespace Ng::Engine