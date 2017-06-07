The game works on the functions of probabilty, class and file I/O operations.
Basically it is a text based game that requires the user to Move carefully till the end of the grid. The user can encounter one of three things on every location:
1) Enemy ship
2) Friend Ship
3) Puzzle.

If the user encounters enemy ship, he has to fight it to proceed to next level.
In order to fight the enemy ship, the user has to select a gun. The gun user selects is used to fight against the enemy. We can choose from three guns, "Rock, Fire and Water"
We have to consider the fact that:
Rock can beat Fire
Fire can beat Water
Water can beat Rock
If the enemy beats the user, the user loses 50% of its health. if the user beats the enemy ship, he can proceed without any damage

If the user encounters friend ship, he instantly gains 25% of its health back

If the user encounters a puzzle, he needs to solve it in order to proceed. Resulting in the wrong answer of the puzzle would end the game immidiately.


It should be noted that the probabilty of encountering any of these things is equal in the middle row, but is altered on the right and left rows. The probabilty of encountering enemy and friendship is low on left side , while probabilty of puzzle is higher. on the other hand, probability of enemy and friend ship is higher on right size, but probability of puzzle is lower.


The external libraries that are used are only <fstream> in order to work with file io.

The game can be simply played by executing and compiling the code, and the rest of the game is self explanatory.

It should be noted that the input should be in exact same case as asked by the program. 


Group member inputs:
Zohaib: The whole idea, rules and concept of the game. Probabilty idea. Made the function on how to response when a friendship or puzzle is encountered in the location.Made ship class. Gathered all the riddles and their answers. Tested the game and made the readme file. Did documentations for the functions made.

Tabish: Made step by step approach to link all the functions. Designed classes, game map and logics on how to implement the rules. Worked with the loops. Did documentations for the functions made.