//TestIntPair.cpp
#include "IntPair.h"
#include "../TestSuite/Test.h"
#include <cmath>

class TestIntPair : public TestSuite::Test
{
public:
  void run()
	{
	  IntPair ip;
	  test_(ip.getX() == 0 && ip.getY() == 0);
	  
	  IntPair ip2(3,-5);
	  test_(ip2.getX() == 3 && ip2.getY() == -5);
	  
	  IntPair ip3 = ip2;
	  test_(ip3.getX() == 3 && ip3.getY() == -5);
	  
	  IntPair ip4 = ip3 + ip2;
	  test_(ip4.getX() == 6 && ip4.getY() == -10);

	  test_(ip2 == ip4 - ip3);
	  
	  test_(ip3 < ip4);
	  IntPair ip5(6,-4);
	  test_(ip5 > ip4);
	  test_(ip4 < ip5);
	  test_((ip4 + ip5) == (ip5 + ip4));
	  
	  Direction left = Direction(Direction::LEFT);
	  test_(*(left.getDirPair()) == IntPair(-1,0));
	  test_(*(left.getDirPair()) < IntPair(0,0));
	
		Direction right = Direction();
	  test_(*(right.getDirPair()) == IntPair(1,0));
  
	  //Direction::initialize();
	  int n = Direction::getRandom().getNo();
	  test_(n < 4 && n >=0);
	  n = Direction::getRandom().getNo();
	  test_(n < 4 && n >=0);
	  n = Direction::getRandom().getNo();
	  test_(n < 4 && n >=0);
	  n = Direction::getRandom().getNo();
	  test_(n < 4 && n >=0);
	  n = Direction::getRandom().getNo();
	  test_(n < 4 && n >=0);

	  n = Direction::getRandomNew(Direction(Direction::RIGHT)).getNo();
	  test_(n < 4 && n >=0 && n != 2);
	  n = Direction::getRandomNew(Direction::UP).getNo();
	  test_(n < 4 && n >=0 && n != 3);
	  n = Direction::getRandomNew(Direction::LEFT).getNo();
	  test_(n < 4 && n >=0 && n != 0);
	  n = Direction::getRandomNew(Direction::DOWN).getNo();
	  test_(n < 4 && n >=0 && n != 1);
	  
	  ip4.print();
	  
	  Direction up = Direction(IntPair(0,1));
	  test_(up.getNo() == Direction::UP);
	  left = Direction(IntPair(-1,0));
	  test_(left.getNo() == Direction::LEFT);
	  
	  Direction child = Direction::getFirstChild(up);
	  test_(child.getNo() == Direction::RIGHT);
	  Direction child2 = Direction::getSecondChild(up);
	  test_(child2.getNo() == Direction::UP);
	  child2 = Direction::getNextChild(up, child);
	  test_(child2.getNo() == Direction::UP);
	  Direction child3 = Direction::getThirdChild(up);
	  test_(child3.getNo() == Direction::LEFT);
	  child3 = Direction::getNextChild(up, child2);
	  test_(child3.getNo() == Direction::LEFT);
	  
	  Direction down(Direction::DOWN);

	  child = Direction::getFirstChild(down);
	  test_(child.getNo() == Direction::LEFT);
	  child2 = Direction::getSecondChild(down);
	  test_(child2.getNo() == Direction::DOWN);
	  child2 = Direction::getNextChild(down, child);
	  test_(child2.getNo() == Direction::DOWN);
	  child3 = Direction::getThirdChild(down);
	  test_(child3.getNo() == Direction::RIGHT);
	  
	  child = Direction::getFirstChild(left);
	  test_(child.getNo() == Direction::UP);
	  child = Direction::getNextChild(left, child);
	  test_(child.getNo() == Direction::LEFT);
	  child = Direction::getNextChild(left, child);
	  test_(child.getNo() == Direction::DOWN);
	  
	  
	  right = Direction(IntPair(1,0));
	  child = Direction::getFirstChild(right);
	  test_(child.getNo() == Direction::DOWN);
	  child2 = Direction::getSecondChild(right);
	  test_(child2.getNo() == Direction::RIGHT);
	  child2 = Direction::getNextChild(right, child);
	  test_(child2.getNo() == Direction::RIGHT);
	  child3 = Direction::getThirdChild(right);
	  test_(child3.getNo() == Direction::UP);
	  
	  IntPair ip10 = IntPair(-1,+20);
	  IntPair ip11 = IntPair::parseIntPair("(-1,+20)");
	  test_(ip10 == ip11);
	}
};

int main() 
{
  TestIntPair tip;
  tip.run();
  return tip.report();
}
