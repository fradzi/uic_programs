//
// Filip Radzikowski
// U.Illinois at Chicago
// CS 361
// HW#
// Garbage Collector
// 


// In this homework, we build a basic, conservative garbage collector for C
// programs. Starting from the set of root pointers present in the stack and
// global variables, we traverse the "object graph" (in the case of malloc, a
// chunk graph) to find all chunks reachable from the root. These are marked using
// the third lowest order bit in the size field of each chunk.
 
// As of today we have not covered the concepts related to garbage collection in
// class; if you wish to get a head start on this homework, take a look at section
// 9.10, and 9.10.2 specifically.
 
// The skeleton code in the public git repository provides supporting code for
// finding the limits of the global variable area in memory, as well as for the
// stack and heap areas. It also demonstrates very basic marking and sweeping.
// Your task is to complete the garbage collector, so that it frees all garbage,
// and leaves every other chunk intact.  To compile the template, type "make", and
// run it with ./hw3.
 
// #### Performance requirements 
// For full points, your program should pass all tests in main.c - that is, it
// should free all garbage memory. At present, these are not coded as actual
// tests, they simply output the heap size and number of free and in-use chunks.
// Nevertheless, your program should produce the correct values.
 
// Runtime performance is not a major goal for this homework. However, the program
// should finish well within 2 seconds.
 

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

struct memory_region{
    size_t * start;
    size_t * end;
};

struct memory_region global_mem;
struct memory_region heap_mem;
struct memory_region stack_mem;

//grabbing the address and size of the global memory region from processor 
void init_global_range(){
    char file[100];
    char * line=NULL;
    size_t n=0;
    size_t read_bytes=0;
    size_t start, end;
    
    printf("PID IS : %d", getpid());
    sprintf(file, "/proc/%d/maps", getpid());
    
    FILE * mapfile  = fopen(file, "r");
    if (mapfile==NULL){
        perror("opening maps file failed\n");
        exit(-1);
    }
    
    int counter=0;
    while ((read_bytes = getline(&line, &n, mapfile)) != -1) {
        if (strstr(line, "hw3")!=NULL){
            ++counter;
            if (counter==3){
                sscanf(line, "%lx-%lx", &start, &end);
                global_mem.start=(size_t*)start;
                global_mem.end=(size_t*)end;
            }
        }
        else if (read_bytes > 0 && counter==3){
            //if the globals are larger than a page, it seems to create a separate mapping
            sscanf(line, "%lx-%lx", &start, &end);
            if (start==global_mem.end){
                global_mem.end=(size_t*)end;
            }
            break;
        }
    }
    fclose(mapfile);
}

// Walk through heap, unmark any marked blocks and deallocate memory
void sweep(){
    // set ptr to heap mememory start address
    char* ptr = (char *)heap_mem.start;

    char* next;
    int isMarked;
    int isFirstBit;
    int isNextUsed;

    // walk through heap
    while (ptr < sbrk(0)){
        // mask three least significant bits to get the length
        // to next block
        int length = *(size_t*)(ptr - sizeof(size_t)) & ~7;
        next = ptr + length; 
        
        if(next < sbrk(0)){
            // check metadata of next block to see if previous was 
            // allocated.
            isNextUsed = *(size_t*)(next - sizeof(size_t)) & 1; 
            // check metadata third least significant bit if marked
            isMarked = *(size_t*)(ptr - sizeof(size_t)) & 4;
            
            // if marked and allocated
            if (isMarked && isNextUsed){  
                
                //unmark current pointer at third least significant bit 
                (*(size_t*)(ptr - sizeof(size_t))) &=~4;      
            }
            // if the following block is allocated then free
            // the current pointer
            else if (isNextUsed){     
                free (ptr); 
            }
        }
        // walk to next 
        ptr=next;
    }
}// end sweep()


// Walking the heap looking for allocated headers and marking them by 
// setting third least significant bit to 1.
void mark (size_t* ptr) {   
    
    size_t* heapPtr;
    // if address is within the heap memory addresses the initialize
    // current heap pointer, else return back to search()
    if(*ptr < heap_mem.end && *ptr >= heap_mem.start){ heapPtr = *ptr; }
    else return;

    void* next = heap_mem.start;
    void* curr = heap_mem.start;
    // walk though heap in search of allocated payloads and when one 
    // is found then initialize heapPtr to it.
    while ( curr < sbrk(0)){
        size_t length = *(size_t*)(curr - sizeof(size_t)) & ~7;
        next = curr + length;
        if(*ptr >= curr && *ptr < (size_t*)next){
            heapPtr = curr;
            break;
        }
        // increment to next pointer
        curr = next;
    }
    // step back from pointing at data to point to metadata
    // in the header
    void* header = ((void*)heapPtr - sizeof(size_t));   
    
    // check if header bit has been marked already and return if so
    int isMarkedBit = (*(size_t*)header) & 4;
    if(isMarkedBit)
        return;
    //check next payloads metadata to see if previous block is allocated
    size_t length2 = *(size_t*)(((void*)heapPtr) - sizeof(size_t)) & ~7 ;   
    size_t* nextPtr = (size_t*)((void*)heapPtr + length2); // next block
    // if next pointer goes beyond the boundry of the heap
    if(nextPtr >= sbrk(0))
        return;
    // check if next payload is allocated
    int isNextValidBit = *(size_t*)((void*)nextPtr - sizeof(size_t)) & 1;
    
    // check if allocated and if not then return
    if (!isNextValidBit)
        return;
    
    // Mark block ..
    (*(size_t*)header) |= 4;     

    //recursive call 
    size_t* iter = heapPtr;
    while ( iter < nextPtr){
        
        mark(iter);     
        iter++;     
    }    
}// end mark()


void search(){
    
    size_t* current = global_mem.start; // current is the L value 
    
    while(current < global_mem.end){
        // check if *current which is the dereferenced pointer that points
        // the heap is within the heap range 
        if(((*current) >= heap_mem.start) && ((*current) < heap_mem.end)){
            // call mark which recursively marks and allocates memory
            mark(current);
        }
        // increment the pointer pointing to the global
        current++;   
    }

    // reset start L value
    current = stack_mem.start; 
    while(current > stack_mem.end){
        // check if *current which is the dereferenced pointer that points
        // the heap is within the heap range
        if((*current) >= heap_mem.start && (*current) < heap_mem.end){
            // call mark which recursively marks and allocates memory
            mark(current);
        }
        // decrement the pointer pointing to the stack
        current--;
    }
}// end search()



// initialize the garbage collector
void init_gc() {

    //create a pointer variable at the beginning of the program as
    // init_gc is the first function to run in main()
    size_t* currentFrame;
    // set stack memory start location to the address of current pointer
    stack_mem.start = &currentFrame;

    // get the global range
    init_global_range();
    
    //malloc will return an address to the heap start since this is 
    // the first malloc to be called
    heap_mem.start=malloc(512);
    free(heap_mem.start);

}// init_gc()

// run the garbage collector
void gc() {
    
    //when gc is called then at the end of the stack. Declaring a 
    // pointer variable at this time and getting the address will 
    // give us the address of the end of the stack.
    size_t* stack_var;
    stack_mem.end = &stack_var;

    // setting the end of the heap using sbrk(0)
    heap_mem.end = sbrk(0);
    // search through stack and global for pointers that
    // point to addresses in the heap. If found then recurse
    // through those addresses marking all allocated headers. 
    search();
    // Unmark all allocated headers and free the allocated 
    // memory
    sweep();    
}// gc()
