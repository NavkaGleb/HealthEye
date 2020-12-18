#pragma once

#include <thread>

#include <imgui.h>

#include <Engine/States/State.hpp>

#include "Timer/Timer.hpp"

namespace Hey {

    class TimerState : public Ng::Engine::State {
    public:
        // constructor / destructor
        TimerState();
        ~TimerState() override;

        // public methods
        void OnKeyPressed(const sf::Event& event) override;

        void OnUpdate(float dt) override;
        void OnRender(sf::RenderTarget& target) const override;

    private:
        // member methods
        void InitFonts();
        void StartTimers();
        void ResetTimers();

        // enums
        enum class TimerType : short { Work = 0, Sleep };

        // aliases
        using TimerContainer = std::unordered_map<TimerType, Timer>;

        // member data
        TimerContainer m_Timers;
        std::thread    m_Thread;
        ImFont*        m_Font;

    }; // class TimerState

} // namespace Hey