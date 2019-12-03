#define SDL_MAIN_HANDLED
#include <SDL.h>
#include "Entities.h"
#include "Vector.h"
#include <stdio.h>

#define FPS 60.0f
#define SOLID 1
#define MOVE_SPEED 4.0f

static bool keep_running;
static int num_tiles_x = 120;
static int num_tiles_y = 120;
static int tile_size = 8; 
static const int num_tiles = 14400;
static int window_width = 960;
static int window_height = 960;

void Cleanup()
{

}

void StartGame(Tile tiles[])
{
	for (int y = 0; y < num_tiles_y; y++)
	{
		for (int x = 0; x < num_tiles_x; x++)
		{
			tiles[y*num_tiles_x + x].state = 0;
			tiles[y*num_tiles_x + x].rect.min.x = x * tile_size;
			tiles[y*num_tiles_x + x].rect.min.y = y * tile_size;
			tiles[y*num_tiles_x + x].rect.max.x = tile_size;
			tiles[y*num_tiles_x + x].rect.max.y = tile_size;
			if (x == 0 || y == 0 || x == (num_tiles_x - 1) || y == (num_tiles_y - 1))
			{
				tiles[y*num_tiles_x + x].state = 1;
			}
		}
	}

	tiles[10 * num_tiles_x + 20].state = 1;
	tiles[11 * num_tiles_x + 20].state = 1;
	tiles[12 * num_tiles_x + 20].state = 1;
	tiles[13 * num_tiles_x + 20].state = 1;
	tiles[14 * num_tiles_x + 20].state = 1;
	tiles[15 * num_tiles_x + 20].state = 1;
	tiles[16 * num_tiles_x + 20].state = 1;
	tiles[17 * num_tiles_x + 20].state = 1;
	tiles[18 * num_tiles_x + 20].state = 1;
	tiles[19 * num_tiles_x + 20].state = 1;
	tiles[20 * num_tiles_x + 20].state = 1;
	tiles[21 * num_tiles_x + 20].state = 1;
	tiles[22 * num_tiles_x + 20].state = 1;
	tiles[23 * num_tiles_x + 20].state = 1;
	tiles[24 * num_tiles_x + 20].state = 1;

	tiles[10 * num_tiles_x + 90].state = 1;
	tiles[11 * num_tiles_x + 90].state = 1;
	tiles[12 * num_tiles_x + 90].state = 1;
	tiles[13 * num_tiles_x + 90].state = 1;
	tiles[14 * num_tiles_x + 90].state = 1;
	tiles[15 * num_tiles_x + 90].state = 1;
	tiles[16 * num_tiles_x + 90].state = 1;
	tiles[17 * num_tiles_x + 90].state = 1;
	tiles[18 * num_tiles_x + 90].state = 1;
	tiles[19 * num_tiles_x + 90].state = 1;
	tiles[20 * num_tiles_x + 90].state = 1;
	tiles[21 * num_tiles_x + 90].state = 1;
	tiles[22 * num_tiles_x + 90].state = 1;
	tiles[23 * num_tiles_x + 90].state = 1;
	tiles[24 * num_tiles_x + 90].state = 1;
}

void HandleEvent(SDL_Event *event, V2 *player, float *player_angle)
{
	SDL_PollEvent(event);
	if (event->type == SDL_KEYDOWN)
	{
		if (event->key.keysym.scancode == SDL_SCANCODE_W)
		{
			player->y -=  MOVE_SPEED;
		}
		if (event->key.keysym.scancode == SDL_SCANCODE_S)
		{
			player->y +=  MOVE_SPEED;
		}
		if (event->key.keysym.scancode == SDL_SCANCODE_A)
		{
			player->x -= MOVE_SPEED;
		}
		if (event->key.keysym.scancode == SDL_SCANCODE_D)
		{
			player->x += MOVE_SPEED;
		}
		if (event->key.keysym.scancode == SDL_SCANCODE_UP)
		{
		}
		if (event->key.keysym.scancode == SDL_SCANCODE_DOWN)
		{
		}
		if (event->key.keysym.scancode == SDL_SCANCODE_LEFT)
		{
			*player_angle -= 0.1f;
		}
		if (event->key.keysym.scancode == SDL_SCANCODE_RIGHT)
		{
			*player_angle += 0.1f;
		}
		if (event->key.keysym.scancode == SDL_SCANCODE_ESCAPE)
		{
			keep_running = false;
		}
	}
	if (event->type == SDL_KEYUP)
	{
		if (event->key.keysym.scancode == SDL_SCANCODE_W)
		{
		}
		if (event->key.keysym.scancode == SDL_SCANCODE_S)
		{
		}
		if (event->key.keysym.scancode == SDL_SCANCODE_A)
		{
		}
		if (event->key.keysym.scancode == SDL_SCANCODE_D)
		{
		}
		if (event->key.keysym.scancode == SDL_SCANCODE_UP)
		{
		}
		if (event->key.keysym.scancode == SDL_SCANCODE_DOWN)
		{
		}
		if (event->key.keysym.scancode == SDL_SCANCODE_LEFT)
		{
		}
		if (event->key.keysym.scancode == SDL_SCANCODE_RIGHT)
		{
		}
	}
}

void UpdateGame(Tile tiles[], V2 *player_tile, V2 *player, float *player_angle, float FOV, SDL_Renderer *renderer)
{
	Tile line_begin_tile = {};
	bool collision = false;

	SDL_Rect rect;

	for (int i = 0; i < num_tiles; i++)
	{
		rect = { (int)tiles[i].rect.min.x, (int)tiles[i].rect.min.y, tile_size, tile_size };
		if (tiles[i].state == 1)
		{
			SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF);
			SDL_RenderFillRect(renderer, &rect);
		}
		else
		{
			SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
			SDL_RenderFillRect(renderer, &rect);
		}
		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);
	}

	int err = SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0x0, 0xFF);

	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);
	for (int x = 0.0f; x < window_width; x++)
	{
		float ray_angle = (*player_angle - FOV / 2) + ((float)x / (float)window_width) * FOV;
		//printf("Ray angle is: %f\n", ray_angle);
		float distance_to_wall = 0.0f;
		int test_point_x = 0;
		int test_point_y = 0;
		//get unit vector for player angle
		V2 player_unit_vector = { sinf(ray_angle), cosf(ray_angle) };
		//V2 test = { (window_width * cosf(ray_angle)) - (window_height * sinf(ray_angle), (window_height * cosf(ray_angle)) + (window_width * sinf(ray_angle))) };

		//printf("PLAYER UNIT VECTOR IS: %f, %f\n", player_unit_vector.x, player_unit_vector.y);
		//printf("TEST VECTOR IS: %f, %f\n", test.x, test.y);
		collision = false;

		while (!collision && distance_to_wall < num_tiles_x)
		{
			distance_to_wall += 0.1f;
			test_point_x = (int)(player_tile->x + player_unit_vector.x * distance_to_wall);
			test_point_y = (int)(player_tile->y + player_unit_vector.y * distance_to_wall);

			if (test_point_x < 0 || test_point_x >= num_tiles_x || test_point_y < 0 || test_point_y >= num_tiles_y)
			{
				collision = true;
				distance_to_wall = num_tiles_x;
			}
			else
			{
				if (tiles[test_point_y * num_tiles_x + test_point_x].state == SOLID)
				{
					collision = true;
					V2 test = { test_point_x - player_tile->x, test_point_y - player_tile->y };
					//printf("%f, %f" ,test.x, test.y);
					V2 corner[4];
					corner[0] = test;
					corner[1] = test + V2{1, 0};
					corner[2] = test + V2{ 0, 1 };
					corner[3] = test + V2{ 1, 1 };

					float d[4];
					d[0] = Magnitude(corner[0]);
					d[1] = Magnitude(corner[1]);
					d[2] = Magnitude(corner[2]);
					d[3] = Magnitude(corner[3]);

					int min = d[0];
					for (int i = 0; i < 4; i++)
					{
						if (d[i] < min)
							min = i;
					}

					if (min == 1)
						test_point_x += 1;
					else if (min == 2)
						test_point_y += 1;
					else if (min == 3)
					{
						test_point_x += 1;
						test_point_y += 1;
					}

					float dot1 = (player_unit_vector.x * corner[0].x / d[0]) + (player_unit_vector.y * corner[0].y / d[0]);
					float dot2 = (player_unit_vector.x * corner[1].x / d[1]) + (player_unit_vector.y * corner[1].y / d[1]);
					float dot3 = (player_unit_vector.x * corner[2].x / d[2]) + (player_unit_vector.y * corner[2].y / d[2]);
					float dot4 = (player_unit_vector.x * corner[3].x / d[3]) + (player_unit_vector.y * corner[3].y / d[3]);

					//printf("x %d\ny %d \n", test_point_x, test_point_y);
					//printf("d2 %f, %f \n", d[1], dot2);
					//printf("d3 %f, %f \n", d[2], dot3);
					//printf("d4 %f, %f \n", d[3], dot4);
				}
			}
		}
		//(window_width * cosf(ray_angle)) - (window_height * sinf(ray_angle)), (window_height * cosf(ray_angle)) + (window_width * sinf(ray_angle)));
		SDL_RenderDrawLine(renderer, (int)player->x, (int)player->y, test_point_x * tile_size, test_point_y * tile_size);
	}
	SDL_RenderPresent(renderer);

	
	/*for (int i = 0; i < num_tiles; i++)
	{
		if (line.begin.x > tiles[i].rect.min.x && line.begin.x < tiles[i].rect.min.x + tile_size &&
			line.begin.y > tiles[i].rect.min.y && line.begin.y < tiles[i].rect.min.y + tile_size)
		{
			line_begin_tile = tiles[i];
			break;
		}
	}

	if (line_begin_tile.state == 1)
	{
		collision = true;
	}
	else
	{
		(line.end.y - line.begin.y) / (line.end.x - line.begin.x);
	}*/
	
}

void Render(SDL_Renderer *renderer, Tile tiles[])
{
	int err = SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0x0, 0xFF);
	SDL_RenderClear(renderer);
	err = SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0x0, 0xFF);
	//err = SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	//SDL_RenderFillRect(renderer, &ball_rect);
	SDL_Rect rect;
	for (int i = 0; i < num_tiles; i++)
	{
		rect = { (int)tiles[i].rect.min.x, (int)tiles[i].rect.min.y, tile_size, tile_size };
		if (tiles[i].state == 1)
		{
			err = SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF);
			SDL_RenderFillRect(renderer, &rect);
		}
		else
		{
			err = SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
			SDL_RenderFillRect(renderer, &rect);
		}
		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);
		SDL_RenderDrawLine(renderer, window_width/2, window_height/2, 1000, 450);
	}
	//err = SDL_RenderDrawRect(renderer, &rect);
	SDL_RenderPresent(renderer);
}

int main()
{
	int SDL_Init(SDL_INIT_EVERYTHING);
	keep_running = true;
	const char title[] = "Less Than Doom";
	
	uint32_t start_time = 0, end_time = 0, delta_time = 0;
	uint32_t frame_delay = 1000 / FPS;
	SDL_Event event;
	SDL_Window* window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_width, window_height, SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	Tile tiles[num_tiles];
	V2 player = { window_width / 2 , window_height / 2 };
	float player_angle = 0.0f;
	V2 player_tile = { player.x / (float)tile_size, player.y / (float)tile_size };
	V2 velocity;
	float FOV = 3.14159f/6.0f;
	Line line = { window_width / 2, window_height / 2, 1000, 450 };

	StartGame(tiles);
	do
	{
		StartGame(tiles);
		keep_running = true;

		start_time = SDL_GetTicks();

		HandleEvent(&event, &player, &player_angle);
		player_tile = { player.x / tile_size, player.y / tile_size };
		UpdateGame(tiles, &player_tile, &player, &player_angle, FOV, renderer);
		//Render(renderer, tiles);

		end_time = SDL_GetTicks();
		delta_time = end_time - start_time;
		if (frame_delay > delta_time)
			SDL_Delay(frame_delay - delta_time);
	}while (keep_running);

	Cleanup();
	return 0;
}