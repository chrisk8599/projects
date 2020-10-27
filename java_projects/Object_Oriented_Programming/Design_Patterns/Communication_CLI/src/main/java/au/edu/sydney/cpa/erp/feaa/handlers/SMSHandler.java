package au.edu.sydney.cpa.erp.feaa.handlers;

import au.edu.sydney.cpa.erp.auth.AuthToken;

import au.edu.sydney.cpa.erp.ordering.Client;
import au.edu.sydney.cpa.erp.contact.SMS;


/**
 * Handles Sending Invoice for the SMS Contact Method.
 */

public class SMSHandler implements Chain{


    private Chain nextChain;

    /**
     * Set another handler as the next chain in the CHAIN OF RESPONSIBILITY
     *  @param nextChain a different contact method handler
     */

    @Override
    public void setNextChain(Chain nextChain) {
        this.nextChain = nextChain;
    }

    /**
     * If the type required is SMS then, send invoice, else check the next in line
     * in the chain. If the client has no phoneNumber, then this method cannot be used.
     *  @param token authentication token
     *  @param client The Client
     *  @param handlerType Type of handler desired
     *  @param data  Data to be sent.
     *  @return an int identifying if the invoice was sent or not.
     */


    @Override
    public int sendInvoice(AuthToken token, Client client, String handlerType, String data) {
        if(handlerType.equals("SMS")){

            String smsPhone = client.getPhoneNumber();
            if (null != smsPhone) {
                SMS.sendInvoice(token, client.getFName(), client.getLName(), data, smsPhone);
                return 1;
            }
            else{
                return 0;
            }
        }
        else{
            return 0;
        }


    }

}
