package au.edu.sydney.cpa.erp.feaa.reports;

import au.edu.sydney.cpa.erp.ordering.Report;
import com.google.common.primitives.ImmutableDoubleArray;

import java.util.HashMap;
import java.util.Objects;

public class  ReportImpl implements Report{

    //They are all set as final because they have to be immutable to be a value object.

    private final String name;
    private final double commissionPerEmployee;
    private final ImmutableDoubleArray legalData;
    private final ImmutableDoubleArray cashFlowData;
    private final ImmutableDoubleArray mergesData;
    private final ImmutableDoubleArray tallyingData;
    private final ImmutableDoubleArray deductionsData;



    public ReportImpl(String name,
                      double commissionPerEmployee,
                      double[] legalData,
                      double[] cashFlowData,
                      double[] mergesData,
                      double[] tallyingData,
                      double[] deductionsData) {

        //Check if the name given exists in the ReportStorage.

        String names = ReportStorage.checkName(name);

        if(names == null){

            // if it doesnt add it to the storage
            this.name = name;
            ReportStorage.addName(name);
        }
        else{

            // if it exists use the name in the Storage.
            this.name = names;
        }

        //Check if the commission given exists in the ReportStorage.

        double comm = ReportStorage.checkComm(commissionPerEmployee);

        if(comm == -5){
            // if it doesnt add it to the Storage.
            this.commissionPerEmployee = commissionPerEmployee;
            ReportStorage.addCommision(commissionPerEmployee);
        }
        else{
            //if it does exist, use the commission value from the storage.
            this.commissionPerEmployee = comm;
        }

        if (legalData == null) {
            this.legalData = null;
        } else {

            //Check if the legal data given exists within the ReportStorage.
            ImmutableDoubleArray legal  = ReportStorage.checkLegal(ImmutableDoubleArray.copyOf(legalData));

            if(legal == null){
                //if not add it to the storage.
                ImmutableDoubleArray legals = ImmutableDoubleArray.copyOf(legalData);
                this.legalData = legals;
                ReportStorage.addLegal(legals);
            }
            else{
                //if it does exist use the data from the storage instead.
                this.legalData = legal;
            }

        }


        if (cashFlowData == null) {
            this.cashFlowData = null;
        } else {
            //check if the cashflow data given exists within the ReportStorage.
            ImmutableDoubleArray cash  = ReportStorage.checkCash(ImmutableDoubleArray.copyOf(cashFlowData));

            if(cash == null){
                //if not , add it to the storage
                ImmutableDoubleArray cashes = ImmutableDoubleArray.copyOf(cashFlowData);
                this.cashFlowData = cashes;
                ReportStorage.addCash(cashes);
            }
            else{
                //If it does exists, use the data from the storage instead.
                this.cashFlowData = cash;
            }
        }

        if (mergesData == null) {
            this.mergesData = null;
        } else {
            //Check if the merges data given exists within the ReportStorage.
            ImmutableDoubleArray merge  = ReportStorage.checkMerges(ImmutableDoubleArray.copyOf(mergesData));

            if(merge == null){
                //If not, add it to the storage.
                ImmutableDoubleArray merges = ImmutableDoubleArray.copyOf(mergesData);
                this.mergesData = merges;
                ReportStorage.addMerges(merges);
            }
            else{
                //if it does exist, use the data from the storage instead.
                this.mergesData = merge;
            }
        }

        if (tallyingData == null) {
            this.tallyingData = null;
        } else {
            //Check if the tallying data given exists within the ReportStorage.
            ImmutableDoubleArray tally  = ReportStorage.checkTally(ImmutableDoubleArray.copyOf(tallyingData));

            if(tally == null){
                //If not, add it to the storage.
                ImmutableDoubleArray tallys = ImmutableDoubleArray.copyOf(tallyingData);
                this.tallyingData = tallys;
                ReportStorage.addTally(tallys);
            }
            else{
                //if it does exist, use the data from the storage instead.
                this.tallyingData = tally;
            }
        }

        if (deductionsData == null) {
            this.deductionsData = null;
        } else {
            //Check if the deductions data given exists within the ReportStorage.
            ImmutableDoubleArray deduction  = ReportStorage.checkDeductions(ImmutableDoubleArray.copyOf(deductionsData));

            if(deduction == null){
                //If not, add it to the storage.
                ImmutableDoubleArray deductions = ImmutableDoubleArray.copyOf(deductionsData);
                this.deductionsData = deductions;
                ReportStorage.addDeduction(deductions);
            }
            else{
                //if it does exist, use the data from the storage instead.
                this.deductionsData = deduction;
            }
        }





    }

    @Override
    public String getReportName() {
        return name;
    }

    @Override
    public double getCommission() {
        return commissionPerEmployee;
    }

    @Override
    public double[] getLegalData() {
        if(legalData == null){
            return null;
        }

        double[] legal =new double[legalData.length()];

        for(int i = 0 ; i < legalData.length();i++){
            legal[i] = legalData.get(i);
        }


        return legal;
    }

    @Override
    public double[] getCashFlowData() {
        if(cashFlowData == null){
            return null;
        }

        double[] cash =new double[cashFlowData.length()];

        for(int i = 0 ; i < cashFlowData.length();i++){
            cash[i] = cashFlowData.get(i);
        }


        return cash;
    }

    @Override
    public double[] getMergesData() {
        if(mergesData == null){
            return null;
        }

        double[] merge =new double[mergesData.length()];

        for(int i = 0 ; i < mergesData.length();i++){
            merge[i] = mergesData.get(i);
        }


        return merge;
    }

    @Override
    public double[] getTallyingData() {
        if(tallyingData == null){
            return null;
        }

        double[] tally =new double[tallyingData.length()];

        for(int i = 0 ; i < tallyingData.length();i++){
            tally[i] = tallyingData.get(i);
        }


        return tally;
    }

    @Override
    public double[] getDeductionsData() {
        if(deductionsData == null){
            return null;
        }

        double[] ded =new double[deductionsData.length()];

        for(int i = 0 ; i < deductionsData.length();i++){
            ded[i] = deductionsData.get(i);
        }


        return ded;
    }

    @Override
    public String toString() {

        return String.format("%s", name);
    }

    /**
     * Report can be treated as a value object and hence
     * reports can be compared to one another based on values.
     * @param o Report objects
     * @return the result of the equality
     */
    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        ReportImpl report = (ReportImpl) o;
        return Double.compare(report.commissionPerEmployee, commissionPerEmployee) == 0 &&
                Objects.equals(name, report.name) &&
                Objects.equals(legalData, report.legalData) &&
                Objects.equals(cashFlowData, report.cashFlowData) &&
                Objects.equals(mergesData, report.mergesData) &&
                Objects.equals(tallyingData, report.tallyingData) &&
                Objects.equals(deductionsData, report.deductionsData);
    }

    @Override
    public int hashCode() {
        return Objects.hash(name, commissionPerEmployee, legalData, cashFlowData, mergesData, tallyingData, deductionsData);
    }
}
