package au.edu.sydney.cpa.erp.feaa.ordering;

import au.edu.sydney.cpa.erp.ordering.Order;
import au.edu.sydney.cpa.erp.ordering.Report;

import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;
import java.util.Set;

/**
 * This class is instantiated whenever a Critical Order has to be created.
 * This class is provided with an OrderTypes, in which it overrides certain
 * methods such that it behaves like a critical order.
 */


public class CriticalOrder implements Order {


    private OrderType type;
    private double criticalLoading;

    /**
     * Receive both the Order Type and the critical Loading.
     */
    public CriticalOrder(OrderType type, double criticalLoading){
        this.type = type;
        this.criticalLoading = criticalLoading;
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
     * @return the total commision
     */

    @Override
    public double getTotalCommission(){
        double cost = 0.0;
        for (Report report : type.getReports().keySet()) {
            cost += type.getReports().get(report) * report.getCommission();
        }
        cost += cost * criticalLoading;
        return cost;
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
     * Critical Orders have shorter invoice data.
     * @return the unique invoice data for Critical Orders.
     */

    @Override
    public String generateInvoiceData() {
        return String.format("Your priority business account has been charged: $%,.2f" +
                "\nPlease see your internal accounting department for itemised details.", getTotalCommission());
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
     * Copy this critical order
     * @return the critical order
     */

    @Override
    public Order copy() {
        Order copy = new CriticalOrder(type, criticalLoading);
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
        return String.format("ID:%s $%,.2f", type.getOrderID(), getTotalCommission());
    }

    /**
     * Override the method such that it accounts for critical loading
     * and has the correct output for a Critical Order.
     * @return the longdesc.
     */

    @Override
    public String longDesc() {
        double baseCommission = 0.0;
        double loadedCommission = getTotalCommission();
        StringBuilder reportSB = new StringBuilder();

        List<Report> keyList = new ArrayList<>(type.getReports().keySet());
        keyList.sort(Comparator.comparing(Report::getReportName).thenComparing(Report::getCommission));

        for (Report report : keyList) {
            double subtotal = report.getCommission() * type.getReports().get(report);
            baseCommission += subtotal;

            reportSB.append(String.format("\tReport name: %s\tEmployee Count: %d\tCommission per employee: $%,.2f\tSubtotal: $%,.2f\n",
                    report.getReportName(),
                    type.getReports().get(report),
                    report.getCommission(),
                    subtotal));
        }

        return String.format(type.isFinalised() ? "" : "*NOT FINALISED*\n" +
                        "Order details (id #%d)\n" +
                        "Date: %s\n" +
                        "Reports:\n" +
                        "%s" +
                        "Critical Loading: $%,.2f\n" +
                        "Total cost: $%,.2f\n",
                type.getOrderID(),
                type.getOrderDate().format(DateTimeFormatter.ISO_LOCAL_DATE),
                reportSB.toString(),
                loadedCommission - baseCommission,
                loadedCommission
        );




    }
}