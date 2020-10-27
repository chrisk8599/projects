package au.edu.sydney.cpa.erp.feaa.unitOfWork;

import au.edu.sydney.cpa.erp.auth.AuthToken;
import au.edu.sydney.cpa.erp.ordering.Order;

import java.util.List;

public interface UnitOfWork {


    void newOrder(Order order);
    void deleteOrder(int id);
    void commit();
    void clean();
    void modifyOrder(Order order);
     List<Order> getOrders();
     Order getOrder(int id);

}
