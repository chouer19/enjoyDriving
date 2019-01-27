#include <boost/thread.hpp>
#include <boost/chrono.hpp>
#include <iostream>

void wait(int seconds)
{
  boost::this_thread::sleep_for(boost::chrono::seconds{seconds});
}

boost::mutex mutex;

void thread(int order, int &number)
{
  using boost::this_thread::get_id;
  for (int i = 0; i < 5; ++i)
  {
    wait(1);
    mutex.lock();
    std::cout << "Thread " << order << " st's number is :" <<  number << std::endl;
    number++;
    mutex.unlock();
  }
}

int main()
{
  int number = 6;
  boost::thread t1{thread, 1,std::ref(number)};
  boost::thread t2{thread, 2, std::ref(number)};

  for (int i=0; i < 5; i++){
    wait(1);
    mutex.lock();
    std::cout << "Main thread number is : " << number++ << '\n';
    mutex.unlock();
  }
 
  t1.join();
  t2.join();

}
