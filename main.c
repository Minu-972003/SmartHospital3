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

float patientTotal[MAX];
float patientDiscount[MAX];

int queue[4] = {0};

int n = 0;

void registerPatient();
int findBed(int w);
void menu();
int waitTime(int s);
float surcharge(int s, int u);
float wardCost(int w, int d);
float grossTotal(int s, int u, int w, int d);
float discount(float total, int a);
float finalAmount(float total, float disc);
void bedStatus();
void priorityList();
void reports();
void urgencyReport();
void moneyReport();
void bedReport();
void highestPatient();

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
        printf("2. View Bed Status\n");
        printf("3. View Patient Priority List\n");
        printf("4. View Reports\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
               registerPatient();
               break;

            case 2:
               bedStatus();
               break;

            case 3:
               priorityList();
               break;

            case 4:
               reports();
               break;

            case 5:
                printf("\nThank you for using the system.\n");
                break;

            default:
               printf("\nInvalid option. Please enter a valid option.\n");
        }

    } while(choice != 5);
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

float discount(float total, int a)
{
    if(a < 5 || a > 65)
    {
        return total * 0.15;
    }

    return 0;
}

float finalAmount(float total, float disc)
{
    return total - disc;
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

void bedStatus()
{
    int i;
    int j;

    printf("\n========== BED STATUS ==========\n");

    for(i = 0; i < 4; i++)
    {
        printf("\n%s\n", wname[i]);

        for(j = 0; j < wcap[i]; j++)
        {
            if(bed[i][j] == 0)
            {
                printf("Bed %d: Available\n", j + 1);
            }
            else
            {
                printf("Bed %d: Occupied\n", j + 1);
            }
        }
    }
}

void priorityList()
{
    int order[MAX];
    int i;
    int j;
    int temp;
    int min;

    for(i = 0; i < n; i++)
    {
        order[i] = i;
    }

    for(i = 0; i < n - 1; i++)
    {
        min = i;

        for(j = i + 1; j < n; j++)
        {
            if(urgent[order[j]] > urgent[order[min]])
            {
                min = j;
            }
        }

        if(min != i)
        {
            temp = order[i];
            order[i] = order[min];
            order[min] = temp;
        }
    }

    printf("\n========== PATIENT PRIORITY LIST ==========\n");

    for(i = 0; i < n; i++)
    {
        printf("%d. %s - Level %d\n",
               i + 1, pname[order[i]], urgent[order[i]]);
    }
}

void reports()
{
    printf("\n========== HOSPITAL REPORTS ==========\n");

    urgencyReport();
    moneyReport();
    bedReport();
    highestPatient();
}

void moneyReport()
{
    float revenue = 0;
    float discounts = 0;
    int i;

    for(i = 0; i < n; i++)
    {
        revenue = revenue + patientTotal[i];
        discounts = discounts + patientDiscount[i];
    }

    printf("\nTotal Revenue: LKR %.2f\n", revenue);
    printf("Total Discounts: LKR %.2f\n", discounts);
}

void bedReport()
{
    int i;
    int j;
    int occupied;
    float percent;

    printf("\nBed Occupancy Report\n");

    for(i = 0; i < 4; i++)
    {
        occupied = 0;

        for(j = 0; j < wcap[i]; j++)
        {
            if(bed[i][j] == 1)
            {
                occupied++;
            }
        }

        percent = (occupied * 100.0) / wcap[i];

        printf("%s: %d/%d beds occupied (%.2f%%)\n",
               wname[i], occupied, wcap[i], percent);
    }
}

void highestPatient()
{
    int i;
    int highest;

    if(n == 0)
    {
        printf("\nNo patients registered yet.\n");
        return;
    }

    highest = 0;

    for(i = 1; i < n; i++)
    {
        if(patientTotal[i] > patientTotal[highest])
        {
            highest = i;
        }
    }

    printf("\nHighest-Paying Patient\n");
    printf("Patient Name: %s\n", pname[highest]);
    printf("Final Payable Amount: LKR %.2f\n", patientTotal[highest]);
}

void urgencyReport()
{
    int normal = 0;
    int urgentCount = 0;
    int critical = 0;
    int i;

    for(i = 0; i < n; i++)
    {
        if(urgent[i] == 1)
        {
            normal++;
        }
        else if(urgent[i] == 2)
        {
            urgentCount++;
        }
        else if(urgent[i] == 3)
        {
            critical++;
        }
    }

    printf("\nPatient Count by Urgency Level\n");
    printf("Normal: %d\n", normal);
    printf("Urgent: %d\n", urgentCount);
    printf("Critical: %d\n", critical);
}

void registerPatient()
{
    float sur;
    float wc;
    float total;
    float disc;
    float final;

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

    sur = surcharge(spec[n], urgent[n]);
    wc = wardCost(ward[n], days[n]);
    total = grossTotal(spec[n], urgent[n], ward[n], days[n]);
    disc = discount(total, age[n]);
    final = finalAmount(total, disc);

    patientTotal[n] = final;
    patientDiscount[n] = disc;

    printf("\n========== PATIENT BILL ==========\n");
printf("Patient Name: %s\n", pname[n]);
printf("Age: %d\n", age[n]);
printf("Specialty: %s\n", spname[spec[n]]);
printf("Urgency Level: %d\n", urgent[n]);

printf("\nBase Consultation Fee: LKR %.2f\n", spfee[spec[n]]);
printf("Emergency Surcharge: LKR %.2f\n", sur);
printf("Ward Stay Cost: LKR %.2f\n", wc);
printf("Gross Total: LKR %.2f\n", total);
printf("Age Subsidy Discount: LKR %.2f\n", disc);
printf("Final Payable Amount: LKR %.2f\n", final);
printf("Estimated Waiting Time: %d minutes\n", wait);

printf("==================================\n");

    n++;

    printf("\nPatient registered successfully.\n");
}
