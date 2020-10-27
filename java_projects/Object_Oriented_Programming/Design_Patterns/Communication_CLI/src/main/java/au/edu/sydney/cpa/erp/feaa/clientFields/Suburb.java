package au.edu.sydney.cpa.erp.feaa.clientFields;

import au.edu.sydney.cpa.erp.auth.AuthToken;
import au.edu.sydney.cpa.erp.database.TestDatabase;

import java.util.concurrent.Callable;


/**
 * Creates a new Thread to grab the Suburb of a client
 */

public class Suburb implements Callable<String> {

    AuthToken token;
    int id;

    public Suburb(AuthToken token, int id){
        this.token = token;
        this.id = id;
    }

    /**
     * Gets Data from database concurrently.
     * @return A String data type.
     */

    @Override
    public String call() {
        return TestDatabase.getInstance().getClientField(token, id, "suburb");
    }
}
