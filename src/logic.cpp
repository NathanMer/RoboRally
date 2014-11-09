#include <vector>
#include <chrono>
#include <thread>
#include <boost/asio.hpp>


#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3

#define EMPTY 0
#define PIT 1
#define CON_STRAIGHT 2
#define FCON_STRAIGHT 3
#define CON_LEFT 4
#define FCON_LEFT 5
#define CON_RIGHT 6
#define FCON_RIGHT 7
#define CON_MERGE 8
#define FCON_MERGE 9
#define CON_TJOIN_LEFT 10
#define FCON_TJOIN_LEFT 11
#define CON_TJOIN_RIGHT 12
#define FCON_TJOIN_RIGHT 13
#define PUSH_EVEN 14
#define PUSH_ODD 15
#define GEAR_CW 16
#define GEAR_CCW 17
#define WRENCH 18
#define HAMMER 19


struct Card
{
	int priority;
	byte type;
};

// enum Direction { NORTH, SOUTH, EAST, WEST };



struct Player
{
	byte posX;
	byte posY;
	byte health;
	byte life;
	byte sprite;
	string name;
	std::vector<card> choices;
};

struct Wall
{
	bool north;
	bool south;
	bool east;
	bool west;
};

// enum FloorType { EMPTY, PIT, 
// 	CON_STRAIGHT, FCON_STRAIGHT,
// 	CON_LEFT, FCON_LEFT,
// 	CON_RIGHT, FCON_RIGHT,
// 	CON_MERGE, FCON_MERGE,
// 	CON_TJOIN_LEFT, FCON_TJOIN_LEFT,
// 	CON_TJOIN_RIGHT, FCON_TJOIN_RIGHT,
// 	PUSH_EVEN, PUSH_ODD,
// 	GEAR_CW, GEAR_CCW,
// 	WRENCH, HAMMER
// };

struct Laser
{
	byte number;		// 0, 1, 2, 3 depending on how many beams there are
	int direction;
};

struct Tile
{
	// this should be drawn in reverse order of listing (ie FloorType comes before lasers)
	Laser lasers;
	Wall walls;
	int type;
	int direction;
};

struct Player {
	uint8 posX;
	uint8 posY;
	uint8 health;
	uint8 life;
	uint8 spriteId;
	std::string name;
	Card choices [5];

};


class Game
{
public:
	player p;
	bool choicesMade = false;
	bool timedOut = false;
	std::vector<player> others;
	std::vector<Card> available;
	ip::tcp::socket sock;

	sock.connect()
	

	game(arguments);
	~game();

	/* data */
};

void gameLogic() {

	Game g;
	/* 
	join server
	get the necessary parts of the game object and first hand of cards
	poplulate the provided game object with this info
	*/

	every turn:
		wait for the user (90 second timer?)
		send in the selected cards
		wait for the server to reply with game updates
		apply these updates to the game object one register at a time while the changes are being drawn to the screen

	 */


	std::chrono::milliseconds dura( 100 )

	while (true) {
		for (int t = 0; t < 900; i++) {
			if (g.choicesMade) {
				break;
			}
			std::this_thread::sleep_for( dura );
		}
		int p = 0
		if (! g.choicesMade) {
			for (int i = 0; i < 5; ++i)
			{
				if (g.p.choices[i] == nullptr) {
					g.p.choices[i] = g.available.at(p);
					p++;
				}
			}
		}
		// send choices

		// get some responses
		


	}
	return 0;
}