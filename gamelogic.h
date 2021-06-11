#ifndef GAMELOGIC_H
#define GAMELOGIC_H

/* Inicializál egy játékost */
Player playerInit(RenderAssets *renderAsset, Difficulty difficulty, TileType pacmanID, Level *level);

/* Lespawnol egy adott játékost a pályára */
void spawnPlayer(Level *level, Player *player);

/* Lespawnol egy adott szörnyet a pályára */
void spawnMonster(Monster *monster, Level *level);

/* Igazzal tér vissza ha a lépés engedélyezett vagyis ha nem fal, egyébként hamis */
bool moveIsValidCheck(Level *level, Coordinate coordinate);

/* Igazzal tér vissza ha a megadott elem pont */
bool isPointCheck(Level * level, Coordinate coordinate);

/* Igazzal tér vissza ha a megadott elem kis pont */
bool isLittlePointCheck(Level * level, Coordinate coordinate);

/* Igazzal tér vissza ha a megadott elem út*/
bool isPathCheck(Level * level, Coordinate coordinate);

/* Igazzal tér vissza ha a megadott elem szörny*/
bool isMonsterCheck(Level *level, Coordinate coordinate);

/* A level struktúra megfelelõ pontkába összeszámolja az elérhetõ pontszámot*/
void sumOfAvalaiablePoints(Level* level);

/* Szörny típus inicializálása*/
void monsterInit(Level *level, Monster *monster, SDL_Texture* texture, TileType id);

/* A és B pontok távolságával visszatér */
double distanceFromAtoB(Coordinate A, Coordinate B);

/* Megadja egy játékos koordinátáit */
Coordinate *getPlayerCoords(Level *level);

/* Megadja egy játékosok számát */
int getPlayerNumber(Level *level);

/* Visszatér egy olyan koordinátával amire lehet lépni */
Coordinate getValidCoords(Level *level);

/* Egy játék játszása*/
void playGame(RenderAssets *renderAsset, Level* level, Player *playerOne, Player *playerTwo, Monsters* baddies);

/* A bemenõ billentyûzet imputot kezeli*/
void keyBoardInputHandler(RenderAssets *renderAsset, Level* level, SDL_Event *event, Player *playerOne, Player *playerTwo, Monsters *monsters);

/* Átrak egy játékost másik pontra */
void playerMoveToNewDest(RenderAssets *renderAsset, Level *level, Player *player, Direction dir, Monsters *monsters);

/* Irányból megmondja a koordinátát */
Coordinate getCoordinateFromDirection(LevelDimensions size, Coordinate coords, Direction dir);

/* Karakter rak át a megadott pontra */
void moveEntityToDest(RenderAssets *renderAsset, Level *level, TileType id, Coordinate oldCoords, Coordinate newCoords, SDL_Texture *texture, Direction dir, bool isPlayer);

/* Koordinátákból megadja az irányt */
Direction getDirectionFromCoords(Coordinate newCoords, Coordinate oldCoords);

/* Iagaz ha véget ért a játék */
bool gameEndCheck(Level* level);

/* Visszatér a HUD kezdõkoordinátájával */
Coordinate getHUDZeroPoint(Level *level);

/* Megadott ms-bemenet alapján ms milisecundomonként SDL_USEREVENT usereventet rak az SDL event queue-ba | Használat: 1 mp-es idõzítõ az eventek idõzítéséhez */
Uint32 timer(Uint32 ms, void *param);

/* Megadott ms-bemenet alapján ms milisecundomonként SDL_USEREVENT + 1 usereventet rak az SDL event queue-ba | Használat: idõzítõ a függvényhez, ami a szörny játékos megevesésért felelõs */
Uint32 timerMonsterAiKill(Uint32 ms, void *param);

/* Megadott ms-bemenet alapján ms milisecundomonként SDL_USEREVENT + 2 usereventet rak az SDL event queue-ba | Használat: idõzítõ a függvényhez, ami a szörny mozgásáért felelõs */
Uint32 timerMonsterAiMove(Uint32 ms, void *param);

/* Igazzal tér vissza ha a megadott adatok frissültek. */
bool updateHUDCheck(int *playerPointsOld, int* playerSumHealtOld, Player *playerOne, Player *playerTwo);

/* Kezel egy TimeHandler struktúrát, alap idõegység: mp */
void clockHandler(TimeHandler *eventTimer);

/* lespawnolja a módosítókat */
void spawnUsables(Level *level);

/* Inicializál egy eventTimer strukturát*/
void levelInitEventTimer(TimeHandler *eventTimer);

/* Idõzített események kezelése */
void timedEventHandler(Level* level, Monsters *monsters, Player *playerOne, Player *playerTwo);

/* Inicializál egy eventTimeAndCondition strukturát*/
void initEventTimeAndCondition(eventTimeAndCondition *event);

/* kiírja az adatokat a consolba a hátékról */
void printDataToConsole(Level *level, Player *playerOne,Player* PlayerTwo, Monsters *baddies);

/* Elhelyezi a nagy pontokat a pályán véletlenszerûen */
void bigPointsInit(Level* level);

/* Visszatér egy MoveEnable struktúráva aminek a tartalmát az határozza meg hogy,a szörny megehet egy játékost */
MoveEnable moveAIPlayerKill(Direction dir, Coordinate coords, Level* level);

/* Vizsgálja hogy  a szörny megehet-e egy játékost, ha igen, akkor végrehajta, vagyis megeszi */
void monsterAiKill(RenderAssets *renderAsset, Level* level, Monster *monster, Player *playerOne, Player *playerTwo);

/* Mozgat egy szörnyet */
void monsterAiMove(RenderAssets *renderAsset, Level *level, Monster *monster);

/* Újra spawnol egy játékost, a szörnyektõl egy bizonyos távolságra !!! Nincs force spawn, a játék leállhat ha nincs elég távolság !!! */
void respawnPlayer(Monsters *monsters, Level *level, Player *player);

/* Visszér egy véletlenszerû koordinátával, ami path-re mutat */
Coordinate getValidPathCoords(Level *level);

/* Igaz ha a megadott irányba a lépés megtehetõ */
bool checkMovementValidDir(Level* level, Coordinate coords);

/* Megadott irányba vissztér a megfelelõ új koordinátával */
Coordinate getCoordsFromDir(Direction dir, Coordinate coords);

/* Igaz a Monster strukturúban a dir változó irányába a lépés megtehetõ */
bool preferredDirAiMove(RenderAssets *renderAsset, Level *level, Monster *monster);

/* A játék alatt szerzett pontokatt módósítja a nehézség függvényében */
int getPointsFromDifficulty(Difficulty difficulty, int score);

/* Felszabadít a Mosnters strujtúrát */
void freeMonsters(Monsters *monsters);

/* Inicializálja a szörnyeket */
Monsters *initMonsters(RenderAssets *renderAsset, Level* level);

/* Ha sfx nem NULL, lejátsza a hangeffektet */
void playSFX(Mix_Chunk *sfx);
#endif 

