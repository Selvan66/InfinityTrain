#pragma once

#include "Utils/Exceptions/base_exception.h"

namespace Except
{

class bad_argument : public base_exception
{
    public:
        bad_argument() : base_exception(name()) { }
        virtual const char* name() const override { return "Bad Argument"; }
};

}