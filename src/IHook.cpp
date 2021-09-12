#include "IHook.hpp"
using namespace ImageCoverExpander;

/*
 * DEFINE IHOOK INTERFACE CLASS METHODS
 */

bool IHook::InstallHooks() {
    for (IHook* hook : IHook::hooks) {
        try {
            hook->AddHooks();
            getLogger().info("Installed %s Hook", hook->name.c_str());
        } catch (...) {
            return false;
        }
    }
    return true;
}

IHook::IHook(const std::string& name) {
    this->name = name;
    hooks.push_back(this);
}

void IHook::AddHooks() {
    getLogger().info("AddHooks method was not overridden for %s Hook", this->name.c_str());
}

std::vector<IHook*> IHook::hooks = std::vector<IHook*>();