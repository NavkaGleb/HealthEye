#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

#include "StateInterface.hpp"
#include "StateStack.hpp"

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

    private:
        // inner structs
        struct Context {
            // data
            sf::RenderWindow* RenderWindow        = nullptr;
            unsigned          FramerateLimit      = 60;
            bool              VerticalSyncEnabled = true;
            bool              Visible             = true;
            bool              KeyRepeatEnabled    = true;
        };

    protected:
        // static protected accessors
        static StateStack& GetStateStack() noexcept;
        static Context& GetContext() noexcept;

    }; // class State

} // namespace Ng::Engine