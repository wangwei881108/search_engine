#include <iostream>
#include <queue>
#include <string>
using namespace std;

class Thread {
  int priority;
  string name;
public:
  Thread() {
     name = "";
     priority = 0;
  }
  Thread(string n, int p) {
     name = n;
     priority = p;
  }

  string getname() const {
     return name;
  }
  int getpriority() const {
     return priority;
  }
  friend bool operator<( const Thread &a, const Thread &b)
  {
   return a.getpriority() < b.getpriority();
  }
};

// Determine priority.
/*
bool operator<( const Thread &a, const Thread &b)
{
  return a.getpriority() < b.getpriority();
}
*/
