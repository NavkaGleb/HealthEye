#include "Timer.hpp"

#include <iostream>
#include <chrono>
#include <thread>

namespace Hey {

    // constructor / destructor
    Timer::Timer()
        : m_CurrentTime(0),
          m_EndTime(0),
          m_IsPaused(false) {}

    Timer::Timer(std::chrono::seconds endTime)
        : m_CurrentTime(0),
          m_EndTime(endTime),
          m_IsPaused(false) {

    }

    Timer::~Timer() {
        std::cout << "destructor Timer" << std::endl;
    }

    // modifiers
    void Timer::SetEndTime(std::chrono::seconds endTime) {
        m_EndTime = endTime;
    }

    // public methods
    void Timer::Start() {
        namespace chr = std::chrono;

        while (true) {
            std::this_thread::sleep_for(std::chrono::seconds(1));

            if (m_IsPaused)
                continue;

            ++m_CurrentTime;

            std::cout << "CurrentTime = " << m_CurrentTime.count() << std::endl;

            int64_t remainder = chr::duration_cast<chr::seconds>(m_EndTime - m_CurrentTime).count();

            if (remainder == 2)
                std::cout << '\7' << std::endl;

            if (remainder == 0)
                return;
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

} // namespace Hey