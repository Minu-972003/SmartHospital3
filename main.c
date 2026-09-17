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
int queue[4] = {0};

int n = 0;

void registerPatient();
int findBed(int w);
void menu();
int waitTime(int s);
float surcharge(int s, int u);
float wardCost(int w, int d);
float grossTotal(int s, int u, int w, int d);

int main()
{
    printf("====================================\n");
    printf("       SMART HOSPITAL SYSTEM\n");
    printf("====================================\n");

    menu();

    return 0;
}

void menu()
{
    int choice;

    do
    {
        printf("\n========== MAIN MENU ==========\n");
        printf("1. Register Patient\n");
        printf("2. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                registerPatient();
                break;

            case 2:
                printf("\nThank you for using the system.\n");
                break;

            default:
                printf("\nInvalid choice.\n");
        }

    } while(choice != 2);
}

int waitTime(int s)
{
    return queue[s] * sptime[s];
}

float surcharge(int s, int u)
{
    if(u == 1)
    {
        return 0;
    }
    else if(u == 2)
    {
        return spfee[s] * 0.20;
    }
    else
    {
        return spfee[s] * 0.50;
    }
}

float wardCost(int w, int d)
{
    if(w == -1)
    {
        return 0;
    }

    return wrate[w] * d;
}

float grossTotal(int s, int u, int w, int d)
{
    return spfee[s] + surcharge(s, u) + wardCost(w, d);
}

int findBed(int w)
{
    int i;

    for(i = 0; i < wcap[w]; i++)
    {
        if(bed[w][i] == 0)
        {
            return i;
        }
    }

    return -1;
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

while(urgent[n] < 1 || urgent[n] > 3)
{
    printf("Invalid level. Enter 1, 2 or 3: ");
    scanf("%d", &urgent[n]);
}

    printf("\nSpecialties\n");

    for(int i = 0; i < 4; i++)
    {
        printf("%d. %s\n", i + 1, spname[i]);
    }

    printf("Enter specialty ID: ");
scanf("%d", &spec[n]);

while(spec[n] < 1 || spec[n] > 4)
{
    printf("Invalid specialty ID. Enter 1 to 4: ");
    scanf("%d", &spec[n]);
}

spec[n] = spec[n] - 1;

int wait = waitTime(spec[n]);

printf("Estimated waiting time: %d minutes\n", wait);

queue[spec[n]]++;

    printf("\nIs admitted to ward?\n");
printf("1. Yes\n");
printf("0. No\n");
printf("Enter choice: ");
scanf("%d", &admit[n]);

while(admit[n] != 0 && admit[n] != 1)
{
    printf("Invalid choice. Enter 1 or 0: ");
    scanf("%d", &admit[n]);
}

ward[n] = -1;
days[n] = 0;

if(admit[n] == 1)
{
    printf("\nWards\n");

    for(int i = 0; i < 4; i++)
    {
        printf("%d. %s\n", i + 1, wname[i]);
    }

    printf("Enter ward ID: ");
scanf("%d", &ward[n]);

while(ward[n] < 1 || ward[n] > 4)
{
    printf("Invalid ward ID. Enter 1 to 4: ");
    scanf("%d", &ward[n]);
}

ward[n] = ward[n] - 1;

    int b = findBed(ward[n]);

    if(b == -1)
    {
        printf("No bed available.\n");
        admit[n] = 0;
        ward[n] = -1;
    }
    else
    {
        printf("Enter number of days: ");
        scanf("%d", &days[n]);

        bed[ward[n]][b] = 1;

        printf("Bed %d assigned.\n", b + 1);
    }
}

    n++;

    printf("\nPatient registered successfully.\n");
}
