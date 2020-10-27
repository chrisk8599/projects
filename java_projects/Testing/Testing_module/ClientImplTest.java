package au.edu.sydney.pac.erp.client;

import org.junit.Test;
import static org.junit.Assert.*;
public class ClientImplTest {

    @Test(expected = IllegalArgumentException.class)
    public void zeroIDClientInstantiation(){ Client client = new ClientImpl(0,"chris","kim","231231231");
    }

    @Test(expected = IllegalArgumentException.class)
    public void negativeIDClientInstantiation(){
        Client client = new ClientImpl(-10,"chris","kim","321321231");
    }

    @Test(expected = IllegalArgumentException.class)
    public void emptyFirstNameIDClientInstantiation(){
        Client client = new ClientImpl(10,"","kim","321321321");
    }

    @Test(expected = IllegalArgumentException.class)
    public void nullFirstNameClientInstantiation(){
        Client client = new ClientImpl(10,null,"kim","231231123");
    }
    @Test(expected = IllegalArgumentException.class)
    public void nullLastNameClientInstantiation(){
        Client client = new ClientImpl(10,"chris",null,"213321213");
    }
    @Test(expected = IllegalArgumentException.class)
    public void emptyLastNameClientInstantiation(){
        Client client = new ClientImpl(10,"chris","","12312231");
    }
    @Test(expected = IllegalArgumentException.class)
    public void nullPhoneNumberClientInstantiation(){
        Client client = new ClientImpl(10,"chris","kim",null);
    }
    @Test(expected = IllegalArgumentException.class)
    public void emptyPhoneNumberClientInstantiation(){
        Client client = new ClientImpl(10,"chris","kim","");
    }

    @Test
    public void sucessfulClientInstantiation(){
        Client client = new ClientImpl(10,"chris","kim","213231321");
        assertNotNull(client);
    }

    @Test(expected = IllegalStateException.class)
    public void clientAlreadyAssigned(){
        Client client = new ClientImpl(10,"chris","kim","123231231");
        client.assignDepartment("Sydney");
        client.assignDepartment("Melbourne");
    }

    @Test(expected = IllegalArgumentException.class)
    public void nullDepartment(){
        Client client = new ClientImpl(10,"chris","kim","123231231");
        client.assignDepartment(null);
    }

    @Test(expected = IllegalArgumentException.class)
    public void emptyDepartment(){
        Client client = new ClientImpl(10,"chris","kim","123231231");
        client.assignDepartment("");
    }

    @Test
    public void assignDepartmentSuccessfully(){
        Client client = new ClientImpl(10,"chris","kim","123231231");
        client.assignDepartment("Sydney");
        assertEquals("Sydney",client.getDepartmentCode());
    }

    @Test
    public void isAssignedFalse(){
        Client client = new ClientImpl(10,"chris","kim","123231231");
        assertFalse(client.isAssigned());
    }

    @Test
    public void isAssignedTrue(){
        Client client = new ClientImpl(10,"chris","kim","123231231");
        client.assignDepartment("Sydney");
        assertTrue(client.isAssigned());
    }

    @Test
    public void getDepartmentWorks(){
        Client client = new ClientImpl(10,"chris","kim","123231231");
        client.assignDepartment("Sydney");
        assertEquals("Sydney", client.getDepartmentCode());
    }

    @Test
    public void getDepartmentWorksWhenNull(){
        Client client = new ClientImpl(10,"chris","kim","123231231");
        assertEquals(null,client.getDepartmentCode());
    }

    @Test
    public void getIdWorks(){
        Client client = new ClientImpl(10,"chris","kim","123231231");
        assertEquals(10,client.getID());
    }
    @Test
    public void getFirstNameWorks(){
        Client client = new ClientImpl(10,"chris","kim","123231231");
        assertEquals("chris",client.getFirstName());
    }

    @Test
    public void getLastNameWorks(){
        Client client = new ClientImpl(10,"chris","kim","123231231");
        assertEquals("kim",client.getLastName());
    }

    @Test
    public void getPhoneNumberWorks(){
        Client client = new ClientImpl(10,"chris","kim","123231231");
        assertEquals("123231231",client.getPhoneNumber());
    }








}