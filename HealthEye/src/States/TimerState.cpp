#include "TimerState.hpp"

#include <imgui.h>

namespace Hey {

    // constructor / destructor
    TimerState::TimerState()
        : m_Timer(std::chrono::seconds(10)) {


        m_Thread = std::move(std::thread([&]() {
            for (int i = 0; i < 4; ++i) {
                m_Timer.Start();
                m_Timer.Reset();
            }
        }));
    }

    TimerState::~TimerState() {
        m_Thread.detach();
    }

    // public methods
    void TimerState::OnUpdate(float dt) {
        ImGui::Begin("Timer");

        ImGui::ProgressBar(
            static_cast<float>(m_Timer.GetCurrentTime().count()) /
            static_cast<float>(m_Timer.GetEndTime().count())
        );

        ImGui::NewLine();

        if (ImGui::Button("Hide Window"))
            Ng::Engine::State::GetContext().SetVisible(false);

        if (ImGui::Button("Kill Application :("))
            Ng::Engine::State::GetContext().GetRenderWindow()->close();

        ImGui::End();
    }

    void TimerState::OnRender(sf::RenderTarget& target) const {

    }

} // namespace Hey