#include "StateStack.hpp"

#include "../../../Engine/include/Engine/States/State.hpp"

namespace Ng::Engine {

    // public methods
    void StateStack::Push(StatePtr&& state) {
        m_States.push(std::move(state));
    }

    void StateStack::Pop() {
        m_States.pop();
    }

    void StateStack::OnMouseMoved(const sf::Event& event) {
        if (!m_States.empty())
            m_States.top()->OnMouseMoved(event);
    }

    void StateStack::OnMouseButtonPressed(const sf::Event& event) {
        if (!m_States.empty())
            m_States.top()->OnMouseButtonPressed(event);
    }

    void StateStack::OnMouseButtonReleased(const sf::Event& event) {
        if (!m_States.empty())
            m_States.top()->OnMouseButtonReleased(event);
    }

    void StateStack::OnKeyPressed(const sf::Event& event) {
        if (!m_States.empty())
            m_States.top()->OnKeyPressed(event);
    }

    void StateStack::OnUpdate(float dt) {
        if (!m_States.empty())
            m_States.top()->OnUpdate(dt);
    }

    void StateStack::OnRender(sf::RenderTarget& target) const {
        if (!m_States.empty())
            m_States.top()->OnRender(target);
    }

} // namespace Ng::Engine