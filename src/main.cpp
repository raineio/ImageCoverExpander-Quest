#include "main.hpp"

#include "GlobalNamespace/StandardLevelDetailViewController.hpp"

#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Transform.hpp"
#include "UnityEngine/Vector2.hpp"
#include "UnityEngine/Vector3.hpp"
#include "UnityEngine/RectTransform.hpp"
#include "UnityEngine/Color.hpp"

#include "HMUI/ImageView.hpp"

static ModInfo modInfo; // Stores the ID and version of our mod, and is sent to the modloader upon startup

// Loads the config from disk using our modInfo, then returns it for use
Configuration& getConfig() {
    static Configuration config(modInfo);
    config.Load();
    return config;
}

// Returns a logger, useful for printing debug messages
Logger& getLogger() {
    static Logger* logger = new Logger(modInfo);
    return *logger;
}

// Called at the early stages of game loading
extern "C" void setup(ModInfo& info) {
    info.id = ID;
    info.version = VERSION;
    modInfo = info;
	
    getConfig().Load(); // Load the config file
    getLogger().info("Completed setup!");
}

MAKE_HOOK_MATCH(StandardLevelDetailViewController_DidActivate, &GlobalNamespace::StandardLevelDetailViewController::DidActivate, void, GlobalNamespace::StandardLevelDetailViewController* self, bool firstActivation, bool addedToHeirarchy, bool screenSystemEnabling) {
    StandardLevelDetailViewController_DidActivate(self, firstActivation, addedToHeirarchy, screenSystemEnabling);

    if (!firstActivation) return;

    auto levelBarTransform = self->get_transform()->Find(il2cpp_utils::newcsstr("LevelDetail"))->Find(il2cpp_utils::newcsstr("LevelBarBig"));
    if (!levelBarTransform) return;
    getLogger().info("Changing artwork for %s", to_utf8(csstrtostr(levelBarTransform->get_name())).c_str());
    try {
        auto imageTransform = levelBarTransform->Find(il2cpp_utils::newcsstr("SongArtwork"))->GetComponent<UnityEngine::RectTransform*>();
        imageTransform->set_sizeDelta(UnityEngine::Vector2(70.5f, 58.0f));
        imageTransform->set_localPosition(UnityEngine::Vector3(-34.4f, -56.0f, 0.0f));
        imageTransform->SetAsFirstSibling();

        auto imageView = imageTransform->GetComponent<HMUI::ImageView*>();
        imageView->set_color(UnityEngine::Color(UnityEngine::Color(0.5f, 0.5f, 0.5f, 1)));
        imageView->set_preserveAspect(false);
    }
    catch (...) {

    }
}

// Called later on in the game loading - a good time to install function hooks
extern "C" void load() {
    il2cpp_functions::Init();

    getLogger().info("Installing hooks...");
    INSTALL_HOOK(getLogger(), StandardLevelDetailViewController_DidActivate);
    getLogger().info("Installed all hooks!");
}