package game.model;


import java.util.ArrayList;

class Caretaker {

    Memento savedArticles ;

    public void addMemento(Memento m) { savedArticles = m; }

    public Memento getMemento() { return savedArticles;}

}
