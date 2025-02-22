

#include <iostream>
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Main.hpp"
#include "SFML/Graphics.hpp"
#include "maze_module.h"
#include "random"
#include <vector>
#include <windows.h>


//#define Maze_Size 15

void generator();



bool GRID[Grid_x][Grid_y];


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

	to_be_generated_modules[0].module_sp.setPosition(window.getSize().x/2-Grid_Size/2, window.getSize().y/2- Grid_Size / 2);
	GRID[Grid_x / 2][Grid_y / 2] = 1;
	to_be_generated_modules[0].grid_position = std::pair<int, int>{ Grid_x / 2 ,Grid_y / 2 };

	int grid_counter = 0;


	

	while (window.isOpen())
	{
		window.clear(sf::Color::Black);
		

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}


		if (grid_counter < Maze_Size) {
			int size = to_be_generated_modules.size();
			for (size_t i = 0; i < size; i++)
			{
				

				if (to_be_generated_modules[i].left 
					&& GRID[to_be_generated_modules[i].grid_position.first - 1][to_be_generated_modules[i].grid_position.second]==0) {

					GRID[to_be_generated_modules[i].grid_position.first - 1][to_be_generated_modules[i].grid_position.second]=1;

					maze_module temp = right[rand() % right.size()];

					temp.grid_position.first = to_be_generated_modules[i].grid_position.first - 1;
					temp.grid_position.second = to_be_generated_modules[i].grid_position.second;

					temp.module_sp.setPosition(to_be_generated_modules[i].module_sp.getPosition().x - Grid_Size, to_be_generated_modules[i].module_sp.getPosition().y);
					temp.right = 0;
					
					to_be_generated_modules.push_back(temp);

				}
				if (to_be_generated_modules[i].right 
					&& GRID[to_be_generated_modules[i].grid_position.first + 1][to_be_generated_modules[i].grid_position.second]==0) {

					GRID[to_be_generated_modules[i].grid_position.first + 1][to_be_generated_modules[i].grid_position.second] = 1;

					maze_module temp = left[rand() % left.size()];


					temp.grid_position.first = to_be_generated_modules[i].grid_position.first + 1;
					temp.grid_position.second = to_be_generated_modules[i].grid_position.second;

					temp.module_sp.setPosition(to_be_generated_modules[i].module_sp.getPosition().x + Grid_Size, to_be_generated_modules[i].module_sp.getPosition().y);
					temp.left = 0;
					
					to_be_generated_modules.push_back(temp);
				}
				if (to_be_generated_modules[i].down 
					&& GRID[to_be_generated_modules[i].grid_position.first][to_be_generated_modules[i].grid_position.second + 1]==0) {

					GRID[to_be_generated_modules[i].grid_position.first][to_be_generated_modules[i].grid_position.second +1] = 1;

					maze_module temp = up[rand() % up.size()];


					temp.grid_position.first = to_be_generated_modules[i].grid_position.first;
					temp.grid_position.second = to_be_generated_modules[i].grid_position.second +1;

					temp.module_sp.setPosition(to_be_generated_modules[i].module_sp.getPosition().x, to_be_generated_modules[i].module_sp.getPosition().y + Grid_Size);
					temp.up = 0;
					
					to_be_generated_modules.push_back(temp);
				}
				if (to_be_generated_modules[i].up 
					&& GRID[to_be_generated_modules[i].grid_position.first][to_be_generated_modules[i].grid_position.second - 1]==0) {

					GRID[to_be_generated_modules[i].grid_position.first][to_be_generated_modules[i].grid_position.second -1] = 1;

					maze_module temp = down[rand() % down.size()];

					temp.grid_position.first = to_be_generated_modules[i].grid_position.first;
					temp.grid_position.second = to_be_generated_modules[i].grid_position.second-1;

					temp.module_sp.setPosition(to_be_generated_modules[i].module_sp.getPosition().x, to_be_generated_modules[i].module_sp.getPosition().y - Grid_Size);
					temp.down = 0;
					
					to_be_generated_modules.push_back(temp);
				}
				
				generated_modules.push_back(to_be_generated_modules[i]);
				to_be_generated_modules.erase(to_be_generated_modules.begin());
				size--;
			}
		}

		for (size_t i = 0; i < generated_modules.size(); i++)
		{
			window.draw(generated_modules[i].module_sp);
		}

		/*window.draw(modules[1].module_sp);

		modules[1].left = 0;

		window.draw(modules[1].module_sp);*/
		//std::sleep(5);
		
		window.display();
		grid_counter++;
	}
	
	
}
