#include <sys/statvfs.h>
#include <linux/limits.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define PATH_LEN_MAX    128
#define BYTES_IN_1K     1024
#define KB_BLOCK_IN_1G  (1024*1024)
#define SEC_IN_ONE_MIN  60
#define MIN_IN_ONE_HR   60

void get_ram_info(void);
void get_hdd_info(char *path);
void get_free_cpu(void);
void get_uptime(void);

int main( int argc, char *argv[] )
{
    /** API to print free RAM info */
    get_ram_info();

    /** API to print total, free and used HDD/flash info*/
    get_hdd_info("/");

    /** API to print free and used CPU total */
    get_free_cpu();

    /** API to print uptime of system. */
    get_uptime();
}

void get_ram_info(void)
{
    FILE *fp = NULL;
    char data[100];
    char str[100];
    unsigned long int freeSize;

    fp = fopen("/proc/meminfo", "r");
    if(fp == NULL)
    {
        printf("failed to open meminfo file\n");
        return;
    }

    char *ptr = NULL;
    while(fgets(data, 100, fp))
    {
        if((ptr = strstr(data, "MemFree")) != NULL)
        {
            break;
        }
    }

    sscanf(data, "%s %lu", str, &freeSize);
    printf("RAM Free Size:[%lu kB]\n", freeSize);
    fclose(fp);
}

void get_hdd_info(char *path)
{
    struct statvfs fiData;
    char fnPath[PATH_LEN_MAX];
    unsigned char blockSizeInKb;
    double totalSize, freeSize, usedSize;
    float totalSizeGb, freeSizeGb, usedSizeGb;

    if(path == NULL)
    {
        printf("Invld path received");
        return;
    }

    snprintf(fnPath, PATH_LEN_MAX, "%s", path);

    if((statvfs(fnPath,&fiData)) < 0 )
    {
        printf("Failed to stat %s:\n", fnPath);
    }
    else
    {
        blockSizeInKb = fiData.f_bsize/BYTES_IN_1K;
        totalSize = fiData.f_blocks*blockSizeInKb;
        freeSize = fiData.f_bfree*blockSizeInKb;
        usedSize = totalSize - freeSize;

        totalSizeGb = (float)(totalSize/KB_BLOCK_IN_1G);
        freeSizeGb = (float)((freeSize/KB_BLOCK_IN_1G) - (totalSizeGb*5/100));
        usedSizeGb = (float)(usedSize/KB_BLOCK_IN_1G);

        printf("Disk Total:[%.2fGB], Free:[%.2fGB], Used[%.2fGB]\n", totalSizeGb, freeSizeGb, usedSizeGb);
    }
}

void get_free_cpu(void)
{
    FILE *fp;
    float freeCpu;
    system("top -d 1 -n 1 | head -3 | tail -1 | awk '{ print $8 }' > ./a.txt");
    fp = fopen("./a.txt", "r");
    if(fp == NULL)
    {
        printf("Failed to open file:[%s]\n", strerror(errno));
        return;
    }

    fscanf(fp, "%f", &freeCpu);
    printf("FreeCpu:%.2f , UsedCpu:%.2f\n", freeCpu, (100.0-freeCpu));
    fclose(fp);
    remove("./a.txt");
}

void get_uptime(void)
{
    FILE *fp;
    float timeInSec;
    int   totalMin, upHr, upMin;
    fp=fopen("/proc/uptime", "r");
    if(NULL == fp)
    {
        printf("Failed to open file in %s:%s\n", __func__, strerror(errno));
        return;
    }

    fscanf(fp, "%f", &timeInSec);
    fclose(fp);

    totalMin = timeInSec/SEC_IN_ONE_MIN;
    upHr = totalMin/MIN_IN_ONE_HR;
    upMin = (totalMin - (upHr*MIN_IN_ONE_HR));
    printf("Uptime:[%dh %dm]\n", upHr, upMin);
}
