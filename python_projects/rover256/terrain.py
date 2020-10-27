
class Tile:

	def __init__(self,tile,coordinates):
		"""
		Initialises the terrain tile and attributes
		"""
		self.tile = tile
		self.explored = 0
		self.type = tile[0]
		if len(self.tile) == 3 :
			self.elev_1 = int(tile[1])     #IF there is two elevation inputs, set 2 separate variables as each
			self.elev_2 = int(tile[2])	  #otherwise just set elevation to the single input
		else :
			self.elevation = int(tile[1])
		self.coordinates = coordinates

		pass


	def elevation(self):
		"""
		Returns an integer value of the elevation number
		of the terrain object
		"""
		if len(self.tile) == 3 :
			self.elevation = self.elev_2
		else:
			pass

	def is_shaded(self):
		"""
		Returns True if the terrain tile is shaded, otherwise False
		"""
		if self.type == 'shaded':
			return True
		else:
			return False
		pass

	def is_explored(self):
		self.explored = 1
		return

	
