#include "EndScreen.h"

EndScreen::EndScreen()
{
	//rectangle for win/lose screen definition
	screen_shape_.setSize(sf::Vector2f(1200, 1200));
	screen_shape_.setFillColor(sf::Color::White);
	screen_shape_.setOrigin(screen_shape_.getSize().x / 2, screen_shape_.getSize().y / 2);
	screen_shape_.setPosition(0.0f, 0.0f);


	//win/loose screen
	lose_screen_texture_.loadFromFile("sprite/lose_screen1.png");
	win_screen_texture_.loadFromFile("sprite/win_screen.png");
}

void EndScreen::draw_the_end_screen_victory(sf::RenderWindow& window)
{
	screen_shape_.setTexture(&win_screen_texture_);
	window.draw(screen_shape_);
}

void EndScreen::draw_the_end_screen_lose(sf::RenderWindow& window)
{
	screen_shape_.setTexture(&lose_screen_texture_);
	window.draw(screen_shape_);

}
