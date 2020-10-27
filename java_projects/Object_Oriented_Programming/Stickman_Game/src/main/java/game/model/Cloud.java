package game.model;

import game.view.GameWindow;

/**
 * Represents a cloud entity in the level
 */
public class Cloud extends MovableEntityAbstraction {

    /**
     * Creates a new Cloud with the given image path,
     * x position, y position, width, height and velocity
     */
    public Cloud(String imagePath, double xPos, double yPos, double width, double height, double xVel) {
        super(imagePath, xPos, yPos, width, height, xVel / GameWindow.ticksPerSecond(), Layer.BACKGROUND);
    }


    public MovableEntity makeMovableCopy() {
        System.out.println("MADE A COPY OF cloud");

        Cloud cloud = null;

        try{
            cloud = (Cloud) super.clone();
        }

        catch(CloneNotSupportedException e ){
            System.out.println("NOT MADE");
            e.printStackTrace();
        }

        return cloud;
    }


    @Override
    public boolean isMoveable(){
        return true;
    }

    @Override
    public Entity makeCopy() {


        Cloud cloud = null;

        try{
            cloud = (Cloud) super.clone();
        }

        catch(CloneNotSupportedException e ){
            System.out.println("NOT MADE");
            e.printStackTrace();
        }

        return cloud;
    }

}
