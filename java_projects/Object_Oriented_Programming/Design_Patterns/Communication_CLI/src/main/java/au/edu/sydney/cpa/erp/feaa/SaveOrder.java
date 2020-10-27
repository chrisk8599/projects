package au.edu.sydney.cpa.erp.feaa;

import au.edu.sydney.cpa.erp.auth.AuthModule;
import au.edu.sydney.cpa.erp.auth.AuthToken;
import au.edu.sydney.cpa.erp.database.TestDatabase;
import au.edu.sydney.cpa.erp.ordering.Order;

public class SaveOrder implements Runnable {

    AuthToken token ;
    Order order;

    public SaveOrder(AuthToken token, Order order){
        this.order = order;
        this.token = token;
    }

    @Override
    public void run() {
        TestDatabase.getInstance().saveOrder(token, order);

    }
}
