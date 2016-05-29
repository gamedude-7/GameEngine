// INCLUDES //
//////////////
#include <dinput.h>

class InputClass
{
public:
	InputClass(HINSTANCE hInst, HWND main_window_handle);
	LPDIRECTINPUTDEVICE8W lpdimouse; // the mouse device
	IDirectInputDevice8* m_mouse;
private:
	IDirectInput8* m_directInput;
	
	
	DIMOUSESTATE mousestate;
	//LPDIRECTINPUTDEVICE8W lpdi; // use to point to com interface
};

