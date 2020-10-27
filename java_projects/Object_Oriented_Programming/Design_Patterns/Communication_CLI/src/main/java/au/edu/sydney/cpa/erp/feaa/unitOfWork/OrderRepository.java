package au.edu.sydney.cpa.erp.feaa.unitOfWork;

import au.edu.sydney.cpa.erp.auth.AuthToken;
import au.edu.sydney.cpa.erp.feaa.FEAAFacade;
import au.edu.sydney.cpa.erp.feaa.threadPools.OrderPool;
import au.edu.sydney.cpa.erp.ordering.Order;

import java.util.ArrayList;
import java.util.List;

public class OrderRepository implements UnitOfWork {
    private List<Order> updatedDatabase = new ArrayList<>();
    private List<Order> newOrders = new ArrayList<>();
    private List<Order> modifiedOrders = new ArrayList<>();
    private List<Order> deleteOrders = new ArrayList<>();

    private FEAAFacade facade;
    private  static AuthToken token;
    public OrderRepository(FEAAFacade facade, List<Order> database,AuthToken tok){
        clean();
        this.facade = facade;
        updatedDatabase.addAll(database);
        token = tok;

    }

    public Order getOrder(int id){
        for(Order order : updatedDatabase){
            if(order.getOrderID() == id){
                return order;
            }
        }
        return null;
    }

    public List<Order> getOrders(){
        return updatedDatabase;
    }

    @Override
    public void newOrder(Order order) {

        for(Order orders: deleteOrders){
            if(orders.equals(order)){
                return;
            }
        }
        for(Order orders: newOrders){
            if(orders.equals(order)){
                return;
            }
        }


        newOrders.add(order);
        updatedDatabase.add(order);
    }


    @Override
    public void deleteOrder(int id) {

        for(Order orders: deleteOrders){
            if(orders.getOrderID() == id){
                return;
            }
        }

        Order order = null;

        for(Order orders: newOrders){
            if(orders.getOrderID() == id){
                order = orders;
                break;
            }
        }

        if(order !=null){
            newOrders.remove(order);
        }
        order = null;

        for(Order orders: updatedDatabase){
            if(orders.getOrderID() == id){
                order = orders;
                updatedDatabase.remove(orders);
                break;
            }
        }
        if(order !=null){
            updatedDatabase.remove(order);
            deleteOrders.add(order);
        }


    }

    @Override
    public void commit() {
        OrderPool orderPool = new OrderPool(newOrders,modifiedOrders,token);
        orderPool.makePool();

        try{Thread.sleep(100);}
        catch(Exception e){

        }

    }

    @Override
    public void clean() {
        updatedDatabase.clear();
        newOrders.clear();
        deleteOrders.clear();
        modifiedOrders.clear();
    }

    @Override
    public void modifyOrder(Order order) {
        for(Order orders: deleteOrders){
            if(orders.equals(order)){
                return;
            }
        }

        Order ord = null;

        for(Order orders: newOrders){
            if(orders.equals(order)){
                ord = order;

            }
        }

        if(ord!=null){
            newOrders.remove(ord);
        }

        modifiedOrders.add(order);


    }


}
