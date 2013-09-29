#ifndef _ASSETCATALOG_
#define _ASSETCATALOG_

#include <memory>
#include <string>

template <class E>
class AssetCatalog {
public:
  std::unique_ptr<E> get(std::string);
  void set(std::string, std::unique_ptr<E>);
private:
  std::map<std::string, std::unique_ptr<E>> assets_;
};

template <class E>
std::unique_ptr<E> AssetCatalog<E>::get(std::string name) {
  if (assets_.find(name) == assets_.end()) {
    return std::unique_ptr<E>();
  }
  return assets_.find(name)->second;
}

template <class E>
void AssetCatalog<E>::set(std::string name, std::unique_ptr<E> asset) {
  assets_[name] = std::move(asset);
}

#endif // !_ASSETCATALOG_
