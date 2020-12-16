#pragma once

#include <array>
#include <windows.h>

#include <SFML/Graphics/RenderWindow.hpp>

#include <imgui.h>

#include "Timer/Timer.hpp"

#include <Engine/Application/Application.hpp>
#include <Engine/System/Shortcut.hpp>

namespace Hey {

    class Application : public Ng::Engine::Application {
    public:
        // constructor / destructor
        Application();
        ~Application() override;

    private:
        // member methods
        void OnPollEvent() override;
        void OnUpdate() override;
        void OnRender() override;

    }; // class Application

} // namespace Hey