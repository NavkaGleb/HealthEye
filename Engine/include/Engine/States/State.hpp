#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

#include "../../../src/States/StateInterface.hpp"
#include "../../../src/States/StateStack.hpp"

namespace Ng::Engine {

    class State : public StateInterface {
    public:
        // constructor / destructor
        State() = default;
        ~State() override = default;

        // public methods
        void OnMouseMoved(const sf::Event& event) override {};
        void OnMouseButtonPressed(const sf::Event& event) override {};
        void OnMouseButtonReleased(const sf::Event& event) override {};
        void OnKeyPressed(const sf::Event& event) override {};

        void OnUpdate(const float& dt) override                = 0;
        void OnRender(sf::RenderTarget& target) const override = 0;

        // friends
        friend class Application;

    protected:
        // inner structs
        class Context {
        public:
            // accessors
            [[nodiscard]] inline const sf::RenderWindow* GetRenderWindow() const { return m_RenderWindow; }
            [[nodiscard]] inline unsigned int GetFramerateLimit() const { return m_FramerateLimit; }
            [[nodiscard]] inline bool GetVerticalSyncEnabled() const { return m_VerticalSyncEnabled; }
            [[nodiscard]] inline bool GetVisible() const { return m_Visible; }
            [[nodiscard]] inline bool GetKeyRepeatEnabled() const { return m_KeyRepeatEnabled; }

            // modifiers
            void SetFramerateLimit(unsigned int framerateLimit);
            void SetVerticalSyncEnabled(bool verticalSyncEnabled);
            void SetVisible(bool visible);
            void SetKeyRepeatEnabled(bool keyRepeatEnabled);

            // friends
            friend class Application;

        private:
            // member data
            sf::RenderWindow* m_RenderWindow        = nullptr;
            unsigned          m_FramerateLimit      = 60;
            bool              m_VerticalSyncEnabled = true;
            bool              m_Visible             = true;
            bool              m_KeyRepeatEnabled    = true;

        }; // class Context

        // static protected accessors
        static StateStack& GetStateStack() noexcept;
        static Context& GetContext() noexcept;

    }; // class State

} // namespace Ng::Engine