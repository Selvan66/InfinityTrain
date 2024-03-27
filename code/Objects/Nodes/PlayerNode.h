/** @file PlayerNode.h */
#pragma once

#include "App/Context.h"
#include "Effects/Animation.h"
#include "Objects/Nodes/Entity.h"
#include "Objects/Nodes/Pickup/Equipment/Special.h"
#include "Objects/Nodes/Pickup/Equipment/Weapon.h"
#include "Player/PlayerInfo.h"

class PlayerNode : public Entity {
public:
  enum Action {
    MoveUp,
    MoveDown,
    MoveLeft,
    MoveRight,
    Fire,
    Interact,
    Specials
  };

public:
  PlayerNode(Context& context, PlayerInfo& playerInfo);

  void makeAction(Action action);
  void pickup(std::unique_ptr<Pickup> pickup);
  bool pay(int price);
  bool updateStat(Stats::Type stat, int value);

  virtual sf::FloatRect getBoundingRect() const override;
  virtual bool damage(int points) override;

protected:
  virtual unsigned int getCategory() const override;
  virtual void drawCurrent(sf::RenderTarget& target,
                           sf::RenderStates states) const override;
  virtual void updateCurrent(sf::Time dt, CommandQueue& commands) override;

private:
  void fire();
  void interact();
  void special();
  void updateAnimation(sf::Time dt);
  void updateEquipedWeapon();
  void updateEquipedSpecial();
  void updateStats();
  void updateWeapon();

private:
  Context& mContext;
  PlayerInfo& mPlayerInfo;
  Command mFireCommand;
  bool mIsFire;
  Command mInteractCommand;
  bool mIsInteract;
  Command mSpecialCommand;
  bool mIsSpecial;
  Animation mAnimation;
  Weapon* mWeapon;
  Special* mSpecial;
  sf::Time mDamageDuration;
  bool mIsWeaponEquip;
  bool mIsSpecialEquip;
};
