package game.model;

import java.time.Duration;
import java.util.List;

public class Score implements Cloneable {


    private  int overallScore;
    private  int currentScore;
    private long levelLimit;


    public Score(Long levelTime){
        levelLimit = levelTime;
    }



    public void generateOverallScore(List<Integer> scores){
        overallScore = 0;
        for (Integer value : scores){
            overallScore += value;
        }

        if(overallScore< 0){
            overallScore = 0;
        }



    }

    public void setLevelLimit(long levelLimit) {
        this.levelLimit = levelLimit;
    }

    public void generateCurrentScore(Duration interval, int slimeDead){
        currentScore = (int) (levelLimit - interval.toSeconds()) + slimeDead*100 ;
        if(currentScore< 0){
            currentScore = 0;
        }
    }


    public void setCurrentScore(int currentScore) {
        this.currentScore = currentScore;
    }

    public void setOverallScore(int overallScore) {
        this.overallScore = overallScore;
    }

    public int getOverallScore(){
        return overallScore;
    }

    public int getCurrentScore(){
        return currentScore;
    }



    public Score makeCopy(){
        System.out.println("MADE A COPY OF score");

        Score score = null;

        try{
            score = (Score) super.clone();
        }

        catch(CloneNotSupportedException e ){
            System.out.println("NOT MADE");
            e.printStackTrace();
        }

        return score;
    }
}
