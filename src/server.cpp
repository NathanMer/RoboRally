#include<std>;
#include<iostream>;
#include <fstream>
#include <vector>

// needs its own game logic

int main(int argc, char const *argv[])
{
	/* 
	initiate a server (gui launcher?)
		max players before start

	game begin:
	distribute cards to each player and send board info

	while game is not won (use a while true with a break statment)
		wait until either all players have sent in their choices or 90 seconds have passed
		compute outcomes, send updated positions for each frame, new cards and any other required info.
	send out victory message and exit
	 */
	return 0;
}

std::vector<std::vector<Tile>> loadBoard(std::string filename, Tile * board) {		//this needs to be fixed
	ifstream fileThing;
	std::string line;
	fileThing.open(filename);
	if (fileThing.is_open()) {
		getline(fileThing, line);
		std::istringstream iss(line);
	    int maxX, maxY;
	    if (!(iss >> maxX >> maxY)) { break; }

	    std::vector<std::vector<Tile>> board (maxY);

		for (int i = 0; i < maxY; i++)
		{
			std::vector<Tile> row (maxX);
			for (int j = 0; j < maxX; j++)
			{
				getline(fileThing, line);

				Tile t;	// here we need to convert the string into a tile object

				row.insert(j, t);

			}
			board.insert(i, row);
		}
	}
	return board;
}


