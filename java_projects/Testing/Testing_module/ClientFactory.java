package au.edu.sydney.pac.erp.client;

public class ClientFactory {

    public ClientList makeClientList(){
        return new ClientListImpl();
    }
}
