/** @file Utility.cpp */
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/spdlog.h"

#include "Utils/Utility.h"
namespace Utility {

void setupLogger() {
  // Create a file rotating logger with 5 MB size max and 3 rotated files
  std::shared_ptr<spdlog::logger> logger = spdlog::rotating_logger_st(
    "default_logger", "logs/logs.log", 1024 * 1024 * 5, 3, true);
  spdlog::set_default_logger(logger);
  spdlog::set_level(spdlog::level::info);
  spdlog::set_pattern("[pid:%P|thread:%t] [%H:%M:%S.%e] [%l] %v");
}

void centerOrigin(sf::Sprite& sprite) {
  sf::FloatRect bounds = sprite.getLocalBounds();
  sprite.setOrigin(std::floor(bounds.left + bounds.width / 2.f),
                   std::floor(bounds.top + bounds.height / 2.f));
}

void centerOrigin(sf::Text& text) {
  sf::FloatRect bounds = text.getLocalBounds();
  text.setOrigin(std::floor(bounds.left + bounds.width / 2.f),
                 std::floor(bounds.top + bounds.height / 2.f));
}

void centerOrigin(sf::Shape& shape) {
  sf::FloatRect bounds = shape.getLocalBounds();
  shape.setOrigin(std::floor(bounds.left + bounds.width / 2.f),
                  std::floor(bounds.top + bounds.height / 2.f));
}

float length(sf::Vector2f vector) {
  return std::sqrt(vector.x * vector.x + vector.y * vector.y);
}

float toDegree(float radian) { return 180.f / 3.14159265f * radian; }

float toRadian(float degree) { return 3.14159265f / 180.f * degree; }

sf::Vector2f unitVector(sf::Vector2f vector) {
  assert(vector != sf::Vector2f(0.f, 0.f));
  return vector / length(vector);
}

float distance(const SceneNode& lhs, const SceneNode& rhs) {
  return length(lhs.getWorldPosition() - rhs.getWorldPosition());
}

bool collision(const SceneNode& lhs, const SceneNode& rhs) {
  return lhs.getBoundingRect().intersects(rhs.getBoundingRect());
}

std::string timeToString(unsigned long long time) {
  return stringFormat("%02d:%02d", ((time / 100) + (time % 100) / 60),
                      (time % 100) % 60);
}

sf::Vector2f getMousePos(sf::RenderWindow& window) {
  return window.mapPixelToCoords(sf::Mouse::getPosition(window));
}

bool areEqual(float lhs, float rhs) {
  return std::fabs(lhs - rhs) <= std::numeric_limits<float>::epsilon() *
                                   std::fmax(std::fabs(lhs), std::fabs(rhs));
}

std::string toString(Player::Output key) {
  sf::Keyboard::Key* keyboard = std::get_if<sf::Keyboard::Key>(&key);
  sf::Mouse::Button* mouse = std::get_if<sf::Mouse::Button>(&key);

#define KEYBOARDTOSTRINGIF(KEY)                                                \
  if (keyboard && (*keyboard == sf::Keyboard::KEY))                            \
    return #KEY;

  KEYBOARDTOSTRINGIF(Unknown)
  KEYBOARDTOSTRINGIF(A)
  KEYBOARDTOSTRINGIF(B)
  KEYBOARDTOSTRINGIF(C)
  KEYBOARDTOSTRINGIF(D)
  KEYBOARDTOSTRINGIF(E)
  KEYBOARDTOSTRINGIF(F)
  KEYBOARDTOSTRINGIF(G)
  KEYBOARDTOSTRINGIF(H)
  KEYBOARDTOSTRINGIF(I)
  KEYBOARDTOSTRINGIF(J)
  KEYBOARDTOSTRINGIF(K)
  KEYBOARDTOSTRINGIF(L)
  KEYBOARDTOSTRINGIF(M)
  KEYBOARDTOSTRINGIF(N)
  KEYBOARDTOSTRINGIF(O)
  KEYBOARDTOSTRINGIF(P)
  KEYBOARDTOSTRINGIF(Q)
  KEYBOARDTOSTRINGIF(R)
  KEYBOARDTOSTRINGIF(S)
  KEYBOARDTOSTRINGIF(T)
  KEYBOARDTOSTRINGIF(U)
  KEYBOARDTOSTRINGIF(V)
  KEYBOARDTOSTRINGIF(W)
  KEYBOARDTOSTRINGIF(X)
  KEYBOARDTOSTRINGIF(Y)
  KEYBOARDTOSTRINGIF(Z)
  KEYBOARDTOSTRINGIF(Num0)
  KEYBOARDTOSTRINGIF(Num1)
  KEYBOARDTOSTRINGIF(Num2)
  KEYBOARDTOSTRINGIF(Num3)
  KEYBOARDTOSTRINGIF(Num4)
  KEYBOARDTOSTRINGIF(Num5)
  KEYBOARDTOSTRINGIF(Num6)
  KEYBOARDTOSTRINGIF(Num7)
  KEYBOARDTOSTRINGIF(Num8)
  KEYBOARDTOSTRINGIF(Num9)
  KEYBOARDTOSTRINGIF(Escape)
  KEYBOARDTOSTRINGIF(LControl)
  KEYBOARDTOSTRINGIF(LShift)
  KEYBOARDTOSTRINGIF(LAlt)
  KEYBOARDTOSTRINGIF(LSystem)
  KEYBOARDTOSTRINGIF(RControl)
  KEYBOARDTOSTRINGIF(RShift)
  KEYBOARDTOSTRINGIF(RAlt)
  KEYBOARDTOSTRINGIF(RSystem)
  KEYBOARDTOSTRINGIF(Menu)
  KEYBOARDTOSTRINGIF(LBracket)
  KEYBOARDTOSTRINGIF(RBracket)
  KEYBOARDTOSTRINGIF(SemiColon)
  KEYBOARDTOSTRINGIF(Comma)
  KEYBOARDTOSTRINGIF(Period)
  KEYBOARDTOSTRINGIF(Quote)
  KEYBOARDTOSTRINGIF(Slash)
  KEYBOARDTOSTRINGIF(BackSlash)
  KEYBOARDTOSTRINGIF(Tilde)
  KEYBOARDTOSTRINGIF(Equal)
  KEYBOARDTOSTRINGIF(Dash)
  KEYBOARDTOSTRINGIF(Space)
  KEYBOARDTOSTRINGIF(Return)
  KEYBOARDTOSTRINGIF(BackSpace)
  KEYBOARDTOSTRINGIF(Tab)
  KEYBOARDTOSTRINGIF(PageUp)
  KEYBOARDTOSTRINGIF(PageDown)
  KEYBOARDTOSTRINGIF(End)
  KEYBOARDTOSTRINGIF(Home)
  KEYBOARDTOSTRINGIF(Insert)
  KEYBOARDTOSTRINGIF(Delete)
  KEYBOARDTOSTRINGIF(Add)
  KEYBOARDTOSTRINGIF(Subtract)
  KEYBOARDTOSTRINGIF(Multiply)
  KEYBOARDTOSTRINGIF(Divide)
  KEYBOARDTOSTRINGIF(Left)
  KEYBOARDTOSTRINGIF(Right)
  KEYBOARDTOSTRINGIF(Up)
  KEYBOARDTOSTRINGIF(Down)
  KEYBOARDTOSTRINGIF(Numpad0)
  KEYBOARDTOSTRINGIF(Numpad1)
  KEYBOARDTOSTRINGIF(Numpad2)
  KEYBOARDTOSTRINGIF(Numpad3)
  KEYBOARDTOSTRINGIF(Numpad4)
  KEYBOARDTOSTRINGIF(Numpad5)
  KEYBOARDTOSTRINGIF(Numpad6)
  KEYBOARDTOSTRINGIF(Numpad7)
  KEYBOARDTOSTRINGIF(Numpad8)
  KEYBOARDTOSTRINGIF(Numpad9)
  KEYBOARDTOSTRINGIF(F1)
  KEYBOARDTOSTRINGIF(F2)
  KEYBOARDTOSTRINGIF(F3)
  KEYBOARDTOSTRINGIF(F4)
  KEYBOARDTOSTRINGIF(F5)
  KEYBOARDTOSTRINGIF(F6)
  KEYBOARDTOSTRINGIF(F7)
  KEYBOARDTOSTRINGIF(F8)
  KEYBOARDTOSTRINGIF(F9)
  KEYBOARDTOSTRINGIF(F10)
  KEYBOARDTOSTRINGIF(F11)
  KEYBOARDTOSTRINGIF(F12)
  KEYBOARDTOSTRINGIF(F13)
  KEYBOARDTOSTRINGIF(F14)
  KEYBOARDTOSTRINGIF(F15)
  KEYBOARDTOSTRINGIF(Pause)

  if ((mouse != nullptr) && (*mouse == sf::Mouse::Left))
    return "MLeft";
  if ((mouse != nullptr) && (*mouse == sf::Mouse::Right))
    return "MRight";
  if ((mouse != nullptr) && (*mouse == sf::Mouse::Middle))
    return "MMiddle";
  if ((mouse != nullptr) && (*mouse == sf::Mouse::XButton1))
    return "MXButton1";
  if ((mouse != nullptr) && (*mouse == sf::Mouse::XButton2))
    return "MXButton2";

  return "";
}

Player::Output toKey(std::string key) {
#define STRINGTOKEYBOARDIF(KEY)                                                \
  if (#KEY == key)                                                             \
    return Player::Output(sf::Keyboard::KEY);

  STRINGTOKEYBOARDIF(Unknown)
  STRINGTOKEYBOARDIF(A)
  STRINGTOKEYBOARDIF(B)
  STRINGTOKEYBOARDIF(C)
  STRINGTOKEYBOARDIF(D)
  STRINGTOKEYBOARDIF(E)
  STRINGTOKEYBOARDIF(F)
  STRINGTOKEYBOARDIF(G)
  STRINGTOKEYBOARDIF(H)
  STRINGTOKEYBOARDIF(I)
  STRINGTOKEYBOARDIF(J)
  STRINGTOKEYBOARDIF(K)
  STRINGTOKEYBOARDIF(L)
  STRINGTOKEYBOARDIF(M)
  STRINGTOKEYBOARDIF(N)
  STRINGTOKEYBOARDIF(O)
  STRINGTOKEYBOARDIF(P)
  STRINGTOKEYBOARDIF(Q)
  STRINGTOKEYBOARDIF(R)
  STRINGTOKEYBOARDIF(S)
  STRINGTOKEYBOARDIF(T)
  STRINGTOKEYBOARDIF(U)
  STRINGTOKEYBOARDIF(V)
  STRINGTOKEYBOARDIF(W)
  STRINGTOKEYBOARDIF(X)
  STRINGTOKEYBOARDIF(Y)
  STRINGTOKEYBOARDIF(Z)
  STRINGTOKEYBOARDIF(Num0)
  STRINGTOKEYBOARDIF(Num1)
  STRINGTOKEYBOARDIF(Num2)
  STRINGTOKEYBOARDIF(Num3)
  STRINGTOKEYBOARDIF(Num4)
  STRINGTOKEYBOARDIF(Num5)
  STRINGTOKEYBOARDIF(Num6)
  STRINGTOKEYBOARDIF(Num7)
  STRINGTOKEYBOARDIF(Num8)
  STRINGTOKEYBOARDIF(Num9)
  STRINGTOKEYBOARDIF(Escape)
  STRINGTOKEYBOARDIF(LControl)
  STRINGTOKEYBOARDIF(LShift)
  STRINGTOKEYBOARDIF(LAlt)
  STRINGTOKEYBOARDIF(LSystem)
  STRINGTOKEYBOARDIF(RControl)
  STRINGTOKEYBOARDIF(RShift)
  STRINGTOKEYBOARDIF(RAlt)
  STRINGTOKEYBOARDIF(RSystem)
  STRINGTOKEYBOARDIF(Menu)
  STRINGTOKEYBOARDIF(LBracket)
  STRINGTOKEYBOARDIF(RBracket)
  STRINGTOKEYBOARDIF(SemiColon)
  STRINGTOKEYBOARDIF(Comma)
  STRINGTOKEYBOARDIF(Period)
  STRINGTOKEYBOARDIF(Quote)
  STRINGTOKEYBOARDIF(Slash)
  STRINGTOKEYBOARDIF(BackSlash)
  STRINGTOKEYBOARDIF(Tilde)
  STRINGTOKEYBOARDIF(Equal)
  STRINGTOKEYBOARDIF(Dash)
  STRINGTOKEYBOARDIF(Space)
  STRINGTOKEYBOARDIF(Return)
  STRINGTOKEYBOARDIF(BackSpace)
  STRINGTOKEYBOARDIF(Tab)
  STRINGTOKEYBOARDIF(PageUp)
  STRINGTOKEYBOARDIF(PageDown)
  STRINGTOKEYBOARDIF(End)
  STRINGTOKEYBOARDIF(Home)
  STRINGTOKEYBOARDIF(Insert)
  STRINGTOKEYBOARDIF(Delete)
  STRINGTOKEYBOARDIF(Add)
  STRINGTOKEYBOARDIF(Subtract)
  STRINGTOKEYBOARDIF(Multiply)
  STRINGTOKEYBOARDIF(Divide)
  STRINGTOKEYBOARDIF(Left)
  STRINGTOKEYBOARDIF(Right)
  STRINGTOKEYBOARDIF(Up)
  STRINGTOKEYBOARDIF(Down)
  STRINGTOKEYBOARDIF(Numpad0)
  STRINGTOKEYBOARDIF(Numpad1)
  STRINGTOKEYBOARDIF(Numpad2)
  STRINGTOKEYBOARDIF(Numpad3)
  STRINGTOKEYBOARDIF(Numpad4)
  STRINGTOKEYBOARDIF(Numpad5)
  STRINGTOKEYBOARDIF(Numpad6)
  STRINGTOKEYBOARDIF(Numpad7)
  STRINGTOKEYBOARDIF(Numpad8)
  STRINGTOKEYBOARDIF(Numpad9)
  STRINGTOKEYBOARDIF(F1)
  STRINGTOKEYBOARDIF(F2)
  STRINGTOKEYBOARDIF(F3)
  STRINGTOKEYBOARDIF(F4)
  STRINGTOKEYBOARDIF(F5)
  STRINGTOKEYBOARDIF(F6)
  STRINGTOKEYBOARDIF(F7)
  STRINGTOKEYBOARDIF(F8)
  STRINGTOKEYBOARDIF(F9)
  STRINGTOKEYBOARDIF(F10)
  STRINGTOKEYBOARDIF(F11)
  STRINGTOKEYBOARDIF(F12)
  STRINGTOKEYBOARDIF(F13)
  STRINGTOKEYBOARDIF(F14)
  STRINGTOKEYBOARDIF(F15)
  STRINGTOKEYBOARDIF(Pause)

  if (key == "MLeft")
    return Player::Output(sf::Mouse::Left);
  if (key == "MRight")
    return Player::Output(sf::Mouse::Right);
  if (key == "MMiddle")
    return Player::Output(sf::Mouse::Middle);
  if (key == "MXButton1")
    return Player::Output(sf::Mouse::XButton1);
  if (key == "MXButton2")
    return Player::Output(sf::Mouse::XButton2);

  return Player::Output();
}

} // namespace Utility
