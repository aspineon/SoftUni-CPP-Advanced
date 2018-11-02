#ifndef CPP_ADVANCED_DIRECTORY_H
#define CPP_ADVANCED_DIRECTORY_H

#include <vector>
#include <algorithm>

#include "FileSystemObjectsContainer.h"

using ObjectPtr = std::shared_ptr<FileSystemObject>;
using Objects = std::vector<ObjectPtr>;

class Directory : public FileSystemObject, public FileSystemObjectsContainer {
private:
  Objects items{ };

public:
  explicit Directory(std::string name) : FileSystemObject(std::move(name)) { }

  void add(const ObjectPtr& obj) override {
    this->items.push_back(obj);
  }

  Objects::const_iterator begin() const override {
    return this->items.begin();
  }

  Objects::const_iterator end() const override {
    return this->items.end();
  }

  size_t getSize() const override {
    size_t totalSize = 0;
    for (const auto& file : this->items) {
      totalSize += file->getSize();
    }
    return totalSize;
  }

  void remove(ObjectPtr obj) override {
    this->items.erase(std::find(this->items.begin(), this->items.end(), obj));
  }

  ObjectPtr getItemByName(const std::string& name) {
    auto it = std::find_if(this->items.begin(), this->items.end(),
                           [&name](const ObjectPtr& obj) { return obj->getName() == name; });
    return (it != this->items.end()) ? *it : nullptr;
  }
};

#endif //CPP_ADVANCED_DIRECTORY_H