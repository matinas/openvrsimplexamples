#include <iostream>
#include <iomanip> // setprecision
#include <sstream> // stringstream

#include <openvr.h>
#include <SDL.h>
#include <SDL_ttf.h>

using namespace std;
using namespace vr;

// OpenVR variables 
HmdError err;
IVRSystem* vr_context;

// SDL variables 
SDL_Event event;
SDL_Window* window;
SDL_Renderer* renderer;
SDL_Texture* solidTexture;
SDL_Color textColor = { 0, 0, 0, 255 };
SDL_Rect solidRect;
SDL_Rect windowRect = { 900, 300, 400, 400 };

TTF_Font* font;

// app variables
bool app_end = false;
float counter = 0;

int init_SDL();
void print_text(TTF_Font*, const char*, SDL_Color, int, int);
string ftos(float f); // float to string with 2-decimal precision

int main(int argv, char** args) {

	if (init_SDL() != 0) return -1;

	//if (VR_IsHmdPresent())
	//{
	//	cout << "An HMD was successfully found in the system" << endl;

	//	if (VR_IsRuntimeInstalled()) {
	//		const char* runtime_path = VR_RuntimePath();
	//		cout << "Runtime correctly installed at '" << runtime_path << "'" << endl;
	//	}
	//	else
	//	{
	//		cout << "Runtime was not found, quitting app" << endl;
	//		return -1;
	//	}
	//}
	//else
	//{
	//	cout << "No HMD was found in the system, quitting app" << endl;
	//	return -1;
	//}

	//// Load the SteamVR Runtime
	//vr_context = VR_Init(&err,EVRApplicationType::VRApplication_Scene);
	//vr_context == NULL ? cout << "Error while initializing SteamVR runtime. Error code is " << VR_GetVRInitErrorAsSymbol(err) << endl : cout << "SteamVR runtime successfully initialized" << endl;

	while (!app_end)
	{
		SDL_RenderClear(renderer);

		while (SDL_PollEvent(&event))
		{
			cout << "entro" << endl;

			switch (event.type)
			{
			case SDL_KEYDOWN:
				{ 
					if (event.key.keysym.sym == SDLK_ESCAPE)
					{
						cout << "Exiting app..." << endl;

						VR_Shutdown();
						SDL_Quit();
						app_end = true;
					}
					else if (event.key.keysym.sym == SDLK_SPACE)
					{
						counter+=0.123f;
					}
				}

				break;
			}
		}

		print_text(font, "Device count: 0", textColor, 10, 10);
		print_text(font, ("Tracked devices: " + ftos(counter)).c_str(), textColor, 10, 40);
		
		SDL_RenderPresent(renderer);
	}

	TTF_CloseFont(font);

	return 0;
}

string ftos(float f)
{
	stringstream stream;
	stream << fixed << setprecision(2) << f;
	string f_str = stream.str();

	return f_str;
}

void print_text(TTF_Font* font, const char* text, SDL_Color color, int posX, int posY)
{
	SDL_Surface* solid = TTF_RenderText_Solid(font, text, color);
	solidTexture = SDL_CreateTextureFromSurface(renderer, solid);
	SDL_QueryTexture(solidTexture, NULL, NULL, &solidRect.w, &solidRect.h);
	solidRect.x = posX;
	solidRect.y = posY;

	SDL_RenderCopy(renderer, solidTexture, NULL, &solidRect);
	SDL_DestroyTexture(solidTexture);
	SDL_FreeSurface(solid);
}

int init_SDL()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		SDL_Quit();

		return -1;
	}

	window = SDL_CreateWindow("OpenVR examples", windowRect.x, windowRect.y, windowRect.w, windowRect.h, 0); // Seems that if we don't initialize a windows SDL's event subsystem doesn't work
	if (window == NULL)
	{
		SDL_Log("Unable to create SDL Window: %s", SDL_GetError());
		SDL_Quit();

		return -1;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL)
	{
		SDL_Log("Unable to create SDL Renderer: %s", SDL_GetError());
		SDL_Quit();

		return -1;
	}

	// Set size of renderer to the same as window
	SDL_RenderSetLogicalSize(renderer, windowRect.w, windowRect.h);

	// Set color of renderer to red
	SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);

	if (TTF_Init() != 0)
	{
		SDL_Log("Unable to initialize SDL ttf: %s", TTF_GetError());
		SDL_Quit();

		return -1;
	}

	if ((font = TTF_OpenFont("resources\\fonts\\Titillium-Semibold.otf", 20)) == NULL)
	{
		SDL_Log("Unable to load ttf font: %s", TTF_GetError());
		SDL_Quit();

		return -1;
	}

	SDL_Log("SDL successfully initialized");

	return 0;
}