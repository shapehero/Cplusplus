#include <iostream>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <deque>


std::mutex g_cvMutex;
std::condition_variable g_cv;

//缓冲区
std::deque<int> g_data_deque;

//缓冲区最大数目
const int MAX_NUM = 30;

//数据
int g_next_index = 0;

//生产者，消费者纯种个数
const int PRODUCER_THREAD_NUM = 3;
const int CONSUMER_THREAD_NUM = 3;

void producer_thread(int thread_id)
{
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        //加锁
        std::unique_lock<std::mutex> lk(g_cvMutex);
        //当队列未满时，继续添加数据
        g_cv.wait(lk, []() { return g_data_deque.size() <= MAX_NUM; });
        g_next_index++;
        g_data_deque.push_back(g_next_index);
        std::cout << "producer_thread: " << thread_id << " producer data: ";
        std::cout << "deque size: " << g_data_deque.size() << std::endl;
        //唤醒其他线程
        g_cv.notify_all();
        //自动释放锁
    }
}

void consumer_thread(int thread_id)
{
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        //加锁
        std::unique_lock<std::mutex> lk(g_cvMutex);
        //检测条件是否达成
        g_cv.wait(lk, []() { return !g_data_deque.empty(); });
        //互斥操作，消息数据
        int data = g_data_deque.front();
        g_data_deque.pop_front();
        std::cout << "\tconsumer_thread: " << thread_id << " consumer data: ";
        std::cout << data << " deque size: "<< g_data_deque.size() << std::endl;
        //唤醒其他线程
        g_cv.notify_all();
        //自动释放锁
    }
}

int main(int argc, char *argv[])
{
    std::thread arrProducerThread[PRODUCER_THREAD_NUM];
    std::thread arrConsumerThread[CONSUMER_THREAD_NUM];

    for (int i = 0; i < PRODUCER_THREAD_NUM; i++)
    {
        arrProducerThread[i] = std::thread(producer_thread, i);
    }

    for (int i = 0; i < CONSUMER_THREAD_NUM; i++)
    {
        arrConsumerThread[i] = std::thread(consumer_thread, i);
    }

    for (int i = 0; i < PRODUCER_THREAD_NUM; i++)
    {
        arrProducerThread[i].join();
    }

    for (int i = 0; i < CONSUMER_THREAD_NUM; i++)
    {
        arrConsumerThread[i].join();
    }

    return 0;
}