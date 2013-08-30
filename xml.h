#include <iostream>
#include <memory>

class XmlObject {
public:
  XmlObject(std::string filename) : filename_(filename) {}
  bool loadFile();
private:
  void parseBuff();
  std::string filename_;
  std::string buff_;
};