#pragma once
#include "Block.h"
#include "Ball.h"
#include "Platform.h"
#include "Rectangle_objects.h"
constexpr float bonus_width{ 10.f }, bonus_height{ 10.f };

enum class BONUS_TYPE
{
	NONE,
	MOVING_BLOCK,
	FLOOR,
	EXTRA_BALL,
	CHANGE_PLATFORM_WIDTH,
	REFLECT_BALL
};

class Bonus : public Rectangle_objects
{
	sf::Vector2f velocity{ 0, 4.f };
	bool active = false;
	bool dropping = false;
	bool floor_enable = false;
	BONUS_TYPE type = BONUS_TYPE::NONE;
public:
	Bonus(int _x, int _y) : Rectangle_objects(_x, _y, bonus_height, bonus_width, sf::Color::Green) {}
	void update_and_move();
	void set_type(BONUS_TYPE _type) { type = _type; }

	void set_position(int x, int y) { rect.setPosition(x, y); }
	void set_activity_state(bool _active) { active = _active; }
	void set_dropping_state(bool _dropping) { dropping = _dropping; }
	void set_floor_state(bool _floor) { floor_enable = _floor; }

	bool get_floor_state() { return floor_enable; }
	bool get_dropping_state() { return dropping; }
	bool get_activity_state() { return active; }

	void floor_action(sf::RenderTarget& window, Border& border);
	void moving_block_action(std::vector <Moving_block>& moving_blocks);
	void extra_ball_action(std::vector<Ball>& balls);
	void reflect_balls(std::vector<Ball>& balls);
	void change_platform_width(Platform& platform);

	void discard_extra_ball_action(std::vector<Ball>& balls);
};