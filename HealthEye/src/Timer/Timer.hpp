#pragma once

#include <chrono>

namespace Hey {

    ///////////////////////////////////////////////////////////////////////
    /// Header
    ///////////////////////////////////////////////////////////////////////
    class Timer {
    public:
        // constructor / destructor
        explicit Timer(std::chrono::seconds seconds);
        ~Timer();

        // accessors
        [[nodiscard]] inline const std::chrono::seconds& GetCurrentTime() const { return m_CurrentTime; }
        [[nodiscard]] inline const std::chrono::seconds& GetEndTime() const { return m_EndTime; }
        [[nodiscard]] inline bool IsEnded() const { return m_CurrentTime == m_EndTime; }

        // public methods
        void Start();
        void Reset();

    private:
        // member methods

        // aliases

        // member data
        std::chrono::seconds m_CurrentTime;
        std::chrono::seconds m_EndTime;

    }; // class Timer

    ///////////////////////////////////////////////////////////////////////
    /// Source
    ///////////////////////////////////////////////////////////////////////


} // namespace Hey