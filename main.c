#include "gamebase.h"
#include "render.h"
#include "rendercalc.h"
#include "IOput.h"
#include "gamelogic.h"
#include <time.h>

/* Egyjátékos mód  */
void singlePlayer(RenderAssets *renderAsset);

/* Többjátékos mód  */
void multiPlayer(RenderAssets *renderAsset);

/* Dicsõség lista kiírása */
void topList(RenderAssets *renderAsset);

/* Dicsõség lista és adott pont kiírása, ha a pont elegendõ a listára felkerüléshez a program bekéri a játékos nevét és felkerül a toplistára, az eredmények.txt-ben is */
void finalScoreToplist(RenderAssets *renderAsset, int score);

int main(int argc, char* args[]){
	srand(time(NULL));
	windowData window = getWindowData();
	Renderer renderer = initRender(window);
	Textures texture = loadTexture(&renderer);
	Font amaticBold = loadFont("resources/fonts/Amatic-Bold.ttf", 32);
	Sounds sounds = loadSounds();
	RenderAssets renderAsset = {&renderer, &texture, &amaticBold, &sounds, &window, false};
	MainMenuCoords mainMenuCoord = getMainMenuCoords(renderer.SCREEN_HEIGHT, renderer.SCREEN_WIDTH);
	MainMenuSelection selection = notvalidinput, selection_next = singleplayer;
	SDL_Event eventMain;
	while (!renderAsset.close){
		while (SDL_PollEvent(&eventMain)) {
			if (eventMain.type == SDL_QUIT) {
				renderAsset.close = true;
			}
			else{
				selection = selection_next;
				selection_next = getMainMenuInput(&eventMain, selection, &renderAsset);
				drawMainMenu(&renderAsset , selection, mainMenuCoord);
				if (selection_next == valaszt) {
					switch (selection){
						case singleplayer:
							singlePlayer(&renderAsset);
							selection_next = selection;
							break;
						case multiplayer:
							multiPlayer(&renderAsset);
							selection_next = selection;
							break;
						case toplist:
							topList(&renderAsset);
							selection_next = selection;
							break;
						case quitgame:
							renderAsset.close = true;
							break;
						default:
							break;
					}
				}
			}
		}
	}
	sdlClose(&renderAsset);
	return 0;
}

void singlePlayer(RenderAssets *renderAsset){

	Level *level = initLevel(renderAsset);
	if (renderAsset->close == true) {
		if (level != NULL)
			freeLevel(level);
		return;
	}

	Difficulty difficulty = getDifficulty(renderAsset);
	if (renderAsset->close == true) {
		freeLevel(level);
		return;
	}

	Player player = playerInit(renderAsset,difficulty,pacmanA,level);

	level->playerHealthSum = player.health;
	
	levelInitEventTimer(&level->eventTimer);

	Monsters *enemies = initMonsters(renderAsset,level);

	sumOfAvalaiablePoints(level);

	bigPointsInit(level);

	playGame(renderAsset, level, &player,NULL, enemies);
	if (renderAsset->close == true) {
		freeMonsters(enemies);
		freeLevel(level);
		return;
	}

	int score = getPointsFromDifficulty(difficulty, player.points);

	freeMonsters(enemies);
	freeLevel(level);
	finalScoreToplist(renderAsset,score);
}

void multiPlayer(RenderAssets *renderAsset){

	Level *level = initLevel(renderAsset);
	if (renderAsset->close == true) {
		freeLevel(level);
		return;
	}

	Difficulty difficulty = getDifficulty(renderAsset);
	if (renderAsset->close == true) {
		freeLevel(level);
		return;
	}

	Player playerOne = playerInit(renderAsset, difficulty, pacmanA, level);
	Player playerTwo = playerInit(renderAsset, difficulty, pacmanB, level);

	level->playerHealthSum = playerTwo.health + playerOne.health;

	levelInitEventTimer(&level->eventTimer);

	Monsters *enemies = initMonsters(renderAsset, level);

	sumOfAvalaiablePoints(level);
	
	bigPointsInit(level);

	playGame(renderAsset, level, &playerOne, &playerTwo, enemies);
	freeMonsters(enemies);
	freeLevel(level);
}

void topList(RenderAssets *renderAsset){

	/*A placementNumber változó befolyásolja a beolvasott.kiirt eredmenyek darabszámát.*/
	int placementNumber = 10;

	TopListCoords topListCoords = getTopListCoords(renderAsset->renderer->SCREEN_HEIGHT, renderAsset->renderer->SCREEN_WIDTH, renderAsset->font->size);
	Place **topListArray = readTopList(placementNumber);
	placeStructArraySelectionSort(topListArray, placementNumber);
	writeTopList(topListArray, placementNumber);
	renderTopList(renderAsset, topListCoords, topListArray, placementNumber);
	SDL_Event eventTopList;
	bool quit = false;
	while (!quit) {
		while (SDL_PollEvent(&eventTopList)) {
			if (eventTopList.type == SDL_KEYDOWN){
				quit = true;
			}
			if (eventTopList.type == SDL_QUIT) {
				renderAsset->close = true;
				freePlaceStructArray(topListArray, placementNumber);
				return;
			}
		}
	}
	freePlaceStructArray(topListArray, placementNumber);
}

void finalScoreToplist(RenderAssets *renderAsset, int score) {

	/*A placementNumber változó befolyásolja a beolvasott.kiirt eredmenyek darabszámát.*/
	int placementNumber = 10;

	TopListCoords topListCoords = getTopListCoords(renderAsset->renderer->SCREEN_HEIGHT, renderAsset->renderer->SCREEN_WIDTH, renderAsset->font->size);
	Place **topListArray = readTopList(placementNumber);
	topListArray = remakeDynPlaceStructArray(topListArray, placementNumber);
	insertNameToplist(renderAsset, topListArray, &placementNumber, score);
	renderTopList(renderAsset, topListCoords, topListArray, placementNumber);

	/* Utolso megjelenített értek fölé vonalat húz */
	SDL_SetRenderDrawColor(renderAsset->renderer->renderer, 12, 12, 12, 255);
	SDL_Rect tmpLine = {topListCoords.placementsBase.x - renderAsset->font->size,
						topListCoords.placementsBase.y + (placementNumber - 1) * renderAsset->font->size,
						topListCoords.placementsBase.w + 2 * renderAsset->font->size,
						2};
	SDL_RenderDrawRect(renderAsset->renderer->renderer,&tmpLine);

	SDL_RenderPresent(renderAsset->renderer->renderer);

	freePlaceStructArray(topListArray, placementNumber);

	SDL_Event eventFinalScoreTopList;
	bool quit = false;
	while (!quit) {
		while (SDL_PollEvent(&eventFinalScoreTopList)) {
			if (eventFinalScoreTopList.type == SDL_KEYDOWN) 
				quit = true;
			if (eventFinalScoreTopList.type == SDL_QUIT) {
				renderAsset->close = true;
				return;
			}
		}
	}
}