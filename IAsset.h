#ifndef _IASSET_
#define _IASSET_

#include <string>

class IAsset {
public:
  virtual void setProperty(const std::string&, const std::string&) = 0;
  virtual operator std::string() const = 0;
};

#endif // !_IASSET_
