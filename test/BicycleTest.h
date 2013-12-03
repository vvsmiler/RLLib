/*
 * BicycleTest.h
 *
 *  Created on: Dec 2, 2013
 *      Author: sam
 */

#ifndef BICYCLETEST_H_
#define BICYCLETEST_H_

#include "Test.h"
#include "RandlovBike.h"

RLLIB_TEST(BicycleTest)
class BicycleTest: public BicycleTestBase
{
  public:
    void run();
  protected:
    void testBicycleBalance();
    void testBicycleGoToTarget();
};

class BicycleProjector: public Projector<double>
{
  protected:
    int nbTiles;
    int memory;
    Vector<double>* vector;
    Hashing* hashing;
    Tiles<double>* tiles;
  public:
    BicycleProjector(const int& nbVars);
    virtual ~BicycleProjector();
    const Vector<double>* project(const Vector<double>* x, int h1);
    const Vector<double>* project(const Vector<double>* x);
    double vectorNorm() const;
    int dimension() const;
};

#endif /* BICYCLETEST_H_ */