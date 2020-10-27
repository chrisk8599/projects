package au.edu.sydney.cpa.erp.feaa.ordering;

import au.edu.sydney.cpa.erp.ordering.Order;
import au.edu.sydney.cpa.erp.ordering.Report;

import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.*;

/**
 * This class is instantiated whenever a Scheduled Order has to be created.
 * This class is provided with an OrderTypes, in which it overrides certain
 * methods such that it behaves like a Scheduled order.
 */

public class ScheduledOrder implements Order, au.edu.sydney.cpa.erp.ordering.ScheduledOrder {
    private int numQuarters;
    private OrderType type ;

    /**
     *
     * @param type type of order
     * @param numQuarters number of quarters (unique to Scheduled)
     */
    public ScheduledOrder(OrderType type, int numQuarters){
        this.type = type;
        this.numQuarters = numQuarters;
    }

    /**
     * Get the Order ID
     * @return the order id
     */
    @Override
    public int getOrderID() {
        return type.getOrderID();
    }

    /**
     * Override the method such that it accounts for number of quarters
     * @return the total commision
     */

    @Override
    public double getTotalCommission() {
        return type.getTotalCommission() * numQuarters;
    }

    /**
     * Get the order date.
     * @return the order date
     */
    @Override
    public LocalDateTime getOrderDate() {
       return type.getOrderDate();
    }

    /**
     * Set report for the order.
     * @param employeeCount count of employees
     * @param report report
     */


    @Override
    public void setReport(Report report, int employeeCount) {
        type.setReport(report,employeeCount);
    }

    /**
     * Retrieve all reports.
     * @return all reports
     */
    @Override
    public Set<Report> getAllReports() {
        return type.getAllReports();
    }

    /**
     * Get the employee count for a report within an order.
     * @param report the report to check the employee count.
     * @return employee count for the report
     */
    @Override
    public int getReportEmployeeCount(Report report) {
       return getReportEmployeeCount(report);
    }

    /**
     * Generate the invoice data for Scheduled Orders.
     * @return the unique invoice data for Scheduled Orders.
     */
    @Override
    public String generateInvoiceData() {
        StringBuilder sb = new StringBuilder();

        sb.append("Thank you for your Crimson Permanent Assurance accounting order!\n");
        sb.append("The cost to provide these services: $");
        sb.append(String.format("%,.2f", getRecurringCost()));
        sb.append(" each quarter, with a total overall cost of: $");
        sb.append(String.format("%,.2f", getTotalCommission()));
        sb.append("\nPlease see below for details:\n");

       return type.generateInvoiceData(sb);

    }

    /**
     * Retrieve client ID
     * @return clientID
     */

    @Override
    public int getClient() {
        return type.getClient();
    }

    /**
     * Get the status of finalise.
     */
    @Override
    public void finalise() {
        type.finalise();
    }

    /**
     * Copy this Scheduled order
     * @return the Scheduled order
     */
    @Override
    public Order copy() {
        Map<Report, Integer> products = type.getReports();

        Order copy = new ScheduledOrder(type, numQuarters);
        for (Report report : products.keySet()) {
            copy.setReport(report, products.get(report));
        }

        return copy;
    }

    /**
     * Output the shortDesc.
     * @return the shortdesc.
     */
    @Override
    public String shortDesc() {
        return String.format("ID:%s $%,.2f per quarter, $%,.2f total", type.getOrderID(), getRecurringCost(), getTotalCommission());
    }


    /**
     * Override the method such that it accounts for number of quarters
     * and has the correct output for a Scheduled Order.
     * @return the longdesc.
     */

    @Override
    public String longDesc() {

        StringBuilder reportSB = type.longDesc();

        return String.format(type.isFinalised() ? "" : "*NOT FINALISED*\n" +
                        "Order details (id #%d)\n" +
                        "Date: %s\n" +
                        "Number of quarters: %d\n" +
                        "Reports:\n" +
                        "%s" +
                        "Recurring cost: $%,.2f\n" +
                        "Total cost: $%,.2f\n",
                type.getOrderID(),
                type.getOrderDate().format(DateTimeFormatter.ISO_LOCAL_DATE),
                numQuarters,
                reportSB.toString(),
                type.getTotalCommission(),
                this.getTotalCommission()

        );
    }


    /**
     * Get the recurring cost to be paid
     * per quarter
     * @return the recurring cost.
     */

    @Override
    public double getRecurringCost() {
        return type.getTotalCommission();
    }

    /**
     * get the number of quarters
     * @return number of quarters
     */
    @Override
    public int getNumberOfQuarters() {
        return numQuarters;
    }
}
