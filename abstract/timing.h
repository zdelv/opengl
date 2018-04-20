#include <iostream>
#include <chrono>

using Time = std::chrono::high_resolution_clock;
using ms = std::chrono::milliseconds;
using namespace std::literals::chrono_literals;

class TimeBench {

    private:
        std::chrono::time_point<std::chrono::steady_clock> start, end;
        std::chrono::time_point<std::chrono::steady_clock> lastCall;
        std::chrono::duration<float> duration;
        float ms;

    public:
        TimeBench()
        {
            ms = 0;
            start = Time::now();
            lastCall = Time::now();
            std::cout << "TIMER STARTED" << std::endl;
        }

        ~TimeBench()
        {
            end = Time::now();
            std::cout << "TIMER STOPPED" << std::endl;
            duration = end - start;
            ms = duration.count() * 1000.0f;
            std::cout << "TOTAL TIME: " << ms << " ms" << std::endl;
        }

        void call() 
        {
            duration = Time::now() - lastCall;
            ms = duration.count() * 1000.0f;
            lastCall = Time::now();
            std::cout << ms << std::endl;
        };

};
