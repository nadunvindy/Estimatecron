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
extern struct crontab CRONTAB[];

struct estimates
{
    char name[40];
    int minutes;
    int totCommands;
};
extern struct estimates ESTIMATES[];

struct processess
{
    int pid;
    int start_time;
    int end_time;
    char name[40];
};
extern struct processess PROCESS[];

extern int daysInMonth[];
extern int startOfMonth[];

void simulate(int);

extern bool isNumber(char[]);

extern int validateMinutes(char *);

extern int validateMinute(char *);

extern int validateHour(char *);

extern int validateDay(char *);

extern int validateMonthCrontab(char *);

extern int validateDayOfWeek(char *);

extern void trim_line(char[]);

extern void readCrontabFile(FILE *);

extern void readEstimatesFile(FILE *);

extern int validateMonth(char *);