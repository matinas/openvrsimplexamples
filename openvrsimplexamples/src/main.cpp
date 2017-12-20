#include <iostream>
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

// app variables
bool app_end = false;

int init_SDL();

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
				}
				break;
			}
		}
	}

	return 0;
}

int init_SDL()
{
	if (SDL_Init(SDL_INIT_EVENTS) != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		SDL_Quit();

		return -1;
	}

	window = SDL_CreateWindow("OpenVR examples", 200, 200, 640, 480, SDL_WINDOW_SHOWN); // Seems that if we don't initialize a windows SDL's event subsystem doesn't work
	if (window == NULL)
	{
		SDL_Log("Unable to create SDL Window: %s", SDL_GetError());
		SDL_Quit();
		return -1;
	}

	if (TTF_Init() != 0)
	{
		SDL_Log("Unable to initialize SDL ttf: %s", TTF_GetError());
		SDL_Quit();

		return -1;
	}

	SDL_Log("SDL successfully initialized");

	return 0;
}