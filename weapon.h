#ifndef _WEAPON_H_
#define _WEAPON_H_

#include <iostream>
#include <string>
#include <memory>
#include <map>
#include <functional>

#include "IAsset.h"

class Weapon : public IAsset {
  public:
    enum DamageType { DT_NONE, ARMOR_PIERCE, BLADE, BULLET };
    static const std::map<const std::string, DamageType> kDamageTypeStrToEnum;
    static const std::map<DamageType, const std::string> kDamageTypeEnumToString;
    enum WeaponType { WT_NONE, PRIMARY, SECONDARY, MELEE };
    static const std::map<const std::string, WeaponType> kWeaponTypeStrToEnum;
    static const std::map<WeaponType, const std::string> kWeaponTypeEnumToStr;
    class Builder {
      private:
        std::unique_ptr<Weapon> weapon_;
      public:
        Builder() : weapon_(new Weapon()) {
        }
        inline Builder& setName(std::string name) {
          weapon_->setName(name);
          return *this;
        }
        inline Builder& setBaseDamage(uint32_t i) {
          weapon_->setDamage(i);
          return *this;
        }
        inline Builder& setCrit(double i) {
          weapon_->setCrit(i);
          return *this;
        }
        inline Builder& setCritDmg(double i) {
          weapon_->setCritDmg(i);
          return *this;
        }
        inline Builder& setBaseRoF(double i) {
          weapon_->setRoF(i);
          return *this;
        }
        inline Builder& setAccuracy(double i) {
          weapon_->setAccuracy(i);
          return *this;
        }
        inline Builder& setBaseClipSize(uint32_t i) {
          weapon_->setClipSize(i);
          return *this;
        }
        inline Builder& setBaseAmmoSize(uint32_t i) {
          weapon_->setAmmoSize(i);
          return *this;
        }
        inline Builder& setBaseReloadSpeed(double i) {
          weapon_->setReloadSpeed(i);
          return *this;
        }
        //Builder& setDamageType(DamageType i) {
        //  weapon_->setDamageType(i);
        //  return *this;
        //}
        //Builder& setWeaponTye(WeaponType i) {
        //  weapon_->setWeaponType(i);
        //  return *this;
        //}
        inline std::unique_ptr<Weapon> build() {
          return std::move(weapon_);
        }
        static inline std::unique_ptr<Weapon> makeWeapon() {
          return std::unique_ptr<Weapon>(new Weapon());
        }
    };
    Weapon()
      : name_(), damage_(0), crit_(0), critDmg_(0),
        rof_(0), accuracy_(0), clipSize_(0),
        ammoSize_(0), reloadSpeed_(0), damageType_(DT_NONE),
        weaponType_(WT_NONE) {}
    inline void setName(std::string name)    { name_ = name; }

    inline void setDamage(long i)            { damage_ = i; }
    void setDamageStr(std::string);

    inline void setCrit(double i)            { crit_ = i; }
    void setCritStr(std::string);

    inline void setCritDmg(double i)         { critDmg_ = i; }
    void setCritDmgStr(std::string);

    inline void setRoF(double i)             { rof_ = i; }
    void setRoFStr(std::string);

    inline void setAccuracy(double i)        { accuracy_ = i; }
    void setAccuracyStr(std::string);

    inline void setClipSize(uint32_t i)      { clipSize_ = i; }
    void setClipSizeStr(std::string);

    inline void setAmmoSize(uint32_t i)      { ammoSize_ = i; }
    void setAmmoSizeStr(std::string);

    inline void setReloadSpeed(double i)     { reloadSpeed_ = i; }
    void setReloadSpeedStr(std::string);

    inline void setDamageType(DamageType i)  { damageType_ = i; }
    void setDamageTypeStr(std::string);

    inline void setWeaponType(WeaponType i)  { weaponType_ = i; }
    void setWeaponTypeStr(std::string);

    const std::string getName() const { return name_; }

    void setProperty(const std::string&, const std::string&);
    operator std::string() const;

  private:
    std::string name_;
    uint32_t damage_;
    double crit_;
    double critDmg_;
    double rof_;
    double accuracy_;
    uint32_t clipSize_;
    uint32_t ammoSize_;
    double reloadSpeed_;
    DamageType damageType_;
    WeaponType weaponType_;
    static std::map<
      std::string,
      std::function<void(Weapon*, std::string)>
    > setterMap;
};

#endif
