#pragma once

#include <array>

#include <imgui.h>

#include <Engine/System/Shortcut.hpp>
#include <Engine/States/State.hpp>

namespace Hey {

    class InitState : public Ng::Engine::State {
    public:
        // constructor / destructor
        InitState();
        ~InitState() override;

        // public methods
        void OnUpdate(float dt) override;
        void OnRender(sf::RenderTarget& target) const override;

    private:
        // member methods
        void InitFonts();

        // enums
        enum class RangeType    : short { WorkTime = 0, SleepTime };

        // inner members
        template <typename RangeType, typename Pointer, std::size_t size>
        struct Range {
            std::array<RangeType, size> Data;
            Pointer                     Current;

        }; // struct Period

        // member data
        Range<float, sf::Color, 3> m_Colors;
        ImFont*                    m_Font;
        Range<const char*, int, 4> m_WorkTime;
        Range<const char*, int, 4> m_SleepTime;

    }; // class InitState

} // namespace Hey