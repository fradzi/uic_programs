/*
 * 	Filip Radzikowski
 *	U. of Illinois, Chicago
 *	CS 361, Spring 15
 * 	HW 5
 *
 *	Concurrent Elevators
 *
 */


#include "hw5.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


/* This array of structs holds all the elevator and passenger infomation 
 * needed for each elevator to operate independantly. */
struct Elevator {

	int current_floor;
	int direction; // -1 down and 1 up
	int occupancy; // 0 empty and 1 occupied by one passenger

	// id, on_floor, and to_from_floor used for elevator reference of passengers
	int passenger_id;
	int passengers_on_floor[FLOORS]; // number of passergers waiting per floor
	/* Keep track of each passenger's movements. 
	 * [PASSENGERS][0] is from_floor
	 * [PASSENGERS][1] is to_floor */
	int passenger_to_from_floor[PASSENGERS][2]; 
	
	pthread_mutex_t lock;
	// Declare condition variables  
	pthread_cond_t ok_to_enter;
	pthread_cond_t ok_to_exit;
	pthread_cond_t ok_to_close;
	pthread_cond_t ok_to_open;

	/* Individual thread created for each floor.
	 * When signaled this means that the elevator is empty and the door 
	 * is open for a single passenger to enter. */
	pthread_cond_t elevator_available[FLOORS];

	// Elevator states
	//enum {ELEVATOR_ARRIVED=1, ELEVATOR_OPEN=2, ELEVATOR_CLOSED=3} state;	

} elevators[ELEVATORS];

/* Initialize each elevators conditionals and variables */
void scheduler_init() {	
		
		int i,j,k; 		

		// For each elevator
		for(i = 0; i < ELEVATORS;i++){
			// id is initialized to correct passenger_id in passenger_request
			elevators[i].passenger_id = 0;


			elevators[i].current_floor=0;		
			elevators[i].direction=-1;
			elevators[i].occupancy=0;
			//elevators[i].state=ELEVATOR_ARRIVED;
			
			//Initialize lock on each elevator
			pthread_mutex_init(&elevators[i].lock,0);
			
			//Initialize condition variables
			pthread_cond_init(&elevators[i].ok_to_enter,NULL);
			pthread_cond_init(&elevators[i].ok_to_exit,NULL);
			pthread_cond_init(&elevators[i].ok_to_close,NULL);
			pthread_cond_init(&elevators[i].ok_to_open,NULL);

			// For every elevator thread have individtual thread per floor
			for(j=0; j < FLOORS; j++){
				pthread_cond_init(&elevators[i].elevator_available[j], NULL);
				elevators[i].passengers_on_floor[j] = 0;

			}
			// For every passengers from_floor and to_floor info per elevator
			for(j = 0; j < PASSENGERS ; j++){
				for(k = 0; k < 2 ; k++)
					elevators[i].passenger_to_from_floor[j][k];
			}

		}
}


void passenger_request(int passenger, int from_floor, int to_floor, 
											 void (*enter)(int, int), 
											 void(*exit)(int, int))
{	
	int assigned_elevator = rand() % ELEVATORS; // random elevator (1-4) to passenger
	
		
		pthread_mutex_lock(&elevators[assigned_elevator].lock);
		
		// With each passeger queueing up for the elevator tally each per floor
		elevators[assigned_elevator].passengers_on_floor[from_floor]++;
		// Declare each passengers from and to floor
		elevators[assigned_elevator].passenger_to_from_floor[passenger][0] = from_floor;
		elevators[assigned_elevator].passenger_to_from_floor[passenger][1] = to_floor;

		// wait for the elevator to arrive at our origin floor, then get in
		pthread_cond_wait(&elevators[assigned_elevator].elevator_available[from_floor], 
											&elevators[assigned_elevator].lock);
			
			// passenger enters empty elevator on passengers floor
			enter(passenger, assigned_elevator); 
			elevators[assigned_elevator].occupancy++;
			// Decrement passengers waiting for elevator on current floor
			elevators[assigned_elevator].passengers_on_floor[from_floor]--;
			elevators[assigned_elevator].passenger_id = passenger;

			// Signal ok to close the elevator door after passenger has entered
			pthread_cond_signal(&elevators[assigned_elevator].ok_to_close);	
			
			// wait for the elevator at destination floor, then get out
			pthread_cond_wait(&elevators[assigned_elevator].ok_to_exit, &elevators[assigned_elevator].lock);

			// passengers exits destination floor
			exit(passenger, assigned_elevator);
			elevators[ assigned_elevator ].occupancy--;
			pthread_cond_signal(&elevators[assigned_elevator].ok_to_close);
			
		
		//unlock after passenger has exited and ok to close elevator door signaled
		pthread_mutex_unlock(&elevators[ assigned_elevator ].lock);
	
} // end passener_request()



void elevator_ready(int elevator, int at_floor, 
										void(*move_direction)(int, int), 
										void(*door_open)(int), void(*door_close)(int)) {
	

	pthread_mutex_lock(&elevators[elevator].lock);
	
	/* For Entering:
	 * If the elevator is currently empty and there are passengers waiting 
	 * waiting on the current floor then open door, send signal that the 
	 * elevator is available, and wait for ok to close the door from passenger
	 * when they have boarded. */
	if ( elevators[elevator].occupancy == 0 
			&& elevators[elevator].passengers_on_floor[at_floor] > 0 ){

		door_open(elevator);
		//elevators[elevator].state=ELEVATOR_OPEN;
		// Signal to passenger that door is open, and elevator is empty. 
		pthread_cond_signal(&elevators[elevator].elevator_available[at_floor]);
		// Wait for signal from passenger to safely close the door after they have entered
		pthread_cond_wait(&elevators[elevator].ok_to_close, &elevators[elevator].lock);
		door_close(elevator);
	}
	/* For Exiting:
	 * If the elevator has a passenger and the elevator has arrived on the desitination 
	 * floor the passenger requested then open the door and signal the passenger to 
	 * exit elevator. Wait for a signal from the passenger to exit before safely closing 
	 * the elevator door again. */
	// check occupancy , check passeger floor 
	else if ( elevators[elevator].occupancy == 1 
		&& elevators[elevator].passenger_to_from_floor[elevators[elevator].passenger_id][1] == at_floor){
		
		door_open(elevator);
		//elevators[elevator].state=ELEVATOR_OPEN;
		// Signal the passenger that the door is open and it is safe to exit 
		pthread_cond_signal(&elevators[elevator].ok_to_exit);
		// Wait for the passenger to signal that they have exited the elevator before closing
		pthread_cond_wait(&elevators[elevator].ok_to_close, &elevators[elevator].lock);
		door_close(elevator);

	}
	//Account for direction
	else {
		if(at_floor==0 || at_floor==FLOORS-1) 
			elevators[elevator].direction*=-1;
		move_direction(elevator,elevators[elevator].direction);
		elevators[elevator].current_floor = at_floor + elevators[elevator].direction;
		//elevators[elevator].state=ELEVATOR_ARRIVED;
	}

	pthread_mutex_unlock(&elevators[elevator].lock);
} // end elevator_ready
