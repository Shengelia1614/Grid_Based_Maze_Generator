#pragma once
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Main.hpp"
#include "SFML/Graphics.hpp"


class maze_module
{
	

public:
	sf::Sprite module_sp;
	bool left, right, down, up;

	//maze_module();

	maze_module(bool left, bool right, bool down, bool up, int a)
		: left(left), right(right), down(down), up(up)
	{
		default_module_texture(a);
	}

	void default_module_texture(int& grid_size) {
		sf::RenderTexture texture;
		texture.create(grid_size, grid_size);
		texture.clear(sf::Color::Transparent);
		

		if (left) { sf::RectangleShape l(sf::Vector2f(grid_size / 2, grid_size / 5)); l.setPosition(0, grid_size / 2 - l.getSize().y / 2); l.setFillColor(sf::Color::White); texture.draw(l); }
		if (right) { sf::RectangleShape r(sf::Vector2f(grid_size / 2, grid_size / 5)); r.setPosition(grid_size / 2, grid_size / 2 - r.getSize().y / 2); r.setFillColor(sf::Color::White); texture.draw(r); }
		if (down) { sf::RectangleShape d(sf::Vector2f(grid_size / 5, grid_size / 2)); d.setPosition(grid_size / 2 - d.getSize().x / 2, grid_size / 2); d.setFillColor(sf::Color::White); texture.draw(d); }
		if (up) { sf::RectangleShape u(sf::Vector2f(grid_size / 5, grid_size / 2)); u.setPosition(grid_size / 2 - u.getSize().x / 2, 0); u.setFillColor(sf::Color::White); texture.draw(u); }

		module_sp.setTexture(texture.getTexture());
	}
	void set_texture(sf::Texture &a) {
		module_sp.setTexture(a);
	}


	
};

class non_grid_maze_module
{
	
	float east, west, south, north;


public:



};