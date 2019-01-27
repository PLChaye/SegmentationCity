#include "functions.h"

#define color(param) printf("\033[%sm",param)

//typedef struct Car Car;
struct Car{
	struct Car *next;
	int xPos;
	int yPos;
	int id;
	char currentDirection;
	int color;
	int level;
};

//typedef struct List List;
struct List{
	Car *firstCar;
	int carsRunning;
};

char key_pressed(){
	struct termios oldterm, newterm;
	int oldfd; char c, result = 0;

	tcgetattr (STDIN_FILENO, &oldterm);
	newterm = oldterm; newterm.c_lflag &= ~(ICANON | ECHO);
	tcsetattr (STDIN_FILENO, TCSANOW, &newterm);
	oldfd = fcntl(STDIN_FILENO, F_GETFL, 0);
	fcntl (STDIN_FILENO, F_SETFL, oldfd | O_NONBLOCK);
	c = getchar();
	tcsetattr (STDIN_FILENO, TCSANOW, &oldterm);
	fcntl (STDIN_FILENO, F_SETFL, oldfd);

	if (c != EOF) {
		ungetc(c, stdin); result = getchar();
	}
	return result;
}

char **loadmap(int mapWidth, int mapHeight, int txtName, char **map){
	int i, j;
	FILE *fichier = NULL;
	if(txtName == 0){
		fichier = fopen("map.txt", "r");
	}
	else if(txtName == 1){
		fichier = fopen("mapSens.txt", "r");
	}
	else if(txtName == 2){
		fichier = fopen("emergencyCircMap.txt", "r");
	}
	else if(txtName == 3){
		fichier = fopen("dangerousCircMap.txt", "r");
	}
	if(fichier != NULL){
		for(i=0; i<mapHeight; i++){
			for(j=0; j<mapWidth+1; j++){
				map[i][j] = fgetc(fichier);
			}
		}
	}
	fclose(fichier);
	return map;
}

void debugMap(int mapWidth, int mapHeight, char **map){
	int i,j;
	for(i=0; i<mapHeight; i++){
		for(j=0; j<mapWidth; j++){
			printf("%c", map[i][j]);
		}
		printf("\n");
	}
}

void displayMap(int mapWidth, int mapHeight, char **map, char **circMap, List *listOfCar, List *listOfTram, int frame){
	int i,j,k;
	Car *currentCar;
	for(i=0; i<mapHeight; i++){
		for(j=0; j<mapWidth; j++){
			/*if(i>=31 && i<=35 && j>=54 && j<=83){
			  color("44;1");
			  }*/
			if(map[i][j] == 'O'){
				printf("▌");
			}
			else if(map[i][j] == 'P'){
				if(i>=31 && i<=35 && j>=54 && j<=83){
					color("44;1");
				}
				printf("▪");
				color("0");
			}
			else if(map[i][j] == 'M'){
				printf("-");
			}
			else if(map[i][j] == 'A'){
				if(i>=31 && i<=35 && j>=54 && j<=82){
					color("44;1");
				}
				printf("│");
				color("0");
			}
			else if(map[i][j] == 'B'){
				if(i>=31 && i<=35 && j>=54 && j<=83){
					color("44;1");
				}
				printf("─");
				color("0");
			}	
			else if(map[i][j] == 'C'){
				currentCar = listOfCar->firstCar;
				while(i!=currentCar->yPos || j!=currentCar->xPos){
					currentCar = currentCar->next;
				}
				if(currentCar->color >= 255){
					if(currentCar->currentDirection == 'L' || currentCar->currentDirection == 'R'){
						if(frame%6 > 2+currentCar->color-255 || frame%6 <= -1+currentCar->color-255){
							printf("\033[22;31m🀰\033[0m");
						}
						else{
							printf("\033[22;34m🀰\033[0m");
						}
					}
					else{
						if(frame%6 > 2+currentCar->color-255 || frame%6 <= -1+currentCar->color-255){
							printf("\033[22;31m🁢\033[0m");
						}
						else{
							printf("\033[22;34m🁢\033[0m");
						}
					}
				}
				else{
					if(currentCar->currentDirection == 'L' || currentCar->currentDirection == 'R'){
						printf("\033[22;3%dm🀰\033[0m", currentCar->color);
					}
					else{
						printf("\033[22;3%dm🁢\033[0m", currentCar->color);
					}
				}
			}
			else if(map[i][j] == 'N'){
				k=rand()%2;
				if((i>=21 && i<=26 && j>=54 && j<=82) || (i==4 && j<=12) || (i==17 && j<=6) || (i==7 && j<=40 && j>=22) || (i==16 && ((j>=54 && j<=61) || (j>=73 && j<=82)))){
					if(k == 0){
						printf("\033[22;43m🛉\033[0m");
					}
					else{
						printf("\033[22;43m🚹\033[0m");
					}
				}
				else if((j>=54 && j<=82 && i<=10) || (j>=62 && j<=72 && i==16)){
					if(k == 0){
						printf("\033[22;40m🛉\033[0m");
					}
					else{
						printf("\033[22;40m🚹\033[0m");
					}
				}
				else{
					if(k == 0){
						printf("🛉");
					}
					else{
						printf("🚹");
					}
				}				
			}
			else if(map[i][j] == 'J'){
				if(i>=31 && i<=35 && j>=54 && j<=83){
					color("44;1");
				}
				printf("└");
				color("0");
			}
			else if(map[i][j] == 'D'){
				if(i>=31 && i<=35 && j>=54 && j<=83){
					color("44;1");
				}
				printf("┐");
				color("0");
			}
			else if(map[i][j] == 'E'){
				if(i>=31 && i<=35 && j>=54 && j<=83){
					color("44;1");
				}
				printf("┘");
				color("0");
			}
			else if(map[i][j] == 'F'){
				if(i>=31 && i<=35 && j>=54 && j<=83){
					color("44;1");
				}
				printf("┌");
				color("0");
			}
			else if(map[i][j] == 'G'){
				if(i>=31 && i<=35 && j>=54 && j<=83){
					color("44;1");
				}
				printf("┬");
				color("0");
			}
			else if(map[i][j] == 'H'){
				if(i>=31 && i<=35 && j>=54 && j<=83){
					color("44;1");
				}
				printf("├");
				color("0");
			}
			else if(map[i][j] == 'I'){
				if(i>=31 && i<=35 && j>=54 && j<=83){
					color("44;1");
				}
				printf("┴");
				color("0");
			}
			else if(map[i][j] == 'K'){
				if(frame%80 < 30){
					printf("\033[22;32m▪\033[0m");
				}
				else{
					printf("\033[22;31m▪\033[0m");
				}
			}
			else if(map[i][j] == 'L'){
				if(frame%80 >= 40 && frame%80 < 70){
					printf("\033[22;32m▪\033[0m");
				}
				else{
					printf("\033[22;31m▪\033[0m");
				}
			}
			else if(map[i][j] == 'Q'){
				printf("\033[22;34m█\033[0m");
			}
			else if(map[i][j] == 'R'){
				printf("⚌");
			}
			else if(map[i][j] == 'Z'){
				printf("\033[22;42m⚌\033[0m");
			}
			else if(map[i][j] == 'a'){
				printf("\033[22;42m \033[0m");
			}
			else if(map[i][j] == 'T'){
				Car *currentTram = listOfTram->firstCar;
				while(i!=currentTram->yPos || j!=currentTram->xPos){
					currentTram = currentTram->next;
				}
				if(currentTram->id == 0){
					if((j>=41 && j<=53) || (j>=83 && j<=89)){
						printf("◗");
					}
					else{
						printf("\033[22;42m◗\033[0m");
					}
				}
				else if(currentTram->id == 1 || currentTram->id == 4 || currentTram->id == 7){
					if((j>=41 && j<=53) || (j>=83 && j<=89)){
						printf(" ");
					}
					else{
						printf("\033[22;42m \033[0m");
					}
				}
				else if(currentTram->id == 10){
					if((j>=41 && j<=53) || (j>=83 && j<=89)){
						printf("◖");
					}
					else{
						printf("\033[22;42m◖\033[0m");
					}
				}
				else{
					if((j>=41 && j<=53) || (j>=83 && j<=89)){
						printf("■");
					}
					else{
						printf("\033[22;42m■\033[0m");
					}
				}
			}
			else if(map[i][j] == 'U'){
				if((frame%80 < 30) && (map[15][32] != 'T' && map[15][41] != 'T' && map[17][62] != 'T' && map[17][53] != 'T' && map[17][50] != 'T' && map[19][48] != 'T')){
					printf("\033[22;32m▪\033[0m");
				}
				else  {
					printf("\033[22;31m▪\033[0m");
				}
			}
			else if(map[i][j] == 'V'){
				if((frame%80 < 30) && (map[17][88] != 'T' && map[17][96] != 'T' && map[15][86] != 'T' && map[15][78] != 'T')){
					printf("\033[22;32m▪\033[0m");
				}
				else  {
					printf("\033[22;31m▪\033[0m");
				}

			}
			else if(map[i][j] == 'W'){
				if((frame%80 >=40 && frame%80 < 70) && (map[17][88] != 'T' && map[17][96] != 'T' && map[15][86] != 'T' && map[15][78] != 'T')){
					printf("\033[22;32m▪\033[0m");
				}
				else  {
					printf("\033[22;31m▪\033[0m");
				}

			}
			else if(map[i][j] == 'X'){
				if((frame%80 < 30) && (map[15][32] != 'T' && map[15][41] != 'T' && map[17][62] != 'T' && map[17][53] != 'T' && map[17][50] != 'T' && map[19][48] != 'T')){
					printf("\033[22;32m▪\033[0m");
				}
				else  {
					printf("\033[22;31m▪\033[0m");
				}

			}
			else if(map[i][j] == 'Y'){
				if((frame%80 >= 40 && frame%80 < 70) && (map[15][32] != 'T' && map[15][41] != 'T' && map[17][62] != 'T' && map[17][53] != 'T' && map[17][50] != 'T' && map[19][48] != 'T')){
					printf("\033[22;32m▪\033[0m");
				}
				else  {
					printf("\033[22;31m▪\033[0m");
				}
			}
			else if(map[i][j] == 'b'){

			}
			else if(map[i][j] == 'c'){
				color("31;2");
				printf("█");
				color("0");
			}
			else if(map[i][j] == 'd'){
				color("31");
				printf("█");
				color("0");
			}
			else if(map[i][j] == 'e'){
				if(i>=31 && i<=35 && j>=54 && j<=83){
					color("44;1");
				}
				printf("╂");
				color("0");
			}
			else if(map[i][j] == 'f'){
				if(i==4){
					color("42;37");
				}
				else if(i==10 && j>=97){
					color("44;30");
				}
				else if(i==10 && j<97){
                                        color("30");
                                }
				else{
					color("37");
				}
				printf("▄");
				color("0");
			}
			else if(map[i][j] == 'g'){
				if((j==16 || j==38 || (j==33 && i>=23) || j==55 || j==65 || j==71 || j==81) && i>=5){
					color("37");
				}
				else{
					color("30");
				}
				printf("█");
				color("0");
			}
			else if(map[i][j] == 'h'){
				if((i>=15 && i<=26 && j>=54 && j<=82) || (i>=0 && i<=26 && j>=0 && j<=13) || (i>=31 && j<=40)){
					color("42;32;2");
					printf("▙");
					color("0");
				}
				else{
					printf("\033[22;2;32m▙\033[0m");
				}
			}
			else if(map[i][j] == 'i'){
				if(i>=31 && i<=35 && j>=54 && j<=83){
					color("34");
				}
				else{
					color("32;2");
				}
				printf("█");
				color("0");
			}
			else if(map[i][j] == 'j'){
				if((i>=15 && i<=26 && j>=54 && j<=82) || (i>=0 && i<=26 && j>=0 && j<=13) || (i>=31 && j<=40)){
					color("42;32;2");
					printf("▛");
					color("0");
				}
				else{
					printf("\033[22;2;32m▛\033[0m");
				}
			}
			else if(map[i][j] == 'k'){
				if((i>=15 && i<=26 && j>=54 && j<=82) || (i>=0 && i<=26 && j>=0 && j<=13) || (i>=31 && j<=40)){
					color("42;32;2");
					printf("▜");
					color("0");
				}
				else{
					printf("\033[22;2;32m▜\033[0m");
				}
			}
			else if(map[i][j] == 'l'){
				if((i>=15 && i<=26 && j>=54 && j<=82) || (i>=0 && i<=26 && j>=0 && j<=13) || (i>=31 && j<=40)){
					color("42;32;2");
					printf("▟");
					color("0");
				}
				else{
					printf("\033[22;2;32m▟\033[0m");
				}
			}
			else if(map[i][j] == 'm'){
				printf("\033[22;33m█\033[0m");
			}
			else if(map[i][j] == 'n'){
				if(i==9 || i==0){
					color("42;37");
				}
				else if(i==22 && j>=97){
					color("44;30");
				}
				else if(i==22 && j<97){
                                        color("30");
                                }
				else{
					color("37");
				}
				printf("▀");
				color("0");
			}
			else if(map[i][j] == 'o'){
				printf("━");
			}
			else if(map[i][j] == 'p'){
				printf("┓");
			}
			else if(map[i][j] == 'q'){
				printf("┃");
			}
			else if(map[i][j] == 'r'){
				printf("┚");
			}
			else if(map[i][j] == 's'){
				if(i>=31 && i<=35 && j>=54 && j<=83){
					color("44;1");
				}
				printf("┤");
				color("0");
			}
			else if(map[i][j] == 't'){
				color("30");
				printf("█");
				color("0");
			}
			else if(map[i][j] == 'u'){

			}
			else if(map[i][j] == 'v'){
				if(frame%6 > 2){
					color("31");
				}
				else{
					color("34");
				}
				printf("🀰");
				color("0");
			}
			else if(map[i][j] == 'w'){
				if(frame%6 > 3 || frame == 0){
					color("31");
				}
				else{
					color("34");
				}
				printf("🀰");
				color("0");
			}
			else if(map[i][j] == 'x'){
				if(frame%6 > 4 || frame%6 < 2){
					color("31");
				}
				else{
					color("34");
				}
				printf("🁢");
				color("0");
			}
			else if(map[i][j] == 'y'){
				color("30");
				printf("🁢");
				color("0");
			}
			else if(map[i][j] == 'z'){
				if(frame%4==0 || frame%4==1){
					color("31");
				}
				else{
					color("33");
				}
				printf("🏙");
				color("0");
			}
			/*if(i>=31 && i<=35 && j>=54 && j<=83){
			  color("0");
			  }*/
			else{
				printf("%c", map[i][j]);
			}
		}
		printf("\n");
	}
	printf("Frame n°%d\n", frame);
}

void displayMenuMap(int mapHeight, int mapWidth, int frame){
	int i,j;	
	char **map = malloc(mapHeight*sizeof(char*));
	for(i=0; i<mapHeight; i++){
		map[i] = malloc((mapWidth+1)*sizeof(char));
	}
	FILE *fichier = NULL;
	fichier = fopen("menu.txt", "r");
	if(fichier != NULL){
		for(i=0; i<mapHeight; i++){
			for(j=0; j<mapWidth+1; j++){
				map[i][j] = fgetc(fichier);
			}
		}
	}
	fclose(fichier);
	for(i=0; i<mapHeight; i++){
		for(j=0; j<mapWidth; j++){
			if(map[i][j] == 'O'){
				printf("▌");
			}
			else if(map[i][j] == 'P'){
				if(i>=31 && i<=35 && j>=54 && j<=83){
					color("44;1");
				}
				printf("▪");
				color("0");
			}
			else if(map[i][j] == 'M'){
				printf("-");
			}
			else if(map[i][j] == 'A'){
				if(i>=31 && i<=35 && j>=54 && j<=82){
					color("44;1");
				}
				printf("│");
				color("0");
			}
			else if(map[i][j] == 'B'){
				if(i>=31 && i<=35 && j>=54 && j<=83){
					color("44;1");
				}
				printf("─");
				color("0");
			}	
			else if(map[i][j] == 'J'){
				if(i>=31 && i<=35 && j>=54 && j<=83){
					color("44;1");
				}
				printf("└");
				color("0");
			}
			else if(map[i][j] == 'D'){
				if(i>=31 && i<=35 && j>=54 && j<=83){
					color("44;1");
				}
				printf("┐");
				color("0");
			}
			else if(map[i][j] == 'E'){
				if(i>=31 && i<=35 && j>=54 && j<=83){
					color("44;1");
				}
				printf("┘");
				color("0");
			}
			else if(map[i][j] == 'F'){
				if(i>=31 && i<=35 && j>=54 && j<=83){
					color("44;1");
				}
				printf("┌");
				color("0");
			}
			else if(map[i][j] == 'G'){
				if(i>=31 && i<=35 && j>=54 && j<=83){
					color("44;1");
				}
				printf("┬");
				color("0");
			}
			else if(map[i][j] == 'H'){
				if(i>=31 && i<=35 && j>=54 && j<=83){
					color("44;1");
				}
				printf("├");
				color("0");
			}
			else if(map[i][j] == 'I'){
				if(i>=31 && i<=35 && j>=54 && j<=83){
					color("44;1");
				}
				printf("┴");
				color("0");
			}
			else if(map[i][j] == 'K'){
				if(frame%800000 < 300000){
					printf("\033[22;32m▪\033[0m");
				}
				else{
					printf("\033[22;31m▪\033[0m");
				}
			}
			else if(map[i][j] == 'L'){
				if(frame%800000 >= 400000 && frame%800000 < 700000){
					printf("\033[22;32m▪\033[0m");
				}
				else{
					printf("\033[22;31m▪\033[0m");
				}
			}
			else if(map[i][j] == 'Q'){
				printf("\033[22;34m█\033[0m");
			}
			else if(map[i][j] == 'R'){
				printf("⚌");
			}
			else if(map[i][j] == 'Z'){
				printf("\033[22;42m⚌\033[0m");
			}
			else if(map[i][j] == 'a'){
				printf("\033[22;42m \033[0m");
			}
			else if(map[i][j] == 'c'){
				color("31;2");
				printf("█");
				color("0");
			}
			else if(map[i][j] == 'd'){
				color("31");
				printf("█");
				color("0");
			}
			else if(map[i][j] == 'e'){
				if(i>=31 && i<=35 && j>=54 && j<=83){
					color("44;1");
				}
				printf("╂");
				color("0");
			}
			else if(map[i][j] == 'f'){
				if(i==4){
					color("42;37");
				}
				else if(i==10 && j>=97){
					color("44;30");
				}
				else if(i==10 && j<97){
                                        color("30");
                                }
				else{
					color("37");
				}
				printf("▄");
				color("0");
			}
			else if(map[i][j] == 'g'){
				if((j==16 || j==38 || (j==33 && i>=23) || j==55 || j==65 || j==71 || j==81) && i>=5){
					color("37");
				}
				else{
					color("30");
				}
				printf("█");
				color("0");
			}
			else if(map[i][j] == 'h'){
				if((i>=15 && i<=26 && j>=54 && j<=82) || (i>=0 && i<=26 && j>=0 && j<=13) || (i>=31 && j<=40)){
					color("42;32;2");
					printf("▙");
					color("0");
				}
				else{
					printf("\033[22;2;32m▙\033[0m");
				}
			}
			else if(map[i][j] == 'i'){
				if(i>=31 && i<=35 && j>=54 && j<=83){
					color("34");
				}
				else{
					color("32;2");
				}
				printf("█");
				color("0");
			}
			else if(map[i][j] == 'j'){
				if((i>=15 && i<=26 && j>=54 && j<=82) || (i>=0 && i<=26 && j>=0 && j<=13) || (i>=31 && j<=40)){
					color("42;32;2");
					printf("▛");
					color("0");
				}
				else{
					printf("\033[22;2;32m▛\033[0m");
				}
			}
			else if(map[i][j] == 'k'){
				if((i>=15 && i<=26 && j>=54 && j<=82) || (i>=0 && i<=26 && j>=0 && j<=13) || (i>=31 && j<=40)){
					color("42;32;2");
					printf("▜");
					color("0");
				}
				else{
					printf("\033[22;2;32m▜\033[0m");
				}
			}
			else if(map[i][j] == 'l'){
				if((i>=15 && i<=26 && j>=54 && j<=82) || (i>=0 && i<=26 && j>=0 && j<=13) || (i>=31 && j<=40)){
					color("42;32;2");
					printf("▟");
					color("0");
				}
				else{
					printf("\033[22;2;32m▟\033[0m");
				}
			}
			else if(map[i][j] == 'm'){
				printf("\033[22;33m█\033[0m");
			}
			else if(map[i][j] == 'n'){
				if(i==9 || i==0){
					color("42;37");
				}
				else if(i==22 && j>=97){
					color("44;30");
				}
				else if(i==22 && j<97){
                                        color("30");
                                }
				else{
					color("37");
				}
				printf("▀");
				color("0");
			}
			else if(map[i][j] == 'o'){
				printf("━");
			}
			else if(map[i][j] == 'p'){
				printf("┓");
			}
			else if(map[i][j] == 'q'){
				printf("┃");
			}
			else if(map[i][j] == 'r'){
				printf("┚");
			}
			else if(map[i][j] == 's'){
				if(i>=31 && i<=35 && j>=54 && j<=83){
					color("44;1");
				}
				printf("┤");
				color("0");
			}
			else if(map[i][j] == 't'){
				color("30");
				printf("█");
				color("0");
			}
			else if(map[i][j] == 'v'){
				if(frame%6 > 2){
					color("31");
				}
				else{
					color("34");
				}
				printf("🀰");
				color("0");
			}
			else if(map[i][j] == 'w'){
				if(frame%6 > 3 || frame == 0){
					color("31");
				}
				else{
					color("34");
				}
				printf("🀰");
				color("0");
			}
			else if(map[i][j] == 'x'){
				if(frame%6 > 4 || frame%6 < 2){
					color("31");
				}
				else{
					color("34");
				}
				printf("🁢");
				color("0");
			}
			else if(map[i][j] == 'y'){
				color("30");
				printf("🁢");
				color("0");
			}
			else{
				printf("%c", map[i][j]);
			}
		}
		printf("\n");
	}
	printf("Frame n°%d\n", frame);
}


List* initiateList(){
	List *list = malloc(sizeof(*list));
	Car *car = NULL;

	if(list == NULL){
		printf("Error n°A1");
		exit(EXIT_FAILURE);
	}
	else{
		list->firstCar = car;
		list->carsRunning = 0;
		return list;
	}
	free(list);
	free(car);
}

List *clearList(List* listOfCar, char** map){
	Car *current = listOfCar->firstCar;
	int random;
	while(listOfCar->carsRunning > 0){
		listOfCar->firstCar = current->next;
		listOfCar->carsRunning--;
		if(current->color >= 255 && current->currentDirection=='R'){
			random = rand()%2;
			if(random==0){
				map[current->yPos][current->xPos] = 'v';
			}
			else{
				map[current->yPos][current->xPos] = 'w';
			}
		}
		else if(current->color >= 255 && (current->currentDirection=='U' || current->currentDirection=='D')){
			map[current->yPos][current->xPos] = 'x';
		}
		else{
			map[current->yPos][current->xPos] = 'y';
		}
		free(current);
		current = listOfCar->firstCar;
	}
	return listOfCar;	
}

List *createCar(List* listOfCar, int posX, int posY, int id, char **map, int kindOfObject){
	int i;
	Car *new = malloc(sizeof(*new));
	if(listOfCar == NULL || new == NULL){
		printf("Error n°A2");
		exit(EXIT_FAILURE);
	}
	else{
		new->xPos = posX;
		new->yPos = posY;
		new->id = id;
		new->level = 1;
		if(kindOfObject == 2 && listOfCar->carsRunning != 0){
			Car *current = listOfCar->firstCar;
			for(i=0; i<listOfCar->carsRunning-1; i++){
				current = current->next;
			}
			current->next = new;
			new->next = NULL;
		}
		else{
			new->next = listOfCar->firstCar;
			listOfCar->firstCar = new;
		}
		listOfCar->carsRunning++;
		//printf("%d cars running. ", listOfCar->carsRunning);
		//printf("Car %d(%d, %d) created\n", id, posX, posY);
		if(kindOfObject == 0){
			map[posY][posX] = 'C';
			new->color = (rand()%5)+1;
		}
		else if(kindOfObject == 1){
			map[posY][posX] = 'N';
		}
		else if(kindOfObject == 2){
			map[posY][posX] = 'T';
		}
		else if(kindOfObject == 3){
			map[posY][posX] = 'C';
			new->color = rand()%3+255;
		}
		return listOfCar;
	}
}


void displayList(List* listOfCar){
	Car *car = listOfCar->firstCar;
	while(car!=NULL){
		printf("%d (%d,%d); ", car->id, car->xPos, car->yPos);
		car = car->next;
	}
	printf("\n\n");
	free(car);
}

List *deleteCar(List *listOfCar, int id/*, char **map, char **staticMap*/){
	if(listOfCar == NULL){
		printf("Error n°A3");
		exit(EXIT_FAILURE);
	}
	else{
		Car *browseList = listOfCar->firstCar;

		if(listOfCar->firstCar->id == id){
			listOfCar->firstCar = browseList->next;
			listOfCar->carsRunning--;
			free(browseList);
			return listOfCar;
		}
		else{
			Car *browseListPrevious = browseList;
			browseList = browseList->next;
			while(browseList!=NULL){
				if(browseList->id == id){
					//map[browseList->yPos][browseList->xPos] = staticMap[browseList->yPos][browseList->xPos];
					//printf("Car n°%d deleted\n", browseList->id);
					browseListPrevious->next = browseList->next;
					listOfCar->carsRunning--;
					free(browseList);
					return listOfCar;
				}
				else{
					browseListPrevious = browseList;	
					browseList = browseList->next;
				}
			}
			printf("This car does not exist\n");
			return listOfCar;
		}
	}
}

List *moveCar(List *listOfCar,/* int id,*/ char **map, char **circMap, char **staticMap, int mapWidth, int mapHeight, int frame, int kindOfObject){
	Car *movingCar = listOfCar->firstCar;
	char currentChar;
	int trafficLight;

	//Color of traffic light

	if(frame%80 < 30){
		trafficLight = 0;
	}
	else if(frame%80 >=40 && frame%80 < 70){
		trafficLight = 1;
	}
	else{
		trafficLight = 2;
	}

	int randomResult/*, randomResult2*/;
	while(movingCar != NULL){
		//if(movingCar->id == id){
		currentChar = circMap[movingCar->yPos][movingCar->xPos];
		//printf("Voiture %d (%d, %d) : %c\n", movingCar->id, movingCar->xPos, movingCar->yPos, currentChar);

		//RAJOUTER POINTS CRITIQUES POUR AFFICHAGE PASSAGE PIETONS HORIZONTAUX

		if(currentChar == 'C'){
			randomResult = rand()%2;
			//randomResult2 = rand()%2;
			if((movingCar->xPos == 17 && movingCar->yPos == 11) || (movingCar->xPos == 49 && movingCar->yPos == 13) || (movingCar->xPos == 68 && movingCar->yPos == 11)){
				if(randomResult==0){
					currentChar = 'L';
				}
				else{
					currentChar = 'U';
				}
			}
			else if((movingCar->xPos == 45 && movingCar->yPos == 13) || (movingCar->xPos == 87 && movingCar->yPos == 13) || (movingCar->xPos == 84 && movingCar->yPos == 2)){
				if(randomResult==0){
					currentChar = 'D';
				}
				else{
					currentChar = 'L';
				}
			}
			else if((movingCar->xPos == 87 && movingCar->yPos == 19) || (movingCar->xPos == 45 && movingCar->yPos == 29)){
				if(randomResult==0){
					currentChar = 'R';
				}
				else{
					currentChar = 'D';
				}
			}
			else if(movingCar->xPos == 54 && movingCar->yPos == 13){
				if(trafficLight == 1 && (map[15][32] != 'T' && map[15][41] != 'T' && map[17][62] != 'T' && map[17][53] != 'T' && map[17][50] != 'T' && map[19][48] != 'T')){
					currentChar = 'L';
				}
			}
			else if(movingCar->xPos == 92 && movingCar->yPos == 13){
				if(trafficLight == 1 && (map[17][88] != 'T' && map[17][96] != 'T' && map[15][86] != 'T' && map[15][78] != 'T')){
					currentChar = 'L';
				}
			}
			else if(movingCar->xPos == 39 && movingCar->yPos == 29){
				if(trafficLight == 1){
					currentChar = 'R';
				}
			}
			else if(movingCar->xPos == 45 && movingCar->yPos == 10){
				if(trafficLight == 0 && (map[15][32] != 'T' && map[15][41] != 'T' && map[17][62] != 'T' && map[17][53] != 'T' && map[17][50] != 'T' && map[19][48] != 'T')){
					currentChar = 'D';
				}
			}
			else if(movingCar->xPos == 45 && movingCar->yPos == 26){
				if(trafficLight == 0){
					currentChar = 'D';
				}
			}
			else if(movingCar->xPos == 87 && movingCar->yPos == 10){
				if(trafficLight == 0 && (map[17][88] != 'T' && map[17][96] != 'T' && map[15][86] != 'T' && map[15][78] != 'T')){
					currentChar = 'D';
				}
			}
			else if(movingCar->xPos == 49 && movingCar->yPos == 31){
				if(trafficLight == 0){
					currentChar = 'U';
				}
			}
			else if(movingCar->xPos == 49 && movingCar->yPos == 19){
				if(trafficLight == 0 && (map[15][32] != 'T' && map[15][41] != 'T' && map[17][62] != 'T' && map[17][53] != 'T' && map[17][50] != 'T' && map[19][48] != 'T')){
					currentChar = 'U';
				}
			}
			else if(movingCar->xPos == 84 && movingCar->yPos == 11){
				if(randomResult == 0){
					if(trafficLight == 0 && (map[12][87] != 'C' && map[11][87] != 'C' && map[13][87] != 'C')){
						currentChar = 'D';
					}
				}
				else{
					currentChar = 'L';
				}
			}
			else if(movingCar->xPos == 42 && movingCar->yPos == 11){
				if(randomResult == 0 && map[12][45]!='C' && map[11][45]!='C' && map[13][46]!='C' && map[13][47]!='C' && map[13][45]){
					if(trafficLight == 0){
						currentChar = 'D';
					}
				}
				else{
					currentChar = 'L';
				}
			}
			else if(movingCar->xPos == 20 && movingCar->yPos == 9){
				if(randomResult == 0){
					currentChar = 'U';
				}
				else{
					if(map[13][19] != 'C' && map[13][20] != 'C' && map[13][18] != 'C'){
						currentChar = 'L';
					}
				}
			}
			else if(movingCar->xPos == 8 && movingCar->yPos == 27){
				if(map[21][11] != 'C' && map[20][11] != 'C' && map[22][11] != 'C'){
					currentChar = 'R';
				}
			}	
			else if(movingCar->xPos == 42 && movingCar->yPos == 27){
				if(randomResult == 0){
					if(trafficLight == 0){
						currentChar = 'D';
					}
				}
				else{
					if(map[29][42] != 'C' && map[29][40] != 'C' && map[29][41] != 'C' && map[29][38] != 'C' && map[29][37] != 'C' && map[29][36]!= 'C' && trafficLight == 1){
						currentChar = 'R';
					}
				}
			}
			else if(movingCar->xPos == 52 && movingCar->yPos == 31){
				if(map[30][49] != 'C' && map[31][49] != 'C' && map[29][48] != 'C' && map[29][47] != 'C' && trafficLight == 0){
					currentChar = 'U';
				}
			}
			else if(movingCar->xPos == 52 && movingCar->yPos == 11){
				if(randomResult == 0){
					currentChar = 'U';
				}
				else{
					if(map[13][54] != 'C' && map[13][55] != 'C' && map[13][53] != 'C' && trafficLight == 1){
						currentChar = 'L';
					}
				}
			}
			else if(movingCar->xPos == 52 && movingCar->yPos == 18){
				if(trafficLight == 0){
					currentChar = 'U';
				}
			}
			else if(movingCar->xPos == 84 && movingCar->yPos == 27){
				if(map[29][80] != 'C' && map[29][79] != 'C' && map[29][78] != 'C'){
					currentChar = 'D';
				}
			}
			else if(movingCar->xPos == 84 && movingCar->yPos == 20){
				if(randomResult == 0){
					currentChar = 'D';
				}
				else{
					if(map[14][87] != 'C' && map[13][87] != 'C' && map[16][88] != 'C'){
						currentChar = 'R';
					}
				}
			}
			else if(movingCar->xPos == 90 && movingCar->yPos == 11){
				if(trafficLight == 1){
					currentChar = 'L';
				}
			}
			else if((movingCar->xPos == 52 && movingCar->yPos == 27) || (movingCar->xPos == 77 && movingCar->yPos == 27) || (movingCar->xPos == 49 && movingCar->yPos == 29) || (movingCar->xPos == 28 && movingCar->yPos == 27) || (movingCar->xPos == 52 && movingCar->yPos == 2) || (movingCar->xPos == 20 && movingCar->yPos == 7) || (movingCar->xPos == 68 && movingCar->yPos == 6)){
				if(randomResult == 0){
					currentChar = 'R';
				}
				else{
					currentChar = 'U';
				}
			}
			else if((movingCar->xPos == 84 && movingCar->yPos == 22) || (movingCar->xPos == 8 && movingCar->yPos == 17)){
				if(randomResult == 0){
					currentChar = 'L';
				}
				else{
					currentChar = 'D';
				}
			}

			//Middle crosswalk

			else if((movingCar->xPos == 87 && movingCar->yPos == 11) || (movingCar->xPos == 45 && movingCar->yPos == 11)){
				if(map[movingCar->yPos][movingCar->xPos] == 'C'){
					currentChar = 'D';
				}
				else if(map[movingCar->yPos][movingCar->xPos] == 'N'){
					currentChar = 'L';
				}
			}
			else if((movingCar->xPos == 84 && movingCar->yPos == 13) || (movingCar->xPos == 42 && movingCar->yPos == 13)){
				if(map[movingCar->yPos][movingCar->xPos] == 'C'){
					currentChar = 'L';
				}
				else if(map[movingCar->yPos][movingCar->xPos] == 'N'){
					currentChar = 'D';
				}
			}
			else if(movingCar->xPos == 52 && movingCar->yPos == 13){
				if(map[movingCar->yPos][movingCar->xPos] == 'C'){
					currentChar = 'L';
				}
				else if(map[movingCar->yPos][movingCar->xPos] == 'N'){
					currentChar = 'U';
				}
			}
			else if((movingCar->xPos == 49 && movingCar->yPos == 11) || (movingCar->xPos == 17 && movingCar->yPos == 9)){
				if(map[movingCar->yPos][movingCar->xPos] == 'C'){
					currentChar = 'U';
				}
				else if(map[movingCar->yPos][movingCar->xPos] == 'N'){
					currentChar = 'L';
				}
			}
			else if((movingCar->xPos == 11 && movingCar->yPos == 27) || (movingCar->xPos == 45 && movingCar->yPos == 27) || (movingCar->xPos == 87 && movingCar->yPos == 20)){
				if(map[movingCar->yPos][movingCar->xPos] == 'C'){
					currentChar = 'D';
				}
				else if(map[movingCar->yPos][movingCar->xPos] == 'N'){
					currentChar = 'R';
				}
			}
			else if((movingCar->xPos == 42 && movingCar->yPos == 29) || (movingCar->xPos == 84 && movingCar->yPos == 29)){
				if(map[movingCar->yPos][movingCar->xPos] == 'C'){
					currentChar = 'R';
				}
				else if(map[movingCar->yPos][movingCar->xPos] == 'N'){
					currentChar = 'D';
				}
			}
			else if(movingCar->xPos == 49 && movingCar->yPos == 27){
				if(map[movingCar->yPos][movingCar->xPos] == 'C'){
					currentChar = 'U';
				}
				else if(map[movingCar->yPos][movingCar->xPos] == 'N'){
					currentChar = 'R';
				}
			}
			else if(movingCar->xPos == 52 && movingCar->yPos == 29){
				if(map[movingCar->yPos][movingCar->xPos] == 'C'){
					currentChar = 'R';
				}
				else if(map[movingCar->yPos][movingCar->xPos] == 'N'){
					currentChar = 'U';
				}
			}

			//Tramtrack intersection

			else if((movingCar->xPos == 42 && movingCar->yPos == 15) || (movingCar->xPos == 84 && movingCar->yPos == 15)){
				if(map[movingCar->yPos][movingCar->xPos] == 'T'){
					currentChar = 'R';
				}
				else if(map[movingCar->yPos][movingCar->xPos] == 'N'){
					currentChar = 'D';
				}
			}
			else if((movingCar->xPos == 45 && movingCar->yPos == 15) || (movingCar->xPos == 87 && movingCar->yPos == 15)){
				if(map[movingCar->yPos][movingCar->xPos] == 'T'){
					currentChar = 'R';
				}
				else if(map[movingCar->yPos][movingCar->xPos] == 'C'){
					currentChar = 'D';
				}
			}
			else if(movingCar->xPos == 49 && movingCar->yPos == 15){
				if(map[movingCar->yPos][movingCar->xPos] == 'T'){
					currentChar = 'R';
				}
				else if(map[movingCar->yPos][movingCar->xPos] == 'C'){
					currentChar = 'U';
				}
			}
			else if(movingCar->xPos == 52 && movingCar->yPos == 15){
				if(map[movingCar->yPos][movingCar->xPos] == 'T'){
					currentChar = 'R';
				}
				else if(map[movingCar->yPos][movingCar->xPos] == 'N'){
					currentChar = 'U';
				}
			}
			else if((movingCar->xPos == 42 && movingCar->yPos == 17) || (movingCar->xPos == 84 && movingCar->yPos == 17)){
				if(map[movingCar->yPos][movingCar->xPos] == 'T'){
					currentChar = 'L';
				}
				else if(map[movingCar->yPos][movingCar->xPos] == 'N'){
					currentChar = 'D';
				}
			}
			else if((movingCar->xPos == 45 && movingCar->yPos == 17) || (movingCar->xPos == 87 && movingCar->yPos == 17)){
				if(map[movingCar->yPos][movingCar->xPos] == 'T'){
					currentChar = 'L';
				}
				else if(map[movingCar->yPos][movingCar->xPos] == 'C'){
					currentChar = 'D';
				}
			}
			else if(movingCar->xPos == 49 && movingCar->yPos == 17){
				if(map[movingCar->yPos][movingCar->xPos] == 'T'){
					currentChar = 'L';
				}
				else if(map[movingCar->yPos][movingCar->xPos] == 'C'){
					currentChar = 'U';
				}
			}
			else if(movingCar->xPos == 52 && movingCar->yPos == 17){
				if(map[movingCar->yPos][movingCar->xPos] == 'T'){
					currentChar = 'L';
				}
				else if(map[movingCar->yPos][movingCar->xPos] == 'N'){
					currentChar = 'U';
				}
			}

			//Tram stop :

			else if(movingCar->xPos>=62 && movingCar->xPos<=71 && movingCar->yPos==15){
				if(frame%400>=100){
					currentChar = 'R';
				}
				else if(frame%2==0 && frame%400<100){
					currentChar = 'R';
				}
			}
			else if(movingCar->xPos>=63 && movingCar->xPos<=72 && movingCar->yPos==17){
				if(frame%300>=150){
					currentChar = 'L';
				}
				else if(frame%2==0 && frame%300<150){
					currentChar = 'L';
				}
			}
			else if(movingCar->xPos == 52 && movingCar->yPos == 16){
				if(randomResult==0){
					currentChar = 'R';
				}
				else{
					currentChar = 'U';
				}
			}
			else if(movingCar->xPos == 65 && movingCar->yPos == 16){
				if(map[15][62] == 'T' && map[15][72] == 'T'){
					currentChar = 'R';
				}
				else if(map[17][72] == 'T' && map[17][62] == 'T'){
					currentChar = 'R';
				}
			}
			else if(movingCar->xPos == 72 && movingCar->yPos == 15){
				if(frame%400 >= 100){
					currentChar = 'R';
				}
			}
			else if(movingCar->xPos == 62 && movingCar->yPos == 17){
				if(frame%300 >= 150){
					currentChar = 'L';
				}
			}

			//Bridge
			else if(movingCar->xPos == 94 && movingCar->yPos == 23){
				movingCar->level = 0;
				currentChar = 'U';
			}
			else if(movingCar->xPos == 94 && (movingCar->yPos >= 11 && movingCar->yPos <= 20)){
				if(movingCar->level == 0){
					currentChar = 'U';
				}
				else{
					currentChar = movingCar->currentDirection;
				}
			}
			else if(movingCar->xPos == 94 && movingCar->yPos == 10){
				map[movingCar->yPos][movingCar->xPos] == 'C';
				movingCar->level = 1;
				currentChar = 'U';
			}

			else{
				printf("Problème\n");
			}
		}
		//printf("Voiture %d (%d, %d) : %c\n", movingCar->id, movingCar->xPos, movingCar->yPos, currentChar);
		//Next position known :

		if(currentChar == 'L'){
			movingCar->currentDirection = 'L';
			if(movingCar->xPos > 2 && kindOfObject == 0 && (movingCar->yPos==13 || (movingCar->yPos==11 && movingCar->xPos>=52))){
				if(map[movingCar->yPos][movingCar->xPos-1] != 'C' && map[movingCar->yPos][movingCar->xPos-1] != 'N' && map[movingCar->yPos][movingCar->xPos-2] != 'C' && map[movingCar->yPos][movingCar->xPos-2] != 'N' && map[movingCar->yPos][movingCar->xPos-3] != 'C' && map[movingCar->yPos][movingCar->xPos-3] != 'N'){
					map[movingCar->yPos][movingCar->xPos] = staticMap[movingCar->yPos][movingCar->xPos];
					movingCar->xPos-=1;

					//Display of crosswalk
					if(movingCar->xPos < (mapWidth-2)){
						map[movingCar->yPos][movingCar->xPos+1] = ' ';
						map[movingCar->yPos][movingCar->xPos+2] = staticMap[movingCar->yPos][movingCar->xPos+2];
					}
				}
			}
			else{
				if(map[movingCar->yPos][movingCar->xPos-1] != 'C' && map[movingCar->yPos][movingCar->xPos-1] != 'N' && map[movingCar->yPos][movingCar->xPos-1] != 'T'){
					map[movingCar->yPos][movingCar->xPos] = staticMap[movingCar->yPos][movingCar->xPos];
					movingCar->xPos-=1;
				}
			}
		}
		else if(currentChar == 'R'){
			movingCar->currentDirection = 'R';
			if(movingCar->xPos < (mapWidth - 3) && kindOfObject == 0 && (movingCar->yPos==29 || movingCar->yPos==19 || ((movingCar->yPos==12 || movingCar->yPos==18) && movingCar->xPos<=50 && movingCar->xPos>=45))){
				if(map[movingCar->yPos][movingCar->xPos+1] != 'C' && map[movingCar->yPos][movingCar->xPos+1] != 'N' && map[movingCar->yPos][movingCar->xPos+2] != 'C' && map[movingCar->yPos][movingCar->xPos+2] != 'N' && map[movingCar->yPos][movingCar->xPos+3] != 'C' && map[movingCar->yPos][movingCar->xPos+3] != 'N'){
					map[movingCar->yPos][movingCar->xPos] = staticMap[movingCar->yPos][movingCar->xPos];
					movingCar->xPos+=1;
					map[movingCar->yPos][movingCar->xPos+1] = ' ';
				}
			}
			else{
				if(map[movingCar->yPos][movingCar->xPos+1] != 'C' && map[movingCar->yPos][movingCar->xPos+1] != 'N' && map[movingCar->yPos][movingCar->xPos+1] != 'T'){
					map[movingCar->yPos][movingCar->xPos] = staticMap[movingCar->yPos][movingCar->xPos];
					movingCar->xPos+=1;
				}
			}
		}
		else if(currentChar == 'U'){
			movingCar->currentDirection = 'U';

			//Under the bridge
			/*if(movingCar->xPos==94 && movingCar->yPos<=22 && movingCar->yPos>=11){
			  movingCar->yPos-=1;
			  movingCar->level = 0;
			  }
			  else{*/
			if(movingCar->yPos > 1 && kindOfObject == 0 && (movingCar->xPos==94 || movingCar->xPos==17 || movingCar->xPos==49 || movingCar->xPos==45)){
				if(map[movingCar->yPos-1][movingCar->xPos] != 'C' && map[movingCar->yPos-1][movingCar->xPos] != 'N' && map[movingCar->yPos-2][movingCar->xPos] != 'C' && map[movingCar->yPos-2][movingCar->xPos] != 'N'){
					map[movingCar->yPos][movingCar->xPos] = staticMap[movingCar->yPos][movingCar->xPos];
					movingCar->yPos-=1;
					//map[movingCar->yPos-1][movingCar->xPos] = ' ';
				}
			}
			else{
				if(map[movingCar->yPos-1][movingCar->xPos] != 'C' && map[movingCar->yPos-1][movingCar->xPos] != 'N' && map[movingCar->yPos-1][movingCar->xPos] != 'T'){
					map[movingCar->yPos][movingCar->xPos] = staticMap[movingCar->yPos][movingCar->xPos];
					movingCar->yPos-=1;
				}
			}
			//}
		}
		else if(currentChar == 'D'){
			movingCar->currentDirection = 'D';
			if(movingCar->yPos < (mapHeight - 2) && kindOfObject == 0 && (movingCar->xPos==45 || movingCar->xPos==11 || movingCar->xPos==87)){
				if(map[movingCar->yPos+1][movingCar->xPos] != 'C' && map[movingCar->yPos+1][movingCar->xPos] != 'N' && map[movingCar->yPos+2][movingCar->xPos] != 'C' && map[movingCar->yPos+2][movingCar->xPos] != 'N'){
					map[movingCar->yPos][movingCar->xPos] = staticMap[movingCar->yPos][movingCar->xPos];
					movingCar->yPos+=1;
					//map[movingCar->yPos+1][movingCar->xPos] = ' ';
				}
			}
			else{
				if(map[movingCar->yPos+1][movingCar->xPos] != 'C' && map[movingCar->yPos+1][movingCar->xPos] != 'N' && map[movingCar->yPos+1][movingCar->xPos] != 'T'){
					map[movingCar->yPos][movingCar->xPos] = staticMap[movingCar->yPos][movingCar->xPos];
					movingCar->yPos+=1;
				}
			}
		}
		if(kindOfObject == 0 && movingCar->level == 1){
			map[movingCar->yPos][movingCar->xPos] = 'C';
		}
		else if(kindOfObject == 1){
			map[movingCar->yPos][movingCar->xPos] = 'N';
		}
		else if(kindOfObject == 2){
			map[movingCar->yPos][movingCar->xPos] = 'T';
		}
		//return listOfCar;
		//}
		//else{
		movingCar = movingCar->next;
		//}
	}
	//printf("You cannot move a car that does not exist");
	return listOfCar;
}

int* findSpawnPoints(int nbOfSpawns, char** map, int kindOfSpawn){
	int i,j;
	int **spawnPoints = malloc(nbOfSpawns*sizeof(int*));
	for(i=0; i<nbOfSpawns; i++){
		spawnPoints[i] = malloc(2*sizeof(int));
	}
	FILE *fichier = NULL;
	if(kindOfSpawn == 0){
		fichier = fopen("spawnPoints.txt", "r");
	}
	else if(kindOfSpawn == 1){
		fichier = fopen("pedestrianSpawnPoints.txt", "r");
	}
	else if(kindOfSpawn == 2){
		fichier = fopen("dangerousSpawnPoints.txt", "r");
	}
	if(fichier != NULL){
		for(i=0; i<nbOfSpawns; i++){
			for(j=0; j<2; j++){
				fscanf(fichier, "%d", &spawnPoints[i][j]);
			}
		}
	}
	fclose(fichier);
	int randSpawn = rand()%nbOfSpawns;
	int spawnOnTram = rand()%3;
	if(kindOfSpawn==1 && spawnOnTram==1 && ((map[15][62]=='T' && map[15][72]=='T') || (map[17][62]=='T' && map[17][72]=='T'))){
		spawnPoints[randSpawn][0] = 69;
		spawnPoints[randSpawn][1] = 16;
	}
	return spawnPoints[randSpawn];
}

List *killVehicles(List *listOfCar, int nbOfDeathPoints, char **map, char **staticMap, int kindOfObject){
	int i,j;
	int **deathPoints = malloc(nbOfDeathPoints*sizeof(int*));
	for(i=0; i<nbOfDeathPoints; i++){
		deathPoints[i] = malloc(2*sizeof(int));
	}
	FILE *fichier = NULL;
	if(kindOfObject == 0){
		fichier = fopen("deathPoints.txt", "r");
		nbOfDeathPoints--;
	}
	else if(kindOfObject == 1){
		fichier = fopen("pedestrianDeathPoints.txt", "r");
	}
	else if(kindOfObject == 2){
		fichier = fopen("tramDeathPoints.txt", "r");
	}
	if(fichier != NULL){
		for(i=0; i<nbOfDeathPoints; i++){
			for(j=0; j<2; j++){
				fscanf(fichier, "%d", &deathPoints[i][j]);
			}
		}
	}
	fclose(fichier);
	Car *car = listOfCar->firstCar;
	while(car != NULL){
		for(i=0; i<nbOfDeathPoints; i++){
			if(car->xPos == deathPoints[i][0] && car->yPos == deathPoints[i][1]){
				listOfCar = deleteCar(listOfCar, car->id);
			}
		}
		car = car->next;		
	}
	return listOfCar;
}

char **clearDeadVehicles(char **map, char **staticMap, int nbOfDeathPoints, int kindOfObject){
	int i,j;
	int **deathPoints = malloc(nbOfDeathPoints*sizeof(int*));
	for(i=0; i<nbOfDeathPoints; i++){
		deathPoints[i] = malloc(2*sizeof(int));
	}
	FILE *fichier = NULL;
	if(kindOfObject == 0){
		fichier = fopen("deathPoints.txt", "r");
	}
	else if(kindOfObject == 1){
		fichier = fopen("pedestrianDeathPoints.txt", "r");
	}
	else if(kindOfObject == 2){
		fichier = fopen("tramDeathPoints.txt", "r");
	}
	if(fichier != NULL){
		for(i=0; i<nbOfDeathPoints; i++){
			for(j=0; j<2; j++){
				fscanf(fichier, "%d", &deathPoints[i][j]);
			}
			map[deathPoints[i][1]][deathPoints[i][0]] = staticMap[deathPoints[i][1]][deathPoints[i][0]];
		}
	}
	fclose(fichier);
	return map;
}


int idIsFree(List *listOfCar, int id){
	Car *car = listOfCar->firstCar;
	while(car != NULL){
		if(car->id == id){
			return 0;
		}
		else{
			car = car->next;
		}
	}
	return 1;
}

int findFreeId(List *listOfCar, int maxNumberOfCars){
	int isFree = 0;
	int freeId = 0;
	while(isFree == 0 && freeId != maxNumberOfCars){
		isFree = idIsFree(listOfCar, freeId);
		if(isFree == 1){
			return freeId;
		}

		else{
			freeId++;
		}
	}
	return -1;
}

List *createVehicle(List *listOfCar, int *spawnPoint, int maxNumberOfCars, int nbOfSpawnPoints, char **map){
	int freeId = 0;
	spawnPoint = findSpawnPoints(nbOfSpawnPoints, map, 0);
	if(listOfCar->carsRunning < maxNumberOfCars){
		freeId = findFreeId(listOfCar, maxNumberOfCars);
		if(freeId >= 0){
			listOfCar = createCar(listOfCar, spawnPoint[0], spawnPoint[1], freeId, map, 0);
		}
		//freeId = 0;
	}
	return listOfCar;
}

List *createPedestrian(List *listOfPedestrian, int *pedestrianSpawnPoint, int maxNumberOfPedestrians, int nbOfPedestrianSpawnPoints, char **map){
	int freeId = 0;
	pedestrianSpawnPoint = findSpawnPoints(nbOfPedestrianSpawnPoints, map, 1);
	if(listOfPedestrian->carsRunning < maxNumberOfPedestrians){
		freeId = findFreeId(listOfPedestrian, maxNumberOfPedestrians);
		if(freeId >= 0){
			listOfPedestrian = createCar(listOfPedestrian, pedestrianSpawnPoint[0], pedestrianSpawnPoint[1], freeId, map, 1);
		}
		//freeId = 0;
	}
	return listOfPedestrian;
}

List *createTram(List *listOfTram, char **map, int frame){
	int i;
	if((frame%400) >=0 && (frame%400) < 11){
		i = frame%400;
		listOfTram = createCar(listOfTram, 14, 15, i, map, 2);
	}
	else if((frame%300) >= 50 && (frame%300) < 61){
		i = frame%300 - 50;
		listOfTram = createCar(listOfTram, 118, 17, 10-i, map, 2);
	}
	return listOfTram;
}

List* moveDangerousCar(List *listOfCar, char **map, char **circMap, char **staticMap, int mapWidth, int mapHeight, int frame, int kindOfObject){
	if(frame<=31 && frame >=18){
		Car *movingCar = listOfCar->firstCar;
		movingCar->currentDirection = 'D';
		map[movingCar->yPos][movingCar->xPos] = staticMap[movingCar->yPos][movingCar->xPos];
		movingCar->yPos+=1;
		map[movingCar->yPos][movingCar->xPos] = 'C';
	}
	return listOfCar;
}

void menu(){
	int choice = 0;
	system("clear");
	char touche1;
	char touche2;
	char touche3;
	int mapWidth = 119;
	int mapHeight = 36; 
	int frame = 0;	
	displayMenuMap(mapHeight, mapWidth, frame);
	printf("\033[%d;%dHNaviguer avec 🡱  et  🡳", 23, 48);
	printf("\033[%d;%dHValider avec Entrée", 24, 50);
	printf("\033[%d;%dHBienvenue à Segmentation City", 2, 46);
	while(frame>=0){
		if(choice==0){
			color("47;30");
			printf("\033[%d;%dH Mode fluide ", 16, 54);
			color("0");
			printf("\033[%d;%dH Mode danger ", 18, 54);
			printf("\033[%d;%dH  Quitter(Q) ", 20, 54);
		}
		if(choice==1){
			printf("\033[%d;%dH Mode fluide ", 16, 54);
			color("47;30");
			printf("\033[%d;%dH Mode danger ", 18, 54);
			color("0");
			printf("\033[%d;%dH  Quitter(Q) ", 20, 54);
		}
		else if(choice==2){
			printf("\033[%d;%dH Mode fluide ", 16, 54);
			printf("\033[%d;%dH Mode danger ", 18, 54);
			color("47;30");
			printf("\033[%d;%dH  Quitter(Q) ", 20, 54);
			color("0");
		}
		printf("\033[%d;%dH         ", 37, 0);
		printf("\033[%d;%dH", 37, 0);
		touche1 = key_pressed();
		touche2 = key_pressed();
		touche3 = key_pressed();

		if(touche1 == '\033' && touche2 == '[' && touche3 == 'A'/* && touche4 == 'A'*/){
			if(choice==0){
				choice=2;
			}
			else{
				choice--;
			}
		}
		else if(touche1 == '\033' && touche2 == '[' && touche3 == 'B'/* && touche4 == 'B'*/){
			//dangerMode();
			choice++;
		}
		else if(touche1 == '\n' || touche2 == '\n' || touche3 == '\n'/* || touche4 == 'q'*/){
			if(choice == 0){
				launch();
			}
			else if(choice == 1){
				dangerMode();
			}
			else{
				system("clear");
				exit(0);
			}
		}
		else if(touche1 == 'q' || touche2 == 'q' || touche3 == 'q'/* || touche4 == 'q'*/){
			system("clear");
			exit(0);
		}
		choice+=3;
		choice = choice%3;
		frame++;
	}
}


void launch(){
	int mapWidth = 119;
	int mapHeight = 36;
	int maxNumberOfCars = 50;
	int maxNumberOfPedestrians = 20;
	int i,j;
	int frame = 0;
	char key;
	srand(time(NULL));

	//Allocation de la matrice contenant la map
	char **map = malloc(mapHeight*sizeof(char*));
	char **staticMap = malloc(mapHeight*sizeof(char*));
	char **circMap = malloc(mapHeight*sizeof(char*));
	for(i=0; i<mapHeight; i++){
		map[i] = malloc((mapWidth+1)*sizeof(char));
		circMap[i] = malloc((mapWidth+1)*sizeof(char));
		staticMap[i] = malloc((mapWidth+1)*sizeof(char));
	}

	map = loadmap(mapWidth, mapHeight, 0, map);
	staticMap = loadmap(mapWidth, mapHeight, 0, staticMap);
	circMap = loadmap(mapWidth, mapHeight, 1, circMap);

	//Déclaration des spawns des véhicules
	int nbOfSpawnPoints = 6;
	int nbOfDeathPoints = 7;
	int nbOfPedestrianSpawnPoints = 10;
	int nbOfPedestrianDeathPoints = 11;
	int nbOfTramDeathPoints = 2;
	int *spawnPoint = malloc(nbOfSpawnPoints*sizeof(int));
	int *pedestrianSpawnPoint = malloc(nbOfSpawnPoints*sizeof(int));

	//Initialisation et remplissage des listes chaînées
	List* listOfCar = initiateList();
	List* listOfPedestrian = initiateList();
	List* listOfTram = initiateList();
	displayList(listOfCar);
	while(key != 'q'){
		key = key_pressed();
		listOfCar = createVehicle(listOfCar, spawnPoint, maxNumberOfCars, nbOfSpawnPoints, map);
		listOfPedestrian = createPedestrian(listOfPedestrian, pedestrianSpawnPoint, maxNumberOfPedestrians, nbOfPedestrianSpawnPoints, map);
		for(j=0; j<3; j++){
			listOfTram = createTram(listOfTram, map, frame);

			moveCar(listOfCar, map, circMap, staticMap, mapWidth, mapHeight, frame, 0);
			if(frame%2==0){
				moveCar(listOfPedestrian, map, circMap, staticMap, mapWidth, mapHeight, frame, 1);
			}
			moveCar(listOfTram, map, circMap, staticMap, mapWidth, mapHeight, frame, 2);

			//Map display :
			system("clear");
			displayMap(mapWidth, mapHeight, map, circMap, listOfCar, listOfTram, frame);
			usleep(100000);

			//Dead vehicles cleaning :
			listOfCar = killVehicles(listOfCar, nbOfDeathPoints, map, staticMap, 0);
			listOfPedestrian = killVehicles(listOfPedestrian, nbOfPedestrianDeathPoints, map, staticMap, 1);
			listOfTram = killVehicles(listOfTram, nbOfTramDeathPoints, map, staticMap, 2);
			map = clearDeadVehicles(map, staticMap, nbOfDeathPoints, 0);	
			map = clearDeadVehicles(map, staticMap, nbOfPedestrianDeathPoints, 1);
			map = clearDeadVehicles(map, staticMap, nbOfTramDeathPoints, 2);

			frame++;
		}

	}
	menu();
}

void dangerMode(){
	//pertubatedCirc:
	int mapWidth = 119;
	int mapHeight = 36;
	int maxNumberOfCars = 50;
	int maxNumberOfPedestrians = 20;
	int i,j;
	int frame = 0;
	char key;
	srand(time(NULL));

	//Allocation de la matrice contenant la map
	char **map = malloc(mapHeight*sizeof(char*));
	char **staticMap = malloc(mapHeight*sizeof(char*));
	char **circMap = malloc(mapHeight*sizeof(char*));
	char **emergencyCircMap = malloc(mapHeight*sizeof(char*));
	char **dangerousCircMap = malloc(mapHeight*sizeof(char*));
	for(i=0; i<mapHeight; i++){
		map[i] = malloc((mapWidth+1)*sizeof(char));
		circMap[i] = malloc((mapWidth+1)*sizeof(char));
		staticMap[i] = malloc((mapWidth+1)*sizeof(char));
		emergencyCircMap[i] = malloc((mapWidth+1)*sizeof(char));
		dangerousCircMap[i] = malloc((mapWidth+1)*sizeof(char));
	}

	map = loadmap(mapWidth, mapHeight, 0, map);
	staticMap = loadmap(mapWidth, mapHeight, 0, staticMap);
	circMap = loadmap(mapWidth, mapHeight, 1, circMap);
	emergencyCircMap = loadmap(mapWidth, mapHeight, 2, emergencyCircMap);
	dangerousCircMap = loadmap(mapWidth, mapHeight, 3, dangerousCircMap);


	//Déclaration des spawns des véhicules
	int nbOfSpawnPoints = 7;
	int nbOfDeathPoints = 7;
	int nbOfPedestrianSpawnPoints = 10;
	int nbOfPedestrianDeathPoints = 11;
	int nbOfTramDeathPoints = 2;
	int *spawnPoint = malloc(nbOfSpawnPoints*sizeof(int));
	int *pedestrianSpawnPoint = malloc(nbOfSpawnPoints*sizeof(int));

	//Initialisation et remplissage des listes chaînées
	List* listOfCurrentlyRunning = initiateList();
	List* listOfPedestrian = initiateList();
	List* listOfTram = initiateList();

	//Accident scene:
	while(key != 'q'){
		key = key_pressed();
		if(frame <= 60){
			listOfTram = createTram(listOfTram, map, frame);
			if(frame == 18){
				listOfCurrentlyRunning = createCar(listOfCurrentlyRunning, 45, 0, 0, map, 0);
			}
			moveDangerousCar(listOfCurrentlyRunning, map, circMap, staticMap, mapWidth, mapHeight, frame, 0);
			if(frame<=33){
				moveCar(listOfTram, map, circMap, staticMap, mapWidth, mapHeight, frame, 2);
			}
			if(frame==33){
				//Delete the burning car to replace it by emergency
				listOfCurrentlyRunning = clearList(listOfCurrentlyRunning, map);
				map[14][43] = 'z';
				map[14][46] = 'z';
				map[15][45] = 'z';
				map[15][46] = 'z';
				map[15][44] = 'z';
			}
		}

		if(frame <= 170 && frame >= 50){
			if(frame%20 == 0 && frame<130){
				listOfCurrentlyRunning = createCar(listOfCurrentlyRunning, 45, 0, (frame-50)/10, map, 3);
			}
			else if(frame%20 == 10 && frame<130){
				listOfCurrentlyRunning = createCar(listOfCurrentlyRunning, 49, 35, (frame-50)/10, map, 3);
			}
			if(frame==170){
				listOfCurrentlyRunning = clearList(listOfCurrentlyRunning, map);
			}
			moveCar(listOfCurrentlyRunning, map, emergencyCircMap, staticMap, mapWidth, mapHeight, frame, 0);
		}
		if(frame >= 170){
			if(frame%3 == 0){	
				listOfCurrentlyRunning = createVehicle(listOfCurrentlyRunning, spawnPoint, maxNumberOfCars, nbOfSpawnPoints, map);
			}
			moveCar(listOfCurrentlyRunning, map, dangerousCircMap, staticMap, mapWidth, mapHeight, frame, 0);
			listOfCurrentlyRunning = killVehicles(listOfCurrentlyRunning, nbOfDeathPoints, map, staticMap, 0);
			map = clearDeadVehicles(map, staticMap, nbOfDeathPoints, 0);
		}
		system("clear");
		displayMap(mapWidth, mapHeight, map, circMap, listOfCurrentlyRunning, listOfTram, frame);
		usleep(100000);
		frame++;
	}
	menu();
}
