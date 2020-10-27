import java.util.*;
import java.io.*;


public class ThreeDigits{

    static String search;
    static  String file;
    static String[] forbidden = new String[500];
    static Node start;
    static Node goal;
    static List<Node> expanded = new ArrayList<Node>();
    static List<Node> idsExpanded = new ArrayList<Node>();
    static List<Node> solution = new ArrayList<Node>();
    static int counter = 0 ;
    static List<Node> queue = new ArrayList<Node>();
    static int idsFinished = 0;
    static int check = 1;
    static int iterator =0;
    static int tracker = 0;
    static int failed =0;

    public static void main(String[] args){

        search  = args[0];
        file = args[1];

        try {
            File input = new File(file);
            Scanner read = new Scanner(input);
            start = new Node(read.nextLine());
            goal = new Node(read.nextLine());

            if(read.hasNextLine()){
                forbidden = read.nextLine().split(",");
            }

            read.close();
        }
        catch (FileNotFoundException e) {

        }

        start.setLevel(0);

        switch(search){
            case "B":
                BFS();
                break;
            case "D":
                DFS();
                break;
            case "I":
                IDS();
                break ;
            case "G":
                GREEDY(start);
                break;
            case "A":
                A(start);
                break ;
            case "H":
                HILL(start);
                break;
        }


        if(expanded.size()>=1000 || failed ==1){
            System.out.println("No solution found.");
        }
        else{
            for(int i = solution.size()-1 ; i>=0 ; i--){
                if(i == 0){
                    System.out.println(solution.get(i).getNumber());
                }
                else{
                    System.out.print(solution.get(i).getNumber() + ',');
                }
            }
        }



        if(expanded.size() >= 1000){
            for (int i = 0; i < 1000; i++) {
                if (i == 0) {
                    System.out.print(expanded.get(i).getNumber());
                }
                else {
                    System.out.print(',' + expanded.get(i).getNumber());
                }

            }
        }
        else {
            for (int i = 0; i < expanded.size(); i++) {
                if (i == 0) {
                    System.out.print(expanded.get(i).getNumber());
                } else {
                    System.out.print(',' + expanded.get(i).getNumber());
                }

            }
        }

    }




    public static List<Node> makeChildren(Node node){
        List<Node> children = new ArrayList<Node>();
        int starting = Integer.parseInt(node.getNumber());
        char[] starts = node.getNumber().toCharArray();

        if(counter == 0){

            node.setLevel(0);

            if(starts[0] != '0'){
                String result;

                if(starting <200){
                    result = String.format("%03d",starting-100);
                }
                else{
                    result = Integer.toString(starting -100);
                }

                int flag = 1;

                for (String s : forbidden) {
                    if (result.equals(s)) {
                        flag =0;
                    }
                }
                if(flag ==1){
                    Node res = new Node(result);
                    res.setParent(node);
                    children.add(res);
                }

            }
            if(starts[0] != '9'){
                String result = Integer.toString(starting +100);
                int flag = 1;
                for (String s : forbidden) {
                    if (result.equals(s)) {
                        flag =0;
                    }
                }
                if(flag ==1){
                    Node res = new Node(result);
                    res.setParent(node);
                    children.add(res);
                }

            }
            if(starts[1] != '0'){
                String result;
                if(starting <100){
                    result = String.format("%03d",starting-10);

                }
                else{
                    result = Integer.toString(starting -10);

                }

                int flag = 1;
                for (String s : forbidden) {
                    if (result.equals(s)) {
                        flag =0;
                    }
                }
                if(flag ==1){
                    Node res = new Node(result);
                    res.setParent(node);
                    children.add(res);
                }
            }
            if(starts[1] != '9'){
                String result;
                if(starting <100){
                    result = String.format("%03d",starting+10);
                }
                else{
                    result = Integer.toString(starting +10);

                }
                int flag = 1;
                for (String s : forbidden) {
                    if (result.equals(s)) {
                        flag =0;
                    }
                }
                if(flag ==1){
                    Node res = new Node(result);
                    res.setParent(node);
                    children.add(res);
                }
            }
            if(starts[2] != '0'){
                String result;
                if(starting <100){
                    result = String.format("%03d",starting -1);

                }
                else{
                    result = Integer.toString(starting -1);

                }
                int flag = 1;
                for (String s : forbidden) {
                    if (result.equals(s)) {
                        flag =0;
                    }
                }
                if(flag ==1){
                    Node res = new Node(result);
                    res.setParent(node);
                    children.add(res);
                }
            }
            if(starts[2] != '9'){
                String result;
                if(starting <100){
                    result = String.format("%03d",starting+1);

                }
                else{
                    result = Integer.toString(starting +1);

                }

                int flag = 1;
                for (String s : forbidden) {
                    if (result.equals(s)) {
                        flag =0;
                    }
                }
                if(flag ==1){
                    Node res = new Node(result);
                    res.setParent(node);
                    children.add(res);
                }
            }



        }
        else{



            check  =1;
            int flag =1;
            int diff = Math.abs(Integer.parseInt(node.getNumber()) - Integer.parseInt(node.getParent().getNumber()));



            for(int i = 0 ; i < expanded.size();i++){
                if(expanded.get(i).getNumber().equals(node.getNumber())){


                    if(i ==0){

                    }
                    else if(diff == Math.abs(Integer.parseInt(expanded.get(i).getNumber())- Integer.parseInt(expanded.get(i).getParent().getNumber()))){
                        flag = 0;
                        check =0;
                        node.setCheck();
                    }
                }

            }




            if(flag == 1) {

                if (starts[0] != '0' && diff != 100) {
                    String result;
                    if (starting < 200) {
                        result = String.format("%03d", starting - 100);

                    } else {
                        result = Integer.toString(starting -100);

                    }
                    int trig = 1;
                    for (String s : forbidden) {
                        if (result.equals(s)) {
                            trig =0;
                        }
                    }
                    if(trig ==1){
                        Node res = new Node(result);
                        res.setParent(node);
                        children.add(res);
                    }

                }
                if (starts[0] != '9' && diff != 100) {
                    String result = Integer.toString(starting +100);
                    int trig = 1;
                    for (String s : forbidden) {
                        if (result.equals(s)) {
                            trig =0;
                        }
                    }
                    if(trig ==1){
                        Node res = new Node(result);
                        res.setParent(node);
                        children.add(res);
                    }

                }
                if (starts[1] != '0' && diff != 10) {
                    String result;
                    if (starting < 100) {
                        result = String.format("%03d", starting - 10);

                    } else {
                        result =Integer.toString(starting -10);

                    }
                    int trig = 1;
                    for (String s : forbidden) {
                        if (result.equals(s)) {
                            trig =0;
                        }
                    }
                    if(trig ==1){
                        Node res = new Node(result);
                        res.setParent(node);
                        children.add(res);
                    }
                }
                if (starts[1] != '9' && diff != 10) {
                    String result;
                    if (starting < 100) {
                        result = String.format("%03d", starting + 10);

                    } else {
                        result = Integer.toString(starting +10);
                    }
                    int trig = 1;
                    for (String s : forbidden) {
                        if (result.equals(s)) {
                            trig =0;
                        }
                    }
                    if(trig ==1){
                        Node res = new Node(result);
                        res.setParent(node);
                        children.add(res);
                    }

                }
                if (starts[2] != '0' && diff != 1) {
                    String result;
                    if (starting < 100) {
                        result = String.format("%03d", starting - 1);
                    } else {
                        result = Integer.toString(starting -1);
                    }
                    int trig = 1;
                    for (String s : forbidden) {
                        if (result.equals(s)) {
                            trig =0;
                        }
                    }
                    if(trig ==1){
                        Node res = new Node(result);
                        res.setParent(node);
                        children.add(res);
                    }

                }
                if (starts[2] != '9' && diff != 1) {
                    String result;
                    if (starting < 100) {
                        result = String.format("%03d", starting + 1);
                    } else {
                        result = Integer.toString(starting +1);
                    }

                    int trig = 1;
                    for (String s : forbidden) {
                        if (result.equals(s)) {
                            trig =0;
                        }
                    }
                    if(trig ==1){
                        Node res = new Node(result);
                        res.setParent(node);
                        children.add(res);
                    }
                }

            }




        }


        counter++;

        for(Node child : children){
            child.setLevel(child.getParent().getLevel() + 1);
        }

        return children;
    }


    public static void BFS(){
        queue.add(start);
        while(queue.size() > 0 ){
            if(queue.get(0).getNumber().equals(goal.getNumber())){
                expanded.add(goal);
                solution.add(goal);

                Node search = queue.get(0);

                while(true){
                    if(search.getParent().equals(start)){
                        solution.add(start);
                        return;
                    }
                    else{
                        solution.add(search.getParent());
                        search = search.getParent();

                    }
                }

                //must add solution code


            }

            else if(expanded.size() == 1000){
               return;

            }

            List<Node> child = new ArrayList<Node>();
            queue.get(0).setChildren();
            child.addAll(queue.get(0).getChildren());


            if(check == 1){
                queue.get(0).setVisited();
                queue.addAll(child);
                expanded.add(queue.get(0));
                queue.remove(0);

            }
            else{

                queue.remove(0);
            }


        }



    }

    public static void DFS(){
        queue.add(start);

        while(queue.size() > 0 ){

            if(queue.get(0).getNumber().equals(goal.getNumber()) ){
                expanded.add(goal);
                solution.add(goal);

                Node search = queue.get(0);

                while(true){
                    if(search.getParent().equals(start)){
                        solution.add(start);
                        break;
                    }
                    else{
                        solution.add(search.getParent());
                        search = search.getParent();

                    }
                }



                break;
            }
            else if(expanded.size() == 1000){


                break;
            }

            Node current = queue.get(0);
            current.setChildren();
            List<Node> kids = new ArrayList<>(current.getChildren());

            if(check == 1 ){
                expanded.add(queue.get(0));
                queue.addAll(0,kids);
                queue.remove(current);

            }
            else{
                queue.remove(current);
            }

        }



    }
    public static void IDS(){
        int i = 0 ;
        List<Node> result = new ArrayList<Node>();
        while(true){
            counter =0;
            result.addAll(DLS(start,i));
            idsExpanded.addAll(result);



            if(idsFinished == 1){

                solution.add(goal);

                Node search = result.get(result.size()-1);

                while(true){
                    if(search.getParent().equals(start)){
                        solution.add(start);
                        break;
                    }
                    else{
                        solution.add(search.getParent());
                        search = search.getParent();

                    }
                }

                expanded.clear();
                expanded = idsExpanded;

                return;
            }
            else if(idsExpanded.size()>=1000){
                expanded.clear();
                expanded = idsExpanded;
                return;
            }

            result.clear();
            i++;
        }

    }

    public static List<Node> DLS(Node node,int iteration){
        queue.clear();
        queue.add(node);
        expanded.clear();
        while(true) {
            int duplicate =0;



            if(queue.size() == 0){

                return expanded;
            }



            if (iteration == queue.get(0).getLevel()) {
                    for (Node nodes : expanded) {
                        if (nodes.getNumber().equals(queue.get(0).getNumber())) {
                            if (!nodes.equals(start)) {
                                int a = Math.abs(Integer.parseInt(queue.get(0).getNumber()) - Integer.parseInt(queue.get(0).getParent().getNumber()));
                                int b = Math.abs(Integer.parseInt(nodes.getNumber()) - Integer.parseInt(nodes.getParent().getNumber()));

                                if (a == b) {
                                    duplicate = 1;
                                }
                            }
                        }
                    }

                    if (duplicate == 1) {
                        queue.remove(queue.get(0));

                    } else {

                        if (queue.get(0).getNumber().equals(goal.getNumber())) {

                            expanded.add(queue.get(0));
                            idsFinished = 1;
                            return expanded;

                        } else {

                            expanded.add(queue.get(0));

                            queue.remove(queue.get(0));

                        }

                    }
            }
            else if (queue.get(0).getLevel() < iteration) {

                List<Node> kids = new ArrayList<Node>();
                    kids.addAll(makeChildren(queue.get(0)));

                    if (queue.get(0).getVisited() == 0) {
                        queue.get(0).setVisited();

                        if (queue.get(0).getNumber().equals(goal.getNumber())) {
                            expanded.add(queue.get(0));
                            idsFinished = 1;
                            return expanded;
                        }
                        if (check == 1) {
                            expanded.add(queue.get(0));
                            queue.remove(queue.get(0));
                            queue.addAll(0, kids);
                        } else {
                            queue.remove(queue.get(0));
                            check = 1;
                        }


                    } else {
                        if (check == 1) {
                            for (Node nodes : expanded) {
                                if (nodes.getNumber().equals(queue.get(0).getNumber())) {
                                    if (!nodes.equals(start)) {
                                        int a = Math.abs(Integer.parseInt(queue.get(0).getNumber()) - Integer.parseInt(queue.get(0).getParent().getNumber()));
                                        int b = Math.abs(Integer.parseInt(nodes.getNumber()) - Integer.parseInt(nodes.getParent().getNumber()));

                                        if (a == b) {
                                            duplicate = 1;
                                        }
                                    }
                                }
                            }
                            if (queue.get(0).getNumber().equals(goal.getNumber())) {
                                expanded.add(queue.get(0));
                                idsFinished = 1;
                                return expanded;
                            }
                            if (duplicate == 1) {
                                queue.remove(queue.get(0));
                            } else {
                                expanded.add(queue.get(0));
                                queue.remove(queue.get(0));
                                queue.addAll(0,kids);

                            }
                        } else {
                            queue.remove(queue.get(0));
                        }
                    }


                }
            else {
                    queue.remove(queue.get(0));
                }


        }
    }




    public static void GREEDY(Node node){

        if(node.getNumber().equals(goal.getNumber())){
            expanded.add(node);

            solution.add(goal);

            Node search = expanded.get(expanded.size()-1);

            while(true){
                if(search.getParent().equals(start)){
                    solution.add(start);
                    break;
                }
                else{
                    solution.add(search.getParent());
                    search = search.getParent();

                }
            }

            return;

        }

        else if(expanded.size() == 999){
            expanded.add(node);
            return;
        }

        node.setChildren();

        if(check == 1) {

            List<Node> children = new ArrayList<Node>();
            children.addAll(node.getChildren());

            for (Node child : children) {
                child.setHeuristic();
            }

            queue.addAll(children);

            if (node.equals(start)) {

            } else {
                queue.remove(node);
            }
            expanded.add(node);
        }
        else {
            queue.remove(node);
        }

       int smallest = 0;
        int smallestIndex = 0;

        for(int i =0 ; i<queue.size() ; i++){
            if(i==0){
                smallest = queue.get(i).getHeuristic();
                smallestIndex = i;
            }
            else{
                if(queue.get(i).getHeuristic() <= smallest){
                    smallest = queue.get(i).getHeuristic();
                    smallestIndex = i;
                }
            }
        }



        if(queue.size() == 0){
            return;
        }
        else{
            GREEDY(queue.get(smallestIndex));
        }









    }

    public static void A(Node node){


        if(node.getNumber().equals(goal.getNumber())){
            expanded.add(node);

            solution.add(goal);

            Node search = expanded.get(expanded.size()-1);

            while(true){
                if(search.getParent().equals(start)){
                    solution.add(start);
                    break;
                }
                else{
                    solution.add(search.getParent());
                    search = search.getParent();

                }
            }

            return;

        }

        else if(expanded.size() == 999){
            expanded.add(node);
            return;
        }

        node.setChildren();

        if(check == 1) {

            List<Node> children = new ArrayList<Node>();
            children.addAll(node.getChildren());




            for (Node child : children) {
                child.setHeuristic();
                child.setCost();
            }

            queue.addAll(children);

            if (node.equals(start)) {

            } else {
                queue.remove(node);
            }
            expanded.add(node);
        }
        else {
            queue.remove(node);
        }

        int smallest = 0;
        int smallestIndex = 0;

        for(int i =0 ; i<queue.size() ; i++){
            if(i==0){
                smallest = queue.get(i).getHeuristic() + queue.get(i).getCost();
                smallestIndex = i;
            }
            else{
                if(( queue.get(i).getHeuristic() + queue.get(i).getCost())<= smallest){
                    smallest =  queue.get(i).getHeuristic()+ queue.get(i).getCost();
                    smallestIndex = i;
                }
            }
        }








        if(queue.size() == 0){
            return;
        }
        else{

            A(queue.get(smallestIndex));
        }










    }

    public static void HILL(Node node){
        if(node.equals(start)){

        }
        else{
            queue.clear();
        }
        if(node.getNumber().equals(goal.getNumber())){
            expanded.add(node);

            solution.add(goal);

            Node search = expanded.get(expanded.size()-1);

            while(true){
                if(search.getParent().equals(start)){
                    solution.add(start);
                    break;
                }
                else{
                    solution.add(search.getParent());
                    search = search.getParent();

                }
            }

            return;

        }

        else if(expanded.size() == 999 || failed ==1){
            expanded.add(node);
            return;
        }

        node.setChildren();

        if(check == 1) {

            List<Node> children = new ArrayList<Node>();
            children.addAll(node.getChildren());

            for (Node child : children) {
                child.setHeuristic();
            }

            queue.addAll(children);


            expanded.add(node);
        }

        int smallest = 0;
        int smallestIndex = 0;

        for(int i =0 ; i<queue.size() ; i++){
            if(i==0){
                smallest = queue.get(i).getHeuristic();
                smallestIndex = i;
            }
            else{
                if(queue.get(i).getHeuristic() <= smallest){
                    smallest = queue.get(i).getHeuristic();
                    smallestIndex = i;
                }
            }
        }

        if(tracker == 0){
            tracker = smallest;
        }
        else{
            if(smallest >= tracker){
                failed =1;
                return;
            }
        }


        if(queue.size() == 0){
            return;
        }
        else{
            HILL(queue.get(smallestIndex));
        }







    }





    static class Node
    {
        String number;
        int visited = 0;
        Node parent;
        int level;
        int checking = 1;
        int heuristic ;
        int cost =0;
        List<Node> children = new ArrayList<Node>();
        Node(String number)
        {
            this.number=number;
        }

        public void setParent(Node parent){
            this.parent = parent;
        }

        public Node getParent(){
            return this.parent;

        }

        public void setLevel(int level){
            this.level = level;
        }

        public int getLevel(){
            return this.level;
        }

        public String getNumber(){
            return number;
        }

        public void setHeuristic(){
            char number1[] = this.number.toCharArray();
            char number2[] = goal.getNumber().toCharArray();

            this.heuristic = Math.abs(number1[0] - number2[0]) +  Math.abs(number1[1] - number2[1]) +  Math.abs(number1[2] - number2[2]);
        }

        public int getHeuristic(){
            return this.heuristic;
        }

        public void setCost(){
            Node test = this;
            while (true){

                if(test.getParent().getNumber().equals(start.getNumber())){
                    this.cost += 1;
                    break;
                }
                else{
                    this.cost += 1;
                    test = test.getParent();

                }

            }

        }

        public int getCost(){
            return this.cost;
        }


        public void setCheck(){
            this.checking = 0;
        }

        public int getCheck(){
            return this.checking;
        }

        public List<Node> getChildren(){
            return this.children;
        }

        public void setChildren(){
            this.children = makeChildren(this);
        }

        public void remove(){
            this.children  = null;
        }

        public void setVisited(){
            this.visited =1;
        }

        public int getVisited(){
            return this.visited;
        }



    }

}
