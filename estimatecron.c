#include "estimatecron.h"

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
