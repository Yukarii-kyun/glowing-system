#include <stdio.h>
#include <conio.h>
#include <string.h>

#define MAX_ROOMS 100
#define MAX_RESERVATIONS 200

typedef struct {
    int id;
    char type[20];
    int capacity;
    float price;
} Room;

typedef struct {
    int id;
    int roomId;
    char guestName[50];
    char checkin[11];
    char checkout[11];
    int guests;
    float totalPrice;
    int nights;
} Reservation;

Room rooms[MAX_ROOMS];
int roomCount = 0;

Reservation reservations[MAX_RESERVATIONS];
int resCount = 0;

int findRoomById(int id) {
    int i;
    for (i = 0; i < roomCount; i++) {
        if (rooms[i].id == id) return i;
    }
    return -1;
}

int getNights(char checkin[], char checkout[]) {
    int y1, m1, d1, y2, m2, d2;
    int days1, days2;
    sscanf(checkin, "%d-%d-%d", &y1, &m1, &d1);
    sscanf(checkout, "%d-%d-%d", &y2, &m2, &d2);
    days1 = y1 * 365 + m1 * 30 + d1;
    days2 = y2 * 365 + m2 * 30 + d2;
    return days2 - days1;
}

void addRoom() {
    Room r;
    r.id = roomCount + 1;

    printf("Enter room type: ");
    fflush(stdin);
    gets(r.type);

    printf("Enter capacity: ");
    scanf("%d", &r.capacity);

    printf("Enter price per night: ");
    scanf("%f", &r.price);

    rooms[roomCount++] = r;
    printf("Room added!\n");
}

void listRooms() {
    int i;
    printf("Rooms:\n");
    for (i = 0; i < roomCount; i++) {
        printf("ID: %d, Type: %s, Capacity: %d, Price: %.2f\n",
               rooms[i].id, rooms[i].type, rooms[i].capacity, rooms[i].price);
    }
}

void makeReservation() {
    Reservation r;
    int roomIndex, nights;

    r.id = resCount + 1;

    printf("Enter room ID: ");
    scanf("%d", &r.roomId);

    roomIndex = findRoomById(r.roomId);
    if (roomIndex == -1) {
        printf("Room not found.\n");
        return;
    }

    printf("Enter guest name: ");
    fflush(stdin);
    gets(r.guestName);

    printf("Enter number of guests: ");
    scanf("%d", &r.guests);

    printf("Enter check-in date (YYYY-MM-DD): ");
    fflush(stdin);
    gets(r.checkin);

    printf("Enter check-out date (YYYY-MM-DD): ");
    gets(r.checkout);

    nights = getNights(r.checkin, r.checkout);
    if (nights <= 0) {
        printf("Invalid dates.\n");
        return;
    }

    r.nights = nights;
    r.totalPrice = nights * rooms[roomIndex].price;

    reservations[resCount++] = r;

    printf("Reservation created!\n");
    printf("Total nights: %d\n", nights);
    printf("Price per night: %.2f\n", rooms[roomIndex].price);
    printf("Total price: %.2f\n", r.totalPrice);
}

void listReservations() {
    int i;
    printf("Reservations:\n");
    for (i = 0; i < resCount; i++) {
        printf("ResID: %d, RoomID: %d, Guest: %s, Guests: %d, %s to %s, Nights: %d, Total: %.2f\n",
               reservations[i].id,
               reservations[i].roomId,
               reservations[i].guestName,
               reservations[i].guests,
               reservations[i].checkin,
               reservations[i].checkout,
               reservations[i].nights,
               reservations[i].totalPrice);
    }
}

void cancelReservation() {
    int id, i, j;
    printf("Enter reservation ID to cancel: ");
    scanf("%d", &id);

    for (i = 0; i < resCount; i++) {
        if (reservations[i].id == id) {
            for (j = i; j < resCount - 1; j++) {
                reservations[j] = reservations[j + 1];
            }
            resCount--;
            printf("Reservation canceled.\n");
            return;
        }
    }

    printf("Reservation not found.\n");
}

void showMenu() {
    printf("\nHotel Reservation System\n");
    printf("1. Add Room\n");
    printf("2. List Rooms\n");
    printf("3. Make Reservation\n");
    printf("4. List Reservations\n");
    printf("5. Cancel Reservation\n");
    printf("6. Exit\n");
    printf("Choose an option: ");
}

int main() {
    int choice;
    clrscr();

    while (1) {
        showMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1: addRoom(); break;
            case 2: listRooms(); break;
            case 3: makeReservation(); break;
            case 4: listReservations(); break;
            case 5: cancelReservation(); break;
            case 6: printf("Goodbye!\n"); getch(); return 0;
            default: printf("Invalid option.\n");
        }

        printf("\nPress any key to continue...");
        getch();
        clrscr();
    }

    return 0;
}
