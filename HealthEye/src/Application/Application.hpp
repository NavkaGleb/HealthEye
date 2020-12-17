#pragma once

#include <Engine/Application/Application.hpp>

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