#include <algorithm>
#include <cstring>

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
  size_t availableSize = MESSAGE_SIZE - mMessageSize;
  size_t clampMessageSize =
    std::clamp<size_t>(strlen(message), 0, availableSize);
  mMessageSize += clampMessageSize;

#if defined(_WIN32)
  strncat_s(mMessage, message, clampMessageSize);
#else // defined(_WIN32)
  std::strncat(mMessage, message, clampMessageSize);
#endif
}

} // namespace Except
