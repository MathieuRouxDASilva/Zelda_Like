#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "EndScreen.h"
#include "Player.h"

class Game
{
	//window_ based stuff
	sf::RenderWindow window_;

	//all vectors :

	//textures
	std::vector<int> map_;
	//collisions
	std::vector<bool> map_collision_;
	//spikes location
	std::vector<bool> spikes_map_;
	//lava location
	std::vector<bool> lava_map_;

	//all bools
	bool spikes_down_;
	bool is_lava_down_;
	bool have_key_;
	bool are_spikes_down_;

	//thing that is used to place Player
	sf::Vector2f player_pos_ = sf::Vector2f(4040, 1240);

	// Clock
	sf::Clock clock_;
	//timing the fade
	sf::Clock bonus_timer_;
	const sf::Time bonus_duration_ = sf::seconds(300.0f);

	//all shapes used in game.h
	sf::RectangleShape tile_;
	sf::RectangleShape spike_down_;
	sf::RectangleShape lava_disapear_;
	sf::RectangleShape end_key_;

	//all textures used in game.h :

	//tiles textures
	sf::Texture ground_texture_;
	sf::Texture path_texture_;
	sf::Texture basic_texture_;
	sf::Texture up_wall_texture_;
	sf::Texture ground_dungeon_texture_;
	sf::Texture right_wall_texture_;
	sf::Texture left_wall_texture_;
	sf::Texture door_texture_;
	//different textures
	sf::Texture spikes_up_;
	sf::Texture spikes_downe_;
	sf::Texture lava_texture_;
	sf::Texture lever_not_activated_texture_;
	sf::Texture lever_activated_texture_;
	sf::Texture end_door_texture_;
	sf::Texture end_key_texture_;

	//setupp for sounds
	sf::SoundBuffer buffer_;
	sf::Sound sound_;
	sf::SoundBuffer buffer_key_;
	sf::Sound sound_key_;
	sf::SoundBuffer buffer_win_;
	sf::Sound sound_win_;
	sf::SoundBuffer buffer_lose_;
	sf::Sound sound_lose_;

public:
	Game();
	void init();
	void SetuppMapTextures(Player player);
	void SetuppCollisionsForLater(float& limit_x_low, float& limit_x_high, float& limit_y_low, float& limit_y_high);
	void HandleEventAndPlayerMouvement(Player& player, sf::Vector2f& delta);
	void CollisionsCalcul(Player player, float limit_x_low, float limit_x_high, float limit_y_low, float limit_y_high, sf::Vector2f delta);
	void AllVariablesObjects(Player player);
	void WhatMakeDamageToThePlayer(Player& player);
	void DrawMapForSpikesAndLava();
	void SetuppOfWinAndLose(Player& player, EndScreen& end_screen, bool& entered_end_door);
	void GraphicalFrame(Player& player);
	void game_loop();

	void tp_to_somewhere(sf::RectangleShape player, int minimal_x_position, int maximal_x_position, int minimal_y_position, int maximal_y_position, sf::Vector2f where_we_tp);
	void all_doors_secret_teleporation(sf::RectangleShape player);

	bool tile_at(sf::Vector2i tile_coord);
	sf::Vector2i pos_to_coords(sf::Vector2f world_position);

	void save();
	void load();

};

