#pragma once

namespace Ng::Engine {

    class StateInterface {
    public:
        // constructor / destructor
        StateInterface() = default;
        virtual ~StateInterface() = default;

        // public methods
        virtual void OnMouseMoved(const sf::Event& event)          = 0;
        virtual void OnMouseButtonPressed(const sf::Event& event)  = 0;
        virtual void OnMouseButtonReleased(const sf::Event& event) = 0;
        virtual void OnKeyPressed(const sf::Event& event)          = 0;

        virtual void OnUpdate(float dt)                            = 0;
        virtual void OnRender(sf::RenderTarget& target) const      = 0;

    }; // class StateInterface

} // namespace Ng::Engine