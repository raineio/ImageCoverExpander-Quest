#include "main.hpp"

#include "Hooks/ArtworkExpander.hpp"
using namespace ImageCoverExpander::Hooks;

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
using namespace Sombrero; // very cool fern <3


#define ARTWORK_ERROR(logger, transform) \
    logger.error("Error changing artwork fields for %s", to_utf8(csstrtostr(levelBarTransform->get_name())).c_str()); \
    return;

MAKE_HOOK_MATCH(StandardLevelDetailViewController_DidActivate,
                &GlobalNamespace::StandardLevelDetailViewController::DidActivate,
                void,
                GlobalNamespace::StandardLevelDetailViewController* self,
                bool firstActivation,
                bool addedToHeirarchy,
                bool screenSystemEnabling) {
    StandardLevelDetailViewController_DidActivate(self, firstActivation, addedToHeirarchy, screenSystemEnabling);

    auto levelBarTransform = self->get_transform()->Find("LevelDetail")->Find("LevelBarBig");
    if (!levelBarTransform) return;
    getLogger().info("Changing artwork for %s", to_utf8(csstrtostr(levelBarTransform->get_name())).c_str());

    // oh boy

    auto* imageTransform = levelBarTransform->Find("SongArtwork")->GetComponent<RectTransform*>();
    if (!imageTransform) {
        ARTWORK_ERROR(getLogger(), levelBarTransform)
    }
    imageTransform->set_sizeDelta(FastVector2(70.5f, 58.0f));
    imageTransform->set_localPosition(FastVector3(-34.4f, -56.0f, 0.0f));
    imageTransform->SetAsFirstSibling();

    auto* imageView = imageTransform->GetComponent<ImageView*>();
    if (!imageView) {
        ARTWORK_ERROR(getLogger(), levelBarTransform)
    }
    imageView->set_color(FastColor(0.5f, 0.5f, 0.5f, 1));
    imageView->set_preserveAspect(false);
    imageView->dyn__skew() = 0.0f;
}

void ArtworkExpander::AddHooks() {
    INSTALL_HOOK(getLogger(), StandardLevelDetailViewController_DidActivate)
}
