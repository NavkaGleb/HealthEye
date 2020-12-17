#include "Timer.hpp"

#include <iostream>
#include <chrono>
#include <thread>

namespace Hey {

    // constructor / destructor
    Timer::Timer()
        : m_CurrentTime(0),
          m_EndTime(0),
          m_IsPaused(false) {

    }

    Timer::Timer(Timer&& other) noexcept {
        m_CurrentTime = other.m_CurrentTime;
        m_EndTime     = other.m_EndTime;
        m_IsPaused    = other.m_IsPaused;
        m_Thread      = std::move(other.m_Thread);
    }

    Timer::~Timer() {
        m_Thread.join();
        std::cout << "destructor Timer" << std::endl;
    }

    // modifiers
    void Timer::SetEndTime(std::chrono::seconds endTime) {
        m_EndTime = endTime;
    }

    // public methods
    void Timer::Start() {
        namespace chr = std::chrono;

        m_Thread = std::move(std::thread([&]() {
            while (true) {
                std::this_thread::sleep_for(std::chrono::seconds(1));

                if (m_IsPaused)
                    return;

                ++m_CurrentTime;

                int64_t remainder = chr::duration_cast<chr::seconds>(m_EndTime - m_CurrentTime).count();

                if (remainder == 2)
                    std::cout << '\7' << std::endl;

                if (remainder == 0)
                    return;
            }
        }));
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