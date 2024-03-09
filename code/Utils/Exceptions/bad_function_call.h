#pragma once

#include "Utils/Exceptions/base_exception.h"

namespace Except {

class bad_function_call : public base_exception {
public:
  bad_function_call() : base_exception(name()) {}
  virtual const char *name() const override { return "Bad Function Call"; }
};

} // namespace Except
