/** @file ParallelTask.cpp */
#include <chrono>

#include "Utils/ParallelTask.h"

ParallelTask::ParallelTask(std::function<bool()> func) {
  mFuture = std::async(std::launch::async,
                       func); //< Carefully it's
                              // not mutex lock
}

ParallelTask::~ParallelTask() { mFuture.get(); }

bool ParallelTask::isFinished() const {
  return mFuture.wait_for(std::chrono::milliseconds(0)) ==
         std::future_status::ready;
}