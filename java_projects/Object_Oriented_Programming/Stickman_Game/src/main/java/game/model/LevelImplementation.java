package game.model;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;
import java.util.Collection;
import java.util.List;
import static game.model.Collision.*;

/**
 * Represents the implementation of a level
 */
public class LevelImplementation implements Level {
    Entity imposter;
    private int count =0;

    public long levelTime;

    public String nextLevel ;

    public boolean isLast = false;

    /**
     * The controllable entity associated with the level
     */
    private Controllable hero;

    /**
     * All the entities associated with the level
     */
    private List<Entity> entities;

    /**
     * All the tangible entities associated with the level
     */
    private List<Entity> tangibles;

    /**
     * All the movable entities associated with the level
     */
    private List<MovableEntity> movableEntities;

    /**
     * All the enemies associated with the level
     */
    private List<Enemy> enemies;

    /**
     * The levels floor height
     */
    private double floorHeight;

    /**
     * The levels width
     */
    private double width;

    /**
     * The levels height
     */
    private double height;

    /**
     * Keeps track of whether or not the controllable entity
     * is sliding
     */
    private boolean slideEffect;

    /**
     * Keeps track of the controllable entities sliding velocity
     */
    private double slideVel;

    /**
     * Keep track of whether or not the level has been finished by the
     * controllable entity
     */
    private boolean finished;

    /**
     * Creates a new level object
     */
    public LevelImplementation() {
        this.tangibles = new ArrayList<>();
    }

    @Override
    public List<Entity> getEntities() {
        return this.entities;
    }

    @Override
    public double getWidth() {
        return this.width;
    }

    @Override
    public double getHeight() {
        return this.height;
    }

    @Override
    public void tick() {
        hero.tick();
        handleHeroVerticalMovement();
        handleHeroHorizontalMovement();
        deleteEnemiesMarkedForDeletion();
        handleEnemyMovement();
        handleMovableEntityMovement();
        handleEnemyAnimations();

        countHero();
    }

    @Override
    public double getFloorHeight() {
        return this.floorHeight;
    }

    @Override
    public double getHeroX() {
        return this.hero.getXPos();
    }

    @Override
    public int getHeroHealth() {
        return hero.getHealth();
    }

    @Override
    public void setHeroHealth(int hp) {
        hero.setHealth(hp);
    }

    @Override
    public void addHero() {
        entities.add(hero);
    }

    @Override
    public void countHero() {
        int c = 0;
        for(Entity te : tangibles){
            if(te.getClass().equals(Hero.class)) {
                c++;
            }



        }

    }

    @Override
    public void removeHero() {
        tangibles.remove(imposter);
    }

    @Override
    public List<Entity> getTangible() {
        return this.tangibles;
    }

    @Override
    public void setTangible() {
        this.tangibles.clear();
    }


    @Override
    public boolean jump() {
        return this.hero.signalJump();
    }

    @Override
    public boolean moveLeft() {
        return this.hero.signalMoveLeft();
    }

    @Override
    public boolean moveRight() {
        return this.hero.signalMoveRight();
    }

    @Override
    public boolean stopMoving() {
        return this.hero.signalStopMoving();
    }


    /**
     * Deals with the vertical movement of the controllable entity
     */
    private void handleHeroVerticalMovement() {

        if (!(hero.isFalling() || hero.isBouncing() || hero.isJumping())) {
            hero.initiateFall();
        }



        for (Entity entity: tangibles) {
            if (verticalCollision(hero, entity, hero.getYVel())) {
                if (entity.isFinishFlag()) {
                    finished = true;
                    return;

                }
                else if (hero.getYVel() > 0) {
                    boolean conserveMomentum = ((hero.getYPos() + hero.getHeight() != entity.getYPos()) && (hero.isMovingLeft() || hero.isMovingRight()));
                    hero.setYPos(entity.getYPos() - hero.getHeight());
                    hero.finishGravitationalState();
                    if (entity.isIcy()) {
                        double slideAcc = 0.1;
                        if (!slideEffect) {
                            if (hero.isMovingRight()) {
                                slideEffect = true;
                                if (conserveMomentum) {
                                    slideVel = hero.getXVel();
                                } else {
                                    slideVel = slideAcc;
                                }
                            } else if (hero.isMovingLeft()) {
                                slideEffect = true;
                                if (conserveMomentum) {
                                    slideVel =  -1 * hero.getXVel();
                                } else {
                                    slideVel = -1 * slideAcc;
                                }
                            }
                        } else {
                            double slideVelMaximum = 8;
                            if (hero.isMovingRight()) {
                                if (slideVel + slideAcc > slideVelMaximum) {
                                    slideVel = slideVelMaximum;
                                } else {
                                    slideVel += slideAcc;
                                }
                            } else if (hero.isMovingLeft()){
                                if (slideVel - slideAcc < -1 * slideVelMaximum) {
                                    slideVel = -1 * slideVelMaximum;
                                } else {
                                    slideVel -= slideAcc;
                                }
                            }
                        }
                    } else if (!entity.isIcy()) {

                        slideEffect = false;
                    }
                    return;
                } else {
                    hero.setYPos(entity.getYPos() + entity.getHeight());
                    hero.reverseYVel();
                    return;
                }
            }
        }

        for (Enemy enemy: enemies) {
            if (verticalCollision(hero, enemy, hero.getYVel())) {
                if (hero.getYVel() >= 0) {
                    hero.setYPos(enemy.getYPos() - hero.getHeight());
                    hero.initiateBounce();
                    enemy.markForDeletion();
                    return;
                } else {
                    hero.takeDamage();
                }
            }
        }

        hero.moveVertically();

    }

    /**
     * Deals with the hero's horizontal movement
     */
    private void handleHeroHorizontalMovement() {
        double dx;
        if (slideEffect) {
            dx = slideVel;
        } else if (hero.isMovingLeft()) {
            dx = hero.getXVel() * -1;
        } else if (hero.isMovingRight()) {
            dx = hero.getXVel();
        } else {
            return;
        }
        if (hero.isMovingRight() || hero.isMovingLeft() || slideEffect) {
            for (Entity entity: tangibles) {
                if (horizontalCollision(hero, entity, dx)) {
                    if (entity.isFinishFlag()) {
                        finished = true;
                        return;
                    }


                    if (hero.getXPos() < entity.getXPos()) {
                        hero.setXPos(entity.getXPos() - hero.getWidth());
                    } else {
                        hero.setXPos(entity.getXPos() + entity.getWidth());
                    }
                    slideEffect = false;
                    return;
                }
            }
            for (Enemy enemy: enemies) {
                if (horizontalCollision(hero, enemy, dx)) {
                    if (hero.getXPos() < enemy.getXPos()) {
                        hero.setXPos(enemy.getXPos() - hero.getWidth());
                    } else {
                        hero.setXPos(enemy.getXPos() + enemy.getWidth());
                    }
                    slideEffect = false;
                    hero.takeDamage();
                    return;
                }
            }
            if (slideEffect) {
                hero.setXPos(hero.getXPos() + dx);
            } else if (hero.isMovingLeft()) {
                hero.moveLeft();
            } else {
                hero.moveRight();
            }
        }
    }



    /**
     * Deals with the movement of all enemies
     */
    private void handleEnemyMovement() {

        for (Enemy enemy: enemies) {
            boolean leftCollision = false;
            boolean rightCollision = false;

            if (horizontalCollision(enemy, hero, enemy.getXVel())) {
                rightCollision = true;
            } else if (horizontalCollision(enemy, hero, -1 * enemy.getXVel())) {
                leftCollision = true;
            }

            for (Entity entity: tangibles) {
                if (horizontalCollision(enemy, entity, enemy.getXVel())) {
                    rightCollision = true;
                } else if (horizontalCollision(enemy, entity, -1 * enemy.getXVel())) {
                    leftCollision = true;
                }
            }

            for (Enemy enemyB: enemies) {
                if (horizontalCollision(enemy, enemyB, enemy.getXVel())) {
                    rightCollision = true;
                } else if (horizontalCollision(enemy, enemyB, -1 * enemy.getXVel())) {
                    leftCollision = true;
                }
            }

            enemy.moveHorizontally(hero, leftCollision, rightCollision);
        }

    }

    /**
     * Deals with the movement of all movable entities
     */
    private void handleMovableEntityMovement() {
        for (MovableEntity entity: movableEntities) {
            entity.moveHorizontally();
        }
    }

    /**
     * Deals with the animation of all enemies
     */
    private void handleEnemyAnimations() {
        for (Enemy enemy: enemies) {
            enemy.animate();
        }
    }

    /**
     * Deletes any enemies marked for deletion
     */
    private void deleteEnemiesMarkedForDeletion() {

        for (Enemy enemy: enemies) {
            if (enemy.isMarkedForDeletion()) {
                entities.remove(enemy);
                this.count++;
            }
        }



        enemies.removeIf(Enemy::isMarkedForDeletion);
    }

    public int getSlimeDead(){
        return this.count;
    }

    public void setSlimeDead(int dead){
        this.count = dead;
    }

    @Override
    public boolean isFinished() {
        return finished;
    }

    @Override
    public double getHeroY() {
        return hero.getYPos();
    }

    @Override
    public void setEntities(List<Entity> entities) {

        this.entities = entities;
        this.tangibles.addAll(entities);
        this.tangibles.removeIf(entity -> !entity.isTangible());

    }




    @Override
    public void setMovableEntities(List<MovableEntity> movableEntities) {
        this.movableEntities = movableEntities;
    }

    @Override
    public void setEnemies(List<Enemy> enemies) {
        this.enemies = enemies;
        this.tangibles.removeAll(enemies);
    }

    @Override
    public void setHero(Controllable hero) {
        this.hero = hero;
        this.slideVel = hero.getXVel();
    }

    @Override
    public void setLevelTime(long time) {

        this.levelTime = time;
    }

    @Override
    public Long getLevelTime() {
        return levelTime;
    }


    @Override
    public void setFloorHeight(double floorHeight) {
        this.floorHeight = floorHeight;
    }

    @Override
    public void setLevelWidth(double width) {
        this.width = width;
    }

    @Override
    public void setLevelHeight(double height) {
        this.height = height;
    }

    @Override
    public void setGround(Entity ground) {
        this.entities.add(ground);
        this.tangibles.add(ground);
    }

    public void removeEntities(){
        entities.clear();
        movableEntities.clear();
        enemies.clear();
        hero = null;
    }

    @Override
    public boolean isLast() {
        return this.isLast;
    }

    @Override
    public void checkLast(String nextlevel) {
        this.nextLevel = nextlevel;

        if(nextlevel.equals("")){
            this.isLast = true;
        }
        else {
            this.isLast = false;
        }
    }

    @Override
    public String getNextLevel() {
        return this.nextLevel;
    }




    @Override
    public Level makeCopy() {

        List<Entity> tang = getTangible();
        LevelImplementation lvl = null;

        try{
            CloneFactory factory = new CloneFactory();
            lvl = (LevelImplementation) super.clone();
            Controllable player = factory.getHeroClone(hero);
            List<Entity> entities = new ArrayList<>();
            List<MovableEntity> moveable = new ArrayList<>();
            List<Enemy> enemies = new ArrayList<>();



            for(Entity e  : this.entities){

                if(e.getClass().equals(Hero.class)){

                }
                else if(e.getClass().equals(Cloud.class)){
                    Entity copy  = factory.getEntityClone(e);
                    entities.add(copy);
                    moveable.add((MovableEntity) copy);
                }
                else if(e.getClass().equals(Slime.class)){
                    Entity copy  = factory.getEntityClone(e);
                    entities.add(copy);
                    enemies.add((Enemy) copy);
                }
                else{
                    Entity copy  = factory.getEntityClone(e);
                    entities.add(copy);
                }



            }

            lvl.setTangible();
            lvl.setEntities(entities);
            lvl.tangibles = tang;
            lvl.setMovableEntities(moveable);
            lvl.setEnemies(enemies);
            lvl.setHero(player);

        }

        catch(CloneNotSupportedException e ){
            e.printStackTrace();
        }

        return lvl;
    }


}
