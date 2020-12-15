#include "State.hpp"

namespace Ng::Engine {

    ///////////////////////////////////////////////////////////////////////
    /// class Context
    ///////////////////////////////////////////////////////////////////////
    // modifiers
    void State::Context::SetFramerateLimit(unsigned int framerateLimit) {
        m_RenderWindow->setFramerateLimit(m_FramerateLimit = framerateLimit);
    }

    void State::Context::SetVerticalSyncEnabled(bool verticalSyncEnabled) {
        m_RenderWindow->setVerticalSyncEnabled(m_VerticalSyncEnabled = verticalSyncEnabled);
    }

    void State::Context::SetVisible(bool visible) {
        m_RenderWindow->setVisible(m_Visible = visible);
    }

    void State::Context::SetKeyRepeatEnabled(bool keyRepeatEnabled) {
        m_RenderWindow->setKeyRepeatEnabled(m_KeyRepeatEnabled = keyRepeatEnabled);
    }

    ///////////////////////////////////////////////////////////////////////
    /// class State
    ///////////////////////////////////////////////////////////////////////
    // static protected accessors
    StateStack& State::GetStateStack() noexcept {
        static StateStack states;
        return states;
    }

    State::Context& State::GetContext() noexcept {
        static Context context;
        return context;
    }

} // namespace Ng::Engine