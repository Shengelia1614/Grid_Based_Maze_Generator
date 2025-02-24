

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
#include <chrono>
#include <utility>







//#define Maze_Size 15
bool GRID[Grid_x][Grid_y];


std::vector<maze_module> generator(sf::RenderWindow& window);
enum sides {
	LEFT, RIGHT, DOWN, UP
};
maze_module direction_changer(maze_module a, sides b);







int main()
{
    
	

	sf::RenderWindow window(sf::VideoMode(1900, 1080), "SFML works!");

	std::vector<maze_module> generated_modules;

	generated_modules= generator(window);

	while (window.isOpen())
	{
		window.clear(sf::Color::Black);


		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}




		for (size_t i = 0; i < generated_modules.size(); i++)
		{
			window.draw(generated_modules[i].module_sp);
		}



		window.display();

	}
}

std::vector<maze_module> generator(sf::RenderWindow& window)
{
	int dead_end_percent = 10;

	maze_module modules[11]{
		//{ 0, 0, 0, 0,Grid_Size },
		{ 1, 1, 1, 1,Grid_Size },
		/*{ 1, 0, 0, 0,Grid_Size },
		{ 0, 1, 0, 0,Grid_Size },
		{ 0, 0, 1, 0,Grid_Size },
		{ 0, 0, 0, 1,Grid_Size },*/
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


	for (size_t i = 0; i < 11; i++)
	{
		if (modules[i].left)left.push_back(modules[i]);
		if (modules[i].right)right.push_back(modules[i]);
		if (modules[i].down)down.push_back(modules[i]);
		if (modules[i].up)up.push_back(modules[i]);
	}
	
	std::srand(time(NULL));

	std::vector<maze_module> to_be_generated_modules;
	//to_be_generated_modules.push_back(modules[rand() % 11]);
	to_be_generated_modules.push_back(modules[0]);
	std::vector<maze_module> generated_modules;
	

	to_be_generated_modules[0].module_sp.setPosition(window.getSize().x/2-Grid_Size/2, window.getSize().y/2- Grid_Size / 2);
	GRID[Grid_x / 2][Grid_y / 2] = 1;
	to_be_generated_modules[0].grid_position = std::pair<int, int>{ Grid_x / 2 ,Grid_y / 2 };

	int grid_counter = 0;

	bool a = 1;
	
	auto start = std::chrono::high_resolution_clock::now();


		while (grid_counter < Maze_Size) {
			int size = to_be_generated_modules.size();
			for (size_t i = 0; i < size; i++)
			{
				

				if (to_be_generated_modules[i].left) {

					if (GRID[to_be_generated_modules[i].grid_position.first - 1][to_be_generated_modules[i].grid_position.second] == 0) {

						GRID[to_be_generated_modules[i].grid_position.first - 1][to_be_generated_modules[i].grid_position.second] = 1;

						maze_module temp = right[rand() % right.size()];

						temp.grid_position.first = to_be_generated_modules[i].grid_position.first - 1;
						temp.grid_position.second = to_be_generated_modules[i].grid_position.second;

						temp.module_sp.setPosition(to_be_generated_modules[i].module_sp.getPosition().x - Grid_Size, to_be_generated_modules[i].module_sp.getPosition().y);
						temp.right = 0;
						

						to_be_generated_modules.push_back(temp);
					}
					else {
						if (rand() % 100 > dead_end_percent) {
							sides side =LEFT;
							to_be_generated_modules[i]=direction_changer(to_be_generated_modules[i], side);
						}
					}

				}

				if (to_be_generated_modules[i].right ) {

					if (GRID[to_be_generated_modules[i].grid_position.first + 1][to_be_generated_modules[i].grid_position.second] == 0) {

						GRID[to_be_generated_modules[i].grid_position.first + 1][to_be_generated_modules[i].grid_position.second] = 1;

						maze_module temp = left[rand() % left.size()];


						temp.grid_position.first = to_be_generated_modules[i].grid_position.first + 1;
						temp.grid_position.second = to_be_generated_modules[i].grid_position.second;

						temp.module_sp.setPosition(to_be_generated_modules[i].module_sp.getPosition().x + Grid_Size, to_be_generated_modules[i].module_sp.getPosition().y);
						temp.left = 0;

						to_be_generated_modules.push_back(temp);
					}
					else {
						if (rand() % 100 > dead_end_percent) {
							sides side = RIGHT;
							to_be_generated_modules[i] = direction_changer(to_be_generated_modules[i], side);
						}
					}
				}

				if (to_be_generated_modules[i].down ) {

					if (GRID[to_be_generated_modules[i].grid_position.first][to_be_generated_modules[i].grid_position.second + 1] == 0) {

						GRID[to_be_generated_modules[i].grid_position.first][to_be_generated_modules[i].grid_position.second + 1] = 1;

						maze_module temp = up[rand() % up.size()];


						temp.grid_position.first = to_be_generated_modules[i].grid_position.first;
						temp.grid_position.second = to_be_generated_modules[i].grid_position.second + 1;

						temp.module_sp.setPosition(to_be_generated_modules[i].module_sp.getPosition().x, to_be_generated_modules[i].module_sp.getPosition().y + Grid_Size);
						temp.up = 0;

						to_be_generated_modules.push_back(temp);
					}
					else {
						if (rand() % 100 > dead_end_percent) {
							sides side = DOWN;
							to_be_generated_modules[i] = direction_changer(to_be_generated_modules[i], side);	
						}
					}

				}
				if (to_be_generated_modules[i].up ) {

					if (GRID[to_be_generated_modules[i].grid_position.first][to_be_generated_modules[i].grid_position.second - 1] == 0) {

						GRID[to_be_generated_modules[i].grid_position.first][to_be_generated_modules[i].grid_position.second - 1] = 1;

						maze_module temp = down[rand() % down.size()];

						temp.grid_position.first = to_be_generated_modules[i].grid_position.first;
						temp.grid_position.second = to_be_generated_modules[i].grid_position.second - 1;

						temp.module_sp.setPosition(to_be_generated_modules[i].module_sp.getPosition().x, to_be_generated_modules[i].module_sp.getPosition().y - Grid_Size);
						temp.down = 0;

						to_be_generated_modules.push_back(temp);
					}
					else {
						if (rand() % 100 > dead_end_percent) {
							sides side = UP;
							to_be_generated_modules[i] = direction_changer(to_be_generated_modules[i], side);
						}
					}
				}
				
				
				generated_modules.push_back(to_be_generated_modules[i]);
				to_be_generated_modules.erase(to_be_generated_modules.begin());
				size--;
			}
			grid_counter++;
		}

			
		if (a) {
				
			auto now = std::chrono::high_resolution_clock::now();
			auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - start).count();
				
			std::cout << "milliseconds since start: " << duration << " ms" << std::endl;
			a = false;
		}

	
		return generated_modules;
}

maze_module direction_changer(maze_module a, sides b) {
	maze_module temp;
	switch (b)
	{
	case LEFT: temp = maze_module(a.old_sides[0], true, a.old_sides[2], a.old_sides[3], Grid_Size);
		break;
	case RIGHT: temp = maze_module(true, a.old_sides[1], a.old_sides[2], a.old_sides[3], Grid_Size);
		break;
	case DOWN: temp = maze_module(a.old_sides[0], a.old_sides[1], a.old_sides[2], true, Grid_Size);
		break;
	case UP: temp = maze_module(a.old_sides[0], a.old_sides[1], true, a.old_sides[3], Grid_Size);
		break;
	}
	temp.grid_position.first = a.grid_position.first;
	temp.grid_position.second = a.grid_position.second;
	temp.module_sp.setPosition(a.module_sp.getPosition());


	return temp;
}

