import struct

class Tile:
	def __init__(self, stringData ):  # floorType, direction, laserNums, laserDir):
		line = stringData.split(",")
		self.floorType = int(line[0])
		self.direction = int(line[1])
		self.laserNums = int(line[2])
		self.laserDir = int(line[3])
		walls = list(line[4])
		out = []
		for i in range(4):
			if int(walls[i]):
				out.append(i)

		self.walls = out

	def pack(self):
		return struct.pack("!BB")

class Card:
	def __init__(self, priority, cardType):
		self.priority = priority
		self.cardType = cardType

	def pack():
		return struct.pack("!iB", self.priority, self.cardType)

class Player:
	def __init__(self, conn, name, id):
		self.conn = conn
		self.name = name
		self.id = id
		self.hp = 9
		self.life = 3
		self.direct = 0  # 0 = up
		self.shutDown = False
		self.archive = (0,0)

	def getMove(self):
		data = conn.recv(1024)
		cards = []
		b = data.pop(0)
		b = struct.unpack("!?")
		self.shutDown = b

		for i in xrange(5):
			i *= 2
			p, t = struct.unpack("!Ib")
			cards.append(Card(p, n))
		self.cards = cards

	def moveTo(self, pos):
		self.p = pos

	def updateArchive(self):
		self.archive = self.p



class Game:
	def __init__(self, filename):
		self.board=[]
		with open(filename, "rU") as f:
    		for line in f:
    			line = line.strip()
    			row = []
    			
    			for t in line.split(";"):
    				row.append(Tile(t))
    			board.append(row)

    	self.players = {}
    	self.startPos = [
    		(0,0), (1,0), (2, 0), (3, 0), (4, 0),
    		(5, 0), (6, 0), (7, 0), (8, 0)
    		]

    	self.boarder = Tile("1,0,0,0,0000")

    def addPlayer(self, conn, name):
    	i = max(self.players.keys() + [-1])+1
    	self.players[i] = Player(conn, name, i)
    	self.players[i].moveTo(startPos[i])

    	# send data to the player
    def playTurn(self):
    	for p in players.values():
    		p.getMove()


    	for regNum in xrange(5):
    		thisRegister = []
    		lowestP = 900
    		lowestId = 0
    		for p in self.players.values():
    			thisRegister.append(([p.id], p.cards[regNum]))
    		thisRegister.sort(key=lambda x: -x[1].priority)

    		for i, card in thisRegister:
    			cardType = card.cardType
    			player = players[i]

    			if cardType == 1:
    				self.move(player, 1, player.direct)
    			elif cardType == 2:
    				self.move(player, 2, player.direct)
				elif cardType == 3:
    				self.move(player, 3, player.direct)
				elif cardType == 4:
    				self.move(player, 1, (player.direct +2)%4)
    			elif cardType == 5:
    				player.direct = (player.direct + 1) %4
    			elif cardType == 6:
    				player.direct = (player.direct - 1) %4
				elif cardType == 7:
    				player.direct = (player.direct + 2) %4

			# express conveyors
			for player in players.values():
				tile = getTileAt(player.pos[0], player.pos[1])
				tileType = tile.floorType
				if tileType in [3, 5, 7, 9, 11, 13]:
					nextTile = self.singleSoftMove(player, tile.direction)
					if nextTile.floorType in [4, 5, 10, 11]:
						player.direct = (player.direct -1)%4
					elif nextTile.floorType in [6, 7, 12, 13]:
						player.direct = (player.direct +1)%4

			# conveyors

			for player in players.values():
				tile = getTileAt(player.pos[0], player.pos[1])
				tileType = tile.floorType
				if tileType in [2, 4, 6, 8, 10, 12]:
					nextTile = self.singleSoftMove(player, tile.direction)
					if nextTile.floorType in [4, 5, 10, 11]:
						player.direct = (player.direct -1)%4
					elif nextTile.floorType in [6, 7, 12, 13]:
						player.direct = (player.direct +1)%4


			# pushers

			for player in players.values():
				tile = getTileAt(player.pos[0], player.pos[1])
				tileType = tile.floorType
				if tileType == 14 and regNum % 2 == 0:
					self.move(player, 1, tile.direction)
				elif tileType == 15 and regNum %2 == 1:
					player.direct = (player.direct -1)%4



			# gears
			for player in players.values():
				tileType = tile.floorType
				if tileType == 16:
					player.direct = (player.direct +1)%4
				elif tileType == 17:
					player.direct = (player.direct -1)%4

    			

	def move(player, distance, direction):
		tile = getTileAt(player.pos[0], player.pos[1])
		if direction in tile.walls:
			return False:

		nextTile, otherPos = getTileInDir(player.pos[0], player.pos[1], direction)
		if (direction + 2)%4 in nextTile.walls:
			return False:

		clear = true
		for other in self.players:
			if other.pos == self.pos:
				clear = move(other, 1, direction)
				break
		if clear:
			player.moveTo(otherPos)
			if distance == 1:
				return True
			else:
				return move(player, distance-1, direction)

		else: return False


	def singleSoftMove(player, direction):
		tile = getTileAt(player.pos[0], player.pos[1])
		if direction in tile.walls:
			return False:

		nextTile, otherPos = getTileInDir(player.pos[0], player.pos[1], direction)
		if (direction + 2)%4 in nextTile.walls:
			return False:

		clear = true
		for other in self.players:
			if other.pos == self.pos:
				return False
		if clear:
			player.moveTo(otherPos)
			return nextTile


	def getTileAt(x, y):
		return board[y][x]

	def getTileInDir(x, y, direct):
		if direct == 0:
			y -= 1
		elif direct == 2:
			y += 1
		elif direct == 1:
			x += 1
		elif direct == 3:
			x -= 1

		if x <0 or x == len(self.board[0]) or y <0 or y == len(self.board):
			return self.boarder, (x, y)

		else:
			return getTileAt(x, y), (x, y)

    			














        