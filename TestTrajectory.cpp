//TestTrajectory.cpp
#include <ctime>
#include <cstdlib>
#include "Trajectory.h"
#include "../TestSuite/Test.h"
#include <cmath>

class TestTrajectory : public TestSuite::Test
{
public:
  void run()
  {
    PathRecorder pr;
    pr.setVisited(IntPair());
    pr.setVisited(IntPair(-1.0));
    pr.setVisited(IntPair(-2,0));
    pr.setVisited(IntPair(-2,1));
    pr.remove(IntPair(-2,0));
    pr.print();
    
    Trajectory tr;
    tr.addLink(Direction::RIGHT);
    tr.addLink(Direction::UP);
    tr.addLink(Direction::LEFT);
    tr.addLink(Direction::UP);
    tr.addLink(Direction::LEFT);
    tr.addLink(Direction::DOWN);
    tr.print(); //only three points added since the fourth (0,0) is already recorded
    Trajectory* tr0 = Trajectory::parseTrajectory("(0,0)(1,0)(1,1)(0,1)(0,2)(-1,2)(-1,1)");
    tr0->print();
	test_(tr == *tr0);
    
    tr.removeLastLink();
    tr.removeLastLink();
    tr.print();
    tr0 = Trajectory::parseTrajectory("(0,0)(1,0)(1,1)(0,1)(0,2)");
    test_(tr == *tr0);
    
    tr.addLink();
    tr.addLink();
    tr.print();
    tr0 = Trajectory::parseTrajectory("(0,0)(1,0)(1,1)(0,1)(0,2)(1,2)(2,2)");
    test_(tr == *tr0);
    
    tr.alterLink();
    tr.print();
    tr0 = Trajectory::parseTrajectory("(0,0)(1,0)(1,1)(0,1)(0,2)(1,2)(1,3)");
    test_(tr == *tr0);

    tr.addLink();
    tr.alterLink();
    tr.alterLink();
    tr.print();
    tr0 = Trajectory::parseTrajectory("(0,0)(1,0)(1,1)(0,1)(0,2)(1,2)(1,3)(0,3)");
    test_(tr == *tr0);

    
    {
       Trajectory tr2(20);
      int length = tr2.grow(20); 
      std::cout << "length: " << length << "\n"; //length is random since recorded points may disrupt further growth
      tr2.print();
    }
    {
      Trajectory tr3(20);
      int length = tr3.grow(20); 
      std::cout << "length: " << length << "\n"; //length is random since recorded points may disrupt further growth
      tr3.print();
    }
    {
      Trajectory tr4(20);
      int length = tr4.grow(20); 
      std::cout << "length: " << length << "\n"; //length is random since recorded points may disrupt further growth
      tr4.print();
    }
    
   }
};

int main() 
{
  srand(time(NULL));
  TestTrajectory tt;
  tt.run();
  return tt.report();
}
