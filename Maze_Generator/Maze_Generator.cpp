

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
#include <unordered_map>
#include <functional>
#include <string> 


//Grid is used to check which positions in grid is already used by a sprite
//we check this to prevent maze modules generating on top of each other,
bool GRID[Grid_x][Grid_y];



struct pair_hash {
	template <typename T1, typename T2>
	std::size_t operator()(const std::pair<T1, T2>& p) const {
		auto h1 = std::hash<T1>{}(p.first);  // Hash for the first element
		auto h2 = std::hash<T2>{}(p.second); // Hash for the second element
		return h1 ^ (h2 << 1); // Combine hashes using XOR and bit shifting
	}
};

std::unordered_map<std::pair<int, int>, int, pair_hash> mp;




//main generator function
std::vector<maze_module> generator(sf::RenderWindow& window);

//this enum is needed for next function that changes the direcion that open face is looking towards
//in generator function if open face cant add another node to itself because grid next to it is already taken by another node
//it will add a face to opposite side
// 
//enum is used to check which side is being blocked in direction changer function 
enum sides {
	LEFT, RIGHT, DOWN, UP
};
maze_module direction_changer(maze_module a, sides b);

void dead_end_closer(std::vector<maze_module>& maze);





int main()
{
    
	

	sf::RenderWindow window(sf::VideoMode(1900, 1080), "SFML works!");


	//this is the vector where we will store all generated maze modules
	//vector itseld is the full maze
	const std::vector<maze_module> generated_modules= generator(window);

	std::cout << "maze is generated" << std::endl;

	while (window.isOpen())
	{
		window.clear(sf::Color::Black);
		

		


		//drawing the maze

		for (size_t i = 0; i < generated_modules.size(); i++)
		{
			window.draw(generated_modules[i].module_sp);
			
		}
		//std::cout << "drawn" << std::endl;


		window.display();



		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

		}

	}
	std::cout << "done" << std::endl;
	return 0;
}



std::vector<maze_module> generator(sf::RenderWindow& window)
{
	//this controls how likely a node is to change its direction when its about to colide with another node
	//lower the value = higher chance
	//value must be between 0 and 100
	int dead_end_percent = 10;
	



	//this is fundamental building blocks of maze
	//i removed dead end nodes because it often resulted in very small mazes

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



	//we split modules into modules that are compatimble with one of the 4 sides

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


	//generator used to generate nodes
	//this can be easly changed
	
	std::srand(time(NULL));



	std::vector<maze_module> to_be_generated_modules;

	//you can have first node generated randomly but 4 sided node is recomended since it usually results in larger mazes

	//to_be_generated_modules.push_back(modules[rand() % 11]);
	to_be_generated_modules.push_back(modules[0]);

	//main vector for storing the maze modules that have been correctly generated and will not be modified
	std::vector<maze_module> generated_modules;
	
	//centering the firss module, you can remove this since its position doesnt actualy matter 
	//especially if you can control where camera is looking
	to_be_generated_modules[0].module_sp.setPosition(window.getSize().x/2-Grid_Size/2, window.getSize().y/2- Grid_Size / 2);

	//this better be left alone even if the maze isnt centered
	//grid is basically virtual and doesnt depend on actual coordinates
	GRID[Grid_x / 2][Grid_y / 2] = 1;

	to_be_generated_modules[0].grid_position = std::pair<int, int>{ Grid_x / 2 ,Grid_y / 2 };
	
	//Maze size is basically max theoritical width and height the maze can have 
	//(it will never happen because chances are very low considering only straight lines must be generated to reach this size)
	
	int grid_counter = 0;

	//this is simply to see how long main algoryth needs
	auto start = std::chrono::high_resolution_clock::now();


	while (grid_counter < Maze_Size) {
		//size must be updated outside after for loop has been finished
		//otherwise it will never leave it
		int size = to_be_generated_modules.size();
		for (size_t i = 0; i < size; i++)
		{
			//if next to be generated node has a left face it will randomly add a node left of that node
			// this is being done for all 4 sides	
			
			if (to_be_generated_modules[i].left) {

				//if grid is taken then it will proceed as expected if not, then there is a chance that node will change direction this is done in else statement 
				if (GRID[to_be_generated_modules[i].grid_position.first - 1][to_be_generated_modules[i].grid_position.second] == 0) {
					
					
					//default sprites that will be loaded will be ones that have all sides closed 
					// it is after we check and set which sides must be opened that we update the sprite
					//to_be_generated_modules[i].open_sides[0] = 1;

					//update the grid
					GRID[to_be_generated_modules[i].grid_position.first - 1][to_be_generated_modules[i].grid_position.second] = 1;

					maze_module temp = right[rand() % right.size()];

					temp.grid_position.first = to_be_generated_modules[i].grid_position.first - 1;
					temp.grid_position.second = to_be_generated_modules[i].grid_position.second;

					temp.module_sp.setPosition(to_be_generated_modules[i].module_sp.getPosition().x - Grid_Size, to_be_generated_modules[i].module_sp.getPosition().y);
					//connected side is made false simply to make code faster by not checking this side 
					//after its time comes since we already know that its taken
					//temp.open_sides[1] = 1;
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
			//this repeats for all 4 sides
			if (to_be_generated_modules[i].right ) {

				if (GRID[to_be_generated_modules[i].grid_position.first + 1][to_be_generated_modules[i].grid_position.second] == 0) {

					//to_be_generated_modules[i].open_sides[1] = 1;


					GRID[to_be_generated_modules[i].grid_position.first + 1][to_be_generated_modules[i].grid_position.second] = 1;

					maze_module temp = left[rand() % left.size()];


					temp.grid_position.first = to_be_generated_modules[i].grid_position.first + 1;
					temp.grid_position.second = to_be_generated_modules[i].grid_position.second;

					temp.module_sp.setPosition(to_be_generated_modules[i].module_sp.getPosition().x + Grid_Size, to_be_generated_modules[i].module_sp.getPosition().y);
					//temp.open_sides[0]=1;
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

					//to_be_generated_modules[i].open_sides[2] = 1;

					GRID[to_be_generated_modules[i].grid_position.first][to_be_generated_modules[i].grid_position.second + 1] = 1;

					maze_module temp = up[rand() % up.size()];


					temp.grid_position.first = to_be_generated_modules[i].grid_position.first;
					temp.grid_position.second = to_be_generated_modules[i].grid_position.second + 1;

					temp.module_sp.setPosition(to_be_generated_modules[i].module_sp.getPosition().x, to_be_generated_modules[i].module_sp.getPosition().y + Grid_Size);
					//temp.open_sides[3] = 1;
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

					//to_be_generated_modules[i].open_sides[3] = 1;

					GRID[to_be_generated_modules[i].grid_position.first][to_be_generated_modules[i].grid_position.second - 1] = 1;

					maze_module temp = down[rand() % down.size()];

					temp.grid_position.first = to_be_generated_modules[i].grid_position.first;
					temp.grid_position.second = to_be_generated_modules[i].grid_position.second - 1;

					temp.module_sp.setPosition(to_be_generated_modules[i].module_sp.getPosition().x, to_be_generated_modules[i].module_sp.getPosition().y - Grid_Size);
					//temp.open_sides[2] = 1;
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


			//std::make_pair(to_be_generated_modules[i].grid_position.first, to_be_generated_modules[i].grid_position.second)
			mp[std::make_pair(to_be_generated_modules[i].grid_position.first, to_be_generated_modules[i].grid_position.second)] = generated_modules.size();
			//std::cout << pair_to_string(to_be_generated_modules[i].grid_position) << "  " << generated_modules.size() <<std::endl;
			//mp[std::string(pair_to_string(to_be_generated_modules[i].grid_position))]=generated_modules.size();

			


			//opening sides that need to be connected
			//to_be_generated_modules[i].module_sprite_changer();
			//once all sides for a to be generated_moduls are checked then it is added to generated modules and then erased
			generated_modules.push_back(to_be_generated_modules[i]);
			
			to_be_generated_modules.erase(to_be_generated_modules.begin());
			size--;
		}
		grid_counter++;
	}

	dead_end_closer(generated_modules);
	
	//getting the time it needed to finish the maze			
	auto now = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - start).count();
				
	std::cout << "milliseconds since start: " << duration << " ms" << std::endl;
	

	
	return generated_modules;
}

maze_module direction_changer(maze_module a, sides b) {

	//we take whichever side is about to collide with already existing node and adds a face to opposite direction
	//we do this by creating temporary node that is identical to existing node except for added face
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

void dead_end_closer(std::vector<maze_module> &maze) {

	
	
	for (size_t i = 0; i < maze.size(); i++)
	{
		if (maze[i].old_sides[0] ) {
			bool temp = 0;
			try {
				mp.at(std::pair<int, int>{maze[i].grid_position.first - 1, maze[i].grid_position.second});
			}
			catch (const std::exception& e) {
				temp = 1;
				}

			if(temp==0 && maze[mp.at(std::pair<int, int>{maze[i].grid_position.first - 1, maze[i].grid_position.second})].right)
			maze[i].open_sides[0] = 1;
		}
		if (maze[i].old_sides[1]) {
			bool temp = 0;
			try {
				mp.at(std::pair<int, int>{maze[i].grid_position.first + 1, maze[i].grid_position.second});
			}
			catch (const std::exception& e) {
				temp = 1;
			}

			if (temp == 0 && maze[mp.at(std::pair<int, int>{maze[i].grid_position.first + 1, maze[i].grid_position.second})].left)
				maze[i].open_sides[1] = 1;
		}
		if (maze[i].old_sides[2]) {
			bool temp = 0;
			try {
				mp.at(std::pair<int, int>{maze[i].grid_position.first, maze[i].grid_position.second+1});
			}
			catch (const std::exception& e) {
				temp = 1;
			}

			if (temp == 0 && maze[mp.at(std::pair<int, int>{maze[i].grid_position.first, maze[i].grid_position.second+1})].up)
				maze[i].open_sides[2] = 1;
		}
		if (maze[i].old_sides[3]) {
			bool temp = 0;
			try {
				mp.at(std::pair<int, int>{maze[i].grid_position.first, maze[i].grid_position.second-1});
			}
			catch (const std::exception& e) {
				temp = 1;
			}

			if (temp == 0 && maze[mp.at(std::pair<int, int>{maze[i].grid_position.first, maze[i].grid_position.second-1})].down)
				maze[i].open_sides[3] = 1;
		}

		/*if (maze[i].old_sides[1]) {
			if (Maze_GRID[maze[i].grid_position.first + 1][maze[i].grid_position.second] != nullptr
				&& Maze_GRID[maze[i].grid_position.first + 1][maze[i].grid_position.second]->right) maze[i].open_sides[1] = 1;
		}
		if (maze[i].old_sides[2]) {
			if (Maze_GRID[maze[i].grid_position.first][maze[i].grid_position.second + 1] != nullptr
				&& Maze_GRID[maze[i].grid_position.first][maze[i].grid_position.second + 1]->right) maze[i].open_sides[2] = 1;
		}
		if (maze[i].old_sides[3]) {
			if (Maze_GRID[maze[i].grid_position.first][maze[i].grid_position.second - 1] != nullptr
				&& Maze_GRID[maze[i].grid_position.first][maze[i].grid_position.second - 1]->right) maze[i].open_sides[3] = 1;
		}*/
		
		maze[i].module_sprite_changer();
	}

}


