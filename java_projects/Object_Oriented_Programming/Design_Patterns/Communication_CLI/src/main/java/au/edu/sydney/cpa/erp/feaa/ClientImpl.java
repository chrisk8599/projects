package au.edu.sydney.cpa.erp.feaa;

import au.edu.sydney.cpa.erp.auth.AuthToken;
import au.edu.sydney.cpa.erp.database.TestDatabase;
import au.edu.sydney.cpa.erp.feaa.clientFields.*;
import au.edu.sydney.cpa.erp.feaa.threadPools.ClientPool;
import au.edu.sydney.cpa.erp.ordering.Client;

import java.net.Inet4Address;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;

public class ClientImpl implements Client {

    private final int id;
    private String fName;
    private String lName;
    private String phoneNumber;
    private String emailAddress;
    private String address;
    private String suburb;
    private String state;
    private String postCode;
    private String internalAccounting;
    private String businessName;
    private String pigeonCoopID;

    public ClientImpl(AuthToken token, int id)  {

        ClientPool threadPool = new ClientPool(token,id);

        this.id = id;

        threadPool.makePool();

        this.fName = threadPool.getfName();
        this.lName = threadPool.getlName();
        this.phoneNumber = threadPool.getPhoneNumber();
        this.emailAddress = threadPool.getEmailAddress();
        this.address = threadPool.getAddress();
        this.suburb = threadPool.getSuburb();
        this.state = threadPool.getState();
        this.postCode = threadPool.getPostCode();
        this.internalAccounting = threadPool.getInternalAccounting();
        this.businessName = threadPool.getBusinessName();
        this.pigeonCoopID = threadPool.getPigeonCoopID();


    }

    public int getId() {
        return id;
    }

    @Override
    public String getFName() {
        return fName;
    }

    @Override
    public String getLName() {
        return lName;
    }

    @Override
    public String getPhoneNumber() {
        return phoneNumber;
    }

    @Override
    public String getEmailAddress() {
        return emailAddress;
    }

    @Override
    public String getAddress() {
        return address;
    }

    @Override
    public String getSuburb() {
        return suburb;
    }

    @Override
    public String getState() {
        return state;
    }

    @Override
    public String getPostCode() {
        return postCode;
    }

    @Override
    public String getInternalAccounting() {
        return internalAccounting;
    }

    @Override
    public String getBusinessName() {
        return businessName;
    }

    @Override
    public String getPigeonCoopID() {
        return pigeonCoopID;
    }
}

