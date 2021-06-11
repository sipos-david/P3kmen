#ifndef RENDERCALC_H
#define RENDERCALC_H

/* Struktúra ami eltárolja a fõ felosztásának méretét */
typedef struct initMainMenuBaseGridSizes{
	int width, height;
}initMainMenuBaseGridSizes;

/* Megadott felbontás alapján kitölti megfelelõen az initMainMenuCoords struktúrát */
initMainMenuCoords getMainMenuCoords(int SCREEN_HEIGHT, int SCREEN_WIDTH);

/* Megadott felbontás,betûméret alapján kitölti megfelelõen az initTopListCoords struktúrát */
initTopListCoords getTopListCoords(int SCREEN_HEIGHT, int SCREEN_WIDTH, int fontSize);

/* Megadott felbontás,betûméret alapján kitölti megfelelõen az initMainMenuBaseGridSizes struktúrát*/
initMainMenuBaseGridSizes getMainMenuBaseGridSizes(int SCREEN_HEIGHT, int SCREEN_WIDTH);

/* Megadott felbontás,betûméret és stringek alapján kitölti megfelelõen az initGetDifficultyCoords struktúrát*/
initGetDifficultyCoords getGetDifficultyCoords(renderAssets *renderAsset, const char* difTextString, const char *easyString, const char *normalString, const char *hardString);

/* Adott Place sturktúrából egyetlen egy megadott stringbe teszi, közöttük a tabNum szóközt hagy ki*/
void placeStructToString(Place *source, char* targetString, int maxNameChar, int maxPlaceChar, int maxPointChar, int plusChar, int tabNum);

/* Adott string helyére number darab szóközt fûz */
void spacePlacerToStringEnd(char* string, int number);

/* Egy integer számról megmondja hány karakter kell a kiírásához */
int numberCharNum(int number);

/* Visszatér az animacóhoz megfelelõ SDL_Rect struktúrával */
SDL_Rect renderAnimateConvert(LevelDimensions size, SDL_Rect start, Coordinate base);

/* Visszatér HUD-on a játékos név megjelenítéséhez szükséges SDL_Rect struktúrával */
SDL_Rect getHUDNameRect(renderAssets *renderAsset, Coordinate start, const char* playerName);

/* Visszatér név alatt lévõ vonal megjelenítéséhez szükséges SDL_Rect struktúrával */
SDL_Rect getHUDNameLineRect(SDL_Rect nameRect);

/* Visszatér HUD-on a pontok megjelenítéséhez szükséges SDL_Rect struktúrával */
SDL_Rect getHUDPointsRect(renderAssets *renderAsset, Coordinate start, const char *scoreString);

/* Visszatér HUD-on az életek megjelenítéséhez szükséges SDL_Rect struktúrával */
SDL_Rect getHeartRectBase(renderAssets *renderAsset, Coordinate start);

/* Megadott int számot visszad char*-ként */
char *getScoreString(int points);

/* levelNumber függvényében visszatér a pálya felépítéséhez szükséges txt elérési útvonalával */
char *getLeveLSourcePathString(int levelNumber);

/* Index függvényéven visszatér a pálya nével, ha au indexhez nem tartozik név, akkor - */
char *getLevelName(int index);

/* Visszatér HUD-on a chili megjelenítéséhez szükséges SDL_Rect struktúrával */
SDL_Rect getStateEnragedRect(renderAssets *renderAsset, Coordinate start);

/* Visszatér HUD-on a jégkása megjelenítéséhez szükséges SDL_Rect struktúrával */
SDL_Rect getStateFrozenRect(renderAssets *renderAsset, Coordinate start);
#endif 