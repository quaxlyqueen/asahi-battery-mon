#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

// Retrieve the current battery status
char * getBatteryStatus() {
    system("acpi -b > /tmp/battery.txt");

    FILE *fp = fopen("/tmp/battery.txt", "r");
    char line[256];

    char* batteryStatus = NULL;
    fgets(line, sizeof(line), fp);

    // Find "discharging" or "charging" in the line
    char* dischargingStr = strstr(line, "Discharging");
    char* chargingStr = strstr(line, "Charging");

    if (dischargingStr != NULL) batteryStatus = "Discharging";
    else if (chargingStr != NULL) batteryStatus = "Charging";
    else batteryStatus = "Unknown";

    fclose(fp);

    return batteryStatus;
}

// Retrieve the current battery percentage
int getBatteryPercentage() {
    system("acpi -b > /tmp/battery.txt");
        FILE *fp = fopen("/tmp/battery.txt", "r");
        char line[256];
        fgets(line, sizeof(line), fp);
        fclose(fp);

        char *token = strtok(line, ",");
        token = strtok(NULL, ",");
        char *percentage = strtok(token, "%");

    return atoi(percentage);
}

// Record the current date, time, and battery percentage
void recordData() {
    time_t now;
    struct tm *tm_info;
    time(&now);
    tm_info = localtime(&now);

    int batteryPercentage = getBatteryPercentage();
    char * batteryStatus = getBatteryStatus();

    // Create a string for date and time
    char datetime[50];
    strftime(datetime, sizeof(datetime), "%Y-%m-%d %H:%M:%S", tm_info);

    // Write the data to a file
    FILE *fp = fopen("/usr/local/etc/data.txt", "a");
    fprintf(fp, "%s, %d, %s\n", datetime, batteryPercentage, batteryStatus);
    fclose(fp);
}

void daemonize() {
    printf("Daemonizing...\n");

    // Daemonize the process
    pid_t pid, sid;
    pid = fork();

    if (pid < 0) {
        printf("daemonizing failed! pid: %d\n", pid);
        exit(EXIT_FAILURE);
    }

    // This is not needed. 
    if (pid > 0) {
        printf("daemonizing succeeded! pid: %d\n", pid);
        exit(EXIT_SUCCESS);
    }

    sid = setsid();

    if (sid < 0) {
        printf("daemonizing failed! sid: %d\n", sid);
        exit(EXIT_FAILURE);
    }

    if ((chdir("/")) < 0) {
        printf("daemonizing failed! dir not changed\n");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char * argv[]) {
    // Check if the argument is --daemonize
    if (argc > 1) {
        if ((strcmp(argv[1], "--daemonize") == 0) || (strcmp(argv[1], "-d") == 0))
            daemonize();
    } else {
        printf("Usage: %s [--daemonize|-d]\n", argv[0]);
        printf("recording data once.\n");
        recordData();
        exit(EXIT_FAILURE);
    }

    while (1) {
        recordData();

        // Sleep for 10 seconds
        sleep(60);
    }

    return 0;
}
