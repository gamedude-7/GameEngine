using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;
using System.Xml.XPath;

namespace GameEngine.Classes
{
    internal class Matrix
    {
        public float[,] m;        

        public Matrix() { 
        
        }

        public static Matrix Identity { 
            get
            {
                Matrix identityMatrix = new Matrix();
                identityMatrix.m = new float[4, 4];
                for (int i = 0; i < 4; i++)
                {
                    for (int j = 0; j < 4; j++)
                    {
                        if (i == j)
                            identityMatrix.m[i, j] = 1;
                        else
                            identityMatrix.m[i, j] = 0;
                    }
                }
                return identityMatrix;
            }          
        }

        public static Matrix Zero
        {
            get
            {
                Matrix zeroMatrix = new Matrix();
                zeroMatrix.m = new float[4, 4];
                for (int i = 0; i < 4; i++)
                {
                    for (int j = 0; j < 4; j++)
                    {                       
                        zeroMatrix.m[i, j] = 0;
                    }
                }
                return zeroMatrix;
            }
        }

        public float M11
        {
            get
            {
                return m[0, 0];
            }
            set
            {
                m[0, 0] = value;
            }
        }

        public float M12
        {
            get
            {
                return m[0, 1];
            }
            set
            {
                m[0, 1] = value;
            }
        }
        public float M13
        {
            get
            {
                return m[0, 2];
            }
            set
            {
                m[0, 2] = value;
            }
        }
        public float M14
        {
            get
            {
                return m[0, 3];
            }
            set
            {
                m[0, 3] = value;
            }
        }

        public float M21
        {
            get
            {
                return m[1, 0];
            }
            set
            {
                m[1, 0] = value;
            }
        }

        public float M22
        {
            get
            {
                return m[1, 1];
            }
            set
            {
                m[1, 1] = value;
            }
        }

        public float M23
        {
            get
            {
                return m[1, 2];
            }
            set
            {
                m[1, 2] = value;
            }
        }

        public float M24
        {
            get
            {
                return m[1, 3];
            }
            set
            {
                m[1, 3] = value;
            }
        }

        public float M31
        {
            get
            {
                return m[2, 0];
            }
            set
            {
                m[2, 0] = value;
            }
        }

        public float M32
        {
            get
            {
                return m[2, 1];
            }
            set
            {
                m[2, 1] = value;
            }
        }

        public float M33
        {
            get
            {
                return m[2, 2];
            }
            set
            {
                m[2, 2] = value;
            }
        }

        public float M34
        {
            get
            {
                return m[2, 3];
            }
            set
            {
                m[2, 3] = value;
            }
        }

        public float M41 { 
            get
            {
                return m[3, 0];
            }
            set
            {
                m[3, 0] = value;
            }
        }

        public float M42
        {
            get
            {
                return m[3, 1];
            }
            set
            {
                m[3, 1] = value;
            }
        }
        public float M43
        {
            get
            {
                return m[3, 2];
            }
            set
            {
                m[3, 2] = value;
            }
        }

        public float M44
        {
            get
            {
                return m[3, 3];
            }
            set
            {
                m[3, 3] = value;
            }
        }       

       

        public static Matrix Multiply(Matrix A, Matrix B)
        {
            return A * B;
        }

        public static Matrix RotationX(float x)
        {
            Matrix result = new Matrix();
            result = Matrix.Identity;
            result.M22 = (float)Math.Cos(x);
            result.M23 = (float)-Math.Sin(x);
            result.M32 = (float)Math.Sin(x);
            result.M33 = (float)Math.Cos(x);
            return result;
        }

        public static Matrix RotationY(float y)
        {
            Matrix result = new Matrix();
            result = Matrix.Identity;
            result.M11 = (float)Math.Cos(y);
            result.M13 = (float)Math.Sin(y);
            result.M31 = (float)-Math.Sin(y);
            result.M33 = (float)Math.Cos(y);
            return result;
        }

        public static Matrix RotationZ(float z)
        {
            Matrix result = new Matrix();
            result = Matrix.Identity;
            result.M11 = (float)Math.Cos(z);
            result.M12 = (float)-Math.Sin(z);
            result.M21 = (float)Math.Sin(z);
            result.M22 = (float)Math.Cos(z);
            return result;
        }

        public static Matrix RotationYawPitchRoll(float y, float x, float z)
        {
            return Matrix.RotationY(y) * Matrix.RotationX(x) * Matrix.RotationZ(z);
        }

        public static Matrix operator *(Matrix A, Matrix B)
        {
            Matrix result = new Matrix();
            result.m = new float[4, 4];
            for (int row = 0; row < 4; row++)
            {
                for (int col = 0; col < 4; col++)
                {                 
                    int r = 0;    
                    for (int c = 0; c < 4; c++)
                    {                       
                        result.m[row, col] += A.m[row, c] * B.m[r, col];
                        r++;
                    }
                }
            }                        
            return result;
        }

        // swap matrix columns
        public Matrix swapCol(int colA, int colB)
        {
            float i, j, k;            
            i = m[0, colA];
            j = m[1, colB];
            k = m[2, colA];
            m[0, colA] = m[0,colB];
            m[1, colA] = m[1,colB];
            m[2, colA] = m[2,colB];
            m[0, colB] = i;
            m[1, colB] = j;
            m[2, colB] = k;
            return this;
        }

        public override string ToString()
        {
            string strMatrix = "";
            strMatrix += M11 + " " + M12 + " " + M13 + " " + M14 + "\n" +
                    M21 + " " + M22 + " " + M23 + " " + M24 + "\n" +
                    M31 + " " + M32 + " " + M33 +" " + M34 + "\n" +
                    M41 + " " + M42 + " " + M43 + " " + M44 + "\n";
            return strMatrix;
        }
    }
}
