package au.edu.sydney.cpa.erp.feaa.ordering;

import au.edu.sydney.cpa.erp.ordering.Order;
import au.edu.sydney.cpa.erp.ordering.Report;

import java.time.LocalDateTime;
import java.util.Map;
import java.util.Set;

public interface OrderType {
    /**
     * Get the Order ID
     * @return the order id
     */
    int getOrderID();

    /**
     * Get the order date.
     * @return the order date
     */

    LocalDateTime getOrderDate();

    /**
     * Set report for the order.
     * @param employeeCount count of employees
     * @param report report
     */
    void setReport(Report report, int employeeCount);

    /**
     * Retrieve all reports.
     * @return all reports
     */

    Set<Report> getAllReports();

    /**
     * Get the employee count for a report within an order.
     * @param report the report to check the employee count.
     * @return employee count for the report
     */
    int getReportEmployeeCount(Report report);

    /**
     * Retrieve client ID
     * @return clientID
     */

    int getClient();

    /**
     * Get the status of finalise.
     */
    void finalise();

    /**
     * Output the shortDesc.
     * @return the shortdesc.
     */
    String shortDesc();

    /**
     * Output the Reports.
     * @return the reports.
     */
    Map<Report, Integer> getReports();

    /**
     * Finalise the order.
     * @return result of finalise.
     */
    boolean isFinalised();

    /**
     * get the base total
     * @return base total to be used in longdesc
     */

    double getBaseTotal();


    /**
     * get the total commmission
     * @return total commision
     */

    double getTotalCommission();

    /**
     *Get the invoice data
     * @param sb append to this StringBuilder everything
     *          needed for the internal order type
     * @return the invoice data
     */

    String generateInvoiceData(StringBuilder sb);

    /**
     *Get the longdesc
     * @return the half finished longdesc to be finished by the
     * surrounding class
     */

    StringBuilder longDesc();
}
