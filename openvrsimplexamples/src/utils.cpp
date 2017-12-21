#include "utils.h"

//-----------------------------------------------------------------------------
// Purpose: Helper to get a string from a tracked device property and turn it
//			into a std::string
//-----------------------------------------------------------------------------
string GetTrackedDeviceString(vr::IVRSystem *pHmd, vr::TrackedDeviceIndex_t unDevice, vr::TrackedDeviceProperty prop, vr::TrackedPropertyError *peError)
{
	uint32_t requiredBufferLen = pHmd->GetStringTrackedDeviceProperty(unDevice, prop, NULL, 0, peError);
	if( requiredBufferLen == 0 )
		return "";

	char *pchBuffer = new char[requiredBufferLen];
	requiredBufferLen = pHmd->GetStringTrackedDeviceProperty(unDevice,prop,pchBuffer,requiredBufferLen,peError);
	string sResult = pchBuffer;
	delete[] pchBuffer;
	return sResult;
}

//-----------------------------------------------------------------------------
// Purpose: Helper to get a string from a tracked device type class
//-----------------------------------------------------------------------------
string GetTrackedDeviceClassString(vr::ETrackedDeviceClass td_class) {

	string str_td_class = "Unknown class";

	switch (td_class)
	{
	case vr::TrackedDeviceClass_Invalid:			// = 0, the ID was not valid.
		str_td_class = "invalid";
		break;
	case vr::TrackedDeviceClass_HMD:				// = 1, Head-Mounted Displays
		str_td_class = "hmd";
		break;
	case vr::TrackedDeviceClass_Controller:			// = 2, Tracked controllers
		str_td_class = "controller";
		break;
	case vr::TrackedDeviceClass_GenericTracker:		// = 3, Generic trackers, similar to controllers
		str_td_class = "generic tracker";
		break;
	case vr::TrackedDeviceClass_TrackingReference:	// = 4, Camera and base stations that serve as tracking reference points
		str_td_class = "base station";
		break;
	case vr::TrackedDeviceClass_DisplayRedirect:	// = 5, Accessories that aren't necessarily tracked themselves, but may redirect video output from other tracked devices
		str_td_class = "display redirect";
		break;
	}

	return str_td_class;
}

string vftos(float v[3], int precision)
{
	stringstream stream;
	stream << "(" << ftos(v[0],precision) << "," << ftos(v[1],precision) << "," << ftos(v[2],precision) << ")";
	string f_str = stream.str();

	return f_str;
}

string ftos(float f, int precision)
{
	stringstream stream;
	stream << fixed << setprecision(precision) << f;
	string f_str = stream.str();

	return f_str;
}

void print_text(TTF_Font* font, const char* text, SDL_Color color, int posX, int posY)
{
	SDL_Surface* solid = TTF_RenderText_Solid(font, text, color);
	SDL_Texture* text_texture = SDL_CreateTextureFromSurface(renderer, solid);

	SDL_Rect solidRect;
	SDL_QueryTexture(text_texture, NULL, NULL, &solidRect.w, &solidRect.h);
	solidRect.x = posX;
	solidRect.y = posY;

	SDL_RenderCopy(renderer, text_texture, NULL, &solidRect);
	SDL_DestroyTexture(text_texture);
	SDL_FreeSurface(solid);
}