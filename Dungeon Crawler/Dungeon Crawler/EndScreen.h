#pragma once
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>

class EndScreen
{
	//end screen shape
	sf::RectangleShape screen_shape_;

	//textures of end screen
	sf::Texture lose_screen_texture_;
	sf::Texture win_screen_texture_;


public:
	//constructor
	EndScreen();

	//draw end screen -> win / lose
	void draw_the_end_screen_victory(sf::RenderWindow& window);
	void draw_the_end_screen_lose(sf::RenderWindow& window);

};

