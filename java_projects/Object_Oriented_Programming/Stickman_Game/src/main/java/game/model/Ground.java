package game.model;

/**
 * Represents the ground in the level
 */
public class Ground extends EntityAbstraction {

    public Ground(String imagePath, double xPos, double yPos, double width, double height) {
        super(imagePath, xPos, yPos, width, height, Layer.FOREGROUND);
    }



    public Entity makeCopy() {


        Ground ground = null;

        try{
            ground = (Ground) super.clone();
        }

        catch(CloneNotSupportedException e ){
            System.out.println("NOT MADE");
            e.printStackTrace();
        }

        return ground;
    }
}
