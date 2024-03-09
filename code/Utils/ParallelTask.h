/** @file ParallelTask.h */
#pragma once

#include <functional>
#include <future>

class ParallelTask {
public:
  explicit ParallelTask(std::function<bool()> func);
  ~ParallelTask();
  bool isFinished() const;

private:
  std::future<bool> mFuture;
};