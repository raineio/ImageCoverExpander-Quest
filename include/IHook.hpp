#pragma once

#include "main.hpp"

#include <string>

namespace ImageCoverExpander {
    class IHook {
    public:

        IHook() {
            getLogger().info("Creating %s Hook", GetName().c_str());
        }

        virtual void InstallHooks();

        virtual std::string GetName();
    };
}