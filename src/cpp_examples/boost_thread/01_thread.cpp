#include <boost/thread.hpp>
#include <boost/chrono.hpp>
#include <iostream>

void wait(int seconds)
{
  boost::this_thread::sleep_for(boost::chrono::seconds{seconds});
}

void thread()
{
  for (int i = 0; i < 5; ++i)
  {
    wait(1);
    std::cout << "1st thread \n";
    std::cout << i << '\n';
  }
}

void thread2()
{
  for (int i = 0; i < 5; ++i)
  {
    wait(1);
    std::cout << "2st thread \n";
    std::cout << i << '\n';
  }
}

int main()
{
  boost::thread t{thread};
  boost::thread t2{thread2};

  t.join();
  t2.join();
}
