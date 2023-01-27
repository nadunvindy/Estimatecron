#include "estimatecron.h"

struct crontab CRONTAB[20];

struct estimates ESTIMATES[20];

struct processess PROCESS[20];

int daysInMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int startOfMonth[12] = {6, 2, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};