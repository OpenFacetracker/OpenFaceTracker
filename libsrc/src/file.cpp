#include <oft/file.hpp>

namespace oft {

    File::File() {}

    File::File(const std::string& _name, const std::string& _extension, const std::string& _location, bool flag)
        : name(_name), size(0), extension(_extension), location(_location), isFile(flag) {}

    File::File(File const& obj)
        : name(obj.name), size(obj.size), extension(obj.extension), location(obj.location), isFile(obj.isFile) {}

    std::string File::distn() const {
        std::string result;

        if (this->extension.empty() || this->extension.compare("") == 0) {
            #ifdef __linux__
                result = this->location + "/" + this->name;
            #elif defined _WIN32
                result = this->location + "\\" + this->name;
            #endif // ! __linux__ or _WIN32
        }
        else {
            #ifdef __linux__
                result = this->location + "/" + this->name + "." + this->extension;
            #elif defined _WIN32
                result = this->location + "\\" + this->name + "." + this->extension;
            #endif // ! __linux__ or _WIN32
        }

        return result;
    }
    
    File::~File() {}
}