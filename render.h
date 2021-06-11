#ifndef RENDER_H
#define RENDER_H

/* Elind�tja az SDL-t, alap felbont�s: 1280x720, windowData strukt�ra alapj�n be�ll�tja a felbont�st �s a teljes k�perny�s m�d�t */
initRenderer initRender(windowData windowResolution);

/* Az initTexture strukt�r�t felt�lti text�r�kkal a static SDL_Texture *loadImage f�ggv�ny seg�ts�g�vel */
initTexture loadTexture(initRenderer *renderer);

/* Megadott el�r�si �tvolnallal bet�lt egy ttf f�jlt fontSize m�retben */
initFont loadFont(const char *filePath, int fontSize);

/* Bet�lti a hangokat, ha nem l�tezik a f�jl akkor a hangra mutat� pointer NULL */
initSounds loadSounds(void);

/* .bmp kiterjeszt�s� f�jlokb�l text�r�kat csin�l */
SDL_Texture *loadImage(const char *picture, initRenderer *renderer);

/* Bez�rja az SDL-t */
void sdlClose(renderAssets *renderAsset);

/* Kirajzolja a f�men�t */
void drawMainMenu(renderAssets *renderAsset, MainMenuSelection selection, initMainMenuCoords mainMenuCoord);

/* Kirajzolja a toplist�t */
void renderTopList(renderAssets *renderAsset, initTopListCoords topListCoords, Place **topList, int placementNumber);

/* string stringet kirajzolja a place �lltal megadott helyen. m�retben */
void renderText(renderAssets *renderAsset, SDL_Rect place, const char* string);

/* Kirajzolja a kiv�laszt�st jelz� cs�kot, de nem jelen�ti meg, a cs�k magass�ga pixelHeight,  */
void placeSelectionRectForRender(renderAssets *renderAsset, SDL_Rect placement, int pixelHeight);

/* Kirajzolja a n�v bek�r�s k�perny�t, ahol a nameString a nevet tartalmazza */
void renderScoreInputScreen(renderAssets *renderAsset, const char* nameString);

/* Kirajzolja a level-ben megadott p�ly�t a sz�rnyek �s j�t�kosok n�lk�l */
void renderMapWithoutEntities(Level *level, renderAssets *renderAsset);

/* Kirajzolja a level-ben megadott p�ly�n sz�rnyeket �s j�t�kosokat */
void renderMapJustEntities(Level *level, renderAssets *renderAsset, Player *playerOne, Player *playerTwo, Monsters *monsters);

/* Kirajzolja a men�t a neh�zs�g v�laszt�shoz, majd visszat�r a kiv�lasztott neh�zs�ggel */
Difficulty getDifficulty(renderAssets *renderAsset);

/* Kirajzolja a men�t a p�lyav�laszt�shoz,majd a kiv�lasztott p�lya el�r�si hely�vel visszat�r */
char *getLevelFromFile(renderAssets *renderAssets);

/* Anim�lja a megadott karaktert*/
void renderAnimateEntity(renderAssets *renderAsset, Level *level, SDL_Texture *texture, Coordinate newCoords, Coordinate oldCoords, Direction dir);

/* Anim�lja a megadott karakter felfel� halad�s�t*/
void renderAnimateEntityMoveUp(renderAssets *renderAsset, SDL_Rect tile, LevelDimensions size, SDL_Texture *texture, Coordinate newCoords, Coordinate oldCoords);

/* Anim�lja a megadott karakter lefel� halad�s�t*/
void renderAnimateEntityMoveDown(renderAssets *renderAsset, SDL_Rect tile, LevelDimensions size, SDL_Texture *texture, Coordinate newCoords, Coordinate oldCoords);

/* Anim�lja a megadott karakter balra halad�s�t*/
void renderAnimateEntityMoveLeft(renderAssets *renderAsset, SDL_Rect tile, LevelDimensions size, SDL_Texture *texture, Coordinate newCoords, Coordinate oldCoords);

/* Anim�lja a megadott karakter jobbra halad�s�t*/
void renderAnimateEntityMoveRight(renderAssets *renderAsset, SDL_Rect tile, LevelDimensions size, SDL_Texture *texture, Coordinate newCoords, Coordinate oldCoords);

/* Kirajzolja a HUD-ot */
void renderHUD(renderAssets *renderAsset, Coordinate hudZero, Player *playerOne, Player *playerTwo, bool renderIce);

/* Clear-eli a HUD-ot */
void renderClearHUD(renderAssets *renderAsset, Coordinate hudZero);

/* Egyj�t�kos adatait rajzolja ki a HUD-ra */
void renderPlayerHUD(renderAssets *renderAsset, Coordinate start, Player* playerTwo, const char* palyerName);

/* Inicializ�l egy p�ly�t, el�sz�r p�lya v�l�szt�st k�ri a felhaszn�l�t�l, majd elv�gzi a p�lya fel�p�ts�s�t */
Level *initLevel(renderAssets *renderAsset);

/* Bek�ri egy j�t�kos nev�t, ha felker�lt a toplist�ra �s friss�ti az Eredm�nyek.txt tartalm�t, majd megjelen�ti a list�t */
void insertNameToplist(renderAssets *renderAsset, Place **topListArray, int *placementNumber, int score);
#endif