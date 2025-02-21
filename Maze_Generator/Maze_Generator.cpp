

#include <iostream>
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Main.hpp"
#include "SFML/Graphics.hpp"
#include "maze_module.h"
#include "random"
#include <vector>

#define Grid_Size 100


void generator();
int main()
{
    std::cout << "Hello World!\n";
	generator();
}

void generator()
{
	

	maze_module modules[16]{
		{ 0, 0, 0, 0,Grid_Size },
		{ 1, 1, 1, 1,Grid_Size },
		{ 1, 0, 0, 0,Grid_Size },
		{ 0, 1, 0, 0,Grid_Size },
		{ 0, 0, 1, 0,Grid_Size },
		{ 0, 0, 0, 1,Grid_Size },
		{ 1, 1, 1, 0,Grid_Size },
		{ 1, 1, 0, 1,Grid_Size },
		{ 1, 0, 1, 1,Grid_Size },
		{ 0, 1, 1, 1,Grid_Size },
		{ 1, 1, 0, 0,Grid_Size },
		{ 1, 0, 1, 0,Grid_Size },
		{ 1, 0, 0, 1,Grid_Size },
		{ 0, 1, 1, 0,Grid_Size },
		{ 0, 1, 0, 1,Grid_Size },
		{ 0, 0, 1, 1,Grid_Size }
	};

	std::vector<maze_module> left;
	std::vector<maze_module> right;
	std::vector<maze_module> down;
	std::vector<maze_module> up;


	for (size_t i = 0; i < 16; i++)
	{
		if (modules[i].left)left.push_back(modules[i]);
		if (modules[i].right)right.push_back(modules[i]);
		if (modules[i].down)down.push_back(modules[i]);
		if (modules[i].up)up.push_back(modules[i]);
	}
	
	std::srand(time(NULL));

	std::vector<maze_module> to_be_generated_modules;
	to_be_generated_modules.push_back(modules[rand() % 16]);
	std::vector<maze_module> generated_modules;

	sf::RenderWindow window(sf::VideoMode(1900, 1080), "SFML works!");


	while (window.isOpen())
	{
		window.clear();

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		for (size_t i = 0; i < to_be_generated_modules.size(); i++)
		{
			
			if (to_be_generated_modules[i].left) { 
				maze_module temp = left[rand() % left.size()];;
				temp.module_sp.setPosition(to_be_generated_modules[i].module_sp.getPosition().x- Grid_Size, to_be_generated_modules[i].module_sp.getPosition().y);
				to_be_generated_modules.push_back(temp);
				
			}
			if (to_be_generated_modules[i].right) {
				maze_module temp = right[rand() % right.size()];;
				temp.module_sp.setPosition(to_be_generated_modules[i].module_sp.getPosition().x + Grid_Size, to_be_generated_modules[i].module_sp.getPosition().y);
				to_be_generated_modules.push_back(temp);
			}
			if (to_be_generated_modules[i].down) {
				maze_module temp = down[rand() % down.size()];;
				temp.module_sp.setPosition(to_be_generated_modules[i].module_sp.getPosition().x, to_be_generated_modules[i].module_sp.getPosition().y + Grid_Size);
				to_be_generated_modules.push_back(temp);
			}
			if (to_be_generated_modules[i].up) {
				maze_module temp = up[rand() % up.size()];;
				temp.module_sp.setPosition(to_be_generated_modules[i].module_sp.getPosition().x, to_be_generated_modules[i].module_sp.getPosition().y - Grid_Size);
				to_be_generated_modules.push_back(temp);
			}
			generated_modules.push_back(to_be_generated_modules[i]);
			to_be_generated_modules.erase(to_be_generated_modules.begin());
		}
	}
	
	for (size_t i = 0; i < generated_modules.size(); i++)
	{
		window.draw(generated_modules[i].module_sp);
	}

	window.display();
}
