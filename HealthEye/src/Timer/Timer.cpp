#include "Timer.hpp"

#include <iostream>
#include <chrono>
#include <thread>

namespace Hey {

    // constructor / destructor
    Timer::Timer(std::chrono::seconds seconds)
        : m_CurrentTime(0),
          m_EndTime(seconds) {

    }

    Timer::~Timer() {
//        thread.join();
    }

    // public methods
    void Timer::Start() {
        namespace chr = std::chrono;
        while (true) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            ++m_CurrentTime;

            int64_t remainder = chr::duration_cast<chr::seconds>(m_EndTime - m_CurrentTime).count();

            if (remainder == 2)
                std::cout << '\7' << std::endl;

            if (remainder == 0)
                return;
        }
    }

    void Timer::Reset() {
        m_CurrentTime = std::chrono::seconds(0);
    }

} // namespace Hey