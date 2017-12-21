#ifndef _UTILS_H
#define _UTILS_H

#include <iostream>
#include <iomanip> // setprecision
#include <sstream> // stringstream

#include <openvr.h>
#include <SDL.h>
#include <SDL_ttf.h>

using namespace std;

SDL_Color black_color = { 0, 0, 0, 255 };
SDL_Color green_color = { 0, 200, 0, 255 };
SDL_Renderer* renderer;

void print_text(TTF_Font*, const char*, SDL_Color, int, int);
string ftos(float f, int precision); // float to string with 2-decimal precision
string vftos(float* v, int precision); // float vector to string with 2-decimal precisions
string GetTrackedDeviceString(vr::IVRSystem*, vr::TrackedDeviceIndex_t, vr::TrackedDeviceProperty, vr::TrackedPropertyError *peError = NULL);
string GetTrackedDeviceClassString(vr::ETrackedDeviceClass td_class);

#endif