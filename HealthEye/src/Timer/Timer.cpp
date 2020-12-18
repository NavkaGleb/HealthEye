#include "Timer.hpp"

#include <iostream>
#include <chrono>
#include <windows.h>

namespace Hey {

    // constructor / destructor
    Timer::Timer()
        : m_CurrentTime(0),
          m_EndTime(0),
          m_IsPaused(false),
          m_IsDestroyed(false) {}

    Timer::Timer(std::chrono::seconds endTime)
        : m_CurrentTime(0),
          m_EndTime(endTime),
          m_IsPaused(false),
          m_IsDestroyed(false) {

    }

    Timer::~Timer() {
        std::cout << "destructor Timer" << std::endl;
        m_IsDestroyed = true;
    }

    // modifiers
    void Timer::SetEndTime(std::chrono::seconds endTime) {
        m_EndTime = endTime;
    }

    // public methods
    void Timer::Start() {
        namespace chr = std::chrono;

        while ((m_EndTime - m_CurrentTime).count() > 0) {
            if (m_IsDestroyed)
                return;

            std::this_thread::sleep_for(std::chrono::seconds(1));

            if (m_IsPaused)
                continue;

            ++m_CurrentTime;

            if ((m_EndTime - m_CurrentTime).count() == 2)
                Beep(500, 300);
        }
    }

    void Timer::Pause() {
        m_IsPaused = true;
    }

    void Timer::Resume() {
        m_IsPaused = false;
    }

    void Timer::Reset() {
        m_CurrentTime = std::chrono::seconds(0);
    }

    void Timer::Destroy() {
        m_IsDestroyed = true;
    }

} // namespace Hey