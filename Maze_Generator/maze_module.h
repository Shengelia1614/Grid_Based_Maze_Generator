#pragma once
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Main.hpp"
#include "SFML/Graphics.hpp"

//std::vector<std::vector<bool>> GRID;

#define Maze_Size 100

#define Grid_Size 20
#define Grid_x 1900/ Grid_Size
#define Grid_y 1080/Grid_Size


class maze_module
{
	
	sf::RenderTexture *texture;
	
public:
	sf::Sprite module_sp;
	bool left, right, down, up;
	std::pair<int, int> grid_position;

	//maze_module();

	maze_module(bool left, bool right, bool down, bool up, int grid_size)
		: left(left), right(right), down(down), up(up)
	{
		//default_module_texture(a);
		//sf::RenderTexture texture;
		texture = new sf::RenderTexture();
		texture->create(grid_size, grid_size);
		texture->clear(sf::Color::Black);


		//texture.display();

		if (left) {
			sf::RectangleShape l(sf::Vector2f((grid_size / 2)+1, grid_size / 10)); l.setPosition(0, grid_size / 2 - l.getSize().y / 2); l.setFillColor(sf::Color::White);  texture->draw(l); texture->display();
		}
		if (right) {
			sf::RectangleShape r(sf::Vector2f((grid_size / 2)+1, grid_size / 10)); r.setPosition((grid_size / 2)-1, grid_size / 2 - r.getSize().y / 2); r.setFillColor(sf::Color::White); texture->draw(r); texture->display();
		}
		if (down) {
			sf::RectangleShape d(sf::Vector2f(grid_size / 10, (grid_size / 2)+1)); d.setPosition((grid_size / 2) - d.getSize().x / 2, grid_size / 2); d.setFillColor(sf::Color::White); texture->draw(d); texture->display();
		}
		if (up) {
			sf::RectangleShape u(sf::Vector2f(grid_size / 10, (grid_size / 2) + 1)); u.setPosition(grid_size / 2 - u.getSize().x / 2, 0); u.setFillColor(sf::Color::White); texture->draw(u); texture->display();
		}

		texture->display();
		//module_sp.setColor(sf::Color::Blue);
		module_sp.setTexture(texture->getTexture());
		module_sp.setTextureRect(sf::IntRect(0, 0, grid_size, grid_size));
	}

	/*void default_module_texture(int& grid_size) {
		
	}*/
	void set_texture(const sf::Texture & a) {
		
		module_sp.setTexture(a);
		module_sp.setTextureRect(sf::IntRect(0, 0, a.getSize().x, a.getSize().y));
	}


	
};

class non_grid_maze_module
{
	
	float east, west, south, north;


public:



};