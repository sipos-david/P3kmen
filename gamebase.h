#ifndef GAMEBASE_H
#define GAMEBASE_H
#define _CRT_SECURE_NO_WARNINGS //visual studio scanf,printf hiba�zenet kiiktat�sa

#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include "SDL_image.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

/* Strukt�ra egy koordin�ta elt�rol�s�hoz */
typedef struct Coordinate{
	int x, y;
}Coordinate;

/* Enum a felbonz�shoz */
typedef enum Resolution{
	_1920x1080,
	_1600x900,
	_1280x720,
	_768x432,
}Resolution;

/* Strukt�ra amely az program ablak adatait t�rolja */
typedef struct windowData {
	Resolution res;
	bool isFullscreen;
}windowData;

/* Strukt�ra ami egybefogja a renderert */
typedef struct initRenderer{
	SDL_Window *window;
	SDL_Renderer *renderer;
	int SCREEN_WIDTH, SCREEN_HEIGHT;
}initRenderer;

/* Strukt�ra ami egybefogja a hangokat */
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

/* Strukt�ra ami egyfogja az �sszes text�r�t*/
typedef struct initTexture{
	/* J�t�kos text�r�k */
	SDL_Texture *pacmanA_up;
	SDL_Texture *pacmanA_down;
	SDL_Texture *pacmanA_left;
	SDL_Texture *pacmanA_right;
	SDL_Texture *pacmanB_up;
	SDL_Texture *pacmanB_down;
	SDL_Texture *pacmanB_left;
	SDL_Texture *pacmanB_right;

	/* HUD text�r�k*/

	SDL_Texture *heart;

	/* Sz�rny text�r�k*/
	SDL_Texture *monster_a;
	SDL_Texture *monster_b;
	SDL_Texture *monster_c;

	/* P�lya text�r�k */
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

	/* F�men� text�r�k*/
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

/* Strukt�ra ami elt�rolja egy SDL_ttf bet�t�pus adatait */
typedef struct initFont {
	TTF_Font *font;
	int size;
	SDL_Color color;
}initFont;

/* Strukt�ra ami elt�rolja a megjelen�t�shez �s a hangeffektek adatait */
typedef struct renderAssets {
	initRenderer *renderer;
	initTexture *texture;
	initFont *font;
	initSounds *sounds;
	windowData *windowResolution;
	bool close;
}renderAssets;

/* Strukt�ra a p�lya dimenz�inak */
typedef struct LevelDimensions{
	int rows, colums;
}LevelDimensions;

/* �sszefogja a f�men� renderel�s�hez sz�ks�ges SDL_Rect v�ltoz�kat */
typedef struct initMainMenuCoords{
	SDL_Rect logo, singleplayer, multiplayer, toplist, quit;
}initMainMenuCoords;

/* �sszefogja a dics�s�glista renderel�s�hez sz�ks�ges SDL_Rect v�ltoz�kat */
typedef struct initTopListCoords{
	SDL_Rect toplistTitle,placementsBase;
}initTopListCoords;

/* �sszefogja a neh�zs�g v�laszt� men� renderel�s�hez sz�ks�ges SDL_Rect v�ltoz�kat */
typedef struct initGetDifficultyCoords {
	SDL_Rect difText, difNormalText, difEasyText, difHardText, selectionClear;
}initGetDifficultyCoords;

/* Enumeriz�ci� a p�lya lehets�ges elemihez*/
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

/* Strukt�ra amelyt�rol : egy ir�nyt, koordin�t�t, �s enged�lyez�st �s hogy j�t�kos-e a l�p�s */
typedef struct MoveEnable {
	Direction dir;
	Coordinate coordinate;
	bool enable, isPlayer;
}MoveEnable;

/* Enumeriz�ci� a sz�rny �llapot�hoz */
typedef enum MonsterState{
	basic,
	eatable,
	frozen,
	dead,
}MonsterState;

/* Enumeriz�ci� a j�t�kos �llapot�hoz */
typedef enum PlayerState{
	base,
	dead_player,
	enraged,
}PlayerState;

/* Strukt�ra mely mag�ba foglalja egy j�t�kos adatait */
typedef struct Player{
	TileType id;
	Coordinate coordinate;
	int health,points;
	SDL_Texture *texture;
	Direction direction;
	PlayerState state;
}Player;

/* Strukt�ra mely mag�ba foglalja egy sz�rny adatait */
typedef struct Monster{
	Direction movementDir;
	TileType id;
	Coordinate coordinate;
	SDL_Texture *texture;
	MonsterState state;
}Monster;

/* Strukt�ra amely mag�ba foglalja 3 sz�rny adatait */
typedef struct Monsters{
	Monster *monster_A, *monster_B, *monster_C;
}Monsters;

/* Enumeriz�ci� a neh�zs�gi szinthez */
typedef enum Difficulty{
	easy,
	normal,
	hard,
}Difficulty;

/* Strukt�ra amely egy event idej�t �s �llapot�t */
typedef struct eventTimeAndCondition{
	int timer;
	bool eventState;
}eventTimeAndCondition;

/* Strukt��ra amely t�rolja a j�t�kban l�v� eventeket */
typedef struct TimeHandler {
	int currentTime;
	eventTimeAndCondition eventSpawnUsable,
						  eventRespawnA, eventEnragedA, 
						  eventRespawnB, eventEnragedB, 
						  eventMonsterA_Respawn, eventMonsterB_Respawn, eventMonsterC_Respawn, 
						  eventMonstersFrozen;
}TimeHandler;

/* Strukt�ra, mely mag�ba foglal egy p�ly�t*/
typedef struct Level{
	TimeHandler eventTimer;
	LevelDimensions dimension;
	TileType **map;
	SDL_Rect tile;
	int playerHealthSum, avaliablePoints;
}Level;

/* Enumeriz�ci� amely t�rolja a f�menu lehets�ges men�jeit*/
typedef enum MainMenuSelection{
	notvalidinput,
	singleplayer,
	multiplayer,
	toplist,
	quitgame,
	valaszt,
}MainMenuSelection;

/* Enumeriz�ci� a toplist�hoz */
typedef struct Place{
	char *name;
	int points, placement;
}Place;

#endif