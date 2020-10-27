from terrain import Tile
class Rover:

	def __init__(self, coordinate,tiles,height,width):
		"""
		Initialises the rover
		"""
		self.coordinate = coordinate
		self.battery = 100
		self.tiles = tiles
		self.count = 0
		self.height = height
		self.width = width
		pass

	def move(self, direction, cycles):
		"""
		Moves the rover on the planet
		"""
		if direction == 'N':
			if cycles > self.battery:
				cycles = self.battery     #Each of the following accounts for the Movement of the rover NSEW
				self.battery = 0		  #it accounts for the battery loss and how much it has travelled so far.
			else:
				self.battery = self.battery - cycles
			new_y = self.coordinate[1] - cycles

			if cycles > self.height:
				self.count += self.height
			else :
				self.count += cycles
			while new_y < 0 :
				new_y = self.height + new_y

			self.coordinate = [self.coordinate[0],new_y]

		elif direction == "E":

			if cycles > self.battery:
				cycles = self.battery
				self.battery = 0
			else:
				self.battery -= cycles
			new_x = self.coordinate[0] + cycles
			if cycles > self.width:
				self.count += self.width
			else :
				self.count += cycles
			while new_x > self.width :
				new_x = new_x - self.width
			self.coordinate = [new_x,self.coordinate[1]]

		elif direction == "S":

			if cycles > self.battery:
				cycles = self.battery
				self.battery = 0
			else:
				self.battery -= cycles
			new_y = self.coordinate[1] + cycles
			if cycles > self.height:
				self.count += self.height
			else :
				self.count += cycles
			while new_y > self.height :
				new_y = new_y - self.height
			self.coordinate = [self.coordinate[0],new_y]

		elif direction == "W":

			if cycles > self.battery:
				cycles = self.battery
				self.battery = 0
			else:
				self.battery -= cycles
			new_x = self.coordinate[0] - cycles
			if cycles > self.width:
				self.count += self.width
			else :
				self.count += cycles
			while new_x < 0 :
				new_x = new_x + self.width
			self.coordinate = [new_x,self.coordinate[1]]

		pass

	def wait(self, cycles):
		"""
		The rover will wait for the specified cycles
		"""
		if cycles > self.battery:
			cycles = self.battery
			self.battery = 0
		else:
			self.battery -= cycles
		pass
	
