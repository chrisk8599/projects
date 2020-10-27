package au.edu.sydney.cpa.erp.feaa.handlers;

import au.edu.sydney.cpa.erp.auth.AuthToken;
import au.edu.sydney.cpa.erp.contact.PhoneCall;
import au.edu.sydney.cpa.erp.ordering.Client;


/**
 * Handles Sending Invoice for the PhoneCall Contact Method.
 */

public class PhoneCallHandler implements Chain {
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
     * If the type required is PhoneCall then, send invoice, else check the next in line
     * in the chain. If the client has no phoneNumber, then this method cannot be used.
     *  @param token authentication token
     *  @param client The Client
     *  @param handlerType Type of handler desired
     *  @param data  Data to be sent.
     *  @return an int identifying if the invoice was sent or not.

     */

    @Override
    public int sendInvoice(AuthToken token, Client client, String handlerType, String data) {
        if(handlerType.equals("Phone call")){


            String phone = client.getPhoneNumber();
            if (null != phone) {
                PhoneCall.sendInvoice(token, client.getFName(), client.getLName(), data, phone);
                return 1;
            }
            else{
                return 0;
            }
        }
        else{
            int res =  nextChain.sendInvoice(token,client,handlerType,data);
            return res;
        }


    }

}
