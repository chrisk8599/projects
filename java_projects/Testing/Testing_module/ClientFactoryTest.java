package au.edu.sydney.pac.erp.client;

import org.junit.Test;
import static org.junit.Assert.*;

public class ClientFactoryTest {

    @Test
    public void testEmpty(){
        ClientFactory factory = new ClientFactory();
        assertNotNull(factory);
        assertNotNull(factory.makeClientList());
        assertTrue(factory.makeClientList().findAll().isEmpty());

    }


}