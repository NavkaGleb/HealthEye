#include "State.hpp"

namespace Ng::Engine {

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