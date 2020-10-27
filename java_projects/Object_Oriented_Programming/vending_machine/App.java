/*
 * This Java source file was generated by the Gradle 'init' task.
 */
package VendingMachine30;

import java.io.*;
import java.util.*;
import java.text.SimpleDateFormat;

import static java.lang.Thread.sleep;


public class App {

    public static VendingMachine  machine;


    public static void main(String[] args) throws Exception {

       executeApp();
    }

    private static void executeApp() throws Exception {
        User user= new User();
        FileReader file = new FileReader();
        String password = file.getPassword();
        machine = new VendingMachine(password);
        addItem(file);
        addTransactions(file);
        Printer printer = new Printer(machine);
        printer.printGreeting();
        Scanner scanner = new Scanner(System.in);
        InputHandler input = new InputHandler(scanner);

        try{
            while(true){
                printer.printSelectPrompt();
                int result = input.handler();
                if(result == 1){
                    System.out.println("You have chosen the staff menu");
                    if(checkPassword(printer,input,machine)){
                        staffLogic(printer,input,machine, file);
                    }
                }

                else if(result == 2){

                    System.out.println("Welcome to the AgileTeam30 Vending Machine");
                    userLogic(printer,input,machine, user);

                }

                else if(result == 3){
                    System.out.println("Thanks for visiting AgileTeam30's Vending Machine\nSee you Again!");
                    machine.updateItems();
                    break;
                }

                else{
                    printer.printInvalidInputMessage();
                    printer.printSelectPrompt();
                }

            }
        } catch
        (Exception e){
            e.printStackTrace();
        }

    }

    public static boolean checkPassword(Printer printer, InputHandler input, VendingMachine machine) throws NoSuchElementException{

        while(true){
            printer.printPasswordMenu();
            String result = input.getPassword();
            if(machine.password(result)){
                printer.printCorrectPasswordMessage();
                return true ;
            }
            else{
                printer.printIncorrectPasswordMessage();
                printer.printTryAgain();
                while(true){
                    int response = input.handler();
                    if(response == 2 ){
                        return false;
                    }
                    else if (response == 1){
                        break ;
                    }

                    else {
                        printer.printInvalidInputMessage();
                    }
                }

            }

        }

    }
    public static void fillMachine(VendingMachine machine){
        ArrayList<Item> items = machine.getAllItems();
        for(Item i: items){
            i.setQuantity(10);
        }
        System.out.println("All items completely filled!");
        machine.updateItems();
    }

    public static void alterStock(VendingMachine machine, InputHandler input, Printer printer)throws NoSuchElementException{

        while(true){
            System.out.println("Current Stock Levels");
            printer.printAllItemStock();
            System.out.println("Please Select Item to Alter Stock");
            int option = input.handler();
            Item i = machine.getItem(option);

            if(i == null){
                printer.printInvalidInputMessage();

                System.out.println("Please Input a Valid Item ID");

            }else{
                System.out.println("Please Input Quantity of Stock");
                while(true){
                    int quantity = input.handler();
                    if(quantity > 10){
                        System.out.println("The maximum capacity of a product is 10. Please input a value of 10 or less.");
                        continue;
                    }
                    if(machine.setItemQuantity(i.getName(), quantity)){
                        System.out.format("You have set the quantity of [%d] %s to %d.\n", i.getID(), i.getName(), i.getQuantity());
                        machine.updateItems();
                        return;
                    }else{
                        printer.printInvalidInputMessage();
                    }
                }

            }
        }
    }

    public static void changePrice(VendingMachine machine, InputHandler input, Printer printer)throws NoSuchElementException{

        while(true){
            System.out.println("Current Item Prices");
            printer.printAllItemOptions();
            System.out.println("Please Select Item to Change Price");
            int option = input.handler();
            Item i = machine.getItem(option);

            if(i == null){
                printer.printInvalidInputMessage();

                System.out.println("Please Input a Valid Item ID");

            }else{
                while(true){
                    System.out.println("Please Input Item Price");
                    double price = input.getMoney();

                    if(i.setPrice(price)){
                        System.out.format("You have set the price of [%d] %s to %.2f.\n", i.getID(), i.getName(), i.getPrice());
                        machine.updateItems();
                        return;
                    }else{
                        printer.printInvalidInputMessage();
                    }
                }

            }
        }
    }

    public static void generateStockReport(VendingMachine machine, Printer printer) {
        Date date = new Date();
        SimpleDateFormat formatter = new SimpleDateFormat("dd-MM-yyyy HH:mm:ss");
        System.out.println("AGILETEAM30 VENDING MACHINE REPORT");
        System.out.printf("GENERATED ON %s\n", formatter.format(date));
        System.out.println("====================");
        System.out.println("\tSUMMARY");
        System.out.printf("Current Number of Items: %d\n", machine.getNumberItems());
        System.out.println("Current Stock Levels");
        printer.printAllItemStock();
        System.out.println("====================");
        System.out.println("CHIPS:");
        printer.printChips(true);
        System.out.println("CHOCOLATES:");
        printer.printChocolates(true);
        System.out.println("DRINKS:");
        printer.printDrinks(true);
        System.out.println("LOLLIES:");
        printer.printLollies(true);
        System.out.println("");
        System.out.println("END OF REPORT");
        System.out.println("====================");
        return;
    }

    public static void generateDailyTransactionReport(VendingMachine machine) {
        Date date = new Date();
        SimpleDateFormat formatter = new SimpleDateFormat("dd-MM-yyyy HH:mm:ss");
        ArrayList<Transaction> transactions = machine.getTransactions();
        System.out.println("AGILETEAM30 DAILY TRANSACTION REPORT");
        System.out.printf("GENERATED ON %s\n", formatter.format(date));
        System.out.println("====================");
        if (transactions.size() != 0) {
            for (Transaction t: transactions) {
                if (t.withinTimeFrame(date)) {
                    t.printTransaction();
                }
            }
        } else {
            System.out.println("No transactions found");
        }
        System.out.println("");
        System.out.println("END OF REPORT");
        System.out.println("====================");
    }

    public static void generateCancelledTransactionReport(VendingMachine machine) {
        Date date = new Date();
        ArrayList<Transaction> transactions = machine.getCancelledTransactions();
        SimpleDateFormat formatter = new SimpleDateFormat("dd-MM-yyyy HH:mm:ss");
        System.out.println("AGILETEAM30 CANCELLED TRANSACTIONS REPORT");
        System.out.printf("GENERATED ON %s\n", formatter.format(date));
        System.out.println("====================");
        if (transactions.size() != 0) {
            for (Transaction t: transactions) {
                t.printTransaction();
            }
        } else {
            System.out.println("No transactions found");
        }
        System.out.println("");
        System.out.println("END OF REPORT");
        System.out.println("====================");
    }

    public static void generateReports(VendingMachine machine, Printer printer, InputHandler input, FileReader file) {

        machine.setTransactions(file.getTransactions());

        machine.setCancelledTransactions(file.getCancelledTransactions());

        while (true) {
            printer.printReportsOptions();
            int result = input.handler();
            if (result == 1) {
                System.out.println("You have chosen to view stock report");
                generateStockReport(machine, printer);
                break;
            } else if (result == 2) {
                System.out.println("You have chosen to view daily transactions");
                generateDailyTransactionReport(machine);
                break;
            } else if (result == 3) {
                System.out.println("You have chosen to view cancelled transactions");
                generateCancelledTransactionReport(machine);
                break;
            } else {
                printer.printInvalidInputMessage();
            }
        }
    }

    public static void staffLogic(Printer printer, InputHandler input,VendingMachine machine, FileReader file) throws NoSuchElementException{
        while(true){

            printer.printStaffMenu();
            int result = input.handler();
            if(result == 1){
                System.out.println("You have chosen to Alter Stock Quantities");
                alterStock(machine, input, printer);
                System.out.println("Current Stock Levels");
                printer.printAllItemStock();
                continue;
            }
            else if(result == 2){
                System.out.println("You have chosen to Completely Fill Stock");
                fillMachine(machine);
                System.out.println("Current Stock Levels");
                printer.printAllItemStock();
                continue;
            }
            else if(result == 3){
                System.out.println("You have chosen to change Item Price");
                changePrice(machine, input, printer);
                System.out.println("Current Item Prices");
                continue;
            }
            else if(result == 4){
                System.out.println("You have chosen to Generate Reports");
                generateReports(machine, printer, input, file);
                continue;
            }
            else if(result == 5) {
                System.out.println("You have chosen to Change Password");
                System.out.println("Please input your new password");
                String pw = input.getPassword();
                setPassword(machine, pw);
                continue;
            }
            else if (result == 6){
                String name;
                Double price = 0.0;
                Integer quantity = 0;
                String Type = "";
                String expiry = "";
                while(true) {
                    int count = 0 ;
                    System.out.println("You have chosen to add an item");
                    System.out.println("Please input the details of your new item in the following format:");
                    System.out.println("name,price,quantity,type,expirydate");
                    System.out.println("Where type is either : \nchocolate\nchips\ndrink\nlolly");
                    System.out.println("And where expiry date is in form DD/MM/YYYY");

                    String item = input.getItem();
                    List<String> inputLine;
                    inputLine = Arrays.asList(item.split(","));

                    if(inputLine.size() < 5){
                        System.out.println("You did not put enough arguments");
                    }
                    else if(inputLine.size() > 5){
                        System.out.println("You  put too much arguments");
                    }
                    else{
                        name = inputLine.get(0);


                        try{
                            price = Double.parseDouble(inputLine.get(1));
                        }
                        catch(Exception e){
                            count++;
                            System.out.println("Invalid input for price");
                        }

                        try{
                            quantity = Integer.parseInt(inputLine.get(2));
                        }
                        catch(Exception e){
                            count++;
                            System.out.println("Invalid input for quantity");
                        }

                        if( (inputLine.get(3).equals("lolly")) || (inputLine.get(3).equals("chocolate")) || (inputLine.get(3).equals("drink")) || (inputLine.get(3).equals("chips")))
                            Type = inputLine.get(3);
                        else {
                            count++;
                            System.out.println("Invalid input for type");

                        }
                        try{
                            expiry = inputLine.get(4);
                        }
                        catch(Exception e){
                            count++;
                            System.out.println("Invalid input for expiry");
                        }

                        if(count==0){
                            machine.addItem(name,price,quantity,Type,expiry);
                            machine.updateItems();

                            System.out.println("Successfully added item !");
                            System.out.println("The current items in the vending machine are:");

                            printer.printAllItemOptions();
                            break;
                        }
                    }
                    System.out.println("Please Input the item to add AGAIN!");
                }





                continue;


                }

            else if (result == 7 ){

                while (true) {

                    System.out.println("You have chosen to remove an item");
                    System.out.println("Please input the name of the item you wish to remove");
                    printer.printAllItemOptions();
                    String name = input.getItem();
                    if (machine.removeItem(name)) {
                        machine.updateItems();

                        System.out.println("Item successfully removed!");
                        System.out.println("Here are the items currently left in the vending machine");
                        printer.printAllItemOptions();
                        break;
                    } else {
                        System.out.println("Please input valid name!");
                    }

                }

            }

             else if(result == 8){
                System.out.println("You have exited Staff Menu");
                break;
            }
            else{
                printer.printInvalidInputMessage();
            }

        }


    }

    public static void setPassword(VendingMachine machine, String pw){

        Write write = new Write();
        write.writePassword(pw);
        machine.changePassword(pw);
    }

    public static void userLogic(Printer printer, InputHandler input, VendingMachine machine, User user) throws NoSuchElementException{
        outerloop:
        while(true){
            machine.printMachineGreeting();
            printer.printCategoryOptions();
            System.out.println("Press 0 to return to main menu.");
            boolean ret = false;
            int result = input.handler();
            if(result == 0){
                break;
            }
            if (result == 1){
                while(true){
                    System.out.println("Here are the Drinks Available\nWhich would you like to purchase?");
                    printer.printDrinks(false);
                    int option = input.handler();
                    if(option == 0){
                        break outerloop;
                    }
                    Item i = machine.getItem(option);
                    if(i == null || !i.getClass().equals(Beverage.class)){
                        printer.printInvalidInputMessage();
                    }else if(machine.getItemQuantity(i.getName()) == 0){
                        System.out.printf("Sorry we don't have any %s left.\n", i.getName());
                        break;
                    }else{
                        ret = selectItem(option, machine, input, printer, user);
                        break;
                    }
                }

                if(ret){
                    break;
                }
            }
            else if( result == 2 ){
                while(true){
                    System.out.println("Here are the Chips Available\nWhich would you like to purchase?");
                    printer.printChips(false);
                    int option = input.handler();
                    if(option == 0){
                        break outerloop;
                    }
                    Item i = machine.getItem(option);
                    if(i == null || !i.getClass().equals(Chips.class)){
                        printer.printInvalidInputMessage();
                    }else if(machine.getItemQuantity(i.getName()) == 0){
                        System.out.printf("Sorry we don't have any %s left.\n", i.getName());
                        break;
                    }else{
                        ret = selectItem(option, machine, input, printer, user);
                        break;
                    }
                }

                if(ret){
                    break;
                }
            }
            else if( result == 3 ){
                while(true){
                    System.out.println("Here are the Chocolates Available\nWhich would you like to purchase?");
                    printer.printChocolates(false);
                    int option = input.handler();
                    if(option == 0){
                        break outerloop;
                    }
                    Item i = machine.getItem(option);
                    if(i == null || !i.getClass().equals(Chocolate.class)){
                        printer.printInvalidInputMessage();
                    }else if(machine.getItemQuantity(i.getName()) == 0){
                        System.out.printf("Sorry we don't have any %s left.\n", i.getName());
                        break;
                    }else{
                        ret = selectItem(option, machine, input, printer, user);
                        break;
                    }
                }

                if(ret){
                    break;
                }
            }
            else if( result == 4 ){
                while(true){
                    System.out.println("Here are the Lollies Available\nWhich would you like to purchase?");
                    printer.printLollies(false);
                    int option = input.handler();
                    if(option == 0){
                        break outerloop;
                    }
                    Item i = machine.getItem(option);
                    if(i == null || !i.getClass().equals(Lolly.class)){
                        printer.printInvalidInputMessage();
                    }else if(machine.getItemQuantity(i.getName()) == 0){
                        System.out.printf("Sorry we don't have any %s left.\n", i.getName());
                        break;
                    }else{
                        ret = selectItem(option, machine, input, printer, user);
                        break;
                    }
                }

                if(ret){
                    break;
                }
            }


            else if( result == 5 ){

                while(true){
                    System.out.println("Here are all the items Available\nWhich would you like to purchase?");
                    printer.printAllItemOptions();
                    int option = input.handler();
                    if(option == 0){
                        break outerloop;
                    }
                    Item i = machine.getItem(option);
                    if(i == null){
                        printer.printInvalidInputMessage();
                    }else if(machine.getItemQuantity(i.getName()) == 0){
                        System.out.printf("Sorry we don't have any %s left.\n", i.getName());
                        break;
                    }else{
                        ret = selectItem(option, machine, input, printer, user);
                        break;
                    }
                }

                if(ret) {
                    break;
                }

            }


            else{
                printer.printInvalidInputMessage();
                machine.printMachineGreeting();
                printer.printCategoryOptions();
            }



        }

    }



    public static boolean selectItem(int option, VendingMachine machine, InputHandler input, Printer printer, User user) throws NoSuchElementException{

        Item newItem = machine.getItem(option);

        String name = newItem.getName();

        while(true){
            System.out.println("How many would you like?");
            int quantity = input.handler();
            if(quantity > machine.getItemQuantity(name)){
                machine.printTooMuchErrorMessage(name);
            }
            else if (quantity<1){
                machine.printNotEnoughMessage();
            }
            else{

                System.out.format("You have added %d %s\n",quantity,name);
                System.out.format("This costs $%.2f \n",newItem.getPrice()*quantity);

                user.addItem(newItem, quantity);
                machine.setItemQuantity(newItem.getName(), machine.getItemQuantity(newItem.getName()) - quantity);

                outerLoop:
                while(true){
                    printer.printContinuePurchase();

                    int selection = input.handler();

                    if(selection == 1){
                        return false;
                    }

                    else if(selection == 2){
                        LinkedHashMap<Item, Integer> current = user.getSelectedItems();
                        int i = 1;

                        System.out.println("=========== CURRENT VENDING SELECTIONS ===========");

                        for (Item item : current.keySet()){
                            System.out.format("%d. %s x %d ($%.2f each)\n", i, item.getName(),  current.get(item), item.getPrice());
                            i++ ;
                        }

                        System.out.println("====================================================");

                        double lineTotal = user.getLineTotal();
                        System.out.format("Your Line Total is: %.2f\n", lineTotal);

                        try {
                            sleep(3000);
                        } catch (InterruptedException e) {
                            e.printStackTrace();
                        }


                        while(true){
                            printer.printContinuePurchaseInCart();
                            int chosen = input.handler();

                            if(chosen == 1){
                                return false;
                            }

                            else if(chosen == 2){
                                finaliseTransaction(machine, user, input, printer);
                                break outerLoop;
                            }

                            else if(chosen == 3){
                                LinkedHashMap<Item, Integer> selected = user.getSelectedItems();
                                machine.addCancelledTransaction(selected, new Date(), user.getLineTotal());
                                for(Item q: selected.keySet()){
                                    machine.setItemQuantity(q.getName(), machine.getItemQuantity(q.getName()) + selected.get(q));
                                }
                                user.resetItems();
                                return false;
                            }

                            else{
                                printer.printInvalidInputMessage();
                            }



                        }
                    }

                    else if(selection == 3){
                        finaliseTransaction(machine, user, input, printer);
                        break;
                    }

                    else if(selection == 4){
                        LinkedHashMap<Item, Integer> selected = user.getSelectedItems();
                        machine.addCancelledTransaction(selected, new Date(), user.getLineTotal());
                        for(Item i: selected.keySet()){
                            machine.setItemQuantity(i.getName(), machine.getItemQuantity(i.getName()) + selected.get(i));
                        }
                        user.resetItems();
                        return false;
                    }


                    else{
                        printer.printInvalidInputMessage();
                    }


                }

                return true;
            }
        }
    }




    public static void finaliseTransaction(VendingMachine machine,User user, InputHandler input, Printer printer) throws NoSuchElementException{

        double lineTotal = user.getLineTotal();
        System.out.println("The items in you cart are: ");
        int i = 1;
        LinkedHashMap<Item, Integer> selected = user.getSelectedItems();
        for (Item item : selected.keySet()){
            System.out.format("%d. %s x %d ($%.2f each)\n", i, item.getName(),  selected.get(item), item.getPrice());
            i++ ;
        }

        double change = paymentSystem(lineTotal, input);

        machine.addTransaction(selected, new Date(), lineTotal, change);

        System.out.println("Thank you for your purchase!");

        user.resetItems();


    }



    public static double paymentSystem(double lineTotal, InputHandler input) throws NoSuchElementException{

        double moneyEntered = 0 ;
        int AUS_20,AUS_10, AUS_5, AUS_2, AUS_1, AUS_C50, AUS_C20, AUS_C10;
        int user_choice;
        double moneyGiven = 0;

        while(true){
            moneyGiven = 0;
            System.out.format("Your Line Total is: %.2f\n", lineTotal);
            System.out.println("Please select which note/coin you want to input.");
            System.out.println("1. $20");
            System.out.println("2. $10");
            System.out.println("3. $5");
            System.out.println("4. $2");
            System.out.println("5. $1");
            System.out.println("6. 50c");
            System.out.println("7. 20c");
            System.out.println("8. 10c");

            user_choice = input.handler();
            if (user_choice == 1)
            {
                System.out.println("Please input the amount of $20 note you want to insert.");
                AUS_20 = input.handler();
                double value = 20 * AUS_20;
                moneyGiven += value;
            }
            else if (user_choice == 2)
            {
                System.out.println("Please input the amount of $10 note you want to insert.");
                AUS_10 = input.handler();
                double value = 10 * AUS_10;
                moneyGiven += value;
            }
            else if (user_choice == 3)
            {
                System.out.println("Please input the amount of $5 note you want to insert.");
                AUS_5 = input.handler();
                double value = 5 * AUS_5;
                moneyGiven += value;
            }

            else if (user_choice == 4)
            {
                System.out.println("Please input the amount of $2 coin you want to insert.");
                AUS_2 = input.handler();
                double value = 2 * AUS_2;
                moneyGiven += value;
            }
            else if (user_choice == 5)
            {
                System.out.println("Please input the amount of $1 coin you want to insert.");
                AUS_1 = input.handler();
                double value = 1 * AUS_1;
                moneyGiven += value;
            }
            else if (user_choice == 6)
            {
                System.out.println("Please input the amount of 50c coins you want to insert.");
                AUS_C50 = input.handler();
                double value = 0.5 * AUS_C50;
                moneyGiven += value;
            }
            else if (user_choice == 7)
            {
                System.out.println("Please input the amount of 20c coins you want to insert.");
                AUS_C20 = input.handler();
                double value = 0.2 * AUS_C20;
                moneyGiven += value;
            }
            else if (user_choice == 8)
            {
                System.out.println("Please input the amount of 10c coins you want to insert.");
                AUS_C10 = input.handler();
                double value = 0.1 * AUS_C10;
                moneyGiven += value;
            }

            else
            {
                System.out.println("Please input a valid choice.");
            }


            if(lineTotal - moneyGiven > 0){
                lineTotal -= moneyGiven ;
                moneyEntered += moneyGiven;
                if(moneyGiven > 0){
                    System.out.format("Accepted $%.2f.\n", moneyGiven);
                }
                System.out.format("Running payment total: $%.2f (what you have paid).\n", moneyEntered);
            }else if(lineTotal - moneyGiven == 0){
                System.out.format("Accepted $%.2f.\n", moneyGiven);
                return 0;
            }else{
                double change = moneyGiven - lineTotal ;
                double originalChange = change;
                int track_AUS_20 = 0, track_AUS_10 = 0, track_AUS_5 = 0, track_AUS_2 = 0, track_AUS_1 = 0, track_AUS_C50 = 0, track_AUS_C20 = 0, track_AUS_C10 = 0;

                while (change > 0.1) {
                    if (change >= 20)
                    {
                        track_AUS_20 += 1;
                        change -= 20;

                    }
                    else if (change >= 10)
                    {
                        track_AUS_10 += 1;
                        change -= 10;
                    }
                    else if(change >= 5)
                    {
                        track_AUS_5 += 1;
                        change -= 5;
                    }
                    else if(change >= 2)
                    {
                        track_AUS_2 += 1;
                        change -= 2;
                    }
                    else if(change >= 1)
                    {
                        track_AUS_1 += 1;
                        change -= 1;
                    }
                    else if(change >= 0.5)
                    {
                        track_AUS_C50 += 1;
                        change -= 0.5;
                    }

                    else if(change >= 0.2)
                    {
                        track_AUS_C20 += 1;
                        change -= 0.2;
                    }

                    else if(change >= 0.1)
                    {
                        track_AUS_C10 += 1;
                        change -= 0.1;
                    }
                }



                System.out.println("Your change is as follows: ");
                System.out.format("1. $20: %d.\n", track_AUS_20);
                System.out.format("2. $10: %d.\n", track_AUS_10);
                System.out.format("3. $5:  %d.\n", track_AUS_5);
                System.out.format("4. $2:  %d.\n", track_AUS_2);
                System.out.format("5. $1:  %d.\n", track_AUS_1);
                System.out.format("6. 50c: %d.\n", track_AUS_C50);
                System.out.format("7. 20c: %d.\n", track_AUS_C20);
                System.out.format("8. 10c: %d.\n", track_AUS_C10);
                System.out.format("$%.2f Total change given.\n", originalChange);
                return originalChange-change;

            }
        }

    }


    public static void addItem(FileReader file){
        for (int i = 0 ; i < file.getName().size();i++){
            machine.addItem(file.getName().get(i),file.getPrice().get(i),file.getQuantity().get(i),file.getType().get(i), file.getExpiry().get(i));

        }
    }

    public static void addTransactions (FileReader file){
        ArrayList<Transaction> transactions = file.getTransactions();
        ArrayList<Transaction> cancelledTransactions = file.getCancelledTransactions();


        machine.setCancelledTransactions(cancelledTransactions);
        machine.setTransactions(transactions);
    }


}
