#ifndef _ASSET_FACTORY_
#define _ASSET_FACTORY_

#include <functional>
#include <map>
#include <memory>
#include <string>

#include "IAsset.h"

class AssetFactory {
public:
  static void addCtor(std::string, std::function<std::unique_ptr<IAsset>()>);
  static std::function<std::unique_ptr<IAsset>()> getCtor(std::string name);
private:
  AssetFactory() {}
  static AssetFactory instance_;
  static std::map<std::string, std::function<std::unique_ptr<IAsset>()>> classMap;
};

#endif // !_ASSET_FACTORY_
