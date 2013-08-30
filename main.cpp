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

class Test {
public:
  Test() {}
  int tttt(int a) { std::cout << "t(): " << a << std::endl; return 1;}
};

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
  BaseModEffect eff(EffectType::BASE_DAMAGE);
  for (auto& w : weapons) {
    eff.applyEffect(*w);
    w->toString();
  }

  //Test t1;
  //std::function<int(int)> f = std::bind(&Test::tttt, &t1, _1);
  //f(10);

  //std::map<std::string, std::function<void(std::string, std::string)>> callbacks;
  //callbacks["test"] = [] (const std::string& a, const std::string& b) {
  //  std::cout << "**** a = " << a << ", b = " << b << std::endl;
  //};
  //callbacks["test"]("string 1", "string 2");

  //std::string testXml = "<id>10</id>\n<abc>120</abc>";
  //std::string testXml = "<warframe><id>10</id>\n<abc>120</abc></warframe>";
  //auto size = testXml.length()+1;
  //char* testChPtr = (char *) malloc(sizeof(char) * size);
  //strncpy_s(testChPtr, size, testXml.c_str(), testXml.length());
  //xml_document<> doc;
  //try {
  //  doc.parse<0>(testChPtr);
  //} catch (const std::exception& e) {
  //  std::cout << "Caught exception: " << e.what() << std::endl;
  //  thr::sleep_for(std::chrono::seconds(10));
  //  return 1;
  //}
  //std::cout << doc; 
  //std::cout << "Name of my first node is: " << doc.first_node()->name() << std::endl;
  //std::cout << "Node id: " << doc.first_node("id")->value() << std::endl;

  //AssetFactory::addCtor("weapon", std::bind(&Weapon::Builder::makeWeapon));
  AssetFactory::addCtor("weapon", &Weapon::Builder::makeWeapon);
  auto w = unique_dynamic_cast<Weapon, IAsset>(AssetFactory::getCtor("weapon")());
  w->setName("testing dynamic cast");
  w->toString();
  //auto w = AssetFactory::getCtor("weapon")().release();
  //std::unique_ptr<Weapon> w_tmp2(dynamic_cast<Weapon*>(w));
  //auto w_tmp3 = w_tmp2.release();
  //w_tmp3->setName("test");
  //w_tmp3->toString();

  XmlObject x("weapons.xml");
  x.loadFile();
  //LOG(INFO) << "Done loading XML";
  //std::cout << "end" << std::endl;
  std::this_thread::sleep_for(std::chrono::seconds(10));

  //std::cout << std::endl;
}