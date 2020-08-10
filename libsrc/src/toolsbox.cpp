#include <oft/toolsbox.hpp>

namespace oft {
    
    ToolsBox::ToolsBox() 
        : flag(false) {}

    ToolsBox::ToolsBox(bool _flag)
        : flag(_flag) {}

    ToolsBox::ToolsBox(ToolsBox const& obj)
        : flag(obj.flag) {}

    ToolsBox::~ToolsBox() {}
}