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


public class Controller implements Runnable {

    // fields
    private TrafficLight NS;
    private TrafficLight EW;
    private static boolean busy;

    private long nsTime = 30000;
    private long ewTime = 20000;
    private long yellowTime = 3000;

    // constructor
    public Controller(TrafficLight NS, TrafficLight EW) {

        this.NS = NS;
        this.EW = EW;
    }
    
    /**
     * North South Light running?
     * @return
     */
    public TrafficLight getNSStatus() {
        return NS;
    }
    
    /**
     * East West Light running?
     * @return
     */
    public TrafficLight getEWStatus() {
        return EW;
    }
    
    /**
     * Is the controller thread still running
     * @return
     */
    public static boolean isBusy() {
        return busy;
    }

    /**
     * Busy status setter
     * @param busy
     */
    public static void setBusy(boolean busy) {
        Controller.busy = busy;
    }

    /**
     * Cycles through NS and EW light patterns changing in synchrony when lights
     * change in either direction
     */
    public void startLightCycle() {
        try {

            System.out.println("NS light signal now YELLOW");
            NS.setLightSignal(LightSignal.YELLOW);

            System.out.println("Yellow waits for " + (yellowTime / 1000)
                    + " secs");
            Thread.sleep(yellowTime);

            System.out.println("NS light signal now RED");
            NS.setLightSignal(LightSignal.RED);

            System.out.println("EW light signal now GREEN");
            EW.setLightSignal(LightSignal.GREEN);

            System.out.println("EW light waits for " + (ewTime / 1000)
                    + " secs");
            Thread.sleep(ewTime);

            System.out.println("EW light signal now YELLOW");
            EW.setLightSignal(LightSignal.YELLOW);

            System.out.println("EW light waits for " + (yellowTime / 1000)
                    + " secs");
            Thread.sleep(yellowTime);

            System.out.println("EW light signal now RED");
            EW.setLightSignal(LightSignal.RED);

            System.out.println("NS light signal GREEN");
            NS.setLightSignal(LightSignal.GREEN);
        } catch (InterruptedException e) {

            e.printStackTrace();
        }
    }
    
    @Override
    public void run() {

        if (NS.getDuration().toMillis() >= nsTime) {
            
            // start the light cycle
            startLightCycle();

        } else {

            try {
                //get the remaining duration to wait if light running < 30 seconds
                long waitTime = Math.abs(nsTime - NS.getDuration().toMillis());
                System.out.println("Waiting for " + waitTime + " milliSecs");
                Thread.sleep(waitTime);

                // start the light cycle
                startLightCycle();

            } catch (InterruptedException e) {
                e.printStackTrace();
                // Thread.currentThread().interrupted();
            }

        }
        // Controller is finished with changes lights returning to NS in green
        busy = false;

    }

}
