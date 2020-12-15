#pragma once

#include <stack>
#include <memory>

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "StateInterface.hpp"

namespace Ng::Engine {

    class State;

    class StateStack : public StateInterface {
    public:
        // alias
        using StatePtr = std::unique_ptr<State>;

        // constructor / destructor
        StateStack() = default;
        ~StateStack() override = default;

        // public methods
        void Push(StatePtr&& state);
        void Pop();

        void OnMouseMoved(const sf::Event& event) override;
        void OnMouseButtonPressed(const sf::Event& event) override;
        void OnMouseButtonReleased(const sf::Event& event) override;
        void OnKeyPressed(const sf::Event& event) override;

        void OnUpdate(const float& dt) override;
        void OnRender(sf::RenderTarget& target) const override;

    private:
        // member data
        std::stack<StatePtr> m_States;

    }; // class StackState

} // namespace Ng::Engine