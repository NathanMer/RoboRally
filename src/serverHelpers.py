import struct

class Tile:
	def __init__(self, floorType, direction, laserNums, laserDir):
		self.floorType = floorType
		self.direction = direction
		self.laserNums = laserNums
		self.laserDir = laserDir

	def pack(self):
		return struct.pack("")