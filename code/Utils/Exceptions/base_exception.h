#pragma once

#include <stdexcept>

namespace Except {

class base_exception : public std::exception {
public:
  base_exception();
  base_exception &add(const char *message);

  virtual const char *name() const;
  virtual const char *what() const noexcept override;

protected:
  base_exception(const char *message);

private:
  void insertMassage(const char *message);

private:
  static constexpr size_t MESSAGE_SIZE = 256;
  char mMessage[MESSAGE_SIZE];
  size_t mMessageSize;
};

} // namespace Except