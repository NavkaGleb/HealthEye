#include "TimerState.hpp"

#include <iostream>
#include <windows.h>

#include <imgui.h>

namespace Hey {

    // constructor / destructor
    TimerState::TimerState() {

        m_Timers[TimerType::Work]  = Timer(std::chrono::seconds(20));
        m_Timers[TimerType::Sleep] = Timer(std::chrono::seconds(5));

//        m_Timers[TimerType::Work].SetEndTime(std::chrono::seconds(20));
//        m_Timers[TimerType::Sleep].SetEndTime(std::chrono::seconds(5));

        m_Thread = std::move(std::thread([&]() {
//            for (int i = 0; i < 4; ++i) {
//            m_Timers[TimerType::Work].Start();
//                m_Timers[TimerType::Sleep].Start();

//            m_Timers[TimerType::Work].Reset();
//                m_Timers[TimerType::Sleep].Reset();
//            }
        }));
    }

    TimerState::~TimerState() {
        m_Thread.detach();
        std::cout << "destructor TimerState" << std::endl;
    }

    // public methods
    void TimerState::OnKeyPressed(const sf::Event& event) {
        if (event.key.code == sf::Keyboard::P) {
            std::cout << "pressed P" << std::endl;
            m_Timers[TimerType::Work].Pause();
        }

        if (event.key.code == sf::Keyboard::R) {
            std::cout << "pressed R" << std::endl;
            m_Timers[TimerType::Work].Resume();
        }

        if (event.key.code == sf::Keyboard::B) {
            std::cout << "pressed B" << std::endl;
            BlockInput(true);
            std::this_thread::sleep_for(std::chrono::seconds(10));
//            Sleep(10000);
//            BlockInput(false);
            BlockInput(false);
        }

        if (event.key.code == sf::Keyboard::V) {
            std::cout << "pressed V" << std::endl;
            BlockInput(false);
        }
    }

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
            static_cast<float>(m_Timers[TimerType::Work].GetTime().count()) /
            static_cast<float>(m_Timers[TimerType::Work].GetEndTime().count())
        );

        ImGui::ProgressBar(
            static_cast<float>(m_Timers[TimerType::Sleep].GetTime().count()) /
            static_cast<float>(m_Timers[TimerType::Sleep].GetEndTime().count())
        );

        ImGui::End();
    }

    void TimerState::OnRender(sf::RenderTarget& target) const {

    }

} // namespace Hey