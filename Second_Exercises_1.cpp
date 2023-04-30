#include<stdio.h>
#include <stdbool.h>
int main() {
    // Initialize variables
    int i = 0, num_processes = 0, total_time = 0, x, output_flag = 0,time_quantum =0;
    int wait_time = 0, turnaround_time = 0, arrival_time[10], burst_time[10],temp[10];
    float average_wait_time = 0, average_turnaround_time = 0;
    bool round_robin_algorithm = true;
    bool printRoundRobinDebug = false;
    for(i = 0; i < 10; i++)
    {
        arrival_time[i] = 0;
        burst_time[i] = 0;
        temp[i] = 0;
    }
    // Define Number of Processes
    while(num_processes < 1 || num_processes > 10)
    {
        printf("\nEnter Total Number of Processes (1 - 10):\t");
        scanf("%d", &num_processes);
        if (num_processes < 1 || num_processes > 10)
        {
            printf("Incorrect Value Entered");
        }
    }
  // Define Process Details
    x = num_processes;
    for(i = 0; i < num_processes; i++)
    {
        printf("\nEnter Details of Process[%d]\n", i + 1);
        printf("Arrival Time (>-1):\t");
        scanf("%d", &arrival_time[i]);
        printf("Burst Time (>0):\t");
        scanf("%d", &burst_time[i]);
        temp[i] = burst_time[i];
        if (arrival_time[i] < 0 && burst_time[i] < 1) {
            printf("Incorrect Values Entered");
            i--;
        } 
    }

    // Define Quantum
    if (round_robin_algorithm) {

    }
    printf("\nEnter Time Quantum (>0):\t");
    scanf("%d", &time_quantum);
    if (time_quantum < 1)
    {   
        printf("Incorrect Value Entered");
    }

    // Prepare Output
    printf("\nProcess ID\t\tArrival Time\t\tBurst Time\t Turnaround Time\tWaiting Time\n");

    // Perform Scheduling Calculations
    int processSorted[num_processes];
    int arrivalTimeCopy[num_processes];
    for(int i = 0; i < num_processes;i++){
        arrivalTimeCopy[i] = arrival_time[i];
    }
    //SORT THE ALGORITHM
    for(int processSort = 0;processSort < num_processes;processSort++){
        int min = __INT_MAX__;
        int minIndex = 0;
        for(int processOrg = 0;processOrg < num_processes;processOrg++){
            if(arrival_time[processOrg] < min){
                min = arrivalTimeCopy[processOrg];
                minIndex = processOrg;
            }
        }
        processSorted[processSort] = minIndex;
        arrivalTimeCopy[minIndex] = __INT_MAX__;
    }

    //Refresh the arrival time copy array
    for(int i = 0; i < num_processes;i++){
        arrivalTimeCopy[i] = arrival_time[i];
    }
    if (!round_robin_algorithm){
        //CALCULATE WAITING
        double totalWaitSum = 0.0;
        double totalTurnaroundSum = 0.0; 
        for(int unsortedprocess = 0; unsortedprocess < num_processes; unsortedprocess++){
            int process = processSorted[unsortedprocess];
            int totalProcessWait = 0;
            for(int wait = 0; wait < unsortedprocess; wait++){
                totalProcessWait += burst_time[wait];
            }
            //acount for arrival time and its own burst time
            double turnAroundTime = (totalProcessWait - arrival_time[process] + burst_time[process]);
            double waitTime = (totalProcessWait - arrival_time[process]);
            totalTurnaroundSum += turnAroundTime;
            totalWaitSum += waitTime;
            printf("\nProcess[%d]\t\t\t%d\t\t\t %d\t%f\t\t%f\n", unsortedprocess,arrival_time[process],burst_time[process],turnAroundTime,waitTime);
        }
        average_wait_time = totalWaitSum/(double)num_processes;
        average_turnaround_time = totalTurnaroundSum/(double)num_processes;
    }
    else
    {
    // Perform Scheduling Calculations
        //the time waited for each process is tracked in an array. When an arrived process is not active, 1 is added to its position in the array
        int timeWaited[num_processes];
        int turnAroundTime[num_processes];
        int burstTimeCopy[num_processes];
        for(int i = 0; i < num_processes; i++){
            timeWaited[processSorted[i]] = 0;
            turnAroundTime[processSorted[i]] = 0;
            burstTimeCopy[processSorted[i]] = burst_time[processSorted[i]];
        }

        //when the burst time of all processes 
        char done = 1;
        do{//while all process are not complete
            done = 1;// start by assuming we are done, the look through the proceses and see if there any with remaining burst time
            for(int process = 0; process < num_processes;process++){//iterate through the process
                if(burstTimeCopy[processSorted[process]] > 0 && arrivalTimeCopy[processSorted[process]] <= 0){ // while the selected process still has work that needs to be done 
                    done = 0; //we know where are not done if there is a process that needs work.
                    for(int quantumPeriod = 0; quantumPeriod < time_quantum; quantumPeriod++){// incremental cycle through the quantum so that we know if a process finishes early
                        burstTimeCopy[processSorted[process]] = burstTimeCopy[processSorted[process]] - 1;// do one period of work on the current process
                        total_time++;//add to the total time elapsed
                        

                    if(printRoundRobinDebug){
                        //DEBUG PRINTING BEGIN
                        printf("\n\nTime Elapsed: %d\t Current on Process %d \n Burst\n", total_time,process);
                        for(int burst = 0; burst < num_processes; burst++){
                            printf("%d: %d\t",burst , burstTimeCopy[burst]);
                        }
                        printf("\nArrival\n");

                        for(int arrival = 0; arrival < num_processes; arrival++){
                            printf("%d: %d\t",arrival , arrivalTimeCopy[arrival]);
                        }
                        printf("\nWaiting\n");

                        for(int wait= 0; wait < num_processes; wait++){
                            printf("%d: %d\t",wait , timeWaited[wait]);
                        }
                        printf("\nTurnaround\n");

                        for(int turnaround= 0; turnaround < num_processes; turnaround++){
                            printf("%d: %d\t",turnaround , turnAroundTime[turnaround]);
                        }
                        printf("\n");
                    }   //DEBUG PRINTING END

                        for(int arrivingProcesses = 0; arrivingProcesses < num_processes; arrivingProcesses++){
                            if(arrivalTimeCopy[arrivingProcesses] > 0){ 
                                arrivalTimeCopy[arrivingProcesses] = arrivalTimeCopy[arrivingProcesses] - 1;
                            }
                        }
                        for(int waitingProcesses = 0; waitingProcesses < num_processes; waitingProcesses++){//add one wait time to all the waiting process
                            if(waitingProcesses != processSorted[process] && arrivalTimeCopy[waitingProcesses] <= 0 && burstTimeCopy[waitingProcesses] > 0){// if the waiting process is not the process that is actually doing work
                                timeWaited[waitingProcesses]= timeWaited[waitingProcesses] + 1; // add one the the time that the process has been waiting.
                            }//end waiting process if
                        }//end waiting process for
                        if(burstTimeCopy[processSorted[process]] <= 0){//If the burst time of the current process is finally zero
                            turnAroundTime[processSorted[process]] = total_time;
                            break;//break from the time quantum loop
                        }
                    }//end process quantum for
                }
            }
        }while(!done);

        double waitingSum = 0;//waiting time sum
        double turnAroundSum = 0;//turn Around time sum
        for(int i = 0;  i < num_processes; i++){//add up the numbers
            waitingSum += timeWaited[i];
            turnAroundSum += turnAroundTime[i];
        }
        average_turnaround_time = turnAroundSum/(double)num_processes;
        average_wait_time = waitingSum/ (double)num_processes;

        for(int i = 0;  i < num_processes; i++){//add up the numbers
           printf("\nProcess[%d]\t\t\t%d\t\t\t %d\t%d\t\t%d\n", i,arrival_time[i],burst_time[i],turnAroundTime[i],timeWaited[i]);
        }
        
    }
    // Calculate & Print Average Wait and Turnaround Times
    printf("\n\nAverage Waiting Time:\t%f", average_wait_time);
    printf("\nAvg Turnaround Time:\t%f\n", average_turnaround_time);
    return 0;
}