package au.edu.sydney.cpa.erp.feaa.threadPools;

import au.edu.sydney.cpa.erp.auth.AuthToken;
import au.edu.sydney.cpa.erp.feaa.clientFields.*;

import java.util.concurrent.Callable;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;

public class ClientPool  {
    private AuthToken token;
    private int id;
    private String fName;
    private String lName;
    private String phoneNumber;
    private String emailAddress;
    private String address;
    private String suburb;
    private String postCode;
    private String internalAccounting;
    private String businessName;
    private String pigeonCoopID;
    private String state;

    public ClientPool(AuthToken token, int id){
        this.token = token;
        this.id = id;
    }

    public void makePool(){
        //Create a threadpool of size 11 so that all attributes can be found at once.
        ExecutorService executor = Executors.newFixedThreadPool(11);

        //Instantiate the Callable threads for each Attribute of the client.
        Callable<String> first = new FirstName(token,id);
        Callable<String> last = new LastName(token,id);
        Callable<String> phone = new PhoneNumber(token,id);
        Callable<String> email = new EmailAddress(token,id);
        Callable<String> add = new Address(token,id);
        Callable<String> sub = new Suburb(token,id);
        Callable<String> st = new State(token,id);
        Callable<String> post = new Postcode(token,id);
        Callable<String> internal = new InternalAccounting(token,id);
        Callable<String> business = new BusinessName(token,id);
        Callable<String> pigeon = new PigeonCoopId(token,id);

        //Start the threads.
        Future<String> firstName = executor.submit(first);
        Future<String> lastName = executor.submit(last);
        Future<String> phones = executor.submit(phone);
        Future<String> emails = executor.submit(email);
        Future<String> adds = executor.submit(add);
        Future<String> subs = executor.submit(sub);
        Future<String> sts = executor.submit(st);
        Future<String> posts = executor.submit(post);
        Future<String> internals = executor.submit(internal);
        Future<String> busi = executor.submit(business);
        Future<String> pigeons = executor.submit(pigeon);

        try {
            //retrieve the values from the threads.
            this.fName = firstName.get();
            this.lName = lastName.get();
            this.phoneNumber = phones.get();
            this.emailAddress = emails.get();
            this.address = adds.get();
            this.suburb = subs.get();
            this.state = sts.get() ;
            this.postCode = posts.get();
            this.internalAccounting = internals.get();
            this.businessName = busi.get();
            this.pigeonCoopID = pigeons.get();
        }
        catch (Exception e){

        }

        executor.shutdownNow();

    }


    public String getAddress() {
        return address;
    }

    public String getBusinessName() {
        return businessName;
    }

    public String getEmailAddress() {
        return emailAddress;
    }

    public String getfName() {
        return fName;
    }

    public String getlName() {
        return lName;
    }

    public String getInternalAccounting() {
        return internalAccounting;
    }

    public String getPhoneNumber() {
        return phoneNumber;
    }

    public String getPigeonCoopID() {
        return pigeonCoopID;
    }

    public String getPostCode() {
        return postCode;
    }

    public String getState() {
        return state;
    }

    public String getSuburb() {
        return suburb;
    }
}
