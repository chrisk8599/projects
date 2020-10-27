package au.edu.sydney.pac.erp.client;
import org.junit.Test;
import static org.junit.Assert.*;

public class ClientListImplTest {

    @Test
    public void initTest(){
        ClientFactory factory = new ClientFactory();
        ClientList clientList = factory.makeClientList();
        assertNotNull(clientList);
    }

    @Test(expected = IllegalArgumentException.class)
    public void addClientZeroID(){
        ClientFactory factory = new ClientFactory();
        ClientList clientList = factory.makeClientList();
        clientList.addClient(0,"chris","kim","123456789");
    }

    @Test(expected = IllegalArgumentException.class)
    public void addClientNegativeID(){
        ClientFactory factory = new ClientFactory();
        ClientList clientList = factory.makeClientList();
        clientList.addClient(-10,"chris","kim","123456789");
    }

    @Test(expected = IllegalArgumentException.class)
    public void addClientFirstNameEmpty(){
        ClientFactory factory = new ClientFactory();
        ClientList clientList = factory.makeClientList();
        clientList.addClient(10,"","kim","123456789");
    }

    @Test(expected = IllegalArgumentException.class)
    public void addClientFirstNameNull(){
        ClientFactory factory = new ClientFactory();
        ClientList clientList = factory.makeClientList();
        clientList.addClient(10,null,"kim","123456789");
    }

    @Test(expected = IllegalArgumentException.class)
    public void addClientLastNameEmpty(){
        ClientFactory factory = new ClientFactory();
        ClientList clientList = factory.makeClientList();
        clientList.addClient(10,"chris","","123456789");
    }

    @Test(expected = IllegalArgumentException.class)
    public void addClientLastNameNull(){
        ClientFactory factory = new ClientFactory();
        ClientList clientList = factory.makeClientList();
        clientList.addClient(10,"chris",null,"123456789");
    }


    @Test(expected = IllegalArgumentException.class)
    public void addClientPhoneNumberEmpty(){
        ClientFactory factory = new ClientFactory();
        ClientList clientList = factory.makeClientList();
        clientList.addClient(10,"chris","kim","");
    }

    @Test(expected = IllegalArgumentException.class)
    public void addClientPhoneNumberNull(){
        ClientFactory factory = new ClientFactory();
        ClientList clientList = factory.makeClientList();
        clientList.addClient(10,"chris","kim",null);
    }

    @Test
    public void addClientSuccessfully(){
        ClientFactory factory = new ClientFactory();
        ClientList clientList = factory.makeClientList();
        assertNotNull(clientList.addClient(10,"chris","kim","12332123"));
    }

    @Test(expected = IllegalStateException.class)
    public void addClientWithSameId(){
        ClientFactory factory = new ClientFactory();
        ClientList clientList = factory.makeClientList();
        clientList.addClient(10,"chris","kim","1232131");
        clientList.addClient(10,"ben","kim","1232131");
    }


    @Test
    public void clearList(){
        ClientFactory factory = new ClientFactory();
        ClientList clientList = factory.makeClientList();
        clientList.addClient(10,"chris","kim","1232131");
        clientList.clear();
        assertTrue(clientList.findAll().isEmpty());
    }

    @Test
    public void findAllNotNull(){
        ClientFactory factory = new ClientFactory();
        ClientList clientList = factory.makeClientList();
        assertNotNull(clientList.findAll());
    }

    @Test
    public void findAllIsEmpty(){
        ClientFactory factory = new ClientFactory();
        ClientList clientList = factory.makeClientList();
        assertTrue(clientList.findAll().isEmpty());
    }

    @Test
    public void findAllWorksSingle(){
        ClientFactory factory = new ClientFactory();
        ClientList clientList = factory.makeClientList();
        clientList.addClient(10,"chris","kim","1232131");

        assertEquals(10,clientList.findAll().get(0).getID());

        assertEquals("chris",clientList.findAll().get(0).getFirstName());

        assertEquals("kim",clientList.findAll().get(0).getLastName());

        assertEquals("1232131",clientList.findAll().get(0).getPhoneNumber());
    }

    @Test
    public void findAllWorksMultiple(){
        ClientFactory factory = new ClientFactory();
        ClientList clientList = factory.makeClientList();
        clientList.addClient(10,"chris","weqewq","1232131");
        clientList.addClient(1,"weq","weq","213231");
        clientList.addClient(120,"weqweq","sfsa","432234");
        clientList.addClient(104,"asdsad","weqweq","6545");

        assertEquals(4,clientList.findAll().size());
    }


    @Test
    public void assignedFalseFindAll(){
        ClientFactory factory = new ClientFactory();
        ClientList clientList = factory.makeClientList();
        clientList.addClient(10,"chris","weqewq","1232131");
        clientList.addClient(1,"weq","weq","213231");
        clientList.addClient(120,"weqweq","sfsa","432234");
        clientList.findAll().get(0).assignDepartment("Sydney");
        assertEquals(2,clientList.findAll(false).size());
    }

    @Test
    public void assignedTrueFindAll(){
        ClientFactory factory = new ClientFactory();
        ClientList clientList = factory.makeClientList();
        clientList.addClient(10,"chris","weqewq","1232131");
        clientList.addClient(1,"weq","weq","213231");
        clientList.addClient(120,"weqweq","sfsa","432234");
        clientList.findAll().get(0).assignDepartment("Sydney");
        assertEquals(1,clientList.findAll(true).size());
    }

    @Test
    public void assignedFindAllEmpty(){
        ClientFactory factory = new ClientFactory();
        ClientList clientList = factory.makeClientList();
        clientList.addClient(10,"chris","weqewq","1232131");
        clientList.addClient(1,"weq","weq","213231");
        clientList.addClient(120,"weqweq","sfsa","432234");
        assertTrue(clientList.findAll(true).isEmpty());
        assertNotNull(clientList.findAll(true));
    }


    @Test
    public void assignedSpecificDepartmentFindAll(){
        ClientFactory factory = new ClientFactory();
        ClientList clientList = factory.makeClientList();
        clientList.addClient(10,"chris","weqewq","1232131");
        clientList.addClient(1,"weq","weq","213231");
        clientList.addClient(120,"weqweq","sfsa","432234");
        clientList.findAll().get(0).assignDepartment("Sydney");
        clientList.findAll().get(1).assignDepartment("Hobart");
        clientList.findAll().get(2).assignDepartment("Melbourne");

        assertEquals(1,clientList.findAll("Sydney").size());
        assertEquals(2,clientList.findAll("Sydney", "Melbourne").size());
        assertEquals(3,clientList.findAll("Sydney", "Melbourne", "Hobart").size());
    }

    @Test
    public void assignedSpecificDepartmentFindAllEmpty(){
        ClientFactory factory = new ClientFactory();
        ClientList clientList = factory.makeClientList();
        clientList.addClient(10,"chris","weqewq","1232131");
        clientList.addClient(1,"weq","weq","213231");
        clientList.addClient(120,"weqweq","sfsa","432234");
        clientList.findAll().get(0).assignDepartment("Sydney");
        clientList.findAll().get(1).assignDepartment("Hobart");
        clientList.findAll().get(2).assignDepartment("Melbourne");

        assertTrue(clientList.findAll("tea","coffee").isEmpty());
        assertNotNull(clientList.findAll("tea","coffee"));
    }

    @Test
    public void assignedSpecificDepartmentFindAllNoneAssigned(){
        ClientFactory factory = new ClientFactory();
        ClientList clientList = factory.makeClientList();
        clientList.addClient(10,"chris","weqewq","1232131");
        clientList.addClient(1,"weq","weq","213231");
        clientList.addClient(120,"weqweq","sfsa","432234");

        assertTrue(clientList.findAll("tea","coffee").isEmpty());
        assertNotNull(clientList.findAll("tea","coffee"));
    }



    @Test(expected = IllegalArgumentException.class)
    public void zeroIdFindOne(){
        ClientFactory factory = new ClientFactory();
        ClientList clientList = factory.makeClientList();
        clientList.addClient(10,"chris","weqewq","1232131");
        clientList.findOne(0);
    }

    @Test(expected = IllegalArgumentException.class)
    public void negativeIdFindOne(){
        ClientFactory factory = new ClientFactory();
        ClientList clientList = factory.makeClientList();
        clientList.addClient(10,"chris","weqewq","1232131");
        clientList.findOne(-10);
    }

    @Test
    public void FindOneWorks(){
        ClientFactory factory = new ClientFactory();
        ClientList clientList = factory.makeClientList();
        clientList.addClient(10,"chris","weqewq","1232131");
        clientList.addClient(1,"weq","weq","213231");
        clientList.addClient(120,"weqweq","sfsa","432234");
        assertEquals(1, clientList.findOne(1).getID());
        assertEquals("weq", clientList.findOne(1).getFirstName());
        assertEquals("weq", clientList.findOne(1).getLastName());
        assertEquals("213231", clientList.findOne(1).getPhoneNumber());
    }

    @Test
    public void FindOneNoMatch(){
        ClientFactory factory = new ClientFactory();
        ClientList clientList = factory.makeClientList();
        clientList.addClient(10,"chris","weqewq","1232131");
        clientList.addClient(1,"weq","weq","213231");
        clientList.addClient(120,"weqweq","sfsa","432234");
        assertNull(clientList.findOne(123));
    }

    @Test(expected = IllegalArgumentException.class)
    public void zeroIdRemove(){
        ClientFactory factory = new ClientFactory();
        ClientList clientList = factory.makeClientList();
        clientList.addClient(10,"chris","weqewq","1232131");
        clientList.remove(0);
    }

    @Test(expected = IllegalArgumentException.class)
    public void negativeIdRemove(){
        ClientFactory factory = new ClientFactory();
        ClientList clientList = factory.makeClientList();
        clientList.addClient(10,"chris","weqewq","1232131");
        clientList.remove(-10);
    }

    @Test
    public void removeWorks(){
        ClientFactory factory = new ClientFactory();
        ClientList clientList = factory.makeClientList();
        clientList.addClient(10,"chris","weqewq","1232131");
        clientList.addClient(1,"weq","weq","213231");
        assertTrue(clientList.remove(1));
        assertEquals(10,clientList.findAll().get(0).getID());
        assertEquals("chris",clientList.findAll().get(0).getFirstName());
        assertEquals("weqewq",clientList.findAll().get(0).getLastName());
        assertEquals("1232131",clientList.findAll().get(0).getPhoneNumber());
        assertEquals(1,clientList.findAll().size());
    }

    @Test
    public void failedRemove(){
        ClientFactory factory = new ClientFactory();
        ClientList clientList = factory.makeClientList();
        clientList.addClient(10,"chris","weqewq","1232131");
        clientList.addClient(1,"weq","weq","213231");
        assertFalse(clientList.remove(100));
        assertEquals(2,clientList.findAll().size());

    }











}