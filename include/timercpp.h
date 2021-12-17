#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>

class Timer {
	std::atomic<bool> active{true};
	
    public:
        void setTimeout(void (*function)(), int delay);
        void setInterval(void (*function)(), int interval);
        void stop();

};

void Timer::setTimeout(void (*function)(), int delay) {
    active = true;
    std::thread t([=]() {
        if(!active.load()) return;
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
        if(!active.load()) return;
        function();
    });
    t.detach();
}



void Timer::stop() {
    active = false;
}
