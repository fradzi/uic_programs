package edu.uic.cs342.fradzi1;

public class MiniVan extends Vehicle{
    
    /** There are two constructors. One with no args and another with 
     * the information provided from VRM class.
     */
    public MiniVan(){}
    
    public MiniVan(String userMake, String userModel, int userYear, 
            String currStatus, int id, double currDailyCost,
            double currLength, double currWidth){
        
        super(userMake, userModel, userYear, currStatus, id, currDailyCost);
        length = currLength;
        width = currWidth;
    }

    
    /**All getters for minivan
     * 
     * @return
     */
    public static double getLength(){return length;}
    public static double getWidth(){return width;}
    
    /**This method is used for printing when called from the VRM class
     * 
     */
    @Override
    public String toString(){
        
        return String.format("%s%-20s%.2f%n%-20s%.2f%n",super.toString(),
                "Length:", getLength(),"Width:", getWidth()); 
                
    }
    
    /** All local variables.
     * 
     */
    private static double length = 0.0;
    private static double width = 0.0;
}
