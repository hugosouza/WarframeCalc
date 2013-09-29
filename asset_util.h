#ifndef _ASSET_UTIL_
#define _ASSET_UTIL_

#include <functional>
#include <string>
#include <map>

template <class T>
void setObjPropertyString(
    std::string value,
    T* asset,
    std::function<void(T*, std::string)> setter) {
  std::bind(setter, asset, value)();
  LOG(INFO) << "setObjProperty() string=" << value;
}

template <class T>
void setObjPropertyLong(
    std::string value,
    T *asset,
    std::function <void(T*, long)> setter) {
  long i = atoi(value.c_str());
  LOG(INFO) << "setObjProperty() long=" << i;
  std::bind(setter, asset, i)();
}

template <class T>
void setObjPropertyDouble(
    std::string value,
    T* asset,
    std::function<void(T*, double)> setter) {
  double i = atof(value.c_str());
  std::bind(setter, asset, i)();
  LOG(INFO) << "setObjProperty() double=" << value;
}

template <class T, class E>
void setObjPropertyEnum(
    const std::string value,
    T *asset,
    std::function <void(T*, E)> setter,
    const std::map<const std::string, E>& strToEnumMap) {
  auto v = strToEnumMap.find(value);
  if (v == strToEnumMap.end()) {
    LOG(ERROR) << "Type [" << value << "] not found in map";
    return;
  }
  std::bind(setter, asset, v->second)();
}

#endif
