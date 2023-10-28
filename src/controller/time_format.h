#include <chrono>
#include <ctime>
#include <iomanip>
#include <string>

int64_t getCurrentWIBTimestamp() {
    int64_t currentTime = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch()
    ).count();

    return currentTime;
}