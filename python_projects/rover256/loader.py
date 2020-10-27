from planet import Planet

def load_level(filename):
	"""
	Loads the level and returns an object of your choosing
	"""
	in_file = open(filename,"r")
	lines = in_file.read().splitlines()
	counter = 0
	no_tiles = 0
	planet = []
	tiles = []
	rows = []
	counter_1 = 0
	for line in lines :
		if counter == 1:
			planet_info = line.split(",")       #THis receives the planet name and puts it in the planet list
			planet.append(planet_info[1])
		elif counter < 4 and counter > 1:
			planet_info = line.split(",")
			planet.append(int(planet_info[1]))    #THis receives the planet width and height and puts it in the planet list
		elif counter == 4 :
			planet_info = line.split(",")
			if len(planet_info) != 3 :
				print("\n",end="")
				print("Unable to load level file\n")
				quit()
			else:
				x_coord = int(planet_info[1])        #This receives the rover coordinates and puts it in the planet list.
				y_coord = int(planet_info[2])

				if x_coord > planet[1] or y_coord > planet[2]:
					print("\n",end="")
					print("Unable to load level file\n")	    #This performs the appropriate checks if the level file
					quit()										#is appropriate
				elif x_coord >= 0 and y_coord >= 0 :
					planet.append([x_coord,y_coord])
					pass
				else :
					print("\n",end="")
					print("Unable to load level file\n")
					quit()

		if counter > 6 :
			no_tiles += 1
			elev = line.split(',')
			if len(elev) == 3 :
				if elev[2] > elev[1]:
					print("Unable to load level file")
					quit()
			counter_1 += 1

			rows.append(elev)
			if counter_1 % planet[1] == 0:       #This creates a matrix of elements which are the attributes of a tile.
				tiles.append(rows)				 #The matrix is in the form of the planet
				rows = []

		counter += 1


	if planet[1] < 5 or planet[2] < 5 :	         #appropriate checks if the level file is appropriate
		print("\n",end="")
		print("Unable to load level file\n")
		quit()

	return Planet(planet[0],planet[1],planet[2],planet[3],tiles)
	pass
