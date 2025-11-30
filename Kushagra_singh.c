#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ---------------------- Structures ---------------------------

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
    int allocated_units;
} Recipient;

// ---------------- Blood Compatibility Logic -------------------

int is_compatible(char donor[], char recipient[]) {
    // Universal donor logic
    if (strcmp(donor, "O-") == 0) return 1;

    // Same type
    if (strcmp(donor, recipient) == 0) return 1;

    // O+ → all positive
    if (strcmp(donor, "O+") == 0 &&
       (strcmp(recipient + strlen(recipient) - 1, "+") == 0))
        return 1;

    // A- → A-, A+
    if (strcmp(donor, "A-") == 0 &&
       (recipient[0] == 'A'))
        return 1;

    // A+ → A+
    if (strcmp(donor, "A+") == 0 &&
        strcmp(recipient, "A+") == 0)
        return 1;

    // B- → B-, B+
    if (strcmp(donor, "B-") == 0 &&
       (recipient[0] == 'B'))
        return 1;

    // B+ → B+
    if (strcmp(donor, "B+") == 0 &&
        strcmp(recipient, "B+") == 0)
        return 1;

    // AB- → AB-, AB+
    if (strcmp(donor, "AB-") == 0 &&
        (recipient[0] == 'A' && recipient[1] == 'B'))
        return 1;

    // AB+ receives from all types
    if (strcmp(recipient, "AB+") == 0)
        return 1;

    return 0;
}

// -------------------- Main Program ---------------------------

int main() {
    int d, r;

    printf("Enter number of donors: ");
    scanf("%d", &d);

    Donor *donors = (Donor*) malloc(d * sizeof(Donor));

    printf("\n--- Enter Donor Details ---\n");
    for (int i = 0; i < d; i++) {
        printf("\nDonor %d:\n", i + 1);

        printf("Name: ");
        scanf("%s", donors[i].name);

        printf("Blood Group: ");
        scanf("%s", donors[i].blood_type);

        printf("Last Donation Date (YYYY-MM-DD): ");
        scanf("%s", donors[i].last_donation_date);

        printf("Available Units: ");
        scanf("%d", &donors[i].available_units);
    }

    printf("\n-------------------------------------\n");

    printf("Enter number of recipients: ");
    scanf("%d", &r);

    Recipient *recipients = (Recipient*) malloc(r * sizeof(Recipient));

    printf("\n--- Enter Recipient Details ---\n");
    for (int i = 0; i < r; i++) {
        printf("\nRecipient %d:\n", i + 1);

        printf("Name: ");
        scanf("%s", recipients[i].name);

        printf("Blood Group: ");
        scanf("%s", recipients[i].blood_type);

        printf("Required Units: ");
        scanf("%d", &recipients[i].required_units);

        recipients[i].allocated_units = 0;
    }

    printf("\n-------------------------------------\n");
    printf("Checking Compatibility & Allocating Blood...\n");
    printf("---------------------------------------------\n");

    // Allocation Logic
    for (int i = 0; i < r; i++) {
        printf("\nRecipient: %s (%s)\n", recipients[i].name, recipients[i].blood_type);
        printf("Allocating units...\n");

        int needed = recipients[i].required_units;

        for (int j = 0; j < d && needed > 0; j++) {
            if (donors[j].available_units > 0 &&
                is_compatible(donors[j].blood_type, recipients[i].blood_type)) {

                int allocated = (donors[j].available_units >= needed)
                                ? needed
                                : donors[j].available_units;

                donors[j].available_units -= allocated;
                recipients[i].allocated_units += allocated;
                needed -= allocated;

                printf("  Donor %s (%s) → %d units allocated\n",
                       donors[j].name, donors[j].blood_type, allocated);
            }
        }

        if (needed == 0)
            printf("Status: ✔ Request Fulfilled\n");
        else
            printf("Status: ✖ Pending (%d units not allocated)\n", needed);

        printf("-------------------------------------\n");
    }

    // ---------------- Daily Summary -----------------
    printf("\n********** DAILY SUMMARY **********\n");

    printf("\nAvailable Units After Allocation:\n");
    for (int i = 0; i < d; i++) {
        printf("%s : %d units remaining\n",
               donors[i].blood_type, donors[i].available_units);
    }

    printf("\nFulfilled Requests:\n");
    for (int i = 0; i < r; i++) {
        if (recipients[i].allocated_units == recipients[i].required_units)
            printf(" - %s (%s) → %d units provided\n",
                recipients[i].name, recipients[i].blood_type, recipients[i].allocated_units);
    }

    printf("\nPending Requests:\n");
    int pendingFlag = 0;
    for (int i = 0; i < r; i++) {
        if (recipients[i].allocated_units < recipients[i].required_units) {
            int pending = recipients[i].required_units - recipients[i].allocated_units;
            printf(" - %s (%s) → %d units pending\n",
                    recipients[i].name, recipients[i].blood_type, pending);
            pendingFlag = 1;
        }
    }

    if (!pendingFlag) printf("None\n");

    printf("\n===============================================\n");

    // Free Memory
    free(donors);
    free(recipients);

    return 0;
}
