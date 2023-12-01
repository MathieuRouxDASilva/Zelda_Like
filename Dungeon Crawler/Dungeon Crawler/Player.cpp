#include "Player.h"
#include <SFML/Window/Keyboard.hpp>
#define SIZE_PXL_TILE 80


Player::Player()
{
	//hp setupp
	full_health_.loadFromFile("sprite/full_hearth1.png");
	health_bar_shape_.setSize(sf::Vector2f(50, 50));
	health_bar_shape_.setFillColor(sf::Color::White);
	health_bar_shape_.setTexture(&full_health_);
	number_of_lives_ = 3;

	//Player setupp
	player_right_texture_.loadFromFile("sprite/character_right.png");
	player_left_texture_.loadFromFile("sprite/character_left.png");
	player_up_texture_.loadFromFile("sprite/character_up.png");
	player_down_texture_.loadFromFile("sprite/character_down.png");

	player_shape_.setSize(sf::Vector2f(20.0f, 20.0f));
	player_shape_.setFillColor(sf::Color::White);
	player_shape_.setTexture(&player_right_texture_);
	player_shape_.setOrigin(player_shape_.getSize().x / 2, player_shape_.getSize().y);

	is_camera_center_ = true;
}

void Player::player_mouvement(sf::Vector2f& delta)
{
	constexpr float player_speed = 1;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		delta += sf::Vector2f(-player_speed * 40, 0);
		player_shape_.setTexture(&player_left_texture_);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		delta += sf::Vector2f(player_speed * 40, 0);
		player_shape_.setTexture(&player_right_texture_);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		delta += sf::Vector2f(0, -player_speed * 40);
		player_shape_.setTexture(&player_up_texture_);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		delta += sf::Vector2f(0, player_speed * 40);
		player_shape_.setTexture(&player_down_texture_);
	}
}

void Player::draw_player(sf::RenderWindow& window)
{
	window.draw(player_shape_);
}

void Player::take_one_damage()
{
	number_of_lives_--;
}

void Player::draw_hp(sf::RenderWindow& window)
{
	if (number_of_lives_ == 3)
	{
		health_bar_shape_.setPosition(view_.getCenter().x + window.getSize().x / 2 - SIZE_PXL_TILE, view_.getCenter().y - window.getSize().y / 2 + SIZE_PXL_TILE);
		window.draw(health_bar_shape_);
		health_bar_shape_.setPosition(view_.getCenter().x + window.getSize().x / 2 - SIZE_PXL_TILE * 1.5f, view_.getCenter().y - window.getSize().y / 2 + SIZE_PXL_TILE);
		window.draw(health_bar_shape_);
		health_bar_shape_.setPosition(view_.getCenter().x + window.getSize().x / 2 - SIZE_PXL_TILE * 2, view_.getCenter().y - window.getSize().y / 2 + SIZE_PXL_TILE);
		window.draw(health_bar_shape_);
	}
	else if (number_of_lives_ == 2)
	{
		health_bar_shape_.setPosition(view_.getCenter().x + window.getSize().x / 2 - SIZE_PXL_TILE, view_.getCenter().y - window.getSize().y / 2 + SIZE_PXL_TILE);
		window.draw(health_bar_shape_);
		health_bar_shape_.setPosition(view_.getCenter().x + window.getSize().x / 2 - SIZE_PXL_TILE * 1.5f, view_.getCenter().y - window.getSize().y / 2 + SIZE_PXL_TILE);
		window.draw(health_bar_shape_);
	}
	else if (number_of_lives_ == 1)
	{
		health_bar_shape_.setPosition(view_.getCenter().x + window.getSize().x / 2 - SIZE_PXL_TILE, view_.getCenter().y - window.getSize().y / 2 + SIZE_PXL_TILE);
		window.draw(health_bar_shape_);
	}

}

void Player::setupp_view(sf::RenderWindow& window)
{
	if (is_camera_center_)
	{
		view_.setCenter(sf::Vector2f(player_shape_.getPosition().x, player_shape_.getPosition().y));
		view_.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
		window.setView(view_);
		is_camera_center_ = false;
	}
	if (player_shape_.getPosition().x > view_.getCenter().x + window.getSize().x / 2 || player_shape_.getPosition().x < view_.getCenter().x - window.getSize().x / 2 || player_shape_.getPosition().y > view_.getCenter().y + window.getSize().y / 2 || player_shape_.getPosition().y < view_.getCenter().y - window.getSize().y / 2)
	{
		is_camera_center_ = true;
	}
}