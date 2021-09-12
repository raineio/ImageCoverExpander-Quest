#pragma once

#include "IHook.hpp"
#include "main.hpp"
using namespace ImageCoverExpander;

namespace ImageCoverExpander::Hooks {
    class ArtworkExpander : IHook {
    public:



        void AddHooks() override;
        explicit ArtworkExpander(const std::string& name) : IHook(name) {}
    };
}