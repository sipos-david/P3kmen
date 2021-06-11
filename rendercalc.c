#include "gamebase.h"
#include "rendercalc.h"


initMainMenuCoords getMainMenuCoords(int SCREEN_HEIGHT, int SCREEN_WIDTH){
	initMainMenuCoords mainMenu;
	initMainMenuBaseGridSizes size = getMainMenuBaseGridSizes(SCREEN_HEIGHT, SCREEN_WIDTH);

	int x = SCREEN_WIDTH * 7/16;
	int y = SCREEN_HEIGHT * 1/8;

	mainMenu.logo.x = SCREEN_WIDTH*3/8;
	mainMenu.logo.y = SCREEN_HEIGHT/8;
	mainMenu.logo.w = size.width * 2;
	mainMenu.logo.h = size.height *2;

	mainMenu.singleplayer.x = x;
	mainMenu.singleplayer.y = 3 * y;
	mainMenu.singleplayer.w = size.width;
	mainMenu.singleplayer.h = size.height;

	mainMenu.multiplayer.x = x;
	mainMenu.multiplayer.y = 4 * y;
	mainMenu.multiplayer.w = size.width;
	mainMenu.multiplayer.h = size.height;

	mainMenu.toplist.x = x;
	mainMenu.toplist.y = 5 * y;
	mainMenu.toplist.w = size.width;
	mainMenu.toplist.h = size.height;

	mainMenu.quit.x = x;
	mainMenu.quit.y = 6 * y;
	mainMenu.quit.w = size.width;
	mainMenu.quit.h = size.height;

	return mainMenu;
}

initTopListCoords getTopListCoords(int SCREEN_HEIGHT, int SCREEN_WIDTH,int fontSize) {
	initTopListCoords topList;
	initMainMenuBaseGridSizes size = getMainMenuBaseGridSizes(SCREEN_HEIGHT, SCREEN_WIDTH);

	topList.toplistTitle.x = SCREEN_WIDTH * 3 / 8;
	topList.toplistTitle.y = SCREEN_HEIGHT / 8;
	topList.toplistTitle.w = size.width * 2;
	topList.toplistTitle.h = size.height * 2;

	topList.placementsBase.x = SCREEN_WIDTH / 4;
	topList.placementsBase.y = SCREEN_HEIGHT / 8 + size.height * 2;
	topList.placementsBase.w = SCREEN_WIDTH / 2;
	topList.placementsBase.h = fontSize;

	return topList;
}

initGetDifficultyCoords getGetDifficultyCoords(renderAssets *renderAsset, const char* difTextString, const char *easyString, const char *normalString, const char *hardString) {
	initGetDifficultyCoords tmp;

	tmp.difText.x = renderAsset->renderer->SCREEN_WIDTH / 2 - strlen(difTextString) / 2 * renderAsset->font->size;
	tmp.difText.y = renderAsset->renderer->SCREEN_HEIGHT / 4 - renderAsset->font->size / 2;
	tmp.difText.w = strlen(difTextString) * renderAsset->font->size;
	tmp.difText.h = renderAsset->font->size;

	tmp.difNormalText.x = renderAsset->renderer->SCREEN_WIDTH / 2 - strlen(normalString) / 2 * renderAsset->font->size;
	tmp.difNormalText.y = renderAsset->renderer->SCREEN_HEIGHT / 2 - renderAsset->font->size / 2;
	tmp.difNormalText.w = strlen(normalString) * renderAsset->font->size; ;
	tmp.difNormalText.h = renderAsset->font->size;

	tmp.difEasyText.x = renderAsset->renderer->SCREEN_WIDTH / 4 - strlen(easyString) / 2 * renderAsset->font->size;
	tmp.difEasyText.y = tmp.difNormalText.y;
	tmp.difEasyText.w = strlen(easyString) * renderAsset->font->size;;
	tmp.difEasyText.h = renderAsset->font->size;

	tmp.difHardText.x = renderAsset->renderer->SCREEN_WIDTH / 4 * 3 - strlen(hardString) / 2 * renderAsset->font->size;
	tmp.difHardText.y = tmp.difNormalText.y;
	tmp.difHardText.w = strlen(hardString) * renderAsset->font->size;;
	tmp.difHardText.h = renderAsset->font->size;

	tmp.selectionClear.x = tmp.difEasyText.x;
	tmp.selectionClear.y = tmp.difEasyText.y + renderAsset->font->size;
	tmp.selectionClear.w = tmp.difHardText.x;

	return tmp;
}

initMainMenuBaseGridSizes getMainMenuBaseGridSizes(int SCREEN_HEIGHT, int SCREEN_WIDTH) {
	// aspect ratio == 16 : 9 base = 1280 * 720

	initMainMenuBaseGridSizes size;
	size.width = 160;
	size.height = 90;

	if (SCREEN_WIDTH != 1280 || SCREEN_HEIGHT != 720) {
		size.width = 160 * SCREEN_WIDTH / 1280;
		size.height = 90 * SCREEN_HEIGHT / 720;
	}
	return size;
}


void placeStructToString(Place *source, char* targetString, int maxNameChar, int maxPlaceChar, int maxPointChar, int plusChar, int tabNum){

	sprintf(targetString, "%d.", source->placement);
	if (maxPlaceChar + 1 > numberCharNum(source->placement)) {
		spacePlacerToStringEnd(targetString, maxPlaceChar + 1 - numberCharNum(source->placement));
	}

	spacePlacerToStringEnd(targetString, tabNum);

	if (source->name == NULL){
		spacePlacerToStringEnd(targetString, maxNameChar);
	}
	else{
		strcat(targetString, source->name);
		if (maxNameChar > (int)strlen(source->name)){
			spacePlacerToStringEnd(targetString, maxNameChar - strlen(source->name));
		}
	}

	char *tmpString = (char*)malloc((maxPointChar + 1) * sizeof(char));
	sprintf(tmpString, "%d", source->points);

	spacePlacerToStringEnd(targetString, tabNum);

	strcat(targetString, tmpString);
	if (maxPointChar + 1 > numberCharNum(source->points)) {
		spacePlacerToStringEnd(targetString, maxPointChar - numberCharNum(source->points));
	}

	free(tmpString);
}

void spacePlacerToStringEnd(char *string, int number) {
	for (int i = 0; i < number; i++) {
		strcat(string, " ");
	}
}

int numberCharNum(int number){
	int charNum = 1;
	while (number / 10 > 0) {
		charNum++;
		number /= 10;
	}		
	return charNum;
}	

SDL_Rect renderAnimateConvert(LevelDimensions size, SDL_Rect start, Coordinate base){
	SDL_Rect tmp = start;
	for (int x = 0; x <= base.x; x++) {
		for (int y = 0; y <= base.y; y++) {
			tmp.x = start.w * y;
			tmp.y = start.h * x;
		}
	}
	return tmp;
}

SDL_Rect getHUDNameRect(renderAssets *renderAsset, Coordinate start,const char* playerName){
	SDL_Rect tmp;
	tmp.x = start.x - (renderAsset->font->size * strlen(playerName)/2);
	tmp.y = start.y - renderAsset->font->size;
	tmp.w = renderAsset->font->size * strlen(playerName);
	tmp.h = renderAsset->font->size;
	return tmp;
}

SDL_Rect getHUDNameLineRect(SDL_Rect nameRect){
	SDL_Rect tmp;
	tmp.x = nameRect.x - nameRect.h/2; //a nameRect az egyenlõ a betûmérettel ebben az esetben
	tmp.y = nameRect.y + nameRect.h;
	tmp.h = 4; //4 db pixel a vonal
	tmp.w = nameRect.w + nameRect.h;
	return tmp;
}

SDL_Rect getHUDPointsRect(renderAssets *renderAsset, Coordinate start, const char *scoreString){
	SDL_Rect tmp;
	tmp.x = start.x - (renderAsset->font->size * strlen(scoreString) / 2);
	tmp.y = start.y + 14; // 4 vonal hossza plusz 10 pixel távolság
	tmp.w = renderAsset->font->size * strlen(scoreString);
	tmp.h = renderAsset->font->size;
	return tmp;
}

char *getScoreString(int points){
	int pointsNumber = numberCharNum(points);
	char *tmp = (char*)malloc(pointsNumber + 1 * sizeof(char));
	sprintf(tmp, "%d", points);
	char *finalText = (char*)malloc((strlen("Pontok: ") + pointsNumber + 1) * sizeof(char));
	sprintf(finalText, "Pontok: ");
	strcat(finalText, tmp);
	free(tmp);
	return finalText;
}

SDL_Rect getHeartRectBase(renderAssets *renderAsset,Coordinate start){
	SDL_Rect tmp;
	start.x = renderAsset->renderer->SCREEN_WIDTH - (renderAsset->renderer->SCREEN_WIDTH - start.x) * 2;
	tmp.w = (renderAsset->renderer->SCREEN_WIDTH - start.x) / 10; // 2*5 vagyis így a szivek mindig a elérhetõ pixelszám fele nagyságúak
	tmp.h = tmp.w;
	tmp.x = start.x + (int)2.5 * tmp.w;
	tmp.y = start.y + 24 + renderAsset->font->size; // font size + 14 távolságra kezdõdik a pontszám kiírás, + a mérete és 10 pixel távolság 
	return tmp;
}

char *getLeveLSourcePathString(int levelNumber) {
	char *sourcePath = (char*)malloc((strlen("resources/levels/level_X.txt") + 1) * sizeof(char));
	sprintf(sourcePath,"resources/levels/level_%d.txt", levelNumber);
	return sourcePath;
}

char *getLevelName(int index){
	switch (index) {
		case 0:
			return "Arena";
			break;
		case 1:
			return "Labirintus";
			break;
		default:
			return "-";
			break;
	}
}

SDL_Rect getStateEnragedRect(renderAssets *renderAsset, Coordinate start) {
	SDL_Rect tmp;
	start.x = renderAsset->renderer->SCREEN_WIDTH - (renderAsset->renderer->SCREEN_WIDTH - start.x) * 2;
	tmp.w = (renderAsset->renderer->SCREEN_WIDTH - start.x) / 10; /* 2*5 vagyis a chili mindig olyan nagy mint a sziv */
	tmp.h = tmp.w;
	tmp.x = 2 * tmp.w + start.x + (int)2.5 * tmp.w; /* középen legyen a chili */
	tmp.y = tmp.h + start.y + 34 + renderAsset->font->size; /* font size + 14 távolságra kezdõdik a pontszám kiírás, 10 pixel távolság a szívektõl */
	return tmp;
}

SDL_Rect getStateFrozenRect(renderAssets *renderAsset, Coordinate start) {
	SDL_Rect tmp;
	start.x = renderAsset->renderer->SCREEN_WIDTH - (renderAsset->renderer->SCREEN_WIDTH - start.x) * 2;
	tmp.w = (renderAsset->renderer->SCREEN_WIDTH - start.x) / 10; /* 2*5 vagyis a jégkása mindig olyan nagy mint a sziv */
	tmp.h = tmp.w;
	tmp.x = 2 * tmp.w + start.x + (int)2.5 * tmp.w; /* középen legyen a jégkása */
	tmp.y = 10;
	return tmp;
}