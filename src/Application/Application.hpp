#pragma once

#include <chrono>
#include <windows.h>

#include <SFML/Graphics/RenderWindow.hpp>

#include <imgui.h>

#include "Shortcut.hpp"

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

        // enums
        enum class ShortcutType : short { Visible = 0, Kill };

        // aliases
        using ShortcutContainer = std::unordered_map<ShortcutType, Shortcut>;

        // member data
        sf::RenderWindow m_Window;
        sf::Color        m_BackgroundColor;
        float            m_Colors[3];
        ImFont*          m_Font;
        std::chrono::time_point<std::chrono::steady_clock> m_Start;
        std::chrono::time_point<std::chrono::steady_clock> m_End;
        sf::Clock        m_Clock;
        ShortcutContainer m_Shortcuts;
        bool             m_Visible;

    }; // class Application

} // namespace Hey