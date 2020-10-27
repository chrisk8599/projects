package game.model;

import java.time.Duration;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class SaveFiles {

    int overallScore;
    int currentScore;

    Duration duration;
    int slimedead;
    int health;
    int lives;
    int levelId;

    int currentLevelId;

    Map<Integer, Level> levels = new HashMap<>();

    public void setLevelId(int levelId) {
        this.levelId = levelId;
    }

    public int getLevelId() {
        return levelId;
    }

    public Map<Integer, Level> getLevels() {
        return levels;
    }

    public void setLevels(Map<Integer, Level> levels) {
        if(this.levels.equals(null)){

        }
        else{
            this.levels.clear();
        }

        this.levels = levels;

    }

    public int getCurrentLevelId() {
        return currentLevelId;
    }

    public void setCurrentLevelId(int currentLevelId) {
        this.currentLevelId = currentLevelId;
    }

    public int getLives() {
        return lives;
    }

    public void setLives(int lives) {
        this.lives = lives;
    }

    public int getHealth() {
        return health;
    }

    public void setHealth(int health) {
        this.health = health;
    }

    public void setDuration(Duration duration){
        this.duration = duration;
    }

    public void setSlimedead(int dead){
        this.slimedead = dead;
    }

    public void setOverallScore(int score){
        this.overallScore = score;
    }
    public void setCurrentScore(int score){
        this.currentScore = score;
    }

    public int getSlimedead() {
        return slimedead;
    }

    public int getOverallScore(){
        return overallScore;
    }

    public int getCurrentScore() {
        return currentScore;
    }
}
