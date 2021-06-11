#ifndef IOPUT_H
#define IOPUT_H

/* A f�men�ben kezeli az inputot, ha billenty�lenyom�s visszat�r a megfelel� �rt�kkel, ellenben selection a kimenet */
MainMenuSelection getMainMenuInput(SDL_Event *eventMain, MainMenuSelection selection, RenderAssets *renderAsset);

/* Eredm�nyek.txt-b�l felt�lt Place struktur�t, annyi darabot ammenyi a placementNumber bemenet */
Place **readTopList(int placementNumber);

/* Egy dinamikus stringhez hozz�f�z egy karaktert, majd a r�git felszabad�tja, �s visszat�r az �j stringre mutat� pointerrel*/
char *remakeDynString(char newchar, char* string);

/* Egy dinamikus stringb�l t�r�l egy karaktert, majd a r�git felszabad�tja, �s visszat�r az �j stringre mutat� pointerrel*/
char *removeDynStringLastChar(char *string);

/* Duplik�l egy dinamikusan foglalt t�mb�t */
char *duplicateDynString(const char* string);

/* String karaktereket integer sz�mm� alak�tja majd visszat�r*/
int numFromString(char *string);

/* Felszabad�t egy Place struktur�kb�l �ll� dinamikus t�mb�t*/
void freePlaceStructArray(Place **list, int size);

/* Pont szerint cs�kken� sorrendbe rak egy Place strukz�r�kb�l �ll� t�mb�t */
void placeStructArraySelectionSort(Place **list, int size);

/* Eredm�nyek.txt f�jlba ki�rja a toplist�t */
void writeTopList(Place **list, int size);

/* Place t�mbh�z hozz�ad egy �res elemet , majd felszabad�tja a r�gi list�t, �s fel�tli a megadott �rt�kekkel*/
Place **remakeDynPlaceStructArray(Place **oldArray, int size);

/* Visszaadja a let�t�tt bet� billenty�t char form�tumban, 0 ha nem bet� a lenyomott gomb, 1 ha ENTER, 3 ha SHIFT, �s ha egyik felt�tel sem teljes�l akkor 2-t ad vissza */
char getSDLInputABC(SDL_Event *eventInput);

/* filePath el�ri �tb�l bet�lti egy dinamikusan foglalt 2D karaktert�mbe a txt tartalm�t  */
char **readLevel(const char* filePath, LevelDimensions *dim);

/* Felszabad�t egy "D dinamikusan foglalt t�mb�t */
void free2DCharArray(char **array, int rowSize);

/* 2D karaktert�mbb�l 2D TileType enumt�mb�t k�sz�t, megfele�en elk�sz�ti a h�tteret */
TileType **mapConverter(char **array, LevelDimensions dim);

/* size m�ret� dinamikus stringet k�sz�t */
char* makeDynString(int size);

/* Felszabd�tja a level strukt�ra dinamukisan foglalt map 2D TileType t�mbj�t */
void freeLevel(Level *level);

/* 0-9 ig megadott number sz�mot ad vissza char v�lt�z�k�nt */
char charFromNum(int number);

/* Konzolban k�ri a felhaszn�l�t a felbont�s �s a teljes k�perny�s m�d kiv�laszt�s�ra */
windowData getWindowData(void);

/* P3Kmen feliratot �r ki a console abalakba */
void renderConsoleP3Kmen(void);

/* Ki�rja a felbont�s v�laszt�men�t a console abalakba */
void renderConsoleResChooseMenu(void);

/* Ki�rja a teljesk�perny�s m�d v�laszt�men�t a console abalakba */
void renderConsoleFullscreenChooseMenu(void);

/* Igaz ha a felhaszn�l� a teljes k�perny�s m�d�t v�lasztotta */
bool getFullsreenFromConsole(void);

/* Azzal az elemmel t�r vissza, amely felbont�st a felhaszn�l� v�lasztotta */
Resolution getResolutionFromConsole(void);
#endif 