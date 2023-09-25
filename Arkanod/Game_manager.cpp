#include "Game_manager.h"
#include "math.h"

bool Game_manager::check_collision_block_n_ball(Block& block, Ball& ball)
{
	if (!check_intersection(block, ball))
		return false;

	block_ball_collision_case(block, ball);

	bool check_left_direction = fabs(ball.get_right() - block.get_left()) < fabs(block.get_right() - ball.get_left());
	bool check_top_direction = fabs(ball.get_bottom() - block.get_top()) < fabs(block.get_bottom() - ball.get_top());

	float directionX = check_left_direction ? ball.get_right() - block.get_left() : block.get_right() - ball.get_left();


	float directionY = check_top_direction ? ball.get_bottom() - block.get_top() : block.get_bottom() - ball.get_top();

	if (fabs(directionX) < fabs(directionY))
		check_left_direction ? ball.move_left() : ball.move_right();
	else
		check_top_direction ? ball.move_up() : ball.move_down();

	return true;

}



bool Game_manager::check_collision_platform_n_ball(Platform& platform, Ball& ball)
{
	if (!check_intersection(platform, ball))
		return false;
	ball.change_velocity(ball.get_position().x < platform.get_position().x ? -ball.speed : ball.speed, -ball.speed);
}

void Game_manager::block_ball_collision_case(Block& block, Ball& ball)
{
	switch (block.type)
	{
	case ORDINARY:
		block.destroyed = true;
		score++;
	case BONUS_INSIDE:
		bonuses.emplace_back(block.get_position().x, block.get_position().y);
		bonuses.back().set_dropping_state(true);
		block.destroyed = true;
		break;
	case SPEED_INCREASING:
		ball.increase_speed();
		block.destroyed = true;
		score++;
	case WITH_HEALTH:
		block.destroyed = block.rect.getFillColor() == sf::Color::Green;
		block.rect.setFillColor(sf::Color::Green);
		score++;
	default:
		break;
	}
	
}

void Game_manager::check_collision_platform_bonus(Platform& platform, Bonus& bonus)
{
	if (!check_intersection(platform, bonus))
		return;
	else if (!bonus.get_activity_state())
	{
		bonus.set_activity_state(true);
		switch (rand() % 5)
		{
		case 0:
			bonus.set_type(BONUS_TYPE::MOVING_BLOCK);
			bonus.moving_block_action(moving_blocks);
			break;
		case 1:
			bonus.set_type(BONUS_TYPE::FLOOR);
			bonus.floor_action(window, border);
			bonus.set_floor_state(true);
			break;
		case 2:
			if (second_ball == false)
			{
				bonus.set_type(BONUS_TYPE::EXTRA_BALL);
				bonus.extra_ball_action(balls);
				second_ball = true;
			}
			break;
		case 3:
			bonus.set_type(BONUS_TYPE::CHANGE_PLATFORM_WIDTH);
			bonus.change_platform_width(platform);
			break;
		case 4:
			bonus.set_type(BONUS_TYPE::REFLECT_BALL);
			bonus.reflect_balls(balls);
			break;
		default:
			break;
		}
	}


}

bool Game_manager::check_collision_balls(Ball& ball1, Ball& ball2)
{
	if (!check_intersection(ball1, ball2))
		return false;

	float overlapLeft = ball1.get_right() - ball2.get_left();
	float overlapRight = ball2.get_right() - ball1.get_left();
	float overlapTop = ball1.get_bottom() - ball2.get_top();
	float overlapBottom = ball2.get_bottom() - ball1.get_top();

	bool check_left_direction = abs(ball1.get_right() - ball2.get_left()) < abs(ball2.get_right() - ball1.get_left());
	bool check_top_direction = abs(ball1.get_bottom() - ball2.get_top()) < abs(ball2.get_bottom() - ball1.get_top());

	float directionX = check_left_direction ? abs(ball1.get_right() - ball2.get_left()) : abs(ball2.get_right() - ball1.get_left());

	float directionY = check_top_direction ? abs(ball1.get_bottom() - ball2.get_top()) : abs(ball2.get_bottom() - ball1.get_top());

	if (directionX < directionY)
	{
		ball1.xy_velocity.x = (check_left_direction ? -abs(ball1.xy_velocity.x) : abs(ball1.xy_velocity.y));
		ball2.xy_velocity.x = (check_left_direction ? abs(ball2.xy_velocity.y) : -abs(ball2.xy_velocity.x));
	}
	else
	{
		ball1.xy_velocity.y = (check_top_direction ? -abs(ball1.xy_velocity.x) : abs(ball1.xy_velocity.y));
		ball2.xy_velocity.y = (check_top_direction ? abs(ball2.xy_velocity.y) : -abs(ball2.xy_velocity.x));
	}
}

bool Game_manager::check_collision_moving_blocks(Moving_block& block1, Moving_block& block2)
{
	if (!check_intersection(block1, block2)) 
	{
		return false;
	}
	block1.reflect_velocity();
	block2.reflect_velocity();
}


Game_manager::Game_manager()
{
	window.setFramerateLimit(60);
	
	text_score.setPosition(sf::Vector2f(windowWidth - 100, 15));
	text_score.setCharacterSize(20);
	text_score.setFillColor(sf::Color::Blue);
	balls.emplace_back(300, 300);
}

void Game_manager::init_blocks()
{
	blocks.clear();
	for (int i = 1; i < (int)quantity_of_blocksY; i++)
		for (int j = 0; j < (int)quantity_of_blocksX; j++)
		{
			blocks.emplace_back((j + 1) * (block_width + 13), (i + 1) * (block_height + 5));
		}

	for (auto& block : blocks)
	{
		switch (rand() % 7)
		{
		
		case 0:
			block.type = BONUS_INSIDE;
			break;
		case 1:
			block.type = SPEED_INCREASING;
			break;
		case 2:
			block.type = WITH_HEALTH;
			break;
		default:
			block.type = ORDINARY;
			break;
		}

	}


	platform.reset_width();
	for (auto& ball : balls)
	{
		ball.reset_speed();
		ball.set_position(300, 300);
	}
}


void Game_manager::draw_field()
{
	window.clear(sf::Color::White);
	for (auto& block : blocks)
		block.draw(window);

	for (auto& ball : balls)
		ball.draw(window);

	for (auto& block_m : moving_blocks)
		block_m.draw(window);
	for (auto& bonus : bonuses)
	{

		if (bonus.get_dropping_state())
			bonus.draw(window);
		if (bonus.get_floor_state())
			border.draw(window);
	}
	
	platform.draw(window);
	window.display();
}


void Game_manager::update()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
	{
		init_blocks();
		state = STATES::CONTINUE;
		sf::sleep(sf::seconds(2));
		return;
	}
	platform.hold_inside_the_window_while_moving(windowWidth);
	for (auto& bonus : bonuses)
		bonus.update_and_move();

	for (auto& ball : balls)
	{
		ball.hold_inside_the_window_while_moving(windowHeight, windowWidth);

		if (ball.get_bottom() >= windowHeight)
		{
			balls.clear();
			balls.emplace_back(300, 300);
			balls.back().set_color(sf::Color::Black);
			moving_blocks.clear();
			second_ball = false;
			state = STATES::OVER;
			score -= 10;
		}

		if (check_collision_platform_n_ball(platform, ball))
		{

		}
		for (auto& bonus : bonuses)
			check_collision_platform_bonus(platform, bonus);
		if (check_collision_block_n_ball(border, ball) && border.destroyed)
			border.rect.setPosition(2000, 2000);

		auto it = blocks.begin();
		for (auto& block : blocks)
		{
			if (check_collision_block_n_ball(block, ball) && block.destroyed)
			{
				blocks.erase(it);
				break;
			}
			it++;
		}
		auto it_mov = moving_blocks.begin();
		for (auto& block : moving_blocks)
		{
			block.update_and_move();
			if (check_collision_block_n_ball(block, ball) && block.destroyed)
			{
				moving_blocks.erase(it_mov);
				break;
			}
			for (auto& other : moving_blocks)
				check_collision_moving_blocks(block, other);
			it_mov++;
		}

	}
}