#pragma once

#include <chrono>
#include <thread>

namespace Hey {

    ///////////////////////////////////////////////////////////////////////
    /// Header
    ///////////////////////////////////////////////////////////////////////
    class Timer {
    public:
        // constructor / destructor
        Timer();
        explicit Timer(std::chrono::seconds endTime);
        ~Timer();

        // accessors
        [[nodiscard]] inline const std::chrono::seconds& GetTime() const { return m_CurrentTime; }
        [[nodiscard]] inline const std::chrono::seconds& GetEndTime() const { return m_EndTime; }
        [[nodiscard]] inline bool IsEnded() const { return m_CurrentTime == m_EndTime; }

        // modifiers
        void SetEndTime(std::chrono::seconds endTime);

        // public methods
        void Start();
        void Pause();
        void Resume();
        void Reset();

    private:
        // member methods

        // aliases

        // member data
        std::chrono::seconds m_CurrentTime;
        std::chrono::seconds m_EndTime;
        bool                 m_IsPaused;

    }; // class Timer

    ///////////////////////////////////////////////////////////////////////
    /// Source
    ///////////////////////////////////////////////////////////////////////


} // namespace Hey