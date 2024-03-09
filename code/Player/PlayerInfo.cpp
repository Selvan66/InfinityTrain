#include "Player/PlayerInfo.h"

PlayerInfo::PlayerInfo(Context& context)
  : stats(context), backpack(context), equipment(context, *this) {}