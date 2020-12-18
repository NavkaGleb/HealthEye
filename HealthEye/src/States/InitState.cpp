#include "InitState.hpp"

#include <imgui-SFML.h>

#include <Engine/Application/Application.hpp>

#include "States/TimerState.hpp"

namespace Hey {

    // constructor / destructor
    InitState::InitState()
        : m_Colors({ 0.0f, 0.0f, 0.0f }),
          m_Font(nullptr),
          m_WorkTime{ { "25", "30", "35", "40" }, 0 },
          m_SleepTime{ { "2", "3", "4", "5" }, 0 } {

        InitFonts();
    }

    InitState::~InitState() {

    }

    // public methods
    void InitState::OnUpdate(float dt) {
        // begin ImGui
        ImGui::PushFont(m_Font);
        ImGui::SetNextWindowPos(sf::Vector2f(0.0f, 0.0f));
        ImGui::SetNextWindowSize(sf::Vector2f(700.0f, 500.0f));
        ImGui::SetNextWindowBgAlpha(0.7f);
        ImGui::Begin(
            "m_RenderWindow",
            nullptr,
            ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse
        );

        if (ImGui::ColorEdit3("Background color", m_Colors.Data.begin())) {
            m_Colors.Current.r = static_cast<sf::Uint8>(m_Colors.Data[0] * 255.0f);
            m_Colors.Current.g = static_cast<sf::Uint8>(m_Colors.Data[1] * 255.0f);
            m_Colors.Current.b = static_cast<sf::Uint8>(m_Colors.Data[2] * 255.0f);
        }

        ImGui::Combo("Work Time",       &m_WorkTime.Current,      m_WorkTime.Data.cbegin(),      m_WorkTime.Data.size()     );
        ImGui::Combo("Sleep Time",      &m_SleepTime.Current,     m_SleepTime.Data.cbegin(),     m_SleepTime.Data.size()    );

        if (ImGui::Button("Timer State")) {
            ImGui::End();
            ImGui::PopFont();
            ImGui::EndFrame();

            Ng::Engine::State::GetStateStack().Push(std::make_unique<Hey::TimerState>());

            return;
        }

        ImGui::NewLine();

        if (ImGui::Button("Hide Window"))
            Ng::Engine::State::GetContext().SetVisible(false);

        if (ImGui::Button("Kill Application :("))
            Ng::Engine::State::GetContext().GetRenderWindow()->close();

        ImGui::End();
        ImGui::PopFont();
    }

    void InitState::OnRender(sf::RenderTarget& target) const {
        Ng::Engine::State::GetContext().GetRenderWindow()->clear(m_Colors.Current);
    }

    // member methods
    void InitState::InitFonts() {
        ImGuiIO& io = ImGui::GetIO();
        m_Font = io.Fonts->AddFontFromFileTTF("../../HealthEye/media/Fonts/Baloo2-Medium.ttf", 30.0f);

        ImGui::SFML::UpdateFontTexture();
    }

} // namespace Hey