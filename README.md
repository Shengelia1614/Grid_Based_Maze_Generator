Maze Generator using sfml library

algorythm is not heavily dependent on the sfml library as such with little modifications it can be used with any other library


unfortunatly due to the randomness of the algorythm size of the maze can vary,
it is possible to make it more consistenet by certain certain values or using modified random generator.

size incosistancy in large grid sizes in not something that can't be fixed. 
for example you could compare final generated maze to the grid size and if its smaller than desired size that you can set youself,
you could generate a new one untill it satisfies the size criteria

or you could modify the generator function so it can start generating new maze in random location in grid after the first one is generated and it turns out to be too small.
you could run dead_end_opener after all mazes have been generated to create one continious maze.
allthough, you may need to add function to check whether or not mazes actually have faces that connect to each other somewhere, which shouldn't be all that difficult
in fact i may actaully add these functionalities in the future

nevertheless, maze will never go past the grid size so you can consistently make it smaller 

here are some examples of generated mazes:

white lines are actuall coridors, not walls
red squares are dead end walls

![Screenshot 2025-02-26 153721](https://github.com/user-attachments/assets/fdcd5987-214a-4d24-99b0-b4fe14c41a69)
![Screenshot 2025-02-26 153736](https://github.com/user-attachments/assets/c36f5289-2a82-4155-aa6e-ff9bfe385e2a)
![Screenshot 2025-02-26 153742](https://github.com/user-attachments/assets/1ab24fc0-5c28-4544-acc2-6d7f8149f5ff)
![Screenshot 2025-02-26 153749](https://github.com/user-attachments/assets/189e9c7a-ce0a-4e71-9cfb-a10e2296ccfd)

