#include <iostream>
#include <fstream>
#include <thread>
#include <string>
#include <memory>
#include <list>
#include <cstdlib>
#include <map>
#include <string>
#include <functional>

#include "weapon.h"
#include "mod_effect.h"
#include "xml.h"
#include "asset_catalog.h"
#include "asset_factory.h"

#include "rapidxml/rapidxml.hpp"
#include "rapidxml/rapidxml_print.hpp"

#include "glog/logging.h"

using namespace std::placeholders;

template <typename D, typename S>
std::unique_ptr<D> unique_dynamic_cast(std::unique_ptr<S>& ptr) {
  auto t = ptr.release();
  std::unique_ptr<D> dst(dynamic_cast<D*>(t));
  if (!dst) ptr.reset(t);
  return dst;
}

int main(int argc, char* argv[]) {
  FLAGS_stderrthreshold = 0;
  google::InitGoogleLogging(argv[0]);

  LOG(INFO) << "Loading xml data";
  std::list<std::unique_ptr<Weapon>> weapons;
  weapons.push_back(std::unique_ptr<Weapon>(Weapon::Builder()
    .setName("Braton Prime")
    .setBaseDamage(25)
    .setCrit(2.5)
    .setCritDmg(150)
    .setAccuracy(11.25)
    .build()));
  weapons.push_back(std::unique_ptr<Weapon>(Weapon::Builder()
    .setName("Braton")
    .setBaseDamage(20)
    .setCrit(2.5)
    .setCritDmg(150)
    .setAccuracy(11.25)
    .build()));
  //BaseModEffect eff(EffectType::BASE_DAMAGE);
  //for (auto& w : weapons) {
  //  eff.applyEffect(*w);
  //  w->toString();
  //}

  AssetFactory::addCtor("weapon", &Weapon::Builder::makeWeapon);
  auto w = unique_dynamic_cast<Weapon, IAsset>(AssetFactory::getCtor("weapon")());
  //w->setName("testing dynamic cast");
  //std::cout << "==>" << std::string(*w);

  AssetCatalog<Weapon> weaponCatalog;
  weaponCatalog.set("test", std::unique_ptr<Weapon>(w.release()));
  //LOG(INFO) << "AssetCatalog.get(): " << weaponCatalog.get("test")->operator std::string() << std::endl;

  XmlObject weaponXml("weapons.xml");
  weaponXml.loadFile();

  LOG(INFO) << "Done loading XML";

  std::string yyy;
  std::cin >> yyy;
}