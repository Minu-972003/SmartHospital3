#include <stdio.h>

char spname[4][30] = {
    "General Practice (OPD)",
    "Paediatrics",
    "Cardiology",
    "Neurology"
};

float spfee[4] = {1500, 2500, 4500, 5000};

int sptime[4] = {15, 20, 30, 30};

int spcap[4] = {30, 20, 12, 10};

char wname[4][30] = {
    "General Ward",
    "Paediatric Ward",
    "Surgical Ward",
    "ICU"
};

float wrate[4] = {3000, 6000, 12000, 25000};

int wcap[4] = {20, 10, 10, 5};

int main()
{
    printf("====================================\n");
    printf("       SMART HOSPITAL SYSTEM\n");
    printf("====================================\n");

    printf("Hospital system started successfully.\n");

    return 0;
}
