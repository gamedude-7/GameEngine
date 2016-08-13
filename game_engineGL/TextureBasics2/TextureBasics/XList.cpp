#include "XList.h"

#include <iostream>
#include <list>
#include "T3DLIB1.h" // game library includes
#include "T3DLIB2.h"
#include "T3DLIB3.h"
#include "T3DLIB4.h"
#include "T3DLIB5.h"

using namespace std;

XList::XList()   // Constructor
{
   x = 0;
   y = 0;
   z = 0;
}

XList::XList(const XList &copyin)   // Copy constructor to handle pass by value.
{                             
   x = copyin.x;
   y = copyin.y;
   z = copyin.z;
}


XList& XList::operator=(const XList &rhs)
{
   this->x = rhs.x;
   this->y = rhs.y;
   this->z = rhs.z;
   return *this;
}
