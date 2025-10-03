// Copyright (c) Eric Jeker 2025.

#include "SFE/Modules/Render/Components/CircleRenderable.h"

#include <SFML/Graphics.hpp>

#include <iostream>

int main()
{
    std::cout << "Testing SFE Engine...\n";

    // Test that we can create engine components
    CircleRenderable circle;
    circle.shape.setRadius(50.f);
    circle.shape.setFillColor(sf::Color::Green);

    std::cout << "CircleRenderable created successfully!\n";
    std::cout << "Radius: " << circle.shape.getRadius() << "\n";

    // Add more tests for your engine features here

    return 0;
}
