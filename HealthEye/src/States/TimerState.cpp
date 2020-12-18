#include "TimerState.hpp"

#include <iostream>
#include <windows.h>

#include <imgui-SFML.h>

namespace Hey {

    // constructor / destructor
    TimerState::TimerState()
        : m_Font(nullptr) {
        std::cout << "constructor TimerState" << std::endl;
        m_Timers[TimerType::Work]  = Timer(std::chrono::seconds(10));
        m_Timers[TimerType::Sleep] = Timer(std::chrono::seconds(5));

        std::cout << m_Timers[TimerType::Work].GetEndTime().count() << std::endl;
        std::cout << m_Timers[TimerType::Sleep].GetEndTime().count() << std::endl;

//        Ng::Engine::State::GetContext().SetVisible(false);

        InitFonts();
        StartTimers();
    }

    TimerState::~TimerState() {
        for (auto& [type, timer] : m_Timers)
            timer.Destroy();

        m_Thread.join();

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
            for (int i = 0; i < 10; ++i) {
                std::this_thread::sleep_for(std::chrono::seconds(1));
                std::cout << "i = " << i << std::endl;
            }
            BlockInput(false);
        }

        if (event.key.code == sf::Keyboard::V) {
            std::cout << "pressed V" << std::endl;
            BlockInput(false);
        }
    }

    void TimerState::OnUpdate(float dt) {
        if (m_Timers[TimerType::Sleep].IsEnded()) {
            m_Thread.join();

            ResetTimers();
            StartTimers();
        }

        ImGui::PushFont(m_Font);
        ImGui::Begin("Timer");

//        if (ImGui::ArrowButton("Back", ImGuiDir_::ImGuiDir_Left)) {
//            Ng::Engine::State::GetStateStack().Pop();
//            ImGui::End();
//            return;
//        }
//        ImGui::SameLine();

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

        if (ImGui::Button("Pause Timers"))
            for (auto& [type, timer] : m_Timers)
                timer.Pause();

        ImGui::SameLine();

        if (ImGui::Button("Resume Timers"))
            for (auto& [type, timer] : m_Timers)
                timer.Resume();

        ImGui::SameLine();

        if (ImGui::Button("Go to init state"))
            Ng::Engine::State::GetStateStack().Pop();

        ImGui::End();
        ImGui::PopFont();
    }

    void TimerState::OnRender(sf::RenderTarget& target) const {

    }

    // member methods
    void TimerState::InitFonts() {
        ImGuiIO& io = ImGui::GetIO();
        m_Font = io.Fonts->AddFontFromFileTTF("../../HealthEye/media/Fonts/Baloo2-Medium.ttf", 30.0f);

        ImGui::SFML::UpdateFontTexture();
    }

    void TimerState::StartTimers() {
        m_Thread = std::move(std::thread([&]() {
            m_Timers[TimerType::Work].Start();
            Ng::Engine::State::GetContext().SetVisible(true);

            BlockInput(true);
            m_Timers[TimerType::Sleep].Start();
            BlockInput(false);
            Ng::Engine::State::GetContext().SetVisible(false);
        }));
    }

    void TimerState::ResetTimers() {
        for (auto& [type, timer] : m_Timers)
            timer.Reset();
    }

} // namespace Hey