/**
 * Traffic Light System
 * 
 * Filip Radzikowski
 * U. of Illinois, Chicago
 * CS 342 Software Design
 * 5.2.15
 * 
 * Project 5
 * 
 * The TLS consists of an intersection between two streets traveled by cars. 
 * The TLS must manage access to the intersection by cars travelling in 
 * perpendicular directions. Your job is to program and simulate the TLS using 
 * Java multi-threading code. The TLS manages the lights at an intersection 
 * between a North-South (NS) street and an East-West (EW) street. Of course, 
 * when the light is green in one direction, it must be red in the opposite 
 * direction and vice versa. The TLS would normally keep the light green in the 
 * NS direction, except when cars approach the intersection from the EW 
 * direction. When this happens, a sensor informs the TLS of the presence of a 
 * car in the EW direction. If the light has been green in the NS direction for 
 * at least 30 seconds, the light will turn to the amber color for 3 seconds, 
 * and then red in the NS direction and green in the EW direction. If, however, 
 * the light was green in the NS direction for less than 30 seconds, the TLS 
 * waits until the green cycle completes 30 seconds and then turns the light to 
 * amber and red. Finally, if the light was not green in the NS direction, input 
 * from the sensor in the EW direction is ignored. Once the light turns green in 
 * the EW direction, it stays that way for 20 seconds, then turns amber (for 3 
 * seconds) and red in the EW direction (now green in the NS direction)
 * 

 * 
 */
package edu.uic.cs342.fradzi1;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;



public class TLSDriver {

    
    public static void main(String[] args) {
        // TODO Auto-generated method stub
        int maxLights = 7;
        
        Lock accessLock = new ReentrantLock();
        Condition carWaiting = accessLock.newCondition();
        
        ExecutorService threadExecutor = Executors.newCachedThreadPool();
        
        // instantiate traffic light system with lock and control
        threadExecutor.execute(new TrafficLightSystem(accessLock, carWaiting));
        // instantiate EWSensor with lock, control, and number of times to 
        // set EW lights to run
        threadExecutor.execute(new EWSensor(accessLock, carWaiting, maxLights));
    
    
        // don't accept any new task and shut down current
        threadExecutor.shutdown();
        // wait for threads to shut down
        try {
            threadExecutor.awaitTermination(1, TimeUnit.MINUTES);
        
        } catch (InterruptedException e) {
            
            e.printStackTrace();
        }finally{
            
            System.out.println("\n>>>TLS ENDED SUCCESSFULLY\n   Thank You!");
        }
        
        
    } // end main() 
    
    
}// *** end TLSDriver Class ***
