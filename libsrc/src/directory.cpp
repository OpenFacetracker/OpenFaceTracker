#include <oft/directory.hpp>

namespace oft {

    Directory::Directory(const std::string& _name, const std::string& _location)
        : File(_name, "", _location, false) {}

    Directory::Directory(Directory const& obj)
        : File(obj) {}
    
    Directory::~Directory() {}
}