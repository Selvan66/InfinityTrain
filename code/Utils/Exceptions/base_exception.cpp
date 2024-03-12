#include <cstring>
#include <stdexcept>

#include "Utils/Exceptions/base_exception.h"

namespace Except {

base_exception::base_exception() : mMessage(), mMessageSize(0) { add(name()); }

base_exception::base_exception(const char* message)
  : mMessage(), mMessageSize(0) {
  add(message);
}

base_exception& base_exception::add(const char* message) {
  if (mMessageSize != 0)
    insertMassage(" | ");
  insertMassage(message);
  return *this;
}

const char* base_exception::name() const { return "Base Exception"; }

const char* base_exception::what() const noexcept { return mMessage; }

void base_exception::insertMassage(const char* message) {
  mMessageSize += strlen(message);

  if (mMessageSize >= MESSAGE_SIZE)
    throw std::out_of_range("Base Exception: RESIZE MESSAGE "
                            "SIZE YOU GREEDY MAN");

  strcat(mMessage, message);
}

} // namespace Except
