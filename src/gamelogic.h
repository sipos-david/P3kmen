#ifndef GAMELOGIC_H
#define GAMELOGIC_H

/* Inicializ�l egy j�t�kost */
Player playerInit(RenderAssets *renderAsset, Difficulty difficulty, TileType pacmanID, Level *level);

/* Lespawnol egy adott j�t�kost a p�ly�ra */
void spawnPlayer(Level *level, Player *player);

/* Lespawnol egy adott sz�rnyet a p�ly�ra */
void spawnMonster(Monster *monster, Level *level);

/* Igazzal t�r vissza ha a l�p�s enged�lyezett vagyis ha nem fal, egy�bk�nt hamis */
bool moveIsValidCheck(Level *level, Coordinate coordinate);

/* Igazzal t�r vissza ha a megadott elem pont */
bool isPointCheck(Level * level, Coordinate coordinate);

/* Igazzal t�r vissza ha a megadott elem kis pont */
bool isLittlePointCheck(Level * level, Coordinate coordinate);

/* Igazzal t�r vissza ha a megadott elem �t*/
bool isPathCheck(Level * level, Coordinate coordinate);

/* Igazzal t�r vissza ha a megadott elem sz�rny*/
bool isMonsterCheck(Level *level, Coordinate coordinate);

/* A level strukt�ra megfelel� pontk�ba �sszesz�molja az el�rhet� pontsz�mot*/
void sumOfAvalaiablePoints(Level* level);

/* Sz�rny t�pus inicializ�l�sa*/
void monsterInit(Level *level, Monster *monster, SDL_Texture* texture, TileType id);

/* A �s B pontok t�vols�g�val visszat�r */
double distanceFromAtoB(Coordinate A, Coordinate B);

/* Megadja egy j�t�kos koordin�t�it */
Coordinate *getPlayerCoords(Level *level);

/* Megadja egy j�t�kosok sz�m�t */
int getPlayerNumber(Level *level);

/* Visszat�r egy olyan koordin�t�val amire lehet l�pni */
Coordinate getValidCoords(Level *level);

/* Egy j�t�k j�tsz�sa*/
void playGame(RenderAssets *renderAsset, Level* level, Player *playerOne, Player *playerTwo, Monsters* baddies);

/* A bemen� billenty�zet imputot kezeli*/
void keyBoardInputHandler(RenderAssets *renderAsset, Level* level, SDL_Event *event, Player *playerOne, Player *playerTwo, Monsters *monsters);

/* �trak egy j�t�kost m�sik pontra */
void playerMoveToNewDest(RenderAssets *renderAsset, Level *level, Player *player, Direction dir, Monsters *monsters);

/* Ir�nyb�l megmondja a koordin�t�t */
Coordinate getCoordinateFromDirection(LevelDimensions size, Coordinate coords, Direction dir);

/* Karakter rak �t a megadott pontra */
void moveEntityToDest(RenderAssets *renderAsset, Level *level, TileType id, Coordinate oldCoords, Coordinate newCoords, SDL_Texture *texture, Direction dir, bool isPlayer);

/* Koordin�t�kb�l megadja az ir�nyt */
Direction getDirectionFromCoords(Coordinate newCoords, Coordinate oldCoords);

/* Iagaz ha v�get �rt a j�t�k */
bool gameEndCheck(Level* level);

/* Visszat�r a HUD kezd�koordin�t�j�val */
Coordinate getHUDZeroPoint(Level *level);

/* Megadott ms-bemenet alapj�n ms milisecundomonk�nt SDL_USEREVENT usereventet rak az SDL event queue-ba | Haszn�lat: 1 mp-es id�z�t� az eventek id�z�t�s�hez */
Uint32 timer(Uint32 ms, void *param);

/* Megadott ms-bemenet alapj�n ms milisecundomonk�nt SDL_USEREVENT + 1 usereventet rak az SDL event queue-ba | Haszn�lat: id�z�t� a f�ggv�nyhez, ami a sz�rny j�t�kos megeves�s�rt felel�s */
Uint32 timerMonsterAiKill(Uint32 ms, void *param);

/* Megadott ms-bemenet alapj�n ms milisecundomonk�nt SDL_USEREVENT + 2 usereventet rak az SDL event queue-ba | Haszn�lat: id�z�t� a f�ggv�nyhez, ami a sz�rny mozg�s��rt felel�s */
Uint32 timerMonsterAiMove(Uint32 ms, void *param);

/* Igazzal t�r vissza ha a megadott adatok friss�ltek. */
bool updateHUDCheck(int *playerPointsOld, int* playerSumHealtOld, Player *playerOne, Player *playerTwo);

/* Kezel egy TimeHandler strukt�r�t, alap id�egys�g: mp */
void clockHandler(TimeHandler *eventTimer);

/* lespawnolja a m�dos�t�kat */
void spawnUsables(Level *level);

/* Inicializ�l egy eventTimer struktur�t*/
void levelInitEventTimer(TimeHandler *eventTimer);

/* Id�z�tett esem�nyek kezel�se */
void timedEventHandler(Level* level, Monsters *monsters, Player *playerOne, Player *playerTwo);

/* Inicializ�l egy eventTimeAndCondition struktur�t*/
void initEventTimeAndCondition(eventTimeAndCondition *event);

/* ki�rja az adatokat a consolba a h�t�kr�l */
void printDataToConsole(Level *level, Player *playerOne,Player* PlayerTwo, Monsters *baddies);

/* Elhelyezi a nagy pontokat a p�ly�n v�letlenszer�en */
void bigPointsInit(Level* level);

/* Visszat�r egy MoveEnable strukt�r�va aminek a tartalm�t az hat�rozza meg hogy,a sz�rny megehet egy j�t�kost */
MoveEnable moveAIPlayerKill(Direction dir, Coordinate coords, Level* level);

/* Vizsg�lja hogy  a sz�rny megehet-e egy j�t�kost, ha igen, akkor v�grehajta, vagyis megeszi */
void monsterAiKill(RenderAssets *renderAsset, Level* level, Monster *monster, Player *playerOne, Player *playerTwo);

/* Mozgat egy sz�rnyet */
void monsterAiMove(RenderAssets *renderAsset, Level *level, Monster *monster);

/* �jra spawnol egy j�t�kost, a sz�rnyekt�l egy bizonyos t�vols�gra !!! Nincs force spawn, a j�t�k le�llhat ha nincs el�g t�vols�g !!! */
void respawnPlayer(Monsters *monsters, Level *level, Player *player);

/* Vissz�r egy v�letlenszer� koordin�t�val, ami path-re mutat */
Coordinate getValidPathCoords(Level *level);

/* Igaz ha a megadott ir�nyba a l�p�s megtehet� */
bool checkMovementValidDir(Level* level, Coordinate coords);

/* Megadott ir�nyba visszt�r a megfelel� �j koordin�t�val */
Coordinate getCoordsFromDir(Direction dir, Coordinate coords);

/* Igaz a Monster struktur�ban a dir v�ltoz� ir�ny�ba a l�p�s megtehet� */
bool preferredDirAiMove(RenderAssets *renderAsset, Level *level, Monster *monster);

/* A j�t�k alatt szerzett pontokatt m�d�s�tja a neh�zs�g f�ggv�ny�ben */
int getPointsFromDifficulty(Difficulty difficulty, int score);

/* Felszabad�t a Mosnters strujt�r�t */
void freeMonsters(Monsters *monsters);

/* Inicializ�lja a sz�rnyeket */
Monsters *initMonsters(RenderAssets *renderAsset, Level* level);

/* Ha sfx nem NULL, lej�tsza a hangeffektet */
void playSFX(Mix_Chunk *sfx);
#endif 

