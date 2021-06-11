#ifndef IOPUT_H
#define IOPUT_H

/* A fõmenüben kezeli az inputot, ha billentyûlenyomás visszatér a megfelelõ értékkel, ellenben selection a kimenet */
MainMenuSelection getMainMenuInput(SDL_Event *eventMain, MainMenuSelection selection, RenderAssets *renderAsset);

/* Eredmények.txt-bõl feltölt Place strukturát, annyi darabot ammenyi a placementNumber bemenet */
Place **readTopList(int placementNumber);

/* Egy dinamikus stringhez hozzáfûz egy karaktert, majd a régit felszabadítja, és visszatér az új stringre mutató pointerrel*/
char *remakeDynString(char newchar, char* string);

/* Egy dinamikus stringbõl töröl egy karaktert, majd a régit felszabadítja, és visszatér az új stringre mutató pointerrel*/
char *removeDynStringLastChar(char *string);

/* Duplikál egy dinamikusan foglalt tömböt */
char *duplicateDynString(const char* string);

/* String karaktereket integer számmá alakítja majd visszatér*/
int numFromString(char *string);

/* Felszabadít egy Place strukturákból álló dinamikus tömböt*/
void freePlaceStructArray(Place **list, int size);

/* Pont szerint csökkenõ sorrendbe rak egy Place strukzúrákból álló tömböt */
void placeStructArraySelectionSort(Place **list, int size);

/* Eredmények.txt fájlba kiírja a toplistát */
void writeTopList(Place **list, int size);

/* Place tömbhöz hozzáad egy üres elemet , majd felszabadítja a régi listát, és felötli a megadott értékekkel*/
Place **remakeDynPlaceStructArray(Place **oldArray, int size);

/* Visszaadja a letütött betû billentyût char formátumban, 0 ha nem betû a lenyomott gomb, 1 ha ENTER, 3 ha SHIFT, és ha egyik feltétel sem teljesül akkor 2-t ad vissza */
char getSDLInputABC(SDL_Event *eventInput);

/* filePath eléri útból betülti egy dinamikusan foglalt 2D karaktertömbe a txt tartalmát  */
char **readLevel(const char* filePath, LevelDimensions *dim);

/* Felszabadít egy "D dinamikusan foglalt tömböt */
void free2DCharArray(char **array, int rowSize);

/* 2D karaktertömbbõl 2D TileType enumtömböt készít, megfeleõen elkészíti a hátteret */
TileType **mapConverter(char **array, LevelDimensions dim);

/* size méretû dinamikus stringet készít */
char* makeDynString(int size);

/* Felszabdítja a level struktúra dinamukisan foglalt map 2D TileType tömbjét */
void freeLevel(Level *level);

/* 0-9 ig megadott number számot ad vissza char váltózóként */
char charFromNum(int number);

/* Konzolban kéri a felhasználót a felbontás és a teljes képernyõs mód kiválasztására */
windowData getWindowData(void);

/* P3Kmen feliratot ír ki a console abalakba */
void renderConsoleP3Kmen(void);

/* Kiírja a felbontás választómenüt a console abalakba */
void renderConsoleResChooseMenu(void);

/* Kiírja a teljesképernyõs mód választómenüt a console abalakba */
void renderConsoleFullscreenChooseMenu(void);

/* Igaz ha a felhasználó a teljes képernyõs módót választotta */
bool getFullsreenFromConsole(void);

/* Azzal az elemmel tér vissza, amely felbontást a felhasználó választotta */
Resolution getResolutionFromConsole(void);
#endif 