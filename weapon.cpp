#include <functional>
#include <exception>

#include "weapon.h"

#include "glog/logging.h"

void Weapon::toString() {
  std::cout << "Name              :" << name_ << std::endl;
  std::cout << "Base damage       :" << baseDamage_ << std::endl;
  std::cout << "Base crit         :" << baseCrit_ << std::endl;
  std::cout << "Base crit dmg     :" << baseCritDmg_ << std::endl;
  std::cout << "Base RoF          :" << baseRoF_ << std::endl;
  std::cout << "Base clip size    :" << baseClipSize_ << std::endl;
  std::cout << "Base ammo size    :" << baseAmmoSize_ << std::endl;
  std::cout << "Base reload speed :" << baseReloadSpeed_ << std::endl;
  std::cout << "Base accuracy     :" << baseAccuracy_ << std::endl;
  std::cout << "Damage type       :" << baseDamage_ << std::endl;
  std::cout << "Weapon type       :" << baseDamage_ << std::endl;
}

void Weapon::setProperty(const std::string& prop,
    const std::string& value) {
  LOG(INFO) << "Weapon::setProperty() called with prop="
    << prop << ", value=" << value;
}

std::map<std::string, std::function<std::unique_ptr<IAsset>()>>
  AssetFactory::classMap;

void AssetFactory::addCtor(std::string name,
    std::function<std::unique_ptr<IAsset>()> f) {
  classMap[name] = f;
}

std::function<std::unique_ptr<IAsset>()>
    AssetFactory::getCtor(std::string name) {
  if (classMap.find(name) != classMap.end()) {
    return classMap[name];
  }
  throw "name %s not found in map";
}


