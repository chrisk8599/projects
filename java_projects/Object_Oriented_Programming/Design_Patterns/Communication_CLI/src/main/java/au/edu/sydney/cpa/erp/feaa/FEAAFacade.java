package au.edu.sydney.cpa.erp.feaa;

import au.edu.sydney.cpa.erp.auth.AuthModule;
import au.edu.sydney.cpa.erp.auth.AuthToken;
import au.edu.sydney.cpa.erp.database.TestDatabase;
import au.edu.sydney.cpa.erp.feaa.handlers.ContactHandler;
import au.edu.sydney.cpa.erp.feaa.handlers.Handler;
import au.edu.sydney.cpa.erp.feaa.reports.ReportStorage;
import au.edu.sydney.cpa.erp.feaa.unitOfWork.OrderRepository;
import au.edu.sydney.cpa.erp.feaa.unitOfWork.UnitOfWork;
import au.edu.sydney.cpa.erp.ordering.Client;
import au.edu.sydney.cpa.erp.ordering.Order;
import au.edu.sydney.cpa.erp.ordering.Report;
import au.edu.sydney.cpa.erp.feaa.ordering.*;
import au.edu.sydney.cpa.erp.feaa.reports.ReportDatabase;

import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;


@SuppressWarnings("Duplicates")
public class FEAAFacade {

    Handler handler;

    UnitOfWork repo = null;

    public FEAAFacade(){
        handler = new ContactHandler();
    }

    private AuthToken token;

    public boolean login(String userName, String password) {
        token = AuthModule.login(userName, password);

        return null != token;
    }

    public List<Integer> getAllOrders() {
        if (null == token) {
            throw new SecurityException();
        }

        if(repo == null){
            repo = new OrderRepository(this,TestDatabase.getInstance().getOrders(token),token);
        }

        List<Order> orders = repo.getOrders();

        List<Integer> result = new ArrayList<>();

        for (Order order : orders) {
            result.add(order.getOrderID());
        }

        return result;
    }

    public Integer createOrder(int clientID, LocalDateTime date, boolean isCritical, boolean isScheduled, int orderType, int criticalLoadingRaw, int maxCountedEmployees, int numQuarters) {
        if (null == token) {
            throw new SecurityException();
        }

        if(repo == null){
            repo = new OrderRepository(this,TestDatabase.getInstance().getOrders(token),token);
        }


        double criticalLoading = criticalLoadingRaw / 100.0;

        Order order;

        if (!TestDatabase.getInstance().getClientIDs(token).contains(clientID)) {
            throw new IllegalArgumentException("Invalid client ID");
        }

        int id = TestDatabase.getInstance().getNextOrderID();

        //Now all you have to do is state the type of order you need and pass in
        //an OrderType to that order. eg ScheduledOrder(type,numQuarters);

        if (isScheduled) {
            if (1 == orderType) { // 1 is regular accounting
                OrderType type = new Order66(id, clientID, date, maxCountedEmployees);
                if (isCritical) {
                    order = new CriticalScheduledOrder(type, criticalLoading, numQuarters);
                } else {
                    order = new ScheduledOrder(type,numQuarters);
                }
            } else if (2 == orderType) { // 2 is audit
                OrderType type = new NewOrderImpl(id, clientID, date);
                if (isCritical) {
                    order = new CriticalScheduledOrder(type, criticalLoading, numQuarters);
                } else {
                    order = new ScheduledOrder(type,numQuarters);
                }
            } else {return null;}
        } else {
            if (1 == orderType) {
                OrderType type = new Order66(id, clientID, date, maxCountedEmployees);
                if (isCritical) {

                    order = new CriticalOrder(type,criticalLoading);

                } else {
                    order = new NormalOrder(type);
                }
            } else if (2 == orderType) {
                OrderType type = new NewOrderImpl(id, clientID, date);
                if (isCritical) {
                    order = new CriticalOrder(type,criticalLoading);
                } else {
                    order = new NormalOrder(type);
                }
            } else {return null;}
        }
        repo.newOrder(order);
//        TestDatabase.getInstance().saveOrder(token, order);
        return order.getOrderID();
    }

    public List<Integer> getAllClientIDs() {
        if (null == token) {
            throw new SecurityException();
        }

        TestDatabase database = TestDatabase.getInstance();
        return database.getClientIDs(token);
    }

    public Client getClient(int id) {
        if (null == token) {
            throw new SecurityException();
        }

        return new ClientImpl(token, id);
    }

    public boolean removeOrder(int id) {
        if (null == token) {
            throw new SecurityException();
        }

        if(repo!=null){
            repo.deleteOrder(id);
        }

        TestDatabase database = TestDatabase.getInstance();
        return database.removeOrder(token, id);
    }

    public List<Report> getAllReports() {
        if (null == token) {
            throw new SecurityException();
        }

        if(ReportStorage.getReports() == null){
            ReportStorage.setReports(ReportDatabase.getTestReports());
        }



        return ReportStorage.getReports();
    }

    public boolean finaliseOrder(int orderID, List<String> contactPriority) {
        if (null == token) {
            throw new SecurityException();
        }


        if (contactPriority == null) { // needs setting to default
            contactPriority = Arrays.asList(
                    "Carrier Pigeon",
                    "Email",
                    "Mail",
                    "Internal Accounting",
                    "Phone call",
                    "SMS"
            );
        }
        Order order;
        if(repo == null){
            order = TestDatabase.getInstance().getOrder(token, orderID);
            repo = new OrderRepository(this,TestDatabase.getInstance().getOrders(token),token);
        }
        else{
            order = repo.getOrder(orderID);
        }


        order.finalise();


        repo.modifyOrder(order);
//        TestDatabase.getInstance().saveOrder(token, order);


        handler.createChain();

        return handler.sendInvoice(token, getClient(order.getClient()), contactPriority, order.generateInvoiceData());
    }

    public void logout()  {
        if(repo!=null){
            repo.commit();
            repo = null;
        }

        AuthModule.logout(token);
        token = null;



    }

    public double getOrderTotalCommission(int orderID) {
        if (null == token) {
            throw new SecurityException();
        }
        Order order;
        if(repo == null){
            order = TestDatabase.getInstance().getOrder(token, orderID);
        }
        else{
            order = repo.getOrder(orderID);
        }

        if (null == order) {
            return 0.0;
        }

        return order.getTotalCommission();
    }

    public void orderLineSet(int orderID, Report report, int numEmployees) {
        if (null == token) {
            throw new SecurityException();
        }

        Order order;
        if(repo == null){
            order = TestDatabase.getInstance().getOrder(token, orderID);
            repo = new OrderRepository(this,TestDatabase.getInstance().getOrders(token),token);
        }
        else{
            order = repo.getOrder(orderID);
        }

        if (null == order) {
            System.out.println("got here");
            return;
        }

        order.setReport(report, numEmployees);
        repo.modifyOrder(order);

//        TestDatabase.getInstance().saveOrder(token, order);
    }

    public String getOrderLongDesc(int orderID) {
        if (null == token) {
            throw new SecurityException();
        }

        Order order;
        if(repo == null){
            order = TestDatabase.getInstance().getOrder(token, orderID);
        }
        else{
            order = repo.getOrder(orderID);
        }

        if (null == order) {
            return null;
        }

        return order.longDesc();
    }

    public String getOrderShortDesc(int orderID) {
        if (null == token) {
            throw new SecurityException();
        }

        Order order;
        if(repo == null){
            order = TestDatabase.getInstance().getOrder(token, orderID);
        }
        else{
            order = repo.getOrder(orderID);
        }

        if (null == order) {
            return null;
        }

        return order.shortDesc();
    }

    public List<String> getKnownContactMethods() {
        if (null == token) {
            throw new SecurityException();
        }
        return handler.getKnownMethods();
    }


}
