package game.model;


import java.util.List;

public class Memento {


    private LevelImplementation article;

    public Memento(LevelImplementation articleSave) {
        article = articleSave;
    }

    public LevelImplementation getSavedArticle() {
        return article;
    }
}
