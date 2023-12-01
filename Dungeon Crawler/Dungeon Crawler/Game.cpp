#include "Game.h"
#include "Player.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <fstream>
#include <iostream>
#include "EndScreen.h"
#define MAP_WIDTH 100
#define MAP_HEIGHT 80
#define SIZE_PXL_TILE 80

//constructor to setupp
Game::Game()
{
	//tile_ of the vector
	tile_.setSize(sf::Vector2f(SIZE_PXL_TILE, SIZE_PXL_TILE));
	tile_.setFillColor(sf::Color::White);

	//tiles
	ground_texture_.loadFromFile("sprite/ground_texture.png");
	path_texture_.loadFromFile("sprite/path_texture.png");
	basic_texture_.loadFromFile("sprite/basic_tile.png");
	up_wall_texture_.loadFromFile("sprite/up_wall.png");
	ground_dungeon_texture_.loadFromFile("sprite/ground_dungeon.png");
	right_wall_texture_.loadFromFile("sprite/right_wall_dungeon.png");
	left_wall_texture_.loadFromFile("sprite/left_wall.png");
	door_texture_.loadFromFile("sprite/door1.png");
	//activable/dangers
	spikes_up_.loadFromFile("sprite/spikes.png");
	spikes_downe_.loadFromFile("sprite/spikes_down.png");
	lava_texture_.loadFromFile("sprite/lava_texture.png");
	lever_not_activated_texture_.loadFromFile("sprite/lever_not_activated.png");
	lever_activated_texture_.loadFromFile("sprite/lever_activated.png");
	end_door_texture_.loadFromFile("sprite/end_door_texture.png");
	end_key_texture_.loadFromFile("sprite/end_key_texture.png");
	//setupp spikes down effect
	are_spikes_down_ = false;
	spike_down_.setSize(sf::Vector2f(50.0f, 50.0f));
	spike_down_.setPosition(7125, 4950);
	spike_down_.setOrigin(spike_down_.getSize().x, spike_down_.getSize().y);
	spike_down_.setTexture(&spikes_downe_);

	//thing that make the lava disapear
	lava_disapear_.setSize(sf::Vector2f(SIZE_PXL_TILE, SIZE_PXL_TILE));
	lava_disapear_.setFillColor(sf::Color::White);
	lava_disapear_.setTexture(&lever_not_activated_texture_);
	lava_disapear_.setPosition(1655, 5575);
	lava_disapear_.setOrigin(lava_disapear_.getSize().x, lava_disapear_.getSize().y);

	//end door setupp
	end_key_.setSize(sf::Vector2f(SIZE_PXL_TILE, SIZE_PXL_TILE));
	end_key_.setFillColor(sf::Color::White);
	end_key_.setTexture(&end_key_texture_);
	end_key_.setPosition(5360, 4970);
	end_key_.setOrigin(end_key_.getSize().x, end_key_.getSize().y);

	spikes_down_ = false;
	is_lava_down_ = false;
	have_key_ = false;
}

//dorrs collisions
void Game::tp_to_somewhere(sf::RectangleShape player, int minimal_x_position, int maximal_x_position, int minimal_y_position, int maximal_y_position, sf::Vector2f where_we_tp)
{
	if (player.getPosition().y >= minimal_y_position && player.getPosition().y <= maximal_y_position)
	{
		if (player.getPosition().x >= minimal_x_position && player.getPosition().x <= maximal_x_position)
		{
			player_pos_ = where_we_tp;
		}
	}
}
void Game::all_doors_secret_teleporation(sf::RectangleShape player)
{
	tp_to_somewhere(player, 1515, 1589, 2545, 2641, sf::Vector2f(1636, 3714));
	tp_to_somewhere(player, 1601, 1669, 3601, 3681, sf::Vector2f(1520, 2500));
	tp_to_somewhere(player, 5120, 5200, 1, 80, sf::Vector2f(4000, 1200));
	tp_to_somewhere(player, 7040, 7120, 3280, 3359, sf::Vector2f(7070, 4190));
	tp_to_somewhere(player, 7035, 7105, 3831, 3891, sf::Vector2f(7080, 3135));
	tp_to_somewhere(player, 7430, 7510, 4146, 4226, sf::Vector2f(7080, 3135));
	tp_to_somewhere(player, 7039, 7109, 4476, 4536, sf::Vector2f(7075, 4740));
	tp_to_somewhere(player, 7036, 7106, 4631, 4696, sf::Vector2f(7070, 4190));
	tp_to_somewhere(player, 6641, 6706, 4156, 4221, sf::Vector2f(5316, 4271));
	tp_to_somewhere(player, 5275, 5350, 4145, 4225, sf::Vector2f(7085, 4185));
}

//transform coord to tiles and collision
bool Game::tile_at(sf::Vector2i tile_coord)
{
	if (tile_coord.x < 0 || tile_coord.y < 0 || tile_coord.x >= MAP_WIDTH || tile_coord.y >= MAP_HEIGHT)
	{
		return true;
	}
	const int index = tile_coord.y * MAP_WIDTH + tile_coord.x;
	return map_collision_[index];
}
sf::Vector2i Game::pos_to_coords(sf::Vector2f world_position)
{
	sf::Vector2i coord;
	coord.x = std::floor(world_position.x / SIZE_PXL_TILE);
	coord.y = std::floor(world_position.y / SIZE_PXL_TILE);
	return coord;
}

//methods to save/load the game
void Game::save()
{
	//save collisions
	std::ofstream save;
	save.open("map_.txt");
	while (save.is_open())
	{
		for (auto element : map_collision_)
		{
			if (element)
			{
				save << "1\n";
			}
			else
			{
				save << "0\n";
			}
		}
		save.close();
	}


	//save spikes location
	std::ofstream save_spikes;
	save_spikes.open("spike_save.txt");
	while (save_spikes.is_open())
	{
		for (auto element : spikes_map_)
		{
			if (element)
			{
				save_spikes << "1\n";
			}
			else
			{
				save_spikes << "0\n";
			}
		}
		save_spikes.close();
	}

	//save lava location
	std::ofstream save_lava;
	save_lava.open("lava_save.txt");
	while (save_lava.is_open())
	{
		for (auto element : lava_map_)
		{
			if (element)
			{
				save_lava << "1\n";
			}
			else
			{
				save_lava << "0\n";
			}
		}
		save_lava.close();
	}

	//save tile_ type
	std::ofstream tile_type_save;
	tile_type_save.open("tile_.txt");
	while (tile_type_save.is_open())
	{
		for (const auto element : map_)
		{
			switch (element)
			{
			case 0:
				tile_type_save << "0\n";
				break;
			case 1:
				tile_type_save << "1\n";
				break;
			case 2:
				tile_type_save << "2\n";
				break;
			case 3:
				tile_type_save << "3\n";
				break;
			case 4:
				tile_type_save << "4\n";
				break;
			case 5:
				tile_type_save << "5\n";
				break;
			case 6:
				tile_type_save << "6\n";
				break;
			case 7:
				tile_type_save << "7\n";
				break;
			case 8:
				tile_type_save << "8\n";
				break;
			case 9:
				tile_type_save << "9\n";
				break;
			default:
				break;
			}
		}
		tile_type_save.close();
	}
}
void Game::load()
{
	//load collisions
	std::string tile;
	std::ifstream file;
	file.open("map_.txt");
	int i = 0;
	while (file.is_open())
	{
		while (file)
		{
			getline(file, tile);

			if (tile == "1")
			{
				map_collision_[i] = true;
				i++;
			}
			else if (tile == "0")
			{
				map_collision_[i] = false;
				i++;
			}
		}
		file.close();
	}

	//load spikes
	std::string spikes;
	std::ifstream save_spikes;
	save_spikes.open("spike_save.txt");
	int line = 0;
	while (save_spikes.is_open())
	{
		while (save_spikes)
		{
			getline(save_spikes, spikes);

			if (spikes == "1")
			{
				spikes_map_[line] = true;
				line++;
			}
			else if (spikes == "0")
			{
				spikes_map_[line] = false;
				line++;
			}
		}
		save_spikes.close();
	}

	//load lava location
	line = 0;
	std::string lava;
	std::ifstream save_lava;
	save_lava.open("lava_save.txt");
	while (save_lava.is_open())
	{
		while (save_lava)
		{
			getline(save_lava, lava);

			if (lava == "1")
			{
				lava_map_[line] = true;
				line++;
			}
			else if (lava == "0")
			{
				lava_map_[line] = false;
				line++;
			}
		}
		save_lava.close();
	}


	//load tile_ type
	std::string tile_type;
	std::ifstream save;
	save.open("tile_.txt");
	int location = 0;
	while (save.is_open())
	{
		while (save)
		{
			getline(save, tile_type);

			if (tile_type == "0")
			{
				map_[location] = 0;
				location++;
			}
			else if (tile_type == "1")
			{
				map_[location] = 1;
				location++;
			}
			else if (tile_type == "2")
			{
				map_[location] = 2;
				location++;
			}
			else if (tile_type == "3")
			{
				map_[location] = 3;
				location++;
			}
			else if (tile_type == "4")
			{
				map_[location] = 4;
				location++;
			}
			else if (tile_type == "5")
			{
				map_[location] = 5;
				location++;
			}
			else if (tile_type == "6")
			{
				map_[location] = 6;
				location++;
			}
			else if (tile_type == "7")
			{
				map_[location] = 7;
				location++;
			}
			else if (tile_type == "8")
			{
				map_[location] = 8;
				location++;
			}
			else if (tile_type == "9")
			{
				map_[location] = 9;
				location++;
			}
			else
			{
				location++;
			}
		}
		save.close();
	}
}

//init the things that needs to be initialised
void Game::init()
{
	//view for the game (600/300)
	window_.create(sf::VideoMode(1200, 1200), "Window");

	//setupp vector
	int tile_place = 0;
	bool tile_collision = false;
	bool spikes_place = false;
	bool lava_place = false;
	for (int y = 0; y < MAP_HEIGHT; y++)
	{
		for (int x = 0; x < MAP_WIDTH; x++)
		{
			map_.emplace_back(tile_place);
			map_collision_.emplace_back(tile_collision);
			spikes_map_.emplace_back(spikes_place);
			lava_map_.emplace_back(lava_place);
		}
	}

	//sound_ for damage
	buffer_.loadFromFile("sound/damage_sound.wav");
	sound_.setBuffer(buffer_);

	//sound_ for key
	buffer_key_.loadFromFile("sound/key_sound.wav");
	sound_key_.setBuffer(buffer_key_);

	//sound_ for win
	buffer_win_.loadFromFile("sound/win_sound.wav");
	sound_win_.setBuffer(buffer_win_);

	//sound_ for lose
	buffer_lose_.loadFromFile("sound/lose_sound.wav");
	sound_lose_.setBuffer(buffer_lose_);

}

//put texture and tile map
void Game::SetuppMapTextures(Player player)
{
	sf::Vector2i mouse_pos = sf::Mouse::getPosition(window_);
	sf::Vector2i mouse_tile = sf::Vector2i((mouse_pos.x + player.GetPosition().x - window_.getSize().x / 2) / MAP_HEIGHT, (mouse_pos.y + player.GetPosition().y - window_.getSize().y / 2) / MAP_HEIGHT);

	bool left_mouse = sf::Mouse::isButtonPressed(sf::Mouse::Left);
	bool right_mouse = sf::Mouse::isButtonPressed(sf::Mouse::Right);
	if (left_mouse || right_mouse)
	{
		//put a collision
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
		{
			map_collision_[mouse_tile.y * MAP_WIDTH + mouse_tile.x] = left_mouse;
		}
		//put a spike
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
		{
			spikes_map_[mouse_tile.y * MAP_WIDTH + mouse_tile.x] = left_mouse;
		}
		//put some lava
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::V))
		{
			lava_map_[mouse_tile.y * MAP_WIDTH + mouse_tile.x] = left_mouse;
		}

		//change tiles texture based on their value
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad0))
		{
			map_.at(mouse_tile.y * MAP_WIDTH + mouse_tile.x) = 0;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1))
		{
			map_.at(mouse_tile.y * MAP_WIDTH + mouse_tile.x) = 1;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2))
		{
			map_.at(mouse_tile.y * MAP_WIDTH + mouse_tile.x) = 2;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad3))
		{
			map_.at(mouse_tile.y * MAP_WIDTH + mouse_tile.x) = 3;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4))
		{
			map_.at(mouse_tile.y * MAP_WIDTH + mouse_tile.x) = 4;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad5))
		{
			map_.at(mouse_tile.y * MAP_WIDTH + mouse_tile.x) = 5;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad6))
		{
			map_.at(mouse_tile.y * MAP_WIDTH + mouse_tile.x) = 6;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad7))
		{
			map_.at(mouse_tile.y * MAP_WIDTH + mouse_tile.x) = 7;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad8))
		{
			map_.at(mouse_tile.y * MAP_WIDTH + mouse_tile.x) = 8;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad9))
		{
			map_.at(mouse_tile.y * MAP_WIDTH + mouse_tile.x) = 9;
		}
	}


	window_.clear();
	for (int y = 0; y < MAP_HEIGHT; y++)
	{
		for (int x = 0; x < MAP_WIDTH; x++)
		{
			int index = y * MAP_WIDTH + x;

			if (map_[index] == 0)
			{
				tile_.setPosition(x * MAP_HEIGHT, y * MAP_HEIGHT);
				tile_.setFillColor(sf::Color::Green);
				tile_.setTexture(&basic_texture_);
				window_.draw(tile_);
			}
			//ground
			if (map_[index] == 1)
			{
				tile_.setFillColor(sf::Color::Green);
				tile_.setTexture(&ground_texture_);
				tile_.setPosition(x * MAP_HEIGHT, y * MAP_HEIGHT);
				window_.draw(tile_);
			}
			//path
			if (map_[index] == 2)
			{
				tile_.setPosition(x * MAP_HEIGHT, y * MAP_HEIGHT);
				tile_.setFillColor(sf::Color(191, 123, 0));
				tile_.setTexture(&path_texture_);
				window_.draw(tile_);
			}
			//new location
			if (map_[index] == 3)
			{
				//14 blocs en dessous -> suite
				tile_.setFillColor(sf::Color::Black);
				tile_.setPosition(x * MAP_HEIGHT, y * MAP_HEIGHT);
				window_.draw(tile_);
			}
			if (map_[index] == 4)
			{
				tile_.setFillColor(sf::Color::White);
				tile_.setPosition(x * MAP_HEIGHT, y * MAP_HEIGHT);
				tile_.setTexture(&up_wall_texture_);
				window_.draw(tile_);
			}
			if (map_[index] == 5)
			{
				tile_.setFillColor(sf::Color::White);
				tile_.setPosition(x * MAP_HEIGHT, y * MAP_HEIGHT);
				tile_.setTexture(&ground_dungeon_texture_);
				window_.draw(tile_);
			}
			if (map_[index] == 6)
			{
				tile_.setFillColor(sf::Color::White);
				tile_.setPosition(x * MAP_HEIGHT, y * MAP_HEIGHT);
				tile_.setTexture(&right_wall_texture_);
				window_.draw(tile_);
			}
			if (map_[index] == 7)
			{
				tile_.setFillColor(sf::Color::White);
				tile_.setPosition(x * MAP_HEIGHT, y * MAP_HEIGHT);
				tile_.setTexture(&left_wall_texture_);
				window_.draw(tile_);
			}
			if (map_[index] == 8)
			{
				tile_.setFillColor(sf::Color::White);
				tile_.setPosition(x * MAP_HEIGHT, y * MAP_HEIGHT);
				tile_.setTexture(&door_texture_);
				window_.draw(tile_);
			}
			if (map_[index] == 9)
			{
				tile_.setFillColor(sf::Color::White);
				tile_.setPosition(x * MAP_HEIGHT, y * MAP_HEIGHT);
				tile_.setTexture(&end_door_texture_);
				window_.draw(tile_);
			}
		}
	}
}

//setupp how collision works
void Game::SetuppCollisionsForLater(float& limit_x_low, float& limit_x_high, float& limit_y_low, float& limit_y_high)
{
	limit_x_low = -1000000000.f;
	limit_x_high = 1000000000.f;
	limit_y_low = -1000000000.f;
	limit_y_high = 1000000000.f;

	sf::Vector2i player_coords = pos_to_coords(player_pos_);
	constexpr int margin = 1;

	if (tile_at(player_coords + sf::Vector2i(1, 0)))
	{
		limit_x_high = (player_coords.x + 1) * SIZE_PXL_TILE - margin;
	}
	if (tile_at(player_coords + sf::Vector2i(-1, 0)))
	{
		limit_x_low = (player_coords.x) * SIZE_PXL_TILE + margin;
	}
	if (tile_at(player_coords + sf::Vector2i(0, 1)))
	{
		limit_y_high = (player_coords.y + 1) * SIZE_PXL_TILE - margin;
	}
	if (tile_at(player_coords + sf::Vector2i(0, -1)))
	{
		limit_y_low = (player_coords.y) * SIZE_PXL_TILE + margin;
	}
}

//Event and player mouvement in player class 
void Game::HandleEventAndPlayerMouvement(Player& player, sf::Vector2f& delta)
{
	sf::Event event;

	while (window_.pollEvent(event))
	{
		if (event.type == sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			window_.close();
		}
		if (event.type == sf::Keyboard::isKeyPressed(sf::Keyboard::U))
		{
			save();
		}
		player.player_mouvement(delta);
	}
}

//collisions
void Game::CollisionsCalcul(Player player, float limit_x_low, float limit_x_high, float limit_y_low, float limit_y_high, sf::Vector2f delta)
{
	player_pos_ += delta;
	if (player_pos_.x >= limit_x_high - (player.GetSize().x / 2))
	{
		player_pos_.x = limit_x_high - (player.GetSize().x / 2);
	}
	if (player_pos_.x <= limit_x_low)
	{
		player_pos_.x = limit_x_low;
	}
	if (player_pos_.y >= limit_y_high)
	{
		player_pos_.y = limit_y_high;
	}
	if (player_pos_.y <= limit_y_low)
	{
		player_pos_.y = limit_y_low;
	}
}

//all objects and what they do
void Game::AllVariablesObjects(Player player)
{
	//collision with spikes
	if (player.GetPosition().x <= spike_down_.getPosition().x && player.GetPosition().x >= spike_down_.getPosition().x - spike_down_.getSize().x)
	{
		if (player.GetPosition().y <= spike_down_.getPosition().y && player.GetPosition().y >= spike_down_.getPosition().y - spike_down_.getSize().y)
		{
			are_spikes_down_ = true;
			spike_down_.setPosition(-1000, -1000);
			bonus_timer_.restart();
		}
	}

	//timer setupp
	if (are_spikes_down_ && bonus_timer_.getElapsedTime() >= bonus_duration_)
	{
		are_spikes_down_ = false;
		spike_down_.setPosition(7065, 4900);
	}

	//lava collision
	if (player.GetPosition().x <= lava_disapear_.getPosition().x - player.GetSize().x / 2 && player.GetPosition().x >= lava_disapear_.getPosition().x - lava_disapear_.getSize().x + player.GetSize().x / 2)
	{
		if (player.GetPosition().y <= lava_disapear_.getPosition().y - player.GetSize().y && player.GetPosition().y >= lava_disapear_.getPosition().y - lava_disapear_.getSize().y + player.GetSize().y)
		{
			is_lava_down_ = true;
			lava_disapear_.setTexture(&lever_activated_texture_);
		}
	}

	//key collision
	if (player.GetPosition().x <= end_key_.getPosition().x && player.GetPosition().x >= end_key_.getPosition().x - end_key_.getSize().x)
	{
		if (player.GetPosition().y <= end_key_.getPosition().y && player.GetPosition().y >= end_key_.getPosition().y - end_key_.getSize().y)
		{
			have_key_ = true;
			end_key_.setPosition(-1000.0f, -1000.0f);
			sound_key_.play();
		}
	}
}

//how player take somme damage
void Game::WhatMakeDamageToThePlayer(Player& player)
{
	sf::Vector2i player_tile = pos_to_coords(player_pos_);
	if (spikes_map_[player_tile.y * MAP_WIDTH + player_tile.x])
	{
		if (!are_spikes_down_)
		{
			player.take_one_damage();
			player_pos_ -= sf::Vector2f(0.0f, SIZE_PXL_TILE);
			sound_.play();
		}
	}
	sf::Vector2i player_tile_position = pos_to_coords(player_pos_);
	if (lava_map_[player_tile_position.y * MAP_WIDTH + player_tile_position.x])
	{
		if (!is_lava_down_)
		{
			player.take_one_damage();
			player_pos_ -= sf::Vector2f(0, SIZE_PXL_TILE);
			sound_.play();
		}
	}
}

//draw spikes and lava so they appear on screen
void Game::DrawMapForSpikesAndLava()
{
	for (int y = 0; y < MAP_HEIGHT; y++)
	{
		for (int x = 0; x < MAP_WIDTH; x++)
		{
			int index = y * MAP_WIDTH + x;

			if (spikes_map_[index])
			{
				if (!are_spikes_down_)
				{
					tile_.setFillColor(sf::Color::White);
					tile_.setPosition(x * MAP_HEIGHT, y * MAP_HEIGHT);
					tile_.setTexture(&spikes_up_);
					window_.draw(tile_);
				}
				else
				{
					tile_.setFillColor(sf::Color::White);
					tile_.setPosition(x * MAP_HEIGHT, y * MAP_HEIGHT);
					tile_.setTexture(&spikes_downe_);
					window_.draw(tile_);
				}
			}
		}
	}



	for (int y = 0; y < MAP_HEIGHT; y++)
	{
		for (int x = 0; x < MAP_WIDTH; x++)
		{
			int index = y * MAP_WIDTH + x;

			if (lava_map_[index])
			{
				if (!is_lava_down_)
				{
					tile_.setFillColor(sf::Color::White);
					tile_.setPosition(x * MAP_HEIGHT, y * MAP_HEIGHT);
					tile_.setTexture(&lava_texture_);
					window_.draw(tile_);
				}
				else
				{
					tile_.setFillColor(sf::Color::White);
					tile_.setPosition(x * MAP_HEIGHT, y * MAP_HEIGHT);
					tile_.setTexture(&path_texture_);
					window_.draw(tile_);
				}
			}
		}
	}
}

//how and what win/lose
void Game::SetuppOfWinAndLose(Player& player, EndScreen& end_screen, bool& entered_end_door)
{
	//setupp to lose
	if (player.GetNumberOfLives() <= 0)
	{
		player_pos_ = sf::Vector2f(0.0f, 0.0f);
		end_screen.draw_the_end_screen_lose(window_);
	}

	//setupp to win
	if (player.GetPosition().x >= 3925 && player.GetPosition().x <= 4241 && player.GetPosition().y <= 81 && have_key_)
	{
		entered_end_door = true;
	}
	if (entered_end_door)
	{
		player_pos_ = sf::Vector2f(0.0f, 0.0f);
		end_screen.draw_the_end_screen_victory(window_);
	}
}

//graphical frame
void Game::GraphicalFrame(Player& player)
{
	player.SetPosition(player_pos_);
	player.draw_player(window_);
	window_.draw(lava_disapear_);
	window_.draw(spike_down_);
	window_.draw(lava_disapear_);
	window_.draw(end_key_);
	window_.display();
}

//game loop
void Game::game_loop()
{
	init();
	class Player player;
	EndScreen end_screen;

	bool entered_end_door = false;

	load();

	while (window_.isOpen())
	{
		//system to scroll like zelda in player class
		player.setupp_view(window_);

		SetuppMapTextures(player);


		float limit_x_low;
		float limit_x_high;
		float limit_y_low;
		float limit_y_high;

		SetuppCollisionsForLater(limit_x_low, limit_x_high, limit_y_low, limit_y_high);

		sf::Vector2f delta(0, 0);
		HandleEventAndPlayerMouvement(player, delta);


		CollisionsCalcul(player, limit_x_low, limit_x_high, limit_y_low, limit_y_high, delta);


		//check collision with all doors
		all_doors_secret_teleporation(player.GetShape());


		AllVariablesObjects(player);

		WhatMakeDamageToThePlayer(player);

		DrawMapForSpikesAndLava();

		player.draw_hp(window_);

		system("cls");
		std::cout << player.GetPosition().x << "\n" << player.GetPosition().y;

		SetuppOfWinAndLose(player, end_screen, entered_end_door);

		GraphicalFrame(player);
	}
}
