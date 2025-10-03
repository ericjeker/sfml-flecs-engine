// Copyright (c) Eric Jeker 2025.

#include "SFE/Modules/UI/UIModule.h"

#include "SFE/GameService.h"

#include "SFE/Modules/Window/Components/Event.h"
#include "SFE/Modules/Lifetime/Components/LifetimeOneFrame.h"
#include "SFE/Modules/Render/Components/Size.h"
#include "SFE/Modules/Render/Components/TextRenderable.h"
#include "SFE/Modules/Render/Components/Transform.h"
#include "SFE/Modules/UI/Components/ButtonBackground.h"
#include "SFE/Modules/UI/Components/ButtonText.h"
#include "SFE/Modules/UI/Components/Clickable.h"
#include "SFE/Modules/UI/Components/FocusGained.h"
#include "SFE/Modules/UI/Components/FocusLost.h"
#include "SFE/Modules/UI/Components/Hoverable.h"
#include "SFE/Modules/UI/Components/Interactable.h"
#include "SFE/Modules/UI/Components/KeyPressed.h"
#include "SFE/Modules/UI/Components/KeyReleased.h"
#include "SFE/Modules/UI/Components/MousePosition.h"
#include "SFE/Modules/UI/Components/MousePressed.h"
#include "SFE/Modules/UI/Components/MouseReleased.h"
#include "SFE/Modules/UI/Prefabs/Button.h"
#include "SFE/Modules/UI/Prefabs/FocusGainedEvent.h"
#include "SFE/Modules/UI/Prefabs/FocusLostEvent.h"
#include "SFE/Modules/UI/Prefabs/KeyPressedEvent.h"
#include "SFE/Modules/UI/Prefabs/KeyReleasedEvent.h"
#include "SFE/Modules/UI/Prefabs/MousePressedEvent.h"
#include "SFE/Modules/UI/Prefabs/MouseReleasedEvent.h"

namespace Core::Modules
{

UIModule::UIModule(const flecs::world& world)
{
    // --- Declare Prefabs ---
    world.prefab<Prefabs::MousePressedEvent>().add<LifetimeOneFrame>().add<MousePressed>();
    world.prefab<Prefabs::MouseReleasedEvent>().add<LifetimeOneFrame>().add<MouseReleased>();
    world.prefab<Prefabs::KeyPressedEvent>().add<LifetimeOneFrame>().add<KeyPressed>();
    world.prefab<Prefabs::KeyReleasedEvent>().add<LifetimeOneFrame>().add<KeyReleased>();
    world.prefab<Prefabs::FocusLostEvent>().add<LifetimeOneFrame>().add<FocusLost>();
    world.prefab<Prefabs::FocusGainedEvent>().add<LifetimeOneFrame>().add<FocusGained>();

    // --- Declare Components ---
    world.component<ButtonBackground>();
    world.component<ButtonText>();
    world.component<Clickable>();
    world.component<Hoverable>();
    world.component<Interactable>();
    world.component<TextRenderable>();

    // --- Declare Singletons ---
    world.singleton<MousePosition>();

    // --- Declare Systems ---

    // Update the mouse position every frame
    world.system("UIInputSystem").write<MousePosition>().kind(flecs::PostLoad).run([](const flecs::iter& it) {
        const auto& renderWindow = GameService::Get<sf::RenderWindow>();
        const auto pos = sf::Mouse::getPosition(renderWindow);
        it.world().set<MousePosition>({.position = pos});
    });

    // Handle mouse-released events and hit test on all the UI components
    world.system<const MouseReleased>("UIHitTest")
        // The UIHitTest need to be immediate to merge the world state so the intents are process within the same frame
        .immediate()
        .kind(flecs::PostLoad)
        .each([](const flecs::iter& it, size_t index, const MouseReleased& mouseReleased) {
            // We have a mouseReleased event. Now, find any clickable entities that were hit.
            if (mouseReleased.button != sf::Mouse::Button::Left)
            {
                return;
            }

            // Query the world for all entities that are Clickable and have the necessary components
            it.world().query<const Clickable, const Event, const Transform, const Size>().each(
                [&mouseReleased](const flecs::entity& e, const Clickable& clickable, const Event& eventTrigger, const Transform& t, const Size& s) {
                    sf::FloatRect bounds;
                    bounds.size = s.size;
                    bounds.position = t.position;

                    // Map the mouse position to world coordinates
                    const auto& window = GameService::Get<sf::RenderWindow>();
                    const auto worldPosition = window.mapPixelToCoords(mouseReleased.position, window.getView());

                    if (bounds.contains(sf::Vector2f(worldPosition)))
                    {
                        // The mouse press hit this clickable entity
                        eventTrigger.callback(e.world());
                    }
                }
            );
        });
}

} // namespace Modules
