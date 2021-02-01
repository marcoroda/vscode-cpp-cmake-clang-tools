// conditionVariables.cpp

#include <atomic>
#include <chrono>
#include <condition_variable>
#include <iostream>
#include <thread>
#include <vector>

std::mutex mutex_;
std::condition_variable condVar;
std::vector<int> myvec;
auto waitFor = std::chrono::milliseconds(1000);
std::atomic<bool> dataReady{false};

void waitingForWork() {
  std::cout << "Waiting " << std::endl;
  std::unique_lock<std::mutex> lck(mutex_);
  condVar.wait(lck, [] { return dataReady.load(); });  // (4)
  std::cout << "Running, val on myvec is: " << myvec.back() << std::endl;
  std::this_thread::sleep_for(waitFor);
}

void setDataReady() {
  {
    std::lock_guard<std::mutex> lck(mutex_);
    myvec.push_back(15);
    std::this_thread::sleep_for(waitFor);
    dataReady = true;
  }
  std::cout << "Data prepared" << std::endl;
  condVar.notify_one();  // (3)
}

int main() {
  std::cout << std::endl;

  while (true) {
    std::thread t1(waitingForWork);  // (1)
    std::thread t2(setDataReady);    // (2)
    t1.join();
    t2.join();
  }

  std::cout << std::endl;
}