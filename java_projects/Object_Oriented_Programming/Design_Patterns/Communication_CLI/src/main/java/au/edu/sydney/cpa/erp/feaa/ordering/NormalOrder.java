package au.edu.sydney.cpa.erp.feaa.ordering;

import au.edu.sydney.cpa.erp.ordering.Order;
import au.edu.sydney.cpa.erp.ordering.Report;

import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.Set;

/**
 * This class is instantiated whenever a Normal Order has to be created.
 * That is, it is neither Critical nor Scheduled
 */
public class NormalOrder implements Order {

    private OrderType type;

    public NormalOrder(OrderType type){
        this.type = type;
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
     * Get the total commision
     * @return the total commision
     */

    @Override
    public double getTotalCommission() {
        return type.getTotalCommission();
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
     * Generate the invoice data for a normal order.
     * @return the unique invoice data for Normal Orders.
     */

    @Override
    public String generateInvoiceData() {
        StringBuilder sb = new StringBuilder();
        sb.append("Thank you for your Crimson Permanent Assurance accounting order!\n");
        sb.append("The cost to provide these services: $");
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
     * Copy this normal order
     * @return the normal order
     */

    @Override
    public Order copy() {
        Order copy = new NormalOrder(type);
        for (Report report : type.getReports().keySet()) {
            copy.setReport(report, type.getReports().get(report));
        }

        return copy;
    }


    /**
     * Output the shortDesc.
     * @return the shortdesc.
     */

    @Override
    public String shortDesc() {
        return type.shortDesc();
    }


    /**
     * Generate the longdesc for a normal order.
     * @return the longdesc.
     */

    @Override
    public String longDesc() {
        StringBuilder reportSB =  type.longDesc();
        return String.format(type.isFinalised() ? "" : "*NOT FINALISED*\n" +
                        "Order details (id #%d)\n" +
                        "Date: %s\n" +
                        "Reports:\n" +
                        "%s" +
                        "Total cost: $%,.2f\n",
                type.getOrderID(),
                type.getOrderDate().format(DateTimeFormatter.ISO_LOCAL_DATE),
                reportSB.toString(),
                getTotalCommission()
        );
    }
}