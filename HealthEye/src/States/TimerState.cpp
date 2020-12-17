#include "TimerState.hpp"

#include <iostream>

#include <imgui.h>

namespace Hey {

    // constructor / destructor
    TimerState::TimerState() {

//        m_Timers[TimerType::Work]  = std::move(Timer(std::chrono::seconds(20)));
//        m_Timers[TimerType::Sleep] = Timer(std::chrono::seconds(5));

        m_Timers[TimerType::Work].SetEndTime(std::chrono::seconds(20));
//        m_Timers[TimerType::Sleep].SetEndTime(std::chrono::seconds(5));

        m_Timers[TimerType::Work].Start();

//        for (int i = 0; i < 4; ++i) {
//            m_Timers[TimerType::Work].Start();
////                m_Timers[TimerType::Sleep].Start();
//
//            m_Timers[TimerType::Work].Reset();
////                m_Timers[TimerType::Sleep].Reset();
//        }
    }

    TimerState::~TimerState() {
        std::cout << "destructor TimerState" << std::endl;
    }

    // public methods
    void TimerState::OnUpdate(float dt) {
        ImGui::Begin("Timer");

        if (ImGui::Button("<"))
            Ng::Engine::State::GetStateStack().Pop();
        ImGui::SameLine();

        if (ImGui::Button("Hide Window"))
            Ng::Engine::State::GetContext().SetVisible(false);
        ImGui::SameLine();

        if (ImGui::Button("Kill Application :("))
            Ng::Engine::State::GetContext().GetRenderWindow()->close();
        ImGui::SameLine();

        ImGui::Separator();

        ImGui::ProgressBar(
            static_cast<float>(m_Timers[TimerType::Work].GetCurrentTime().count()) /
            static_cast<float>(m_Timers[TimerType::Work].GetEndTime().count())
        );

        ImGui::ProgressBar(
            static_cast<float>(m_Timers[TimerType::Sleep].GetCurrentTime().count()) /
            static_cast<float>(m_Timers[TimerType::Sleep].GetEndTime().count())
        );

        ImGui::End();
    }

    void TimerState::OnRender(sf::RenderTarget& target) const {

    }

} // namespace Hey