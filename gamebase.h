#ifndef GAMEBASE_H
#define GAMEBASE_H
#define _CRT_SECURE_NO_WARNINGS //visual studio scanf,printf hibaüzenet kiiktatása

#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include "SDL_image.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

/* Struktúra egy koordináta eltárolásához */
typedef struct Coordinate{
	int x, y;
}Coordinate;

/* Enum a felbonzáshoz */
typedef enum Resolution{
	_1920x1080,
	_1600x900,
	_1280x720,
	_768x432,
}Resolution;

/* Struktúra amely az program ablak adatait tárolja */
typedef struct windowData {
	Resolution res;
	bool isFullscreen;
}windowData;

/* Struktúra ami egybefogja a renderert */
typedef struct initRenderer{
	SDL_Window *window;
	SDL_Renderer *renderer;
	int SCREEN_WIDTH, SCREEN_HEIGHT;
}initRenderer;

/* Struktúra ami egybefogja a hangokat */
typedef struct initSounds {
	Mix_Chunk *nom_nom;
	Mix_Chunk *menu_move;
	Mix_Chunk *menu_choose;
	Mix_Chunk *point_normal_eaten;
	Mix_Chunk *point_big_eaten;
	Mix_Chunk *freeze;
	Mix_Chunk *monster_eaten;
	Mix_Chunk *chili;
	Mix_Music *background_music;
}initSounds;

/* Struktúra ami egyfogja az összes textúrát*/
typedef struct initTexture{
	/* Játékos textúrák */
	SDL_Texture *pacmanA_up;
	SDL_Texture *pacmanA_down;
	SDL_Texture *pacmanA_left;
	SDL_Texture *pacmanA_right;
	SDL_Texture *pacmanB_up;
	SDL_Texture *pacmanB_down;
	SDL_Texture *pacmanB_left;
	SDL_Texture *pacmanB_right;

	/* HUD textúrák*/

	SDL_Texture *heart;

	/* Szörny textúrák*/
	SDL_Texture *monster_a;
	SDL_Texture *monster_b;
	SDL_Texture *monster_c;

	/* Pálya textúrák */
	SDL_Texture *path;
	SDL_Texture *path_point;
	SDL_Texture *path_big_point;
	SDL_Texture *shaved_ice;
	SDL_Texture *chili;
	SDL_Texture *wall_0;
	SDL_Texture *wall_1_up;
	SDL_Texture *wall_1_down;
	SDL_Texture *wall_1_left;
	SDL_Texture *wall_1_right;
	SDL_Texture *wall_2_hor;
	SDL_Texture *wall_2_vert;
	SDL_Texture *wall_2_u_r;
	SDL_Texture *wall_2_u_l;
	SDL_Texture *wall_2_d_r;
	SDL_Texture *wall_2_d_l;
	SDL_Texture *wall_3_up;
	SDL_Texture *wall_3_down;
	SDL_Texture *wall_3_left;
	SDL_Texture *wall_3_right;
	SDL_Texture *wall_4;

	/* Fõmenü textúrák*/
	SDL_Texture *mainmenu_logo;
	SDL_Texture *mainmenu_singleplayer_a;
	SDL_Texture *mainmenu_singleplayer_b;
	SDL_Texture *mainmenu_multiplayer_a;
	SDL_Texture *mainmenu_multiplayer_b;
	SDL_Texture *mainmenu_toplist_a;
	SDL_Texture *mainmenu_toplist_b;
	SDL_Texture *mainmenu_quit_a;
	SDL_Texture *mainmenu_quit_b;
}initTexture;

/* Struktúra ami eltárolja egy SDL_ttf betûtípus adatait */
typedef struct initFont {
	TTF_Font *font;
	int size;
	SDL_Color color;
}initFont;

/* Struktúra ami eltárolja a megjelenítéshez és a hangeffektek adatait */
typedef struct renderAssets {
	initRenderer *renderer;
	initTexture *texture;
	initFont *font;
	initSounds *sounds;
	windowData *windowResolution;
	bool close;
}renderAssets;

/* Struktúra a pálya dimenzóinak */
typedef struct LevelDimensions{
	int rows, colums;
}LevelDimensions;

/* Összefogja a fõmenü rendereléséhez szükséges SDL_Rect változókat */
typedef struct initMainMenuCoords{
	SDL_Rect logo, singleplayer, multiplayer, toplist, quit;
}initMainMenuCoords;

/* Összefogja a dicsõséglista rendereléséhez szükséges SDL_Rect változókat */
typedef struct initTopListCoords{
	SDL_Rect toplistTitle,placementsBase;
}initTopListCoords;

/* Összefogja a nehézség választó menü rendereléséhez szükséges SDL_Rect változókat */
typedef struct initGetDifficultyCoords {
	SDL_Rect difText, difNormalText, difEasyText, difHardText, selectionClear;
}initGetDifficultyCoords;

/* Enumerizáció a pálya lehetséges elemihez*/
typedef enum TileType {
	pacmanA,
	pacmanB,
	monsterA,
	monsterB,
	monsterC,
	path,
	path_point,
	path_big_point,
	shaved_ice,
	chili,
	wall_0,
	wall_1_up,
	wall_1_down,
	wall_1_left,
	wall_1_right,
	wall_2_hor,
	wall_2_vert,
	wall_2_u_r,
	wall_2_u_l,
	wall_2_d_r,
	wall_2_d_l,
	wall_3_up,
	wall_3_down,
	wall_3_left,
	wall_3_right,
	wall_4,
}TileType;

typedef enum Direction{
	up = 0,
	down = 1,
	left = 2,
	right = 3,
}Direction;

/* Struktúra amelytárol : egy irányt, koordinátát, és engedélyezést és hogy játékos-e a lépés */
typedef struct MoveEnable {
	Direction dir;
	Coordinate coordinate;
	bool enable, isPlayer;
}MoveEnable;

/* Enumerizáció a szörny állapotához */
typedef enum MonsterState{
	basic,
	eatable,
	frozen,
	dead,
}MonsterState;

/* Enumerizáció a játékos állapotához */
typedef enum PlayerState{
	base,
	dead_player,
	enraged,
}PlayerState;

/* Struktúra mely magába foglalja egy játékos adatait */
typedef struct Player{
	TileType id;
	Coordinate coordinate;
	int health,points;
	SDL_Texture *texture;
	Direction direction;
	PlayerState state;
}Player;

/* Struktúra mely magába foglalja egy szörny adatait */
typedef struct Monster{
	Direction movementDir;
	TileType id;
	Coordinate coordinate;
	SDL_Texture *texture;
	MonsterState state;
}Monster;

/* Struktúra amely magába foglalja 3 szörny adatait */
typedef struct Monsters{
	Monster *monster_A, *monster_B, *monster_C;
}Monsters;

/* Enumerizáció a nehézségi szinthez */
typedef enum Difficulty{
	easy,
	normal,
	hard,
}Difficulty;

/* Struktúra amely egy event idejét és állapotát */
typedef struct eventTimeAndCondition{
	int timer;
	bool eventState;
}eventTimeAndCondition;

/* Struktóúra amely tárolja a játékban lévõ eventeket */
typedef struct TimeHandler {
	int currentTime;
	eventTimeAndCondition eventSpawnUsable,
						  eventRespawnA, eventEnragedA, 
						  eventRespawnB, eventEnragedB, 
						  eventMonsterA_Respawn, eventMonsterB_Respawn, eventMonsterC_Respawn, 
						  eventMonstersFrozen;
}TimeHandler;

/* Struktúra, mely magába foglal egy pályát*/
typedef struct Level{
	TimeHandler eventTimer;
	LevelDimensions dimension;
	TileType **map;
	SDL_Rect tile;
	int playerHealthSum, avaliablePoints;
}Level;

/* Enumerizáció amely tárolja a fõmenu lehetséges menüjeit*/
typedef enum MainMenuSelection{
	notvalidinput,
	singleplayer,
	multiplayer,
	toplist,
	quitgame,
	valaszt,
}MainMenuSelection;

/* Enumerizáció a toplistához */
typedef struct Place{
	char *name;
	int points, placement;
}Place;

#endif