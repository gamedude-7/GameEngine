#include "stdafx.h"
#include "inputclass.h"

InputClass::InputClass(HINSTANCE hInst, HWND main_window_handle)
{
	m_directInput = 0;
	lpdimouse = NULL;
	
	//lpdi = NULL;
	// create the main directinput object
	HRESULT hr = DirectInput8Create(hInst, DIRECTINPUT_VERSION,IID_IDirectInput8A, (void**)&m_directInput, NULL);
	if (FAILED(hr))
	{
		/* error */
	}

	hr = m_directInput->CreateDevice(GUID_SysMouse, &lpdimouse, NULL);
	if (FAILED(hr))
	{
		/* error */
	}

	hr = lpdimouse->SetCooperativeLevel(main_window_handle, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE);
	if (FAILED(hr))
	{
		/* error */
	}

	hr = lpdimouse->SetDataFormat(&c_dfDIMouse);
	if (FAILED(hr))
	{
		/* error */
	}

	hr = lpdimouse->Acquire();
	if (FAILED(hr))
	{
		/* error */
	}
}