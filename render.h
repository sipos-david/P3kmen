#ifndef RENDER_H
#define RENDER_H

/* Elindítja az SDL-t, alap felbontás: 1280x720, windowData struktúra alapján beállítja a felbontást és a teljes képernyõs módót */
Renderer initRender(windowData windowResolution);

/* Az initTexture struktúrát feltölti textúrákkal a static SDL_Texture *loadImage függvény segítségével */
Textures loadTexture(Renderer *renderer);

/* Megadott elérési útvolnallal betölt egy ttf fájlt fontSize méretben */
Font loadFont(const char *filePath, int fontSize);

/* Betölti a hangokat, ha nem létezik a fájl akkor a hangra mutató pointer NULL */
Sounds loadSounds(void);

/* .bmp kiterjesztésû fájlokból textúrákat csinál */
SDL_Texture *loadImage(const char *picture, Renderer *renderer);

/* Bezárja az SDL-t */
void sdlClose(RenderAssets *renderAsset);

/* Kirajzolja a fõmenüt */
void drawMainMenu(RenderAssets *renderAsset, MainMenuSelection selection, MainMenuCoords mainMenuCoord);

/* Kirajzolja a toplistát */
void renderTopList(RenderAssets *renderAsset, TopListCoords topListCoords, Place **topList, int placementNumber);

/* string stringet kirajzolja a place álltal megadott helyen. méretben */
void renderText(RenderAssets *renderAsset, SDL_Rect place, const char* string);

/* Kirajzolja a kiválasztást jelzõ csíkot, de nem jeleníti meg, a csík magassága pixelHeight,  */
void placeSelectionRectForRender(RenderAssets *renderAsset, SDL_Rect placement, int pixelHeight);

/* Kirajzolja a név bekérés képernyõt, ahol a nameString a nevet tartalmazza */
void renderScoreInputScreen(RenderAssets *renderAsset, const char* nameString);

/* Kirajzolja a level-ben megadott pályát a szörnyek és játékosok nélkül */
void renderMapWithoutEntities(Level *level, RenderAssets *renderAsset);

/* Kirajzolja a level-ben megadott pályán szörnyeket és játékosokat */
void renderMapJustEntities(Level *level, RenderAssets *renderAsset, Player *playerOne, Player *playerTwo, Monsters *monsters);

/* Kirajzolja a menüt a nehézség választáshoz, majd visszatér a kiválasztott nehézséggel */
Difficulty getDifficulty(RenderAssets *renderAsset);

/* Kirajzolja a menüt a pályaválasztáshoz,majd a kiválasztott pálya elérési helyével visszatér */
char *getLevelFromFile(RenderAssets *renderAssets);

/* Animálja a megadott karaktert*/
void renderAnimateEntity(RenderAssets *renderAsset, Level *level, SDL_Texture *texture, Coordinate newCoords, Coordinate oldCoords, Direction dir);

/* Animálja a megadott karakter felfelé haladását*/
void renderAnimateEntityMoveUp(RenderAssets *renderAsset, SDL_Rect tile, LevelDimensions size, SDL_Texture *texture, Coordinate newCoords, Coordinate oldCoords);

/* Animálja a megadott karakter lefelé haladását*/
void renderAnimateEntityMoveDown(RenderAssets *renderAsset, SDL_Rect tile, LevelDimensions size, SDL_Texture *texture, Coordinate newCoords, Coordinate oldCoords);

/* Animálja a megadott karakter balra haladását*/
void renderAnimateEntityMoveLeft(RenderAssets *renderAsset, SDL_Rect tile, LevelDimensions size, SDL_Texture *texture, Coordinate newCoords, Coordinate oldCoords);

/* Animálja a megadott karakter jobbra haladását*/
void renderAnimateEntityMoveRight(RenderAssets *renderAsset, SDL_Rect tile, LevelDimensions size, SDL_Texture *texture, Coordinate newCoords, Coordinate oldCoords);

/* Kirajzolja a HUD-ot */
void renderHUD(RenderAssets *renderAsset, Coordinate hudZero, Player *playerOne, Player *playerTwo, bool renderIce);

/* Clear-eli a HUD-ot */
void renderClearHUD(RenderAssets *renderAsset, Coordinate hudZero);

/* Egyjátékos adatait rajzolja ki a HUD-ra */
void renderPlayerHUD(RenderAssets *renderAsset, Coordinate start, Player* playerTwo, const char* palyerName);

/* Inicializál egy pályát, elõszõr pálya válásztást kéri a felhasználótól, majd elvégzi a pálya felépítsését */
Level *initLevel(RenderAssets *renderAsset);

/* Bekéri egy játékos nevét, ha felkerült a toplistára és frissíti az Eredmények.txt tartalmát, majd megjeleníti a listát */
void insertNameToplist(RenderAssets *renderAsset, Place **topListArray, int *placementNumber, int score);
#endif