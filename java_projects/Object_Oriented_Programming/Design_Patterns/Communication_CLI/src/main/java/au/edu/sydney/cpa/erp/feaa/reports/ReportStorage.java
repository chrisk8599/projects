package au.edu.sydney.cpa.erp.feaa.reports;

import au.edu.sydney.cpa.erp.ordering.Report;
import com.google.common.primitives.ImmutableDoubleArray;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.List;

public class ReportStorage {

    //Store every attribute of a report in a cache.
    private static List<String> name = new ArrayList<>();
    private static List<Double> commissionPerEmployee= new ArrayList<>();
    private static List<ImmutableDoubleArray> legalData= new ArrayList<>();
    private static List<ImmutableDoubleArray> cashFlowData= new ArrayList<>();
    private static List<ImmutableDoubleArray> mergesData= new ArrayList<>();
    private static List<ImmutableDoubleArray> tallyingData= new ArrayList<>();
    private static List<ImmutableDoubleArray> deductionsData= new ArrayList<>();
    private static List<Report> reports= new ArrayList<>();

    /**
     * Add a name to the report Storage
     * @param names name
     */
    public static void addName(String names){
        name.add(names);
    }

    /**
     * Add a commission to the report Storage
     * @param comm commission
     */
    public static void addCommision(double comm){
        commissionPerEmployee.add(comm);
    }

    /**
     * Add a legal data array to the report storage
     * @param legal the legal data
     */
    public static void addLegal(ImmutableDoubleArray legal){
        legalData.add(legal);
    }

    /**
     * Add a cash data array to the report storage
     * @param cash the cash data array
     */
    public static void addCash(ImmutableDoubleArray cash){
        cashFlowData.add(cash);
    }

    /**
     * Add a merges data array to the report Storage
     * @param merge the merges data array.
     */
    public static void addMerges(ImmutableDoubleArray merge){
        mergesData.add(merge);
    }

    /**
     * Add a tally data array to the report Storage.
     * @param tally the tally data array
     */
    public static void addTally(ImmutableDoubleArray tally){
        tallyingData.add(tally);
    }


    /**
     * Add a deductions data array to the report storage.
     * @param ded the deductions data array.
     */
    public static void addDeduction(ImmutableDoubleArray ded){
        deductionsData.add(ded);
    }


    /**
     * Check if the given name exists in the storage.
     * @param names name to check
     * @return null if not found, else return the name from the storage
     * if found.
     */
    public static String checkName(String names){
        for(String name : name){
            if(name.equals(names)){
                return name;
            }
        }

        return null;
    }

    /**
     * Check if the given commission exists in the storage.
     * @param comm commission to check
     * @return null if not found, else return the commission from the storage
     * if found.
     */
    public static double checkComm(double comm){
        for(double com : commissionPerEmployee){
            if(com == comm){
                return com;
            }
        }

        return -5;
    }


    /**
     * Check if the given legalData exists in the storage.
     * @param legals legalData to check
     * @return null if not found, else return the legalData from the storage
     * if found.
     */
    public static ImmutableDoubleArray checkLegal(ImmutableDoubleArray legals){

        for(ImmutableDoubleArray legal : legalData){
            if(legal.asList().equals(legals.asList())){
                return legal;
            }
        }

        return null;
    }


    /**
     * Check if the given cashData exists in the storage.
     * @param cashs cashData to check
     * @return null if not found, else return the cashData from the storage
     * if found.
     */
    public static ImmutableDoubleArray checkCash(ImmutableDoubleArray cashs){
        for(ImmutableDoubleArray cash : cashFlowData){
            if(cash.asList().equals(cashs.asList())){
                return cash;
            }
        }

        return null;
    }


    /**
     * Check if the given mergesData exists in the storage.
     * @param merges mergesData to check
     * @return null if not found, else return the mergesData from the storage
     * if found.
     */
    public static ImmutableDoubleArray checkMerges(ImmutableDoubleArray merges){
        for(ImmutableDoubleArray merge : mergesData){
            if(merge.asList().equals(merges.asList())){
                return merge;
            }
        }

        return null;
    }


    /**
     * Check if the given tallyData exists in the storage.
     * @param tallys tallyData to check
     * @return null if not found, else return the tallyData from the storage
     * if found.
     */
    public static ImmutableDoubleArray checkTally(ImmutableDoubleArray tallys){
        for(ImmutableDoubleArray tally : tallyingData){
            if(tally.asList().equals(tallys.asList())){
                return tally;
            }
        }

        return null;
    }


    /**
     * Check if the given deductionData exists in the storage.
     * @param deductions deductionData to check
     * @return null if not found, else return the deductionData from the storage
     * if found.
     */
    public static ImmutableDoubleArray checkDeductions(ImmutableDoubleArray deductions){
        for(ImmutableDoubleArray deduction : deductionsData){
            if(deduction.asList().equals(deductions.asList())){
                return deduction;
            }
        }

        return null;
    }


    /**
     * Add the reports from the database and store them.
     * @param database the reports from the database.
     */
    public static void setReports(Collection<Report> database){
        reports.addAll(database);
    }

    /**
     * Get the reports stored in the storage.
     * @return null if no reports are being stored , else return
     * the reports being stored.
     */

    public static List<Report> getReports(){
        if(reports.size() == 0){
            return null;
        }
       return reports;
    }

}
