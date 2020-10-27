import java.io.IOException;
import java.io.File;
import java.util.Scanner;
import java.util.ArrayList;
import java.io.PrintWriter;



/**
 * Maze Game
 *
 * INFO1113 Assignment 1
 * 2018 Semester 2
 *
 * The Maze Game.
 * In this assignment you will be designing a maze game.
 * You will have a maze board and a player moving around the board.
 * The player can step left, right, up or down.
 * However, you need to complete the maze within a given number of steps.
 *
 * As in any maze, there are walls that you cannot move through. If you try to
 * move through a wall, you lose a life. You have a limited number of lives.
 * There is also gold on the board that you can collect if you move ontop of it.
 *
 * Please implement the methods provided, as some of the marks are allocated to
 * testing these methods directly.
 *
 * @author YOU :)
 * @date 23 August 2018
 *
 */
public class MazeGame {
    /* You can put variables that you need throughout the class up here.
     * You MUST INITIALISE ALL of these class variables in your initialiseGame
     * method.
     */

    // A sample variable to show you can put variables here.
    // You would initialise it in initialiseGame method.
    // e.g. Have the following line in the initialiseGame method.
    // sampleVariable = 1;
    static int sampleVariable;
	static String line;
	static String[] lines;
	static ArrayList<char[]> board ;
	static int lives;
	static String boardLine;
	static int steps;
	static int gold;
	static int earn;
	static int rows;
	static int posX;
	static int posY;
	static Scanner user;
	static Scanner scan;
	static String input;
	static int x;
	static int y;
	static int currentX;
	static int currentY;
	static String userInput;
	static File mazeFile;
	static String[] saveList;
	static char nextPos;
	static int a;
	static int b;
	static int c;
	static int d;
	static int e;
	static int f;
	static int g;
	static int h;

    /**
     * Initialises the game from the given configuration file.
     * This includes the number of lives, the number of steps, the starting gold
     * and the board.
     *
     * If the configuration file name is "DEFAULT", load the default
     * game configuration.
     *
     * NOTE: Please also initialise all of your class variables.
     *
     * @args configFileName The name of the game configuration file to read from.
     * @throws IOException If there was an error reading in the game.
     *         For example, if the input file could not be found.
     */
    public static void initialiseGame(String configFileName) throws IOException {
        // TODO: Implement this method.
		mazeFile = new File(configFileName);
		if(!mazeFile.exists()){
			throw new IOException();
		}
		else{
			scan = new Scanner(mazeFile);
			line = scan.nextLine();
			lines = line.split(" ");
			lives = Integer.parseInt(lines[0]);
			steps = Integer.parseInt(lines[1]);
			gold = Integer.parseInt(lines[2]);
			rows = Integer.parseInt(lines[3]);
			board = new ArrayList<char[]>();

			while (scan.hasNextLine()){
				boardLine = scan.nextLine();
				board.add(boardLine.toCharArray());
			}
		}
	}



    /**
     * Save the current board to the given file name.
     * Note: save it in the same format as you read it in.
     * That is:
     *
     * <number of lives> <number of steps> <amount of gold> <number of rows on the board>
     * <BOARD>
     *
     * @args toFileName The name of the file to save the game configuration to.
     * @throws IOException If there was an error writing the game to the file.
     */
    public static void saveGame(String toFileName) throws IOException {
        // TODO: Implement this method.
 		File f = new File(toFileName);
		PrintWriter writer = new PrintWriter(f);
		writer.printf("%d %d %d %d\n",lives,steps,gold,rows);
		for (char[] q : board) {
			for(  a = 0 ; a < q.length ; a++) {
				writer.print(q[a]);
			}
			writer.print("\n")	;
		}
		writer.close();
	}
    /**
     * Gets the current x position of the player.
     *
     * @return The players current x position.
     */
    public static int getCurrentXPosition() {
        // TODO: Implement this method.
		for (char[] w : board){
			g=0;
			for ( b = 0 ; b<w.length ; b++){
				if (w[b] == '&'){
					posX = g;
				}
				g+=1;
			}
		}
       return posX;
    }

    /**
     * Gets the current y position of the player.
     *
     * @return The players current y position.
     */
    public static int getCurrentYPosition() {
        // TODO: Implement this method.
		h = 0;
		for (char[] r : board){
			for ( c = 0 ; c<r.length ; c++){
				if (r[c] == '&'){
					posY = h;
				}
			}
			h+=1;
		}
       return posY;
    }

    /**
     * Gets the number of lives the player currently has.
     *
     * @return The number of lives the player currently has.
     */
    public static int numberOfLives() {
        // TODO: Implement this method.
		return lives;

    }

    /**
     * Gets the number of remaining steps that the player can use.
     *
     * @return The number of steps remaining in the game.
     */
    public static int numberOfStepsRemaining() {
        // TODO: Implement this method.
        return steps;
    }

    /**
     * Gets the amount of gold that the player has collected so far.
     *
     * @return The amount of gold the player has collected so far.
     */
    public static int amountOfGold() {
        // TODO: Implement this method.
        return gold;
    }


    /**
     * Checks to see if the player has completed the maze.
     * The player has completed the maze if they have reached the destination.
     *
     * @return True if the player has completed the maze.
     */
    public static boolean isMazeCompleted() {
        // TODO: Implement this method.
		for(char[] t : board){
			for(d=0;d<t.length;d++){
				if(t[d]=='@'){
					return false;
				}
			}
		}
    		return true;
    }

    /**
     * Checks to see if it is the end of the game.
     * It is the end of the game if one of the following conditions is true:
     *  - There are no remaining steps.
     *  - The player has no lives.
     *  - The player has completed the maze.
     *
     * @return True if any one of the conditions that end the game is true.
     */
    public static boolean isGameEnd() {
        // TODO: Implement this method.
		if ( steps < 0 || lives ==  0 ||  isMazeCompleted()|| lives < 0 || steps == 0 ){
			return true;
		}
		 return false;


    }

    /**
     * Checks if the coordinates (x, y) are valid.
     * That is, if they are on the board.
     *
     * @args x The x coordinate.
     * @args y The y coordinate.
     * @return True if the given coordinates are valid (on the board),
     *         otherwise, false (the coordinates are out or range).
     */
    public static boolean isValidCoordinates(int x, int y) {
        // TODO: Implement this method.
		if ( x > ((board.get(0).length)-1) || x < 0 || y < 0 || y > (rows - 1)){
			return false;
		}
			return true;
    }

    /**
     * Checks if a move to the given coordinates is valid.
     * A move is invalid if:
     *  - It is move to a coordinate off the board.
     *  - There is a wall at that coordinate.
     *  - The game is ended.
     *
     * @args x The x coordinate to move to.
     * @args y The y coordinate to move to.
     * @return True if the move is valid, otherwise false.
     */
    public static boolean canMoveTo(int x, int y) {
        // TODO: Implement this method.
			if(!isValidCoordinates(x,y) || isGameEnd() ) {
				return false;
			}
			if(board.get(y)[x] == '#') {
				return false;
			}
				return true;
			}




    /**
     * Move the player to the given coordinates on the board.
     * After a successful move, it prints "Moved to (x, y)."
     * where (x, y) were the coordinates given.
     *
     * If there was gold at the position the player moved to,
     * the gold should be collected and the message "Plus n gold."
     * should also be printed, where n is the amount of gold collected.
     *
     * If it is an invalid move, a life is lost.
     * The method prints: "Invalid move. One life lost."
     *
     * @args x The x coordinate to move to.
     * @args y The y coordinate to move to.
     */
    public static void moveTo(int x, int y) {
        // TODO: Implement this method.

		if (canMoveTo(x,y)){
			System.out.printf("Moved to (%d, %d).\n", x,y);
			nextPos = board.get(y)[x];
			if(nextPos == '0' || nextPos == '1' || nextPos == '2'|| nextPos == '3'|| nextPos == '4'|| nextPos == '5'|| nextPos == '6'|| nextPos == '7'|| nextPos == '8'|| nextPos == '9'){
				int earn = Character.getNumericValue(nextPos) ;
				gold += earn ;
				System.out.println("Plus " + nextPos + " gold.");
				}
			board.get(currentY)[currentX] = '.';
			board.get(y)[x] = '&';
			steps -=1;

		}

		else  {
			steps -= 1;
			lives -= 1;
			System.out.println("Invalid move. One life lost.");

		}
	}



    /**
     * Prints out the help message.
     */
    public static void printHelp() {
        // TODO: Implement this method.

		System.out.println("Usage: You can type one of the following commands.\n" +
							"help         Print this help message.\n" +"board        Print the current board.\n" +
							"status       Print the current status.\n" +"left         Move the player 1 square to the left.\n" +"right        Move the player 1 square to the right.\n" +
						   "up           Move the player 1 square up.\n" +"down         Move the player 1 square down.\n" +"save <file>  Save the current game configuration to the given file.");}
    /**
     * Prints out the status message.
     */
    public static void printStatus() {
        // TODO: Implement this method.
		System.out.println("Number of live(s): " + lives + "\n" +"Number of step(s) remaining: " + steps + "\n" +"Amount of gold: " + gold);
	}

    /**
     * Prints out the board.
     */
    public static void printBoard() {
        // TODO: Implement this method.

		for (f =0 ; f < board.size() ; f++){
			System.out.println(board.get(f));
    }
	}

    /**
     * Performs the given action by calling the appropriate helper methods.
     * [For example, calling the printHelp() method if the action is "help".]
     *
     * The valid actions are "help", "board", "status", "left", "right",
     * "up", "down", and "save".
     * [Note: The actions are case insensitive.]
     * If it is not a valid action, an IllegalArgumentException should be thrown.
     *
     * @args action The action we are performing.
     * @throws IllegalArgumentException If the action given isn't one of the
     *         allowed actions.
     */
    public static void performAction(String action) throws IllegalArgumentException {
        // TODO: Implement this method.
			userInput = action.toLowerCase();
			currentX =getCurrentXPosition();
			currentY = getCurrentYPosition();
			if (userInput.equals("help")){
				printHelp();
			}
			else if (userInput.equals("board")){
				printBoard();
			}
			else if (userInput.equals("status")){
				printStatus();
			}
			else if (userInput.equals("left")){

			moveTo(currentX - 1,currentY);
			}
			else if (userInput.equals("right")){

				moveTo(currentX + 1,currentY);
			}

			else if (userInput.equals("up")){

				moveTo(currentX,currentY-1);
			}

			else if (userInput.equals("down")){
				moveTo(currentX,currentY +1);
			}

			else if (userInput.contains("save ")){
				saveList = action.split(" ");
				if(saveList.length > 2 || saveList.length < 2) {
				throw new IllegalArgumentException();
				}
				try{
					saveGame(saveList[1]);
				}
				catch(IOException e) {
					System.out.println("Error: Could not save the current game configuration to '" + saveList[1] + "'.");
				}
			}
			else if (userInput.isEmpty()){

			}

			else{
				throw new IllegalArgumentException();
			}

			if( lives ==0 && steps ==0 ) {
				System.out.println("Oh no! You have no lives and no steps left.");
				System.out.println("Better luck next time!");

			}

			else if(isMazeCompleted()) {
				System.out.println("Congratulations! You completed the maze!");
				System.out.println("Your final status is:");
				printStatus();


			}

			else if(lives == 0) {
				System.out.println("Oh no! You have no lives left.");
				System.out.println("Better luck next time!");
			}



			else if(steps == 0) {

				System.out.println("Oh no! You have no steps left.");
				System.out.println("Better luck next time!");
		}

    }

    /**
     * The main method of your program.
     *
     * @args args[0] The game configuration file from which to initialise the
     *       maze game. If it is DEFAULT, load the default configuration.
     */
    public static void main(String[] args) {

        // Run your program (reading in from args etc) from here.


		if (args.length == 0 ){
			System.out.println("Error: Too few arguments given. Expected 1 argument, found 0.");
			System.out.println("Usage: MazeGame [<game configuration file>|DEFAULT]");
			return;
		}

		if (args.length > 1){
			System.out.println("Error: Too many arguments given. Expected 1 argument, found " + Integer.toString(args.length)+".");
			System.out.println("Usage: MazeGame [<game configuration file>|DEFAULT]");
			return;
		}


		try {
			initialiseGame(args[0]);
			}
		catch (IOException e){
			System.out.println("Error: Could not load the game configuration from '"  + args[0] +  "'." ) ;
			return;
			}





			user = new Scanner(System.in);
			while(user.hasNextLine()){
				input = user.nextLine();
				try{
					performAction(input);
				}
				catch(IllegalArgumentException e){
					System.out.println("Error: Could not find command '" + input + "'.\n" + "To find the list of valid commands, please type 'help'." );
				}
			}
			if(!isGameEnd()) {
					System.out.println("You did not complete the game.");
				}





    }

}
