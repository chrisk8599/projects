package game.model;

/**
 * Represents a finish flag in the game
 */
public class FinishFlag extends EntityAbstraction {

    /**
     * Creates a finish flag with the specified image path, xPos, yPos, width and height
     */
    public FinishFlag(String imagePath, double xPos, double yPos, double width, double height) {
        super(imagePath, xPos, yPos, width, height, Layer.FOREGROUND);
    }

    @Override
    public boolean isFinishFlag() {
        return true;
    }


    public Entity makeCopy() {


        FinishFlag flag = null;

        try{
            flag = (FinishFlag) super.clone();
        }

        catch(CloneNotSupportedException e ){
            System.out.println("NOT MADE");
            e.printStackTrace();
        }

        return flag;
    }

}
