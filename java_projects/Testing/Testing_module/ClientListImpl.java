package au.edu.sydney.pac.erp.client;

import java.util.ArrayList;
import java.util.List;

public class ClientListImpl implements ClientList  {
    private List<Client> list = new ArrayList<Client>();

    public ClientListImpl(){

    }


    @Override
    public Client addClient(int id, String firstName, String lastName, String phoneNumber) throws IllegalStateException, IllegalArgumentException {
        for(Client client : list){
            if(client.getID()==(id)){
                throw new IllegalStateException("Client has already been added");
            }
        }

        if((id>0) &&(firstName!=null)&& (lastName!=null)&& (phoneNumber!=null) && (!firstName.isEmpty())&&(!lastName.isEmpty())&&(!phoneNumber.isEmpty()) ){
            Client client = new ClientImpl(id,firstName,lastName,phoneNumber);
            list.add(client);
            return client;

        }
        else {
            throw new IllegalArgumentException("Invalid parameters provided for client instantiation");
        }

    }

    @Override
    public void clear() {
        list.clear();
    }

    @Override
    public List<Client> findAll() {
        return list;
    }

    @Override
    public List<Client> findAll(boolean assigned) {

        List<Client> assign = new ArrayList<Client>();

        for(Client client: list){

            if(assigned){
                if (client.isAssigned()){
                    assign.add(client);
                }
            }
            else{
                if (!client.isAssigned()){
                    assign.add(client);
                }
            }


        }

        return assign;
    }

    @Override
    public List<Client> findAll(String... departmentCodes) {
        List<Client> department = new ArrayList<Client>();

        for(Client client: list){
            if(client.isAssigned()){
                for(String code : departmentCodes){
                    if (client.getDepartmentCode().equals(code)){
                        department.add(client);
                    }
                }
            }
        }

        return department;
    }

    @Override
    public Client findOne(int id) throws IllegalArgumentException {
        if(id>0){
            for(Client client : list){
                if (client.getID() == id){
                    return client;
                }
            }
            return null;
        }
        else
        {
            throw new IllegalArgumentException("ID must be positive!");
        }
    }

    @Override
    public boolean remove(int id) throws IllegalArgumentException {
        if (id > 0 ){
            for(Client client : list){
                if (client.getID() == id){
                    list.remove(client);
                    return true;
                }
            }

            return false;
        }
        else {
            throw new IllegalArgumentException("ID must be positive");
        }
    }
}
