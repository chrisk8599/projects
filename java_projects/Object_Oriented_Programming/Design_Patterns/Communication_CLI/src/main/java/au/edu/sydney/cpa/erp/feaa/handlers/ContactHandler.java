package au.edu.sydney.cpa.erp.feaa.handlers;

import au.edu.sydney.cpa.erp.auth.AuthToken;
import au.edu.sydney.cpa.erp.feaa.handlers.*;
import au.edu.sydney.cpa.erp.ordering.Client;

import java.util.Arrays;
import java.util.List;

public class ContactHandler implements Handler {

    private   Chain carrierPigeon;
    private   Chain email;
    private   Chain internalAccounting;
    private   Chain mail;
    private   Chain phoneCall;
    private   Chain sms;


    /**
     * Create the CHAIN OF RESPONSIBILITY.
     */
    public void createChain(){
         carrierPigeon = new CarrierHandler();
         email = new EmailHandler();
         internalAccounting = new InternalAccountingHandler();
         mail = new MailHandler();
         phoneCall = new PhoneCallHandler();
         sms = new SMSHandler();

        carrierPigeon.setNextChain(email);
        email.setNextChain(internalAccounting);
        internalAccounting.setNextChain(mail);
        mail.setNextChain(phoneCall);
        phoneCall.setNextChain(sms);

    }

    /**
     *
     * @param token auth token
     * @param client client
     * @param priority list of preferred contact methods
     * @param data data to be sent
     * @return whether the invoice was sent successfully or not as a boolean
     */
    public  boolean sendInvoice(AuthToken token, Client client, List<String> priority, String data) {
        for (String method : priority) {

            //For each method in the priority list
            //Check the handlers one by one if they match
            //in the order set by the chain
          int res =  carrierPigeon.sendInvoice(token,client,method,data);

          //if res is 1 the invoice has been sent
          if(res == 1){
              return true;
          }
          //else continue for the next method in  the priority list.

        }
        return false;
    }
    public  List<String> getKnownMethods() {
        return Arrays.asList(
                "Carrier Pigeon",
                "Email",
                "Mail",
                "Internal Accounting",
                "Phone call",
                "SMS"
        );
    }
}
