from rover import Rover
import planet
import loader
from terrain import Tile

def quit_game():
	quit()		   #This will be used for the quit option
	pass

def menu_help():
	print('')
	print('START <level file> - Starts the game with a provided file.')
	print('QUIT - Quits the game')                                         #This shows the help menu
	print('HELP - Shows this message')
	print('')
	menu()
	pass

def menu_start_game(filepath):
	"""
	Will start the game with the given file path
	"""
	tile = []

	y = 0

	try:
		open(filepath,"r")
	except FileNotFoundError:
		print("\n",end="")                               #Checking if valid filepath
		print("Level file could not be found\n")
		quit()

	planet_object = loader.load_level(filepath)
	rover = Rover(planet_object.coordinates,planet_object.tiles,planet_object.height,planet_object.width)

	while y < planet_object.height:
		rows = []
		x = 0
		while x < planet_object.width:
			terrain = Tile(planet_object.tiles[y][x],rover.coordinate)      #Here we create a matrix with each element
			rows.append(terrain)											#Being a tile object. The matrix is in the
			x += 1															#form of the planet.

		tile.append(rows)
		y += 1
	scan = 0
	tile[rover.coordinate[1]][rover.coordinate[0]].is_explored()
	while True:
		user = input()                 #Reading user inputs it performs appropriate functions
		func = user.split(" ")
		if func[0] == 'FINISH':
			y = 0
			explored = 0
			while y < len(tile):
				x = 0
				while x < len(tile[y]):
					if tile[y][x].explored == 1:
						explored += 1
					x += 1
				y+=1
			print("\n",end="")
			print("You explored {}% of {}".format(int(100*explored/(planet_object.width*planet_object.height)),planet_object.name))
			print("\n",end="")
			break

		elif len(func) == 1 :
			if func[0] == 'STATS':
				y = 0
				explored = 0
				while y < len(tile):
					x = 0
					while x < len(tile[y]):
						if tile[y][x].explored == 1:
							explored += 1
						x += 1
					y+=1
				print("\n",end="")
				print('Explored: {}%'.format(int(100*explored/(planet_object.width * planet_object.height))))
				print('Battery: {}/100'.format(rover.battery))
				print("\n",end="")
			else:
				print('Cannot perform this command')
		elif func[0] == 'WAIT':
			if tile[rover.coordinate[1]][rover.coordinate[0]].type == 'shaded':
				rover.wait(int(func[1]))
			elif tile[rover.coordinate[1]][rover.coordinate[0]].type == 'plains':
				rover.battery += int(func[1])
		elif func[0] == 'MOVE':
			i = 0
			while i < int(func[2]):
				if func[1] == 'N':
					index = rover.coordinate[1] - i
					while index < 0:
						index = planet_object.height + index
					if index >= planet_object.height:
						index = index - planet_object.height
					else:
						pass
					tile[index][rover.coordinate[0]].is_explored()
					if tile[index][rover.coordinate[0]].is_shaded():
						pass
					else:
						rover.battery += 1
				if func[1] == 'S':
					index = rover.coordinate[1] + i
					if index >= planet_object.height:
						index = index - planet_object.height
					elif index < 0:
						index = planet_object.height + index
					else:
						pass
					tile[index][rover.coordinate[0]].is_explored()
					if tile[index][rover.coordinate[0]].is_shaded():
						pass
					else:
						rover.battery += 1
				if func[1] == 'E':
					index = rover.coordinate[0] + i
					if index >= planet_object.width:
						index = index - planet_object.width
					elif index < 0 :
						index = index + planet_object.width
					else:
						pass
					tile[rover.coordinate[1]][index].is_explored()
					if tile[rover.coordinate[1]][index].is_shaded():
						pass
					else:
						rover.battery += 1
				if func[1] == 'W':
					index = rover.coordinate[0] - i
					if index < 0 :
						index = index + planet_object.width
					elif index >= planet_object.width:
						index = index - planet_object.width
					else:
						pass
					tile[rover.coordinate[1]][index].is_explored()
					if tile[rover.coordinate[1]][index].is_shaded():
						pass
					else:
						rover.battery += 1
				i += 1

			if func[1] == 'N' :
				index -= 1
				while index < 0:
						index = planet_object.height + index
				if index >= planet_object.height:
					index = index - planet_object.height
				else:
					pass
				if tile[index][rover.coordinate[0]].is_shaded():
						pass
				else:
					rover.battery += 1
			elif func[1] == 'S' :
				index += 1
				if index >= planet_object.height:
					index = index - planet_object.height
				elif index < 0:
					index = planet_object.height + index
				else:
					pass
				if tile[index][rover.coordinate[0]].is_shaded():
					pass
				else:
					rover.battery += 1
			elif func[1] == 'W':
				if tile[rover.coordinate[1]][index-1].is_shaded():
					pass
				else:
					rover.battery += 1
			elif func[1] == 'E':
				if tile[rover.coordinate[1]][index+1].is_shaded():
					pass
				else:
					rover.battery += 1
			rover.move(func[1],int(func[2]))


		elif func[1] == 'shade':
			scan += 1
			print("\n",end="")
			m = rover.coordinate[1] - 2
			counter_2 = 0
			while counter_2 < 5:
				t = rover.coordinate[0] - 2
				row = []
				if m >= planet_object.height:
					m = m - planet_object.height
				if m < 0:
					m = planet_object.height + m

				while t < (rover.coordinate[0] + 3) and t < planet_object.width:

					if t >= planet_object.width:
						t = t - planet_object.width
					if t < 0 :
						t = planet_object.width + t
					if m == rover.coordinate[1] and t == rover.coordinate[0]:
						row.append("|H")
						tile[m][t].is_explored()
					elif tile[m][t].is_shaded() and t == (rover.coordinate[0] + 2):
						row.append("|#|")
						tile[m][t].is_explored()
					elif tile[m][t].is_shaded():			#THis loop creates a matrix with each element corresponding
						row.append("|#")
						tile[m][t].is_explored()			#to criteria given for SCAN SHADED and prints accordingly
					elif t == (rover.coordinate[0] + 2):
						row.append("| |")
						tile[m][t].is_explored()
					else :
						row.append("| ")
						tile[m][t].is_explored()
					t += 1
				z = 0

				while z < len(row):

					if z == len(row) - 1:
						print(row[z])
					else:
						print(row[z],end = "",sep = '')
					z += 1
				m += 1
				counter_2 += 1
			print("\n",end="")

		elif func[1] == 'elevation':
			scan += 1
			x = 0
			print("\n",end="")
			if rover.coordinate[1] >= planet_object.height:
				rover.coordinate[1] = rover.coordinate[1] - planet_object.height
			if rover.coordinate[0] >= planet_object.width:
				rover.coordinate[0] = rover.coordinate[0] - planet_object.width
			try:
				elev = tile[rover.coordinate[1]][rover.coordinate[0]].elevation
				eleva = int(elev)
			except TypeError:
				tile[rover.coordinate[1]][rover.coordinate[0]].elevation()
				elev = tile[rover.coordinate[1]][rover.coordinate[0]].elevation
				eleva = int(elev)

			m = rover.coordinate[1] - 2
			counter_2 =0
			while counter_2 <5:
				t = rover.coordinate[0] - 2
				row = []
				if m >= planet_object.height :
					m = m - planet_object.height
				while t < (rover.coordinate[0] + 3):
					try:
						tile_elevation = tile[m][t].elevation
						elevation = int(tile_elevation)
					except TypeError:
						tile[m][t].elevation()
						tile_elevation = tile[m][t].elevation
						elevation = int(tile_elevation)
						pass
					if len(tile[rover.coordinate[1]][rover.coordinate[0]].tile) == 3:
						x = 1
					if m == rover.coordinate[1] and t == rover.coordinate[0]:
						row.append("|H")
						tile[m][t].is_explored()
					elif x == 1:
						if t == (rover.coordinate[0] + 2):
							row.append("| |")
						else:
							row.append("| ")
					elif len(tile[m][t].tile) == 3:
						if tile[m][t].elev_1 == elev:
							if tile[m][t].elev_1 > tile[m][t].elev_2 and t == (rover.coordinate[0] + 2):
								row.append("|\\|")
								tile[m][t].is_explored()              #this loop creates a matrixwith each element corresponding
							elif tile[m][t].elev_1 > tile[m][t].elev_2:   #to criteria for SCAN ELEVATION ACCORDINGLY
								row.append("|\\")
								tile[m][t].is_explored()
							elif t == (rover.coordinate[0] + 2):
								row.append("|/|")
								tile[m][t].is_explored()
							else:
								row.append("|/")
								tile[m][t].is_explored()
						elif tile[m][t].elev_2 == elev:
							if tile[m][t].elev_2 > tile[m][t].elev_1 and t == (rover.coordinate[0] + 2):
								row.append("|\\|")
								tile[m][t].is_explored()
							elif tile[m][t].elev_2 > tile[m][t].elev_1:
								row.append("|\\")
								tile[m][t].is_explored()
							elif t == (rover.coordinate[0] + 2):
								row.append("|/|")
								tile[m][t].is_explored()
							else:
								row.append("|/")
								tile[m][t].is_explored()

					elif elevation > eleva and t == (rover.coordinate[0] + 2):
						row.append("|+|")
						tile[m][t].is_explored()
					elif elevation > eleva:
						row.append("|+")
						tile[m][t].is_explored()
					elif elevation < eleva and t == (rover.coordinate[0] + 2):
						row.append("|-|")
						tile[m][t].is_explored()
					elif elevation < eleva:
						row.append("|-")
						tile[m][t].is_explored()
					elif t == (rover.coordinate[0] + 2):
						row.append("| |")
						tile[m][t].is_explored()
					else :
						row.append("| ")
						tile[m][t].is_explored()
					t += 1

				z = 0
				while z < len(row):

					if z == len(row) - 1:
						print(row[z])
					else:
						print(row[z],end = "",sep = '')
					z += 1
				m += 1
				counter_2 += 1
			print("\n",end="")



		pass


def menu():
	"""
	Start the menu component of the game
	"""
	user_input = input()
	if user_input == 'QUIT' :
		quit_game()
	elif user_input == 'HELP':	                      #According to user input it
		menu_help()                                   #Performs appropriate functions
		menu()
	elif user_input[0:5] == 'START':
		menu_start_game(user_input[6:len(user_input)])
	else :
		print("\n",end="")
		print("No menu item")
		print("\n",end="")
	pass
menu()
