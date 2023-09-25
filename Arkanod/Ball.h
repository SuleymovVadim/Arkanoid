#pragma once
#include <SFML/Graphics.hpp>
constexpr float default_speed{ 4.0f };

class Ball
{
protected:
	sf::CircleShape ball;
	float radius = 6.f;
public:
	void draw(sf::RenderTarget& game) { game.draw(ball); }
	float speed = 4.0f;
	sf::Vector2f xy_velocity = { speed, speed };
	Ball(int x, int y, sf::Color col = sf::Color::Black)
	{
		ball.setPosition(x, y);
		ball.setRadius(radius);
		ball.setFillColor(col);
		ball.setOrigin(radius, radius);
	}
	sf::Color get_color() { return ball.getFillColor(); }

	void hold_inside_the_window_while_moving(unsigned int height, unsigned int width);

	
	float get_left() { return ball.getPosition().x - radius; };
	float get_right() { return ball.getPosition().x + radius; };
	float get_top() { return ball.getPosition().y - radius; };
	float get_bottom() { return ball.getPosition().y + radius; };
	sf::Vector2f get_velocity() { return xy_velocity; }
	void set_position(int x, int y) { ball.setPosition(x, y); };
	void set_position(sf::Vector2f position) { ball.setPosition({ position.x, position.y - radius + speed }); }
	sf::Vector2f get_position() { return ball.getPosition(); };

	void move_left() { xy_velocity.x = -speed; };
	void move_right() { xy_velocity.x = speed; };
	void move_up() { xy_velocity.y = -speed; };
	void move_down() { xy_velocity.y = speed; };

	void change_velocity(float x_velocity, float y_velocity) { xy_velocity = { x_velocity, y_velocity }; }
	void increase_speed() { speed++; };
	void decrease_speed() { speed--; };
	void reset_speed() { speed = default_speed; };
	void bounce_x() { xy_velocity.x = -xy_velocity.x; };
	void set_color(sf::Color color) { ball.setFillColor(color); }
	bool operator==(Ball& ball1) { return get_position() == ball1.get_position() && get_color() == ball1.get_color(); }
};