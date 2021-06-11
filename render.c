#include "gamebase.h" 
#include "render.h"
#include "rendercalc.h"
#include "IOput.h"
#include "gamelogic.h"

Renderer initRender(windowData windowResolution){
	Renderer renderer;
	//renderer.SCREEN_WIDTH  = 1280;
	//renderer.SCREEN_HEIGHT = 720;

	switch (windowResolution.res) {
		case _768x432:
			renderer.SCREEN_WIDTH = 768;
			renderer.SCREEN_HEIGHT = 432;
			break;
		case _1280x720:
			renderer.SCREEN_WIDTH = 1280;
			renderer.SCREEN_HEIGHT = 720;
			 break;
		case _1600x900:
			renderer.SCREEN_WIDTH = 1600;
			renderer.SCREEN_HEIGHT = 900;
			break;
		case _1920x1080:
			renderer.SCREEN_WIDTH = 1920;
			renderer.SCREEN_HEIGHT = 1080;
			break;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		printf("SDL could not initialiaze! SDL_error: %s\n", SDL_GetError());
	}
	else {
		renderer.window = SDL_CreateWindow("P3Kmen", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
							  renderer.SCREEN_WIDTH, renderer.SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (renderer.window == NULL) {
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		}	
		renderer.renderer = SDL_CreateRenderer(renderer.window, -1, SDL_RENDERER_ACCELERATED);
		if (renderer.renderer == NULL) {
			printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
		}
		SDL_ShowCursor(SDL_DISABLE);
		if (TTF_Init() == -1){
			printf("SDL_ttf could not be initialized! SDL_Error: %s\n", TTF_GetError());
		}
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		{
			printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		}
	}

	if (windowResolution.isFullscreen)
		SDL_SetWindowFullscreen(renderer.window, SDL_WINDOW_FULLSCREEN);

	return renderer;
}

Sounds loadSounds(void) {
	Sounds sounds;

	sounds.background_music = Mix_LoadMUS("resources/sounds/Loyalty_Freak_Music_-_Sweat_Time.wav");
	if (sounds.background_music == NULL)
		printf("Failed to load - background_music - music! SDL_mixer Error: %s\n", Mix_GetError());

	sounds.menu_choose = Mix_LoadWAV("resources/sounds/menu_choose.wav");
	if (sounds.menu_choose == NULL)
		printf("Failed to load - menu_choose - effect! SDL_mixer Error: %s\n", Mix_GetError());

	sounds.menu_move = Mix_LoadWAV("resources/sounds/menu_click.wav");
	if (sounds.menu_move == NULL)
		printf("Failed to load - sounds.menu_move - effect! SDL_mixer Error: %s\n", Mix_GetError());

	sounds.nom_nom = Mix_LoadWAV("resources/sounds/nom_nom.wav");
	if (sounds.nom_nom == NULL)
		printf("Failed to load - sounds.nom_nom - effect! SDL_mixer Error: %s\n", Mix_GetError());

	sounds.point_normal_eaten = Mix_LoadWAV("resources/sounds/point_normal_eaten.wav");
	if (sounds.point_normal_eaten == NULL)
		printf("Failed to load - point_normal_eaten - effect! SDL_mixer Error: %s\n", Mix_GetError());

	sounds.point_big_eaten = Mix_LoadWAV("resources/sounds/point_big_eaten.wav");
	if (sounds.point_big_eaten == NULL)
		printf("Failed to load - point_big_eaten - effect! SDL_mixer Error: %s\n", Mix_GetError());

	sounds.freeze = Mix_LoadWAV("resources/sounds/freeze.wav");
	if (sounds.freeze == NULL)
		printf("Failed to load - freeze - effect! SDL_mixer Error: %s\n", Mix_GetError());

	sounds.monster_eaten = Mix_LoadWAV("resources/sounds/monster_eaten.wav");
	if (sounds.monster_eaten == NULL)
		printf("Failed to load - monster_eaten - effect! SDL_mixer Error: %s\n", Mix_GetError());

	sounds.chili = Mix_LoadWAV("resources/sounds/chili.wav");
	if (sounds.chili == NULL)
		printf("Failed to load - chili - effect! SDL_mixer Error: %s\n", Mix_GetError());

	return sounds;
}

SDL_Texture *loadImage(const char *picture, Renderer *renderer) {
	SDL_RenderClear(renderer->renderer);
	SDL_Surface *loadedImage = IMG_Load(picture);
	if (loadedImage == NULL)
		printf("Error: failed IMG_load: %s\n", IMG_GetError());
	SDL_Texture *loadedTexture = SDL_CreateTextureFromSurface(renderer->renderer, loadedImage);
	if (loadedTexture == NULL)
		printf("Error: failed SDL_CreateTextureFromSurface SDL Error: %s\n", SDL_GetError());
	SDL_FreeSurface(loadedImage);
	return loadedTexture;
}

Textures loadTexture(Renderer *renderer){
	Textures texture;
	
	/* Player textúrák betöltése*/
	texture.pacmanA_up = loadImage("resources/textures/pacman_a_up.bmp", renderer);
	texture.pacmanA_down = loadImage("resources/textures/pacman_a_down.bmp", renderer);
	texture.pacmanA_left = loadImage("resources/textures/pacman_a_left.bmp", renderer);
	texture.pacmanA_right = loadImage("resources/textures/pacman_a_right.bmp", renderer);
	texture.pacmanB_up = loadImage("resources/textures/pacman_b_up.bmp", renderer);
	texture.pacmanB_down = loadImage("resources/textures/pacman_b_down.bmp", renderer);
	texture.pacmanB_left = loadImage("resources/textures/pacman_b_left.bmp", renderer);
	texture.pacmanB_right = loadImage("resources/textures/pacman_b_right.bmp", renderer);

	/* Szörny textúrák betöltése*/
	texture.monster_a = loadImage("resources/textures/Mask.bmp", renderer);
	texture.monster_b = loadImage("resources/textures/Pearl.bmp", renderer);
	texture.monster_c = loadImage("resources/textures/Cthute.bmp", renderer);

	/* Egyéb textúrák betöltése*/

	texture.heart = loadImage("resources/textures/heart.bmp", renderer);

	/* Pálya textúrák betöltése */
	texture.path = loadImage("resources/textures/path.bmp", renderer);
	texture.path_point = loadImage("resources/textures/point.bmp", renderer);
	texture.path_big_point = loadImage("resources/textures/big_point.bmp", renderer);
	texture.shaved_ice = loadImage("resources/textures/shaved_ice.bmp", renderer);
	texture.chili = loadImage("resources/textures/chili.bmp", renderer);
	texture.wall_0 = loadImage("resources/textures/wall_0.bmp", renderer);
	texture.wall_1_up = loadImage("resources/textures/wall_1_up.bmp", renderer);
	texture.wall_1_down = loadImage("resources/textures/wall_1_down.bmp", renderer);
	texture.wall_1_left = loadImage("resources/textures/wall_1_left.bmp", renderer);
	texture.wall_1_right = loadImage("resources/textures/wall_1_right.bmp", renderer);
	texture.wall_2_hor = loadImage("resources/textures/wall_2_horizontal.bmp", renderer);
	texture.wall_2_vert = loadImage("resources/textures/wall_2_vertical.bmp", renderer);
	texture.wall_2_u_r = loadImage("resources/textures/wall_2_u_r.bmp", renderer);
	texture.wall_2_u_l = loadImage("resources/textures/wall_2_u_l.bmp", renderer);
	texture.wall_2_d_r = loadImage("resources/textures/wall_2_d_r.bmp", renderer);
	texture.wall_2_d_l = loadImage("resources/textures/wall_2_d_l.bmp", renderer);
	texture.wall_3_up = loadImage("resources/textures/wall_3_up.bmp", renderer);
	texture.wall_3_down = loadImage("resources/textures/wall_3_down.bmp", renderer);
	texture.wall_3_left = loadImage("resources/textures/wall_3_left.bmp", renderer);
	texture.wall_3_right = loadImage("resources/textures/wall_3_right.bmp", renderer);
	texture.wall_4 = loadImage("resources/textures/wall_4.bmp", renderer);

	/* Fõmenu textúrák betöltése*/
	texture.mainmenu_logo = loadImage("resources/textures/mainmenu_logo.bmp", renderer);
	texture.mainmenu_singleplayer_a = loadImage("resources/textures/mainmenu_singleplayer_a.bmp", renderer);
	texture.mainmenu_singleplayer_b = loadImage("resources/textures/mainmenu_singleplayer_b.bmp", renderer);
	texture.mainmenu_multiplayer_a = loadImage("resources/textures/mainmenu_multiplayer_a.bmp", renderer);
	texture.mainmenu_multiplayer_b = loadImage("resources/textures/mainmenu_multiplayer_b.bmp", renderer);
	texture.mainmenu_toplist_a = loadImage("resources/textures/mainmenu_toplist_a.bmp", renderer);
	texture.mainmenu_toplist_b = loadImage("resources/textures/mainmenu_toplist_b.bmp", renderer);
	texture.mainmenu_quit_a = loadImage("resources/textures/mainmenu_quit_a.bmp", renderer);
	texture.mainmenu_quit_b = loadImage("resources/textures/mainmenu_quit_b.bmp", renderer);
	return texture;
}

Font loadFont(const char* filePath, int fontSize){
	Font font;
	font.size = fontSize;
	font.font = TTF_OpenFont(filePath, font.size);
	if (!font.font)
		printf("TTF_OpenFont: %s\n", TTF_GetError());
	font.color.r = 80;
	font.color.g = 80;
	font.color.b = 80;
	font.color.a = 255;
	return font;
}

void sdlClose(RenderAssets *renderAsset) {
	if (renderAsset->windowResolution->isFullscreen)
		SDL_SetWindowFullscreen(renderAsset->renderer->window, 0);

	/* Játékos textúrák felszabadítása */
	SDL_DestroyTexture(renderAsset->texture->pacmanA_up);
	SDL_DestroyTexture(renderAsset->texture->pacmanA_down);
	SDL_DestroyTexture(renderAsset->texture->pacmanA_left);
	SDL_DestroyTexture(renderAsset->texture->pacmanA_right);
	SDL_DestroyTexture(renderAsset->texture->pacmanB_up);
	SDL_DestroyTexture(renderAsset->texture->pacmanB_down);
	SDL_DestroyTexture(renderAsset->texture->pacmanB_left);
	SDL_DestroyTexture(renderAsset->texture->pacmanB_right);
	
	/* Szörny textúrák felszabadítása */
	SDL_DestroyTexture(renderAsset->texture->monster_a);
	SDL_DestroyTexture(renderAsset->texture->monster_b);
	SDL_DestroyTexture(renderAsset->texture->monster_c);

	/* Egyébb textúrák felszabadítása */

	SDL_DestroyTexture(renderAsset->texture->heart);

	/* Pálya textúrák felszabadítása */
	SDL_DestroyTexture(renderAsset->texture->path);
	SDL_DestroyTexture(renderAsset->texture->path_point);
	SDL_DestroyTexture(renderAsset->texture->path_big_point);
	SDL_DestroyTexture(renderAsset->texture->shaved_ice);
	SDL_DestroyTexture(renderAsset->texture->chili);
	SDL_DestroyTexture(renderAsset->texture->wall_0);
	SDL_DestroyTexture(renderAsset->texture->wall_1_up);
	SDL_DestroyTexture(renderAsset->texture->wall_1_down);
	SDL_DestroyTexture(renderAsset->texture->wall_1_left);
	SDL_DestroyTexture(renderAsset->texture->wall_1_right);
	SDL_DestroyTexture(renderAsset->texture->wall_2_hor);
	SDL_DestroyTexture(renderAsset->texture->wall_2_vert);
	SDL_DestroyTexture(renderAsset->texture->wall_2_u_r);
	SDL_DestroyTexture(renderAsset->texture->wall_2_u_l);
	SDL_DestroyTexture(renderAsset->texture->wall_2_d_r);
	SDL_DestroyTexture(renderAsset->texture->wall_2_d_l);
	SDL_DestroyTexture(renderAsset->texture->wall_3_up);
	SDL_DestroyTexture(renderAsset->texture->wall_3_down);
	SDL_DestroyTexture(renderAsset->texture->wall_3_left);
	SDL_DestroyTexture(renderAsset->texture->wall_3_right);
	SDL_DestroyTexture(renderAsset->texture->wall_4);

	/* Fõmenü textúrák felszabadítása */
	SDL_DestroyTexture(renderAsset->texture->mainmenu_logo);
	SDL_DestroyTexture(renderAsset->texture->mainmenu_singleplayer_a);
	SDL_DestroyTexture(renderAsset->texture->mainmenu_singleplayer_b);
	SDL_DestroyTexture(renderAsset->texture->mainmenu_multiplayer_a);
	SDL_DestroyTexture(renderAsset->texture->mainmenu_multiplayer_b);
	SDL_DestroyTexture(renderAsset->texture->mainmenu_toplist_a);
	SDL_DestroyTexture(renderAsset->texture->mainmenu_toplist_b);
	SDL_DestroyTexture(renderAsset->texture->mainmenu_quit_a);
	SDL_DestroyTexture(renderAsset->texture->mainmenu_quit_b);
	SDL_DestroyRenderer(renderAsset->renderer->renderer);
	SDL_DestroyWindow(renderAsset->renderer->window);

	/* Hangeffektek felszabadítása */
	Mix_FreeChunk(renderAsset->sounds->menu_choose);
	Mix_FreeChunk(renderAsset->sounds->menu_move);
	Mix_FreeChunk(renderAsset->sounds->chili);
	Mix_FreeChunk(renderAsset->sounds->freeze);
	Mix_FreeChunk(renderAsset->sounds->point_big_eaten);
	Mix_FreeChunk(renderAsset->sounds->point_normal_eaten);
	Mix_FreeChunk(renderAsset->sounds->monster_eaten);
	Mix_FreeChunk(renderAsset->sounds->nom_nom);

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void drawMainMenu(RenderAssets *renderAsset, MainMenuSelection selection, MainMenuCoords mainMenuCoord)
{
	SDL_SetRenderDrawColor(renderAsset->renderer->renderer,255,255,255,255);
	SDL_RenderClear(renderAsset->renderer->renderer);
	SDL_RenderCopy(renderAsset->renderer->renderer, renderAsset->texture->mainmenu_logo, NULL, &mainMenuCoord.logo);

	if (selection == singleplayer)
		SDL_RenderCopy(renderAsset->renderer->renderer, renderAsset->texture->mainmenu_singleplayer_b, NULL, &mainMenuCoord.singleplayer);
	else SDL_RenderCopy(renderAsset->renderer->renderer, renderAsset->texture->mainmenu_singleplayer_a, NULL, &mainMenuCoord.singleplayer);

	if (selection == multiplayer)
		SDL_RenderCopy(renderAsset->renderer->renderer, renderAsset->texture->mainmenu_multiplayer_b, NULL, &mainMenuCoord.multiplayer);
	else SDL_RenderCopy(renderAsset->renderer->renderer, renderAsset->texture->mainmenu_multiplayer_a, NULL, &mainMenuCoord.multiplayer);

	if (selection == toplist)
		SDL_RenderCopy(renderAsset->renderer->renderer, renderAsset->texture->mainmenu_toplist_b, NULL, &mainMenuCoord.toplist);
	else SDL_RenderCopy(renderAsset->renderer->renderer, renderAsset->texture->mainmenu_toplist_a, NULL, &mainMenuCoord.toplist);

	if (selection == quitgame)
		SDL_RenderCopy(renderAsset->renderer->renderer, renderAsset->texture->mainmenu_quit_b, NULL, &mainMenuCoord.quit);
	else SDL_RenderCopy(renderAsset->renderer->renderer, renderAsset->texture->mainmenu_quit_a, NULL, &mainMenuCoord.quit);

	SDL_RenderPresent(renderAsset->renderer->renderer);
}

void renderTopList(RenderAssets *renderAsset, TopListCoords topListCoords, Place **topList, int placementNumber) {
	SDL_SetRenderDrawColor(renderAsset->renderer->renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderAsset->renderer->renderer);
	SDL_RenderCopy(renderAsset->renderer->renderer, renderAsset->texture->mainmenu_toplist_a, NULL, &topListCoords.toplistTitle);
	
	int maxPlaceChar = 0, maxNameChar = 0, maxPointChar = 0;
	for (int i = 0, tmp; i < placementNumber; i++) {
		tmp = numberCharNum(topList[i]->placement);
		if (tmp > maxPlaceChar)
			maxPlaceChar = tmp;
		if (topList[i]->name == NULL){
			tmp = 0;
		}
		else tmp = strlen(topList[i]->name);
		if (tmp > maxNameChar)
			maxNameChar = tmp;
		tmp = numberCharNum(topList[i]->points);
		if (tmp > maxPointChar)
			maxPointChar = tmp;
	}

	char *placeStructString = (char*) malloc((maxNameChar + maxPlaceChar + maxPointChar + 15) * sizeof(char));
	placeStructString[0] = '\0';

	for (int i = 0; i < placementNumber; i++) {
		SDL_Rect tmp;
		tmp.x = topListCoords.placementsBase.x;
		tmp.y = topListCoords.placementsBase.y + i* renderAsset->font->size;
		tmp.w = topListCoords.placementsBase.w;
		tmp.h = topListCoords.placementsBase.h;

		placeStructToString(topList[i], placeStructString, maxNameChar, maxPlaceChar, maxPointChar, 15, 6);

		renderText(renderAsset,tmp, placeStructString);
	}

	free(placeStructString);
	SDL_RenderPresent(renderAsset->renderer->renderer);
}

void renderScoreInputScreen(RenderAssets *renderAsset,const char* nameString) {
	SDL_SetRenderDrawColor(renderAsset->renderer->renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderAsset->renderer->renderer);
	SDL_Rect nameText, nameInputText;
	
	nameText.x = renderAsset->renderer->SCREEN_WIDTH / 4;
	nameText.y = renderAsset->renderer->SCREEN_HEIGHT/2 - renderAsset->font->size/2;
	nameText.w = renderAsset->renderer->SCREEN_WIDTH / 4;
	nameText.h = renderAsset->font->size;

	nameInputText.x = renderAsset->renderer->SCREEN_WIDTH / 2;
	nameInputText.y = nameText.y;
	if (nameString == NULL)
		nameInputText.w = renderAsset->font->size * 1;
	else {
		nameInputText.w = renderAsset->font->size * strlen(nameString);
	}
	nameInputText.h = nameText.h;

	renderText(renderAsset, nameText, "Add meg a nevedet: ");

	if (nameString != NULL) {
		renderText(renderAsset, nameInputText, nameString);
	}
	SDL_RenderPresent(renderAsset->renderer->renderer);
}

void renderText(RenderAssets *renderAsset, SDL_Rect place, const char* string) {
	SDL_Surface* tmpSurface = NULL;
	SDL_Texture* tmpTexture = NULL;
	tmpSurface = TTF_RenderText_Solid(renderAsset->font->font, string, renderAsset->font->color);
	if (tmpSurface == NULL)
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	else {
		tmpTexture = SDL_CreateTextureFromSurface(renderAsset->renderer->renderer, tmpSurface);
		if (tmpTexture == NULL)
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
	}
	SDL_RenderCopy(renderAsset->renderer->renderer, tmpTexture, NULL, &place);
	SDL_FreeSurface(tmpSurface);
	SDL_DestroyTexture(tmpTexture);
}

void renderMapWithoutEntities(Level *level, RenderAssets *renderAsset) {
	for (int x = 0; x < level->dimension.colums; x++){
		for (int y = 0; y < level->dimension.rows; y++){
			SDL_Rect tmp;
			tmp.x = level->tile.w * y;
			tmp.y = level->tile.h * x;
			tmp.w = level->tile.w;
			tmp.h = level->tile.h;

			switch (level->map[x][y]) {
				case path:
					SDL_RenderCopy(renderAsset->renderer->renderer, renderAsset->texture->path, NULL, &tmp);
					break;
				case path_point:
					SDL_RenderCopy(renderAsset->renderer->renderer, renderAsset->texture->path_point, NULL, &tmp);
					break;
				case path_big_point:
					SDL_RenderCopy(renderAsset->renderer->renderer, renderAsset->texture->path_big_point, NULL, &tmp);
					break;
				case shaved_ice:
					SDL_RenderCopy(renderAsset->renderer->renderer, renderAsset->texture->shaved_ice, NULL, &tmp);
					break;
				case chili:
					SDL_RenderCopy(renderAsset->renderer->renderer, renderAsset->texture->chili, NULL, &tmp);
					break;
				case wall_0:
					SDL_RenderCopy(renderAsset->renderer->renderer, renderAsset->texture->wall_0, NULL, &tmp);
					break;
				case wall_1_up:
					SDL_RenderCopy(renderAsset->renderer->renderer, renderAsset->texture->wall_1_up, NULL, &tmp);
					break;
				case wall_1_down:
					SDL_RenderCopy(renderAsset->renderer->renderer, renderAsset->texture->wall_1_down, NULL, &tmp);
					break;
				case wall_1_left:
					SDL_RenderCopy(renderAsset->renderer->renderer, renderAsset->texture->wall_1_left, NULL, &tmp);
					break;
				case wall_1_right:
					SDL_RenderCopy(renderAsset->renderer->renderer, renderAsset->texture->wall_1_right, NULL, &tmp);
					break;
				case wall_2_hor:
					SDL_RenderCopy(renderAsset->renderer->renderer, renderAsset->texture->wall_2_hor, NULL, &tmp);
					break;
				case wall_2_vert:
					SDL_RenderCopy(renderAsset->renderer->renderer, renderAsset->texture->wall_2_vert, NULL, &tmp);
					break;
				case wall_2_u_r:
					SDL_RenderCopy(renderAsset->renderer->renderer, renderAsset->texture->wall_2_u_r, NULL, &tmp);
					break;
				case wall_2_u_l:
					SDL_RenderCopy(renderAsset->renderer->renderer, renderAsset->texture->wall_2_u_l, NULL, &tmp);
					break;
				case wall_2_d_r:
					SDL_RenderCopy(renderAsset->renderer->renderer, renderAsset->texture->wall_2_d_r, NULL, &tmp);
					break;
				case wall_2_d_l:
					SDL_RenderCopy(renderAsset->renderer->renderer, renderAsset->texture->wall_2_d_l, NULL, &tmp);
					break;
				case wall_3_up:
					SDL_RenderCopy(renderAsset->renderer->renderer, renderAsset->texture->wall_3_up, NULL, &tmp);
					break;
				case wall_3_down:
					SDL_RenderCopy(renderAsset->renderer->renderer, renderAsset->texture->wall_3_down, NULL, &tmp);
					break;
				case wall_3_left:
					SDL_RenderCopy(renderAsset->renderer->renderer, renderAsset->texture->wall_3_left, NULL, &tmp);
					break;
				case wall_3_right:
					SDL_RenderCopy(renderAsset->renderer->renderer, renderAsset->texture->wall_3_right, NULL, &tmp);
					break;
				case wall_4:
					SDL_RenderCopy(renderAsset->renderer->renderer, renderAsset->texture->wall_4, NULL, &tmp);
					break;
				default:
					break;
			}
		}
	}
	SDL_RenderPresent(renderAsset->renderer->renderer);
}

Difficulty getDifficulty(RenderAssets *renderAsset) {
	
	SDL_SetRenderDrawColor(renderAsset->renderer->renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderAsset->renderer->renderer);
	Difficulty difficulty = normal;
	char difTextString[] = "Valaszd ki a nehezsegi szintet:",
		easyString[] = "Konnyu",
		normalString[] = "Normal",
		hardString[] = "Nehez";

	GetDifficultyCoords coords = getGetDifficultyCoords(renderAsset, difTextString, easyString, normalString, hardString);
	/* Aktuálisan kiválasztott opció aláhúzásának magassága pixelekben */
	int selectionPixelHeight = 5;
	coords.selectionClear.h = selectionPixelHeight;

	renderText(renderAsset, coords.difText, difTextString);
	renderText(renderAsset, coords.difEasyText, easyString);
	renderText(renderAsset, coords.difNormalText, normalString);
	renderText(renderAsset, coords.difHardText, hardString);

	SDL_RenderPresent(renderAsset->renderer->renderer);

	SDL_Event getDifficulty;
	bool quit = false;

	while (!quit) {
		while (SDL_PollEvent(&getDifficulty)) {
			if (getDifficulty.type == SDL_QUIT) {
				renderAsset->close = true;
				return 0;
			}
			if (getDifficulty.type == SDL_KEYDOWN) {
				if (getDifficulty.key.keysym.sym == SDLK_LEFT && difficulty > 0) {
					playSFX(renderAsset->sounds->menu_move);
					difficulty--;
				}
				if (getDifficulty.key.keysym.sym == SDLK_RIGHT && difficulty < 2) {
					playSFX(renderAsset->sounds->menu_move);
					difficulty++;
				}
				if (getDifficulty.key.keysym.sym == SDLK_RETURN) {
					playSFX(renderAsset->sounds->menu_choose);
					quit = true;
				}
			}
			SDL_SetRenderDrawColor(renderAsset->renderer->renderer, 255, 255, 255, 255);
			SDL_RenderFillRect(renderAsset->renderer->renderer, &coords.selectionClear);
			switch (difficulty) {
				case easy:
					placeSelectionRectForRender(renderAsset, coords.difEasyText, selectionPixelHeight);
					break;
				case normal:
					placeSelectionRectForRender(renderAsset, coords.difNormalText, selectionPixelHeight);
					break;
				case hard:
					placeSelectionRectForRender(renderAsset, coords.difHardText, selectionPixelHeight);
					break;
			}
			SDL_RenderPresent(renderAsset->renderer->renderer);
		}
	}

	switch (difficulty){
		case easy:
			return easy;
			break;
		case normal:
			return normal;
			break;
		case hard:
			return hard;
			break;
	}
	return normal;
}

void placeSelectionRectForRender(RenderAssets *renderAsset, SDL_Rect placement, int pixelHeight){
	SDL_Rect selectionMarker;
	selectionMarker.x = placement.x;
	selectionMarker.y = placement.y + renderAsset->font->size;
	selectionMarker.w = placement.w;
	selectionMarker.h = pixelHeight;
	SDL_SetRenderDrawColor(renderAsset->renderer->renderer, 80, 80, 80, 255);
	SDL_RenderFillRect(renderAsset->renderer->renderer, &selectionMarker);
}

char *getLevelFromFile(RenderAssets *renderAsset){
	SDL_SetRenderDrawColor(renderAsset->renderer->renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderAsset->renderer->renderer);

	/* numOfLevels = pályák száma */
	const int numOfLevels = 2;

	SDL_Rect levelText;

	levelText.x = renderAsset->renderer->SCREEN_WIDTH / 2 - strlen("Valaszd ki a palyat:") / 2 * renderAsset->font->size;
	levelText.y = renderAsset->renderer->SCREEN_HEIGHT / 4 - renderAsset->font->size / 2;
	levelText.w = strlen("Valaszd ki a palyat:") * renderAsset->font->size;
	levelText.h = renderAsset->font->size;

	renderText(renderAsset,levelText, "Valaszd ki a palyat:");

	SDL_RenderPresent(renderAsset->renderer->renderer);
	SDL_Event getLevel;
	bool quit = false;

	int levelNumber = 0;
	while (!quit) {
		while (SDL_PollEvent(&getLevel)) {
			if (getLevel.type == SDL_QUIT){
				renderAsset->close = true;
				quit = true;
			}
			if (getLevel.type == SDL_KEYDOWN) {
				if (getLevel.key.keysym.sym == SDLK_UP && levelNumber > 0) {
					playSFX(renderAsset->sounds->menu_move);
					levelNumber--;
				}
				if (getLevel.key.keysym.sym == SDLK_DOWN && levelNumber < numOfLevels - 1) {
					playSFX(renderAsset->sounds->menu_move);
					levelNumber++;
				}
				if (getLevel.key.keysym.sym == SDLK_RETURN) {
					playSFX(renderAsset->sounds->menu_choose);
					quit = true;
				}
			}
			SDL_Rect currentLevelText, currentLevelSelection;
			currentLevelSelection.h = 4;
			for (int i = 0; i < numOfLevels; i++) {
				currentLevelSelection.x = renderAsset->renderer->SCREEN_WIDTH / 2 - strlen(getLevelName(i)) / 2 * renderAsset->font->size;
				currentLevelSelection.y = renderAsset->renderer->SCREEN_HEIGHT / 2 + renderAsset->font->size / 2 + i*(renderAsset->font->size + currentLevelSelection.h);
				currentLevelSelection.w = strlen(getLevelName(i)) * renderAsset->font->size;

				currentLevelText.x = currentLevelSelection.x;
				currentLevelText.y = renderAsset->renderer->SCREEN_HEIGHT / 2 - renderAsset->font->size / 2 - currentLevelSelection.h + i*(renderAsset->font->size + currentLevelSelection.h);
				currentLevelText.w = currentLevelSelection.w;
				currentLevelText.h = renderAsset->font->size;

				renderText(renderAsset, currentLevelText, getLevelName(i));

				if (i == levelNumber)
					SDL_SetRenderDrawColor(renderAsset->renderer->renderer, 80, 80, 80, 255);
				else SDL_SetRenderDrawColor(renderAsset->renderer->renderer, 255, 255, 255, 255);
					
				SDL_RenderFillRect(renderAsset->renderer->renderer, &currentLevelSelection);
			}
			SDL_RenderPresent(renderAsset->renderer->renderer);
		}
	}
	if (renderAsset->close == true)
		return NULL;
	else
		return getLeveLSourcePathString(levelNumber);
}

void renderAnimateEntity(RenderAssets *renderAsset, Level *level, SDL_Texture *texture, Coordinate newCoords, Coordinate oldCoords, Direction dir){
	switch (dir) {
		case up:
			renderAnimateEntityMoveUp(renderAsset,level->tile,level->dimension,texture,newCoords, oldCoords);
			break;
		case down:
			renderAnimateEntityMoveDown(renderAsset, level->tile, level->dimension, texture, newCoords, oldCoords);
			break;
		case left:
			renderAnimateEntityMoveLeft(renderAsset, level->tile, level->dimension, texture, newCoords, oldCoords);
			break;
		case right:
			renderAnimateEntityMoveRight(renderAsset, level->tile, level->dimension, texture, newCoords, oldCoords);
			break;
	}
}

void renderAnimateEntityMoveUp(RenderAssets *renderAsset,SDL_Rect tile,LevelDimensions size, SDL_Texture *texture, Coordinate newCoords, Coordinate oldCoords) {
	SDL_Rect current = renderAnimateConvert(size, tile, oldCoords);
	for (int y = 0; y < tile.h; y++){
		SDL_RenderCopy(renderAsset->renderer->renderer, renderAsset->texture->path,NULL,&current);
		current.y--;
		SDL_RenderCopy(renderAsset->renderer->renderer, texture, NULL, &current);
		SDL_RenderPresent(renderAsset->renderer->renderer);
	}
}

void renderAnimateEntityMoveDown(RenderAssets *renderAsset, SDL_Rect tile, LevelDimensions size, SDL_Texture *texture, Coordinate newCoords, Coordinate oldCoords) {
	SDL_Rect current = renderAnimateConvert(size, tile, oldCoords);
	for (int y = 0; y < tile.h; y++) {
		SDL_RenderCopy(renderAsset->renderer->renderer, renderAsset->texture->path, NULL, &current);
		current.y++;
		SDL_RenderCopy(renderAsset->renderer->renderer, texture, NULL, &current);
		SDL_RenderPresent(renderAsset->renderer->renderer);
	}
}

void renderAnimateEntityMoveLeft(RenderAssets *renderAsset, SDL_Rect tile, LevelDimensions size, SDL_Texture *texture, Coordinate newCoords, Coordinate oldCoords) {
	SDL_Rect current = renderAnimateConvert(size, tile, oldCoords);
	for (int x = 0; x < tile.w; x++) {
		SDL_RenderCopy(renderAsset->renderer->renderer, renderAsset->texture->path, NULL, &current);
		current.x--;
		SDL_RenderCopy(renderAsset->renderer->renderer, texture, NULL, &current);
		SDL_RenderPresent(renderAsset->renderer->renderer);
	}
}

void renderAnimateEntityMoveRight(RenderAssets *renderAsset, SDL_Rect tile, LevelDimensions size, SDL_Texture *texture, Coordinate newCoords, Coordinate oldCoords) {
	SDL_Rect current = renderAnimateConvert(size, tile, oldCoords);
	for (int x = 0; x < tile.w; x++) {
		SDL_RenderCopy(renderAsset->renderer->renderer, renderAsset->texture->path, NULL, &current);
		current.x++;
		SDL_RenderCopy(renderAsset->renderer->renderer, texture, NULL, &current);
		SDL_RenderPresent(renderAsset->renderer->renderer);
	}
}

void renderMapJustEntities(Level *level, RenderAssets *renderAsset, Player *playerOne, Player *playerTwo, Monsters *monsters) {
	for (int x = 0; x < level->dimension.colums; x++) {
		for (int y = 0; y < level->dimension.rows; y++) {
			SDL_Rect tmp;
			tmp.x = level->tile.w * y;
			tmp.y = level->tile.h * x;
			tmp.w = level->tile.w;
			tmp.h = level->tile.h;
			if (level->map[x][y] == monsterA && monsters->monster_A->state != dead)
				SDL_RenderCopy(renderAsset->renderer->renderer, renderAsset->texture->monster_a, NULL, &tmp);
			if (level->map[x][y] == monsterB && monsters->monster_B->state != dead)
				SDL_RenderCopy(renderAsset->renderer->renderer, renderAsset->texture->monster_b, NULL, &tmp);
			if (level->map[x][y] == monsterC && monsters->monster_B->state != dead)
				SDL_RenderCopy(renderAsset->renderer->renderer, renderAsset->texture->monster_c, NULL, &tmp);
			
			if (playerOne != NULL) {
				if (level->map[x][y] == playerOne->id)
					SDL_RenderCopy(renderAsset->renderer->renderer, playerOne->texture, NULL, &tmp);
			}
			if (playerTwo != NULL){
				if (level->map[x][y] == playerTwo->id)
					SDL_RenderCopy(renderAsset->renderer->renderer, playerTwo->texture, NULL, &tmp);
			}
		}
	}
}

void renderHUD(RenderAssets *renderAsset,Coordinate hudZero, Player *playerOne,Player *playerTwo, bool renderIce) {
	renderClearHUD(renderAsset,hudZero);
	SDL_SetRenderDrawColor(renderAsset->renderer->renderer, 0,0,0,255);
	if (renderIce) {
		Coordinate start;
		start.x = hudZero.x + (renderAsset->renderer->SCREEN_WIDTH - hudZero.x) / 2;
		start.y = 10;
		SDL_Rect iceCoords = getStateFrozenRect(renderAsset,start);
		SDL_RenderCopy(renderAsset->renderer->renderer, renderAsset->texture->shaved_ice, NULL, &iceCoords);
	}

	int lineWidth = 5;
	for (int i = 0; i < lineWidth; i++ )
		SDL_RenderDrawLine(renderAsset->renderer->renderer, hudZero.x+i, hudZero.y, hudZero.x+i, renderAsset->renderer->SCREEN_HEIGHT);
	if (playerOne != NULL) {
		Coordinate start;
		start.x = hudZero.x + (renderAsset->renderer->SCREEN_WIDTH - hudZero.x)/2;
		start.y = renderAsset->renderer->SCREEN_HEIGHT / 4;
		renderPlayerHUD(renderAsset, start, playerOne, "SARGA JATEKOS");
	}
	if (playerTwo != NULL) {
		Coordinate start;
		start.x = hudZero.x + (renderAsset->renderer->SCREEN_WIDTH - hudZero.x) / 2;
		start.y = renderAsset->renderer->SCREEN_HEIGHT/ 4 * 3;
		renderPlayerHUD(renderAsset, start, playerTwo, "KEK JATEKOS");
	}
}

void renderClearHUD(RenderAssets *renderAsset, Coordinate hudZero) {
	SDL_Rect tmp;
	tmp.x = hudZero.x;
	tmp.y = hudZero.y;
	tmp.w = renderAsset->renderer->SCREEN_WIDTH - hudZero.x;
	tmp.h = renderAsset->renderer->SCREEN_HEIGHT;
	SDL_SetRenderDrawColor(renderAsset->renderer->renderer, 255,255,255,255);
	SDL_RenderFillRect(renderAsset->renderer->renderer, &tmp);
	SDL_RenderPresent(renderAsset->renderer->renderer);
}

void renderPlayerHUD(RenderAssets *renderAsset, Coordinate start, Player* player, const char* playerName) {
	SDL_Rect nameRect = getHUDNameRect(renderAsset,start, playerName);
	renderText(renderAsset, nameRect, playerName);

	SDL_SetRenderDrawColor(renderAsset->renderer->renderer, 80, 80, 80, 255);
	SDL_Rect lineRect = getHUDNameLineRect(nameRect);
	SDL_RenderFillRect(renderAsset->renderer->renderer, &lineRect);

	char *scoreString = getScoreString(player->points);
	SDL_Rect pointRect = getHUDPointsRect(renderAsset, start, scoreString);
	renderText(renderAsset, pointRect, scoreString);

	SDL_Rect heartRectBase = getHeartRectBase(renderAsset,start);

	for (int i = 0; i < player->health; i++){
		SDL_RenderCopy(renderAsset->renderer->renderer, renderAsset->texture->heart, NULL, &heartRectBase);
		heartRectBase.x += heartRectBase.w;
	}

	SDL_Rect stateEnraged = getStateEnragedRect(renderAsset, start);
	if (player->state == enraged) {
		SDL_RenderCopy(renderAsset->renderer->renderer, renderAsset->texture->chili, NULL, &stateEnraged);
	}

	SDL_RenderPresent(renderAsset->renderer->renderer);
	free(scoreString);
}

Level* initLevel(RenderAssets *renderAsset) {
	LevelDimensions dim;
	char *levelSourceFilePath = getLevelFromFile(renderAsset);
	if (renderAsset->close == true) return NULL;

	char **mapBase = readLevel(levelSourceFilePath, &dim);
	free(levelSourceFilePath);

	Level *level = (Level*)malloc(sizeof(Level));
	level->dimension.rows = dim.rows - 1;				// A beolvasásnál +1 a \n-ek miatt
	level->dimension.colums = dim.colums;
	level->map = mapConverter(mapBase, level->dimension);
	level->tile.x = 0;
	level->tile.y = 0;
	level->tile.w = renderAsset->renderer->SCREEN_HEIGHT / level->dimension.rows;
	level->tile.h = renderAsset->renderer->SCREEN_HEIGHT / level->dimension.rows;

	free2DCharArray(mapBase, dim.colums);

	return level;
}

void insertNameToplist(RenderAssets *renderAsset, Place **topListArray, int *placementNumber, int score) {
	SDL_Event insertNameToplist;
	bool quit = false;
	if (topListArray[*placementNumber - 1]->points < score) {
		topListArray[*placementNumber - 1]->points = score;
		topListArray[*placementNumber]->name = NULL;
		char tmp = '-';

		while (!quit) {
			while (SDL_PollEvent(&insertNameToplist)) {
				tmp = getSDLInputABC(&insertNameToplist);

				if (tmp != '0' && tmp != '1' && tmp != '2' && tmp != '3')
					topListArray[*placementNumber]->name = remakeDynString(tmp, topListArray[*placementNumber]->name);
				if (tmp == '3')
					topListArray[*placementNumber]->name = removeDynStringLastChar(topListArray[*placementNumber]->name);
				if (tmp == '1')
					quit = true;

				renderScoreInputScreen(renderAsset, topListArray[*placementNumber]->name);
			}
		}
		if (topListArray[*placementNumber]->name == NULL) {
			topListArray[*placementNumber]->name = duplicateDynString("JATEKOS");
			topListArray[*placementNumber - 1]->name = duplicateDynString(topListArray[*placementNumber]->name);
		}
		else {
			topListArray[*placementNumber - 1]->name = makeDynString(strlen(topListArray[*placementNumber]->name) + 1);
			for (int i = 0; i < (int)strlen(topListArray[*placementNumber]->name) + 1; i++) {
				topListArray[*placementNumber - 1]->name[i] = topListArray[*placementNumber]->name[i];
			}
		}

		placeStructArraySelectionSort(topListArray, *placementNumber);
		writeTopList(topListArray, *placementNumber);
	}
	else {
		topListArray[*placementNumber]->name = duplicateDynString("TE");
	}

	topListArray[*placementNumber]->points = score;
	topListArray[*placementNumber]->placement = *placementNumber + 1;

	*placementNumber += 1;
}