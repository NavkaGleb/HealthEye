#pragma once

#include <array>

#include <imgui.h>

#include <Engine/System/Shortcut.hpp>
#include <Engine/States/State.hpp>

#include "Timer/Timer.hpp"

namespace Hey {

    class InitState : public Ng::Engine::State {
    public:
        // constructor / destructor
        InitState();
        ~InitState() override;

        // public methods
        void OnUpdate(float dt) override;
        void OnRender(sf::RenderTarget& target) const override;

    private:
        // member methods
        void InitFonts();
        void InitShortcuts();

        // enums
        enum class ShortcutType : short { Visible = 0, Kill };
        enum class RangeType    : short { WorkTime = 0, SleepTime };

        // inner members
        template <typename RangeType, typename Pointer, std::size_t size>
        struct Range {
            std::array<RangeType, size> Data;
            Pointer                     Current;

        }; // struct Period

        // aliases
        using ShortcutContainer   = std::unordered_map<ShortcutType, Ng::Engine::Shortcut>;
        using TimerRangeContainer = std::unordered_map<RangeType, Range<const char*, int, 4>>;

        // member data
        Range<float, sf::Color, 3> m_Colors;
        ImFont*                    m_Font;
        ShortcutContainer          m_Shortcuts;
        Range<const char*, int, 4> m_WorkTime;
        Range<const char*, int, 4> m_SleepTime;
        Timer                      m_Timer;

    }; // class InitState

} // namespace Hey