#include "Ball.h"

void Ball::hold_inside_the_window_while_moving(unsigned int height, unsigned int width)
{
	ball.move(xy_velocity);
	if (get_left() <= 0)
		xy_velocity.x = speed;
	else if (get_right() >= width)
		xy_velocity.x = -speed;
	if (get_top() <= 0)
		xy_velocity.y = speed;

}