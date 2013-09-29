#include "asset_factory.h"

std::map<std::string, std::function<std::unique_ptr<IAsset>()>>
  AssetFactory::classMap;

void AssetFactory::addCtor(std::string name,
  std::function<std::unique_ptr<IAsset>()> f) {
    classMap[name] = f;
}

std::function<std::unique_ptr<IAsset>()> AssetFactory::getCtor(std::string name) {
  if (classMap.find(name) != classMap.end()) {
    return classMap[name];
  }
  std::string msg = name + " not found in map";
  throw msg;
}
