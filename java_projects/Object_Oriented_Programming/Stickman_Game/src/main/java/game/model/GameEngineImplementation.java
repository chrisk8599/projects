package game.model;

import java.time.Duration;
import java.time.Instant;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class GameEngineImplementation implements GameEngine {
    SaveFiles save;

    Caretaker caretaker = new Caretaker();

    Originator originator = new Originator();

    int saveFiles = 0, currentArticle = 0;

    List<Integer> scores = new ArrayList<>();

    List<String> levelFiles = new ArrayList<>();

    /**
     * The height of the game engine
     */
    private double height;

    /**
     * The current level
     */
    private Level currentLevel;

    /**
     * Map of all the levels
     */
    private Map<Integer, Level> levels;

    /**
     * Used to create distinct level id's for each level
     */
    private int levelId;

    /**
     * Level id of the current level
     */
    private int currentLevelId;

    List<String> builtLevels = new ArrayList<>();

    /**
     * Json path to the level configuration file
     */
    private String jsonPath;

    /**
     * Used to keep track of how long it takes the user to complete the game
     */
    private Instant start;

    private Instant levelStart;

    /**
     * Used to keep track of how long it takes the user to complete the game
     */
    private Duration interval;
    private Duration currentinterval;

    /**
     * The number of lives the hero has
     */
    private int lives;


    private Score score;

    /**
     * Creates the game engine using the specified json configuration file and height
     * @param jsonPath The path to the json configuration file containing the level information
     * @param height The height of the game engine's window
     */
    public GameEngineImplementation(String jsonPath, double height) {
        this.jsonPath = jsonPath;
        this.height = height;
        this.levels = new HashMap<>();
        this.levelId = 1;
        this.currentLevelId = 1;
        this.lives = 3;
        scores.add(0);

        createLevels();
        startLevel();
        start = Instant.now();
        score = new Score(currentLevel.getLevelTime());
    }

    /**
     * Creates the levels associated with the json file
     */
    public void createLevels() {
        builtLevels.add(this.jsonPath);
        levelFiles.add(this.jsonPath);
        LevelBuilder levelBuilder = new LevelBuilder(this.jsonPath);
        LevelDirector levelDirector = new LevelDirector(levelBuilder);
        levelDirector.buildLevel();
        this.levels.put(this.levelId, levelDirector.getLevel());
        levelId += 1;
        levelStart = Instant.now();
    }

    @Override
    public void startLevel() {
        this.currentLevel = levels.get(currentLevelId);

    }

    @Override
    public Level getCurrentLevel() {
        return this.currentLevel;
    }

    @Override
    public boolean jump() {
        return this.currentLevel.jump();
    }

    @Override
    public boolean moveLeft() {
        return this.currentLevel.moveLeft();
    }

    @Override
    public boolean moveRight() {
        return this.currentLevel.moveRight();
    }

    @Override
    public boolean stopMoving() {
        return this.currentLevel.stopMoving();
    }
    @Override
    public boolean undo(){
        if(saveFiles > 0){

            System.out.println("Undo");

            return undoLogic();
        }
        else {
            return false;
        }

    }
    @Override
    public boolean save(){
        if(saveFiles>0){
            System.out.println("Already Saved!");
        }
        else {
            System.out.println("save");
        }


        return saveLogic();
    }

    @Override
    public void tick() {
        this.currentLevel.tick();
        interval = Duration.between(start, Instant.now());
        currentinterval = Duration.between(levelStart, Instant.now());

        score.generateCurrentScore(currentinterval, currentLevel.getSlimeDead());

    }

    @Override
    public void resetCurrentLevel() {
        levelStart = Instant.now();
        this.lives--;
        if (this.lives == 0) {
            scores.add(score.getCurrentScore());

            score.generateOverallScore(scores);
            return;
        }

        this.jsonPath = levelFiles.get(currentLevelId-1);

        LevelBuilder levelBuilder = new LevelBuilder(this.jsonPath);
        LevelDirector levelDirector = new LevelDirector(levelBuilder);
        levelDirector.buildLevel();
        this.levels.put(this.currentLevelId, levelDirector.getLevel());
        score.setLevelLimit(currentLevel.getLevelTime());


        startLevel();
    }

    @Override
    public boolean isFinished() {
        if(currentLevel.isFinished()){

            if(currentLevel.isLast()){
                scores.add(score.getCurrentScore());

                score.generateOverallScore(scores);
                return true;
            }

            else {
                scores.add(score.getCurrentScore());
                int health = currentLevel.getHeroHealth();
                score.generateOverallScore(scores);

                this.jsonPath = currentLevel.getNextLevel();
                currentLevelId+=1;

                createLevels();
                startLevel();
                score.setLevelLimit(currentLevel.getLevelTime());
                currentLevel.setHeroHealth(health);

                return false;
            }
        }

        else{
            return false;
        }


    }


    @Override
    public Duration getDuration() {
        return interval;
    }

    @Override
    public boolean gameOver() {
        return this.lives == 0;
    }

    @Override
    public int getLives() {
        return this.lives;
    }

    @Override
    public int getOverallScore() {
        return score.getOverallScore();
    }

    @Override
    public int getCurrentScore() {
        return score.getCurrentScore();
    }

    @Override
    public void setCurrentScore(int value) {
        score.setCurrentScore(value);

    }

    @Override
    public void setOverallScore(int value) {
        score.setOverallScore(value);
    }




    public boolean undoLogic(){

        if(currentArticle >= 1 ){


            currentLevel.removeEntities();

            LevelImplementation older = (originator.restoreFromMemento( caretaker.getMemento() ));

            older.addHero();




            this.levels.put(this.currentLevelId,older);

            startLevel();



            score.setLevelLimit(save.getCurrentScore() - save.getSlimedead()*100);
            setCurrentScore(save.getCurrentScore());

            levelStart = Instant.now();

            setOverallScore(save.getOverallScore());

            scores.clear();
            scores.add(save.getOverallScore());

            setOverallScore(score.getOverallScore());
            score.generateOverallScore(scores);

            this.lives = save.getLives();
            currentLevel.setHeroHealth(save.getHealth());

            this.currentLevelId =save.getCurrentLevelId();
            this.levelId = save.getLevelId();




            saveFiles = 0 ;
            saveLogic();



            return true;

        } else {

            System.out.println("works");

            return false;

        }

    }

    public boolean saveLogic(){

        if (saveFiles < 1){

            currentLevel.removeHero();
            save = new SaveFiles();

            save.setLevelId(levelId);

            save.setLevels(this.levels);

            save.setLives(this.lives);

            save.setCurrentLevelId(currentLevelId);

            save.setHealth(currentLevel.getHeroHealth());

            save.setCurrentScore(getCurrentScore());

            save.setOverallScore(getOverallScore());

            save.setDuration(getDuration());

            save.setSlimedead(currentLevel.getSlimeDead());

            CloneFactory levelMaker  = new CloneFactory();

            LevelImplementation savedState = (LevelImplementation) levelMaker.getClone(currentLevel);

            originator.set(savedState);

            caretaker.addMemento( originator.storeInMemento() );

            saveFiles++;

            currentArticle++;


            return true;

        }

        return false;

    }




}


