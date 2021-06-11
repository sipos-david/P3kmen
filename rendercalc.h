#ifndef RENDERCALC_H
#define RENDERCALC_H

/* Strukt�ra ami elt�rolja a f� feloszt�s�nak m�ret�t */
typedef struct initMainMenuBaseGridSizes{
	int width, height;
}initMainMenuBaseGridSizes;

/* Megadott felbont�s alapj�n kit�lti megfelel�en az initMainMenuCoords strukt�r�t */
initMainMenuCoords getMainMenuCoords(int SCREEN_HEIGHT, int SCREEN_WIDTH);

/* Megadott felbont�s,bet�m�ret alapj�n kit�lti megfelel�en az initTopListCoords strukt�r�t */
initTopListCoords getTopListCoords(int SCREEN_HEIGHT, int SCREEN_WIDTH, int fontSize);

/* Megadott felbont�s,bet�m�ret alapj�n kit�lti megfelel�en az initMainMenuBaseGridSizes strukt�r�t*/
initMainMenuBaseGridSizes getMainMenuBaseGridSizes(int SCREEN_HEIGHT, int SCREEN_WIDTH);

/* Megadott felbont�s,bet�m�ret �s stringek alapj�n kit�lti megfelel�en az initGetDifficultyCoords strukt�r�t*/
initGetDifficultyCoords getGetDifficultyCoords(renderAssets *renderAsset, const char* difTextString, const char *easyString, const char *normalString, const char *hardString);

/* Adott Place sturkt�r�b�l egyetlen egy megadott stringbe teszi, k�z�tt�k a tabNum sz�k�zt hagy ki*/
void placeStructToString(Place *source, char* targetString, int maxNameChar, int maxPlaceChar, int maxPointChar, int plusChar, int tabNum);

/* Adott string hely�re number darab sz�k�zt f�z */
void spacePlacerToStringEnd(char* string, int number);

/* Egy integer sz�mr�l megmondja h�ny karakter kell a ki�r�s�hoz */
int numberCharNum(int number);

/* Visszat�r az animac�hoz megfelel� SDL_Rect strukt�r�val */
SDL_Rect renderAnimateConvert(LevelDimensions size, SDL_Rect start, Coordinate base);

/* Visszat�r HUD-on a j�t�kos n�v megjelen�t�s�hez sz�ks�ges SDL_Rect strukt�r�val */
SDL_Rect getHUDNameRect(renderAssets *renderAsset, Coordinate start, const char* playerName);

/* Visszat�r n�v alatt l�v� vonal megjelen�t�s�hez sz�ks�ges SDL_Rect strukt�r�val */
SDL_Rect getHUDNameLineRect(SDL_Rect nameRect);

/* Visszat�r HUD-on a pontok megjelen�t�s�hez sz�ks�ges SDL_Rect strukt�r�val */
SDL_Rect getHUDPointsRect(renderAssets *renderAsset, Coordinate start, const char *scoreString);

/* Visszat�r HUD-on az �letek megjelen�t�s�hez sz�ks�ges SDL_Rect strukt�r�val */
SDL_Rect getHeartRectBase(renderAssets *renderAsset, Coordinate start);

/* Megadott int sz�mot visszad char*-k�nt */
char *getScoreString(int points);

/* levelNumber f�ggv�ny�ben visszat�r a p�lya fel�p�t�s�hez sz�ks�ges txt el�r�si �tvonal�val */
char *getLeveLSourcePathString(int levelNumber);

/* Index f�ggv�ny�ven visszat�r a p�lya n�vel, ha au indexhez nem tartozik n�v, akkor - */
char *getLevelName(int index);

/* Visszat�r HUD-on a chili megjelen�t�s�hez sz�ks�ges SDL_Rect strukt�r�val */
SDL_Rect getStateEnragedRect(renderAssets *renderAsset, Coordinate start);

/* Visszat�r HUD-on a j�gk�sa megjelen�t�s�hez sz�ks�ges SDL_Rect strukt�r�val */
SDL_Rect getStateFrozenRect(renderAssets *renderAsset, Coordinate start);
#endif 