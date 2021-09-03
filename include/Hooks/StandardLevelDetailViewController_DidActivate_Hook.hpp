#pragma once

#include "IHook.hpp"
#include "main.hpp"
using namespace ImageCoverExpander;

namespace ImageCoverExpander::Hooks {
    class StandardLevelDetailViewController_DidActivate_Hook : public IHook {
    public:
        StandardLevelDetailViewController_DidActivate_Hook() {
            getLogger().info("Creating %s Hook", GetName().c_str());
        }

        void InstallHooks() override;
        std::string GetName() override;
    };
}