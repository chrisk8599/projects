package au.edu.sydney.pac.erp.client;

public class ClientImpl implements Client{

    private int id;
    private String firstName;
    private String lastName;
    private String phoneNumber;
    private String departmentCode = null;

    public ClientImpl(int id, String firstName, String lastName, String phoneNumber) throws IllegalArgumentException{

        if ((id > 0)&& (firstName != null ) && (!firstName.equals(""))   && (lastName != null )&& (!lastName.equals("")) && (phoneNumber != null ) && (!phoneNumber.equals("")) ){
            this.id = id;
            this.firstName = firstName;
            this.lastName = lastName;
            this.phoneNumber = phoneNumber;

        }
        else
        {
            throw new IllegalArgumentException("Invalid Client parameters");
        }




    }

    @java.lang.Override
    public void assignDepartment(String departmentCode) throws IllegalStateException, IllegalArgumentException {

        if(this.departmentCode != null){
           throw new IllegalStateException("Already assigned a Department");
        }

        if((departmentCode != "") && (departmentCode != null)){
            this.departmentCode = departmentCode;
        }
        else {
            throw new IllegalArgumentException("Invalid Client parameters");
        }



    }

    @java.lang.Override
    public boolean isAssigned() {
        if(this.departmentCode != null){
            return true;
        }
        else {
            return false;
        }
    }

    @java.lang.Override
    public String getDepartmentCode() {
        return this.departmentCode;
    }

    @java.lang.Override
    public int getID() {
        return this.id;
    }

    @java.lang.Override
    public String getFirstName() {
        return this.firstName;
    }

    @java.lang.Override
    public String getLastName() {
        return this.lastName;
    }

    @java.lang.Override
    public String getPhoneNumber() {
        return this.phoneNumber;
    }
}
