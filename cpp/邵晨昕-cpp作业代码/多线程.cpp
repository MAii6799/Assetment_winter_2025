// 编写一个模板类 ThreadSafeQueue<T>，表示一个线程安全的队列。要求：

// 使用 std::queue 作为底层容器。

// 使用 std::mutex 和 std::condition_variable 实现线程安全。

// 提供 push(T value) 和 bool pop(T& value) 函数，分别用于入队和出队。

// pop 函数在队列为空时应阻塞，直到有新元素入队。

// （可选）支持超时机制，pop 函数在指定时间内未获取到元素时返回 false
#include<iostream>
#include<queue>
#include<thread>
#include<condition_variable>


template<class T>
class ThreadSafeQueue{
public:
    void push(T value);//入队
    bool pop(T& value);//出队
private:
    std::queue<T> que;
    std::mutex mtx;
    std::condition_variable cv;
};

template<class T>
void ThreadSafeQueue<T>::push(T value){
    std::unique_lock<std::mutex> lock(mtx);
    que.push(value);
    cv.notify_one();
}
template<class T>
bool ThreadSafeQueue<T>::pop(T& value){
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock,[this] { return !que.empty(); });
    value=que.front();
    que.pop();
    return true;
}


//////这是一段测试代码//////
int main() {
    ThreadSafeQueue<int> tsQueue;
    std::thread producer([&] {
        for (int i = 0; i < 5; ++i) {
            tsQueue.push(i);
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    });

    std::thread consumer([&] {
        int value;
        for (int i = 0; i < 5; ++i) {
            if (tsQueue.pop(value)) {
                std::cout << "Popped value: " << value << std::endl;
            }
        }
    });

    producer.join();
    consumer.join();

    return 0;
}