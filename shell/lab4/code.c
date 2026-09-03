#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    int size;
    int allocated;
    char pid[10];
} Block;

Block *blocks;
int blockCount;
int nextFitLast = 0;

typedef struct {
    int id;
    int size;
    int allocated;
    char pid[10];
} BuddyBlock;

BuddyBlock *buddy;
int buddyCount;
int buddyCap;

void initBlocks() {
    blockCount = 10;
    blocks = (Block*)malloc(blockCount * sizeof(Block));
    int sizes[10] = {100, 500, 200, 300, 600, 150, 250, 400, 350, 700};
    int allocFlag[10] = {1, 0, 1, 0, 0, 1, 0, 0, 1, 0};
    char *pids[10] = {"P0", "-", "P1", "-", "-", "P3", "-", "-", "P4", "-"};
    for (int i = 0; i < blockCount; i++) {
        blocks[i].id = i + 1;
        blocks[i].size = sizes[i];
        blocks[i].allocated = allocFlag[i];
        strcpy(blocks[i].pid, pids[i]);
    }
}

void displayBlocks() {
    printf("\nBlockID\tSize\tStatus\t\tProcessID\n");
    for (int i = 0; i < blockCount; i++) {
        printf("%d\t%d\t%s\t%s\n", blocks[i].id, blocks[i].size,
               blocks[i].allocated ? "Allocated" : "Free", blocks[i].pid);
    }
}

void firstFit(char *pid, int size) {
    for (int i = 0; i < blockCount; i++) {
        if (!blocks[i].allocated && blocks[i].size >= size) {
            blocks[i].allocated = 1;
            strcpy(blocks[i].pid, pid);
            printf("Process %s of size %d allocated to Block %d (Size %d) using First Fit\n",
                   pid, size, blocks[i].id, blocks[i].size);
            return;
        }
    }
    printf("Process %s of size %d could not be allocated (First Fit)\n", pid, size);
}

void bestFit(char *pid, int size) {
    int idx = -1;
    for (int i = 0; i < blockCount; i++) {
        if (!blocks[i].allocated && blocks[i].size >= size) {
            if (idx == -1 || blocks[i].size < blocks[idx].size) idx = i;
        }
    }
    if (idx != -1) {
        blocks[idx].allocated = 1;
        strcpy(blocks[idx].pid, pid);
        printf("Process %s of size %d allocated to Block %d (Size %d) using Best Fit\n",
               pid, size, blocks[idx].id, blocks[idx].size);
    } else {
        printf("Process %s of size %d could not be allocated (Best Fit)\n", pid, size);
    }
}

void worstFit(char *pid, int size) {
    int idx = -1;
    for (int i = 0; i < blockCount; i++) {
        if (!blocks[i].allocated && blocks[i].size >= size) {
            if (idx == -1 || blocks[i].size > blocks[idx].size) idx = i;
        }
    }
    if (idx != -1) {
        blocks[idx].allocated = 1;
        strcpy(blocks[idx].pid, pid);
        printf("Process %s of size %d allocated to Block %d (Size %d) using Worst Fit\n",
               pid, size, blocks[idx].id, blocks[idx].size);
    } else {
        printf("Process %s of size %d could not be allocated (Worst Fit)\n", pid, size);
    }
}

void nextFit(char *pid, int size) {
    for (int c = 0; c < blockCount; c++) {
        int i = (nextFitLast + c) % blockCount;
        if (!blocks[i].allocated && blocks[i].size >= size) {
            blocks[i].allocated = 1;
            strcpy(blocks[i].pid, pid);
            nextFitLast = (i + 1) % blockCount;
            printf("Process %s of size %d allocated to Block %d (Size %d) using Next Fit\n",
                   pid, size, blocks[i].id, blocks[i].size);
            return;
        }
    }
    printf("Process %s of size %d could not be allocated (Next Fit)\n", pid, size);
}

int nextPow2(int x) {
    int p = 1;
    while (p < x) p *= 2;
    return p;
}

void buddyInit() {
    buddyCap = 10;
    buddy = (BuddyBlock*)malloc(buddyCap * sizeof(BuddyBlock));
    buddyCount = 3;
    buddy[0].id = 1; buddy[0].size = 256; buddy[0].allocated = 1; strcpy(buddy[0].pid, "P0");
    buddy[1].id = 2; buddy[1].size = 256; buddy[1].allocated = 0; strcpy(buddy[1].pid, "-");
    buddy[2].id = 3; buddy[2].size = 512; buddy[2].allocated = 0; strcpy(buddy[2].pid, "-");
}

void buddyDisplay() {
    printf("\nBlockID\tSize\tStatus\t\tProcessID\n");
    for (int i = 0; i < buddyCount; i++) {
        printf("%d\t%d\t%s\t%s\n", buddy[i].id, buddy[i].size,
               buddy[i].allocated ? "Allocated" : "Free", buddy[i].pid);
    }
}

void buddyEnsureCap() {
    if (buddyCount >= buddyCap) {
        buddyCap *= 2;
        buddy = (BuddyBlock*)realloc(buddy, buddyCap * sizeof(BuddyBlock));
    }
}

void buddyAllocate(char *pid, int size) {
    int reqSize = nextPow2(size);
    int idx = -1;
    for (int i = 0; i < buddyCount; i++) {
        if (!buddy[i].allocated && buddy[i].size >= reqSize) {
            if (idx == -1 || buddy[i].size < buddy[idx].size) idx = i;
        }
    }
    if (idx == -1) {
        printf("Process %s of size %d could not be allocated (Buddy System)\n", pid, size);
        return;
    }
    while (buddy[idx].size / 2 >= reqSize) {
        int half = buddy[idx].size / 2;
        buddyEnsureCap();
        buddy[idx].size = half;
        buddy[buddyCount].id = buddyCount + 1;
        buddy[buddyCount].size = half;
        buddy[buddyCount].allocated = 0;
        strcpy(buddy[buddyCount].pid, "-");
        buddyCount++;
    }
    buddy[idx].allocated = 1;
    strcpy(buddy[idx].pid, pid);
    printf("Process %s of size %d allocated to Block %d (Size %d) using Buddy System\n",
           pid, size, buddy[idx].id, buddy[idx].size);
}

int main() {
    initBlocks();
    buddyInit();
    int choice;
    char pid[10];
    int size;

    printf("Base Partition Table (Initial State):\n");
    displayBlocks();
    printf("\nBase Buddy System Table (Initial State):\n");
    buddyDisplay();

    while (1) {
        printf("\n--- Memory Allocation Menu ---\n");
        printf("1. First Fit\n2. Best Fit\n3. Worst Fit\n4. Next Fit\n");
        printf("5. Buddy System\n6. Display Partition Table\n7. Display Buddy Table\n8. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 8) break;

        if (choice == 6) {
            displayBlocks();
            continue;
        }
        if (choice == 7) {
            buddyDisplay();
            continue;
        }

        if (choice >= 1 && choice <= 5) {
            printf("Enter Process ID: ");
            scanf("%s", pid);
            printf("Enter Process Size: ");
            scanf("%d", &size);
        }

        switch (choice) {
            case 1: firstFit(pid, size); displayBlocks(); break;
            case 2: bestFit(pid, size); displayBlocks(); break;
            case 3: worstFit(pid, size); displayBlocks(); break;
            case 4: nextFit(pid, size); displayBlocks(); break;
            case 5: buddyAllocate(pid, size); buddyDisplay(); break;
            default: printf("Invalid choice\n");
        }
    }

    free(blocks);
    free(buddy);
    printf("Memory freed. Program exited.\n");
    return 0;
}
