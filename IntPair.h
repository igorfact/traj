//IntPair.h
#ifndef INTPAIR_H
#define INTPAIR_H
#include <cstdlib>
#include <cassert>
#include <iostream>
#include <memory>
#include <string>
#include "../require.h"

class IntPair
{
  int x;
  int y;
public:
  IntPair(int i=0, int j=0) : x(i), y(j){}
  int getX() const {return x;}
  int getY() const {return y;}
  IntPair(const IntPair& ip) : x(ip.getX()), y(ip.getY()){}
  IntPair& operator=(const IntPair& ip) 
  {
    if(ip == *this)
      return *this;
    x=ip.getX(); 
    y=ip.getY(); 
    return *this;
  }
/*
  IntPair& operator+(const IntPair& ip) const
  {
    return *(new IntPair(x+ip.getX(), y+ip.getY()));
  }
  IntPair& operator-(const IntPair& ip) const
  {
    return *(new IntPair(x-ip.getX(), y-ip.getY()));
  }
*/
  IntPair operator+(const IntPair& ip) const
  {
    return IntPair(x+ip.getX(), y+ip.getY());
  }
  IntPair operator-(const IntPair& ip) const
  {
    return IntPair(x-ip.getX(), y-ip.getY());
  }
  bool operator<(const IntPair& ip) const
  {
    if (x < ip.getX())
      return true;
    else if (x == ip.getX() && y < ip.getY())
      return true;
    return false;  
  }
  bool operator>(const IntPair& ip) const
  {
    if (x > ip.getX())
      return true;
    else if (x == ip.getX() && y > ip.getY())
      return true;
    return false;  
  }
  bool operator==(const IntPair& ip) const
  {
    if (x == ip.getX() && y == ip.getY())
      return true;
    return false;  
  }
  bool operator!=(const IntPair& ip) const
  {
    return !(*this == ip);
  }
  void print(){std::cout << "(" << x << "," << y << ")";}
  
  static IntPair parseIntPair(const std::string& ipString)
  {//string must be like "(x,y)", where x and y are int
    assert(ipString.length() >=5 && ipString[0] == '(' && ipString[ipString.length()-1] ==')');
    size_t pos = ipString.find(',');
    assert(pos != std::string::npos && pos > 1 && ipString.length()-2 > pos);
    std::string xString = ipString.substr(1, pos-1);
    std::string yString = ipString.substr(pos+1, ipString.length() - 2 - pos);
    int x = atoi(xString.c_str());
    int y = atoi(yString.c_str());
    return IntPair(x,y);
  }
};


#endif

    
    

