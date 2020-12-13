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
        void InitWindow(unsigned int width, unsigned int height, const char* title);
        void InitFonts();
        void InitShortcuts();

        void HideWindow();
        void ShowWindow();
        void Kill();

        void OnPollEvent();
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
        sf::Clock        m_Clock;
        ShortcutContainer m_Shortcuts;
        bool             m_Visible;

    }; // class Application

} // namespace Hey