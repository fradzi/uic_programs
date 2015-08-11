package edu.uic.cs342.fradzi1;

import java.security.SecureRandom;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;

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
public class EWSensor implements Runnable {
    
    // fields
    private static final SecureRandom randomGenerator = new SecureRandom();
    private Lock accessLock;
    private Condition carWaiting;
    private int maxLights;
    private int randSeed = 10000;
    private static boolean isEnd = true;
    
    
    
    //constructor
    public EWSensor(Lock accessLock, Condition carWaiting, int maxLights){
        this.accessLock = accessLock; 
        this.carWaiting = carWaiting;
        this.maxLights = maxLights;
    }
    
    // returns false when signal loop finishes
    public static boolean getIsEnd(){
        return isEnd;
    }
    
    @Override
    public void run() {
        
        for(int i = 0; i < maxLights; i++ ){
    
            try {
                // set thread to sleep for random time
                Thread.sleep(randomGenerator.nextInt(randSeed));
                accessLock.lock();
                System.out.println("Sending Signal " + (i+1) + " carWaiting at EW light.");
                // signal when car is waiting to TrafficLightSystem
                carWaiting.signal();
       
            } catch (InterruptedException e) {
                e.printStackTrace();
                Thread.currentThread().interrupt();
            } finally{
                accessLock.unlock();
            }
       
        }
        // reached max number of EW lights set
        isEnd = false;
    }
 
}// *** end EWSensor Class ***
