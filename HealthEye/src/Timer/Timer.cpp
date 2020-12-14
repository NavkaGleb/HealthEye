#include "Timer.hpp"

#include <iostream>
#include <chrono>
#include <thread>
#include <windows.h>

namespace Hey {

    // constructor / destructor
    Timer::Timer(std::chrono::seconds seconds)
        : m_Period(seconds) {

    }

    // public methods
    void Timer::Start() {
        namespace chr = std::chrono;

        for (chr::seconds seconds(0); true; ++seconds) {
            std::this_thread::sleep_for(std::chrono::seconds(1));

            int64_t remainder = chr::duration_cast<chr::seconds>(m_Period - seconds).count();

            if (remainder == 2)
                std::cout << '\7' << std::endl;

            if (remainder == 0)
                return;
        }
    }

    void Timer::Reset() {

    }

} // namespace Hey