#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ROOMS 200
#define MAX_RESERVATIONS 1000
#define STRLEN 128

typedef struct {
    int id;
    char type[32];
    int capacity;
    double price;
    int active; 
} Room;

typedef struct {
    int id;
    int roomId;
    char guestName[STRLEN];
    int guests;
    char checkin[11];  
    char checkout[11]; 
    int active; 
} Reservation;


static Room rooms[MAX_ROOMS];
static int roomCount = 0;
static Reservation reservations[MAX_RESERVATIONS];
static int resCount = 0;


const char *ROOMS_FILE = "rooms.txt";
const char *RES_FILE = "reservations.txt";


static void clearInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

static int nextRoomId(void) {
    int max = 0;
    for (int i = 0; i < roomCount; ++i) if (rooms[i].id > max) max = rooms[i].id;
    return max + 1;
}
static int nextReservationId(void) {
    int max = 0;
    for (int i = 0; i < resCount; ++i) if (reservations[i].id > max) max = reservations[i].id;
    return max + 1;
}


void loadRooms(void) {
    FILE *f = fopen(ROOMS_FILE, "r");
    if (!f) return;
    roomCount = 0;
    while (roomCount < MAX_ROOMS &&
           fscanf(f, "%d|%31[^|]|%d|%lf|%d\n",
                  &rooms[roomCount].id,
                  rooms[roomCount].type,
                  &rooms[roomCount].capacity,
                  &rooms[roomCount].price,
                  &rooms[roomCount].active) == 5) {
        roomCount++;
    }
    fclose(f);
}

void saveRooms(void) {
    FILE *f = fopen(ROOMS_FILE, "w");
    if (!f) {
        perror("saveRooms fopen");
        return;
    }
    for (int i = 0; i < roomCount; ++i) {
        fprintf(f, "%d|%s|%d|%.2f|%d\n",
                rooms[i].id,
                rooms[i].type,
                rooms[i].capacity,
                rooms[i].price,
                rooms[i].active);
    }
    fclose(f);
}

void loadReservations(void) {
    FILE *f = fopen(RES_FILE, "r");
    if (!f) return;
    resCount = 0;
    while (resCount < MAX_RESERVATIONS &&
           fscanf(f, "%d|%d|%127[^|]|%d|%10[^|]|%10[^|]|%d\n",
                  &reservations[resCount].id,
                  &reservations[resCount].roomId,
                  reservations[resCount].guestName,
                  &reservations[resCount].guests,
                  reservations[resCount].checkin,
                  reservations[resCount].checkout,
                  &reservations[resCount].active) == 7) {
        resCount++;
    }
    fclose(f);
}

void saveReservations(void) {
    FILE *f = fopen(RES_FILE, "w");
    if (!f) {
        perror("saveReservations fopen");
        return;
    }
    for (int i = 0; i < resCount; ++i) {
        fprintf(f, "%d|%d|%s|%d|%s|%s|%d\n",
                reservations[i].id,
                reservations[i].roomId,
                reservations[i].guestName,
                reservations[i].guests,
                reservations[i].checkin,
                reservations[i].checkout,
                reservations[i].active);
    }
    fclose(f);
}

void addRoom(void) {
    if (roomCount >= MAX_ROOMS) { puts("Room capacity reached."); return; }
    Room r = {0};
    r.id = nextRoomId();
    printf("Type (e.g., Single, Double, Suite): ");
    fgets(r.type, sizeof(r.type), stdin);
    r.type[strcspn(r.type, "\n")] = '\0';
    printf("Capacity: ");
    if (scanf("%d", &r.capacity) != 1) { clearInputBuffer(); puts("Invalid input."); return; }
    printf("Price per night: ");
    if (scanf("%lf", &r.price) != 1) { clearInputBuffer(); puts("Invalid input."); return; }
    clearInputBuffer();
    r.active = 1;
    rooms[roomCount++] = r;
    saveRooms();
    puts("Room added.");
}

void listRooms(void) {
    puts("Rooms:");
    for (int i = 0; i < roomCount; ++i) {
        if (!rooms[i].active) continue;
        printf("ID:%d Type:%s Cap:%d Price:%.2f\n",
               rooms[i].id, rooms[i].type, rooms[i].capacity, rooms[i].price);
    }
}


int roomExistsAndActive(int id) {
    for (int i = 0; i < roomCount; ++i) if (rooms[i].id == id && rooms[i].active) return 1;
    return 0;
}

void createReservation(void) {
    if (resCount >= MAX_RESERVATIONS) { puts("Too many reservations."); return; }
    Reservation r = {0};
    r.id = nextReservationId();
    printf("Room ID: ");
    if (scanf("%d", &r.roomId) != 1) { clearInputBuffer(); puts("Invalid input."); return; }
    if (!roomExistsAndActive(r.roomId)) { puts("Room not found."); clearInputBuffer(); return; }
    clearInputBuffer();
    printf("Guest name: ");
    fgets(r.guestName, sizeof(r.guestName), stdin);
    r.guestName[strcspn(r.guestName, "\n")] = '\0';
    printf("Number of guests: ");
    if (scanf("%d", &r.guests) != 1) { clearInputBuffer(); puts("Invalid input."); return; }
    clearInputBuffer();
    printf("Check-in (YYYY-MM-DD): ");
    fgets(r.checkin, sizeof(r.checkin), stdin);
    r.checkin[strcspn(r.checkin, "\n")] = '\0';
    printf("Check-out (YYYY-MM-DD): ");
    fgets(r.checkout, sizeof(r.checkout), stdin);
    r.checkout[strcspn(r.checkout, "\n")] = '\0';
    r.active = 1;
    reservations[resCount++] = r;
    saveReservations();
    puts("Reservation created.");
}

void listReservations(void) {
    puts("Reservations:");
    for (int i = 0; i < resCount; ++i) {
        if (!reservations[i].active) continue;
        printf("ResID:%d Room:%d Guest:%s Guests:%d %s->%s\n",
               reservations[i].id,
               reservations[i].roomId,
               reservations[i].guestName,
               reservations[i].guests,
               reservations[i].checkin,
               reservations[i].checkout);
    }
}

void cancelReservation(void) {
    int id;
    printf("Reservation ID to cancel: ");
    if (scanf("%d", &id) != 1) { clearInputBuffer(); puts("Invalid input."); return; }
    for (int i = 0; i < resCount; ++i) {
        if (reservations[i].id == id && reservations[i].active) {
            reservations[i].active = 0;
            saveReservations();
            puts("Reservation cancelled.");
            clearInputBuffer();
            return;
        }
    }
    puts("Reservation not found or already cancelled.");
    clearInputBuffer();
}


void seedIfEmpty(void) {
    if (roomCount == 0) {
        Room r1 = { .id = 1, .capacity = 1, .price = 59.99, .active = 1 }; strcpy(r1.type, "Single");
        Room r2 = { .id = 2, .capacity = 2, .price = 89.99, .active = 1 }; strcpy(r2.type, "Double");
        rooms[roomCount++] = r1;
        rooms[roomCount++] = r2;
        saveRooms();
    }
}



typedef void (*MenuAction)(void);

typedef struct {
    const char *label;
    MenuAction action;
} MenuItem;

static int g_shouldQuit = 0;

void saveAndExit(void) {
    saveRooms();
    saveReservations();
    puts("Saved. Exiting.");
    g_shouldQuit = 1;
}

void printMenuWithItems(const MenuItem *items, size_t count) {
    puts("\nHotel Reservation System");
    for (size_t i = 0; i < count; ++i) {
        printf("%zu) %s\n", i + 1, items[i].label);
    }
    printf("Choose: ");
}

int main(void) {
    loadRooms();
    loadReservations();
    seedIfEmpty();


    MenuItem menu[] = {
        { "List rooms",        listRooms },
        { "Add room",          addRoom },
        { "List reservations", listReservations },
        { "Create reservation", createReservation },
        { "Cancel reservation", cancelReservation },
        { "Save & Exit",        saveAndExit }
    };
    const size_t menuCount = sizeof(menu) / sizeof(menu[0]);

    int choice = 0;
    while (!g_shouldQuit) {
        printMenuWithItems(menu, menuCount);
        if (scanf("%d", &choice) != 1) { clearInputBuffer(); puts("Invalid input."); continue; }
        clearInputBuffer();
        if (choice < 1 || choice > (int)menuCount) {
            puts("Invalid choice.");
            continue;
        }
       
        MenuAction act = menu[choice - 1].action;
        if (act) act();
    }

    return 0;
}