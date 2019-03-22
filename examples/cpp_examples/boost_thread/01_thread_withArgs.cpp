#include <boost/thread.hpp>
#include <boost/chrono.hpp>
#include <iostream>

void wait(int seconds)
{
  boost::this_thread::sleep_for(boost::chrono::seconds{seconds});
}

void thread(int number)
{
  for (int i = 0; i < 5; ++i)
  {
    wait(1);
    std::cout << number <<":"<< i << "\n";
  }
}

void thread2(int number)
{
  for (int i = 0; i < 5; ++i)
  {
    wait(1);
    std::cout << number <<":"<< i << "\n";
  }
}

int main()
{
  boost::thread t{thread,1};
  boost::thread t2{thread,2};
  boost::thread t3(thread,3);

  t.join();
  t2.join();
  t3.join();
}
