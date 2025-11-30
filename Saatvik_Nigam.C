#include <stdio.h>
#include <stdlib.h>
#include <string.h>



typedef struct {
    char name[50];
    char blood_type[5];
    char last_donation_date[15];
    int available_units;
} Donor;

typedef struct {
    char name[50];
    char blood_type[5];
    int required_units;
    int fulfilled;     // 1 = fulfilled, 0 = pending
} Recipient;


int isCompatible(char donor_bt[], char recipient_bt[]);
void allocateUnits(Donor *donors, int dcount, Recipient *recipients, int rcount);
void generateSummary(Donor *donors, int dcount, Recipient *recipients, int rcount);


int isCompatible(char donor_bt[], char recipient_bt[]) {
    if (strcmp(donor_bt, "O-") == 0) return 1;
    if (strcmp(donor_bt, "O+") == 0 && 
       (strcmp(recipient_bt, "O+") == 0 || strcmp(recipient_bt, "A+") == 0 ||
        strcmp(recipient_bt, "B+") == 0 || strcmp(recipient_bt, "AB+") == 0))
        return 1;

    if (strcmp(donor_bt, "A-") == 0 && 
       (strcmp(recipient_bt, "A-") == 0 || strcmp(recipient_bt, "A+") == 0 || 
        strcmp(recipient_bt, "AB-") == 0 || strcmp(recipient_bt, "AB+") == 0))
        return 1;

    if (strcmp(donor_bt, "A+") == 0 && 
       (strcmp(recipient_bt, "A+") == 0 || strcmp(recipient_bt, "AB+") == 0))
        return 1;

    if (strcmp(donor_bt, "B-") == 0 && 
       (strcmp(recipient_bt, "B-") == 0 || strcmp(recipient_bt, "B+") == 0 || 
        strcmp(recipient_bt, "AB-") == 0 || strcmp(recipient_bt, "AB+") == 0))
        return 1;

    if (strcmp(donor_bt, "B+") == 0 && 
       (strcmp(recipient_bt, "B+") == 0 || strcmp(recipient_bt, "AB+") == 0))
        return 1;

    if (strcmp(donor_bt, "AB-") == 0 && 
       (strcmp(recipient_bt, "AB-") == 0 || strcmp(recipient_bt, "AB+") == 0))
        return 1;

    if (strcmp(donor_bt, "AB+") == 0 && strcmp(recipient_bt, "AB+") == 0)
        return 1;

    return 0;
}



void allocateUnits(Donor *donors, int dcount, Recipient *recipients, int rcount) {
    for (int i = 0; i < rcount; i++) {
        int needed = recipients[i].required_units;

        for (int j = 0; j < dcount && needed > 0; j++) {
            if (donors[j].available_units > 0 &&
                isCompatible(donors[j].blood_type, recipients[i].blood_type)) {

                int transferred = (donors[j].available_units >= needed)
                                  ? needed : donors[j].available_units;

                donors[j].available_units -= transferred;
                needed -= transferred;
            }
        }

        recipients[i].fulfilled = (needed == 0) ? 1 : 0;
    }
}



void generateSummary(Donor *donors, int dcount, Recipient *recipients, int rcount) {
    printf("\n--- DAILY SUMMARY ---\n");
    printf("\nAvailable Units by Blood Group:\n");

    char groups[8][5] = {"O-","O+","A-","A+","B-","B+","AB-","AB+"};
    int units[8] = {0};

    for (int i = 0; i < dcount; i++) {
        for (int g = 0; g < 8; g++) {
            if (strcmp(donors[i].blood_type, groups[g]) == 0) {
                units[g] += donors[i].available_units;
                break;
            }
        }
    }

    for (int g = 0; g < 8; g++)
        printf("%s : %d units\n", groups[g], units[g]);

    printf("\nRequest Status:\n");
    for (int i = 0; i < rcount; i++) {
        printf("Recipient %s (%s): %s\n",
               recipients[i].name, recipients[i].blood_type,
               recipients[i].fulfilled ? "Fulfilled" : "Pending");
    }
}



int main() {
    int dcount, rcount;

    printf("Enter number of donors: ");
    scanf("%d", &dcount);

    Donor donors = (Donor) malloc(dcount * sizeof(Donor));

    for (int i = 0; i < dcount; i++) {
        printf("\n--- Donor %d ---\n", i+1);
        printf("Name: ");
        scanf("%s", donors[i].name);
        printf("Blood Type (O-,O+,A-,A+,B-,B+,AB-,AB+): ");
        scanf("%s", donors[i].blood_type);
        printf("Last Donation Date (DD/MM/YYYY): ");
        scanf("%s", donors[i].last_donation_date);
        printf("Available Units: ");
        scanf("%d", &donors[i].available_units);
    }

    printf("\nEnter number of recipients: ");
    scanf("%d", &rcount);

    Recipient recipients = (Recipient) malloc(rcount * sizeof(Recipient));

    for (int i = 0; i < rcount; i++) {
        printf("\n--- Recipient %d ---\n", i+1);
        printf("Name: ");
        scanf("%s", recipients[i].name);
        printf("Blood Type: ");
        scanf("%s", recipients[i].blood_type);
        printf("Required Units: ");
        scanf("%d", &recipients[i].required_units);
        recipients[i].fulfilled = 0;
    }

    allocateUnits(donors, dcount, recipients, rcount);

    generateSummary(donors, dcount, recipients, rcount);

    free(donors);
    free(recipients);

    return 0;
}