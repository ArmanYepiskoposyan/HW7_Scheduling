#include <stdio.h>

#define MAX 100

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int waiting_time;
    int turnaround_time;
    int response_time;
};

void printResults(struct Process p[], int n){

    double total_waiting = 0;
    double total_turnaround = 0;
    double total_response = 0;

    printf("\nPID\tAT\tBT\tWT\tTAT\tRT\n");

    for (int i = 0; i < n; i++){
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].arrival_time, p[i].burst_time,
               p[i].waiting_time, p[i].turnaround_time,
               p[i].response_time);

        total_waiting += p[i].waiting_time;
        total_turnaround += p[i].turnaround_time;
        total_response += p[i].response_time;
    }

    printf("\nAverage Waiting Time: %.2f\n", total_waiting / n);
    printf("Average Turnaround Time: %.2f\n", total_turnaround / n);
    printf("Average Response Time: %.2f\n", total_response / n);
}

void fcfs(struct Process p[], int n){

    int order[MAX];

    for (int i = 0; i < n; i++){
        order[i] = i;
    }

    for (int i = 0; i < n - 1; i++){
        for (int j = 0; j < n - i - 1; j++){

            if (p[order[j]].arrival_time > p[order[j+1]].arrival_time){
                int temp = order[j];
                order[j] = order[j+1];
                order[j+1] = temp;
            }
        }
    }

    int time = 0;

    printf("\nFirst Come First Served\n");
    printf("Gantt Chart: ");

    for (int i = 0; i < n; i++){

        int j = order[i];

        if (time < p[j].arrival_time){
            printf("Idle (%d-%d) ", time, p[j].arrival_time);
            time = p[j].arrival_time;
        }

        int start = time;

        p[j].waiting_time = time - p[j].arrival_time;
        p[j].response_time = p[j].waiting_time;

        time += p[j].burst_time;

        p[j].turnaround_time = time - p[j].arrival_time;

        printf("P%d (%d-%d) ", p[j].pid, start, time);
    }

    printf("\n");

    printResults(p, n);
}

void sjf(struct Process p[], int n){

    int completed[MAX] = {0};
    int count = 0;
    int time = 0;

    printf("\nShortest Job First\n");
    printf("Gantt Chart: ");

    while (count < n){

        int shortest = -1;

        for (int i = 0; i < n; i++){

            if (completed[i] == 0 && p[i].arrival_time <= time){

                if (shortest == -1 ||
                    p[i].burst_time < p[shortest].burst_time){

                    shortest = i;
                }
                else if (p[i].burst_time == p[shortest].burst_time &&
                         p[i].arrival_time < p[shortest].arrival_time){

                    shortest = i;
                }
            }
        }

        if (shortest == -1){

            int next = -1;

            for (int i = 0; i < n; i++){

                if (completed[i] == 0){

                    if (next == -1 ||
                        p[i].arrival_time < p[next].arrival_time){

                        next = i;
                    }
                }
            }

            printf("Idle (%d-%d) ", time, p[next].arrival_time);
            time = p[next].arrival_time;
        }
        else{

            int start = time;

            p[shortest].waiting_time = time - p[shortest].arrival_time;
            p[shortest].response_time = p[shortest].waiting_time;

            time += p[shortest].burst_time;

            p[shortest].turnaround_time =
                time - p[shortest].arrival_time;

            printf("P%d (%d-%d) ", p[shortest].pid, start, time);

            completed[shortest] = 1;
            count++;
        }
    }

    printf("\n");

    printResults(p, n);
}

int main(){

    struct Process p[MAX];
    int n;

    printf("Enter the number of processes: ");
    if (scanf("%d", &n) != 1 || n < 1 || n > MAX){
        printf("Invalid number of processes.\n");
        return 1;
    }

    for (int i = 0; i < n; i++){

        p[i].pid = i + 1;

        printf("Enter arrival time and burst time for process %d: ", i+1);

        if (scanf("%d %d", &p[i].arrival_time, &p[i].burst_time) != 2){
            printf("Invalid input.\n");
            return 1;
        }

        if (p[i].arrival_time < 0 || p[i].burst_time <= 0){
            printf("Invalid time values.\n");
            return 1;
        }
    }

    fcfs(p, n);
    sjf(p, n);

    return 0;
}
