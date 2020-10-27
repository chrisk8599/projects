package au.edu.sydney.cpa.erp.feaa.handlers;

import au.edu.sydney.cpa.erp.auth.AuthToken;
import au.edu.sydney.cpa.erp.ordering.Client;

import java.util.List;

public interface Handler {
      /**
       * Create the CHAIN OF RESPONSIBILITY.
       */
      void createChain();


      /**
       *
       * @param token auth token
       * @param client client
       * @param priority list of preferred contact methods
       * @param data data to be sent
       * @return whether the invoice was sent successfully or not as a boolean
       */
      boolean sendInvoice(AuthToken token, Client client, List<String> priority, String data);
      List<String> getKnownMethods();

}
