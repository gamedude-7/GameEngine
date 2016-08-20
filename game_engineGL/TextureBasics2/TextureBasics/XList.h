// Standard Template Library example using a class.

#ifndef XLIST
#define XLIST


// The List STL template requires overloading operators =, == and <.

class XList
{   
   public:
      OBJECT4DV1 obj;

      XList();
      XList(const XList &);
      ~XList(){};
      XList &operator=(const XList &rhs);
     
};

#endif