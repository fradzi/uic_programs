package edu.uic.cs342.fradzi1;

/**
 * @author f
 *
 */
public class LinkedList {

    
    /** No-arg constructor just increments total number of instances created
     * 
     */
    public LinkedList() {
        size = 1;
        tally++;
    }
    
    
    /** This method is called before a LinkedList is destroyed by the garbage collector.
     * 
     */
    public void finalize() {
        tally--;
    }
    
    /** This method inserts a new Vehicle in the receiver LinkedList 
     * 
     * @param x:  The integer to be inserted 
     * @return the modified receiver
     */
    public LinkedList insert(Vehicle newVehicle) {
        
        if (head == null) {         
            head = tail = new Node(newVehicle) ;  }
        
        else {
            tail.next(new Node(newVehicle)) ;
            tail = tail.next() ;
        }
        
        size++;
        return this ;
    }
   
    
    /** Boolean method to check between two strings and returns 
     * true if the parameters are met.   
     * @param x
     * @param y
     * @return
     */
    private boolean lessThanMake(Node x, Node y){
        
        if (x.vehicle().getMake().compareToIgnoreCase(y.vehicle().getMake()) < 0){
            return true;
        }
        else
            return false;        
    } // end lessThanMake()
    /** Boolean method to check between two strings and returns 
     * true if the parameters are met.   
     * @param x
     * @param y
     * @return
     */
    private boolean lessThanModel(Node x, Node y){
        
        if (x.vehicle().getModel().compareToIgnoreCase(y.vehicle().getModel()) < 0){
            return true;
        }
        else
            return false;
    }
    /** Boolean method to check between two strings and returns 
     * true if the parameters are met.   
     * @param x
     * @param y
     * @return
     */
    private boolean greaterThanMake(Node x, Node y){
        
        if (x.vehicle().getMake().compareToIgnoreCase(y.vehicle().getMake()) > 0){
            return true;
        }
        else
            return false;        
    } // end lessThanMake()
    /** Boolean method to check between two strings and returns 
     * true if the parameters are met.   
     * @param x
     * @param y
     * @return
     */
    private boolean greaterThanModel(Node x, Node y){
    
        if (x.vehicle().getModel().compareToIgnoreCase(y.vehicle().getModel()) > 0){
            return true;
        }
        else
            return false; 
    }
    /** Boolean method to check between two strings and returns 
     * true if the parameters are met.   
     * @param x
     * @param y
     * @return
     */
    private boolean equalToMake(Node x, Node y ){
        
        if (x.vehicle().getMake().compareToIgnoreCase(y.vehicle().getMake()) == 0){
            return true;
        }
        else
            return false;        
    } // end lessThanMake()

    
    
    /**This method is returns a new linked list with the 
     * elements in order by make and model.Calls on booleans to 
     * check if strings are less, greater, or equal to each other.
     * @param x
     * @return
     */
    public LinkedList insertInOrder(Node x){
      
        Node newNode = new Node(x.vehicle());
        
        
        if (head == null) {
            head = tail = newNode;
            size = 1;
            return this;
        }
        if (lessThanMake(x, head)) {
            newNode.next(head);
            head = newNode;
            size++;
            return this;
        }
        else if (equalToMake(x,head)){
            
            if (lessThanModel(x, head)) {
                newNode.next(head);
                head = newNode;
                size++;
                return this;
            }   
        }

        for (Node previous = head, current = head.next(); current != null; 
                previous = current, current = current.next()) {
            
            if (greaterThanMake (current , x)) {
                newNode.next(current);
                previous.next(newNode);
                size++;
                return this;
            }
            else if( equalToMake(current, x)){
                if (greaterThanModel(current, x)) {
                    newNode.next(current);
                    previous.next(newNode);
                    size++;
                    return this;
                } 
            }
        }
        tail.next(newNode);
        tail = newNode;
        size++;
        return this;
    }
        
      
    
    /**This method is called when the user requests that 
     * the data base be sorted by make and model. Calls insertInOrder()
     * to take all current vehicle nodes and pass them one by one 
     * to get inserted in order.
     */
    public void aphaOrder(){

        if (this.head == null)
            return;
        
        LinkedList newList = new LinkedList();
        //Node newHead = newList.head();
        
        Node temp = this.head;
        
        while( temp != null){
            
            newList.insertInOrder(temp);
            
            temp = temp.next();
            //Node newNode = new Node(head.vehicle());
            //System.out.format("%s\n", newNode);
         
       }
    this.head = newList.head();
    this.tail = newList.tail();
        
    }// end aphaOrder()
    
   
    
    
    /** This method sets linked list instance to null, deleting 
     * all vehicle data. 
     * @return
     */
    public LinkedList reset(){
        head = null;
        size = 1;
        tally = 0;
        
        return this;
    }// end reset() 

    
    /** This method returns true id a certain ID that the user 
     * input exist in the database.
     * @param currID
     * @return
     */
    public boolean idExists(int currID){
        Node temp = head;
        
        while(temp != null){
       
            if(temp.vehicle().getID() == currID)
                return true;
            else{
                temp = temp.next();
            }      
        }
        
        return false;
        
    }// end idExists();
    
    /**This method changes the status of the vehicle selected to 
     * what the user sets it to.
     * @param currID
     * @param currStatus
     */
    public void changeStatus(int currID, String currStatus){
        
        Node temp = head;
        
        while(temp != null){
            
            if(temp.vehicle().getID() == currID)
                break;
            else{
                temp = temp.next();
            }
        }
        
        temp.vehicle().setStatus(currStatus);
        
       
    }// end changeStatus
    
    
    /** This method returns true id a vehicle is available 
     * for rent.
     * @param n
     * @return
     */
    public boolean available (Node n){
        if( n.vehicle().getStatus().equals("available"))
            return true;
        else
            return false;
    }
    
    /** This method prints all the available vehicles 
     * 
     */
    
    public void printAvailable(){
        
        if (head == null)
            System.out.format("No vehicles in database.\n");
        else{
            boolean avblExists = false;
            for(Node n = head; n != null; n = n.next()){
                if( available(n))  {   
                    System.out.format("%s \n", n.vehicle()); 
                    avblExists = true;
                }
            }
            if(!avblExists)
                System.out.format("No available vehicles.\n");
            
        }
    }
    
   
    /** This method prints the content of the receiver on the standard output stream.
     * An appropriate message is output if the receiver has no nodes.  Otherwise, the
     * integer number stored in each node is printed in the order of the nodes.
     */
    public void print() {
        
        if (head == null) 
            System.out.print("No vehicles in database\n");
        else {    
            for(Node n = head; n != null; n = n.next()){
               System.out.format("%s \n", n.vehicle()); 
            }
        }
            System.out.print("\n");
    }
    
    
    /** 
     * Getter method for size field.
     * @return int size
     */
    public int size() {
        return size;
    }   

    /** 
     * Getter method for head field.
     * @return int size
     */
    public Node head() {
        return head ;
    }
    /** 
     * Getter method for tail field.
     * @return int size
     */
    public Node tail() {
        return tail ;
    }
    
    /** The fields point to the head and tail Node objects of the list.
     * A size field keeps track of the total size of the list.
     */
    protected Node head = null ;
    protected Node tail = null ;
    protected int size = 0 ;
    
    /** returns the tally
     * 
     */
    public static int tally() {
        return tally;
    }
    
    /** 
     * Static field to keep track of total number of instances of LinkedList created
     * and not garbage collected yet.
     */
    protected static int tally = 0;
    
    

}
