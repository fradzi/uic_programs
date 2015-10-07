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

import java.time.Duration;
import java.time.Instant;


public class TrafficLight {

    // fields
    private LightSignal currentSignal; 
    private Instant time;
    
    
    //constructor
    public TrafficLight(LightSignal currentSignal){
        
        this.currentSignal = currentSignal;
        this.time = Instant.now();
    }
    
    /**
     * Get the light duration
     * @return
     */
    public Duration getDuration(){
        return Duration.between(time, Instant.now());
    }// getDuration()
    
    /**
     * Resets the traffic light time and signal 
     * @param currentSignal
     */
    public void setLightSignal(LightSignal currentSignal){
        this.currentSignal = currentSignal;
        this.time = Instant.now();
    }// setLightSignal()
    
    /**
     * Get the current light signal
     * @return
     */
    public LightSignal getLightSignal(){
        return currentSignal;    
    }// getLightSignal()
    
    
        
} //*** end TrafficLight Class ***
