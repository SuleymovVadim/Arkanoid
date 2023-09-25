#pragma once
#include "Rectangle_objects.h"
constexpr float block_width{ 45.f }, block_height{ 20.f }, moving_block_velocity{ 5.f };
constexpr int windowWidth{ 512 }, windowHeight{ 512 }, frameLimit{ 60 }, quantity_of_blocksX{ 8 }, quantity_of_blocksY{ 5 };

enum TYPE
{
	ORDINARY,
	BONUS_INSIDE,
	SPEED_INCREASING,
	WITH_HEALTH
};


class Block : public Rectangle_objects
{
public:
	int type = ORDINARY;
	bool destructible = true;
	bool destroyed = false;

	Block(int x, int y) : Rectangle_objects(x, y, block_height, block_width, sf::Color::Black) {};
	Block(int x, int y, int height, int width, sf::Color color) : Rectangle_objects(x, y, height, width, color) {};
	void set_type(int _type)
	{
		type = _type;
		switch (_type)
		{
		case WITH_HEALTH:
			destructible = true;
		default:
			break;
		}
	}
};

class Moving_block : public Block
{
	sf::Vector2f velocity{ moving_block_velocity, 0 };
public:
	Moving_block(int x, int y) : Block(x, y) { set_type(WITH_HEALTH); };
	void reflect_velocity() { velocity.x *= -1; }
	void update_and_move()
	{
		rect.move(velocity);
		if (get_left() <= 0 || get_right() >= windowWidth)
			reflect_velocity();
	}
};

class Border : public Block
{
public:
	Border() : Block(255, 255, 0, 1024, sf::Color::Red) {};
};
