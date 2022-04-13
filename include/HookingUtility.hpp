#pragma once
#include "main.hpp"

#include "beatsaber-hook/shared/utils/hooking.hpp"

namespace ImageCoverExpander {
    class HookingUtility {
    private:
        inline static std::vector<void (*)(Logger &logger)> installFuncs;
    public:
        static void AddInstallFunc(void (*installFunc)(Logger &logger)) {
            installFuncs.push_back(installFunc);
        }

        static void InstallHooks(Logger &logger) {
            for (auto installFunc : installFuncs) {
                installFunc(logger);
            }
        }
    };
}
#define CoversInstallHooks(func) \
struct __CoverssRegister##func { \
    __CoversRegister##func() { \
       Covers::HookingUtility::AddInstallFunc(func); \
    } \
}; \
static __CoversRegister##func __CoversRegisterInstance##func