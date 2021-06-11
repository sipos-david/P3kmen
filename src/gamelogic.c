#include "gamebase.h"
#include "gamelogic.h"
#include "render.h"
#include <math.h>

Player playerInit(RenderAssets *renderAsset,Difficulty difficulty,TileType pacmanID,Level *level) {
	Player player;

	switch (difficulty) {
	case easy:
		player.health = 5;
		break;
	case normal:
		player.health = 3;
		break;
	case hard:
		player.health = 1;
		break;
	}

	player.points = 0;
	player.direction = right;

	switch (pacmanID) {
		case pacmanA:
			player.texture = renderAsset->texture->pacmanA_right;
			break;
		case pacmanB:
			player.texture = renderAsset->texture->pacmanB_right;
			break;
		default:
			break;
	}

	player.id = pacmanID;
	player.state = base;
	spawnPlayer(level, &player);

	return player;
}


void spawnPlayer(Level *level, Player *player){
	Coordinate newCoords = getValidCoords(level);
	player->coordinate.x = newCoords.x;
	player->coordinate.y = newCoords.y;
	level->map[player->coordinate.x][player->coordinate.y] = player->id;
}

void spawnMonster(Monster *monster, Level *level){
	int playerNumber = getPlayerNumber(level);
	Coordinate *players = getPlayerCoords(level);
	Coordinate newCoords;
	double minDistance = level->dimension.colums / 3;
	bool allConditionsTrueCheck = true;
	while (allConditionsTrueCheck) {
		newCoords = getValidCoords(level);
		for (int i = 0; i < playerNumber; i++) {
			if (distanceFromAtoB(newCoords, players[i]) >= minDistance)
				allConditionsTrueCheck = false;
		}
	}
	monster->state = basic;
	monster->coordinate.x = newCoords.x;
	monster->coordinate.y = newCoords.y;
	level->map[newCoords.x][newCoords.y] = monster->id;
	free(players);
}

bool moveIsValidCheck(Level *level, Coordinate coordinate){
	if (coordinate.x >= 0 && coordinate.x < level->dimension.colums && coordinate.y >= 0 && coordinate.y < level->dimension.rows) {
		if (level->map[coordinate.x][coordinate.y] == path ||
			level->map[coordinate.x][coordinate.y] == path_point ||
			level->map[coordinate.x][coordinate.y] == path_big_point ||
			level->map[coordinate.x][coordinate.y] == shaved_ice ||
			level->map[coordinate.x][coordinate.y] == chili)
			return true;
	}
	return false;
}

bool isPointCheck(Level *level, Coordinate coordinate){
	if (level->map[coordinate.x][coordinate.y] == path_point ||
		level->map[coordinate.x][coordinate.y] == path_big_point)
		return true;
	return false;
}

bool isLittlePointCheck(Level *level, Coordinate coordinate){
	if (level->map[coordinate.x][coordinate.y] == path_point)
		return true;
	return false;
}

bool isPathCheck(Level *level, Coordinate coordinate) {
	if (level->map[coordinate.x][coordinate.y] == path)
		return true;
	return false;
}

bool isMonsterCheck(Level *level, Coordinate coordinate) {
	if (level->map[coordinate.x][coordinate.y] == monsterA ||
		level->map[coordinate.x][coordinate.y] == monsterB ||
		level->map[coordinate.x][coordinate.y] == monsterC)
		return true;
	return false;
}

void monsterInit(Level *level,Monster *monster,SDL_Texture* texture, TileType id){
	monster->id = id;
	monster->state = basic;
	monster->movementDir = rand() % 4;
	spawnMonster(monster, level);
	monster->texture = texture;
}

double distanceFromAtoB(Coordinate A, Coordinate B){
	return sqrt(pow((A.x - B.x), 2) + pow((A.y - B.y), 2));
}

int getPlayerNumber(Level *level) {
	int playerCount = 0;
	for (int x = 0; x < level->dimension.colums; x++) {
		for (int y = 0; y < level->dimension.rows; y++) {
			if (level->map[x][y] == pacmanA || level->map[x][y] == pacmanB)
				playerCount++;
		}
	}
	return playerCount;
};

Coordinate *getPlayerCoords(Level *level) {
	int playerNumber = getPlayerNumber(level);
	int playerNumberIter = 0;
	Coordinate *playerCoords = (Coordinate*)malloc(playerNumber * sizeof(Coordinate));
	for (int x = 0; x < level->dimension.colums; x++){
		for (int y = 0; y < level->dimension.rows; y++){
			if (level->map[x][y] == pacmanA || level->map[x][y] == pacmanB) {
				playerCoords[playerNumberIter].x = x;
				playerCoords[playerNumberIter].y = y;
			}
		}
	}
	return playerCoords;
}

Coordinate getValidCoords(Level *level){
	Coordinate newCoords;
	newCoords.x = rand() % level->dimension.colums;
	newCoords.y = rand() % level->dimension.rows;
	while (!moveIsValidCheck(level, newCoords)) {
		newCoords.x = rand() % level->dimension.colums;
		newCoords.y = rand() % level->dimension.rows;
	}
	return newCoords;
}

void sumOfAvalaiablePoints(Level* level) {
	level->avaliablePoints = 0;
	Coordinate coords;
	for (int x = 0; x < level->dimension.colums; x++) {
		for (int y = 0; y < level->dimension.rows; y++) {
			coords.x = x;
			coords.y = y;
			if (isPointCheck(level, coords)){
				level->avaliablePoints++;
			}
		}
	}
}

Uint32 timer(Uint32 ms, void *param) {
	SDL_Event ev;
	ev.type = SDL_USEREVENT;
	SDL_PushEvent(&ev);
	return ms;
}


Uint32 timerMonsterAiKill(Uint32 ms, void *param){
	SDL_Event ev;
	ev.type = SDL_USEREVENT+1;
	SDL_PushEvent(&ev);
	return ms;
}

Uint32 timerMonsterAiMove(Uint32 ms, void *param) {
	SDL_Event ev;
	ev.type = SDL_USEREVENT + 2;
	SDL_PushEvent(&ev);
	return ms;
}


void playGame(RenderAssets *renderAsset, Level* level, Player *playerOne, Player *playerTwo, Monsters* baddies){
	SDL_TimerID timer1SecID = SDL_AddTimer(1000, timer, NULL);
	SDL_TimerID timerForMonsterAiKill = SDL_AddTimer(100, timerMonsterAiKill, NULL);
	SDL_TimerID timerForMonsterAiMove = SDL_AddTimer(200, timerMonsterAiMove, NULL);
	Coordinate hudZero = getHUDZeroPoint(level);
	renderHUD(renderAsset, hudZero, playerOne, playerTwo, level->eventTimer.eventMonstersFrozen.eventState);
	if (Mix_PlayingMusic() == 0 && renderAsset->sounds->background_music != NULL) {
		Mix_PlayMusic(renderAsset->sounds->background_music, -1);
		Mix_VolumeMusic(4);
	}
	SDL_Event eventSinglePlayer;
	bool gameEnd = false;
	int playerPointsOld = 0, playerHealthOld = 0;
	if (playerOne != NULL)
		playerHealthOld += playerOne->health;
	if (playerTwo != NULL)
		playerHealthOld += playerTwo->health;
	while (!gameEnd){
		while (SDL_PollEvent(&eventSinglePlayer)){
			switch (eventSinglePlayer.type) {
				case SDL_USEREVENT:
					clockHandler(&level->eventTimer);
					renderHUD(renderAsset, hudZero, playerOne, playerTwo, level->eventTimer.eventMonstersFrozen.eventState); /* másodpercenként való újból kirjazolás az idõzített események miatt, chili, fagyasztás*/
					timedEventHandler(level,baddies, playerOne, playerTwo);
					break;
				case SDL_USEREVENT+1:
					if (baddies->monster_A->state != dead && baddies->monster_A->state != frozen) monsterAiKill(renderAsset, level, baddies->monster_A, playerOne, playerTwo);
					if (baddies->monster_B->state != dead && baddies->monster_A->state != frozen) monsterAiKill(renderAsset, level, baddies->monster_B, playerOne, playerTwo);
					if (baddies->monster_C->state != dead && baddies->monster_A->state != frozen) monsterAiKill(renderAsset, level, baddies->monster_C, playerOne, playerTwo);
					break;
				case SDL_USEREVENT + 2:
					if (baddies->monster_A->state != dead && baddies->monster_A->state != frozen) monsterAiMove(renderAsset, level, baddies->monster_A);
					if (baddies->monster_B->state != dead && baddies->monster_B->state != frozen) monsterAiMove(renderAsset, level, baddies->monster_B);
					if (baddies->monster_C->state != dead && baddies->monster_C->state != frozen) monsterAiMove(renderAsset, level, baddies->monster_C);
					break;
				case SDL_KEYDOWN:
					keyBoardInputHandler(renderAsset, level, &eventSinglePlayer, playerOne, playerTwo, baddies);
					break;
				case SDL_QUIT:
					Mix_HaltMusic();
					SDL_RemoveTimer(timer1SecID);
					SDL_RemoveTimer(timerForMonsterAiKill);
					SDL_RemoveTimer(timerForMonsterAiMove);
					renderAsset->close = true;
					return;
					break;
				default:
					break;
			}
		}
		if(updateHUDCheck(&playerPointsOld, &playerHealthOld, playerOne, playerTwo))
			renderHUD(renderAsset,hudZero, playerOne, playerTwo, level->eventTimer.eventMonstersFrozen.eventState);
		renderMapWithoutEntities(level, renderAsset);
		renderMapJustEntities(level,renderAsset, playerOne, playerTwo,baddies);
		gameEnd = gameEndCheck(level);
		//printDataToConsole(level, playerOne, playerTwo,baddies);
	}
	Mix_HaltMusic();
	SDL_RemoveTimer(timer1SecID);
	SDL_RemoveTimer(timerForMonsterAiKill);
	SDL_RemoveTimer(timerForMonsterAiMove);
}

void printDataToConsole(Level *level, Player *playerOne, Player *playerTwo,Monsters *baddies){

	if (playerOne != NULL){
		printf("playerOne coords: (%2d,%2d) player state: ", playerOne->coordinate.x, playerOne->coordinate.x);
		if (playerOne->state == base) printf("base\n\n");
		if (playerOne->state == dead_player) printf("dead_player\n\n");
		if (playerOne->state == enraged) printf("enraged\n\n");
	}

	if (playerTwo != NULL){
		printf("playerTwo coords: (%2d,%2d) player state: ", playerTwo->coordinate.x, playerTwo->coordinate.x);
		if (playerTwo->state == base) printf("base\n\n");
		if (playerTwo->state == dead_player) printf("dead_player\n\n");
		if (playerTwo->state == enraged) printf("enraged\n\n");
	}

	printf("max lives: %2d     avaliable points: %d\n\n", level->playerHealthSum, level->avaliablePoints);

	printf("monster_A coords: (%2d,%2d) monster_A state: ", baddies->monster_A->coordinate.x, baddies->monster_A->coordinate.x);
	if (baddies->monster_A->state == basic) printf("basic\n");
	if (baddies->monster_A->state == eatable) printf("eatable\n");
	if (baddies->monster_A->state == frozen) printf("frozen\n");
	if (baddies->monster_A->state == dead) printf("dead\n");

	printf("monster_B coords: (%2d,%2d) monster_B state: ", baddies->monster_B->coordinate.x, baddies->monster_B->coordinate.x);
	if (baddies->monster_B->state == basic) printf("basic\n");
	if (baddies->monster_B->state == eatable) printf("eatable\n");
	if (baddies->monster_B->state == frozen) printf("frozen\n");
	if (baddies->monster_B->state == dead) printf("dead\n");

	printf("monster_C coords: (%2d,%2d) monster_C state: ", baddies->monster_C->coordinate.x, baddies->monster_C->coordinate.x);
	if (baddies->monster_C->state == basic) printf("basic\n\n");
	if (baddies->monster_C->state == eatable) printf("eatable\n\n");
	if (baddies->monster_C->state == frozen) printf("frozen\n\n");
	if (baddies->monster_C->state == dead) printf("dead\n\n");

	printf("eventSpawnUsable       active: %d  time: %2d\n",level->eventTimer.eventSpawnUsable.eventState, level->eventTimer.eventSpawnUsable.timer );
	printf("eventRespawnA          active: %d  time: %2d\n", level->eventTimer.eventRespawnA.eventState, level->eventTimer.eventRespawnA.timer);
	printf("eventEnragedA          active: %d  time: %2d\n", level->eventTimer.eventEnragedA.eventState, level->eventTimer.eventEnragedA.timer);
	printf("eventRespawnB          active: %d  time: %2d\n", level->eventTimer.eventRespawnB.eventState, level->eventTimer.eventRespawnB.timer);
	printf("eventEnragedB          active: %d  time: %2d\n", level->eventTimer.eventEnragedB.eventState, level->eventTimer.eventEnragedB.timer);
	printf("eventMonsterA_Respawn  active: %d  time: %2d\n", level->eventTimer.eventMonsterA_Respawn.eventState, level->eventTimer.eventMonsterA_Respawn.timer);
	printf("eventMonsterB_Respawn  active: %d  time: %2d\n", level->eventTimer.eventMonsterB_Respawn.eventState, level->eventTimer.eventMonsterB_Respawn.timer);
	printf("eventMonsterC_Respawn  active: %d  time: %2d\n", level->eventTimer.eventMonsterC_Respawn.eventState, level->eventTimer.eventMonsterC_Respawn.timer);
	printf("eventMonstersFrozen    active: %d  time: %2d\n", level->eventTimer.eventMonstersFrozen.eventState, level->eventTimer.eventMonstersFrozen.timer);

	system("cls");
}

bool gameEndCheck(Level* level){
	sumOfAvalaiablePoints(level);
	if (level->playerHealthSum == 0 || level->avaliablePoints == 0)
		return true;
	else return false;
}

void keyBoardInputHandler(RenderAssets *renderAsset, Level* level, SDL_Event *event, Player *playerOne, Player *playerTwo, Monsters *monsters) {
	if (playerOne != NULL && playerOne->state != dead_player ) {
		switch (event->key.keysym.sym) {
			case SDLK_UP:
				playerOne->texture = renderAsset->texture->pacmanA_up;
				playerMoveToNewDest(renderAsset, level, playerOne, up, monsters);
				break;
			case SDLK_DOWN:
				playerOne->texture = renderAsset->texture->pacmanA_down;
				playerMoveToNewDest(renderAsset, level, playerOne, down, monsters);
				break;
			case SDLK_LEFT:
				playerOne->texture = renderAsset->texture->pacmanA_left;
				playerMoveToNewDest(renderAsset, level, playerOne, left, monsters);
				break;
			case SDLK_RIGHT:
				playerOne->texture = renderAsset->texture->pacmanA_right;
				playerMoveToNewDest(renderAsset, level, playerOne, right, monsters);
				break;
			default:
				break;
		}
	}
	if (playerTwo != NULL && playerTwo->state != dead_player) {
		switch (event->key.keysym.sym) {
			case SDLK_w:
				playerTwo->texture = renderAsset->texture->pacmanB_up;
				playerMoveToNewDest(renderAsset, level, playerTwo, up, monsters);
				break;
			case SDLK_s:
				playerTwo->texture = renderAsset->texture->pacmanB_down;
				playerMoveToNewDest(renderAsset, level, playerTwo, down, monsters);
				break;
			case SDLK_a:
				playerTwo->texture = renderAsset->texture->pacmanB_left;
				playerMoveToNewDest(renderAsset, level, playerTwo, left, monsters);
				break;
			case SDLK_d:
				playerTwo->texture = renderAsset->texture->pacmanB_right;
				playerMoveToNewDest(renderAsset, level, playerTwo, right, monsters);
				break;
			default:
				break;
		}
	}
}

void playerMoveToNewDest(RenderAssets *renderAsset, Level *level, Player *player, Direction dir, Monsters *monsters){
	Coordinate newCoords = getCoordinateFromDirection(level->dimension, player->coordinate,dir);
	if (moveIsValidCheck(level, newCoords)) {
		switch (level->map[newCoords.x][newCoords.y]) {
			case path:
				moveEntityToDest(renderAsset, level, player->id, player->coordinate, newCoords, player->texture, dir, true);
				player->coordinate.x = newCoords.x;
				player->coordinate.y = newCoords.y;
				break;
			case path_point:
				playSFX(renderAsset->sounds->point_normal_eaten);
				level->avaliablePoints--;
				player->points += 10;
				moveEntityToDest(renderAsset, level, player->id, player->coordinate, newCoords, player->texture, dir, true);
				player->coordinate.x = newCoords.x;
				player->coordinate.y = newCoords.y;
				break;
			case path_big_point:
				playSFX(renderAsset->sounds->point_big_eaten);
				level->avaliablePoints--;
				player->points += 30;
				moveEntityToDest(renderAsset, level, player->id, player->coordinate, newCoords, player->texture, dir, true);
				player->coordinate.x = newCoords.x;
				player->coordinate.y = newCoords.y;
				break;
			case shaved_ice:
				playSFX(renderAsset->sounds->freeze);
				player->points += 50;
				if (monsters->monster_A->state != dead) monsters->monster_A->state = frozen;
				if (monsters->monster_B->state != dead) monsters->monster_B->state = frozen;
				if (monsters->monster_C->state != dead) monsters->monster_C->state = frozen;
				level->eventTimer.eventMonstersFrozen.timer = 10; // 5 másodperc fagyasztás
				level->eventTimer.eventMonstersFrozen.eventState = true;
				moveEntityToDest(renderAsset, level, player->id, player->coordinate, newCoords, player->texture, dir, true);
				player->coordinate.x = newCoords.x;
				player->coordinate.y = newCoords.y;
				break;
			case chili:
				playSFX(renderAsset->sounds->chili);
				if (player->id == pacmanA) {
					level->eventTimer.eventEnragedA.eventState = true;
					level->eventTimer.eventEnragedA.timer = 10;
				}
				else if (player->id == pacmanB) {
					level->eventTimer.eventEnragedB.eventState = true;
					level->eventTimer.eventEnragedB.timer = 10;
				}
				player->state = enraged;
				player->points += 25;
				moveEntityToDest(renderAsset, level, player->id, player->coordinate, newCoords, player->texture, dir, true);
				player->coordinate.x = newCoords.x;
				player->coordinate.y = newCoords.y;
				break;
			default:
				break;
		}
	}
	if (player->state == enraged) {
		if (isMonsterCheck(level,newCoords)) {
			switch (level->map[newCoords.x][newCoords.y]){
				case monsterA:
					monsters->monster_A->state = dead;
					level->eventTimer.eventMonsterA_Respawn.eventState = true;
					level->eventTimer.eventMonsterA_Respawn.timer = 10;
					break;
				case monsterB:
					monsters->monster_B->state = dead;
					level->eventTimer.eventMonsterB_Respawn.eventState = true;
					level->eventTimer.eventMonsterB_Respawn.timer = 10;
					break;
				case monsterC:
					monsters->monster_C->state = dead;
					level->eventTimer.eventMonsterC_Respawn.eventState = true;
					level->eventTimer.eventMonsterC_Respawn.timer = 10;
					break;
				default:
					break;
			}
			playSFX(renderAsset->sounds->monster_eaten);
			player->points += 50;
			moveEntityToDest(renderAsset, level, player->id, player->coordinate, newCoords, player->texture, dir, true);
			player->coordinate.x = newCoords.x;
			player->coordinate.y = newCoords.y;
		}
	}
}

Coordinate getCoordinateFromDirection(LevelDimensions size,Coordinate coords, Direction dir) {
	switch (dir) {
		case up:
			if (coords.x >= 0)
				coords.x -= 1;
			break;
		case down:
			if (coords.x + 1 < size.colums)
				coords.x += 1;
			break;
		case left:
			if (coords.y - 1 >= 0)
				coords.y -= 1;
			break;
		case right:
			if (coords.y + 1 < size.rows)
				coords.y += 1;
			break;
	}
	return coords;
}

void moveEntityToDest(RenderAssets *renderAsset, Level *level,TileType id, Coordinate oldCoords ,Coordinate newCoords, SDL_Texture *texture, Direction dir, bool isPlayer){
	if (isPlayer) {
		level->map[newCoords.x][newCoords.y] = id;
		level->map[oldCoords.x][oldCoords.y] = path;
	}
	else {
		TileType tmp = level->map[newCoords.x][newCoords.y];
		level->map[newCoords.x][newCoords.y] = id;
		level->map[oldCoords.x][oldCoords.y] = tmp;
	}
	renderAnimateEntity(renderAsset, level,texture,newCoords,oldCoords,dir);
}

Direction getDirectionFromCoords(Coordinate newCoords, Coordinate oldCoords){
	Direction dir;
	if (newCoords.x > oldCoords.x)
		dir = down;
	else if (newCoords.x < oldCoords.x)
		dir = up;
	if (newCoords.y > oldCoords.y)
		dir = right;
	else if (newCoords.y > oldCoords.y)
		dir = left;
	return dir;
}

void bigPointsInit(Level* level){
	int bigPointNumber = level->avaliablePoints / 6;
	Coordinate coords;
	while (bigPointNumber >= 0) {
		coords = getValidCoords(level);
		if (isLittlePointCheck(level, coords)) {
			level->map[coords.x][coords.y] = path_big_point;
			bigPointNumber -= 1;
		}
	}
}

Coordinate getHUDZeroPoint(Level *level) {
	Coordinate tmp;
	tmp.x = level->tile.w * level->dimension.colums;
	tmp.y = 0;
	return tmp;
}

bool updateHUDCheck(int *playerPointsOld, int *playerSumHealtOld, Player *playerOne, Player *playerTwo){
	int playerPointsCurrent = 0, playerSumHealthCurrent = 0;
	if (playerOne != NULL) {
		playerPointsCurrent += playerOne->points;
		playerSumHealthCurrent += playerOne->health;
	}
	if (playerTwo != NULL) {
		playerPointsCurrent += playerTwo->points;
		playerSumHealthCurrent += playerTwo->health;
	}
	if (playerPointsCurrent > *playerPointsOld || playerSumHealthCurrent < *playerSumHealtOld){
		*playerPointsOld = playerPointsCurrent;
		*playerSumHealtOld = playerSumHealthCurrent;
		return true;
	}
	return false;
}

void clockHandler(TimeHandler *eventTimer){
	if (eventTimer->currentTime < 31)
		eventTimer->currentTime++;
	else eventTimer->currentTime = 1;

	if (eventTimer->eventSpawnUsable.timer < 21) {
		eventTimer->eventSpawnUsable.timer++;
	}
	else{
		eventTimer->eventSpawnUsable.timer = 1; 
		eventTimer->eventSpawnUsable.eventState = true;
	}

	if (eventTimer->eventRespawnA.eventState == true && eventTimer->eventRespawnA.timer > 0) {
		eventTimer->eventRespawnA.timer--;
	}
	if (eventTimer->eventEnragedA.eventState == true && eventTimer->eventEnragedA.timer > 0) {
		eventTimer->eventEnragedA.timer--;
	}
	if (eventTimer->eventRespawnB.eventState == true && eventTimer->eventRespawnB.timer > 0) {
		eventTimer->eventRespawnB.timer--;
	}
	if (eventTimer->eventEnragedB.eventState == true && eventTimer->eventEnragedB.timer > 0) {
		eventTimer->eventEnragedB.timer--;
	}
	if (eventTimer->eventMonsterA_Respawn.eventState == true && eventTimer->eventMonsterA_Respawn.timer > 0) {
		eventTimer->eventMonsterA_Respawn.timer--;
	}
	if (eventTimer->eventMonsterB_Respawn.eventState == true && eventTimer->eventMonsterB_Respawn.timer > 0) {
		eventTimer->eventMonsterB_Respawn.timer--;
	}
	if (eventTimer->eventMonsterC_Respawn.eventState == true && eventTimer->eventMonsterC_Respawn.timer > 0) {
		eventTimer->eventMonsterC_Respawn.timer--;
	}
	if (eventTimer->eventMonstersFrozen.eventState == true && eventTimer->eventMonstersFrozen.timer > 0) {
		eventTimer->eventMonstersFrozen.timer--;
	}


}

void spawnUsables(Level *level){
	Coordinate coords = getValidCoords(level);
	while (!isPathCheck(level,coords)){
		coords = getValidCoords(level);
	}
	if (rand() % 2 == 0)
		level->map[coords.x][coords.y] = chili;
	else level->map[coords.x][coords.y] = shaved_ice;
}

void levelInitEventTimer(TimeHandler *eventTimer){
	eventTimer->currentTime = 1;

	initEventTimeAndCondition(&eventTimer->eventSpawnUsable);

	initEventTimeAndCondition(&eventTimer->eventRespawnA);
	initEventTimeAndCondition(&eventTimer->eventEnragedA);

	initEventTimeAndCondition(&eventTimer->eventRespawnB);
	initEventTimeAndCondition(&eventTimer->eventEnragedB);

	initEventTimeAndCondition(&eventTimer->eventMonsterA_Respawn);
	initEventTimeAndCondition(&eventTimer->eventMonsterB_Respawn);
	initEventTimeAndCondition(&eventTimer->eventMonsterC_Respawn);

	initEventTimeAndCondition(&eventTimer->eventMonstersFrozen);
}

void initEventTimeAndCondition(eventTimeAndCondition *event) {
	event->eventState = false;
	event->timer = 0;
}

void timedEventHandler(Level* level,Monsters *monsters, Player *playerOne, Player *playerTwo){
	if (level->eventTimer.eventSpawnUsable.eventState == true && level->eventTimer.eventSpawnUsable.timer == 1) {
		spawnUsables(level);
		level->eventTimer.eventSpawnUsable.eventState = false;
	}

	if (level->eventTimer.eventRespawnA.eventState == true && level->eventTimer.eventRespawnA.timer == 0){
		if (playerOne->health > 0)respawnPlayer(monsters,level,playerOne);
		level->eventTimer.eventRespawnA.eventState = false;
	}
	if (level->eventTimer.eventEnragedA.eventState == true && level->eventTimer.eventEnragedA.timer == 0){
		playerOne->state = base;
		level->eventTimer.eventEnragedA.eventState = false;
	}
	if (level->eventTimer.eventRespawnB.eventState == true && level->eventTimer.eventRespawnB.timer == 0){
		if (playerTwo->health > 0) respawnPlayer(monsters, level, playerTwo);
		level->eventTimer.eventRespawnB.eventState = false;
	}
	if (level->eventTimer.eventEnragedB.eventState == true && level->eventTimer.eventEnragedB.timer == 0){
		playerTwo->state = base;
		level->eventTimer.eventEnragedB.eventState = false;
	}
	if (level->eventTimer.eventMonsterA_Respawn.eventState == true && level->eventTimer.eventMonsterA_Respawn.timer == 0){
		spawnMonster(monsters->monster_A,level);
		level->eventTimer.eventMonsterA_Respawn.eventState = false;
	}
	if (level->eventTimer.eventMonsterB_Respawn.eventState == true && level->eventTimer.eventMonsterB_Respawn.timer == 0){
		spawnMonster(monsters->monster_B, level);
		level->eventTimer.eventMonsterB_Respawn.eventState = false;
	}
	if (level->eventTimer.eventMonsterC_Respawn.eventState == true && level->eventTimer.eventMonsterC_Respawn.timer == 0){
		spawnMonster(monsters->monster_C, level);
		level->eventTimer.eventMonsterC_Respawn.eventState = false;
	}
	if (level->eventTimer.eventMonstersFrozen.eventState == true && level->eventTimer.eventMonstersFrozen.timer == 0){
		if (monsters->monster_A->state != dead) monsters->monster_A->state = basic;
		if (monsters->monster_B->state != dead) monsters->monster_B->state = basic;
		if (monsters->monster_C->state != dead) monsters->monster_C->state = basic;
		level->eventTimer.eventMonstersFrozen.eventState = false;
	}
}

MoveEnable moveAIPlayerKill(Direction dir, Coordinate coords, Level* level){
	MoveEnable nextMove;
	switch (dir){
		case up:
			coords.x -= 1;
			if (checkMovementValidDir(level, coords) && (level->map[coords.x][coords.y] == pacmanA || level->map[coords.x][coords.y] == pacmanB)){
				nextMove.enable = true;
				nextMove.isPlayer = true;
			}
			else{
				nextMove.enable = false;
				nextMove.isPlayer = false;
			}
			nextMove.dir = up;
			break;
		case down:
			coords.x += 1;
			if (checkMovementValidDir(level, coords) && (level->map[coords.x][coords.y] == pacmanA || level->map[coords.x][coords.y] == pacmanB)){
				nextMove.enable = true;
				nextMove.isPlayer = true;
			}
			else {
				nextMove.enable = false;
				nextMove.isPlayer = false;
			}
			nextMove.dir = down;
			break;
		case right:
			coords.y += 1;
			if (checkMovementValidDir(level, coords) && (level->map[coords.x][coords.y] == pacmanA || level->map[coords.x][coords.y] == pacmanB)){
				nextMove.enable = true;
				nextMove.isPlayer = true;
			}
			else {
				nextMove.enable = false;
				nextMove.isPlayer = false;
			}
			nextMove.dir = right;
			break;
		case left:
			coords.y -= 1;
			if (checkMovementValidDir(level, coords) && (level->map[coords.x][coords.y] == pacmanA || level->map[coords.x][coords.y] == pacmanB)){
				nextMove.enable = true;
				nextMove.isPlayer = true;
			}
			else {
				nextMove.enable = false;
				nextMove.isPlayer = false;
			}
			nextMove.dir = left;
			break;
	}
	nextMove.coordinate = coords;
	return nextMove;
}
void  monsterMoveAiExecute(RenderAssets *renderAsset, Level *level, Monster *monster, Player *player, Direction dir, MoveEnable nextMove){
	if (nextMove.enable && nextMove.isPlayer) {
		playSFX(renderAsset->sounds->nom_nom);
		if (level->map[nextMove.coordinate.x][nextMove.coordinate.y] == pacmanA && player->state == base) {
			player->health--;
			player->state = dead_player;
			level->playerHealthSum--;
			level->eventTimer.eventRespawnA.eventState = true;
			level->eventTimer.eventRespawnA.timer = 5;
		}
		if (level->map[nextMove.coordinate.x][nextMove.coordinate.y] == pacmanB && player->state == base) {
			player->health--;
			player->state = dead_player;
			level->playerHealthSum--;
			level->eventTimer.eventRespawnB.eventState = true;
			level->eventTimer.eventRespawnB.timer = 5;
		}
		level->map[nextMove.coordinate.x][nextMove.coordinate.y] = path;
		moveEntityToDest(renderAsset, level, monster->id, monster->coordinate, nextMove.coordinate, monster->texture, dir, false);
		monster->coordinate.x = nextMove.coordinate.x;
		monster->coordinate.y = nextMove.coordinate.y;
	}
}


void monsterAiKill(RenderAssets *renderAsset, Level *level, Monster *monster, Player *playerOne, Player *playerTwo){
	MoveEnable nextMove = moveAIPlayerKill(up,monster->coordinate,level);
	if (nextMove.enable && nextMove.isPlayer && level->map[nextMove.coordinate.x][nextMove.coordinate.y] == pacmanA && playerOne->state == base) {
		monsterMoveAiExecute(renderAsset, level, monster, playerOne, up, nextMove);
	}
	nextMove = moveAIPlayerKill(down, monster->coordinate, level);
	if (nextMove.enable && nextMove.isPlayer && level->map[nextMove.coordinate.x][nextMove.coordinate.y] == pacmanA && playerOne->state == base) {
		monsterMoveAiExecute(renderAsset, level, monster, playerOne, down, nextMove);
	}
	nextMove = moveAIPlayerKill(left, monster->coordinate, level);
	if (nextMove.enable && nextMove.isPlayer && level->map[nextMove.coordinate.x][nextMove.coordinate.y] == pacmanA && playerOne->state == base) {
		monsterMoveAiExecute(renderAsset, level, monster, playerOne, left, nextMove);
	}
	nextMove = moveAIPlayerKill(right, monster->coordinate, level);
	if (nextMove.enable && nextMove.isPlayer && level->map[nextMove.coordinate.x][nextMove.coordinate.y] == pacmanA && playerOne->state == base) {
		monsterMoveAiExecute(renderAsset, level, monster, playerOne, right, nextMove);
	}

	nextMove = moveAIPlayerKill(up, monster->coordinate, level);
	if (nextMove.enable && nextMove.isPlayer && level->map[nextMove.coordinate.x][nextMove.coordinate.y] == pacmanB && playerTwo->state == base) {
		monsterMoveAiExecute(renderAsset, level, monster,  playerTwo, up, nextMove);
	}
	nextMove = moveAIPlayerKill(down, monster->coordinate, level);
	if (nextMove.enable && nextMove.isPlayer && level->map[nextMove.coordinate.x][nextMove.coordinate.y] == pacmanB && playerTwo->state == base) {
		monsterMoveAiExecute(renderAsset, level, monster, playerTwo, down, nextMove);
	}
	nextMove = moveAIPlayerKill(left, monster->coordinate, level);
	if (nextMove.enable && nextMove.isPlayer && level->map[nextMove.coordinate.x][nextMove.coordinate.y] == pacmanB && playerTwo->state == base) {
		monsterMoveAiExecute(renderAsset, level, monster, playerTwo, left, nextMove);
	}
	nextMove = moveAIPlayerKill(right, monster->coordinate, level);
	if (nextMove.enable && nextMove.isPlayer && level->map[nextMove.coordinate.x][nextMove.coordinate.y] == pacmanB && playerTwo->state == base) {
		monsterMoveAiExecute(renderAsset, level, monster, playerTwo, right, nextMove);
	}
}

void monsterAiMove(RenderAssets *renderAsset, Level *level, Monster *monster){
	if (preferredDirAiMove(renderAsset, level, monster)) {
		return;
	}
	monster->movementDir = rand() % 4;
	preferredDirAiMove(renderAsset, level, monster);
}

bool preferredDirAiMove(RenderAssets *renderAsset, Level *level, Monster *monster){
	Coordinate newCoords = getCoordsFromDir(monster->movementDir, monster->coordinate);
	if (checkMovementValidDir(level, newCoords) && moveIsValidCheck(level, newCoords)){
		moveEntityToDest(renderAsset, level, monster->id, monster->coordinate, newCoords, monster->texture, monster->movementDir, false);
		monster->coordinate.x = newCoords.x;
		monster->coordinate.y = newCoords.y;
	}
	return false;
}

Coordinate getCoordsFromDir(Direction dir,Coordinate coords) {
	switch (dir) {
		case up:
			coords.x -= 1;
			break;
		case down:
			coords.x += 1;
			break;
		case right:
			coords.y += 1;
			break;
		case left:
			coords.y -= 1;
			break;
	}
	return coords;
}
void respawnPlayer(Monsters *monsters, Level *level,Player *player) {
	Coordinate newCoords;
	double minDistance = level->dimension.colums / 4;
	bool allConditionsTrueCheck = true;
	while (allConditionsTrueCheck) {
		newCoords = getValidPathCoords(level);
		if (distanceFromAtoB(monsters->monster_A->coordinate, newCoords) >= minDistance){
			if (distanceFromAtoB(monsters->monster_B->coordinate, newCoords) >= minDistance){
				if (distanceFromAtoB(monsters->monster_C->coordinate, newCoords) >= minDistance){
					allConditionsTrueCheck = false;
				}
			}
		}
	}
	player->state = base;
	player->coordinate.x = newCoords.x;
	player->coordinate.y = newCoords.y;
	level->map[newCoords.x][newCoords.y] = player->id;
}

Coordinate getValidPathCoords(Level *level){
	Coordinate newCoords;
	newCoords.x = rand() % level->dimension.colums;
	newCoords.y = rand() % level->dimension.rows;
	while (!isPathCheck(level, newCoords)){
		newCoords.x = rand() % level->dimension.colums;
		newCoords.y = rand() % level->dimension.rows;
	}
	return newCoords;
}

bool checkMovementValidDir(Level* level, Coordinate coords){
	if (level->dimension.colums <= coords.x || 0 > coords.x)
		return false;
	if (level->dimension.rows <= coords.y || 0 > coords.y)
		return false;
	return true;
}

int getPointsFromDifficulty(Difficulty difficulty, int score) {
	switch (difficulty) {
		case easy:
			score = score * 2 / 3;
			break;
		case normal:
			score *= 1;
			break;
		case hard:
			score = score * 4 / 3;
			break;
		default:
			break;
	}
	return score;
}

void freeMonsters(Monsters *monsters) {
	free(monsters->monster_A);
	free(monsters->monster_B);
	free(monsters->monster_C);
	free(monsters);
}

Monsters *initMonsters(RenderAssets *renderAsset,Level* level) {
	Monsters *enemies = (Monsters*)malloc(sizeof(Monsters));

	enemies->monster_A = (Monster*)malloc(sizeof(Monster));
	enemies->monster_B = (Monster*)malloc(sizeof(Monster));
	enemies->monster_C = (Monster*)malloc(sizeof(Monster));

	monsterInit(level, enemies->monster_A, renderAsset->texture->monster_a, monsterA);
	monsterInit(level, enemies->monster_B, renderAsset->texture->monster_b, monsterB);
	monsterInit(level, enemies->monster_C, renderAsset->texture->monster_c, monsterC);

	return enemies;
}

void playSFX(Mix_Chunk *sfx) {
	if (sfx != NULL)
		Mix_PlayChannel(-1, sfx, 0);
}