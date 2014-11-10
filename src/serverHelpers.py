import struct, random, socket

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
	def __init__(self, conn, id):
		self.conn = conn
		# self.name = name
		self.id = id
		self.hp = 9
		self.life = 3
		self.direct = 0  # 0 = up
		self.shutDown = False
		self.archive = (0,0)
		self.packed = ""

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

	def pack(self):
		self.packed = "".join([struct.pack("!BBBBBB10s",
			self.pos[0], self.pos[1], self.direct, self.hp, self.life, self.id, self.name.ljust(10, " ")
			), "".join([x.pack() for x in self.cards])])




class Game:
	def __init__(self, filename):
		self.board=[]
		self.cards = []
		self.players = {}
		self.startPos = [
			(14, 5), (14, 6), (14, 3), (14, 8),
			(14, 1), (14, 10), (14, 0), (14, 11)
			]

		for line in open(filename, "rU"):
			line = line.strip()
			row = []

			for t in line.split():
				row.append(Tile(t))
			self.board.append(row)

		cards = []
		cardDefs = {
			"Move 1":1,
			"Move 2":2,
			"Move 3":3,
			"Back up":4,
			"Rotate Right":5,
			"Rotate Left":6,
			"U-Turn":7}

		for line in open("cards.txt", "rU"):
			num, t = line.strip().strip("#").split(" / ")
			self.cards.append(Card(int(num), cardDefs[t]))


		self.boarder = Tile("1,0,0,0,0000")

	def addPlayer(self, conn):
		i = max(self.players.keys() + [-1])+1
		self.players[i] = Player(conn, i)
		self.players[i].moveTo(startPos[i])

    	# send data to the player

	def getMoves(self):
		map(lambda x: x.getMove(), self.players.values())

	def sendData():
		cards.shuffle()
		p = 0

		packedB = "".join(["".join([t.pack for t in row]) for row in self.board])

		map(lambda x:x.pack(), self.players.values())

		vs = self.players.values()


		for i in range(len(players.keys())):
			p = self.players[i]
			vs.remove(p)
			mess = "".join(map(lambda x: x.packed, vs)) + p.packed

			p.conn.sendall(mess)
			vs.append(p)


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
			return False

		nextTile, otherPos = getTileInDir(player.pos[0], player.pos[1], direction)
		if (direction + 2)%4 in nextTile.walls:
			return False

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
			return False

		nextTile, otherPos = getTileInDir(player.pos[0], player.pos[1], direction)
		if (direction + 2)%4 in nextTile.walls:
			return False

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

