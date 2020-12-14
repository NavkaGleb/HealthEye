#include "Shortcut.hpp"

namespace Hey {

    // constructor / destructor
    Shortcut::Shortcut()
        : m_IsActive(false) {}

    Shortcut::Shortcut(const std::initializer_list<sf::Keyboard::Key>& keys)
        : Shortcut() {

        for (const auto& key : keys)
            m_Keys[key] = false;
    }

    // public methods
    bool Shortcut::IsActive() {
        if (!m_IsActive && std::ranges::all_of(
                m_Keys.begin(),
                m_Keys.end(),
                [](const std::pair<sf::Keyboard::Key, bool>& pair) { return pair.second; }
            )) {
            return m_IsActive = true;
        }

        return false;
    }

    void Shortcut::OnUpdate() {
        for (auto& [key, active] : m_Keys) {
            if (active != sf::Keyboard::isKeyPressed(key)) {
                active = sf::Keyboard::isKeyPressed(key);
                m_IsActive = false;
            }
        }
    }

} // namespace Hey