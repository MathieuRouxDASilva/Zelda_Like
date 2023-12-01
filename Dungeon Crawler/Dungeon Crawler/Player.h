#pragma once
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>

class Player
{
	//all rectangle shapes in player.h
	sf::RectangleShape player_shape_;
	sf::RectangleShape health_bar_shape_;

	//all textures in player.h 
	sf::Texture player_right_texture_;
	sf::Texture player_left_texture_;
	sf::Texture player_up_texture_;
	sf::Texture player_down_texture_;
	sf::Texture full_health_;

	//hp
	int number_of_lives_;

	//what view system needs
	bool is_camera_center_;
	sf::View view_;

public:
	//constructor
	Player();
	//moove player
	void player_mouvement(sf::Vector2f& delta);
	//draw player
	void draw_player(sf::RenderWindow& window);
	//take a dmg -> number of lives - 1
	void take_one_damage();
	//draw hp "HUD"
	void draw_hp(sf::RenderWindow& window);
	//view setupp
	void setupp_view(sf::RenderWindow& window);


	//getteur/setteur
	int GetNumberOfLives() { return number_of_lives_; }
	sf::Vector2f GetPosition() { return player_shape_.getPosition(); }
	sf::Vector2f GetSize() { return player_shape_.getSize(); }
	sf::RectangleShape GetShape() { return player_shape_; }
	void SetPosition(sf::Vector2f position) { player_shape_.setPosition(position); }

};

