package edu.uic.cs342.fradzi1;

public class Car extends Vehicle {

    /** There are two constructors. One with no args and another with 
     * the information provided from VRM class.
     */
    public Car(){}
    
    public Car(String userMake, String userModel, int userYear, 
                String currStatus, int id, double currDailyCost,
                String currBodyType){
        
        super(userMake, userModel, userYear, currStatus, id, currDailyCost);
        bodyType = currBodyType;
        
    }
    
    /**All getters for car
     * 
     * @return
     */
    public String getBodyType(){return bodyType; }
    
    /**This method is used for printing when called from the VRM class
     * 
     */
    @Override
    public String toString(){
        
        return String.format("%s%-20s%s%n",super.toString(),"Body Type:", 
                getBodyType());
    }
    
  
    /** All local variables.
     * 
     */
    private String bodyType = "";
}
