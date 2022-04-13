#include "main.hpp"
#include "HookingUtility.hpp"
using namespace ImageCoverExpander;

#include "custom-types/shared/register.hpp"
using namespace custom_types;

#include "GlobalNamespace/StandardLevelDetailViewController.hpp"
using namespace GlobalNamespace;

#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Transform.hpp"
#include "UnityEngine/RectTransform.hpp"
using namespace UnityEngine;

#include "UnityEngine/UI/Button.hpp"
using namespace UnityEngine::UI;

#include "HMUI/ImageView.hpp"
using namespace HMUI;

// best library evvar
#include "sombrero/shared/Vector2Utils.hpp"
#include "sombrero/shared/Vector3Utils.hpp"
#include "sombrero/shared/ColorUtils.hpp"
#include "HookingUtility.hpp"

using namespace Sombrero; // very cool fern <3

#include <array>

static ModInfo modInfo; // Stores the ID and version of our mod, and is sent to the modloader upon startup

// Loads the config from disk using our modInfo, then returns it for use
Configuration& getConfig() {
    static Configuration config(modInfo);
    config.Load();
    return config;
}

// Returns a logger, useful for printing debug messages
Logger& getLogger() {
    static auto* logger = new Logger(modInfo);
    return *logger;
}

MAKE_HOOK_MATCH(StandardLevelDetailViewController_DidActivate,
                &GlobalNamespace::StandardLevelDetailViewController::DidActivate,
                void,
                GlobalNamespace::StandardLevelDetailViewController* self,
                bool firstActivation,
                bool addedToHeirarchy,
                bool screenSystemEnabling) {
    StandardLevelDetailViewController_DidActivate(self, firstActivation, addedToHeirarchy, screenSystemEnabling);

    auto ImageCoverTransform = self
            ->get_transform()->Find("LevelDetail/LevelBarBig/SongArtwork")->GetComponent<RectTransform*>();

    ImageCoverTransform->set_sizeDelta(FastVector2(70.5f, 58.0f));
    ImageCoverTransform->set_localPosition(FastVector3(-34.4f, -56.0f, 0.0f));
    ImageCoverTransform->SetAsFirstSibling();

    auto* imageView = ImageCoverTransform->GetComponent<ImageView*>();
    imageView->set_color(FastColor(0.5f, 0.5f, 0.5f, 1));
    imageView->set_preserveAspect(false);
    imageView->dyn__skew() = 0.0f;
}

// Called at the early stages of game loading
extern "C" void setup(ModInfo& info) {
    std::string ID = "ImageCoverExpander";
    info.id = ID;
    info.version = VERSION;
    modInfo = info;
	
    getConfig().Load(); // Load the config file
    getLogger().info("Completed setup!");
}

// Called later on in the game loading - a good time to install function hooks
extern "C" void load() {
    il2cpp_functions::Init();
    Register::AutoRegister(); // Custom Types

    INSTALL_HOOK(getLogger(), StandardLevelDetailViewController_DidActivate);
}