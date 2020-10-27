package au.edu.sydney.cpa.erp.feaa.handlers;

import au.edu.sydney.cpa.erp.auth.AuthToken;
import au.edu.sydney.cpa.erp.ordering.Client;

/**
 * Interface to define methods for the individual handlers that make up
 * the chain.
 */

public interface Chain {
     /**
      * Set another handler as the next chain in the CHAIN OF RESPONSIBILITY
      *  @param nextChain a different contact method handler
      */

     void setNextChain(Chain nextChain);


     /**
      * If the type required is correct then, send invoice, else check the next in line
      * in the chain. If the client does not pass the required checks, then this method cannot be used.

      *  @param token authentication token
      *  @param client The Client
      *  @param handlerType Type of handler desired
      *  @param data  Data to be sent.
      *  @return an int identifying if the invoice was sent or not.
      */
     int sendInvoice(AuthToken token, Client client, String handlerType, String data);
}
