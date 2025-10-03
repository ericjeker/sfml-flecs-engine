// Copyright (c) Eric Jeker 2025.

#pragma once

#include "SFE/Modules/Input/InputKey.h"

#include <unordered_map>


struct InputBindings
{
    std::unordered_map<InputKey, flecs::entity, InputKeyHash> map;
};


