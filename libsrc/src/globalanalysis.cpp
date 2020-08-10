#include <oft/globalanalysis.hpp>

namespace oft {
    
    GlobalAnalysis::GlobalAnalysis() {}

    GlobalAnalysis::GlobalAnalysis(bool _fuse)
        : fuse(_fuse) {}

    GlobalAnalysis::GlobalAnalysis(GlobalAnalysis const& obj)
        : fuse(obj.fuse) {}
    
    GlobalAnalysis::~GlobalAnalysis() {}
}