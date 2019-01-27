#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <termios.h>
#include <fcntl.h>

typedef struct Car Car;
typedef struct List List;

char key_pressed();
char **loadmap(int mapWidth, int mapHeight, int txtName, char **map);
void displayMap(int mapWidth, int mapHeight, char **map, char **circMap, List *listOfCar, List *listOfTram, int frame);
void displayMenuMap(int mapWidth, int mapHeight, int frame);
List* initiateList();
List *clearList(List* listOfCar, char** map);
List *createCar(List* listOfCar, int posX, int posY, int id, char **map, int kindOfObject);
void displayList(List* listOfCar);
List *deleteCar(List *listOfCar, int id/*, char **map, char **staticMap*/);
List *moveCar(List *listOfCar,/* int id,*/ char **map, char **circMap, char **staticMap, int mapWidth, int mapHeight, int frame, int kindOfObject);
int* findSpawnPoints(int nbOfSpawns, char** map, int kindOfSpawn);
List *killVehicles(List *listOfCar, int nbOfDeathPoints, char **map, char **staticMap, int kindOfObject);
char **clearDeadVehicles(char **map, char **staticMap, int nbOfDeathPoints, int kindOfObject);
int idIsFree(List *listOfCar, int id);
int findFreeId(List *listOfCar, int maxNumberOfCars);
List *createVehicle(List *listOfCar, int *spawnPoint, int maxNumberOfCars, int nbOfSpawnPoints, char **map);
List *createPedestrian(List *listOfPedestrian, int *pedestrianSpawnPoint, int maxNumberOfPedestrians, int nbOfPedestrianSpawnPoints, char **map);
List *createTram(List *listOfTram, char **map, int frame);
List *moveDangerousCar(List *listOfCar, char **map, char **circMap, char **staticMap, int mapWidth, int mapHeight, int frame, int kindOfObject);
void menu();
void launch();
void dangerMode();
