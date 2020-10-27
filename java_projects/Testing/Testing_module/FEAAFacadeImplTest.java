package au.edu.sydney.pac.erp.feaa;

import au.edu.sydney.pac.erp.client.ClientList;
import au.edu.sydney.pac.erp.client.ClientListImpl;
import org.junit.Test;
import static org.junit.Assert.*;
public class FEAAFacadeImplTest {

    @Test (expected = IllegalStateException.class)
    public void nullClientProviderAddClient(){
        FEAAFacade fe = new FEAAFacadeImpl();
        fe.addClient("chris","kim","0123213231");
    }

    @Test
    public void NotNullClientProviderAddClient(){
        ClientList provider = new ClientListImpl();
        FEAAFacade fe = new FEAAFacadeImpl();
        fe.setClientProvider(provider);
        assertNotNull(fe.addClient("chris","kim","0123213231"));
    }

    @Test(expected = IllegalArgumentException.class)
    public void NotNullFNameAddClient(){
        ClientList provider = new ClientListImpl();
        FEAAFacade fe = new FEAAFacadeImpl();
        fe.setClientProvider(provider);
        fe.addClient(null,"kim","0123213231");
    }
    @Test(expected = IllegalArgumentException.class)
    public void NotEmptyFNameAddClient(){
        ClientList provider = new ClientListImpl();
        FEAAFacade fe = new FEAAFacadeImpl();
        fe.setClientProvider(provider);
        fe.addClient("","kim","0123213231");
    }

    @Test(expected = IllegalArgumentException.class)
    public void NotEmptyLNameAddClient(){
        ClientList provider = new ClientListImpl();
        FEAAFacade fe = new FEAAFacadeImpl();
        fe.setClientProvider(provider);
        fe.addClient("chris","","0123213231");
    }

    @Test(expected = IllegalArgumentException.class)
    public void NotNullLNameAddClient(){
        ClientList provider = new ClientListImpl();
        FEAAFacade fe = new FEAAFacadeImpl();
        fe.setClientProvider(provider);
        fe.addClient("chris",null,"0123213231");
    }

    @Test(expected = IllegalArgumentException.class)
    public void NotNullPhoneAddClient(){
        ClientList provider = new ClientListImpl();
        FEAAFacade fe = new FEAAFacadeImpl();
        fe.setClientProvider(provider);
        fe.addClient("chris","kim",null);
    }

    @Test(expected = IllegalArgumentException.class)
    public void NotEmptyPhoneAddClient(){
        ClientList provider = new ClientListImpl();
        FEAAFacade fe = new FEAAFacadeImpl();
        fe.setClientProvider(provider);
        fe.addClient("chris","kim","");
    }

    @Test(expected = IllegalArgumentException.class)
    public void IncorrectInputForPhoneNumberAddClient1(){
        ClientList provider = new ClientListImpl();
        FEAAFacade fe = new FEAAFacadeImpl();
        fe.setClientProvider(provider);
        fe.addClient("chris","kim","abc");
    }

    @Test(expected = IllegalArgumentException.class)
    public void IncorrectInputForPhoneNumberAddClient2(){
        ClientList provider = new ClientListImpl();
        FEAAFacade fe = new FEAAFacadeImpl();
        fe.setClientProvider(provider);
        fe.addClient("chris","kim","123.2121");
    }

    @Test
    public void testValidAddClient(){
        ClientList provider = new ClientListImpl();
        FEAAFacade fe = new FEAAFacadeImpl();
        fe.setClientProvider(provider);
        assertNotNull(fe.addClient("chris","kim","12  2323  +  ()"));

    }

    @Test(expected = IllegalStateException.class)
    public void NotNullProviderAssignClient(){
        FEAAFacade fe = new FEAAFacadeImpl();
        fe.assignClient(12,"sydney");
    }

    @Test(expected = IllegalArgumentException.class)
    public void NotZeroIDAssignClient(){
        ClientList provider = new ClientListImpl();
        FEAAFacade fe = new FEAAFacadeImpl();
        fe.setClientProvider(provider);
        fe.addClient("chris","kim","12313");
        fe.assignClient(0,"sydney");
    }

    @Test(expected = IllegalArgumentException.class)
    public void NotNegativeIDAssignClient(){
        ClientList provider = new ClientListImpl();
        FEAAFacade fe = new FEAAFacadeImpl();
        fe.setClientProvider(provider);
        fe.addClient("chris","kim","12313");
        fe.assignClient(-110,"sydney");
    }

    @Test(expected = IllegalArgumentException.class)
    public void invalidDepartmentCodeAssignClient(){
        ClientList provider = new ClientListImpl();
        FEAAFacade fe = new FEAAFacadeImpl();
        fe.setClientProvider(provider);
        fe.addClient("chris","kim","12313");
        fe.assignClient(1,"DOMESTICC");
    }

    @Test(expected = IllegalArgumentException.class)
    public void invalidDepartmentCodeAbrevAssignClient(){
        ClientList provider = new ClientListImpl();
        FEAAFacade fe = new FEAAFacadeImpl();
        fe.setClientProvider(provider);
        fe.addClient("chris","kim","12313");
        fe.assignClient(1,"INTT");
    }

    @Test(expected = IllegalArgumentException.class)
    public void notNullDepartmentCodeAssignClient(){
        ClientList provider = new ClientListImpl();
        FEAAFacade fe = new FEAAFacadeImpl();
        fe.setClientProvider(provider);
        fe.addClient("chris","kim","12313");
        fe.assignClient(1,null);
    }

    @Test
    public void domesticCodeAssignClient(){
        ClientList provider = new ClientListImpl();
        FEAAFacade fe = new FEAAFacadeImpl();
        fe.setClientProvider(provider);
        fe.addClient("chris","kim","12313");
        fe.assignClient(1,"DOMESTIC");
        assertEquals("DOMESTIC",fe.getAllClients().get(0).getDepartmentCode());
    }

    @Test
    public void internationalCodeAssignClient(){
        ClientList provider = new ClientListImpl();
        FEAAFacade fe = new FEAAFacadeImpl();
        fe.setClientProvider(provider);
        fe.addClient("chris","kim","12313");
        fe.assignClient(1,"INTERNATIONAL");
        assertEquals("INTERNATIONAL",fe.getAllClients().get(0).getDepartmentCode());
    }

    @Test
    public void largeAccountsCodeAssignClient(){
        ClientList provider = new ClientListImpl();
        FEAAFacade fe = new FEAAFacadeImpl();
        fe.setClientProvider(provider);
        fe.addClient("chris","kim","12313");
        fe.assignClient(1,"LARGE ACCOUNTS");
        assertEquals("LARGE ACCOUNTS",fe.getAllClients().get(0).getDepartmentCode());
    }

    @Test
    public void domesticCodeAbbrevAssignClient(){
        ClientList provider = new ClientListImpl();
        FEAAFacade fe = new FEAAFacadeImpl();
        fe.setClientProvider(provider);
        fe.addClient("chris","kim","12313");
        fe.assignClient(1,"DOM");
        assertEquals("DOMESTIC",fe.getAllClients().get(0).getDepartmentCode());
    }

    @Test
    public void internationalCodeAbbrevAssignClient(){
        ClientList provider = new ClientListImpl();
        FEAAFacade fe = new FEAAFacadeImpl();
        fe.setClientProvider(provider);
        fe.addClient("chris","kim","12313");
        fe.assignClient(1,"INT");
        assertEquals("INTERNATIONAL",fe.getAllClients().get(0).getDepartmentCode());
    }

    @Test
    public void largeAccountsCodeAbrrevAssignClient(){
        ClientList provider = new ClientListImpl();
        FEAAFacade fe = new FEAAFacadeImpl();
        fe.setClientProvider(provider);
        fe.addClient("chris","kim","12313");
        fe.assignClient(1,"LRG");
        assertEquals("LARGE ACCOUNTS",fe.getAllClients().get(0).getDepartmentCode());
    }


    @Test(expected = IllegalStateException.class)
    public void invalidIdAssignClient(){
        ClientList provider = new ClientListImpl();
        FEAAFacade fe = new FEAAFacadeImpl();
        fe.setClientProvider(provider);
        fe.addClient("chris","kim","12313");
        fe.assignClient(100,"LRG");
    }

    @Test(expected = IllegalStateException.class)
    public void alreadyAssignedAssignClient(){
        ClientList provider = new ClientListImpl();
        FEAAFacade fe = new FEAAFacadeImpl();
        fe.setClientProvider(provider);
        fe.addClient("chris","kim","12313");
        fe.assignClient(1,"LRG");
        fe.assignClient(1,"LRG");
    }


    @Test
    public void nullProviderViewAllClients(){
        FEAAFacade fe = new FEAAFacadeImpl();
        assertTrue(fe.viewAllClients().isEmpty());
    }

    @Test
    public void noClientsViewAllClients(){
        ClientList provider = new ClientListImpl();
        FEAAFacade fe = new FEAAFacadeImpl();
        fe.setClientProvider(provider);
        assertTrue(fe.viewAllClients().isEmpty());
    }

    @Test
    public void successfulViewAllClients(){
        ClientList provider = new ClientListImpl();
        FEAAFacade fe = new FEAAFacadeImpl();
        fe.setClientProvider(provider);
        fe.addClient("chris","kim","12313");
        assertEquals("kim, chris",fe.viewAllClients().get(0));
    }

    @Test
    public void successfulMultipleViewAllClients(){
        ClientList provider = new ClientListImpl();
        FEAAFacade fe = new FEAAFacadeImpl();
        fe.setClientProvider(provider);
        fe.addClient("chris","kim","12313");
        fe.addClient("asd","dsa","321231");
        fe.addClient("vhj","wqe","43543");
        assertEquals("kim, chris",fe.viewAllClients().get(0));
        assertEquals("dsa, asd",fe.viewAllClients().get(1));
        assertEquals("wqe, vhj",fe.viewAllClients().get(2));
    }

    @Test(expected = IllegalStateException.class)
    public void nullProviderGetAllClients(){
        FEAAFacade fe = new FEAAFacadeImpl();
        fe.getAllClients();
    }

    @Test
    public void successfulGetAllClients(){
        ClientList provider = new ClientListImpl();
        FEAAFacade fe = new FEAAFacadeImpl();
        fe.setClientProvider(provider);
        fe.addClient("chris","kim","12313");
        fe.addClient("asd","dsa","321231");
        fe.addClient("vhj","wqe","43543");
        assertEquals("chris",fe.getAllClients().get(0).getFirstName());
        assertEquals("asd",fe.getAllClients().get(1).getFirstName());
        assertEquals("vhj",fe.getAllClients().get(2).getFirstName());
    }

    @Test(expected = IllegalStateException.class)
    public void nullProviderAddAccount(){
        FEAAFacade fe = new FEAAFacadeImpl();
        fe.addAccount(1,1,"hello",1,1);
    }

    @Test(expected = IllegalArgumentException.class)
    public void accIdNegativeAddAccount(){
        ClientList provider = new ClientListImpl();
        FEAAFacade fe = new FEAAFacadeImpl();
        fe.setClientProvider(provider);
        fe.addClient("chris","kim","12313");
        fe.addAccount(-1,1,"Chris",1,1);
    }

    @Test(expected = IllegalArgumentException.class)
    public void accIdZeroAddAccount(){
        ClientList provider = new ClientListImpl();
        FEAAFacade fe = new FEAAFacadeImpl();
        fe.setClientProvider(provider);
        fe.addClient("chris","kim","12313");
        fe.addAccount(0,1,"Chris",1,1);
    }

    @Test
    public void accIdNotUniqueAddAccount(){
        ClientList provider = new ClientListImpl();
        FEAAFacade fe = new FEAAFacadeImpl();
        fe.setClientProvider(provider);
        fe.addClient("chris","kim","12313");
        fe.addClient("asd","dsa","321231");
        fe.addAccount(1,1,"Chris",1,1);
        fe.addAccount(1,2,"assa",1,1);

        //an Error is expected to be thrown.
    }

    @Test(expected = IllegalStateException.class)
    public void accIdNullAddAccount(){
        ClientList provider = new ClientListImpl();
        FEAAFacade fe = new FEAAFacadeImpl();
        fe.setClientProvider(provider);
        fe.addClient("chris","kim","12313");
        fe.addClient("asd","dsa","321231");
        fe.addAccount(1,1,"acc",1,1);
        fe.addAccount(null,2,"chris",1,1);
    }

    @Test(expected = IllegalStateException.class)
    public void accIdFutureNullAddAccount(){
        ClientList provider = new ClientListImpl();
        FEAAFacade fe = new FEAAFacadeImpl();
        fe.setClientProvider(provider);
        fe.addClient("chris","kim","12313");
        fe.addClient("asd","dsa","321231");
        fe.addClient("vhj","wqe","43543");
        fe.addAccount(null,1,"acc",1,1);
        fe.addAccount(2,2,"chris",1,1);
        fe.addAccount(null,3,"cewq",1,1);
    }

    @Test
    public void successfulAccIdAddAccount(){
        ClientList provider = new ClientListImpl();
        FEAAFacade fe = new FEAAFacadeImpl();
        fe.setClientProvider(provider);
        fe.addClient("chris","kim","12313");
        fe.addClient("asd","dsa","321231");
        fe.addClient("vhj","wqe","43543");
        fe.addAccount(null,1,"acc",1,1);
        fe.addAccount(2,2,"chris",1,1);
        fe.addAccount(3,3,"cewq",1,1);
        assertEquals(3,fe.getAccounts().size());
    }

    @Test(expected = IllegalArgumentException.class)
    public void negativeClientIdAddAccounts(){
        ClientList provider = new ClientListImpl();
        FEAAFacade fe = new FEAAFacadeImpl();
        fe.setClientProvider(provider);
        fe.addClient("chris","kim","12313");
        fe.addAccount(null,-100,"acc",1,1);

    }

    @Test(expected = IllegalArgumentException.class)
    public void zeroClientIdAddAccounts(){
        ClientList provider = new ClientListImpl();
        FEAAFacade fe = new FEAAFacadeImpl();
        fe.setClientProvider(provider);
        fe.addClient("chris","kim","12313");
        fe.addAccount(null,0,"acc",1,1);

    }

    @Test(expected = IllegalArgumentException.class)
    public void nullAccNameAddAccounts(){
        ClientList provider = new ClientListImpl();
        FEAAFacade fe = new FEAAFacadeImpl();
        fe.setClientProvider(provider);
        fe.addClient("chris","kim","12313");
        fe.addAccount(null,1,null,1,1);

    }


    @Test(expected = IllegalArgumentException.class)
    public void emptyAccNameAddAccounts(){
        ClientList provider = new ClientListImpl();
        FEAAFacade fe = new FEAAFacadeImpl();
        fe.setClientProvider(provider);
        fe.addClient("chris","kim","12313");
        fe.addAccount(null,1,"",1,1);

    }


    @Test(expected = IllegalArgumentException.class)
    public void negativeIncomeAddAccounts(){
        ClientList provider = new ClientListImpl();
        FEAAFacade fe = new FEAAFacadeImpl();
        fe.setClientProvider(provider);
        fe.addClient("chris","kim","12313");
        fe.addAccount(null,1,"asd",-1,1);

    }

    @Test(expected = IllegalArgumentException.class)
    public void negativeOutgoingAddAccounts(){
        ClientList provider = new ClientListImpl();
        FEAAFacade fe = new FEAAFacadeImpl();
        fe.setClientProvider(provider);
        fe.addClient("chris","kim","12313");
        fe.addAccount(null,1,"asd",1,-1);

    }

    @Test(expected = IllegalStateException.class)
    public void nonExistingClientAddAccounts(){
        ClientList provider = new ClientListImpl();
        FEAAFacade fe = new FEAAFacadeImpl();
        fe.setClientProvider(provider);
        fe.addClient("chris","kim","12313");
        fe.addAccount(null,2,"asd",1,1);

    }

    @Test
    public void successfulAddAccounts(){
        ClientList provider = new ClientListImpl();
        FEAAFacade fe = new FEAAFacadeImpl();
        fe.setClientProvider(provider);
        fe.addClient("chris","kim","12313");
        fe.addClient("weq","dsa","213213");
        fe.addClient("cxv","bff","234234");

        fe.addAccount(null,1,"a",1,1);
        assertEquals(2,fe.addAccount(2,2,"b",1,1));
        assertEquals(3,fe.addAccount(3,3,"c",1,1));

        assertEquals(3,fe.getAccounts().size());

    }

    @Test
    public void nullProviderGetAccounts(){
        FEAAFacade fe = new FEAAFacadeImpl();
        assertTrue(fe.getAccounts().isEmpty());
    }


    @Test
    public void emptyGetAccounts(){
        ClientList provider = new ClientListImpl();
        FEAAFacade fe = new FEAAFacadeImpl();
        fe.setClientProvider(provider);
        assertTrue(fe.getAccounts().isEmpty());
    }


    @Test
    public void successfulSingleGetAccounts(){
        ClientList provider = new ClientListImpl();
        FEAAFacade fe = new FEAAFacadeImpl();
        fe.setClientProvider(provider);
        fe.addClient("chris","kim","12313");
        fe.addAccount(1,1,"a",1,1);
        assertEquals("1: a",fe.getAccounts().get(0));
    }

    @Test
    public void successfulMultipleGetAccounts(){
        ClientList provider = new ClientListImpl();
        FEAAFacade fe = new FEAAFacadeImpl();
        fe.setClientProvider(provider);
        fe.addClient("chris","kim","12313");
        fe.addClient("weq","dsa","213213");
        fe.addClient("cxv","bff","234234");
        fe.addAccount(1,1,"a",1,1);
        fe.addAccount(2,2,"b",1,1);
        fe.addAccount(3,3,"c",1,1);
        assertEquals("1: a",fe.getAccounts().get(0));
        assertEquals("2: b",fe.getAccounts().get(1));
        assertEquals("3: c",fe.getAccounts().get(2));
    }


    @Test(expected = IllegalStateException.class)
    public void nullProviderIdGetAccounts(){
        FEAAFacade fe = new FEAAFacadeImpl();
        fe.getAccounts(1);
    }

    @Test(expected = IllegalArgumentException.class)
    public void negativeIdGetAccounts(){
        ClientList provider = new ClientListImpl();
        FEAAFacade fe = new FEAAFacadeImpl();
        fe.setClientProvider(provider);
        fe.addClient("chris","kim","12313");
        fe.addAccount(1,1,"a",1,1);
        fe.getAccounts(-199);
    }

    @Test(expected = IllegalArgumentException.class)
    public void zeroIdGetAccounts(){
        ClientList provider = new ClientListImpl();
        FEAAFacade fe = new FEAAFacadeImpl();
        fe.setClientProvider(provider);
        fe.addClient("chris","kim","12313");
        fe.addAccount(1,1,"a",1,1);
        fe.getAccounts(0);
    }

    @Test
    public void emptyAccounts(){
        ClientList provider = new ClientListImpl();
        FEAAFacade fe = new FEAAFacadeImpl();
        fe.setClientProvider(provider);
        fe.addClient("chris","kim","12313");
        assertTrue(fe.getAccounts(1).isEmpty());
    }

    @Test
    public void singleGetAccountsID(){
        ClientList provider = new ClientListImpl();
        FEAAFacade fe = new FEAAFacadeImpl();
        fe.setClientProvider(provider);
        fe.addClient("chris","kim","12313");
        fe.addAccount(1,1,"a",1,1);
        assertEquals(1,fe.getAccounts(1).size());
    }

    @Test
    public void multipleGetAccountsID(){
        ClientList provider = new ClientListImpl();
        FEAAFacade fe = new FEAAFacadeImpl();
        fe.setClientProvider(provider);
        fe.addClient("chris","kim","12313");
        fe.addAccount(1,1,"a",1,1);
        fe.addAccount(2,1,"b",1,1);
        fe.addAccount(3,1,"c",1,1);
        assertEquals(3,fe.getAccounts(1).size());
    }

    @Test(expected = IllegalStateException.class)
    public void unknownClientGetAccountsID(){
        ClientList provider = new ClientListImpl();
        FEAAFacade fe = new FEAAFacadeImpl();
        fe.setClientProvider(provider);
        fe.addClient("chris","kim","12313");
        fe.addAccount(1,1,"a",1,1);
        fe.addAccount(2,1,"b",1,1);
        fe.addAccount(3,1,"c",1,1);
        fe.getAccounts(2);
    }

    @Test(expected = IllegalStateException.class)
    public void nullProviderGetAccountName(){
        FEAAFacade fe = new FEAAFacadeImpl();
        fe.getAccountName(1);
    }

    @Test(expected = IllegalArgumentException.class)
    public void negativeIDGetAccountName(){
        ClientList provider = new ClientListImpl();
        FEAAFacade fe = new FEAAFacadeImpl();
        fe.setClientProvider(provider);
        fe.addClient("chris","kim","12313");
        fe.addAccount(1,1,"a",1,1);
        fe.getAccountName(-10);
    }

    @Test(expected = IllegalArgumentException.class)
    public void zeroIDGetAccountName(){
        ClientList provider = new ClientListImpl();
        FEAAFacade fe = new FEAAFacadeImpl();
        fe.setClientProvider(provider);
        fe.addClient("chris","kim","12313");
        fe.addAccount(1,1,"a",1,1);
        fe.getAccountName(0);
    }

    @Test
    public void successfulSingleGetAccountName(){
        ClientList provider = new ClientListImpl();
        FEAAFacade fe = new FEAAFacadeImpl();
        fe.setClientProvider(provider);
        fe.addClient("chris","kim","12313");
        fe.addAccount(1,1,"a",1,1);
        assertEquals("a",fe.getAccountName(1));

    }

    @Test
    public void successfulMultipleGetAccountName(){
        ClientList provider = new ClientListImpl();
        FEAAFacade fe = new FEAAFacadeImpl();
        fe.setClientProvider(provider);
        fe.addClient("chris","kim","12313");
        fe.addAccount(1,1,"a",1,1);
        fe.addAccount(2,1,"b",1,1);
        fe.addAccount(3,1,"c",1,1);
        assertEquals("a",fe.getAccountName(1));
        assertEquals("b",fe.getAccountName(2));
        assertEquals("c",fe.getAccountName(3));

    }

    @Test(expected = IllegalStateException.class)
    public void unknownAccountGetAccountName(){
        ClientList provider = new ClientListImpl();
        FEAAFacade fe = new FEAAFacadeImpl();
        fe.setClientProvider(provider);
        fe.addClient("chris","kim","12313");
        fe.addAccount(1,1,"a",1,1);
        fe.addAccount(2,1,"b",1,1);
        fe.addAccount(3,1,"c",1,1);
        fe.getAccountName(5);
    }

    @Test(expected = IllegalStateException.class)
    public void nullProviderGetAccountBalance(){
        FEAAFacade fe = new FEAAFacadeImpl();
        fe.getAccountBalance(1);
    }

    @Test(expected = IllegalArgumentException.class)
    public void negativeIdGetAccountBalance(){
        ClientList provider = new ClientListImpl();
        FEAAFacade fe = new FEAAFacadeImpl();
        fe.setClientProvider(provider);
        fe.addClient("chris","kim","12313");
        fe.addAccount(1,1,"a",10,1);
        fe.getAccountBalance(-1);
    }

    @Test(expected = IllegalArgumentException.class)
    public void zeroIdGetAccountBalance(){
        ClientList provider = new ClientListImpl();
        FEAAFacade fe = new FEAAFacadeImpl();
        fe.setClientProvider(provider);
        fe.addClient("chris","kim","12313");
        fe.addAccount(1,1,"a",10,1);
        fe.getAccountBalance(0);
    }

    @Test
    public void successfulGetAccountBalance(){
        ClientList provider = new ClientListImpl();
        FEAAFacade fe = new FEAAFacadeImpl();
        fe.setClientProvider(provider);
        fe.addClient("chris","kim","12313");
        fe.addAccount(1,1,"a",10,1);
        assertEquals(9,fe.getAccountBalance(1));
    }

    @Test(expected = IllegalStateException.class)
    public void unknownGetAccountBalance(){
        ClientList provider = new ClientListImpl();
        FEAAFacade fe = new FEAAFacadeImpl();
        fe.setClientProvider(provider);
        fe.addClient("chris","kim","12313");
        fe.addAccount(1,1,"a",10,1);
        fe.getAccountBalance(2);
    }

    @Test(expected = IllegalStateException.class)
    public void nullProviderGetAccountIncomings(){
        FEAAFacade fe = new FEAAFacadeImpl();
        fe.getAccountIncomings(1);
    }

    @Test(expected = IllegalArgumentException.class)
    public void negativeIdGetAccountIncomings(){
        ClientList provider = new ClientListImpl();
        FEAAFacade fe = new FEAAFacadeImpl();
        fe.setClientProvider(provider);
        fe.addClient("chris","kim","12313");
        fe.addAccount(1,1,"a",10,1);
        fe.getAccountIncomings(-1);
    }

    @Test(expected = IllegalArgumentException.class)
    public void zeroIdGetAccountIncomings(){
        ClientList provider = new ClientListImpl();
        FEAAFacade fe = new FEAAFacadeImpl();
        fe.setClientProvider(provider);
        fe.addClient("chris","kim","12313");
        fe.addAccount(1,1,"a",10,1);
        fe.getAccountIncomings(0);
    }

    @Test
    public void successfulGetAccountIncomings(){
        ClientList provider = new ClientListImpl();
        FEAAFacade fe = new FEAAFacadeImpl();
        fe.setClientProvider(provider);
        fe.addClient("chris","kim","12313");
        fe.addAccount(1,1,"a",10,1);
        fe.addAccount(2,1,"b",6,5);
        assertEquals(10,fe.getAccountIncomings(1));
        assertEquals(6,fe.getAccountIncomings(2));
    }

    @Test(expected = IllegalStateException.class)
    public void unknownGetAccountIncomings(){
        ClientList provider = new ClientListImpl();
        FEAAFacade fe = new FEAAFacadeImpl();
        fe.setClientProvider(provider);
        fe.addClient("chris","kim","12313");
        fe.addAccount(1,1,"a",10,1);
        fe.addAccount(2,1,"b",6,5);
        fe.getAccountIncomings(3);
    }


    @Test(expected = IllegalStateException.class)
    public void nullProviderGetAccountOutgoings(){
        FEAAFacade fe = new FEAAFacadeImpl();
        fe.getAccountOutgoings(1);
    }

    @Test(expected = IllegalArgumentException.class)
    public void negativeIdGetAccountOutgoings(){
        ClientList provider = new ClientListImpl();
        FEAAFacade fe = new FEAAFacadeImpl();
        fe.setClientProvider(provider);
        fe.addClient("chris","kim","12313");
        fe.addAccount(1,1,"a",10,1);
        fe.getAccountOutgoings(-1);
    }

    @Test(expected = IllegalArgumentException.class)
    public void zeroIdGetAccountOutgoings(){
        ClientList provider = new ClientListImpl();
        FEAAFacade fe = new FEAAFacadeImpl();
        fe.setClientProvider(provider);
        fe.addClient("chris","kim","12313");
        fe.addAccount(1,1,"a",10,1);
        fe.getAccountOutgoings(0);
    }

    @Test
    public void successfulGetAccountOutgoings(){
        ClientList provider = new ClientListImpl();
        FEAAFacade fe = new FEAAFacadeImpl();
        fe.setClientProvider(provider);
        fe.addClient("chris","kim","12313");
        fe.addAccount(1,1,"a",10,1);
        fe.addAccount(2,1,"b",6,5);
        assertEquals(1,fe.getAccountOutgoings(1));
        assertEquals(5,fe.getAccountOutgoings(2));
    }

    @Test(expected = IllegalStateException.class)
    public void unknownGetAccountOutgoings(){
        ClientList provider = new ClientListImpl();
        FEAAFacade fe = new FEAAFacadeImpl();
        fe.setClientProvider(provider);
        fe.addClient("chris","kim","12313");
        fe.addAccount(1,1,"a",10,1);
        fe.addAccount(2,1,"b",6,5);
        fe.getAccountOutgoings(3);
    }

    @Test(expected = IllegalStateException.class)
    public void nullProviderSetAccountIncomings(){
        FEAAFacade fe = new FEAAFacadeImpl();
        fe.setAccountIncomings(1,1);
    }

    @Test(expected = IllegalArgumentException.class)
    public void negativeIdSetAccountIncomings(){
        ClientList provider = new ClientListImpl();
        FEAAFacade fe = new FEAAFacadeImpl();
        fe.setClientProvider(provider);
        fe.addClient("chris","kim","12313");
        fe.addAccount(1,1,"a",10,1);
        fe.setAccountIncomings(-1,1);
    }

    @Test(expected = IllegalArgumentException.class)
    public void zeroIdSetAccountIncomings(){
        ClientList provider = new ClientListImpl();
        FEAAFacade fe = new FEAAFacadeImpl();
        fe.setClientProvider(provider);
        fe.addClient("chris","kim","12313");
        fe.addAccount(1,1,"a",10,1);
        fe.setAccountIncomings(0,1);
    }

    @Test(expected = IllegalArgumentException.class)
    public void negativeIncomingsSetAccountIncomings(){
        ClientList provider = new ClientListImpl();
        FEAAFacade fe = new FEAAFacadeImpl();
        fe.setClientProvider(provider);
        fe.addClient("chris","kim","12313");
        fe.addAccount(1,1,"a",10,1);
        fe.setAccountIncomings(1,-1);
    }


    @Test
    public void successfulSetAccountIncomings(){
        try {
            ClientList provider = new ClientListImpl();
            FEAAFacade fe = new FEAAFacadeImpl();
            fe.setClientProvider(provider);
            fe.addClient("chris", "kim", "12313");
            fe.addAccount(1, 1, "a", 10, 1);
            fe.setAccountIncomings(1, 1);
            assertEquals(1, fe.getAccountIncomings(1));
        }
        catch(Exception e){

        }
        }


    @Test(expected = IllegalStateException.class)
    public void unknownSetAccountIncomings(){
        ClientList provider = new ClientListImpl();
        FEAAFacade fe = new FEAAFacadeImpl();
        fe.setClientProvider(provider);
        fe.addClient("chris","kim","12313");
        fe.addAccount(1,1,"a",10,1);
        fe.setAccountIncomings(3,1);
    }


    @Test(expected = IllegalStateException.class)
    public void nullProviderSetAccountOutgoings(){
        FEAAFacade fe = new FEAAFacadeImpl();
        fe.setAccountOutgoings(1,1);
    }

    @Test(expected = IllegalArgumentException.class)
    public void negativeIdSetAccountOutgoings(){
        ClientList provider = new ClientListImpl();
        FEAAFacade fe = new FEAAFacadeImpl();
        fe.setClientProvider(provider);
        fe.addClient("chris","kim","12313");
        fe.addAccount(1,1,"a",10,1);
        fe.setAccountOutgoings(-1,1);
    }

    @Test(expected = IllegalArgumentException.class)
    public void zeroIdSetAccountOutgoings(){
        ClientList provider = new ClientListImpl();
        FEAAFacade fe = new FEAAFacadeImpl();
        fe.setClientProvider(provider);
        fe.addClient("chris","kim","12313");
        fe.addAccount(1,1,"a",10,1);
        fe.setAccountOutgoings(0,1);
    }

    @Test(expected = IllegalArgumentException.class)
    public void negativeOutgoingsSetAccountOutgoings(){
        ClientList provider = new ClientListImpl();
        FEAAFacade fe = new FEAAFacadeImpl();
        fe.setClientProvider(provider);
        fe.addClient("chris","kim","12313");
        fe.addAccount(1,1,"a",10,1);
        fe.setAccountOutgoings(1,-1);
    }


    @Test
    public void successfulSetAccountOutgoings(){
        try {
            ClientList provider = new ClientListImpl();
            FEAAFacade fe = new FEAAFacadeImpl();
            fe.setClientProvider(provider);
            fe.addClient("chris", "kim", "12313");
            fe.addAccount(1, 1, "a", 10, 5);
            fe.setAccountOutgoings(1, 1);
            assertEquals(1, fe.getAccountOutgoings(1));
        }
        catch(Exception e){

        }
    }

    @Test(expected = IllegalStateException.class)
    public void unknownSetAccountOutgoings(){
        ClientList provider = new ClientListImpl();
        FEAAFacade fe = new FEAAFacadeImpl();
        fe.setClientProvider(provider);
        fe.addClient("chris","kim","12313");
        fe.addAccount(1,1,"a",10,1);
        fe.setAccountOutgoings(3,1);
    }


    @Test
    public void testSetClientProvider(){
        ClientList provider = new ClientListImpl();
        provider.addClient(1,"hello","name","1231321");
        provider.addClient(2,"as","gre","6545");
        provider.addClient(10,"weq","mee","21331");
        FEAAFacade fe = new FEAAFacadeImpl();
        fe.setClientProvider(provider);
        assertTrue(fe.getAccounts().isEmpty());
        fe.addClient("chris","kim","12313");
        fe.addAccount(null,1,"a",10,1);
        assertEquals("1: a",fe.getAccounts().get(0));
        assertEquals(11,fe.getAllClients().get(3).getID());


    }








































}

