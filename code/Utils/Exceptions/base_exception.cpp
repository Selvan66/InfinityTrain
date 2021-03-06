#include <cstring>
#include <cassert>

#include "Utils/Exceptions/base_exception.h"

namespace Except
{

base_exception::base_exception()
: mMessageSize(0)
, mMessage()
{
    add(name());
}

base_exception::base_exception(const char* message)
: mMessageSize(0)
, mMessage()
{
    add(message);
}

base_exception& base_exception::add(const char* message)
{
    if (mMessageSize != 0)
        insertMassage(" | ");
    insertMassage(message);
    return *this;
}

const char* base_exception::name() const
{
    return "Base Exception";
}

const char* base_exception::what() const 
{
    return mMessage;
}

void base_exception::insertMassage(const char* message)
{
    mMessageSize += strlen(message);

    if (mMessageSize >= MESSAGE_SIZE)
        throw std::out_of_range("Base Exception: RESIZE MESSAGE SIZE YOU GREEDY MAN");

    strcat_s(mMessage, message);
}

}