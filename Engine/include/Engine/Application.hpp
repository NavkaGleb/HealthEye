#pragma once

#include <cstdint>

#include <SFML/Graphics/RenderWindow.hpp>

namespace Ng::Engine {

    class Application {
    public:
        // constructor / destructor
        Application(unsigned int width, unsigned int height, const char* title, uint32_t style = sf::Style::Default);
        virtual ~Application();

        // public methods
        void Run();

    protected:
        // subsidiaries methods
        virtual void OnPollEvent();
        virtual void OnUpdate() = 0;
        virtual void OnRender() = 0;

        // subsidiaries data
        sf::RenderWindow m_RenderWindow;
        sf::Time         m_ElapsedTime;

    private:
        // member methods
        void OnImGuiUpdate();

        // member data
        sf::Clock        m_Clock;

    }; // Application

} // namespace Ng::Engine