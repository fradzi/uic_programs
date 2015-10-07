package edu.uic.cs342.fradzi1;

public abstract class Vehicle {
    /** There are two constructors. One with no args and another with 
     * the information provided from VRM class.
     */
    public Vehicle(){};
    public Vehicle (String userMake, String userModel, int userYear, 
                    String currStatus, int currentID, double currDailyCost) {
        make = userMake;
        model = userModel;
        year = userYear;
        status = currStatus; 
        id = currentID;
        dailyCost = currDailyCost;
        
    }
    
 
    /**All getters for Vehicle
     * 
     * @return
     */
    public int getID(){ return id;}
    public String getMake(){ return make;}
    public String getModel(){ return model;}
    public int getYear(){ return year;}
    public String getStatus(){ return status;}
    public double getCost(){ return dailyCost;}
    
    /**All setters for Vehicle
     * 
     * @return
     */
    public void setStatus(String newStatus){
        status = newStatus;
    }
    
    
    /**This method is used for printing when called from the VRM class
     * 
     */
    @Override
    public String toString(){
        
        return String.format("%-20s%s%n%-20s%s%n%-20s%d%n%-20s%s%n%-20s%d%n%-20s%.2f%n",
                "Make:", getMake(), "Model:", getModel(), "Year:", getYear(), 
                "Status:", getStatus(), "ID:", getID(), "Cost:", getCost());
        
    }
    /** All local variables.
     * 
     */
    private String make = null; 
    private String model = null;
    private int year = 0;
    private String status = "";
    private int id = 0;
    private double dailyCost = 0.0;
    
        
} // ** end Vehicle class **
