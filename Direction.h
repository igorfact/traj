//Direction.h
#ifndef DIRECTION_H
#define DIRECTION_H
//#include <cstdlib>
#include <cassert>

class Direction
{
public:
  enum dirEnum{RIGHT, UP, LEFT, DOWN};
private:
  dirEnum dir;
public:
  Direction(dirEnum de = RIGHT)
  {
    assert(de >= 0 && de < 4);
    dir = de;
  }
  
  Direction(IntPair ip)
  {
    int x = ip.getX(); 
    int y = ip.getY();
    assert(x*x + y*y == 1);
    if (x == 1)
      dir = RIGHT;
    else if (x == -1)
      dir = LEFT;
    else if (y == 1)
      dir = UP;
    else if (y == -1)
      dir = DOWN;
  }
  
  Direction(const Direction& otherDir) : dir(otherDir.getEnum()){}
  
  std::auto_ptr<IntPair> getDirPairPointer() const
  {
    switch(dir)
    {
      case RIGHT:
        return std::auto_ptr<IntPair>(new IntPair(1,0));
      case UP:
        return std::auto_ptr<IntPair>(new IntPair(0,1));
      case LEFT:
        return std::auto_ptr<IntPair>(new IntPair(-1,0));
      default:
        return std::auto_ptr<IntPair>(new IntPair(0,-1));
    }
  }

  IntPair getDirPair() const
  {
    switch(dir)
    {
      case RIGHT:
        return IntPair(1,0);
      case UP:
        return IntPair(0,1);
      case LEFT:
        return IntPair(-1,0);
      default:
        return IntPair(0,-1);
    }
  }
  
  int getNo() const {return dir;}
  
  dirEnum getEnum() const{return dir;}
  
  static Direction getRandom()
  {
     return Direction(static_cast<dirEnum>(rand()%4));
  }
  
  static Direction getRandomNew(const Direction& parent) 
  {  //return random direction other than given
     return Direction(static_cast<dirEnum>((parent.getNo() + 3 + rand()%3)%4));
  }
  
  static Direction getFirstChild(const Direction& parent) 
  {  //return first direction other than given (turn right from given)
     return Direction(static_cast<dirEnum>((parent.getNo() + 3)%4));
  }

  static Direction getSecondChild(const Direction& parent) 
  {  //return second direction other than given (same as given)
     return Direction(parent.getEnum());
  }

  static Direction getThirdChild(const Direction& parent) 
  {  //return third direction other than given (turn left from given)
     return Direction(static_cast<dirEnum>((parent.getNo() + 1)%4));
  }
  
  static Direction getNextChild(const Direction& parent, const Direction& child) 
  {  //return next direction other than parent and the child (turn left from child)
     //only three children allowed
     assert(child.getEnum() != getThirdChild(parent).getEnum()); //child is not the last one
     return Direction(static_cast<dirEnum>((child.getNo() + 1)%4));
  }
};
#endif
