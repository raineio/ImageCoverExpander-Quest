#include "main.hpp"
#include "IHook.hpp"
using namespace ImageCoverExpander;

#include "Hooks/StandardLevelDetailViewController_DidActivate_Hook.hpp"
using namespace ImageCoverExpander::Hooks;

#include "GlobalNamespace/StandardLevelDetailViewController.hpp"
#include "GlobalNamespace/MainMenuViewController.hpp"
using namespace GlobalNamespace;

#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Transform.hpp"
#include "UnityEngine/RectTransform.hpp"
using namespace UnityEngine;

#include "HMUI/ImageView.hpp"
using namespace HMUI;

std::string StandardLevelDetailViewController_DidActivate_Hook::GetName() {
    return "StandardLevelDetailViewController_DidActivate";
}

#define ARTWORK_ERROR(logger, transform) \
    logger.error("Error changing artwork fields for %s", to_utf8(csstrtostr(levelBarTransform->get_name())).c_str()); \
    return;

MAKE_HOOK_MATCH(StandardLevelDetailViewController_DidActivate, &GlobalNamespace::StandardLevelDetailViewController::DidActivate, void, GlobalNamespace::StandardLevelDetailViewController* self, bool firstActivation, bool addedToHeirarchy, bool screenSystemEnabling) {
    StandardLevelDetailViewController_DidActivate(self, firstActivation, addedToHeirarchy, screenSystemEnabling);

    auto levelBarTransform = self->get_transform()->Find(il2cpp_utils::newcsstr("LevelDetail"))->Find(il2cpp_utils::newcsstr("LevelBarBig"));
    if (!levelBarTransform) return;
    getLogger().info("Changing artwork for %s", to_utf8(csstrtostr(levelBarTransform->get_name())).c_str());

    // oh boy

    auto imageTransform = levelBarTransform->Find(il2cpp_utils::newcsstr("SongArtwork"))->GetComponent<RectTransform*>();
    if (!imageTransform) {ARTWORK_ERROR(getLogger(), levelBarTransform)}
    imageTransform->set_sizeDelta(Vector2(70.5f, 58.0f));
    imageTransform->set_localPosition(Vector3(-34.4f, -56.0f, 0.0f));
    imageTransform->SetAsFirstSibling();

    auto imageView = imageTransform->GetComponent<ImageView*>();
    if (!imageView) {ARTWORK_ERROR(getLogger(), levelBarTransform)}
    imageView->set_color(Color(0.5f, 0.5f, 0.5f, 1));
    imageView->set_preserveAspect(false);
    imageView->skew = 0.0f;


}

void StandardLevelDetailViewController_DidActivate_Hook::InstallHooks() {
    INSTALL_HOOK(getLogger(), StandardLevelDetailViewController_DidActivate);
    getLogger().info("Installed %s Hook", GetName().c_str());
}
