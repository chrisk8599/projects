package au.edu.sydney.cpa.erp.feaa.ordering;

import au.edu.sydney.cpa.erp.ordering.Order;
import au.edu.sydney.cpa.erp.ordering.Report;
import au.edu.sydney.cpa.erp.ordering.ScheduledOrder;

import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.*;

/**
 * This class is instantiated whenever a CriticalScheduledOrder has to be created.
 * This class is provided with an OrderTypes, in which it overrides certain
 * methods such that it behaves like a critical scheduled order.
 */


 public class CriticalScheduledOrder implements Order, ScheduledOrder {
    private OrderType type;
    private double criticalLoading;
    private int numQuarters;

    /**
     * Receive the Order type, critical loading for Critical Orders, and num Quarters for Scheduled Reports.
     */

    public CriticalScheduledOrder(OrderType type, double criticalLoading, int numQuarters){
        this.type = type;
        this.criticalLoading = criticalLoading;
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
     * Override the method such that it accounts for critical loading
     * and for number of quarters.
     * @return the total commision
     */


    @Override
    public double getTotalCommission() {
        double cost = 0.0;
        for (Report report : type.getReports().keySet()) {
            cost += type.getReports().get(report) * report.getCommission();
        }
        cost += cost * criticalLoading;
        return cost * numQuarters;
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
        return type.getReportEmployeeCount(report);
    }

    /**
     * Generate the unique invoice data for Critical Scheduled orders
     * @return the unique invoice data for Critical Scheduled orders.
     */

    @Override
    public String generateInvoiceData() {
        return String.format("Your priority business account will be charged: $%,.2f each quarter for %d quarters, with a total overall cost of: $%,.2f" +
                "\nPlease see your internal accounting department for itemised details.", getRecurringCost(), getNumberOfQuarters(), getTotalCommission());
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
     * Copy this critical scheduled order
     * @return the critical scheduled order
     */

    @Override
    public Order copy() {
        Map<Report, Integer> products = type.getReports();

        Order copy = new CriticalScheduledOrder(type, criticalLoading, getNumberOfQuarters());
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
     * Override the method such that it accounts for critical loading
     * and for num quarters and has the correct output for a
     * Critical Scheduled Order.
     * @return the longdesc.
     */


    @Override
    public String longDesc() {
        double totalBaseCost = 0.0;
        double loadedCostPerQuarter = getRecurringCost();
        double totalLoadedCost = this.getTotalCommission();
        StringBuilder reportSB = type.longDesc();

        totalBaseCost = type.getBaseTotal();

        return String.format(type.isFinalised() ? "" : "*NOT FINALISED*\n" +
                        "Order details (id #%d)\n" +
                        "Date: %s\n" +
                        "Number of quarters: %d\n" +
                        "Reports:\n" +
                        "%s" +
                        "Critical Loading: $%,.2f\n" +
                        "Recurring cost: $%,.2f\n" +
                        "Total cost: $%,.2f\n",
                type.getOrderID(),
                type.getOrderDate().format(DateTimeFormatter.ISO_LOCAL_DATE),
                numQuarters,
                reportSB.toString(),
                totalLoadedCost - (totalBaseCost * numQuarters),
                loadedCostPerQuarter,
                totalLoadedCost

        );

    }

    /**
     * Implement the Scheduled Order interface.
     */


    @Override
    public double getRecurringCost() {
        double cost = 0.0;
        for (Report report : type.getReports().keySet()) {
            cost += type.getReports().get(report) * report.getCommission();
        }
        cost += cost * criticalLoading;
        return cost;
    }

    @Override
    public int getNumberOfQuarters() {
        return numQuarters;
    }
}
