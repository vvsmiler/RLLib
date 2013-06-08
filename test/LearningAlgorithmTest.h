/*
 * Copyright 2013 Saminda Abeyruwan (saminda@cs.miami.edu)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * LearningAlgorithmTest.h
 *
 *  Created on: May 12, 2013
 *      Author: sam
 */

#ifndef LEARNINGALGORITHMTEST_H_
#define LEARNINGALGORITHMTEST_H_

#include "HeaderTest.h"
#include "Projector.h"
#include "SupervisedAlgorithm.h"

RLLIB_TEST(SupervisedAlgorithmTest)

class SupervisedAlgorithmTest: public SupervisedAlgorithmTestBase
{
  public:
    SupervisedAlgorithmTest()
    {
      srand(time(0));
    }

    virtual ~SupervisedAlgorithmTest()
    {
    }
    void run();

    void linearRegression();
    void logisticRegression();
};

#endif /* LEARNINGALGORITHMTEST_H_ */
