#pragma once

#include <array>
#include <windows.h>

#include <SFML/Graphics/RenderWindow.hpp>

#include <imgui.h>

#include "Timer/Timer.hpp"

#include <Engine/Shortcut.hpp>
#include <Engine/Application.hpp>

namespace Hey {

    class Application : public ::Ng::Engine::Application {
    public:
        // constructor / destructor
        Application(unsigned int width, unsigned int height, const char* title);
        ~Application() override = default;

    private:
        // member methods
        void InitWindow();
        void InitFonts();
        void InitShortcuts();

        void HideWindow();
        void ShowWindow();
        void Kill();

        void OnPollEvent() override;
        void OnUpdate() override;
        void OnRender() override;

        // enums
        enum class ShortcutType : short { Visible = 0, Kill };

        // inner members
        template <typename RangeType, typename Pointer, std::size_t size>
        struct Range {
            std::array<RangeType, size> Data;
            Pointer                     Current;
        }; // struct Period


        // aliases
        using ShortcutContainer = std::unordered_map<ShortcutType, Shortcut>;

        // member data
        Range<float, sf::Color, 3>  m_Colors;
        ImFont*          m_Font;
        ShortcutContainer m_Shortcuts;
        bool             m_Visible;
        Range<const char*, int, 4>        m_WorkTime;
        Range<const char*, int, 4>        m_SleepTime;
        Range<const char*, int, 2>        m_BigSleepTime;
        Range<const char*, int, 2>        m_WorkTimeCount;
        Timer            m_Timer;

    }; // class Application

} // namespace Hey