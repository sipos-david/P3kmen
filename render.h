#ifndef RENDER_H
#define RENDER_H

/* Elindítja az SDL-t, alap felbontás: 1280x720, windowData struktúra alapján beállítja a felbontást és a teljes képernyõs módót */
initRenderer initRender(windowData windowResolution);

/* Az initTexture struktúrát feltölti textúrákkal a static SDL_Texture *loadImage függvény segítségével */
initTexture loadTexture(initRenderer *renderer);

/* Megadott elérési útvolnallal betölt egy ttf fájlt fontSize méretben */
initFont loadFont(const char *filePath, int fontSize);

/* Betölti a hangokat, ha nem létezik a fájl akkor a hangra mutató pointer NULL */
initSounds loadSounds(void);

/* .bmp kiterjesztésû fájlokból textúrákat csinál */
SDL_Texture *loadImage(const char *picture, initRenderer *renderer);

/* Bezárja az SDL-t */
void sdlClose(renderAssets *renderAsset);

/* Kirajzolja a fõmenüt */
void drawMainMenu(renderAssets *renderAsset, MainMenuSelection selection, initMainMenuCoords mainMenuCoord);

/* Kirajzolja a toplistát */
void renderTopList(renderAssets *renderAsset, initTopListCoords topListCoords, Place **topList, int placementNumber);

/* string stringet kirajzolja a place álltal megadott helyen. méretben */
void renderText(renderAssets *renderAsset, SDL_Rect place, const char* string);

/* Kirajzolja a kiválasztást jelzõ csíkot, de nem jeleníti meg, a csík magassága pixelHeight,  */
void placeSelectionRectForRender(renderAssets *renderAsset, SDL_Rect placement, int pixelHeight);

/* Kirajzolja a név bekérés képernyõt, ahol a nameString a nevet tartalmazza */
void renderScoreInputScreen(renderAssets *renderAsset, const char* nameString);

/* Kirajzolja a level-ben megadott pályát a szörnyek és játékosok nélkül */
void renderMapWithoutEntities(Level *level, renderAssets *renderAsset);

/* Kirajzolja a level-ben megadott pályán szörnyeket és játékosokat */
void renderMapJustEntities(Level *level, renderAssets *renderAsset, Player *playerOne, Player *playerTwo, Monsters *monsters);

/* Kirajzolja a menüt a nehézség választáshoz, majd visszatér a kiválasztott nehézséggel */
Difficulty getDifficulty(renderAssets *renderAsset);

/* Kirajzolja a menüt a pályaválasztáshoz,majd a kiválasztott pálya elérési helyével visszatér */
char *getLevelFromFile(renderAssets *renderAssets);

/* Animálja a megadott karaktert*/
void renderAnimateEntity(renderAssets *renderAsset, Level *level, SDL_Texture *texture, Coordinate newCoords, Coordinate oldCoords, Direction dir);

/* Animálja a megadott karakter felfelé haladását*/
void renderAnimateEntityMoveUp(renderAssets *renderAsset, SDL_Rect tile, LevelDimensions size, SDL_Texture *texture, Coordinate newCoords, Coordinate oldCoords);

/* Animálja a megadott karakter lefelé haladását*/
void renderAnimateEntityMoveDown(renderAssets *renderAsset, SDL_Rect tile, LevelDimensions size, SDL_Texture *texture, Coordinate newCoords, Coordinate oldCoords);

/* Animálja a megadott karakter balra haladását*/
void renderAnimateEntityMoveLeft(renderAssets *renderAsset, SDL_Rect tile, LevelDimensions size, SDL_Texture *texture, Coordinate newCoords, Coordinate oldCoords);

/* Animálja a megadott karakter jobbra haladását*/
void renderAnimateEntityMoveRight(renderAssets *renderAsset, SDL_Rect tile, LevelDimensions size, SDL_Texture *texture, Coordinate newCoords, Coordinate oldCoords);

/* Kirajzolja a HUD-ot */
void renderHUD(renderAssets *renderAsset, Coordinate hudZero, Player *playerOne, Player *playerTwo, bool renderIce);

/* Clear-eli a HUD-ot */
void renderClearHUD(renderAssets *renderAsset, Coordinate hudZero);

/* Egyjátékos adatait rajzolja ki a HUD-ra */
void renderPlayerHUD(renderAssets *renderAsset, Coordinate start, Player* playerTwo, const char* palyerName);

/* Inicializál egy pályát, elõszõr pálya válásztást kéri a felhasználótól, majd elvégzi a pálya felépítsését */
Level *initLevel(renderAssets *renderAsset);

/* Bekéri egy játékos nevét, ha felkerült a toplistára és frissíti az Eredmények.txt tartalmát, majd megjeleníti a listát */
void insertNameToplist(renderAssets *renderAsset, Place **topListArray, int *placementNumber, int score);
#endif