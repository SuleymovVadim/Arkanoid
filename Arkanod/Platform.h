#pragma once
#include "Rectangle_objects.h"
constexpr float platform_width{ 100.f }, platform_height{ 18.f };

class Platform : public Rectangle_objects
{
protected:
	float speed = 13.f;
	sf::Vector2f x_velocity{ speed, 0 };
public:
	Platform(int x, int y) : Rectangle_objects(x, y, platform_height, platform_width, sf::Color::Black) {};
	void hold_inside_the_window_while_moving(int width);
	void widen();
	void reset_width();
	sf::Vector2f get_velocity() { return x_velocity; }

};