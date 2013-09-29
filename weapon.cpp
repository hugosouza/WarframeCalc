#include "weapon.h"

#include <functional>
#include <exception>

#include "glog/logging.h"

#include "asset_util.h"
#include "asset_factory.h"

const std::map<const std::string, Weapon::DamageType>
  Weapon::kDamageTypeStrToEnum = {
    { "DT_NONE", Weapon::DamageType::DT_NONE },
    { "ARMOR_PIERCE", Weapon::DamageType::ARMOR_PIERCE },
    { "BLADE", Weapon::DamageType::BLADE },
    { "BULLET", Weapon::DamageType::BULLET },
};

const std::map<Weapon::DamageType, const std::string>
  Weapon::kDamageTypeEnumToString = {
    { Weapon::DamageType::DT_NONE, "DT_NONE" },
    { Weapon::DamageType::ARMOR_PIERCE, "ARMOR_PIERCE" },
    { Weapon::DamageType::BLADE, "BLADE" },
    { Weapon::DamageType::BULLET, "BULLET" },
};

const std::map<const std::string, Weapon::WeaponType>
  Weapon::kWeaponTypeStrToEnum = {
    { "WT_NONE", Weapon::WeaponType::WT_NONE },
    { "PRIMARY", Weapon::WeaponType::PRIMARY },
    { "SECONDARY", Weapon::WeaponType::SECONDARY },
    { "MELEE", Weapon::WeaponType::MELEE },
};

const std::map<Weapon::WeaponType, const std::string>
  Weapon::kWeaponTypeEnumToStr = {
    { Weapon::WeaponType::WT_NONE, "WT_NONE" },
    { Weapon::WeaponType::PRIMARY, "PRIMARY" },
    { Weapon::WeaponType::SECONDARY, "SECONDARY" },
    { Weapon::WeaponType::MELEE, "MELEE" },
};

std::map<std::string, std::function<void(Weapon*, std::string)>>
  Weapon::setterMap = {
    { "name",         std::mem_fn(&Weapon::setName) },
    { "damage",       std::mem_fn(&Weapon::setDamageStr) },
    { "critChance",   std::mem_fn(&Weapon::setCritStr) },
    { "critDamage",   std::mem_fn(&Weapon::setCritDmgStr) },
    { "rof",          std::mem_fn(&Weapon::setRoFStr) },
    { "accuracy",     std::mem_fn(&Weapon::setAccuracyStr) },
    { "clipsize",     std::mem_fn(&Weapon::setClipSizeStr) },
    { "ammosize",     std::mem_fn(&Weapon::setAmmoSizeStr) },
    { "reloadspeed",  std::mem_fn(&Weapon::setReloadSpeedStr) },
    { "damagetype",   std::mem_fn(&Weapon::setDamageTypeStr) },
    { "weapontype",   std::mem_fn(&Weapon::setWeaponTypeStr) },
};

Weapon::operator std::string() const {
  std::stringstream ss;
  ss << "Name              :" << name_ << std::endl;
  ss << "Base damage       :" << damage_ << std::endl;
  ss << "Base crit         :" << crit_ << std::endl;
  ss << "Base crit dmg     :" << critDmg_ << std::endl;
  ss << "Base RoF          :" << rof_ << std::endl;
  ss << "Base clip size    :" << clipSize_ << std::endl;
  ss << "Base ammo size    :" << ammoSize_ << std::endl;
  ss << "Base reload speed :" << reloadSpeed_ << std::endl;
  ss << "Base accuracy     :" << accuracy_ << std::endl;
  ss << "damage type       :"
    << kDamageTypeEnumToString.find(damageType_)->second
    << std::endl;
  ss << "weapon type       :"
    << kWeaponTypeEnumToStr.find(weaponType_)->second
    << std::endl;
  return ss.str();
}

void Weapon::setProperty(const std::string& prop,
    const std::string& value) {
  LOG(INFO) << "Weapon::setProperty() called with prop="
    << prop << ", value=" << value;
  if (setterMap.find(prop) != setterMap.end()) {
    LOG(INFO) << "found setter in map for " << prop << std::endl;
    std::bind(setterMap[prop], this, value)();
    std::cout << "New name [" << getName() << "]" << std::endl;
  }
}

void Weapon::setDamageStr(std::string damage) {
  setObjPropertyLong<Weapon>(damage, this, std::mem_fn(&Weapon::setDamage));
}

void Weapon::setCritStr(std::string damage) {
  setObjPropertyDouble<Weapon>(damage, this, std::mem_fn(&Weapon::setCrit));
}

void Weapon::setCritDmgStr(std::string damage) {
  setObjPropertyDouble<Weapon>(damage, this, std::mem_fn(&Weapon::setCritDmg));
}

void Weapon::setRoFStr(std::string rof) {
  setObjPropertyDouble<Weapon>(rof, this, std::mem_fn(&Weapon::setRoF));
}

void Weapon::setAccuracyStr(std::string accuracy) {
  setObjPropertyDouble<Weapon>(accuracy, this, std::mem_fn(&Weapon::setAccuracy));
}

void Weapon::setClipSizeStr(std::string clipsize) {
  setObjPropertyLong<Weapon>(clipsize, this, std::mem_fn(&Weapon::setClipSize));
}

void Weapon::setAmmoSizeStr(std::string ammosize) {
  setObjPropertyLong<Weapon>(ammosize, this, std::mem_fn(&Weapon::setAmmoSize));
}

void Weapon::setReloadSpeedStr(std::string reloadspeed) {
  setObjPropertyLong<Weapon>(reloadspeed, this, std::mem_fn(&Weapon::setReloadSpeed));
}

void Weapon::setDamageTypeStr(std::string damagetype) {
  setObjPropertyEnum<Weapon, Weapon::DamageType>(damagetype, this,
    std::mem_fn(&Weapon::setDamageType),
    Weapon::kDamageTypeStrToEnum);
}

void Weapon::setWeaponTypeStr(std::string weaponType) {
  setObjPropertyEnum<Weapon, Weapon::WeaponType>(weaponType, this,
    std::mem_fn(&Weapon::setWeaponType),
    Weapon::kWeaponTypeStrToEnum);
}
