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
        Timer(Timer&& other) noexcept;
        ~Timer();

        // accessors
        [[nodiscard]] inline const std::chrono::seconds& GetCurrentTime() const { return m_CurrentTime; }
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
        std::chrono::seconds m_CurrentTime{};
        std::chrono::seconds m_EndTime{};
        bool                 m_IsPaused;
        std::thread          m_Thread;

    }; // class Timer

    ///////////////////////////////////////////////////////////////////////
    /// Source
    ///////////////////////////////////////////////////////////////////////


} // namespace Hey