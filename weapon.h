#ifndef _WEAPON_H_
#define _WEAPON_H_

#include <iostream>
#include <string>
#include <memory>
#include <map>

class IAsset {
public:
  virtual void setProperty(const std::string&, const std::string&) = 0;
};

class AssetFactory {
public:
  static void addCtor(std::string, std::function<std::unique_ptr<IAsset>()>);
  static std::function<std::unique_ptr<IAsset>()> getCtor(std::string name);
private:
  AssetFactory () {}
  static AssetFactory instance_;
  static std::map<std::string, std::function<std::unique_ptr<IAsset>()>> classMap;
};

class Weapon : public IAsset {
  public:
    enum DamageType { DT_NONE, ARMOR_PIERCE, BLADE, BULLET };
    enum WeaponType { WT_NONE, PRIMARY, SECONDARY, MELEE };
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
          weapon_->setBaseDamage(i);
          return *this;
        }
        inline Builder& setCrit(double i) {
          weapon_->setBaseCrit(i);
          return *this;
        }
        inline Builder& setCritDmg(double i) {
          weapon_->setBaseCritDmg(i);
          return *this;
        }
        inline Builder& setBaseRoF(double i) {
          weapon_->setBaseRoF(i);
          return *this;
        }
        inline Builder& setAccuracy(double i) {
          weapon_->setAccuracy(i);
          return *this;
        }
        inline Builder& setBaseClipSize(uint32_t i) {
          weapon_->setBaseClipSize(i);
          return *this;
        }
        inline Builder& setBaseAmmoSize(uint32_t i) {
          weapon_->setBaseAmmoSize(i);
          return *this;
        }
        inline Builder& setBaseReloadSpeed(double i) {
          weapon_->setBaseReloadSpeed(i);
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
      : name_(), baseDamage_(0), baseCrit_(0), baseCritDmg_(0),
        baseRoF_(0), baseAccuracy_(0), baseClipSize_(0),
        baseAmmoSize_(0), baseReloadSpeed_(0), dmgType_(DT_NONE),
        weaponType_(WT_NONE) {}
    inline void setName(std::string name)    { name_ = name; }
    inline void setBaseDamage(long i)        { baseDamage_ = i; }
    inline void setBaseCrit(double i)        { baseCrit_ = i; }
    inline void setBaseCritDmg(double i)     { baseCritDmg_ = i; }
    inline void setBaseRoF(double i)         { baseRoF_ = i; }
    inline void setAccuracy(double i)        { baseAccuracy_ = i; }
    inline void setBaseClipSize(uint32_t i)  { baseClipSize_ = i; }
    inline void setBaseAmmoSize(uint32_t i)  { baseAmmoSize_ = i; }
    inline void setBaseReloadSpeed(double i) { baseReloadSpeed_ = i; }
    inline void setDamageType(DamageType i)  { dmgType_ = i; }
    inline void setWeaponType(WeaponType i)  { weaponType_ = i; }
    const std::string getName() const { return name_; }
    void toString();

    void setProperty(const std::string&, const std::string&);
  private:
    std::string name_;
    uint32_t baseDamage_;
    double baseCrit_;
    double baseCritDmg_;
    double baseRoF_;
    double baseAccuracy_;
    uint32_t baseClipSize_;
    uint32_t baseAmmoSize_;
    double baseReloadSpeed_;
    DamageType dmgType_;
    WeaponType weaponType_;
};
#endif
