#include <iostream>
#include <map>

int main ()
{
  std::map<int, int> myMap;

  myMap[2112]=10;
  myMap[2211]=30;
  myMap[1000]=50;
  myMap[5000]=70;

  ++myMap[2112];

  for(auto it = myMap.begin(); it != myMap.end(); ++it)
  {
	  std::cout << it->first << ", " << it->second << std::endl;
  }

  return 0;
}
