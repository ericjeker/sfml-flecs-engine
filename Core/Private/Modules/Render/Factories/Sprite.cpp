// Copyright (c) Eric Jeker 2025.

#include "SFE/Modules/Render/Factories/Sprite.h"

#include "SFE/GameService.h"
#include "SFE/Managers/ResourceManager.h"
#include "SFE/Modules/Render/Components/SpriteRenderable.h"
#include "SFE/Modules/Render/Components/Transform.h"
#include "SFE/Modules/Render/Components/ZOrder.h"


namespace Factories
{

flecs::entity Sprite::Create(const flecs::world& world, const SpriteParams& params)
{
    const auto texture = GameService::Get<ResourceManager>().GetResource<sf::Texture>(params.textureAsset);
    if (!texture)
    {
        return flecs::entity::null();
    }

    auto sprite = std::make_unique<sf::Sprite>(*texture);
    const auto size = texture->getSize();
    sprite->setOrigin({size.x * params.origin.x, size.y * params.origin.y});

    const auto entity = world.entity()
                            .set<Transform>({.position = params.position, .scale = params.scale, .rotation = params.rotation})
                            .set<ZOrder>({params.zOrder})
                            .set<SpriteRenderable>({std::move(sprite)});

    return entity;
}


} // namespace Factories
