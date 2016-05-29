#ifndef COLOR_H
#define COLOR_H

//struct Color
//{
//
//	union
//	{
//		int rgba;	// compressed format
//		//unsigned char rgba[4];
//		/*struct { 
//			unsigned char r, g, b, a;
//		};*/
//	}
//
//};
class Color
{
public:
union 
    {
    int rgba;                    // compressed format
    unsigned char rgba_M[4];             // array format
    struct {  unsigned char a,b,g,r;  }; // explict name format
    }; // end union
    
} ;
#endif