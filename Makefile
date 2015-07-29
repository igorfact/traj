#Makefile

CPP = g++
OFLAG = -o
CPPFLAGS = -Wall
.SUFFIXES : .o .h .cpp .c
.cpp.o :
	$(CPP) $(CPPFLAGS) -c $<
.c.o :
	$(CPP) $(CPPFLAGS) -c $<

all: \
  cycles 
Test:
TestIntPair:
TestTrajectory:
TestHistogram:
TestBunchHistogram:
TestTrajectoryBunch:

cycles: cycles.o
	$(CPP) $(OFLAG) cycles cycles.o 

Test: Test.o
	$(CPP) $(OFLAG) Test Test.o

TestIntPair: TestIntPair.o Test.o
	$(CPP) $(OFLAG) TestIntPair TestIntPair.o Test.o 
	
TestTrajectory: TestTrajectory.o
	$(CPP) $(OFLAG) TestTrajectory TestTrajectory.o Test.o 
	
TestHistogram: TestHistogram.o
	$(CPP) $(OFLAG) TestHistogram TestHistogram.o
	
TestBunchHistogram: TestBunchHistogram.o
	$(CPP) $(OFLAG) TestBunchHistogram TestBunchHistogram.o
	
TestTrajectoryBunch: TestTrajectoryBunch.o
	$(CPP) $(OFLAG) TestTrajectoryBunch TestTrajectoryBunch.o

TestTrial: TestTrial.o
	$(CPP) $(OFLAG) TestTrial TestTrial.o


cycles.o: IntPair.h Trajectory.h Ratio.h Histogram.h cycles.h cycles.cpp
Test.o: ../TestSuite/Test.h ../TestSuite/Test.cpp
	$(CPP) $(CPPFLAGS) -c ../TestSuite/Test.h ../TestSuite/Test.cpp
TestIntPair.o: IntPair.h ../TestSuite/Test.h TestIntPair.cpp
	$(CPP) $(CPPFLAGS) -c IntPair.h ../TestSuite/Test.h TestIntPair.cpp
TestTrajectory.o: IntPair.h Trajectory.h TestTrajectory.cpp
	$(CPP) $(CPPFLAGS) -c Trajectory.h ../TestSuite/Test.h TestTrajectory.cpp
TestHistogram.o: IntPair.h Trajectory.h Histogram.h TestHistogram.cpp
TestBunchHistogram.o: IntPair.h Trajectory.h BunchHistogram.h TestBunchHistogram.cpp
TestTrajectoryBunch.o: IntPair.h Trajectory.h BunchHistogram.h TrajectoryBunch.h TestTrajectoryBunch.cpp
	$(CPP) $(CPPFLAGS) -c IntPair.h Trajectory.h BunchHistogram.h TrajectoryBunch.h TestTrajectoryBunch.cpp
TestTrial.o: Trial.h TestTrial.cpp
	$(CPP) $(CPPFLAGS) -c Trial.h TestTrial.cpp

.PHONY: clean

clean:
	rm -f *.o *~ core 


