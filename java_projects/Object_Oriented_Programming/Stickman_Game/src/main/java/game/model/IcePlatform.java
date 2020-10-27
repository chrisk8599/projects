package game.model;

/**
 * Represents an ice platform in the game
 */
public class IcePlatform extends EntityAbstraction {

    /**
     * Creates an ice platform with the specified image path, xPos, yPos,
     * width and height
     */
    public IcePlatform(String imagePath, double xPos, double yPos, double width, double height) {
        super(imagePath, xPos, yPos, width, height, Layer.FOREGROUND);
    }

    @Override
    public boolean isIcy() {
        return true;
    }



    public Entity makeCopy() {


        IcePlatform ice = null;

        try{
            ice = (IcePlatform) super.clone();
        }

        catch(CloneNotSupportedException e ){
            System.out.println("NOT MADE");
            e.printStackTrace();
        }

        return ice;
    }

}
