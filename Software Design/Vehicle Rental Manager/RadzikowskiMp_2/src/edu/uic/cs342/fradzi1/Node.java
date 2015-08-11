package edu.uic.cs342.fradzi1;

public class Node {

    public Node(){}
    
    /**
     * Single argument constructor initializes new Node instance to store the object Vehicle
     * passed as an argument.  No default constructor exists, so instance creation for 
     * this class is always required to provide an integer value.
     * 
     * @param Vehicle newVehicle--The value to be stored in the initially created node.
     */
    public Node(Vehicle newVehicle) {
        vehicle = newVehicle;
        next = null;
    }
    
    /** 
     * Getter method for vehicle field
     * 
     * @return Vehicle--The current value of vehicle object
     */
    public Vehicle vehicle() { return vehicle ; }
    
    /**
     * Getter method for next field
     * 
     * @return Node--The next Node in the chain, or null
     * 
     */
    public Node next() { return next ; }
    
    /**
     * Setter method for vehicle field
     * 
     * @param Vehicle newVehicle--New value of vehicle field.
     * 
     */
    public void vehicle(Vehicle newVehicle) {
        vehicle = newVehicle;
    }
    
    /**
     * Setter method for next field
     * 
     * @param Node newNext--New value for next field
     * 
     */
    public void next(Node newNext) {
        next = newNext ;
    }
    
    // Vehicle field stores Vehicle object; next stores pointer to next node.
    private Vehicle vehicle; 
    private Node next = null ;
}
