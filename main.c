#include <stdio.h>
#define MAX 100

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

int bed[4][20] = {0};

char pname[MAX][50];
int age[MAX];
int urgent[MAX];
int spec[MAX];
int admit[MAX];
int ward[MAX];
int days[MAX];

int n = 0;

void registerPatient();

int main()
{
    printf("====================================\n");
    printf("       SMART HOSPITAL SYSTEM\n");
    printf("====================================\n");

    registerPatient();

    return 0;
}

void registerPatient()
{
    printf("\n========== PATIENT REGISTRATION ==========\n");

    printf("Enter patient name: ");
    scanf(" %[^\n]", pname[n]);

    printf("Enter age: ");
    scanf("%d", &age[n]);

    printf("\nEmergency Level\n");
    printf("1. Normal\n");
    printf("2. Urgent\n");
    printf("3. Critical\n");
    printf("Enter level: ");
    scanf("%d", &urgent[n]);

    printf("\nSpecialties\n");

    for(int i = 0; i < 4; i++)
    {
        printf("%d. %s\n", i + 1, spname[i]);
    }

    printf("Enter specialty ID: ");
    scanf("%d", &spec[n]);

    spec[n] = spec[n] - 1;

    n++;

    printf("\nPatient registered successfully.\n");
}
