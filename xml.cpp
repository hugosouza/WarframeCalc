#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <thread>

#include <glog/logging.h>

#include "rapidxml/rapidxml.hpp"
#include "rapidxml/rapidxml_print.hpp"

#include "xml.h"
#include "weapon.h"
#include "asset_factory.h"

bool XmlObject::loadFile() {
  std::ifstream file;
  LOG(INFO) << "Loading: " << filename_;
  file.open(filename_, std::ios::in);
  if (file.is_open()) {
    buff_ = std::move(std::string(std::istreambuf_iterator<char>(file),
      std::istreambuf_iterator<char>()));
    parseBuff();
  } else {
    LOG(ERROR) << "file isn't opened";
  }
  return true;
}

void XmlObject::parseBuff() {
  auto size = buff_.length();
  std::unique_ptr<char> t(
    (char *) malloc(sizeof(char) * (size+1)));
  strncpy_s(t.get(), size+1, buff_.c_str(), size);
  rapidxml::xml_document<> doc;
  try {
    doc.parse<0>(t.get());
    auto node = doc.first_node();
    for (auto n = node->first_node(); n; n = n->next_sibling()) {
      auto wpn = AssetFactory::getCtor(n->name())();
      for (auto i = n->first_node(); i; i = i->next_sibling()) {
        wpn->setProperty(i->name(), i->value());
      }
      std::cout << "Weapon loaded: " << std::endl  << std::string(*wpn) << std::endl;
    }
  } catch (const std::exception& e) {
    std::cout << "Caught exception: " << e.what() << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(10));
  }
}