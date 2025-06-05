#pragma once

#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

// variable translations
#define REAL static float
#define INTEGER static int

// comparisons
#define IF		if
#define ELSEIF	else if
#define EQUALS	==
#define NOTEQUAL !=

// block starts and ends
#define BEGIN	{
#define END		}

#define BEGINIF		{
#define ENDIF		}
#define ENDWHILE	}
#define ENDELSE		}
#define ENDFOR		}

// looping
#define WHILE	while
#define FOR		for

#define VK_W	0x57
#define VK_A	0x41
#define VK_S	0x53
#define VK_D	0x44

#define VK_Q	0x51