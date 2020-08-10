#include <oft/handlerjson.hpp>

namespace oft {
    
    HandlerJson::HandlerJson(bool _flag) 
        : ToolsBox(_flag) {}

    HandlerJson::HandlerJson(HandlerJson const& obj)
        : ToolsBox(obj) {}

    void HandlerJson::stop() {
        this->flag = false;
    }
    
    HandlerJson::~HandlerJson() {}
}