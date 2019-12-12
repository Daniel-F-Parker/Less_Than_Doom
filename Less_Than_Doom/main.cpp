#define SDL_MAIN_HANDLED
#include <SDL.h>
#include "Entities.h"
#include "Vector.h"
#include <stdio.h>

#define FPS 60.0f
#define RED 1
#define GREEN 2
#define BLUE 3
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
			tiles[y*num_tiles_x + x].rect.min.x = (float)(x * tile_size);
			tiles[y*num_tiles_x + x].rect.min.y = (float)(y * tile_size);
			tiles[y*num_tiles_x + x].rect.max.x = (float)tile_size;
			tiles[y*num_tiles_x + x].rect.max.y = (float)tile_size;
			if (x == 0 || y == 0 || x == (num_tiles_x - 1) || y == (num_tiles_y - 1))
			{
				tiles[y*num_tiles_x + x].state = 1;
			}
			/*else if ((y > 10) && (y < 50) && ((x == 20) || (x == 90)))
			{
				tiles[y*num_tiles_x + x].state = 1;
			}*/
			else
			{
				tiles[y*num_tiles_x + x].state = 0;
			}
		}
	}
}

void HandleEvent(SDL_Event *event, V2 *player, float *player_angle)
{
	SDL_PollEvent(event);
	if (event->type == SDL_KEYDOWN)
	{
		if (event->key.keysym.scancode == SDL_SCANCODE_W)
		{
			player->x += sinf(*player_angle) * MOVE_SPEED;
			player->y += cosf(*player_angle) * MOVE_SPEED;
		}
		if (event->key.keysym.scancode == SDL_SCANCODE_S)
		{
			player->x -= sinf(*player_angle) * MOVE_SPEED;
			player->y -= cosf(*player_angle) * MOVE_SPEED;
		}
		if (event->key.keysym.scancode == SDL_SCANCODE_UP)
		{
		}
		if (event->key.keysym.scancode == SDL_SCANCODE_DOWN)
		{
		}
		if (event->key.keysym.scancode == SDL_SCANCODE_LEFT)
		{
			*player_angle -= 0.01f;
		}
		if (event->key.keysym.scancode == SDL_SCANCODE_RIGHT)
		{
			*player_angle += 0.01f;
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

void UpdateGame(Tile tiles[], V2 *player_tile, V2 *player, float player_angle, float FOV, SDL_Renderer *renderer)
{
	Tile line_begin_tile = {};
	bool collision = false;

	SDL_Rect rect;

	for (int i = 0; i < num_tiles; i++)
	{
		rect = { (int)tiles[i].rect.min.x, (int)tiles[i].rect.min.y, tile_size, tile_size };
		//if (tiles[i].state == 1)
		//{
			SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
			SDL_RenderFillRect(renderer, &rect);
		//}
		//else
		//{
		//	SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
		//	SDL_RenderFillRect(renderer, &rect);
		//}
		//SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);
	}

	/*int err = SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0x0, 0xFF);
	
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);*/
	for (int x = 0; x < window_width; x++)
	{
		float ray_angle = (player_angle - FOV / 2) + ((float)x / (float)window_width) * FOV;
		float distance_to_wall = 0.0f;
		float corrected_distance_to_wall = 0;
		float ray_to_player_angle = 0.0f;
		int test_point_x = 0;
		int test_point_y = 0;
		int previous_x = 0;

		//get unit vector for player angle
		V2 player_unit_vector = { sinf(ray_angle), cosf(ray_angle) };

		collision = false;

		while (!collision)
		{
			distance_to_wall += 0.1f;
			test_point_x = (int)(player_tile->x + player_unit_vector.x * distance_to_wall);
			test_point_y = (int)(player_tile->y + player_unit_vector.y * distance_to_wall);

			if (test_point_x < 0 || test_point_x >= num_tiles_x || test_point_y < 0 || test_point_y >= num_tiles_y)
			{
				collision = true;
				distance_to_wall = (float)num_tiles_x;
			}
			else
			{
				if (tiles[test_point_y * num_tiles_x + test_point_x].state > 0)
				{
					collision = true;
					V2 corner[4] = {0};
					corner[0] = { test_point_x - player_tile->x, test_point_y - player_tile->y };
					corner[1] = { (test_point_x + 1) - player_tile->x, test_point_y - player_tile->y };
					corner[2] = { test_point_x - player_tile->x, (test_point_y + 1) - player_tile->y };
					corner[3] = { (test_point_x + 1) - player_tile->x, (test_point_y + 1) - player_tile->y };

					float d[4] = {0};
					d[0] = Magnitude(corner[0]);
					d[1] = Magnitude(corner[1]);
					d[2] = Magnitude(corner[2]);
					d[3] = Magnitude(corner[3]);

					float min = d[0];
					int corner_min = 0;
					for (int i = 1; i < 4; i++)
					{
						if (d[i] < min)
						{
							min = d[i];
							corner_min = i;
						}
					}

					if (corner_min == 1)
						test_point_x += 1;
					else if (corner_min == 2)
						test_point_y += 1;
					else if (corner_min == 3)
					{
						test_point_x += 1;
						test_point_y += 1;
					}
				}
			}
		}
		
		/*float wall;
		if (player_angle >= 0)
		{
			ray_to_player_angle = player_angle - ray_angle;
		}
		else
		{
			ray_to_player_angle = ray_angle - player_angle;
		}
		corrected_distance_to_wall = (int)(distance_to_wall * cosf(ray_to_player_angle));*/
		
		
		int wall_height = (int)(window_height / distance_to_wall);
		int wall_start = -wall_height / 2 + window_height / 2;
		int wall_end = wall_height / 2 + window_height / 2;
		int red = 0xFF - distance_to_wall * 2;
		if (red <= 0) { red = 0; }
		SDL_SetRenderDrawColor(renderer, red, 0x00, 0x00, 0xFF);
		SDL_RenderDrawLine(renderer, x, wall_start, x, wall_end);
	}
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
	float FOV = 3.14159f/3.0f;
	Line line = { window_width / 2, window_height / 2, 1000, 450 };

	StartGame(tiles);
	do
	{
		StartGame(tiles);
		keep_running = true;

		start_time = SDL_GetTicks();

		HandleEvent(&event, &player, &player_angle);
		player_tile = { player.x / tile_size, player.y / tile_size };
		UpdateGame(tiles, &player_tile, &player, player_angle, FOV, renderer);

		end_time = SDL_GetTicks();
		delta_time = end_time - start_time;
		if (frame_delay > delta_time)
			SDL_Delay(frame_delay - delta_time);
	}while (keep_running);

	Cleanup();
	return 0;
}