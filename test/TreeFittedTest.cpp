/*
 * TreeFittedTest.cpp
 *
 *  Created on: Nov 21, 2014
 *      Author: sam
 */

#include "TreeFittedTest.h"
#include "Math.h"
#include "util/TreeFitted/ExtraTreeEnsemble.h"

RLLIB_TEST_MAKE(TreeFittedTest)

TreeFittedTest::TreeFittedTest()
{
}

TreeFittedTest::~TreeFittedTest()
{
}

void TreeFittedTest::testRosenbrock()
{
  const int input_size = 2;
  const int output_size = 1;
  RLLib::Random<float>* random = new RLLib::Random<float>();
  RLLib::Range<float>* range = new RLLib::Range<float>(-2.0f, 2.0f);
  PoliFitted::Dataset* trainingDataset = new PoliFitted::Dataset(input_size, output_size);
  PoliFitted::Dataset* testingDataset = new PoliFitted::Dataset(input_size, output_size);
  PoliFitted::Regressor* reg = new PoliFitted::ExtraTreeEnsemble(input_size, output_size, 30, 2);

  for (int i = 0; i < 500 + 200; i++)
  {
    const float x = range->choose(random);
    const float y = range->choose(random);
    const float f_xy = std::pow((1 - x), 2) + 100.0f * std::pow((y - std::pow(x, 2)), 2);
    PoliFitted::Tuple* input = new PoliFitted::Tuple(input_size);
    PoliFitted::Tuple* output = new PoliFitted::Tuple(output_size);
    input->at(0) = x;
    input->at(1) = y;
    output->at(0) = f_xy;
    if (i < 500)
      trainingDataset->AddSample(input, output);
    else
      testingDataset->AddSample(input, output);
  }

  std::cout << "Learning: " << std::endl;
  reg->Train(trainingDataset);

  std::cout << "Evaluation: " << std::endl;
  for (PoliFitted::Dataset::iterator iter = testingDataset->begin(); iter != testingDataset->end();
      ++iter)
  {
    PoliFitted::Tuple* input = (*iter)->GetInputTuple();
    PoliFitted::Tuple* ouput = (*iter)->GetOutputTuple();
    PoliFitted::Tuple result(input_size);
    reg->Evaluate(input, result);
    std::cout << "f_actual: " << ouput->at(0) << " f_estimated: " << result.at(0) << std::endl;
  }

  std::cout << "training_err (L2): " << reg->ComputeTrainError(trainingDataset)
      << " testing_err (L2): " << reg->ComputeTrainError(testingDataset) << std::endl;

  for (PoliFitted::Dataset::iterator iter = trainingDataset->begin();
      iter != trainingDataset->end(); ++iter)
    delete (*iter);
  for (PoliFitted::Dataset::iterator iter = testingDataset->begin(); iter != testingDataset->end();
      ++iter)
    delete (*iter);

  delete random;
  delete range;
  delete trainingDataset;
  delete testingDataset;
  delete reg;

}

void TreeFittedTest::testRastrigin()
{
  const int input_size = 100;
  const int output_size = 1;
  const float A = 10.0f;
  RLLib::Random<float>* random = new RLLib::Random<float>();
  RLLib::Range<float>* range = new RLLib::Range<float>(-5.12f, 5.12f);
  PoliFitted::Dataset* trainingDataset = new PoliFitted::Dataset(input_size, output_size);
  PoliFitted::Dataset* testingDataset = new PoliFitted::Dataset(input_size, output_size);
  PoliFitted::Regressor* reg = new PoliFitted::ExtraTreeEnsemble(input_size,
      output_size/*using default parameters*/);

  const int nbTrainingSamples = 1000;
  const int nbTestingSamples = 200;
  for (int i = 0; i < nbTrainingSamples + nbTestingSamples; i++)
  {
    PoliFitted::Tuple* input = new PoliFitted::Tuple(input_size);
    PoliFitted::Tuple* output = new PoliFitted::Tuple(output_size);
    float f_x = A * input_size;
    for (int j = 0; j < input_size; j++)
    {
      input->at(j) = range->choose(random);
      f_x += (std::pow(input->at(j), 2) - A * cos(2.0f * M_PI * input->at(j)));
    }
    output->at(0) = f_x;
    if (i < nbTrainingSamples)
      trainingDataset->AddSample(input, output);
    else
      testingDataset->AddSample(input, output);
  }

  std::cout << "Learning: " << std::endl;
  reg->Train(trainingDataset);

  std::cout << "Evaluation: " << std::endl;
  for (PoliFitted::Dataset::iterator iter = testingDataset->begin(); iter != testingDataset->end();
      ++iter)
  {
    PoliFitted::Tuple* input = (*iter)->GetInputTuple();
    PoliFitted::Tuple* ouput = (*iter)->GetOutputTuple();
    PoliFitted::Tuple result(input_size);
    reg->Evaluate(input, result);
    std::cout << "f_actual: " << ouput->at(0) << " f_estimated: " << result.at(0) << std::endl;
  }

  std::cout << "training_err (L2): " << reg->ComputeTrainError(trainingDataset)
      << " testing_err (L2): " << reg->ComputeTrainError(testingDataset) << std::endl;

  for (PoliFitted::Dataset::iterator iter = trainingDataset->begin();
      iter != trainingDataset->end(); ++iter)
    delete (*iter);
  for (PoliFitted::Dataset::iterator iter = testingDataset->begin(); iter != testingDataset->end();
      ++iter)
    delete (*iter);

  delete random;
  delete range;
  delete trainingDataset;
  delete testingDataset;
  delete reg;

}

void TreeFittedTest::testCigar()
{
  const int input_size = 100;
  const int output_size = 1;
  RLLib::Random<float>* random = new RLLib::Random<float>();
  RLLib::Range<float>* range = new RLLib::Range<float>(-5, 5);
  PoliFitted::Dataset* trainingDataset = new PoliFitted::Dataset(input_size, output_size);
  PoliFitted::Dataset* testingDataset = new PoliFitted::Dataset(input_size, output_size);
  PoliFitted::Regressor* reg = new PoliFitted::ExtraTreeEnsemble(input_size, output_size, 50, 5, 2,
      0.0f, LeafType::CONSTANT);

  const int nbTrainingSamples = 1000;
  const int nbTestingSamples = 200;
  for (int i = 0; i < nbTrainingSamples + nbTestingSamples; i++)
  {
    PoliFitted::Tuple* input = new PoliFitted::Tuple(input_size);
    PoliFitted::Tuple* output = new PoliFitted::Tuple(output_size);
    input->at(0) = range->choose(random);
    float f_x = std::pow(input->at(0), 2);
    for (int j = 1; j < input_size; j++)
    {
      input->at(j) = range->choose(random);
      f_x += std::pow(10.0f * input->at(j), 2);
    }
    output->at(0) = f_x;
    if (i < nbTrainingSamples)
      trainingDataset->AddSample(input, output);
    else
      testingDataset->AddSample(input, output);
  }

  std::cout << "Learning: " << std::endl;
  reg->Train(trainingDataset);

  std::cout << "Evaluation reg: " << std::endl;
  for (PoliFitted::Dataset::iterator iter = testingDataset->begin(); iter != testingDataset->end();
      ++iter)
  {
    PoliFitted::Tuple* input = (*iter)->GetInputTuple();
    PoliFitted::Tuple* ouput = (*iter)->GetOutputTuple();
    PoliFitted::Tuple result(input_size);
    reg->Evaluate(input, result);
    std::cout << "f_actual: " << ouput->at(0) << " f_estimated: " << result.at(0) << std::endl;
  }

  std::cout << "reg_training_err (L2): " << reg->ComputeTrainError(trainingDataset)
      << " reg_testing_err (L2): " << reg->ComputeTrainError(testingDataset) << std::endl;

  std::string fName = "ExtraTreeEnsemble.bin";
  std::ofstream of(fName);
  reg->WriteOnStream(of);

  PoliFitted::Regressor* reg2 = new PoliFitted::ExtraTreeEnsemble(input_size, output_size, 50, 5, 2,
      0.0f, LeafType::CONSTANT);
  std::ifstream in(fName);
  reg2->ReadFromStream(in);

  std::cout << "Evaluation reg2: " << std::endl;
  for (PoliFitted::Dataset::iterator iter = testingDataset->begin(); iter != testingDataset->end();
      ++iter)
  {
    PoliFitted::Tuple* input = (*iter)->GetInputTuple();
    PoliFitted::Tuple* ouput = (*iter)->GetOutputTuple();
    PoliFitted::Tuple result(input_size);
    reg2->Evaluate(input, result);
    std::cout << "f_actual: " << ouput->at(0) << " f_estimated: " << result.at(0) << std::endl;
  }

  std::cout << "reg2_training_err (L2): " << reg2->ComputeTrainError(trainingDataset)
      << " reg2_testing_err (L2): " << reg2->ComputeTrainError(testingDataset) << std::endl;

  for (PoliFitted::Dataset::iterator iter = trainingDataset->begin();
      iter != trainingDataset->end(); ++iter)
    delete (*iter);
  for (PoliFitted::Dataset::iterator iter = testingDataset->begin(); iter != testingDataset->end();
      ++iter)
    delete (*iter);

  delete random;
  delete range;
  delete trainingDataset;
  delete testingDataset;
  delete reg;
  delete reg2;
}

void TreeFittedTest::run()
{
  testRosenbrock();
  testRastrigin();
  testCigar();
}

