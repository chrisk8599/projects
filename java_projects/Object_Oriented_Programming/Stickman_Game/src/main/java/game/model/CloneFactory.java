package game.model;

public class CloneFactory {


    public Level getClone(Level levelSample){
        return levelSample.makeCopy();
    }

    public Controllable getHeroClone (Controllable hero){return hero.makeHeroCopy();}

    public MovableEntity getMovableClone(MovableEntity entity){
        return entity.makeMovableCopy();
    }

    public Enemy getEnemyClone(Enemy entity){
        return entity.makeEnemyCopy();
    }


    public Entity getEntityClone(Entity entity){
        return entity.makeCopy();
    }





}
