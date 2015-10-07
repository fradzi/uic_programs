/* --------------------------------------------------------
 * Vehicle Rental Manager
 * 
 * Class: CS 342, Spring 2015. 
 * System: Mac OS X, Version 10.10.1, Eclipse
 * Author:  Filip Radzikowski                     
 * Program: #2 (2.16.15)
 * 
 * Description: This program prompts the user for vehicle 
 * information which can then be sorted by make and model
 * by available cars, listing all cars, changing status,
 * and deleting the whole database.
 ----------------------------------------------------------*/

package edu.uic.cs342.fradzi1;


import java.util.*;


public class VRM {

    private static Scanner input = new Scanner(System.in);
    private static LinkedList vrm = new LinkedList();
   
    /**
     * This is the static main() method from which execution of the class would start. 
     * We use it mainly as a test driver for the methods in the class.  It creates a few
     * instances of the class and then sends various messages to those instances.
     * 
     * @param String[] sl--The list of arguments when this class is executed. 
     */
    public static void main (String[] args){
        
        System.out.format("Please enter a command: ");
        while(input.hasNext()){
            
            
            String currInput = input.next();
            char command = currInput.charAt(0);
            
            if(command == 'v' || command == 'V'){              
                vehicleKind(); 
            }
            else if ( command == 'c' || command == 'C'){
                newStatus();
            }
            else if ( command == 'd' || command == 'D'){
                vrm.reset();
            }
            else if (command == 'l' || command == 'L'){
                vrm.print();
            }
            else if (command == 'a' || command == 'A'){
                vrm.printAvailable();
            }
            else if (command == 's' || command == 'S'){
                if (vrm.head() == null)
                    System.err.format("There is nothing to sort.");
                else
                    vrm.aphaOrder();
            }
            else if ( command == 'q' || command == 'Q'){      
                System.out.format("GOOD BYE....\n");
                input.close();
                return;
            }
            else {
                System.out.format("Incorrect input. Please try again.\n");
                
            }
         
            System.out.format("Please enter a command: ");
        }
    }
    
    /** This method prompts, error checks, and performs changes to the 
     * status of the vehicle selected by the user using the vehicle ID. 
     */
    public static void newStatus(){
        
        boolean condition = true;
        while (true){
            
            do {
                try {
                    System.out.format("Please enter car ID to change status of: ");
                    id = input.nextInt();
                    condition = false;
                } catch (Exception e) {
                    // TODO Auto-generated catch block
                    System.err.format("Invalid Input. Please use decimal.\n");
                    input.nextLine();
                }
            } while (condition);
            
            if( vrm.idExists(id))
                break;
            else
                System.out.format("ID does not exist. Try again.\n");
            
        }
        
        while(true){
            
            System.out.format("Please enter new status(available, rented"
                    + ", or down):");
            sts = input.next();
            sts.toLowerCase();
            
            if( sts.equals("available") 
                    || sts.equals("rented")
                    || sts.equals("down"))
                    break;
            else
                System.err.format("Invalid Input: Please enter available,"
                        + " rented, or down.\n");
                    
        }
        
        vrm.changeStatus(id, sts);
        
    }// end newStatus()
    
    
    /** This method prompts the user for a specific kind of vehicle
     * before providing the user with additional question regarding their
     * choice.
     */
    public static void vehicleKind (){
        
        while(true){
            
            System.out.format("Please enter the kind of vehicle (car, truck, "
                    + " minivan): ");
            String currInput = input.next();
            currInput.toLowerCase();
            
            if( currInput.equals("car")){
                
                vehicleSetupInfo();
                carSetupInfo();
                return;
            }
            else if( currInput.equals("truck")){
                
                vehicleSetupInfo();
                truckSetupInfo();
                return;
                
            }
            else if (currInput.equals("minivan")){
                vehicleSetupInfo();
                miniVanSetupInfo();
                return;
            }
            else{
                System.out.format("Incorrect input. Please type car, truck"
                        + ", or minivan.\n");
            }  
        }  
    }// end vehicleKind();
    
    /**This method sets up the all the general questions that are asked
     * for all of the vehicles. There is error checking. The information is 
     * passed by argument to car class.
     */
    public static void carSetupInfo(){
        
        String bodyType = null;
        boolean condition = true;
        do {
            try {
                
                System.out.format("Please enter body type: ");
                bodyType = input.next();
                condition = false;
            } catch (Exception e) {
                // TODO Auto-generated catch block
                System.err.println("Incorrect Input. Enter string\n");
                input.nextLine();
            }
        } while (condition);
        
        Car car = new Car(mk,md,yr,sts,id,cst,bodyType);
        vrm.insert(car);
        System.out.println();
    }// end carSetupInfo()
    
    
    /**This method sets up the all the general questions that are asked
     * for all of the vehicles. There is error checking. The information is 
     * passed by argument to truck class.
     */
    public static void truckSetupInfo(){
        
        double maxCargoWeight = 0.0;
        boolean condition = true;
        do {
            try {
                
                System.out.format("Please enter maximum cargo weight (lbs): ");
                maxCargoWeight = input.nextDouble();
                System.out.println();
                condition = false;
            } catch (Exception e) {
                // TODO Auto-generated catch block
                System.err.println("Incorrect Input. Enter double.\n");
                input.nextLine();
            }
        } while (condition);
        
        Truck truck = new Truck(mk,md,yr,sts,id,cst,maxCargoWeight);
        vrm.insert(truck);
        System.out.println();
    
    }// end truckSetupInfo()
    
    /**This method sets up the all the general questions that are asked
     * for all of the vehicles. There is error checking. The information is 
     * passed by argument to minivan class.
     */
    public static void miniVanSetupInfo(){
        
        double length = 0.0;
        double width = 0.0;
        boolean condition = true;
        do {
            try {
                
                System.out.format("Please enter van's total length: ");
                length = input.nextDouble();
                System.out.format("Please enter van's total width: ");
                width = input.nextDouble();
                condition = false;
            } catch (Exception e) {
                // TODO Auto-generated catch block
                System.err.println("Incorrect Input. Enter double.\n");
                input.nextLine();
            }
        } while (condition);
        
        MiniVan minivan= new MiniVan(mk,md,yr,sts,id,cst,length, width);
        vrm.insert(minivan);
        System.out.println();
    
    }// end truckSetupInfo()
    
    
    
    /**This method sets up the all the general questions that are asked
     * for all of the vehicles. There is error checking. The information is 
     * passed by argument to vehicle class.
     */
    public static void vehicleSetupInfo(){
        
        
        id = vrm.size();
    
        System.out.format("Please enter vehicle make: ");
        mk = input.next();
        mk = mk.toLowerCase();
        
        System.out.format("Please enter vehicle model: ");
        md = input.next();
        md = md.toLowerCase();
        
        
        while(true){
            boolean condition = true;
            do {  
                try {
                    System.out.format("Please enter vehicle year: ");
                    yr = input.nextInt();
                    condition = false;
                
                } catch (Exception e) {
                    // TODO Auto-generated catch block
                    System.err.format("Invalid Input. Please use decimal.\n");
                    input.nextLine();
                }
            
            } while (condition); // end do-while()       
            
            if (yr <= 2016 && yr >= 1980)
                break;
            else
                System.err.format("Invalid Input: Please enter valid year "
                                + "between 1980 and 2016\n");
                        
        }// end while()
        
        
        
        
        while(true){
            
            System.out.format("Please enter current status(available, rented"
                    + ", or down):");
            sts = input.next();
            sts.toLowerCase();
            
            if( sts.equals("available") 
                    || sts.equals("rented")
                    || sts.equals("down"))
                    break;
            else
                System.err.format("Invalid Input: Please enter available,"
                        + " rented, or down.\n");
                    
        }
        
        boolean condition = true;
        do {
            try {
                System.out.format("Please enter current daily cost: ");
                cst = input.nextDouble();
                condition = false;
            } catch (Exception e) {
                // TODO Auto-generated catch block
                System.err.format("Invalid Input. Please use double.\n");
                input.nextLine();

            }
        } while (condition);
        return;
       
        
    }
    
    // local variables
    private static String mk = null; 
    private static String md = null;
    private static int yr = 0;
    private static String sts = "";
    private static int id = 0;
    private static double cst = 0.0;


} //*** end VRM class ***//


