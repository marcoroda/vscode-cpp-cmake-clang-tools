#include <atomic>
#include <chrono>
#include <condition_variable>
#include <deque>
#include <iostream>
#include <thread>

std::mutex mutex_app;
std::condition_variable cond;
std::deque<int> mydeque;
const unsigned int max_buffer_size = 5;

void producer(unsigned int update_interval_millisecs,
              std::atomic<bool>& running) {
  const auto wait_duration =
      std::chrono::milliseconds(update_interval_millisecs);

  while (running) {
    std::unique_lock<std::mutex> locker(mutex_app);
    cond.wait(locker, []() { return mydeque.size() < max_buffer_size; });
    int val = rand();
    mydeque.push_back(val);
    std::cout << "Produced " << val << "\n";
    locker.unlock();
    std::this_thread::sleep_for(wait_duration);
    cond.notify_one();
  }
}

void consumer(unsigned int update_interval_millisecs,
              std::atomic<bool>& running) {
  const auto wait_d = std::chrono::milliseconds(update_interval_millisecs);
  while (running) {
    std::unique_lock<std::mutex> locker(mutex_app);
    cond.wait(locker, []() { return mydeque.size() > 0; });
    int val = mydeque.back();
    mydeque.pop_back();
    std::cout << "Consumed: " << val << "\n";
    std::this_thread::sleep_for(wait_d);
    locker.unlock();
    cond.notify_one();
  }
}

int main() {
  std::cout << "*** press enter to exit the program gracefully\n\n";

  const unsigned int update_interval =
      500;  // update after every 50 milliseconds

  std::atomic<bool> running{true};
  std::thread update_thread(producer, update_interval, std::ref(running));
  std::thread consume_thread(consumer, update_interval, std::ref(running));

  // exit nicely
  std::cin.get();
  running.store(false);

  update_thread.join();
  consume_thread.join();
}