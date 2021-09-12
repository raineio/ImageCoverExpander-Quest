#pragma once

#include "main.hpp"

#include <string>
#include <vector>

namespace ImageCoverExpander {

    /*
     * DECLARE IHOOK INTERFACE CLASS
     */

    class IHook {
    private:
        static std::vector<IHook*> hooks;
    protected:
        std::string name;

    public:
        static bool InstallHooks();

        explicit IHook(const std::string& name);

        virtual void AddHooks();
    };
}