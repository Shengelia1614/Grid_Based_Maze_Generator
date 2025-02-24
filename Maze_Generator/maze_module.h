#pragma once
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Main.hpp"
#include "SFML/Graphics.hpp"



#define Maze_Size 100

#define Grid_Size 40

#define Grid_x Maze_Size
#define Grid_y Maze_Size


class maze_module
{
	
	sf::RenderTexture *texture;
	sf::RenderTexture* texture_updated;
public:

	//you can change sprite to somethingelse if you are not using sfml 
	// but you must change the generator function too since sprite position is used to determine actuall position of nodes
	sf::Sprite module_sp;
	bool left, right, down, up;

	//this is used to remember what original sides were since we need this in direction changer
	//original sides gets changed
	bool old_sides[4];

	bool open_sides[4];
	std::pair<int, int> grid_position;


	
	maze_module() {};


	//constructor also generates default sprites for the maze
	maze_module(bool left, bool right, bool down, bool up, int grid_size)
		: left(left), right(right), down(down), up(up)
	{
		old_sides[0] = left;
		old_sides[1] = right;
		old_sides[2] = down;
		old_sides[3] = up;

		//default_module_texture(a);
		//sf::RenderTexture texture;
		texture = new sf::RenderTexture();
		texture->create(grid_size, grid_size);
		texture->clear(sf::Color::Black);


		//texture.display();

		if (left) {
			sf::RectangleShape l(sf::Vector2f((grid_size / 2)+1, grid_size / 6)); l.setPosition(0, grid_size / 2 - l.getSize().y / 2); l.setFillColor(sf::Color::White);  texture->draw(l); texture->display();
			
			sf::RectangleShape l1(sf::Vector2f((grid_size / 6) , grid_size / 6));
			l1.setPosition(0, grid_size / 2 - l1.getSize().y / 2); 
			l1.setFillColor(sf::Color::Red);
			texture->draw(l1); texture->display(); 
			
		}
		if (right) {
			sf::RectangleShape r(sf::Vector2f((grid_size / 2)+1, grid_size / 6)); r.setPosition((grid_size / 2)-1, grid_size / 2 - r.getSize().y / 2); r.setFillColor(sf::Color::White); texture->draw(r); texture->display();
			
			sf::RectangleShape r1(sf::Vector2f((grid_size / 6), grid_size / 6));
			r1.setPosition(grid_size - r1.getSize().x, grid_size / 2 - r1.getSize().y / 2);
			r1.setFillColor(sf::Color::Red);
			texture->draw(r1); texture->display();
			
		}
		if (down) {
			sf::RectangleShape d(sf::Vector2f(grid_size / 6, (grid_size / 2)+1)); d.setPosition((grid_size / 2) - d.getSize().x / 2, grid_size / 2); d.setFillColor(sf::Color::White); texture->draw(d); texture->display();

			sf::RectangleShape d1(sf::Vector2f((grid_size / 6), grid_size / 6));
			d1.setPosition((grid_size / 2) - d1.getSize().x / 2, grid_size - d1.getSize().y);
			d1.setFillColor(sf::Color::Red);
			texture->draw(d1); texture->display();
			
		}
		if (up) {
			sf::RectangleShape u(sf::Vector2f(grid_size / 6, (grid_size / 2) + 1)); u.setPosition(grid_size / 2 - u.getSize().x / 2, 0); u.setFillColor(sf::Color::White); texture->draw(u); texture->display();
			
			sf::RectangleShape u1(sf::Vector2f((grid_size / 6), grid_size / 6));
			u1.setPosition((grid_size / 2) - u1.getSize().x / 2, 0);
			u1.setFillColor(sf::Color::Red);
			texture->draw(u1); texture->display();
			
		}

		texture->display();
		//module_sp.setColor(sf::Color::Blue);
		module_sp.setTexture(texture->getTexture());
		module_sp.setTextureRect(sf::IntRect(0, 0, grid_size, grid_size));
	}



	//if you wish to set custom textures yourself
	void set_texture(const sf::Texture & a) {
		
		module_sp.setTexture(a);
		module_sp.setTextureRect(sf::IntRect(0, 0, a.getSize().x, a.getSize().y));
	}

	void module_sprite_changer() {

		//sf::Sprite 
		
		texture_updated = new sf::RenderTexture();
		texture_updated->create(Grid_Size, Grid_Size);
		texture_updated->clear(sf::Color::Black);


		//texture.display();


		if (old_sides[0]) {
			sf::RectangleShape l(sf::Vector2f((Grid_Size / 2) + 1, Grid_Size / 6)); l.setPosition(0, Grid_Size / 2 - l.getSize().y / 2); l.setFillColor(sf::Color::White);  texture_updated->draw(l); texture_updated->display();
			if (!open_sides[0]) {

				sf::RectangleShape l1(sf::Vector2f((Grid_Size / 6), Grid_Size / 6));
				l1.setPosition(0, Grid_Size / 2 - l1.getSize().y / 2);
				l1.setFillColor(sf::Color::Red);
				texture_updated->draw(l1); texture_updated->display();
			}
		}
		if (old_sides[1]) {
			sf::RectangleShape r(sf::Vector2f((Grid_Size / 2) + 1, Grid_Size / 6)); r.setPosition((Grid_Size / 2) - 1, Grid_Size / 2 - r.getSize().y / 2); r.setFillColor(sf::Color::White); texture_updated->draw(r); texture_updated->display();
			if (!open_sides[1]) {

				sf::RectangleShape r1(sf::Vector2f((Grid_Size / 6), Grid_Size / 6));
				r1.setPosition(Grid_Size - r1.getSize().x, Grid_Size / 2 - r1.getSize().y / 2);
				r1.setFillColor(sf::Color::Red);
				texture_updated->draw(r1); texture_updated->display();
			}

		}
		if (old_sides[2]) {
			sf::RectangleShape d(sf::Vector2f(Grid_Size / 6, (Grid_Size / 2) + 1)); d.setPosition((Grid_Size / 2) - d.getSize().x / 2, Grid_Size / 2); d.setFillColor(sf::Color::White); texture_updated->draw(d); texture_updated->display();
			if (!open_sides[2]) {

				sf::RectangleShape d1(sf::Vector2f((Grid_Size / 6), Grid_Size / 6));
				d1.setPosition((Grid_Size / 2) - d1.getSize().x / 2, Grid_Size - d1.getSize().y);
				d1.setFillColor(sf::Color::Red);
				texture_updated->draw(d1); texture_updated->display();
			}

		}
		if (old_sides[3]) {
			sf::RectangleShape u(sf::Vector2f(Grid_Size / 6, (Grid_Size / 2) + 1)); u.setPosition(Grid_Size / 2 - u.getSize().x / 2, 0); u.setFillColor(sf::Color::White); texture_updated->draw(u); texture_updated->display();
			if (!open_sides[3]) {

				sf::RectangleShape u1(sf::Vector2f((Grid_Size / 6), Grid_Size / 6));
				u1.setPosition((Grid_Size / 2) - u1.getSize().x / 2, 0);
				u1.setFillColor(sf::Color::Red);
				texture_updated->draw(u1); texture_updated->display();
			}

		}

		texture_updated->display();
		//module_sp.setColor(sf::Color::Blue);
		module_sp.setTexture(texture_updated->getTexture());
		module_sp.setTextureRect(sf::IntRect(0, 0, Grid_Size, Grid_Size));
	}
	
};

