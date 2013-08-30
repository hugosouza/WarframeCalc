#ifndef _MOD_EFFECT_H_
#define _MOD_EFFECT_H_

#include <iostream>

#include "weapon.h"

typedef enum EffectType {
  BASE_DAMAGE = 0,
  CRIT_CHANCE = 1,
  CRI_DAMAGE = 2,
};

class IModEffect {
public:
  IModEffect(EffectType ef) : effect_type_(ef) {}
  virtual ~IModEffect() {}
  virtual void applyEffect(const Weapon&) = 0;
protected:
  EffectType effect_type_;
};

class BaseModEffect : public IModEffect {
public:
  BaseModEffect(EffectType ef) : IModEffect(ef) {}
  ~BaseModEffect() {}
  void applyEffect(const Weapon& w) {
    std::cout << "applyEffect " << effect_type_ << " on " << w.getName() << std::endl;
  }
};
#endif
