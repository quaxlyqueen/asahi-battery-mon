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
    FILE *fp = fopen("/tmp/data.txt", "a");
    fprintf(fp, "%s, %d, %s\n", datetime, batteryPercentage, batteryStatus);
    fclose(fp);
}

int main() {
    // Daemonize the process
    pid_t pid, sid;
    pid = fork();
    if (pid < 0) exit(EXIT_FAILURE);
    if (pid > 0) exit(EXIT_SUCCESS);

    sid = setsid();

    if (sid < 0) exit(EXIT_FAILURE);
    if ((chdir("/")) < 0) exit(EXIT_FAILURE);

    while (1) {
        recordData();

        // Sleep for 10 seconds
        sleep(60);
    }

    return 0;
}
