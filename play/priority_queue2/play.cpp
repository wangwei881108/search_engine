#include <iostream>
#include <queue>
#include <string>
#include "Thread.h"
using namespace std;
int main()
{
  priority_queue<Thread> q;
  
  q.push(Thread("F", 10));
  q.push(Thread("M", 2));

  // show priority
  cout << "Priorities: "; 
  while(!q.empty()) {
    cout << q.top().getname() << endl;
    cout << "            ";
    q.pop();
  }

  return 0;
}

