using GameEngine;
using System.Drawing;
using System.Windows.Forms;
using System.Diagnostics;
namespace GUI
{    
    class Cube : OBJECT4DV1
    {
        public float width, height, length;
        
        public Cube() : base()
        {
            base.num_vertices = 8;
        }

        public override Triangle[] ConvertToTriangles()
        {
            Debug.Print("cube convert to triangles caled... YAY!!");

            int []offsets = new int[]
                 {0,1,2,3, // front
                 0,3,7,4, // left side
                 0,4,5,1, // top
                 4,5,6,7, // back
                 3,2,6,7, // bottom
                 1,2,6,5 // right side
                 };

            Point4D[] vertices = new Point4D[8];
              for (int i=0;i<8;i++)
                  vertices[i]=vlist_trans[i];

             Triangle[] result = new Triangle[6*2];

              // loop through the square sides of the cube
              for (int side=0;side<6;side++)
              {
                  // loop through triangles on each side
                  for (int v=2;v<4;v++)
                  {
                      int offset = side*4;
                      result[side*2+(v-2)]=
                          new Triangle(
                          vertices[offsets[offset]], vertices[offsets[offset+v-1]], vertices[offsets[offset+v]]);
                  }
              }
            return result;
        }

    }
   
    class GUI
    {
        private Form1 form;
        public GUI(Form1 f)
        {
            form = f;
        }                             

        public static void DrawLine(Graphics g, Pen pen, int x1, int y1, int x2, int y2, int borderwidth, int borderheight)
        {
            int flag;
            Point p1 = new Point(x1,y1), p2 = new Point(x2,y2);
            Parametric_Line2D pl1 = new Parametric_Line2D(p1, p2);

            // right border
            p1 = new Point(borderwidth, 0); 
            p2 = new Point(borderwidth, borderheight);
            Parametric_Line2D pl2 = new Parametric_Line2D(p1,p2);
            Point p = new Point();
            flag =Engine.Intersect_Parametric_Line2D(pl1, pl2, ref p);
            if (flag == (int)PARM_LINE.LINE_INTERSECT_IN_SEGMENT)
            {
                if (x2>borderwidth)
                {
                    x2 = p.X;
                    y2 = p.Y;                
                }
                else if (x1>borderwidth)
                {
                    x1 = p.X;
                    y1 = p.Y;
                }
            }

            // left border
            p1 = new Point(0,0);
            p2 = new Point(0,borderheight);
            pl2 = new Parametric_Line2D(p1,p2);
            flag = (int)Engine.Intersect_Parametric_Line2D(pl1,pl2,ref p);
            if (flag == (int)PARM_LINE.LINE_INTERSECT_IN_SEGMENT)
            {
                if (x2 < 0)
                {
                    x2 = p.X;
                    y2 = p.Y;        
                }
                else if (x1 < 0)
                {
                    x1 = p.X;
                    y1 = p.Y;
                }
            }

            // top border
            p1 = new Point(0, 0);
            p2 = new Point(borderwidth,0);
            pl2 = new Parametric_Line2D(p1, p2);
            flag = (int)Engine.Intersect_Parametric_Line2D(pl1, pl2, ref p);
            if (flag == (int)PARM_LINE.LINE_INTERSECT_IN_SEGMENT)
            {
                if (y2 < 0)
                {
                    x2 = p.X;
                    y2 = p.Y;
                }
                else if (y1 < 0)
                {
                    x1 = p.X;
                    y1 = p.Y;
                }
            }

            // bottom border
            p1 = new Point(0, borderheight);
            p2 = new Point(borderwidth, borderheight);
            pl2 = new Parametric_Line2D(p1, p2);
            flag = (int)Engine.Intersect_Parametric_Line2D(pl1, pl2, ref p);
            if (flag == (int)PARM_LINE.LINE_INTERSECT_IN_SEGMENT)
            {
                if (y2 > borderheight)
                {
                    x2 = p.X;
                    y2 = p.Y;
                }
                else if (y1 > borderheight)
                {
                    x1 = p.X;
                    y1 = p.Y;
                }
            }

            if (x1>=0 && x1<=borderwidth && x2>=0 && x2<=borderwidth && y1>=0 & y1<=borderheight && y2>=0 && y2<=borderheight)
            {
                g.DrawLine(pen, x1, y1, x2, y2);
            }
            
        }
    }
}
