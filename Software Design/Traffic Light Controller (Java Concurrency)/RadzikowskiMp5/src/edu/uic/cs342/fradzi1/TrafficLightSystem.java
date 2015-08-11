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
 */
package edu.uic.cs342.fradzi1;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.Condition;


public class TrafficLightSystem implements Runnable {
    
    // fields
    int i = 1;
    private Lock accessLock;
    private Condition carWaiting;
    private ExecutorService threadExecutor;
    private TrafficLight NS, EW;
    
    // constructor
    public TrafficLightSystem(Lock accessLock, Condition carWaiting){
        this.accessLock = accessLock;
        this.carWaiting = carWaiting;
        this.threadExecutor = Executors.newCachedThreadPool();
        
        // initializing NS Light to green and EW to Red
        NS = new TrafficLight(LightSignal.GREEN);
        EW = new TrafficLight(LightSignal.RED);
    }
    
    
    /**
     * The main logic synchronizing the Sensor threads and the Traffic light
     * system thread. 
     */
    public void run(){
        Controller.setBusy(false);
        while(EWSensor.getIsEnd()){
            
            accessLock.lock();
            
            try {
                //Waiting for signal from Sensor that car is waiting
                carWaiting.await();
                
                System.out.println("Recieved signal" + i + " from EW ");
                i++;
                
                // if the EW light is already green or yellow then cars can pass
                if(NS.getLightSignal() != LightSignal.GREEN){   
                    System.out.println("Ignoring Signal because NS not green");
                // if NS light is green
                }else{
                    // if EW is already letting cars pass
                    if(Controller.isBusy()){
                        System.out.println("Ignoring Signal EW already running");
                    // start new thread for EW to let cars beging to pass
                    }else{
                        Controller.setBusy(true);
                        threadExecutor.execute(new Controller( NS, EW ));
                    }    
                }
            } catch (Exception e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
                Thread.currentThread().interrupt();
            } finally{
                // release traffic light system lock
                accessLock.unlock();
            }
    
        }// end while loop

        // don't accept any new task and shut down current
        threadExecutor.shutdown();
        // wait for threads to shut down
        try {
            threadExecutor.awaitTermination(1, TimeUnit.MINUTES);
        
        } catch (InterruptedException e) {
            
            e.printStackTrace();
        }
    
    }// end run()
    

}// *** end TrafficLightSystem Class ***
