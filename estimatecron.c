#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

struct crontab
{
    int minute;
    int hour;
    int day;
    int month;
    int dayOfWeek;
    char name[40];
};
struct crontab CRONTAB[20];

struct estimates
{
    char name[40];
    int minutes;
    int totCommands;
};
struct estimates ESTIMATES[20];

struct processess
{
    int pid;
    int start_time;
    int end_time;
    char name[40];
};
struct processess PROCESS[20];

int daysInMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int startOfMonth[12] = {6, 2, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};

void simulate(int month)
{
    int totalCommandCount = 0;
    int maxAnytimeCount = 0;
    int realTimeCount = 0;
    int days = daysInMonth[month];
    int startTime = 0;
    int endTime = 0;
    char processName[40];
    int currentDay = startOfMonth[month];

    for (int day = 1; day < days; day++)
    {
        for (int hour = 0; hour < 24; hour++)
        {
            for (int minute = 0; minute < 60; minute++)
            {
                int time = ((day - 1) * 24 * 60) + (hour * 60) + minute;
                for (int i = 0; i < 20; i++)
                {
                    if ((CRONTAB[i].minute == minute || CRONTAB[i].minute == -1) && (CRONTAB[i].hour == hour || CRONTAB[i].hour == -1) && (CRONTAB[i].day == day || CRONTAB[i].day == -1) && (CRONTAB[i].dayOfWeek == currentDay || CRONTAB[i].dayOfWeek == -1) && (CRONTAB[i].month == month || CRONTAB[i].month == -1))
                    {
                        strcpy(processName, CRONTAB[i].name);
                        startTime = time;
                        realTimeCount++;
                        totalCommandCount++;
                        int pindex = 0;

                        for (int k = 0; k < 20; k++)
                        {
                            if (PROCESS[k].end_time == 0)
                            {

                                PROCESS[k].start_time = time;
                                PROCESS[k].pid = k;
                                strcpy(PROCESS[k].name, processName);
                                pindex = k;
                                break;
                            }
                        }

                        for (int j = 0; j < 20; j++)
                        {
                            if (strcmp(ESTIMATES[j].name, CRONTAB[i].name) == 0)
                            {
                                PROCESS[pindex].end_time = startTime + ESTIMATES[j].minutes;
                                if (endTime > days * 24 * 60)
                                {
                                    endTime = (days * 24 * 60) - 1;
                                }
                                ESTIMATES[j].totCommands++;
                            }
                        }
                    }
                    for (int k = 0; k < 20; k++)
                    {
                        if (PROCESS[k].end_time == time && PROCESS[k].end_time != 0)
                        {

                            PROCESS[k].end_time = 0;
                            realTimeCount--;
                        }
                    }
                }
                if (realTimeCount > maxAnytimeCount)
                {
                    maxAnytimeCount = realTimeCount;
                }
            }
        }
        if (currentDay == 6)
        {
            currentDay = 0;
        }
        else
        {
            currentDay++;
        }
    }

    int mostCommand = 0;
    char mostCommandname[40];
    for (int i = 0; i < 20; i++)
    {
        if (ESTIMATES[i].totCommands > mostCommand)
        {
            mostCommand = ESTIMATES[i].totCommands;
            strcpy(mostCommandname, ESTIMATES[i].name);
        }
    }

    printf("Maximum number of commands at anytime: %d | Total number of commands invoked: %d | Most invoked command was: %s which was invoked %d times\n", maxAnytimeCount, totalCommandCount, mostCommandname, mostCommand);
}

bool isNumber(char number[])
{
    int i = 0;

    // checking for negative numbers
    if (number[0] == '-')
        i = 1;
    for (; number[i] != 0; i++)
    {
        // if (number[i] > '9' || number[i] < '0')
        if (!isdigit(number[i]))
            return false;
    }
    return true;
}

int validateMinutes(char *minutes) // Validate the number of minutes in the estimates-file
{
    for (int i = 0; i < strlen(minutes); i++)
    {
        if (isdigit(minutes[i]) == 0)
        {
            printf("Invalid crontabfile contents\n");
            exit(EXIT_FAILURE);
        }
    }
    return atoi(minutes);
}

int validateMinute(char *minute)
{
    if (strcmp(minute, "*") == 0)
    {
        return -1;
    }

    else if (atoi(minute) < 0 || atoi(minute) > 59)
    {
        printf("Invalid crontabfile contents\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        for (int i = 0; i < strlen(minute); i++)
        {
            if (isdigit(minute[i]) == 0)
            {
                printf("Invalid crontabfile contents\n");
                exit(EXIT_FAILURE);
            }
        }
        return atoi(minute);
    }
}

int validateHour(char *hour)
{
    if (strcmp(hour, "*") == 0)
    {
        return -1;
    }

    else if (atoi(hour) < 1 || atoi(hour) > 23)
    {
        printf("Invalid crontabfile contents\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        for (int i = 0; i < strlen(hour); i++)
        {
            if (isdigit(hour[i]) == 0)
            {
                printf("Invalid crontabfile contents\n");
                exit(EXIT_FAILURE);
            }
        }
        return atoi(hour);
    }
}

int validateDay(char *day)
{

    if (strcmp(day, "*") == 0)
    {
        return -1;
    }

    else if (atoi(day) < 1 || atoi(day) > 31)
    {
        printf("Invalid crontabfile contents\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        for (int i = 0; i < strlen(day); i++)
        {
            if (isdigit(day[i]) == 0)
            {
                printf("Invalid crontabfile contents\n");
                exit(EXIT_FAILURE);
            }
        }
        return atoi(day);
    }
}

int validateMonthCrontab(char *month)
{
    int m = -2;

    if (strcmp(month, "*") == 0)
    {
        m = -1;
        return m;
    }

    if (isNumber(month) == false)
    {
        const char *a[12] = {"jan", "feb", "mar", "apr", "may", "jun", "jul", "aug", "sep", "oct", "nov", "dec"};
        for (int i = 0; i < 12; i++)
        {
            if (strcmp(month, a[i]) == 0)
            {
                m = i;
            }
        }
        if (m >= 0 && m <= 11)
        {
            return m;
        }
        else
        {
            printf("Invalid month entered\n");
            exit(EXIT_FAILURE);
        }
    }

    else if (isNumber(month) == true && atoi(month) >= 0 && atoi(month) <= 11)
    {
        m = atoi(month);
        return m;
    }

    else if (m == -2)
    {
        printf("Invalid month entered\n");
        exit(EXIT_FAILURE);
    }
    return m;
}

int validateDayOfWeek(char *dOW)
{
    int m = -2;

    if (strcmp(dOW, "*") == 0)
    {
        m = -1;
        return m;
    }
    else
    {
        const char *a[7] = {"sun", "mon", "tue", "wed", "thu", "fri", "sat"};
        for (int i = 0; i < 7; i++)
        {
            if (strcmp(dOW, a[i]) == 0)
            {
                m = i;
            }
        }
        if (m > 0 && m < 32)
        {
            return m;
        }
    }
    if (atoi(dOW) >= 0 && atoi(dOW) <= 6)
    {
        m = atoi(dOW);
        return m;
    }
    else if (m == -2)
    {
        printf("Invalid month found in Crontab-file\n");
        exit(EXIT_FAILURE);
    }
    return m;
}

void trim_line(char line[])
{
    int i = 0;
    while (line[i] != '\0')
    {

        if (line[i] == '\r' || line[i] == '\n')
        {
            line[i] = '\0';
            break;
        }

        i = i + 1;
    }
}

void readCrontabFile(FILE *crontab)
{
    char line[BUFSIZ];
    int cronCount = 0;
    while (fgets(line, sizeof line, crontab) != NULL)
    {
        if (line[0] == '#')
        {
            continue;
        }
        trim_line(line);
        char *token = strtok(line, " ");
        int j = 0;
        while (token != NULL)
        {
            if (j == 0)
            {
                int minute = validateMinute(token);
                CRONTAB[cronCount].minute = minute;
            }
            else if (j == 1)
            {
                int hour = validateHour(token);
                CRONTAB[cronCount].hour = hour;
            }
            else if (j == 2)
            {
                int day = validateDay(token);
                CRONTAB[cronCount].day = day;
            }
            else if (j == 3)
            {
                int month = validateMonthCrontab(token);
                CRONTAB[cronCount].month = month;
            }
            else if (j == 4)
            {
                int dayOfWeek = validateDayOfWeek(token);
                CRONTAB[cronCount].dayOfWeek = dayOfWeek;
            }
            else if (j == 5)
            {
                strcpy(CRONTAB[cronCount].name, token);
            }

            token = strtok(NULL, " ");
            j++;
        }
        cronCount++;
    }
}

void readEstimatesFile(FILE *estimates)
{
    char line[BUFSIZ];
    int estCount = 0;
    while (fgets(line, sizeof line, estimates) != NULL)
    {

        if (line[0] == '#')
        {
            continue;
        }
        trim_line(line);
        char *token = strtok(line, " ");
        int j = 0;
        while (token != NULL)
        {
            if (j == 0)
            {
                strcpy(ESTIMATES[estCount].name, token);
            }
            else if (j == 1)
            {
                int minutes = validateMinutes(token);
                ESTIMATES[estCount].minutes = minutes;
            }
            token = strtok(NULL, " ");
            j++;
        }
        estCount++;
    }
}

int validateMonth(char *month)
{
    int m = -2;

    if (isNumber(month) == false)
    {
        const char *a[12] = {"jan", "feb", "mar", "apr", "may", "jun", "jul", "aug", "sep", "oct", "nov", "dec"};
        for (int i = 0; i < 12; i++)
        {
            if (strcmp(month, a[i]) == 0)
            {
                m = i;
            }
        }
        if (m >= 0 && m <= 11)
        {
            return m;
        }
        else
        {
            printf("Invalid month entered\n");
            exit(EXIT_FAILURE);
        }
    }

    else if (isNumber(month) == true && atoi(month) >= 0 && atoi(month) <= 11)
    {
        m = atoi(month);
        return m;
    }

    else if (m == -2)
    {
        printf("Invalid month entered\n");
        exit(EXIT_FAILURE);
    }
    return m;
}

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        printf("Invalid number of arguments\n");
        exit(EXIT_FAILURE);
    }
    int month = validateMonth(argv[1]);
    FILE *crontabFile = fopen(argv[2], "r");
    FILE *estimateFile = fopen(argv[3], "r");
    if (crontabFile == NULL)
    {
        printf("Cannot open crontab-file");
        exit(EXIT_FAILURE);
    }
    else if (estimateFile == NULL)
    {
        printf("Cannot open the estimates-file");
        exit(EXIT_FAILURE);
    }
    else
    {
        readCrontabFile(crontabFile);
        readEstimatesFile(estimateFile);

        simulate(month);
    }
}
