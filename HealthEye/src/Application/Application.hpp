#pragma once

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

        // enums
        enum class ShortcutType : short { Visible = 0, Kill };

        // aliases
        using ShortcutContainer = std::unordered_map<ShortcutType, Ng::Engine::Shortcut>;

        // member data
        ShortcutContainer m_Shortcuts;

    }; // class Application

} // namespace Hey