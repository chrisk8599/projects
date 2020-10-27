package game.model;

import java.util.List;

public class Originator{

    private LevelImplementation article;

    public void set(LevelImplementation newArticle) {


        this.article = newArticle;

    }

    public Memento storeInMemento() {

        return new Memento(article);

    }


    public LevelImplementation restoreFromMemento(Memento memento) {

        article = memento.getSavedArticle();


        return article;

    }

}
