#include "gamebase.h" 
#include "gamelogic.h"
#include "IOput.h"
#include <math.h>

MainMenuSelection getMainMenuInput(SDL_Event *eventMain, MainMenuSelection selection, renderAssets *renderAsset){
	if (eventMain->type == SDL_KEYDOWN) {
		switch (eventMain->key.keysym.sym) {
		case SDLK_UP:
			selection -= 1;
			if (selection == notvalidinput) {
				playSFX(renderAsset->sounds->menu_move);
				return quitgame;
			}
			playSFX(renderAsset->sounds->menu_move);
			return selection;
			break;
		case SDLK_DOWN:
			selection += 1;
			if (selection == valaszt) {
				playSFX(renderAsset->sounds->menu_move);
				return singleplayer;
			}
			playSFX(renderAsset->sounds->menu_move);
			return selection;
			break;
		case SDLK_RETURN:
			playSFX(renderAsset->sounds->menu_choose);
			return valaszt;
			break;
		default:
			return selection;
			break;
		}
	}
	else return selection; 
}

Place **readTopList(int placementNumber){
	
	Place **topList = (Place**) malloc(placementNumber * sizeof(Place*));

	for (int i = 0; i < placementNumber; i++){
		topList[i] = (Place*) malloc(1 * sizeof(Place));
	}

	FILE *eredmenyek;

	eredmenyek = fopen("Eredmények.txt", "rt");
	if (eredmenyek == NULL) {
		printf("Eredmények.txt could not open!\n");
		return NULL;
	}
	char read;
	for (int i = 0; i < placementNumber; i++) {
		fscanf(eredmenyek, "%c", &read);
		char *placementNumberString = (char*)malloc(1 * sizeof(char));
		placementNumberString[0] = '\0';
		while (read != '\t') {
			placementNumberString = remakeDynString(read, placementNumberString);
			fscanf(eredmenyek, "%c", &read);
		}
		topList[i]->placement = numFromString(placementNumberString);

		char *placementName = (char*)malloc(1 * sizeof(char));
		placementName[0] = '\0';
		fscanf(eredmenyek, "%c", &read);
		while (read != '\t') {
			placementName = remakeDynString(read, placementName);
			fscanf(eredmenyek, "%c", &read);
		}
		topList[i]->name = placementName;

		char *placementPointsString = (char*)malloc(1 * sizeof(char));
		placementPointsString[0] = '\0';
		fscanf(eredmenyek, "%c", &read);
		while (read != '\n' && read != ';') {
			placementPointsString = remakeDynString(read, placementPointsString);
			fscanf(eredmenyek, "%c", &read);
		}
		topList[i]->points = numFromString(placementPointsString);
	}
	fclose(eredmenyek);
	return topList;
}

char *remakeDynString(char newchar, char *string) {
	if (string == NULL){
		char *newDynString = (char*) malloc(2 * sizeof(char));
		newDynString[0] = newchar;
		newDynString[1] = '\0';
		return newDynString;
	}
	else{
		char *newDynString = (char*) malloc((strlen(string) + 2) * sizeof(char));
		char tmp[] = {newchar,'\0'};
		strcpy(newDynString, string);
		strcat(newDynString, tmp);
		free(string);
		return newDynString;
	}
}

char *removeDynStringLastChar(char *string) {
	if (string == NULL){
		return NULL;
	}
	else if(strlen(string) == 1){
		free(string);
		return NULL;
	}
	else{
		char *newDynString = (char*) malloc((strlen(string)) * sizeof(char));
		for (int i = 0; i  < (int)strlen(string) - 1; i++) {
			newDynString[i] = string[i];
		}
		newDynString[strlen(string)-1] = '\0';
		free(string);
		return newDynString;
	}
}


int numFromString(char *string){
	int number = 0, length = strlen(string)-1;
	for (int i = 0; i < (int)strlen(string); i++){
		if (string[i] != '\0')
			number += (string[i] - '0') * (int)pow(10,(double)length--);
	}
	free(string);
	return number;
}

void freePlaceStructArray(Place **list, int size) {
	for (int i = size-1; i >= 0; i--) {
		free(list[i]->name);
		free(list[i]);
	}
	free(list); 
}

void placeStructArraySelectionSort(Place **list, int size){
	for (int i = 0; i < size-1; i++) {
		int minIndex = i;
		for (int n = i + 1; n < size; n++)
			if (list[n]->points > list[minIndex]->points)
				minIndex = n;
		if (minIndex != i) {
			int tmpInt = list[i]->points;
			char *tmpString = list[i]->name;
			list[i]->points = list[minIndex]->points;
			list[i]->name = list[minIndex]->name;
			list[minIndex]->points = tmpInt;
			list[minIndex]->name = tmpString;
		}
	}
}

void writeTopList(Place **list, int size) {
	FILE *eredmenyek;

	eredmenyek = fopen("Eredmények.txt", "wt");
	if (eredmenyek == NULL) {
		printf("Eredmények.txt could not open!\n");
		return;
	}

	for (int i = 0; i < size-1; i++) {
		fprintf(eredmenyek,"%d\t%s\t%d\n", list[i]->placement, list[i]->name, list[i]->points);
	}
	fprintf(eredmenyek,"%d\t%s\t%d;", list[size-1]->placement, list[size - 1]->name, list[size - 1]->points);

	fclose(eredmenyek);
}

Place **remakeDynPlaceStructArray(Place **oldArray, int size){
	Place **newArray = (Place**) malloc((size + 1) * sizeof(Place*));
	for (int i = 0; i < size + 1; i++) {
		newArray[i] = (Place*)malloc(1 * sizeof(Place));
	}

	for (int i = 0; i < size; i++) {
		newArray[i]->name = oldArray[i]->name;

		char *filler = (char*)malloc(2 * sizeof(char));
		filler[0] = '-';
		filler[1] = '\0';
		oldArray[i]->name = filler;
	
		newArray[i]->placement = oldArray[i]->placement;
		newArray[i]->points = oldArray[i]->points;
	}

	freePlaceStructArray(oldArray,size);

	return newArray;
}

char *duplicateDynString(const char* string) {
	char *duplicate = (char*)malloc(strlen(string) +1 * sizeof(char));
	strcpy(duplicate, string);
	return duplicate;
}

char getSDLInputABC(SDL_Event *eventInput) {
	if (eventInput->type == SDL_KEYDOWN) {
		switch (eventInput->key.keysym.sym) {
		case SDLK_a:
			return 'A';
			break;
		case SDLK_b:
			return 'B';
			break;
		case SDLK_c:
			return 'C';
			break;
		case SDLK_d:
			return 'D';
			break;
		case SDLK_e:
			return 'E';
			break;
		case SDLK_f:
			return 'F';
			break;
		case SDLK_g:
			return 'G';
			break;
		case SDLK_h:
			return 'H';
			break;
		case SDLK_i:
			return 'I';
			break;
		case SDLK_j:
			return 'J';
			break;
		case SDLK_k:
			return 'K';
			break;
		case SDLK_l:
			return 'L';
			break;
		case SDLK_m:
			return 'M';
			break;
		case SDLK_n:
			return 'N';
			break;
		case SDLK_o:
			return 'O';
			break;
		case SDLK_p:
			return 'P';
			break;
		case SDLK_q:
			return 'Q';
			break;
		case SDLK_r:
			return 'R';
			break;
		case SDLK_s:
			return 'S';
			break;
		case SDLK_t:
			return 'T';
			break;
		case SDLK_u:
			return 'U';
			break;
		case SDLK_v:
			return 'V';
			break;
		case SDLK_w:
			return 'W';
			break;
		case SDLK_x:
			return 'X';
			break;
		case SDLK_y:
			return 'Y';
			break;
		case SDLK_z:
			return 'Z';
			break;
		case SDLK_RETURN:
			return '1';
			break;
		case SDLK_BACKSPACE:
			return '3';
			break;
		default:
			return '0';
			break;
		}
	}
	else return '2';
	return '2';
}

char **readLevel(const char* filePath, LevelDimensions *dim){
	FILE *level;

	level = fopen(filePath, "rt");
	if (level == NULL) {
		printf("%s could not open!\n", filePath);
		return NULL;
	}

	int size;
	fscanf(level, "%d", &size);

	dim->colums = size;
	dim->rows = size + 1;

	

	char **newArray = (char**)malloc(dim->colums * sizeof(char*));

	for (int i = 0; i <dim->colums; i++) {
		newArray[i] = (char*)malloc(dim->rows * sizeof(char));
	}
	
	fscanf(level, "%c", &newArray[0][0]);

	for (int x = 0; x < dim->colums; x++) {
		for (int y = 0; y < dim->rows; y++) {
			fscanf(level, "%c", &newArray[x][y]);
		}
	}

	fclose(level);
	return newArray;
}

void free2DCharArray(char **array,int columSize){
	for (int i = 0; i < columSize; i++) {
			free(array[i]);
	}
	free(array);
	array = NULL;
}

TileType **mapConverter(char **arrayBase, LevelDimensions size) {

	
	for (int x = 0; x < size.colums; x++) {
		for (int y = 0; y < size.rows; y++) {
			if (arrayBase[x][y] == '0' || arrayBase[x][y] == '1');
			else {
				printf("Error: Invalid input! array[%d][%d]\n", x, y);
				arrayBase[x][y] = '0';
			}
		}
	}

	TileType **newArray = (TileType**)malloc(size.colums * sizeof(TileType*));
	for (int i = 0; i < size.colums; i++) {
		newArray[i] = (TileType*)malloc(size.rows * sizeof(TileType));
	}

	for (int x = 0; x < size.colums; x++) {
		for (int y = 0; y < size.rows; y++) {

			char left, right, up, down;

			if (y - 1 >= 0)
				left = arrayBase[x][y - 1];
			else left = '0';

			if (y + 1 < size.rows)
				right = arrayBase[x][y + 1];
			else right = '0';

			if (x - 1 >= 0)
				up = arrayBase[x - 1][y];
			else up = '0';

			if (x + 1 < size.colums)
				down = arrayBase[x + 1][y];
			else down = '0';

			if (arrayBase[x][y] == '0')
				newArray[x][y] = path_point;
			else if (right == '0' && left == '0' && down == '0' && up == '0')
				newArray[x][y] = wall_0;

			else if (right == '0' && left == '0' && down == '0' && up == '1')
				newArray[x][y] = wall_1_up;
			else if (right == '0' && left == '0' && down == '1' && up == '0')
				newArray[x][y] = wall_1_down;
			else if (right == '0' && left == '1' && down == '0' && up == '0')
				newArray[x][y] = wall_1_left;
			else if (right == '1' && left == '0' && down == '0' && up == '0')
				newArray[x][y] = wall_1_right;

			else if (right == '1' && left == '1' && down == '0' && up == '0')
				newArray[x][y] = wall_2_hor;
			else if (right == '0' && left == '0' && down == '1' && up == '1')
				newArray[x][y] = wall_2_vert;

			else if (right == '1' && left == '0' && down == '0' && up == '1')
				newArray[x][y] = wall_2_u_r;
			else if (right == '0' && left == '1' && down == '0' && up == '1')
				newArray[x][y] = wall_2_u_l;
			else if (right == '1' && left == '0' && down == '1' && up == '0')
				newArray[x][y] = wall_2_d_r;
			else if (right == '0' && left == '1' && down == '1' && up == '0')
				newArray[x][y] = wall_2_d_l;

			else if (right == '1' && left == '1' && down == '1' && up == '0')
				newArray[x][y] = wall_3_up;
			else if (right == '1' && left == '1' && down == '0' && up == '1')
				newArray[x][y] = wall_3_down;
			else if (right == '1' && left == '0' && down == '1' && up == '1')
				newArray[x][y] = wall_3_left;
			else if (right == '0' && left == '1' && down == '1' && up == '1')
				newArray[x][y] = wall_3_right;
			else if (right == '1' && left == '1' && down == '1' && up == '1')
				newArray[x][y] = wall_4;
			else newArray[x][y] = path_point;
		}
	}
	return newArray;
}

char* makeDynString(int size) {
	char *tmp = (char*)malloc(size * sizeof(char));
	return tmp;
}

void freeLevel(Level *level) {
	for (int i = 0; i < level->dimension.colums; i++){
		free(level->map[i]);
	}
	free(level->map);

	free(level);
	level = NULL;
}

char charFromNum(int number){
	return number + '0';
}

windowData getWindowData(void) {
	windowData tmp;
	tmp.res = getResolutionFromConsole();
	tmp.isFullscreen = getFullsreenFromConsole();
	return tmp;
}

void renderConsoleP3Kmen(void){
	printf( "X----------------------------------------------------X\n"
			"|    _____   ____   _  __                            |\n"
			"|   |  __ \\ |___ \\ | |/ /                            |\n"
			"|   | |__)|  __) | | ' /   _ __ ___    ___  _ __     |\n"
			"|   |  ___/  |__ < |  <   | '_ \\ _ \\  / _ \\| '_ \\    |\n"
			"|   | |      ___)| | . \\  | | | | | ||  __/| | | |   |\n"
			"|   |_|     |____/ |_|\\_\\ |_| |_| |_| \\___||_| |_|   |\n"
			"|                                                    |\n"
			"X----------------------------------------------------X\n");
}

void renderConsoleResChooseMenu(void){
	printf( "|                                                    |\n"
			"|             Kerlek valassz felbontast:             |\n"
			"|           ------------------------------           |\n"
			"|                                                    |\n"
			"|                  (1): 1920 x 1080                  |\n"
			"|                  (2): 1600 x  900                  |\n"
			"|                  (3): 1280 x  720                  |\n"
			"|                  (4):  768 x  432                  |\n"
			"|                                                    |\n"
			"X----------------------------------------------------X\n\n"
	        "                     valaszod: ");
}

void renderConsoleFullscreenChooseMenu(void) {
	printf( "|                                                    |\n"
			"|          Teljes kepernyon akarsz jatszani?         |\n"
			"|        -------------------------------------       |\n"
			"|                                                    |\n"
			"|                      (y): igen                     |\n"
			"|                      (n): nem                      |\n"
			"|                                                    |\n"
			"X----------------------------------------------------X\n\n"
			"                      valaszod: ");
}

Resolution getResolutionFromConsole(void) {
	int consoleInput;
	renderConsoleP3Kmen();
	renderConsoleResChooseMenu();

	scanf("%d", &consoleInput);
	while (consoleInput != 1 && consoleInput != 2 && consoleInput != 3 && consoleInput != 4) {
		system("cls");
		renderConsoleP3Kmen();
		renderConsoleResChooseMenu();
		scanf("%d", &consoleInput);
	}
	system("cls");
	switch (consoleInput) {
		case 1:
			return _1920x1080;
			break;
		case 2:
			return _1600x900;
			break;
		case 3:
			return _1280x720;
			break;
		case 4:
			return _768x432;
			break;
	}
	return _1280x720;
}

bool getFullsreenFromConsole(void) {
	int consoleInput = getchar();
	while (consoleInput != 'n' && consoleInput != 'N' && consoleInput != 'y' && consoleInput != 'Y') {
		system("cls");
		renderConsoleP3Kmen();
		renderConsoleFullscreenChooseMenu();
		consoleInput = getchar();
	}
	system("cls");

	switch (consoleInput) {
		case 'y':
		case 'Y':
			return true;
			break;
		case 'n':
		case 'N':
			return false;
			break;
	}
	return false;
}