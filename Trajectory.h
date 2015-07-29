//Trajectory.h
#ifndef TRAJECTORY_H
#define TRAJECTORY_H
#include <set>
#include <vector>
#include <iostream>
#include <cassert>
#include "IntPair.h"
#include "Direction.h"

class PathRecorder
{//records the trajectory points
  std::set<IntPair> pathSet;
public:
  PathRecorder(){}
  ~PathRecorder(){}
  bool isVisited(const IntPair& point) const
  {
    return (pathSet.count(point) > 0);
  }
  void setVisited(const IntPair& point)
  {
    pathSet.insert(point);
  }
  void remove(IntPair point)
  {
    pathSet.erase(point);
  }
  IntPair find(IntPair& point)
  {
    return static_cast<IntPair>(*pathSet.find(point));
  }
  void print()
  {
    for (std::set<IntPair>::iterator it = pathSet.begin(); it != pathSet.end(); it++)
    {
      ((IntPair)(*it)).print();
    }
    std::cout << std::endl;
  }
};

class Trajectory
{
  IntPair origin;
  std::vector<IntPair*> trv;
  PathRecorder recorder;
  Direction currentDir;
public:
  Trajectory(int length = 100) : 
    //origin(new IntPair(0,0)), 
    currentDir(Direction(Direction::RIGHT))
  {
    trv.reserve(length);
    recorder.setVisited(origin);
    trv.push_back(recorder.find(origin));
  }
  
  ~Trajectory(){} 
  
  size_t getSize() const
  {
    return trv.size();
  }

  IntPair* getPoint(size_t i) const
  {
    assert(getSize() > i);
    return trv[i];
  }
  
  bool operator==(const Trajectory& otherTr) const
  {
    if (getSize() != otherTr.getSize())
      return false;
    
    for (size_t i=0; i < getSize(); i++)
    {
      if (*getPoint(i) != *otherTr.getPoint(i))
        return false;
    }
    return true;  
  }

  Direction getCurrentDirection() const
  {
    return currentDir;
  }
  
  Direction getLastDirection() const
  {
    return Direction(*getPoint(getSize()-1) - *getPoint(getSize()-2));
  }
  
  Direction getPreLastDirection() const
  {
    return Direction(*getPoint(getSize()-2) - *getPoint(getSize()-3));
  }
  
  bool addLink(Direction dir)
  { //true when new point isn't in the trajectory
    IntPair point = *getPoint(getSize()-1) + dir.getDirPair();
    if (recorder.isVisited(point))
    {
      return false;
    }
    recorder.setVisited(point);
    trv.push_back(recorder.find(point));
    currentDir = dir;
    return true;
  }

  bool addLink(Direction::dirEnum de)
  {
    Direction dir = Direction(de);
    return addLink(dir);
  }
  
  bool addLink()
  {
    Direction parentLink = getLastDirection();
    Direction childLink = Direction::getFirstChild(parentLink);
    if (!addLink(childLink))
    {
      childLink = Direction::getSecondChild(parentLink);
      if (!addLink(childLink))
      {
        childLink = Direction::getThirdChild(parentLink);
        if (!addLink(childLink))
          return false;
      }
    }
    return true;
  }
    
  bool addRandomLink()
  {
    //return addLink(Direction::getRandom()); - allowing reverse direction
    return addLink(Direction::getRandomNew(currentDir));
  }
  
  void removeLastLink()
  {
    assert(trv.size() > 2);
    recorder.remove(*(trv.back()));	
    trv.pop_back();
  }
  
  bool alterLink()
  {
    Direction parentLink = getPreLastDirection();
    Direction childLink = getLastDirection();
    while(childLink.getNo() != Direction::getThirdChild(parentLink).getNo())
    {
      childLink = Direction::getNextChild(parentLink,childLink);
      removeLastLink();
      if (addLink(childLink))
        return true;
    }
    return false;
  }

  int grow(size_t maxLength)
  { //for random trajectory growth 
    if (maxLength == 0)
      return 0;
    else
      addLink(Direction(Direction::RIGHT));
    if (maxLength >= 2)
    {
      for (size_t i=0; i < maxLength; i++)
      {
        if (!addRandomLink())
           break;
      }
    }
    return getSize();
  }
  
  void print()
  {
    std::cout << "Printing trajectory: ";
    for (std::vector<IntPair*>::iterator it = trv.begin(); it != trv.end(); it++)
    {
      (static_cust<IntPair*>(it))->print();
    }
    std::cout << "\n";
  }
  
  static Trajectory* parseTrajectory(const std::string& trString)
  {
    Trajectory* tr = new Trajectory(trString.length()/5 + 1);
    IntPair currIntPair = tr->getPoint(0);
    size_t pos = 4; //position of ')' in (0,0)
    IntPair ipp;
    size_t newpos;
    while((newpos = trString.find(')', pos+1)) != std::string::npos)
    {
      std::string ipString = trString.substr(pos+1, newpos-pos);
      ipp = IntPair::parseIntPair(ipString);
      Direction d = Direction(ipp - currIntPair);
      tr->addLink(d);
      currIntPair = ipp; 
      pos = newpos;
    }
    return tr;
  }
};

#endif 
