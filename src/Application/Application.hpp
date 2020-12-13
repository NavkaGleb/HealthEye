#pragma once

#include <windows.h>

#include <SFML/Graphics/RenderWindow.hpp>

namespace Hey {

    class Application {
    public:
        // constructor / destructor
        Application(unsigned int width, unsigned int height, const char* title);
        virtual ~Application();

        // public methods
        void Run();

    private:
        // member methods
        void OpenWindow();
        void CloseWindow();
        void OnUpdate();
        void OnRender();

        // member data
        sf::VideoMode    m_VideoMode;
        const char*      m_Title;
        sf::RenderWindow m_SFMLWindow;
        HWND__*          m_WINWindow;

    }; // class Application

} // namespace Hey