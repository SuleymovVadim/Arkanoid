#include "Platform.h"

void Platform::hold_inside_the_window_while_moving(int window_width)
{
    rect.move(x_velocity);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) && get_left() >= 0)
        x_velocity.x = -speed;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) && get_right() <= window_width)
        x_velocity.x = speed;
    else
        x_velocity.x = 0.f;
}

void Platform::widen()
{
    width += 10.f;
    rect.setSize({ width, height });
    rect.setOrigin(width / 2.f, height / 2.f);
}

void Platform::reset_width()
{
    width = platform_width;
    rect.setSize({ width, height });
    rect.setOrigin(width / 2.f, height / 2.f);
}