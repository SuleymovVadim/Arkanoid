#pragma once

#include "Ball.h"
#include "Bonus.h"
#include "platform.h"
#include "Block.h"
#include <iostream>
#include <fstream>
#include <ctime>

enum STATES
{
	CONTINUE,
	OVER
};

class Game_manager
{
	sf::Clock clock;
	sf::Font font;
	sf::Text text_score;

	template <class T1, class T2> bool check_intersection(T1& object1, T2& object2);
	bool check_collision_block_n_ball(Block& block, Ball& ball);
	bool check_collision_platform_n_ball(Platform& platform, Ball& ball);
	void block_ball_collision_case(Block& block, Ball& ball);
	void check_collision_platform_bonus(Platform& platform, Bonus& bonus);
	bool check_collision_balls(Ball& ball1, Ball& ball2);
	bool check_collision_moving_blocks(Moving_block& block1, Moving_block& block2);
public:
	bool second_ball = false;
	int score = 0;
	int state = STATES::CONTINUE;
	sf::RenderWindow window{ sf::VideoMode(windowWidth, windowHeight), "Arkanoid", sf::Style::Titlebar | sf::Style::Close };

	std::vector<Bonus> bonuses;
	Border border;
	std::vector<Ball> balls;
	std::vector<Moving_block> moving_blocks;
	Platform platform{ windowWidth / 2.f, windowHeight - 30.f };
	std::vector<Block> blocks;

	Game_manager();

	void init_blocks();
	void draw_field();
	void update();

};

template<class T1, class T2> bool Game_manager::check_intersection(T1& object1, T2& object2)
{
	return object1.get_right() >= object2.get_left() && object1.get_left() <= object2.get_right() && object1.get_bottom() >= object2.get_top() && object1.get_top() <= object2.get_bottom();
}