package edu.uic.cs342.fradzi1;

public class Truck extends Vehicle{
    
    /** There are two constructors. One with no args and another with 
     * the information provided from VRM class.
     */
    public Truck(){}
    
    public Truck(String userMake, String userModel, int userYear, 
            String currStatus, int id, double currDailyCost,
            double currMaxCargoWeight){
        
        super(userMake, userModel, userYear, currStatus, id, currDailyCost);
        maxCargoWeight = currMaxCargoWeight;
    
    }

    /**All getters for truck
     * 
     * @return
     */
    public static double getMaxCargoWeight(){return maxCargoWeight;}
    
    /**This method is used for printing when called from the VRM class
     * 
     */
    @Override
    public String toString(){
        
        return String.format("%s%-20s%.2f%n",super.toString(),"Max Cargo (lbs):", 
                getMaxCargoWeight());
    }
    
    /** All local variables.
     * 
     */
    private static double maxCargoWeight = 0.0;
    
} // *** end Truck class ***
