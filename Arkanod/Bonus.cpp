#include "Bonus.h"

void Bonus::update_and_move()
{
	if (dropping)
	{
		rect.move(velocity);
		if (get_bottom() > windowHeight)
			set_activity_state(false);
	}

}

void Bonus::moving_block_action(std::vector<Moving_block>& moving_blocks)
{
	moving_blocks.emplace_back(windowWidth / 2, windowHeight / 2);
	moving_blocks.back().destroyed = false;
	moving_blocks.back().destructible = true;

}

void Bonus::extra_ball_action(std::vector<Ball>& balls)
{
	balls.emplace_back(windowWidth / 2 + 100, windowHeight / 2);
	balls.back().set_color(sf::Color::Magenta);
}

void Bonus::floor_action(sf::RenderTarget& window, Border& border)
{
	border.rect.setPosition(512, 760);
	border.draw(window);
}

void Bonus::reflect_balls(std::vector<Ball>& balls)
{
	for (auto& ball : balls)
		ball.bounce_x();
}

void Bonus::change_platform_width(Platform& platform)
{
	platform.widen();
	if (platform.rect.getSize().x > 220)
		platform.reset_width();
}

void Bonus::discard_extra_ball_action(std::vector<Ball>& balls)
{
	balls.clear();
	balls.emplace_back(300, 300);
}
