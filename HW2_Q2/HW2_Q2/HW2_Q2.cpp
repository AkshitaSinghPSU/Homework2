#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <mutex>

const int NUM_ROBOTS = 5;
const int NUM_TOOLS = 5;
const int TASK_DURATION = 5;

std::vector<bool> tools(NUM_TOOLS, true);
std::mutex mutex;

void performTask(int robotId, int left_tool_index, int right_tool_index) {
    bool left_tool_acquired = false;
    bool right_tool_acquired = false;

    while (!left_tool_acquired || !right_tool_acquired) {
        std::unique_lock<std::mutex> lock(mutex);

        if (tools[left_tool_index] && tools[right_tool_index]) {
            tools[left_tool_index] = false;
            tools[right_tool_index] = false;
            left_tool_acquired = true;
            right_tool_acquired = true;
            lock.unlock();

            std::cout << "Robot " << robotId << " acquired tools and starts performing a task." << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(TASK_DURATION));
            std::cout << "Robot " << robotId << " finished the task and returning the tools." << std::endl;

            lock.lock();
            tools[left_tool_index] = true;
            tools[right_tool_index] = true;
        }
    }
}

int main() {
    // Start threads for each robot
    std::vector<std::thread> robots;
    for (int i = 0; i < NUM_ROBOTS; ++i) {
        int left_tool_index = i;
        int right_tool_index = (i + 1) % NUM_TOOLS;
        robots.emplace_back(performTask, i, left_tool_index, right_tool_index);
    }

    // Join threads
    for (auto& robot : robots) {
        robot.join();
    }

    std::cout << "Total time taken by all robots to finish tasks: " << (NUM_ROBOTS * TASK_DURATION) << " seconds." << std::endl;

    return 0;
}
