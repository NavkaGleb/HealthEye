#pragma once

#include <initializer_list>
#include <unordered_map>

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

namespace Hey {

    class Shortcut {
    public:
        // constructor / destructor
        Shortcut();
        Shortcut(const std::initializer_list<sf::Keyboard::Key>& keys);

        // public methods
        bool IsActive();
        void OnUpdate();

    private:
        // member data
        std::unordered_map<sf::Keyboard::Key, bool> m_Keys;
        bool                                        m_IsActive;

    };

} // namespace Hey