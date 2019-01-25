#include <boost/thread.hpp>
#include <boost/chrono.hpp>
#include <iostream>

void wait(int seconds)
{
  boost::this_thread::sleep_for(boost::chrono::seconds{seconds});
}

void thread()
{
  boost::this_thread::disable_interruption no_interruption;
  try
  {
    for (int i = 0; i < 5; ++i)
    {
      wait(1);
      std::cout << i << '\n';
    }
  }
  catch (boost::thread_interrupted&) {}
}

int main()
{
  std::cout << "1st debug point\n";
  boost::thread t{thread};
  std::cout << "2ed debug point\n";
  wait(3);
  std::cout << "3rd debug point\n";
  t.interrupt();
  t.join();
}
