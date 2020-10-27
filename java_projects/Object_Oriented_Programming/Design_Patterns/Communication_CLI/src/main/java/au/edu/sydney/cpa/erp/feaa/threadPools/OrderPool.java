package au.edu.sydney.cpa.erp.feaa.threadPools;

import au.edu.sydney.cpa.erp.auth.AuthToken;
import au.edu.sydney.cpa.erp.feaa.SaveOrder;
import au.edu.sydney.cpa.erp.ordering.Order;

import java.util.List;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class OrderPool {
    private List<Order> newOrders;
    private List<Order> modifiedOrders;
    private AuthToken token;
    public OrderPool(List<Order> newOrders, List<Order> modifiedOrders, AuthToken token){
        this.newOrders = newOrders;
        this.modifiedOrders = modifiedOrders;
        this.token = token;
    }

    public void makePool(){
        ExecutorService orderPool = Executors.newFixedThreadPool(10);


        for(Order order : newOrders){
            Runnable thread = new SaveOrder(token,order);
            orderPool.execute(thread);
        }
        for(Order order : modifiedOrders){
            Runnable thread = new SaveOrder(token,order);
            orderPool.execute(thread);
        }

        orderPool.shutdown();
    }
}
