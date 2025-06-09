using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using GUI;
//using Microsoft.DirectX;
//using Microsoft.DirectX.Direct3D;
using System.IO;
using System.Runtime.InteropServices;
using System.Diagnostics;
using System.Runtime.InteropServices.ComTypes;
using GameEngine.Classes;
using System.Reflection;

namespace GameEngine
{

    public partial class Form1 : Form
    {
        float width, height;
        const int WM_KEYDOWN = 0x100;
        const int WM_SYSKEYDOWN = 0x104;

        [DllImport("user32.dll")]
        public static extern int SendMessage(IntPtr hwnd,
        [MarshalAs(UnmanagedType.U4)] int Msg, int wParam,
        [MarshalAs(System.Runtime.InteropServices.UnmanagedType.LPStr)] string
        lParam);
        private const int DEBUG = 0;
        private int x, y;
        private float z;
        //private Graphics g;
        private Pen p;
        private bool isMouseDown;
        private CAM4DV1 camFront = new CAM4DV1(),
                                   camLeft = new CAM4DV1(),
                                   camTop = new CAM4DV1(),
                                   camMain = new CAM4DV1();
        private Cube cube;
        private int numOfObjects;
        private Process game;
        private OBJECT4DV1 objectInstance;
        LinkedList<OBJECT4DV1> listObjects;

        bool sendingMessage = false;

        //        protected override void WndProc(
        //            ref Message m
        //            )
        //        {
        //            Point mp = MousePosition;

        //            if (m.Msg == WM_KEYDOWN || m.Msg == WM_SYSKEYDOWN)
        //            {
        ////                if (sendingMessage)
        ////                {
        ////                    m.Result = (IntPtr)0;
        ////                    return;
        ////                }
        //                Debug.Print("Mouse Wheel: lparam = {0},WParam = {1}, Result ={2}",
        //m.LParam, m.WParam, m.Result);
        //                if (m.WParam.ToInt32()==65) // a
        //                    camMain.pos.X-=5;
        //                else if (m.WParam.ToInt32()==68) //d
        //                    camMain.pos.X+=5;
        //                splitContainer2_Panel2_Paint(null, null);
        ////                try
        ////                {
        ////                    sendingMessage = true;
        ////                    SendMessage(GetChildAtPoint(PointToClient(mp)).Handle,
        ////                        m.Msg, m.WParam.ToInt32(), m.LParam.ToString());
        ////                    sendingMessage = false;
        ////                }
        ////                catch (Exception exception)
        ////                {
        ////                    exception.ToString();
        ////                }
        ////                m.Result = (IntPtr)0;
        // textBox1.Text += m.Msg + "\r\n";
        //            }
        //            base.WndProc(ref m);
        //        }


        protected override bool ProcessCmdKey(ref Message msg, Keys keyData)
        {
            if ((msg.Msg == WM_KEYDOWN) || (msg.Msg == WM_SYSKEYDOWN))
            {
                switch (keyData)
                {
                    case Keys.A:
                        moveSideways(-5);
                        break;
                    case Keys.D:
                        moveSideways(5);
                        break;
                    case Keys.W:
                        moveForward(5);
                        break;
                    case Keys.S:
                        moveForward(-5);
                        break;
                    case Keys.Up:
                        camMain.pos.Y += 5;
                        break;
                    case Keys.Down:
                        camMain.pos.Y -= 5;
                        break;
                    case Keys.Left:
                        camMain.pos.X -= 5;
                        break;
                    case Keys.Right:
                        camMain.pos.X += 5;
                        break;
                }
                splitContainer2_Panel2_Paint(null, null);
            }
            return base.ProcessCmdKey(ref msg, keyData);
        }

        public Form1()
        {
            InitializeComponent();
            width = this.Width;
            height = this.Height;
            this.WindowState = FormWindowState.Maximized;


            listObjects = new LinkedList<OBJECT4DV1>();

            numOfObjects = listObjects.Count;
            p = new Pen(Color.Black);
            isMouseDown = false;
            float fov = 90; // field of view
            #region init cameras
            // front cam
            Point4D cam_pos = new Point4D(0, 0, -100, 0);
            Vector cam_dir = new Vector(0, 0, 0, 0);
            camFront.Init_CAM4DV1(cam_pos, cam_dir, fov,
                                                 splitContainer1.Panel1.Width,
                                                 splitContainer1.Panel1.Height);
            // left cam
            cam_pos.X = -100;
            cam_pos.Z = 0;
            cam_dir.Y = (float)Math.PI / 2;
            camLeft.Init_CAM4DV1(cam_pos, cam_dir, fov,
                                                splitContainer1.Panel2.Width,
                                                splitContainer1.Panel2.Height);
            // top cam
            cam_pos.X = 0; cam_pos.Y = 100; cam_pos.Z = 0;
            cam_dir.X = (float)Math.PI / 2; cam_dir.Y = 0;
            camTop.Init_CAM4DV1(cam_pos, cam_dir, fov,
                                                splitContainer2.Panel1.Width,
                                                splitContainer2.Panel1.Height);

            // main cams
            cam_pos.X = 0; cam_pos.Y = 0; cam_pos.Z = -100;
            cam_dir.X = 0; cam_dir.Y = 0; cam_dir.Z = 0;
            camMain.Init_CAM4DV1(cam_pos, cam_dir, fov,
                                                splitContainer2.Panel2.Width,
                                                splitContainer2.Panel2.Height);

            #endregion
        }

        private void toolStrip1_ItemClicked(object sender, ToolStripItemClickedEventArgs e)
        {
            tsbMove.Checked = false;
            tsbRotate.Checked = false;
            tsbScale.Checked = false;
            tsbSelect.Checked = false;
            tsbCube.Checked = false;
            if (e.ClickedItem == tsbMove)
                tsbMove.Checked = true;
            else if (e.ClickedItem == tsbRotate)
                tsbRotate.Checked = true;
            else if (e.ClickedItem == tsbScale)
                tsbScale.Checked = true;
            else if (e.ClickedItem == tsbSelect)
                tsbSelect.Checked = true;
            else if (e.ClickedItem == tsbCube)
                tsbCube.Checked = true;
        }

        private void saveToolStripMenuItem_Click(object sender, EventArgs e)
        {
            DialogResult dr;
            Stream fileStream;
            StreamWriter wtr;
            saveFileDialog1.Filter = "Text file (*.txt)|*.txt|PLY File (*.ply)|*.ply |PLG File (*.plg)|*.plg|Level File (*.lvl)|*.lvl";
            dr = saveFileDialog1.ShowDialog();

            if (dr == DialogResult.OK)
            {
                fileStream = saveFileDialog1.OpenFile();
                wtr = new StreamWriter(fileStream);
                String extention = saveFileDialog1.FileName.Substring(saveFileDialog1.FileName.Length - 4);
                if (extention == ".txt")
                {
                    wtr.WriteLine(listObjects.Count);
                    foreach (OBJECT4DV1 o in listObjects)
                    {
                        wtr.WriteLine("cube 8");
                        for (int i = 0; i < 8; i++)
                        {
                            wtr.WriteLine(o.vlist_trans[i].X + " " + o.vlist_trans[i].Y + " " + o.vlist_trans[i].Z);
                        }
                    }
                }
                else if (extention == ".ply")
                {
                    LinkedList<Triangle> modelAsTriangles = new LinkedList<Triangle>();
                    foreach (OBJECT4DV1 o in listObjects)
                    {
                        Triangle[] triangles = o.ConvertToTriangles();
                        for (int i = 0; i < triangles.Length; i++)
                            modelAsTriangles.AddLast(triangles[i]);
                    }
                    int numTriangles = modelAsTriangles.Count;
                    wtr.Write("ply\n");
                    wtr.Write("format ascii 1.0\n");
                    wtr.Write("comment generator Josh Greig's opensource "
                          + "PolyMapper available at http://www.planet-source-code.com"
                          + " and http://www.programmersheaven.com\n");
                    wtr.Write("element vertex " + (numTriangles * 3) + '\n');
                    wtr.Write("property float x\n");
                    wtr.Write("property float y\n");
                    wtr.Write("property float z\n");
                    wtr.Write("property uchar red\n");
                    wtr.Write("property uchar green\n");
                    wtr.Write("property uchar blue\n");
                    wtr.Write("element face " + numTriangles + '\n');
                    wtr.Write("property list uchar int vertex_index\n");
                    wtr.Write("end_header\n");

                    // loop through triangles
                    foreach (Triangle t in modelAsTriangles)
                    {
                        // loop through vertices of the triangle
                        for (int i = 0; i < 3; i++)
                        {
                            wtr.Write(t.vlist_trans[i].X + " " + t.vlist_trans[i].Y + " " + t.vlist_trans[i].Z);
                            wtr.Write(" 255 255 255\n");
                        }
                    }
                    int triIndex = 0;
                    // loop through faces(polygons, triangles)
                    foreach (Triangle t in modelAsTriangles)
                    {
                        int offset = 3 * triIndex;
                        // loop through sides of the cube
                        wtr.Write("3 " + offset + " " + (offset + 1) + " " + (offset + 2) + "\n");
                        triIndex++;
                    }
                }
                wtr.Close();
                fileStream.Close();
                if (extention == ".lvl")
                {
                    SaveLevel(saveFileDialog1.FileName);
                }
            }
        }

        private void openToolStripMenuItem_Click(object sender, EventArgs e)
        {

            DialogResult dr;
            FileStream theFile;
            StreamReader rdr;
            String str;
            string sPath = "";
            string[] split;
            string[] token;
            listObjects.Clear();

            dr = openFileDialog1.ShowDialog(this);

            if (dr == DialogResult.OK)
            {
                sPath = openFileDialog1.FileName;

                if (sPath.Substring(sPath.Length - 4) == ".txt")
                {
                    theFile = File.Open(sPath, FileMode.Open, FileAccess.Read);
                    rdr = new StreamReader(theFile);

                    while ((str = rdr.ReadLine()) != null)
                    {
                        split = str.Split(new Char[] { ' ' });
                        if (split[0] == "cube")
                        {
                            cube = new Cube();
                            for (int i = 0; i < int.Parse(split[1]); i++)
                            {
                                str = rdr.ReadLine();
                                token = str.Split(new Char[] { ' ' });
                                cube.vlist_trans[i].X = float.Parse(token[0]);
                                cube.vlist_trans[i].Y = float.Parse(token[1]);
                                cube.vlist_trans[i].Z = float.Parse(token[2]);
                                cube.vlist_trans[i].W = 1;
                            }

                            listObjects.AddLast(cube);
                        }
                    }
                }
                else if (sPath.Substring(sPath.Length - 4) == ".plg")
                {
                    /*cube = new Cube();                    
                    cube.Load_PLG(ref sPath,new Vector4(1, 1, 1, 1), new Vector4(0, 0, 0, 0), new Vector4(0, 0, 0, 0));
                    #region local to world coordinates
                    for (int i = 0; i < 8; i++)
                    {
                        cube.vlist_trans[i].X = cube.world_pos.X + cube.vlist_local[i].X;
                        cube.vlist_trans[i].Y = cube.world_pos.Y + cube.vlist_local[i].Y;
                        cube.vlist_trans[i].Z = cube.world_pos.Z + cube.vlist_local[i].Z;
                        cube.vlist_trans[i].W = 1;
                    }
                    #endregion
                    listObjects.AddLast(cube);*/

                    OBJECT4DV1 obj = new OBJECT4DV1();
                    obj.Load_PLG(ref sPath, new Vector(1, 1, 1, 1), new Vector(0, 0, 0, 1), new Vector(0, 0, 0, 1));
                    for (int i = 0; i < obj.num_vertices; i++)
                    {
                        obj.vlist_trans[i].X = obj.world_pos.X + obj.vlist_local[i].X;
                        obj.vlist_trans[i].Y = obj.world_pos.Y + obj.vlist_local[i].Y;
                        obj.vlist_trans[i].Z = obj.world_pos.Z + obj.vlist_local[i].Z;
                        obj.vlist_trans[i].W = 1;
                    }
                    listObjects.AddLast(obj);
                }
                else if (sPath.Substring(sPath.Length - 4) == ".lvl")
                {
                    theFile = File.Open(sPath, FileMode.Open, FileAccess.Read);
                    rdr = new StreamReader(theFile);
                    str = rdr.ReadLine();
                    int cnt = int.Parse(str);
                    for (int i = 0; i < cnt; i++)
                    {
                        str = rdr.ReadLine();
                        if (str == "cube")
                        {
                            cube = new Cube();
                            string strName = rdr.ReadLine();
                            cube.name = strName;
                            cube.scriptName = rdr.ReadLine();
                            str = rdr.ReadLine();
                            token = str.Split(new Char[] { ' ' });
                            cube.world_pos.X = float.Parse(token[0]);
                            cube.world_pos.Y = float.Parse(token[1]);
                            cube.world_pos.Z = float.Parse(token[2]);
                            str = rdr.ReadLine();
                            token = str.Split(new Char[] { ' ' });
                            cube.width = float.Parse(token[0]);
                            cube.height = float.Parse(token[1]);
                            cube.length = float.Parse(token[2]);
                            str = rdr.ReadLine();
                            token = str.Split(new Char[] { ' ' });
                            cube.dir.X = float.Parse(token[0]);
                            cube.dir.Y = float.Parse(token[1]);
                            cube.dir.Z = float.Parse(token[2]);
                            str = rdr.ReadLine();
                            token = str.Split(new Char[] { ' ' });
                            cube.scale.X = float.Parse(token[0]);
                            cube.scale.Y = float.Parse(token[1]);
                            cube.scale.Z = float.Parse(token[2]);
                            cube.vlist_local[0].X = -cube.width / 2;
                            cube.vlist_local[0].Y = cube.height / 2;
                            cube.vlist_local[0].Z = -cube.length / 2;
                            cube.vlist_local[1].X = cube.width / 2;
                            cube.vlist_local[1].Y = cube.height / 2;
                            cube.vlist_local[1].Z = -cube.length / 2;
                            cube.vlist_local[2].X = cube.width / 2;
                            cube.vlist_local[2].Y = -cube.height / 2;
                            cube.vlist_local[2].Z = -cube.length / 2;
                            cube.vlist_local[3].X = -cube.width / 2;
                            cube.vlist_local[3].Y = -cube.height / 2;
                            cube.vlist_local[3].Z = -cube.length / 2;
                            cube.vlist_local[4].X = -cube.width / 2;
                            cube.vlist_local[4].Y = cube.height / 2;
                            cube.vlist_local[4].Z = cube.length;
                            cube.vlist_local[5].X = cube.width / 2;
                            cube.vlist_local[5].Y = cube.height / 2;
                            cube.vlist_local[5].Z = cube.length;
                            cube.vlist_local[6].X = cube.width / 2;
                            cube.vlist_local[6].Y = -cube.height / 2;
                            cube.vlist_local[6].Z = cube.length;
                            cube.vlist_local[7].X = -cube.width / 2;
                            cube.vlist_local[7].Y = -cube.height / 2;
                            cube.vlist_local[7].Z = cube.length;

                            cube.num_polys = 6;
                            cube.plist[0] = new POLY4DV1();
                            cube.plist[0].poly_num_verts = 4;
                            cube.plist[0].vert = new int[4];
                            cube.plist[0].vert[0] = 0;
                            cube.plist[0].vert[1] = 1;
                            cube.plist[0].vert[2] = 2;
                            cube.plist[0].vert[3] = 3;

                            cube.plist[1] = new POLY4DV1();
                            cube.plist[1].poly_num_verts = 4;
                            cube.plist[1].vert = new int[4];
                            cube.plist[1].vert[0] = 4;
                            cube.plist[1].vert[1] = 5;
                            cube.plist[1].vert[2] = 6;
                            cube.plist[1].vert[3] = 7;

                            cube.plist[2] = new POLY4DV1();
                            cube.plist[2].poly_num_verts = 4;
                            cube.plist[2].vert = new int[4];
                            cube.plist[2].vert[0] = 0;
                            cube.plist[2].vert[1] = 3;
                            cube.plist[2].vert[2] = 7;
                            cube.plist[2].vert[3] = 4;

                            cube.plist[3] = new POLY4DV1();
                            cube.plist[3].poly_num_verts = 4;
                            cube.plist[3].vert = new int[4];
                            cube.plist[3].vert[0] = 1;
                            cube.plist[3].vert[1] = 2;
                            cube.plist[3].vert[2] = 6;
                            cube.plist[3].vert[3] = 5;

                            cube.plist[4] = new POLY4DV1();
                            cube.plist[4].poly_num_verts = 4;
                            cube.plist[4].vert = new int[4];
                            cube.plist[4].vert[0] = 0;
                            cube.plist[4].vert[1] = 1;
                            cube.plist[4].vert[2] = 5;
                            cube.plist[4].vert[3] = 4;

                            cube.plist[5] = new POLY4DV1();
                            cube.plist[5].poly_num_verts = 4;
                            cube.plist[5].vert = new int[4];
                            cube.plist[5].vert[0] = 2;
                            cube.plist[5].vert[1] = 3;
                            cube.plist[5].vert[2] = 7;
                            cube.plist[5].vert[3] = 6;
                            //#endregion
                            cube.id = i;
                            listObjects.AddLast(cube);
                        }
                        else if (str == "object")
                        {
                            OBJECT4DV1 obj = new OBJECT4DV1();
                            string strName = rdr.ReadLine();
                            obj.name = strName;
                            obj.scriptName = rdr.ReadLine();
                            str = rdr.ReadLine();
                            token = str.Split(new Char[] { ' ' });
                            obj.world_pos.X = float.Parse(token[0]);
                            obj.world_pos.Y = float.Parse(token[1]);
                            obj.world_pos.Z = float.Parse(token[2]);
                            str = rdr.ReadLine();
                            token = str.Split(new Char[] { ' ' });
                            obj.dir.X = float.Parse(token[0]);
                            obj.dir.Y = float.Parse(token[1]);
                            obj.dir.Z = float.Parse(token[2]);
                            str = rdr.ReadLine();
                            token = str.Split(new Char[] { ' ' });
                            obj.scale.X = float.Parse(token[0]);
                            obj.scale.Y = float.Parse(token[1]);
                            obj.scale.Z = float.Parse(token[2]);
                            str = rdr.ReadLine();
                            obj.num_vertices = int.Parse(str);
                            for (int j = 0; j < obj.num_vertices; j++)
                            {
                                str = rdr.ReadLine();
                                token = str.Split(new Char[] { ' ' });
                                obj.vlist_local[j].X = float.Parse(token[0]);
                                obj.vlist_local[j].Y = float.Parse(token[1]);
                                obj.vlist_local[j].Z = float.Parse(token[2]);
                            }
                            str = rdr.ReadLine();
                            obj.num_polys = int.Parse(str);
                            for (int j = 0; j < obj.num_polys; j++)
                            {
                                str = rdr.ReadLine();
                                token = str.Split(new Char[] { ' ' });
                                obj.plist[j] = new POLY4DV1();
                                obj.plist[j].vert[0] = int.Parse(token[0]);
                                obj.plist[j].vert[1] = int.Parse(token[1]);
                                obj.plist[j].vert[2] = int.Parse(token[2]);
                            }
                            obj.id = i;
                            listObjects.AddLast(obj);
                        }
                    }
                    theFile.Close();
                }
                UpdateTree();
            }

            numOfObjects = listObjects.Count;

            containerControl1_Paint(null, null);
        }

        private void splitContainer1_Panel1_MouseWheel(object sender, MouseEventArgs e)
        {
            int x2, x1, y1, y2;
            float xper, yper;
            if (isMouseDown)
            {
                if (tsbCube.Checked)
                {
                    if (listObjects.Count > numOfObjects)
                    {
                        listObjects.RemoveLast();
                    }
                }
                if ((cube.length + (e.Delta >> 4)) > 0)
                    cube.length += e.Delta >> 4;
                else
                    cube.length = 1;

                if (tsbCube.Checked)
                {
                    if (listObjects.Count > numOfObjects)
                    {
                        listObjects.RemoveLast();
                    }
                    p.Color = Color.Black;
                    #region cube
                    xper = (e.X - splitContainer1.Panel1.Width / 2f) / (splitContainer1.Panel1.Width / 2f);
                    x1 = (int)(xper * (-camFront.pos.Z));
                    xper = (x - splitContainer1.Panel1.Width / 2f) / (splitContainer1.Panel1.Width / 2f);
                    x2 = (int)(xper * (-camFront.pos.Z));

                    if (x2 > x1)
                        cube.width = (x2 - x1);// *(int)camFront.pos.Z / -100;
                    else
                        cube.width = (x1 - x2);// *(int)camFront.pos.Z / -100;

                    yper = (e.Y - splitContainer1.Panel1.Height / 2f) / (splitContainer1.Panel1.Height / 2f);
                    y1 = (int)(yper * (-camFront.pos.Z));
                    yper = (y - splitContainer1.Panel1.Height / 2f) / (splitContainer1.Panel1.Height / 2f);
                    y2 = (int)(yper * (-camFront.pos.Z));

                    if (y2 > y1)
                        cube.height = Math.Abs(y2 - y1);// * (int)camFront.pos.Z / -100;
                    else
                        cube.height = Math.Abs(y1 - y2);// *(int)camFront.pos.Z / -100;

                    cube.world_pos.X = ((x1 + x2) / 2);// *camFront.pos.Z / (-100);
                    cube.world_pos.Y = -((y1 + y2) / 2);// (splitContainer1.Panel1.Height - (y1 + y2) / 2);//(y + (e.Y - y) / 2) - splitContainer1.Panel1.Height / 2) * (int)camFront.pos.Z / (-100) ;                    
                    cube.world_pos.Z = (cube.length / 2);// *camFront.pos.Z / (-100);

                    #endregion
                    #region local coordinates
                    cube.vlist_local[0].X = -cube.width / 2;
                    cube.vlist_local[0].Y = cube.height / 2;
                    cube.vlist_local[0].Z = -cube.length / 2;
                    cube.vlist_local[1].X = cube.width / 2;
                    cube.vlist_local[1].Y = cube.height / 2;
                    cube.vlist_local[1].Z = -cube.length / 2;
                    cube.vlist_local[2].X = cube.width / 2;
                    cube.vlist_local[2].Y = -cube.height / 2;
                    cube.vlist_local[2].Z = -cube.length / 2;
                    cube.vlist_local[3].X = -cube.width / 2;
                    cube.vlist_local[3].Y = -cube.height / 2;
                    cube.vlist_local[3].Z = -cube.length / 2;
                    cube.vlist_local[4].X = -cube.width / 2;
                    cube.vlist_local[4].Y = cube.height / 2;
                    cube.vlist_local[4].Z = cube.length / 2;
                    cube.vlist_local[5].X = cube.width / 2;
                    cube.vlist_local[5].Y = cube.height / 2;
                    cube.vlist_local[5].Z = cube.length / 2;
                    cube.vlist_local[6].X = cube.width / 2;
                    cube.vlist_local[6].Y = -cube.height / 2;
                    cube.vlist_local[6].Z = cube.length / 2;
                    cube.vlist_local[7].X = -cube.width / 2;
                    cube.vlist_local[7].Y = -cube.height / 2;
                    cube.vlist_local[7].Z = cube.length / 2;
                    #endregion
                    listObjects.AddLast(cube);
                }
            }
            else
            {
                camFront.pos.Z += e.Delta >> 4;
                toolStripStatusLabel1.Text = "(" + camFront.pos.X + ", " + camFront.pos.Y + ", " + camFront.pos.Z + ")";
                toolStripStatusLabel2.Text = "(" + camFront.dir.X + ", " + camFront.dir.Y + ", " + camFront.dir.Z + ")";
                toolStripStatusLabel3.Text = camFront.dir.X * 180 / Math.PI + ", " + camFront.dir.Y * 180 / Math.PI + ", " + camFront.dir.Z * 180 / Math.PI;
            }
            containerControl1_Paint(null, null);
        }

        private void splitContainer1_Panel1_MouseDown(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                x = e.X;
                y = e.Y;
                z = camFront.pos.Z;
                isMouseDown = true;
                cube = new Cube();
            }
        }

        private void splitContainer1_Panel1_MouseMove(object sender, MouseEventArgs e)
        {
            int xcoord = e.X - splitContainer1.Panel1.Width / 2;
            int ycoord = (splitContainer1.Panel1.Height - e.Y) - splitContainer1.Panel1.Height / 2;
            toolStripStatusLabel1.Text = "(" + e.X + "," + e.Y + ") | (" + xcoord + "," + ycoord + ")";
            Graphics mainScreen = splitContainer2.Panel2.CreateGraphics();
            Graphics g = splitContainer1.Panel1.CreateGraphics();


            float alpha = 0.5f * (float)splitContainer1.Panel1.Width - 0.5f;
            float beta = 0.5f * (float)splitContainer1.Panel1.Height - 0.5f;
            int x2, x1, y1, y2;
            float xper, yper, d;
            if (e.Button == MouseButtons.Left && cube != null)
            {
                containerControl1_Paint(null, null);
                if (tsbCube.Checked)
                {
                    if (listObjects.Count > numOfObjects)
                    {
                        listObjects.RemoveLast();
                    }
                    p.Color = Color.Black;
                    #region cube                    
                    //d = splitContainer1.Panel1.Width / 2f;

                    xper = (e.X - splitContainer1.Panel1.Width / 2f) / (splitContainer1.Panel1.Width / 2f);
                    x1 = (int)(xper * (-camFront.pos.Z));///d);
                    xper = (x - splitContainer1.Panel1.Width / 2f) / (splitContainer1.Panel1.Width / 2f);
                    x2 = (int)(xper * (-camFront.pos.Z));///d));

                    if (x2 > x1)
                        cube.width = (x2 - x1);
                    else
                        cube.width = (x1 - x2);
                    //float ar = (float)splitContainer1.Panel1.Width/(float)splitContainer1.Panel1.Height;
                    yper = (e.Y - splitContainer1.Panel1.Height / 2f) / (splitContainer1.Panel1.Height / 2f);
                    y1 = (int)(yper * (-camFront.pos.Z));///(d*ar));
                    yper = (y - splitContainer1.Panel1.Height / 2f) / (splitContainer1.Panel1.Height / 2f);
                    y2 = (int)(yper * (-camFront.pos.Z));///(d*ar));

                    if (y2 > y1)
                        cube.height = Math.Abs(y2 - y1);
                    else
                        cube.height = Math.Abs(y1 - y2);

                    cube.world_pos.X = ((x1 + x2) / 2);
                    cube.world_pos.Y = -((y1 + y2) / 2);
                    cube.world_pos.Z = (cube.length / 2);

                    #endregion
                    #region local coordinates
                    cube.vlist_local[0].X = -cube.width / 2;
                    cube.vlist_local[0].Y = cube.height / 2;
                    cube.vlist_local[0].Z = -cube.length / 2;
                    cube.vlist_local[1].X = cube.width / 2;
                    cube.vlist_local[1].Y = cube.height / 2;
                    cube.vlist_local[1].Z = -cube.length / 2;
                    cube.vlist_local[2].X = cube.width / 2;
                    cube.vlist_local[2].Y = -cube.height / 2;
                    cube.vlist_local[2].Z = -cube.length / 2;
                    cube.vlist_local[3].X = -cube.width / 2;
                    cube.vlist_local[3].Y = -cube.height / 2;
                    cube.vlist_local[3].Z = -cube.length / 2;
                    cube.vlist_local[4].X = -cube.width / 2;
                    cube.vlist_local[4].Y = cube.height / 2;
                    cube.vlist_local[4].Z = cube.length;
                    cube.vlist_local[5].X = cube.width / 2;
                    cube.vlist_local[5].Y = cube.height / 2;
                    cube.vlist_local[5].Z = cube.length;
                    cube.vlist_local[6].X = cube.width / 2;
                    cube.vlist_local[6].Y = -cube.height / 2;
                    cube.vlist_local[6].Z = cube.length;
                    cube.vlist_local[7].X = -cube.width / 2;
                    cube.vlist_local[7].Y = -cube.height / 2;
                    cube.vlist_local[7].Z = cube.length;
                    #endregion

                    cube.num_polys = 6;
                    cube.plist[0] = new POLY4DV1();
                    cube.plist[0].poly_num_verts = 4;
                    cube.plist[0].vert = new int[4];
                    cube.plist[0].vert[0] = 0;
                    cube.plist[0].vert[1] = 1;
                    cube.plist[0].vert[2] = 2;
                    cube.plist[0].vert[3] = 3;

                    cube.plist[1] = new POLY4DV1();
                    cube.plist[1].poly_num_verts = 4;
                    cube.plist[1].vert = new int[4];
                    cube.plist[1].vert[0] = 4;
                    cube.plist[1].vert[1] = 5;
                    cube.plist[1].vert[2] = 6;
                    cube.plist[1].vert[3] = 7;

                    cube.plist[2] = new POLY4DV1();
                    cube.plist[2].poly_num_verts = 4;
                    cube.plist[2].vert = new int[4];
                    cube.plist[2].vert[0] = 0;
                    cube.plist[2].vert[1] = 3;
                    cube.plist[2].vert[2] = 7;
                    cube.plist[2].vert[3] = 4;

                    cube.plist[3] = new POLY4DV1();
                    cube.plist[3].poly_num_verts = 4;
                    cube.plist[3].vert = new int[4];
                    cube.plist[3].vert[0] = 1;
                    cube.plist[3].vert[1] = 2;
                    cube.plist[3].vert[2] = 6;
                    cube.plist[3].vert[3] = 5;

                    cube.plist[4] = new POLY4DV1();
                    cube.plist[4].poly_num_verts = 4;
                    cube.plist[4].vert = new int[4];
                    cube.plist[4].vert[0] = 0;
                    cube.plist[4].vert[1] = 1;
                    cube.plist[4].vert[2] = 5;
                    cube.plist[4].vert[3] = 4;

                    cube.plist[5] = new POLY4DV1();
                    cube.plist[5].poly_num_verts = 4;
                    cube.plist[5].vert = new int[4];
                    cube.plist[5].vert[0] = 2;
                    cube.plist[5].vert[1] = 3;
                    cube.plist[5].vert[2] = 7;
                    cube.plist[5].vert[3] = 6;

                    listObjects.AddLast(cube);
                }
                else if (tsbSelect.Checked)
                {
                    p.Color = Color.Yellow;
                    g.DrawLine(p, x, y, e.X, y);
                    g.DrawLine(p, e.X, y, e.X, e.Y);
                    g.DrawLine(p, e.X, e.Y, x, e.Y);
                    g.DrawLine(p, x, e.Y, x, y);
                }
                else if (tsbMove.Checked)
                {
                    for (int i = 0; i < treeView1.SelectedNodes.Count; i++)
                    {
                        TreeNode node = treeView1.SelectedNodes[i] as TreeNode;
                        foreach (OBJECT4DV1 obj in listObjects)
                        {
                            if (node.Index == obj.id)
                            {
                                obj.world_pos.X += e.X - x;
                                obj.world_pos.Y -= e.Y - y;
                                for (int v = 0; v < obj.num_vertices; v++)
                                {
                                    obj.vlist_trans[v].X = obj.world_pos.X + obj.vlist_local[v].X;
                                    obj.vlist_trans[v].Y = obj.world_pos.Y + obj.vlist_local[v].Y;
                                }
                                updateProperties(obj.name);
                            }
                        }
                    }
                    x = e.X;
                    y = e.Y;
                }
                else if (tsbScale.Checked)
                {
                    for (int i = 0; i < treeView1.SelectedNodes.Count; i++)
                    {
                        TreeNode node = treeView1.SelectedNodes[i] as TreeNode;

                        foreach (OBJECT4DV1 obj in listObjects)
                        {
                            if (node.Index == obj.id)
                            {
                                obj.scale.X = obj.scale.X + ((e.X - x) / z);
                                obj.scale.Y = obj.scale.Y + ((e.Y - y) / z);
                                break;
                            }
                        }
                    }
                    x = e.X;
                    y = e.Y;
                }
                else if (tsbRotate.Checked)
                {
                    for (int i = 0; i < treeView1.SelectedNodes.Count; i++)
                    {
                        foreach (OBJECT4DV1 obj in listObjects)
                        {
                            TreeNode node = treeView1.SelectedNodes[i] as TreeNode;
                            if (node.Index == obj.id)
                            {
                                float rad_angle;
                                rad_angle = (e.X - x) * 3.14f / 180.0f;
                                obj.dir.Y += rad_angle;
                                rad_angle = (e.Y - y) * 3.14f / 180.0f;
                                obj.dir.X += rad_angle;

                            }
                        }
                    }
                    x = e.X;
                    y = e.Y;
                }
            }

            toolStripStatusLabel1.Text = "(" + e.X + ", " + e.Y + ", " + 0 + ")";//toolStripStatusLabel1.Text = "(" + camFront.pos.X + ", " + camFront.pos.Y + ", " + camFront.pos.Z + ")";
            toolStripStatusLabel2.Text = "(" + camFront.dir.X + ", " + camFront.dir.Y + ", " + camFront.dir.Z + ")";
            toolStripStatusLabel3.Text = camFront.dir.X * 180 / Math.PI + ", " + camFront.dir.Y * 180 / Math.PI + ", " + camFront.dir.Z * 180 / Math.PI;
        }

        private void splitContainer2_Panel2_MouseMove(object sender, MouseEventArgs e)
        {
            const float one_degree = 5.0f * (float)Math.PI / 180f; // in radians
            if (isMouseDown)
            {
                if (e.Y > y)
                    camMain.dir.X += one_degree;
                else if (e.Y < y)
                    camMain.dir.X -= one_degree;

                if (e.X < x)
                    camMain.dir.Y += one_degree;
                else if (e.X > x)
                    camMain.dir.Y -= one_degree;

                y = e.Y;
                x = e.X;
            }
            toolStripStatusLabel1.Text = "(" + camMain.pos.X + ", " + camMain.pos.Y + ", " + camMain.pos.Z + ")";
            toolStripStatusLabel2.Text = "(" + camMain.dir.X + ", " + camMain.dir.Y + ", " + camMain.dir.Z + ")";
            toolStripStatusLabel3.Text = camMain.dir.X * 180 / Math.PI + ", " + camMain.dir.Y * 180 / Math.PI + ", " + camMain.dir.Z * 180 / Math.PI;
            containerControl1_Paint(null, null);
        }

        private void moveSideways(float moveDist)
        {
            if (moveDist > 0)
            {
                camMain.pos.X += moveDist * (float)Math.Cos((camMain.dir.Y));
                camMain.pos.Z += moveDist * (float)Math.Sin((camMain.dir.Y));
            }
            else
            {
                moveDist = -moveDist;
                camMain.pos.X += moveDist * (float)Math.Cos((camMain.dir.Y + 3.14f));
                camMain.pos.Z += moveDist * (float)Math.Sin((camMain.dir.Y + 3.14f));
            }
        }

        private void moveForward(Single amount)
        {
            if (amount > 0)
            {
                camMain.pos.Z += amount * (float)Math.Cos((float)camMain.dir.X) * (float)Math.Cos(camMain.dir.Y);
                camMain.pos.X += amount * (float)Math.Cos((float)camMain.dir.X) * (float)Math.Sin(camMain.dir.Y);
                camMain.pos.Y += amount * (float)Math.Sin((float)camMain.dir.X);
            }
            else
            {
                camMain.pos.Z += -amount * (float)Math.Cos((float)camMain.dir.X) * (float)Math.Cos(camMain.dir.Y + 3.14);
                camMain.pos.X += -amount * (float)Math.Cos((float)camMain.dir.X) * (float)Math.Sin(camMain.dir.Y + 3.14);
                camMain.pos.Y += -amount * (float)Math.Sin((float)camMain.dir.X + 3.14);
            }
            splitContainer2_Panel2_Paint(null, null);
        }

        private void refreshDisplay()
        {
            splitContainer1_Panel1_Paint(null, null);
            splitContainer1_Panel2_Paint(null, null);
            splitContainer2_Panel1_Paint(null, null);
            splitContainer2_Panel2_Paint(null, null);

        }

        private void splitContainer2_Panel2_MouseWheel(object sender, MouseEventArgs e)
        {
            Debug.Print("" + (e.Delta >> 4));
            moveForward(e.Delta >> 4);
        }

        private void splitContainer1_Panel2_MouseWheel(object sender, MouseEventArgs e)
        {
            int x2, x1, y1, y2;
            float xper, yper;
            if (isMouseDown)
            {
                if (tsbCube.Checked)
                {
                    if (listObjects.Count > numOfObjects)
                    {
                        listObjects.RemoveLast();
                    }
                    p.Color = Color.Black;
                }
                if ((cube.width + (e.Delta >> 4)) > 0)
                    cube.width += e.Delta >> 4;
                else
                    cube.width = 1;

                if (tsbCube.Checked)
                {
                    if (listObjects.Count > numOfObjects)
                    {
                        listObjects.RemoveLast();
                    }
                    p.Color = Color.Black;
                    #region cube
                    xper = (e.X - splitContainer1.Panel2.Width / 2f) / (splitContainer1.Panel2.Width / 2f);
                    x1 = (int)(xper * (-camLeft.pos.X));
                    xper = (x - splitContainer1.Panel2.Width / 2f) / (splitContainer1.Panel2.Width / 2f);
                    x2 = (int)(xper * (-camLeft.pos.X));

                    if (x2 > x1)
                        cube.length = (x2 - x1);
                    else
                        cube.length = (x1 - x2);

                    yper = (e.Y - splitContainer2.Panel1.Height / 2f) / (splitContainer2.Panel1.Height / 2f);
                    y1 = (int)(yper * (-camLeft.pos.X));
                    yper = (y - splitContainer2.Panel1.Height / 2f) / (splitContainer2.Panel1.Height / 2f);
                    y2 = (int)(yper * (-camLeft.pos.X));

                    if (y2 > y1)
                        cube.height = Math.Abs(y2 - y1);
                    else
                        cube.height = Math.Abs(y1 - y2);

                    cube.world_pos.X = cube.width / 2;
                    cube.world_pos.Y = -((y1 + y2) / 2);
                    cube.world_pos.Z = -((x1 + x2) / 2);

                    #endregion
                    #region local coordinates
                    cube.vlist_local[0].X = -cube.width / 2;
                    cube.vlist_local[0].Y = cube.height / 2;
                    cube.vlist_local[0].Z = -cube.length / 2;
                    cube.vlist_local[1].X = cube.width / 2;
                    cube.vlist_local[1].Y = cube.height / 2;
                    cube.vlist_local[1].Z = -cube.length / 2;
                    cube.vlist_local[2].X = cube.width / 2;
                    cube.vlist_local[2].Y = -cube.height / 2;
                    cube.vlist_local[2].Z = -cube.length / 2;
                    cube.vlist_local[3].X = -cube.width / 2;
                    cube.vlist_local[3].Y = -cube.height / 2;
                    cube.vlist_local[3].Z = -cube.length / 2;
                    cube.vlist_local[4].X = -cube.width / 2;
                    cube.vlist_local[4].Y = cube.height / 2;
                    cube.vlist_local[4].Z = cube.length / 2;
                    cube.vlist_local[5].X = cube.width / 2;
                    cube.vlist_local[5].Y = cube.height / 2;
                    cube.vlist_local[5].Z = cube.length / 2;
                    cube.vlist_local[6].X = cube.width / 2;
                    cube.vlist_local[6].Y = -cube.height / 2;
                    cube.vlist_local[6].Z = cube.length / 2;
                    cube.vlist_local[7].X = -cube.width / 2;
                    cube.vlist_local[7].Y = -cube.height / 2;
                    cube.vlist_local[7].Z = cube.length / 2;
                    #endregion
                    listObjects.AddLast(cube);
                }
            }
            else
            {
                camLeft.pos.X += e.Delta >> 4;
            }
            containerControl1_Paint(null, null);
        }

        private void splitContainer2_Panel1_MouseWheel(object sender, MouseEventArgs e)
        {
            int x2, x1, y1, y2;
            float xper, yper;
            if (isMouseDown)
            {
                if (tsbCube.Checked)
                {
                    if (listObjects.Count > numOfObjects)
                    {
                        listObjects.RemoveLast();
                    }
                    p.Color = Color.Black;
                }
                if ((cube.height + (e.Delta >> 4)) > 0)
                    cube.height += e.Delta >> 4;
                else
                    cube.height = 1;

                if (tsbCube.Checked)
                {
                    if (listObjects.Count > numOfObjects)
                    {
                        listObjects.RemoveLast();
                    }
                    p.Color = Color.Black;
                    #region cube
                    xper = (e.X - splitContainer2.Panel1.Width / 2f) / (splitContainer2.Panel1.Width / 2f);
                    x1 = (int)(xper * (-camTop.pos.Y));
                    xper = (x - splitContainer2.Panel1.Width / 2f) / (splitContainer2.Panel1.Width / 2f);
                    x2 = (int)(xper * (-camTop.pos.Y));

                    if (x2 > x1)
                        cube.width = (x2 - x1);
                    else
                        cube.width = (x1 - x2);

                    yper = (e.Y - splitContainer2.Panel1.Height / 2f) / (splitContainer2.Panel1.Height / 2f);
                    y1 = (int)(yper * (-camTop.pos.Y));
                    yper = (y - splitContainer2.Panel1.Height / 2f) / (splitContainer2.Panel1.Height / 2f);
                    y2 = (int)(yper * (-camTop.pos.Y));

                    if (y2 > y1)
                        cube.length = Math.Abs(y2 - y1);
                    else
                        cube.length = Math.Abs(y1 - y2);

                    cube.world_pos.X = ((x1 + x2) / 2);
                    cube.world_pos.Y = -cube.height / 2;
                    cube.world_pos.Z = -((y1 + y2) / 2);

                    #endregion
                    #region local coordinates
                    cube.vlist_local[0].X = -cube.width / 2;
                    cube.vlist_local[0].Y = cube.height / 2;
                    cube.vlist_local[0].Z = -cube.length / 2;
                    cube.vlist_local[1].X = cube.width / 2;
                    cube.vlist_local[1].Y = cube.height / 2;
                    cube.vlist_local[1].Z = -cube.length / 2;
                    cube.vlist_local[2].X = cube.width / 2;
                    cube.vlist_local[2].Y = -cube.height / 2;
                    cube.vlist_local[2].Z = -cube.length / 2;
                    cube.vlist_local[3].X = -cube.width / 2;
                    cube.vlist_local[3].Y = -cube.height / 2;
                    cube.vlist_local[3].Z = -cube.length / 2;
                    cube.vlist_local[4].X = -cube.width / 2;
                    cube.vlist_local[4].Y = cube.height / 2;
                    cube.vlist_local[4].Z = cube.length / 2;
                    cube.vlist_local[5].X = cube.width / 2;
                    cube.vlist_local[5].Y = cube.height / 2;
                    cube.vlist_local[5].Z = cube.length / 2;
                    cube.vlist_local[6].X = cube.width / 2;
                    cube.vlist_local[6].Y = -cube.height / 2;
                    cube.vlist_local[6].Z = cube.length / 2;
                    cube.vlist_local[7].X = -cube.width / 2;
                    cube.vlist_local[7].Y = -cube.height / 2;
                    cube.vlist_local[7].Z = cube.length / 2;
                    #endregion
                    listObjects.AddLast(cube);
                }
            }
            else
            {
                camTop.pos.Y += e.Delta >> 4;
            }
            containerControl1_Paint(null, null);

        }

        private void splitContainer1_Panel1_MouseUp(object sender, MouseEventArgs e)
        {
            int h = splitContainer1.Panel1.Height;
            if (tsbCube.Checked)
            {
                if (listObjects.Count > 0)
                {
                    if (listObjects.Last.Value is Cube)
                    {
                        listObjects.RemoveLast();
                        cube.id = listObjects.Count;
                        listObjects.AddLast(cube);
                        //numOfObjects++;
                        UpdateTree();
                    }
                }
                treeView1.SelectedNodes.RemoveRange(0, treeView1.SelectedNodes.Count);
            }
            else if (tsbSelect.Checked)
            {
                treeView1.SelectedNodes.RemoveRange(0, treeView1.SelectedNodes.Count);
                foreach (OBJECT4DV1 obj in listObjects)
                {
                    float alpha = 0.5f * (float)splitContainer1.Panel1.Width - 0.5f;
                    float beta = 0.5f * (float)splitContainer1.Panel1.Height - 0.5f;
                    Point pt = new Point();
                    Point4D pt_per = new Point4D();
                    pt_per.X = obj.world_pos.X / -camFront.pos.Z;
                    pt_per.Y = obj.world_pos.Y / -camFront.pos.Z;
                    pt.X = (int)(alpha + pt_per.X * alpha);
                    pt.Y = h - (int)(beta + pt_per.Y * beta);
                    if (e.X > x && e.Y > y)
                    {
                        if (pt.X < e.X && pt.X > x && pt.Y < e.Y && pt.Y > y)
                        {
                            TreeNode[] nodes = treeView1.Nodes.Find(obj.id.ToString(), true);
                            treeView1.SelectedNodes.Add(nodes[0]);
                        }
                        else
                        {
                            treeView1.SelectedNodes.Remove(obj.id);
                        }
                    }
                    else if (e.X < x && e.Y > y)
                    {
                        if (pt.X > e.X && pt.X < x && pt.Y < e.Y && pt.Y > y)
                        {
                            TreeNode[] nodes = treeView1.Nodes.Find(obj.id.ToString(), true);
                            treeView1.SelectedNodes.Add(nodes[0]);
                        }
                        else
                        {
                            treeView1.SelectedNodes.Remove(obj.id);
                        }
                    }
                    else if (e.X < x && e.Y < y)
                    {
                        if (pt.X > e.X && pt.X < x && pt.Y > e.Y && pt.Y < y)
                        {
                            TreeNode[] nodes = treeView1.Nodes.Find(obj.id.ToString(), true);
                            treeView1.SelectedNodes.Add(nodes[0]);
                        }
                        else
                        {
                            treeView1.SelectedNodes.Remove(obj.id);
                        }
                    }
                    else if (e.X > x && e.Y < y)
                    {
                        if (pt.X < e.X && pt.X > x && pt.Y > e.Y && pt.Y < y)
                        {
                            TreeNode[] nodes = treeView1.Nodes.Find(obj.id.ToString(), true);
                            treeView1.SelectedNodes.Add(nodes[0]);
                        }
                        else
                        {
                            treeView1.SelectedNodes.Remove(obj.id);
                        }
                    }
                }
                //treeView1.paintSelectedNodes();
            }
            refreshDisplay();
            isMouseDown = false;
        }

        // top left panel with front view
        private void splitContainer1_Panel1_Paint(object sender, PaintEventArgs e)
        {
            Graphics g = splitContainer1.Panel1.CreateGraphics();
            int h = splitContainer1.Panel1.Height;
            int w = splitContainer1.Panel1.Width;
            int x1, y1, x2, y2;
            g.Clear(splitContainer1.Panel1.BackColor);
            foreach (OBJECT4DV1 obj in listObjects)
            {
                p.Color = Color.Black;
                if (treeView1.SelectedNodes.Count > 0)
                {
                    for (int i = 0; i < treeView1.SelectedNodes.Count; i++)
                    {
                        TreeNode node = treeView1.SelectedNodes[i] as TreeNode;
                        if (node.Index == obj.id)
                            p.Color = Color.Red;
                    }
                }
                #region convert from world to camera coordinates
                Matrix Tcam_inv = Matrix.Identity, Mtemp1, Mtemp2;
                Tcam_inv.M41 = -camFront.pos.X;
                Tcam_inv.M42 = -camFront.pos.Y;
                Tcam_inv.M43 = -camFront.pos.Z;
                Tcam_inv.M44 = 1;

                Mtemp1 = Matrix.Multiply(Tcam_inv, Matrix.RotationY(camFront.dir.Y));
                Mtemp2 = Matrix.Multiply(Matrix.RotationX(camFront.dir.X),
                                                      Matrix.RotationZ(camFront.dir.Z));
                Tcam_inv = Matrix.Multiply(Mtemp1, Mtemp2);
                Matrix[] cube_camera = new Matrix[obj.num_vertices];
                Matrix[] cube_world = new Matrix[obj.num_vertices];
                Matrix[] cube_rotate = new Matrix[obj.num_vertices];
                Matrix[] cube_rotation = new Matrix[obj.num_vertices];

                Matrix Mrotation;
                Mrotation = Matrix.RotationYawPitchRoll(obj.dir.Y, obj.dir.X, obj.dir.Z);

                for (int i = 0; i < obj.num_vertices; i++)
                {
                    cube_rotate[i] = Matrix.Zero;
                    cube_rotate[i].M11 = obj.vlist_local[i].X * obj.scale.X;
                    cube_rotate[i].M12 = obj.vlist_local[i].Y * obj.scale.Y;
                    cube_rotate[i].M13 = obj.vlist_local[i].Z * obj.scale.Z;
                    cube_rotate[i].M14 = obj.vlist_local[i].W;
                    cube_rotation[i] = Matrix.Multiply(cube_rotate[i], Mrotation);
                }

                for (int i = 0; i < obj.num_vertices; i++)
                {
                    cube_world[i] = Matrix.Zero;
                    cube_world[i].M11 = obj.world_pos.X + cube_rotation[i].M11;
                    cube_world[i].M12 = obj.world_pos.Y + cube_rotation[i].M12;
                    cube_world[i].M13 = obj.world_pos.Z + cube_rotation[i].M13;
                    cube_world[i].M14 = 1;
                    cube_camera[i] = Matrix.Multiply(cube_world[i], Tcam_inv);
                }
                #endregion

                #region perspective
                int d = 1;// splitContainer1.Panel1.Width / 2;
                //float ar =(float) splitContainer1.Panel1.Width / (float)splitContainer1.Panel1.Height;
                Point4D[] cube_per = new Point4D[obj.num_vertices];
                Single z_nearest = Single.MaxValue, z_farthest = Single.MinValue;
                for (int vertex = 0; vertex < obj.num_vertices; vertex++)
                {
                    cube_per[vertex].X = d * cube_camera[vertex].M11 / cube_camera[vertex].M13;
                    cube_per[vertex].Y = d * cube_camera[vertex].M12 / cube_camera[vertex].M13;
                    if (cube_camera[vertex].M13 < z_nearest)
                        z_nearest = cube_camera[vertex].M13;
                    if (cube_camera[vertex].M13 > z_farthest)
                        z_farthest = cube_camera[vertex].M13;
                }
                #endregion

                #region image space clipping

                if (z_nearest < camFront.pos.Z + 50 || z_farthest > Single.MaxValue)
                    continue;
                #endregion

                #region screen
                float alpha = 0.5f * (float)splitContainer1.Panel1.Width - 0.5f;
                float beta = 0.5f * (float)splitContainer1.Panel1.Height - 0.5f;

                Point[] pt = new Point[obj.num_vertices];
                for (int vertex = 0; vertex < obj.num_vertices; vertex++)
                {
                    pt[vertex] = new Point();
                    pt[vertex].X = (int)(alpha + cube_per[vertex].X * alpha);
                    pt[vertex].Y = h - (int)(beta + cube_per[vertex].Y * beta);
                }

                for (int poly = 0; poly < obj.num_polys; poly++)
                {
                    for (int i = 0; i < obj.plist[poly].vert.Length; i++)
                    {
                        if (i == obj.plist[poly].vert.Length - 1)
                        {
                            x1 = pt[obj.plist[poly].vert[i]].X;
                            y1 = pt[obj.plist[poly].vert[i]].Y;
                            x2 = pt[obj.plist[poly].vert[0]].X;
                            y2 = pt[obj.plist[poly].vert[0]].Y;

                            if (x1 < 0)
                                x1 = 0;
                            else if (x1 > splitContainer1.Panel1.Width)
                                x1 = splitContainer1.Panel1.Width;
                            if (x2 < 0)
                                x2 = 0;
                            else if (x2 > splitContainer1.Panel1.Width)
                                x2 = splitContainer1.Panel1.Width;

                            if (y1 < 0)
                                y1 = 0;
                            else if (y1 > splitContainer1.Panel1.Height)
                                y1 = splitContainer1.Panel1.Height;
                            if (y2 < 0)
                                y2 = 0;
                            else if (y2 > splitContainer1.Panel1.Height)
                                y2 = splitContainer1.Panel1.Height;
                            GUI.GUI.DrawLine(g, p, x1, y1, x2, y2, splitContainer1.Panel1.Width, splitContainer1.Panel1.Height);
                        }
                        else
                        {
                            x1 = pt[obj.plist[poly].vert[i]].X;
                            y1 = pt[obj.plist[poly].vert[i]].Y;
                            x2 = pt[obj.plist[poly].vert[i + 1]].X;
                            y2 = pt[obj.plist[poly].vert[i + 1]].Y;

                            if (x1 < 0)
                                x1 = 0;
                            else if (x1 > splitContainer1.Panel1.Width)
                                x1 = splitContainer1.Panel1.Width;
                            if (x2 < 0)
                                x2 = 0;
                            else if (x2 > splitContainer1.Panel1.Width)
                                x2 = splitContainer1.Panel1.Width;

                            if (y1 < 0)
                                y1 = 0;
                            else if (y1 > splitContainer1.Panel1.Height)
                                y1 = splitContainer1.Panel1.Height;
                            if (y2 < 0)
                                y2 = 0;
                            else if (y2 > splitContainer1.Panel1.Height)
                                y2 = splitContainer1.Panel1.Height;

                            GUI.GUI.DrawLine(g, p, x1, y1, x2, y2, splitContainer1.Panel1.Width, splitContainer1.Panel1.Height);
                        }
                    }
                }

                #endregion

            }

        }

        private void containerControl1_Paint(object sender, PaintEventArgs e)
        {
            splitContainer2_Panel2_Paint(null, null);
            splitContainer1_Panel1_Paint(null, null);
            splitContainer2_Panel1_Paint(null, null);
            splitContainer1_Panel2_Paint(null, null);
        }

        // top right panel with top view
        private void splitContainer2_Panel1_Paint(object sender, PaintEventArgs e)
        {
            Graphics g = splitContainer2.Panel1.CreateGraphics();
            int h = splitContainer2.Panel1.Height;
            int w = splitContainer2.Panel1.Width;
            int x1, y1, x2, y2;
            LinkedList<Point> vertices;

            g.Clear(splitContainer2.Panel1.BackColor);
            foreach (OBJECT4DV1 obj in listObjects)
            {
                p.Color = Color.Black;
                if (treeView1.SelectedNodes.Count > 0)
                {
                    for (int i = 0; i < treeView1.SelectedNodes.Count; i++)
                    {
                        TreeNode node = treeView1.SelectedNodes[i] as TreeNode;
                        if (node.Index == obj.id)
                            p.Color = Color.Red;
                    }
                }
                #region convert from world to camera coordinates
                Matrix Tcam_inv = Matrix.Identity, Mtemp1, Mtemp2;
                Tcam_inv.M41 = -camTop.pos.X;
                Tcam_inv.M42 = -camTop.pos.Y;
                Tcam_inv.M43 = -camTop.pos.Z;
                Tcam_inv.M44 = 1;

                Mtemp1 = Matrix.Multiply(Tcam_inv, Matrix.RotationY(camTop.dir.Y));
                Mtemp2 = Matrix.Multiply(Matrix.RotationX(camTop.dir.X),
                                                      Matrix.RotationZ(camTop.dir.Z));
                Tcam_inv = Matrix.Multiply(Mtemp1, Mtemp2);
                Matrix[] cube_camera = new Matrix[obj.num_vertices];
                Matrix[] cube_world = new Matrix[obj.num_vertices];
                Matrix[] cube_rotate = new Matrix[obj.num_vertices];
                Matrix[] cube_rotation = new Matrix[obj.num_vertices];

                Matrix Mrotation;
                Mrotation = Matrix.RotationYawPitchRoll(obj.dir.Y, obj.dir.X, obj.dir.Z);
                for (int i = 0; i < obj.num_vertices; i++)
                {
                    cube_rotate[i] = Matrix.Zero;
                    cube_rotate[i].M11 = obj.vlist_local[i].X * obj.scale.X;
                    cube_rotate[i].M12 = obj.vlist_local[i].Y * obj.scale.Y;
                    cube_rotate[i].M13 = obj.vlist_local[i].Z * obj.scale.Z;
                    cube_rotate[i].M14 = obj.vlist_local[i].W;
                    cube_rotation[i] = Matrix.Multiply(cube_rotate[i], Mrotation);
                }

                for (int i = 0; i < obj.num_vertices; i++)
                {
                    cube_world[i] = Matrix.Zero;
                    cube_world[i].M11 = obj.world_pos.X + cube_rotation[i].M11;
                    cube_world[i].M12 = obj.world_pos.Y + cube_rotation[i].M12;
                    cube_world[i].M13 = obj.world_pos.Z + cube_rotation[i].M13;
                    cube_world[i].M14 = 1;
                    cube_camera[i] = Matrix.Multiply(cube_world[i], Tcam_inv);

                }
                #endregion

                #region perspective
                int d = 1;
                Point4D[] cube_per = new Point4D[obj.num_vertices];
                Single y_nearest = Single.MinValue, y_farthest = Single.MaxValue;
                for (int vertex = 0; vertex < obj.num_vertices; vertex++)
                {
                    cube_per[vertex].X = d * cube_camera[vertex].M11 / cube_camera[vertex].M12;
                    cube_per[vertex].Y = -d * cube_camera[vertex].M13 / cube_camera[vertex].M12;
                    if (cube_camera[vertex].M13 < y_farthest)
                        y_nearest = cube_camera[vertex].M12;
                    if (cube_camera[vertex].M13 > y_nearest)
                        y_farthest = cube_camera[vertex].M12;
                }
                #endregion                                                

                #region image space clipping

                if (y_nearest > camTop.pos.Y + 50 || y_farthest < Single.MinValue)
                    continue;
                #endregion

                #region screen
                float alpha = 0.5f * (float)splitContainer2.Panel1.Width - 0.5f;
                float beta = 0.5f * (float)splitContainer2.Panel1.Height - 0.5f;

                Point[] pt = new Point[obj.num_vertices];
                for (int vertex = 0; vertex < obj.num_vertices; vertex++)
                {
                    pt[vertex] = new Point();
                    pt[vertex].X = (int)(alpha + cube_per[vertex].X * alpha);
                    pt[vertex].Y = (int)(beta + cube_per[vertex].Y * beta);
                }
                for (int poly = 0; poly < obj.num_polys; poly++)
                {
                    for (int i = 0; i < obj.plist[poly].vert.Length; i++)
                    {
                        if (i == obj.plist[poly].vert.Length - 1)
                        {
                            x1 = pt[obj.plist[poly].vert[i]].X;
                            y1 = pt[obj.plist[poly].vert[i]].Y;
                            x2 = pt[obj.plist[poly].vert[0]].X;
                            y2 = pt[obj.plist[poly].vert[0]].Y;

                            if (x1 < 0)
                                x1 = 0;
                            else if (x1 > splitContainer2.Panel1.Width)
                                x1 = splitContainer2.Panel1.Width;
                            if (x2 < 0)
                                x2 = 0;
                            else if (x2 > splitContainer2.Panel1.Width)
                                x2 = splitContainer2.Panel1.Width;

                            if (y1 < 0)
                                y1 = 0;
                            else if (y1 > splitContainer2.Panel1.Height)
                                y1 = splitContainer2.Panel1.Height;
                            if (y2 < 0)
                                y2 = 0;
                            else if (y2 > splitContainer2.Panel1.Height)
                                y2 = splitContainer2.Panel1.Height;
                            GUI.GUI.DrawLine(g, p, x1, y1, x2, y2, splitContainer2.Panel1.Width, splitContainer2.Panel1.Height);
                        }
                        else
                        {
                            x1 = pt[obj.plist[poly].vert[i]].X;
                            y1 = pt[obj.plist[poly].vert[i]].Y;
                            x2 = pt[obj.plist[poly].vert[i + 1]].X;
                            y2 = pt[obj.plist[poly].vert[i + 1]].Y;

                            if (x1 < 0)
                                x1 = 0;
                            else if (x1 > splitContainer2.Panel1.Width)
                                x1 = splitContainer2.Panel1.Width;
                            if (x2 < 0)
                                x2 = 0;
                            else if (x2 > splitContainer2.Panel1.Width)
                                x2 = splitContainer2.Panel1.Width;

                            if (y1 < 0)
                                y1 = 0;
                            else if (y1 > splitContainer2.Panel1.Height)
                                y1 = splitContainer2.Panel1.Height;
                            if (y2 < 0)
                                y2 = 0;
                            else if (y2 > splitContainer2.Panel1.Height)
                                y2 = splitContainer2.Panel1.Height;
                            GUI.GUI.DrawLine(g, p, x1, y1, x2, y2, splitContainer2.Panel1.Width, splitContainer2.Panel1.Height);
                        }
                    }
                }


                #endregion

            }
        }

        private void splitContainer2_Panel2_MouseDown(object sender, MouseEventArgs e)
        {
            x = e.X;
            y = e.Y;
            isMouseDown = true;
        }


        private void splitContainer2_Panel2_Paint(object sender, PaintEventArgs e)
        {
            Graphics mainScreen = splitContainer2.Panel2.CreateGraphics();
            int h = splitContainer2.Panel2.Height;
            int w = splitContainer2.Panel2.Width;
            int x1, y1, x2, y2;
            LinkedList<Point> vertices;

            mainScreen.Clear(splitContainer2.Panel2.BackColor);

            foreach (OBJECT4DV1 obj in listObjects)
            {
                p.Color = Color.Black;
                if (treeView1.SelectedNodes.Count > 0)
                {
                    for (int i = 0; i < treeView1.SelectedNodes.Count; i++)
                    {
                        TreeNode node = treeView1.SelectedNodes[i] as TreeNode;
                        if (node.Index == obj.id)
                            p.Color = Color.Red;
                    }
                }
                #region convert from world to camera coordinates
                Matrix Tcam_inv = Matrix.Identity, Mtemp1, Mtemp2;
                Tcam_inv.M41 = -camMain.pos.X;
                Tcam_inv.M42 = -camMain.pos.Y;
                Tcam_inv.M43 = -camMain.pos.Z;
                Tcam_inv.M44 = 1;

                Mtemp1 = Matrix.Multiply(Tcam_inv, Matrix.RotationY(camMain.dir.Y));
                Mtemp2 = Matrix.Multiply(Matrix.RotationX(camMain.dir.X),
                                                      Matrix.RotationZ(camMain.dir.Z));
                Tcam_inv = Matrix.Multiply(Mtemp1, Mtemp2);

                Matrix[] cube_camera = new Matrix[obj.num_vertices];
                Matrix[] cube_world = new Matrix[obj.num_vertices];
                Matrix[] cube_rotate = new Matrix[obj.num_vertices];
                Matrix[] cube_rotation = new Matrix[obj.num_vertices];

                Matrix Mrotation = new Matrix();
                Mrotation = Matrix.RotationYawPitchRoll(obj.dir.Y, obj.dir.X, obj.dir.Z);
                for (int i = 0; i < obj.num_vertices; i++)
                {
                    cube_rotate[i] = Matrix.Zero;
                    cube_rotate[i].M11 = obj.vlist_local[i].X * obj.scale.X;
                    cube_rotate[i].M12 = obj.vlist_local[i].Y * obj.scale.Y;
                    cube_rotate[i].M13 = obj.vlist_local[i].Z * obj.scale.Z;
                    cube_rotate[i].M14 = obj.vlist_local[i].W;
                    cube_rotation[i] = Matrix.Multiply(cube_rotate[i], Mrotation);
                }

                for (int i = 0; i < obj.num_vertices; i++)
                {
                    cube_world[i] = Matrix.Zero;
                    cube_world[i].M11 = obj.world_pos.X + cube_rotation[i].M11;
                    cube_world[i].M12 = obj.world_pos.Y + cube_rotation[i].M12;
                    cube_world[i].M13 = obj.world_pos.Z + cube_rotation[i].M13;
                    cube_world[i].M14 = 1;
                    cube_camera[i] = Matrix.Multiply(cube_world[i], Tcam_inv);

                }
                #endregion

                #region perspective
                int d = 1;
                Point4D[] cube_per = new Point4D[obj.num_vertices];
                for (int vertex = 0; vertex < obj.num_vertices; vertex++)
                {
                    cube_per[vertex].X = d * cube_camera[vertex].M11 / cube_camera[vertex].M13;
                    cube_per[vertex].Y = d * cube_camera[vertex].M12 / cube_camera[vertex].M13;
                }
                #endregion

                #region screen
                float alpha = 0.5f * (float)splitContainer2.Panel2.Width - 0.5f;
                float beta = 0.5f * (float)splitContainer2.Panel2.Height - 0.5f;

                Point[] pt = new Point[obj.num_vertices];
                for (int vertex = 0; vertex < obj.num_vertices; vertex++)
                {
                    pt[vertex] = new Point();
                    pt[vertex].X = (int)(alpha + cube_per[vertex].X * alpha);
                    pt[vertex].Y = h - (int)(beta + cube_per[vertex].Y * beta);
                }

                for (int poly = 0; poly < obj.num_polys; poly++)
                {
                    for (int i = 0; i < obj.plist[poly].vert.Length; i++)
                    {
                        if (i == obj.plist[poly].vert.Length - 1)
                        {
                            x1 = pt[obj.plist[poly].vert[i]].X;
                            y1 = pt[obj.plist[poly].vert[i]].Y;
                            x2 = pt[obj.plist[poly].vert[0]].X;
                            y2 = pt[obj.plist[poly].vert[0]].Y;

                            if (x1 < 0)
                                x1 = 0;
                            else if (x1 > splitContainer2.Panel2.Width)
                                x1 = splitContainer2.Panel2.Width;
                            if (x2 < 0)
                                x2 = 0;
                            else if (x2 > splitContainer2.Panel2.Width)
                                x2 = splitContainer2.Panel2.Width;

                            if (y1 < 0)
                                y1 = 0;
                            else if (y1 > splitContainer2.Panel2.Height)
                                y1 = splitContainer2.Panel2.Height;
                            if (y2 < 0)
                                y2 = 0;
                            GUI.GUI.DrawLine(mainScreen, p, x1, y1, x2, y2, splitContainer2.Panel2.Width, splitContainer1.Panel2.Height);
                        }
                        else
                        {
                            x1 = pt[obj.plist[poly].vert[i]].X;
                            y1 = pt[obj.plist[poly].vert[i]].Y;
                            x2 = pt[obj.plist[poly].vert[i + 1]].X;
                            y2 = pt[obj.plist[poly].vert[i + 1]].Y;

                            if (x1 < 0)
                                x1 = 0;
                            else if (x1 > splitContainer1.Panel1.Width)
                                x1 = splitContainer2.Panel2.Width;
                            if (x2 < 0)
                                x2 = 0;
                            else if (x2 > splitContainer1.Panel1.Width)
                                x2 = splitContainer2.Panel2.Width;

                            if (y1 < 0)
                                y1 = 0;
                            else if (y1 > splitContainer2.Panel2.Height)
                                y1 = splitContainer2.Panel2.Height;
                            if (y2 < 0)
                                y2 = 0;
                            else if (y2 > splitContainer2.Panel2.Height)
                                y2 = splitContainer2.Panel2.Height;
                            GUI.GUI.DrawLine(mainScreen, p, x1, y1, x2, y2, splitContainer2.Panel2.Width, splitContainer1.Panel2.Height);
                        }
                    }
                }

                #endregion
            }
        }

        private void splitContainer2_Panel2_MouseUp(object sender, MouseEventArgs e)
        {
            isMouseDown = false;
        }

        private void splitContainer2_Panel2_MouseHover(object sender, EventArgs e)
        {
            //this.Focus();            

        }

        private void splitContainer2_Panel2_MouseEnter(object sender, EventArgs e)
        {
            splitContainer2.Panel2.Focus();

        }

        private void splitContainer2_Panel2_MouseLeave(object sender, EventArgs e)
        {
            this.ActiveControl = null;
        }

        private void splitContainer1_Panel1_MouseEnter(object sender, EventArgs e)
        {
            splitContainer1.Panel1.Focus();
        }

        private void newToolStripMenuItem_Click(object sender, EventArgs e)
        {
            listObjects.Clear();
            numOfObjects = listObjects.Count;
            UpdateTree();
            containerControl1_Paint(null, null);
        }

        private void splitContainer2_Panel2_Enter(object sender, EventArgs e)
        {

        }

        private void splitContainer1_Panel2_Paint(object sender, PaintEventArgs e)
        {
            Graphics g = splitContainer1.Panel2.CreateGraphics();
            LinkedList<Point> vertices;
            int h = splitContainer1.Panel2.Height;
            int x1, y1, x2, y2;
            g.Clear(splitContainer1.Panel2.BackColor);

            foreach (OBJECT4DV1 obj in listObjects)
            {
                p.Color = Color.Black;
                if (treeView1.SelectedNodes.Count > 0)
                {
                    for (int i = 0; i < treeView1.SelectedNodes.Count; i++)
                    {
                        TreeNode node = treeView1.SelectedNodes[i] as TreeNode;
                        if (node.Index == obj.id)
                            p.Color = Color.Red;
                    }
                }

                #region convert from world to camera coordinates
                Matrix Tcam_inv = Matrix.Identity, Mtemp1, Mtemp2;
                Tcam_inv.M41 = -camLeft.pos.X;
                Tcam_inv.M42 = -camLeft.pos.Y;
                Tcam_inv.M43 = -camLeft.pos.Z;
                Tcam_inv.M44 = 1;

                Mtemp1 = Matrix.Multiply(Tcam_inv, Matrix.RotationY(camLeft.dir.Y));
                Mtemp2 = Matrix.Multiply(Matrix.RotationX(camLeft.dir.X),
                                                      Matrix.RotationZ(camLeft.dir.Z));
                Tcam_inv = Matrix.Multiply(Mtemp1, Mtemp2);
                Matrix[] cube_camera = new Matrix[obj.num_vertices];
                Matrix[] cube_world = new Matrix[obj.num_vertices];
                Matrix[] cube_rotate = new Matrix[obj.num_vertices];
                Matrix[] cube_rotation = new Matrix[obj.num_vertices];

                Matrix Mrotation;
                Mrotation = Matrix.RotationYawPitchRoll(obj.dir.Y, obj.dir.X, obj.dir.Z);
                for (int i = 0; i < obj.num_vertices; i++)
                {
                    cube_rotate[i] = Matrix.Zero;
                    cube_rotate[i].M11 = obj.vlist_local[i].X * obj.scale.X;
                    cube_rotate[i].M12 = obj.vlist_local[i].Y * obj.scale.Y;
                    cube_rotate[i].M13 = obj.vlist_local[i].Z * obj.scale.Z;
                    cube_rotate[i].M14 = obj.vlist_local[i].W;
                    cube_rotation[i] = Matrix.Multiply(cube_rotate[i], Mrotation);
                }

                for (int i = 0; i < obj.num_vertices; i++)
                {
                    cube_world[i] = Matrix.Zero;
                    cube_world[i].M11 = obj.world_pos.X + cube_rotation[i].M11;
                    cube_world[i].M12 = obj.world_pos.Y + cube_rotation[i].M12;
                    cube_world[i].M13 = obj.world_pos.Z + cube_rotation[i].M13;
                    cube_world[i].M14 = 1;
                    cube_camera[i] = Matrix.Multiply(cube_world[i], Tcam_inv);
                }

                #endregion

                #region perspective
                int d = 1;
                Point4D[] cube_per = new Point4D[obj.num_vertices];
                Single x_nearest = Single.MaxValue, x_farthest = Single.MinValue;
                for (int vertex = 0; vertex < obj.num_vertices; vertex++)
                {
                    cube_per[vertex].X = -d * cube_camera[vertex].M13 / cube_camera[vertex].M11;
                    cube_per[vertex].Y = -d * cube_camera[vertex].M12 / cube_camera[vertex].M11;
                    if (cube_camera[vertex].M13 < x_nearest)
                        x_nearest = cube_camera[vertex].M11;
                    if (cube_camera[vertex].M13 > x_farthest)
                        x_farthest = cube_camera[vertex].M11;
                }
                #endregion                

                #region image space clipping

                if (x_nearest < camLeft.pos.X + 50 || x_farthest > Single.MaxValue)
                    continue;
                #endregion

                #region screen
                float alpha = 0.5f * (float)splitContainer1.Panel2.Width - 0.5f;
                float beta = 0.5f * (float)splitContainer1.Panel2.Height - 0.5f;

                Point[] pt = new Point[obj.num_vertices];
                for (int vertex = 0; vertex < obj.num_vertices; vertex++)
                {
                    pt[vertex] = new Point();
                    pt[vertex].X = (int)(alpha + cube_per[vertex].X * alpha);
                    pt[vertex].Y = (int)(beta + cube_per[vertex].Y * beta);
                }
                for (int poly = 0; poly < obj.num_polys; poly++)
                {
                    for (int i = 0; i < obj.plist[poly].vert.Length; i++)
                    {
                        if (i == obj.plist[poly].vert.Length - 1)
                        {
                            x1 = pt[obj.plist[poly].vert[i]].X;
                            y1 = pt[obj.plist[poly].vert[i]].Y;
                            x2 = pt[obj.plist[poly].vert[0]].X;
                            y2 = pt[obj.plist[poly].vert[0]].Y;

                            if (x1 < 0)
                                x1 = 0;
                            else if (x1 > splitContainer1.Panel1.Width)
                                x1 = splitContainer1.Panel1.Width;
                            if (x2 < 0)
                                x2 = 0;
                            else if (x2 > splitContainer1.Panel1.Width)
                                x2 = splitContainer1.Panel1.Width;

                            if (y1 < 0)
                                y1 = 0;
                            else if (y1 > splitContainer1.Panel1.Height)
                                y1 = splitContainer1.Panel1.Height;
                            if (y2 < 0)
                                y2 = 0;
                            else if (y2 > splitContainer1.Panel1.Height)
                                y2 = splitContainer1.Panel1.Height;
                            GUI.GUI.DrawLine(g, p, x1, y1, x2, y2, splitContainer1.Panel2.Width, splitContainer1.Panel2.Height);
                        }
                        else
                        {
                            x1 = pt[obj.plist[poly].vert[i]].X;
                            y1 = pt[obj.plist[poly].vert[i]].Y;
                            x2 = pt[obj.plist[poly].vert[i + 1]].X;
                            y2 = pt[obj.plist[poly].vert[i + 1]].Y;

                            if (x1 < 0)
                                x1 = 0;
                            else if (x1 > splitContainer1.Panel2.Width)
                                x1 = splitContainer1.Panel1.Width;
                            if (x2 < 0)
                                x2 = 0;
                            else if (x2 > splitContainer1.Panel2.Width)
                                x2 = splitContainer1.Panel1.Width;

                            if (y1 < 0)
                                y1 = 0;
                            else if (y1 > splitContainer1.Panel2.Height)
                                y1 = splitContainer1.Panel2.Height;
                            if (y2 < 0)
                                y2 = 0;
                            else if (y2 > splitContainer1.Panel2.Height)
                                y2 = splitContainer1.Panel2.Height;
                            GUI.GUI.DrawLine(g, p, x1, y1, x2, y2, splitContainer1.Panel2.Width, splitContainer1.Panel2.Height);
                        }
                    }

                }


                #endregion

            }
        }

        private void splitContainer1_Panel2_MouseEnter(object sender, EventArgs e)
        {
            splitContainer1.Panel2.Focus();
        }

        private void splitContainer2_Panel1_MouseEnter(object sender, EventArgs e)
        {
            splitContainer2.Panel1.Focus();
        }

        private void toolStripButton1_Click(object sender, EventArgs e)
        {

            SaveLevel("world.lvl");
            game = Process.Start(@"Win32DirectDraw.exe");
            //game = Process.Start(@"TextureBasics.exe");
            //game = Process.Start(@"C:\\jly\\game_engineGL\\TextureBasics2\\TextureBasics\\Release\\TextureBasics.exe"); // runs texturebasics.exe in ./GameEngine/bin/Debug
        }

        //private void toolStripButton2_Click(object sender, EventArgs e)
        //{

        //    game.Close();

        //}

        private void splitContainer2_Panel1_MouseDown(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                x = e.X;
                y = e.Y;
                z = camTop.pos.Y;
                isMouseDown = true;
                cube = new Cube();
            }
        }

        private void splitContainer2_Panel1_MouseMove(object sender, MouseEventArgs e)
        {
            int xcoord = e.X - splitContainer2.Panel1.Width / 2;
            int ycoord = (splitContainer2.Panel1.Height - e.Y) - splitContainer2.Panel1.Height / 2;
            toolStripStatusLabel1.Text = "(" + e.X + "," + e.Y + ") | (" + xcoord + "," + ycoord + ")";
            Graphics mainScreen = splitContainer2.Panel2.CreateGraphics();
            Graphics g = splitContainer2.Panel1.CreateGraphics();


            float alpha = 0.5f * (float)splitContainer2.Panel1.Width - 0.5f;
            float beta = 0.5f * (float)splitContainer2.Panel1.Height - 0.5f;
            int x2, x1, y1, y2;
            float xper, yper;
            if (isMouseDown)
            {
                containerControl1_Paint(null, null);
                if (tsbCube.Checked)
                {
                    if (listObjects.Count > numOfObjects)
                    {
                        listObjects.RemoveLast();
                    }
                    p.Color = Color.Black;

                    #region cube

                    xper = (e.X - splitContainer2.Panel1.Width / 2f) / (splitContainer2.Panel1.Width / 2f);
                    x1 = (int)(xper * (-camTop.pos.Y));
                    xper = (x - splitContainer2.Panel1.Width / 2f) / (splitContainer2.Panel1.Width / 2f);
                    x2 = (int)(xper * (-camTop.pos.Y));

                    if (x2 > x1)
                        cube.width = (x2 - x1);
                    else
                        cube.width = (x1 - x2);

                    yper = (e.Y - splitContainer2.Panel1.Height / 2f) / (splitContainer2.Panel1.Height / 2f);
                    y1 = (int)(yper * (-camTop.pos.Y));
                    yper = (y - splitContainer2.Panel1.Height / 2f) / (splitContainer2.Panel1.Height / 2f);
                    y2 = (int)(yper * (-camTop.pos.Y));

                    if (y2 > y1)
                        cube.length = Math.Abs(y2 - y1);
                    else
                        cube.length = Math.Abs(y1 - y2);

                    cube.world_pos.X = ((x1 + x2) / 2);
                    cube.world_pos.Y = -cube.height / 2;
                    cube.world_pos.Z = -((y1 + y2) / 2);

                    #endregion
                    #region local coordinates
                    cube.vlist_local[0].X = -cube.width / 2;
                    cube.vlist_local[0].Y = cube.height / 2;
                    cube.vlist_local[0].Z = -cube.length / 2;
                    cube.vlist_local[1].X = cube.width / 2;
                    cube.vlist_local[1].Y = cube.height / 2;
                    cube.vlist_local[1].Z = -cube.length / 2;
                    cube.vlist_local[2].X = cube.width / 2;
                    cube.vlist_local[2].Y = -cube.height / 2;
                    cube.vlist_local[2].Z = -cube.length / 2;
                    cube.vlist_local[3].X = -cube.width / 2;
                    cube.vlist_local[3].Y = -cube.height / 2;
                    cube.vlist_local[3].Z = -cube.length / 2;
                    cube.vlist_local[4].X = -cube.width / 2;
                    cube.vlist_local[4].Y = cube.height / 2;
                    cube.vlist_local[4].Z = cube.length / 2;
                    cube.vlist_local[5].X = cube.width / 2;
                    cube.vlist_local[5].Y = cube.height / 2;
                    cube.vlist_local[5].Z = cube.length / 2;
                    cube.vlist_local[6].X = cube.width / 2;
                    cube.vlist_local[6].Y = -cube.height / 2;
                    cube.vlist_local[6].Z = cube.length / 2;
                    cube.vlist_local[7].X = -cube.width / 2;
                    cube.vlist_local[7].Y = -cube.height / 2;
                    cube.vlist_local[7].Z = cube.length / 2;

                    #endregion

                    cube.num_polys = 6;
                    cube.plist[0] = new POLY4DV1();
                    cube.plist[0].poly_num_verts = 4;
                    cube.plist[0].vert = new int[4];
                    cube.plist[0].vert[0] = 0;
                    cube.plist[0].vert[1] = 1;
                    cube.plist[0].vert[2] = 2;
                    cube.plist[0].vert[3] = 3;

                    cube.plist[1] = new POLY4DV1();
                    cube.plist[1].poly_num_verts = 4;
                    cube.plist[1].vert = new int[4];
                    cube.plist[1].vert[0] = 4;
                    cube.plist[1].vert[1] = 5;
                    cube.plist[1].vert[2] = 6;
                    cube.plist[1].vert[3] = 7;

                    cube.plist[2] = new POLY4DV1();
                    cube.plist[2].poly_num_verts = 4;
                    cube.plist[2].vert = new int[4];
                    cube.plist[2].vert[0] = 0;
                    cube.plist[2].vert[1] = 3;
                    cube.plist[2].vert[2] = 7;
                    cube.plist[2].vert[3] = 4;

                    cube.plist[3] = new POLY4DV1();
                    cube.plist[3].poly_num_verts = 4;
                    cube.plist[3].vert = new int[4];
                    cube.plist[3].vert[0] = 1;
                    cube.plist[3].vert[1] = 2;
                    cube.plist[3].vert[2] = 6;
                    cube.plist[3].vert[3] = 5;

                    cube.plist[4] = new POLY4DV1();
                    cube.plist[4].poly_num_verts = 4;
                    cube.plist[4].vert = new int[4];
                    cube.plist[4].vert[0] = 0;
                    cube.plist[4].vert[1] = 1;
                    cube.plist[4].vert[2] = 5;
                    cube.plist[4].vert[3] = 4;

                    cube.plist[5] = new POLY4DV1();
                    cube.plist[5].poly_num_verts = 4;
                    cube.plist[5].vert = new int[4];
                    cube.plist[5].vert[0] = 2;
                    cube.plist[5].vert[1] = 3;
                    cube.plist[5].vert[2] = 7;
                    cube.plist[5].vert[3] = 6;

                    listObjects.AddLast(cube);
                }
                else if (tsbSelect.Checked)
                {
                    p.Color = Color.Yellow;
                    g.DrawLine(p, x, y, e.X, y);
                    g.DrawLine(p, e.X, y, e.X, e.Y);
                    g.DrawLine(p, e.X, e.Y, x, e.Y);
                    g.DrawLine(p, x, e.Y, x, y);
                }
                else if (tsbMove.Checked)
                {
                    for (int i = 0; i < treeView1.SelectedNodes.Count; i++)
                    {
                        TreeNode node = treeView1.SelectedNodes[i] as TreeNode;
                        foreach (OBJECT4DV1 obj in listObjects)
                        {
                            if (node.Index == obj.id)
                            {
                                obj.world_pos.X -= e.X - x;
                                obj.world_pos.Z += e.Y - y;
                                for (int v = 0; v < obj.num_vertices; v++)
                                {
                                    obj.vlist_trans[v].X = obj.world_pos.X + obj.vlist_local[v].X;
                                    obj.vlist_trans[v].Z = obj.world_pos.Z + obj.vlist_local[v].Z;
                                }
                                updateProperties(obj.name);
                            }
                        }
                    }
                    x = e.X;
                    y = e.Y;
                }
                else if (tsbScale.Checked)
                {
                    for (int i = 0; i < treeView1.SelectedNodes.Count; i++)
                    {
                        TreeNode node = treeView1.SelectedNodes[i] as TreeNode;

                        foreach (OBJECT4DV1 obj in listObjects)
                        {
                            if (node.Index == obj.id)
                            {
                                obj.scale.X = obj.scale.X + ((e.X - x) / z);
                                obj.scale.Z = obj.scale.Z + ((e.Y - y) / z);
                                break;
                            }
                        }
                    }
                    x = e.X;
                    y = e.Y;
                }
                else if (tsbRotate.Checked)
                {
                    for (int i = 0; i < treeView1.SelectedNodes.Count; i++)
                    {
                        foreach (OBJECT4DV1 obj in listObjects)
                        {
                            TreeNode node = treeView1.SelectedNodes[i] as TreeNode;
                            if (node.Index == obj.id)
                            {
                                float rad_angle;
                                rad_angle = (e.X - x) * 3.14f / 180.0f;
                                obj.dir.Z += rad_angle;
                                rad_angle = (e.Y - y) * 3.14f / 180.0f;
                                obj.dir.X += rad_angle;

                            }
                        }
                    }
                    x = e.X;
                    y = e.Y;
                }
            }
        }

        private void splitContainer2_Panel1_MouseUp(object sender, MouseEventArgs e)
        {
            int h = splitContainer2.Panel1.Height;
            if (tsbCube.Checked)
            {
                if (listObjects.Count > 0)
                {
                    if (listObjects.Last.Value is Cube)
                    {
                        listObjects.RemoveLast();
                        cube.id = listObjects.Count;
                        //for (int i = 0; i <  listObjects.Count; i++)
                        //{
                        //    cube.plist[cube.id].vert[i] = cube.world_pos.X + cube.vlist_local[i].X; 
                        //}
                        listObjects.AddLast(cube);
                        // numOfObjects++;
                        UpdateTree();
                    }
                }
                treeView1.SelectedNodes.RemoveRange(0, treeView1.SelectedNodes.Count);
            }
            else if (tsbSelect.Checked)
            {
                treeView1.SelectedNodes.RemoveRange(0, treeView1.SelectedNodes.Count);
                foreach (OBJECT4DV1 obj in listObjects)
                {
                    float alpha = 0.5f * (float)splitContainer1.Panel2.Width - 0.5f;
                    float beta = 0.5f * (float)splitContainer1.Panel2.Height - 0.5f;
                    Point pt = new Point();
                    Point4D pt_per = new Point4D();
                    pt_per.X = obj.world_pos.X / -camTop.pos.Y;
                    pt_per.Y = obj.world_pos.Z / -camTop.pos.Y;
                    pt.X = (int)(alpha + pt_per.X * alpha);
                    pt.Y = h - (int)(beta + pt_per.Y * beta);
                    if (e.X > x && e.Y > y)
                    {
                        if (pt.X < e.X && pt.X > x && pt.Y < e.Y && pt.Y > y)
                        {
                            TreeNode[] nodes = treeView1.Nodes.Find(obj.id.ToString(), true);
                            treeView1.SelectedNodes.Add(nodes[0]);
                        }
                        else
                        {
                            treeView1.SelectedNodes.Remove(obj.id);
                        }
                    }
                    else if (e.X < x && e.Y > y)
                    {
                        if (pt.X > e.X && pt.X < x && pt.Y < e.Y && pt.Y > y)
                        {
                            TreeNode[] nodes = treeView1.Nodes.Find(obj.id.ToString(), true);
                            treeView1.SelectedNodes.Add(nodes[0]);
                        }
                        else
                        {
                            treeView1.SelectedNodes.Remove(obj.id);
                        }
                    }
                    else if (e.X < x && e.Y < y)
                    {
                        if (pt.X > e.X && pt.X < x && pt.Y > e.Y && pt.Y < y)
                        {
                            TreeNode[] nodes = treeView1.Nodes.Find(obj.id.ToString(), true);
                            treeView1.SelectedNodes.Add(nodes[0]);
                        }
                        else
                        {
                            treeView1.SelectedNodes.Remove(obj.id);
                        }
                    }
                    else if (e.X > x && e.Y < y)
                    {
                        if (pt.X < e.X && pt.X > x && pt.Y > e.Y && pt.Y < y)
                        {
                            TreeNode[] nodes = treeView1.Nodes.Find(obj.id.ToString(), true);
                            treeView1.SelectedNodes.Add(nodes[0]);
                        }
                        else
                        {
                            treeView1.SelectedNodes.Remove(obj.id);
                        }
                    }
                }
                //treeView1.paintSelectedNodes();
            }
            isMouseDown = false;
            refreshDisplay();
        }

        private void splitContainer1_Panel2_MouseDown(object sender, MouseEventArgs e) // bottom left panel
        {
            if (e.Button == MouseButtons.Left)
            {
                x = e.X;
                y = e.Y;
                z = camLeft.pos.X;
                isMouseDown = true;
                cube = new Cube();
            }
        }

        private void splitContainer1_Panel2_MouseUp(object sender, MouseEventArgs e)
        {
            int h = splitContainer1.Panel2.Height;
            if (tsbCube.Checked)
            {
                if (listObjects.Count > 0)
                {
                    if (listObjects.Last.Value is Cube)
                    {
                        listObjects.RemoveLast();
                        cube.id = listObjects.Count;
                        listObjects.AddLast(cube);
                        //numOfObjects++;
                        UpdateTree();
                    }
                }
                treeView1.SelectedNodes.RemoveRange(0, treeView1.SelectedNodes.Count);
            }
            else if (tsbSelect.Checked)
            {
                treeView1.SelectedNodes.RemoveRange(0, treeView1.SelectedNodes.Count);
                foreach (OBJECT4DV1 obj in listObjects)
                {
                    float alpha = 0.5f * (float)splitContainer1.Panel2.Width - 0.5f;
                    float beta = 0.5f * (float)splitContainer1.Panel2.Height - 0.5f;
                    Point pt = new Point();
                    Point4D pt_per = new Point4D();
                    pt_per.X = obj.world_pos.Z / camLeft.pos.X;
                    pt_per.Y = obj.world_pos.Y / -camLeft.pos.X;
                    pt.X = (int)(alpha + pt_per.X * alpha);
                    pt.Y = h - (int)(beta + pt_per.Y * beta);
                    if (e.X > x && e.Y > y)
                    {
                        if (pt.X < e.X && pt.X > x && pt.Y < e.Y && pt.Y > y)
                        {
                            TreeNode[] nodes = treeView1.Nodes.Find(obj.id.ToString(), true);
                            treeView1.SelectedNodes.Add(nodes[0]);
                        }
                        else
                        {
                            treeView1.SelectedNodes.Remove(obj.id);
                        }
                    }
                    else if (e.X < x && e.Y > y)
                    {
                        if (pt.X > e.X && pt.X < x && pt.Y < e.Y && pt.Y > y)
                        {
                            TreeNode[] nodes = treeView1.Nodes.Find(obj.id.ToString(), true);
                            treeView1.SelectedNodes.Add(nodes[0]);
                        }
                        else
                        {
                            treeView1.SelectedNodes.Remove(obj.id);
                        }
                    }
                    else if (e.X < x && e.Y < y)
                    {
                        if (pt.X > e.X && pt.X < x && pt.Y > e.Y && pt.Y < y)
                        {
                            TreeNode[] nodes = treeView1.Nodes.Find(obj.id.ToString(), true);
                            treeView1.SelectedNodes.Add(nodes[0]);
                        }
                        else
                        {
                            treeView1.SelectedNodes.Remove(obj.id);
                        }
                    }
                    else if (e.X > x && e.Y < y)
                    {
                        if (pt.X < e.X && pt.X > x && pt.Y > e.Y && pt.Y < y)
                        {
                            TreeNode[] nodes = treeView1.Nodes.Find(obj.id.ToString(), true);
                            treeView1.SelectedNodes.Add(nodes[0]);
                        }
                        else
                        {
                            treeView1.SelectedNodes.Remove(obj.id);
                        }
                    }
                }
                //treeView1.paintSelectedNodes();
            }
            isMouseDown = false;
            refreshDisplay();
        }

        private void splitContainer1_Panel2_MouseMove(object sender, MouseEventArgs e)
        {
            int xcoord = e.X - splitContainer1.Panel2.Width / 2;
            int ycoord = (splitContainer1.Panel2.Height - e.Y) - splitContainer1.Panel2.Height / 2;
            toolStripStatusLabel1.Text = "(" + e.X + "," + e.Y + ") | (" + xcoord + "," + ycoord + ")";
            Graphics mainScreen = splitContainer2.Panel2.CreateGraphics();
            Graphics g = splitContainer1.Panel2.CreateGraphics();


            float alpha = 0.5f * (float)splitContainer2.Panel2.Width - 0.5f;
            float beta = 0.5f * (float)splitContainer2.Panel2.Height - 0.5f;
            int x2, x1, y1, y2;
            float xper, yper;
            if (isMouseDown)
            {
                containerControl1_Paint(null, null);
                if (tsbCube.Checked)
                {
                    if (listObjects.Count > numOfObjects)
                    {
                        listObjects.RemoveLast();
                    }
                    p.Color = Color.Black;

                    #region cube
                    xper = (e.X - splitContainer1.Panel2.Width / 2f) / (splitContainer1.Panel2.Width / 2f);
                    x1 = (int)(xper * (-camLeft.pos.X));
                    xper = (x - splitContainer1.Panel2.Width / 2f) / (splitContainer1.Panel2.Width / 2f);
                    x2 = (int)(xper * (-camLeft.pos.X));

                    if (x2 > x1)
                        cube.length = (x2 - x1);
                    else
                        cube.length = (x1 - x2);

                    yper = (e.Y - splitContainer1.Panel2.Height / 2f) / (splitContainer1.Panel2.Height / 2f);
                    y1 = (int)(yper * (-camLeft.pos.X));
                    yper = (y - splitContainer1.Panel2.Height / 2f) / (splitContainer1.Panel2.Height / 2f);
                    y2 = (int)(yper * (-camLeft.pos.X));

                    if (y2 > y1)
                        cube.height = Math.Abs(y2 - y1);
                    else
                        cube.height = Math.Abs(y1 - y2);

                    cube.world_pos.X = cube.width / 2;
                    cube.world_pos.Y = -((y1 + y2) / 2);
                    cube.world_pos.Z = -((x1 + x2) / 2);

                    #endregion
                    #region local coordinates
                    cube.vlist_local[0].X = -cube.width / 2;
                    cube.vlist_local[0].Y = cube.height / 2;
                    cube.vlist_local[0].Z = -cube.length / 2;
                    cube.vlist_local[1].X = cube.width;
                    cube.vlist_local[1].Y = cube.height / 2;
                    cube.vlist_local[1].Z = -cube.length / 2;
                    cube.vlist_local[2].X = cube.width;
                    cube.vlist_local[2].Y = -cube.height / 2;
                    cube.vlist_local[2].Z = -cube.length / 2;
                    cube.vlist_local[3].X = -cube.width / 2;
                    cube.vlist_local[3].Y = -cube.height / 2;
                    cube.vlist_local[3].Z = -cube.length / 2;
                    cube.vlist_local[4].X = -cube.width / 2;
                    cube.vlist_local[4].Y = cube.height / 2;
                    cube.vlist_local[4].Z = cube.length / 2;
                    cube.vlist_local[5].X = cube.width;
                    cube.vlist_local[5].Y = cube.height / 2;
                    cube.vlist_local[5].Z = cube.length / 2;
                    cube.vlist_local[6].X = cube.width;
                    cube.vlist_local[6].Y = -cube.height / 2;
                    cube.vlist_local[6].Z = cube.length / 2;
                    cube.vlist_local[7].X = -cube.width / 2;
                    cube.vlist_local[7].Y = -cube.height / 2;
                    cube.vlist_local[7].Z = cube.length / 2;
                    #endregion

                    cube.num_polys = 6;
                    cube.plist[0] = new POLY4DV1();
                    cube.plist[0].poly_num_verts = 4;
                    cube.plist[0].vert = new int[4];
                    cube.plist[0].vert[0] = 0;
                    cube.plist[0].vert[1] = 1;
                    cube.plist[0].vert[2] = 2;
                    cube.plist[0].vert[3] = 3;

                    cube.plist[1] = new POLY4DV1();
                    cube.plist[1].poly_num_verts = 4;
                    cube.plist[1].vert = new int[4];
                    cube.plist[1].vert[0] = 4;
                    cube.plist[1].vert[1] = 5;
                    cube.plist[1].vert[2] = 6;
                    cube.plist[1].vert[3] = 7;

                    cube.plist[2] = new POLY4DV1();
                    cube.plist[2].poly_num_verts = 4;
                    cube.plist[2].vert = new int[4];
                    cube.plist[2].vert[0] = 0;
                    cube.plist[2].vert[1] = 3;
                    cube.plist[2].vert[2] = 7;
                    cube.plist[2].vert[3] = 4;

                    cube.plist[3] = new POLY4DV1();
                    cube.plist[3].poly_num_verts = 4;
                    cube.plist[3].vert = new int[4];
                    cube.plist[3].vert[0] = 1;
                    cube.plist[3].vert[1] = 2;
                    cube.plist[3].vert[2] = 6;
                    cube.plist[3].vert[3] = 5;

                    cube.plist[4] = new POLY4DV1();
                    cube.plist[4].poly_num_verts = 4;
                    cube.plist[4].vert = new int[4];
                    cube.plist[4].vert[0] = 0;
                    cube.plist[4].vert[1] = 1;
                    cube.plist[4].vert[2] = 5;
                    cube.plist[4].vert[3] = 4;

                    cube.plist[5] = new POLY4DV1();
                    cube.plist[5].poly_num_verts = 4;
                    cube.plist[5].vert = new int[4];
                    cube.plist[5].vert[0] = 2;
                    cube.plist[5].vert[1] = 3;
                    cube.plist[5].vert[2] = 7;
                    cube.plist[5].vert[3] = 6;

                    listObjects.AddLast(cube);
                }
                else if (tsbSelect.Checked)
                {
                    p.Color = Color.Yellow;
                    g.DrawLine(p, x, y, e.X, y);
                    g.DrawLine(p, e.X, y, e.X, e.Y);
                    g.DrawLine(p, e.X, e.Y, x, e.Y);
                    g.DrawLine(p, x, e.Y, x, y);
                }
                else if (tsbMove.Checked)
                {
                    for (int i = 0; i < treeView1.SelectedNodes.Count; i++)
                    {
                        TreeNode node = treeView1.SelectedNodes[i] as TreeNode;
                        foreach (OBJECT4DV1 obj in listObjects)
                        {
                            if (node.Index == obj.id)
                            {
                                obj.world_pos.Z -= e.X - x;
                                obj.world_pos.Y -= e.Y - y;
                                for (int v = 0; v < obj.num_vertices; v++)
                                {
                                    obj.vlist_trans[v].Z = obj.world_pos.Z + obj.vlist_local[v].Z;
                                    obj.vlist_trans[v].Y = obj.world_pos.Y + obj.vlist_local[v].Y;
                                }
                                updateProperties(obj.name);
                            }
                        }
                    }
                    x = e.X;
                    y = e.Y;
                }
                else if (tsbScale.Checked)
                {
                    for (int i = 0; i < treeView1.SelectedNodes.Count; i++)
                    {
                        TreeNode node = treeView1.SelectedNodes[i] as TreeNode;

                        foreach (OBJECT4DV1 obj in listObjects)
                        {
                            if (node.Index == obj.id)
                            {
                                obj.scale.Z = obj.scale.Z + ((e.X - x) / z);
                                obj.scale.Y = obj.scale.Y + ((e.Y - y) / z);
                                break;
                            }
                        }
                    }
                    x = e.X;
                    y = e.Y;
                }
                else if (tsbRotate.Checked)
                {
                    for (int i = 0; i < treeView1.SelectedNodes.Count; i++)
                    {
                        foreach (OBJECT4DV1 obj in listObjects)
                        {
                            TreeNode node = treeView1.SelectedNodes[i] as TreeNode;
                            if (node.Index == obj.id)
                            {
                                float rad_angle;
                                rad_angle = (e.X - x) * 3.14f / 180.0f;
                                obj.dir.Y += rad_angle;
                                rad_angle = (e.Y - y) * 3.14f / 180.0f;
                                obj.dir.Z += rad_angle;

                            }
                        }
                    }
                    x = e.X;
                    y = e.Y;
                }
            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            float wScale = this.Width / width;
            float hScale = this.Height / height;
            containerControl1.Scale(new SizeF(wScale, hScale));
            treeView1.Scale(new SizeF(wScale, hScale));
            int x = containerControl1.Left + containerControl1.Width / 2;
            //int y = frontLabel.Location.Y * Convert.ToInt32(hScale);
            frontLabel.Location = new Point(containerControl1.Left, frontLabel.Location.Y);
            sideLabel.Location = new Point(containerControl1.Left, containerControl1.Bottom);
            topLabel.Location = new Point(x, topLabel.Location.Y);
            perspectiveLabel.Location = new Point(x, containerControl1.Bottom);
            propertyGrid1.Location = new Point(x + containerControl1.Width / 2, containerControl1.Top);
            propertyGroupBox.Location = new Point(x + containerControl1.Width / 2, propertyGrid1.Bottom);
        }

        private void treeView1_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Delete)
            {
                int i = 0;
                foreach (OBJECT4DV1 objInst in listObjects)
                {
                    if (objInst.name == treeView1.SelectedNode.Text)
                    {
                        listObjects.Remove(objInst);
                        treeView1.Nodes.RemoveAt(i);
                        numOfObjects = listObjects.Count;
                        break;
                    }
                    i++;
                }

                refreshDisplay();
                //treeView1.SelectedImageIndex
                //treeView1.SelectedNode.Text
            }
        }

        private void cameraButton_Click(object sender, EventArgs e)
        {
            FileStream theFile;
            StreamReader rdr;
            String str;
            string sPath = "";
            string[] split;
            string[] token;

            sPath = "camera.ply";

            OBJECT4DV1 obj = new OBJECT4DV1();
            obj.Load_PLY(ref sPath, new Vector(1, 1, 1, 1), new Vector(0, 0, 100, 1), new Vector(0, 0, 0, 1));
            obj.id = listObjects.Count;
            listObjects.AddLast(obj);

            numOfObjects = listObjects.Count;
            UpdateTree();
            containerControl1_Paint(null, null);
        }

        private void propertyGrid1_PropertyValueChanged(object s, PropertyValueChangedEventArgs e)
        {
            string name = e.ChangedItem.PropertyDescriptor.Name;
            if (name == "Name")
            {
                treeView1.SelectedNode.Text = e.ChangedItem.Value.ToString();
                objectInstance.name = treeView1.SelectedNode.Text;
            }
            else if (name == "Script")
            {
                objectInstance.scriptName = e.ChangedItem.Value.ToString();
            }
            valueTextBox.Text = e.ChangedItem.Value.ToString();
        }

        private void propertyGrid1_MouseClick(object sender, MouseEventArgs e)
        {

        }

        private void propertyGrid1_SelectedGridItemChanged(object sender, SelectedGridItemChangedEventArgs e)
        {
            if (e.NewSelection.PropertyDescriptor != null)
            {
                nameTextBox.Text = e.NewSelection.PropertyDescriptor.Name;
                if (e.NewSelection.Value == null)
                    valueTextBox.Text = "";
                else
                    valueTextBox.Text = e.NewSelection.Value.ToString();
            }
        }

        private void ChangeButton_Click(object sender, EventArgs e)
        {
            Process.Start(@"Notepad.exe", valueTextBox.Text);
            // if (nameTextBox.Text == )
            //treeView1.SelectedNode.
            //propertyGrid1.SelectedGridItem. = valueTextBox.Text;
            // propertyGrid1.SelectedGridItem.PropertyDescriptor.SetValue(propertyGrid1.SelectedGridItem, valueTextBox.Text);
        }

        private void Form1_ResizeEnd(object sender, EventArgs e)
        {
            //float wScale = this.Width / width;
            //float hScale = this.Height / height;
            //containerControl1.Scale(new SizeF(wScale, hScale));
        }

        private void colorButton_Click(object sender, EventArgs e)
        {
            DialogResult dr;
            dr = colorDialog1.ShowDialog(this);

            if (dr == DialogResult.OK)
            {
                Color color = colorDialog1.Color;
                
            }
        }

        private void loadModelToolStripMenuItem_Click(object sender, EventArgs e)
        {
            DialogResult dr;
            FileStream theFile;
            StreamReader rdr;
            String str;
            string sPath = "";
            string[] split;
            string[] token;


            if (sender.ToString() == "Load Model")
            {
                this.Enabled = false;
                dr = openFileDialog1.ShowDialog(this);

                if (dr == DialogResult.OK)
                {

                    sPath = openFileDialog1.FileName;

                    if (sPath.Substring(sPath.Length - 4) == ".txt")
                    {
                        theFile = File.Open(sPath, FileMode.Open, FileAccess.Read);
                        rdr = new StreamReader(theFile);

                        while ((str = rdr.ReadLine()) != null)
                        {
                            split = str.Split(new Char[] { ' ' });
                            if (split[0] == "cube")
                            {
                                cube = new Cube();
                                for (int i = 0; i < int.Parse(split[1]); i++)
                                {
                                    str = rdr.ReadLine();
                                    token = str.Split(new Char[] { ' ' });
                                    cube.vlist_trans[i].X = float.Parse(token[0]);
                                    cube.vlist_trans[i].Y = float.Parse(token[1]);
                                    cube.vlist_trans[i].Z = float.Parse(token[2]);
                                    cube.vlist_trans[i].W = 1;
                                }

                                listObjects.AddLast(cube);
                            }
                        }
                    }
                    else if (sPath.Substring(sPath.Length - 4) == ".plg")
                    {
                        /*cube = new Cube();                    
                        cube.Load_PLG(ref sPath,new Vector4(1, 1, 1, 1), new Vector4(0, 0, 0, 0), new Vector4(0, 0, 0, 0));
                        #region local to world coordinates
                        for (int i = 0; i < 8; i++)
                        {
                            cube.vlist_trans[i].X = cube.world_pos.X + cube.vlist_local[i].X;
                            cube.vlist_trans[i].Y = cube.world_pos.Y + cube.vlist_local[i].Y;
                            cube.vlist_trans[i].Z = cube.world_pos.Z + cube.vlist_local[i].Z;
                            cube.vlist_trans[i].W = 1;
                        }
                        #endregion
                        listObjects.AddLast(cube);*/

                        OBJECT4DV1 obj = new OBJECT4DV1();
                        obj.Load_PLG(ref sPath, new Vector(1, 1, 1, 1), new Vector(0, 0, 100, 1), new Vector(0, 0, 0, 1));
                        /*for (int i = 0; i < obj.num_vertices; i++)
                        {
                            obj.vlist_trans[i].X = obj.world_pos.X + obj.vlist_local[i].X;// +listObjects.Count * 100;
                            obj.vlist_trans[i].Y = obj.world_pos.Y + obj.vlist_local[i].Y;
                            obj.vlist_trans[i].Z = obj.world_pos.Z + obj.vlist_local[i].Z;
                            obj.vlist_trans[i].W = 1;
                        }*/
                        obj.id = listObjects.Count;
                        listObjects.AddLast(obj);
                    }
                    else if (sPath.Substring(sPath.Length - 4) == ".ply")
                    {
                        OBJECT4DV1 obj = new OBJECT4DV1();
                        obj.Load_PLY(ref sPath, new Vector(1, 1, 1, 1), new Vector(0, 0, 100, 1), new Vector(0, 0, 0, 1));
                        obj.id = listObjects.Count;
                        listObjects.AddLast(obj);
                        //try
                        //{
                        //    using (var stream = File.OpenRead(sPath))
                        //    {
                        //        //BinaryReader binReader = new BinaryReader(File.Open(fileName, FileMode.Open);
                        //        var reader = new PlyReader(stream);

                        //        // Read the header
                        //        var header = reader.ReadHeader();
                        //    }
                        //}
                        //catch (Exception ex)
                        //{
                        //    Console.WriteLine($"Error: {ex.Message}");
                        //}
                    }
                }
                numOfObjects = listObjects.Count;
                UpdateTree();
                containerControl1_Paint(null, null);
                this.Enabled = true;
            }
        }

        private void UpdateTree()
        {
            treeView1.Nodes.Clear();
            foreach (OBJECT4DV1 obj in listObjects)
            {
                if (obj.name == null)
                    obj.name = obj.ToString() + obj.id.ToString();
                treeView1.Nodes.Add(obj.id.ToString(), obj.name);

            }
            //treeView1.paintSelectedNodes();
            treeView1.Refresh();
            //treeView1.Nodes.Add(listObjects.Count.ToString());
        }

        private void updateProperties(string objName)
        {
            objectInstance = new OBJECT4DV1();
            foreach (OBJECT4DV1 objInst in listObjects)
            {
                if (objInst.name == objName)
                {
                    objectInstance = objInst;
                    propertyGrid1.SelectedObject = objInst;

                    break;
                }
            }

            CustomClass myProperties = new CustomClass();
            foreach (PropertyInfo prop in objectInstance.GetType().GetProperties())
            {

                CustomProperty myProp = new CustomProperty(prop.Name, prop.GetValue(objectInstance, null),
                               false, true);
                myProperties.Add(myProp);
            }

            propertyGrid1.Refresh();
        }

        private void treeView1_NodeMouseClick(object sender, TreeNodeMouseClickEventArgs e)
        {
            updateProperties(e.Node.Text);
            //objectInstance = new OBJECT4DV1();
            //foreach (OBJECT4DV1 objInst in listObjects)
            //{
            //    if (objInst.name == e.Node.Text)
            //    {
            //        objectInstance = objInst;
            //        propertyGrid1.SelectedObject = objInst;

            //        break;
            //    }                
            //}

            //CustomClass myProperties = new CustomClass();
            //foreach (PropertyInfo prop in objectInstance.GetType().GetProperties())
            //{

            //    CustomProperty myProp = new CustomProperty(prop.Name, prop.GetValue(objectInstance, null),
            //                   false, true);
            //    myProperties.Add(myProp);
            //}         

            //propertyGrid1.Refresh();
        }


        private void SaveLevel(string filename)
        {
            StreamWriter wtr, wtrScripts;
            FileStream fs = new FileStream(filename,
                FileMode.Truncate, FileAccess.Write, FileShare.None);

            //File.WriteAllText("allScripts.txt", string.Empty);
            FileStream fsScripts = new FileStream("allScripts.txt",
                FileMode.Truncate, FileAccess.Write, FileShare.None);


            wtr = new StreamWriter(fs);
            wtrScripts = new StreamWriter(fsScripts);
            wtrScripts.WriteLine("#include \"ScriptTrans.h\"");
            wtr.WriteLine(listObjects.Count);
            foreach (OBJECT4DV1 o in listObjects)
            {
                if (o is Cube)
                {
                    Cube c = (Cube)o;
                    wtr.WriteLine("cube");
                    wtr.WriteLine(c.name);
                    wtr.WriteLine(c.scriptName);
                    wtr.WriteLine(c.world_pos.X + " " + c.world_pos.Y + " " + c.world_pos.Z);
                    wtr.WriteLine(c.width + " " + c.height + " " + c.length);
                    wtr.WriteLine(c.dir.X + " " + c.dir.Y + " " + c.dir.Z);
                    wtr.WriteLine(c.scale.X + " " + c.scale.Y + " " + c.scale.Z);
                }
                else
                {
                    wtr.WriteLine("object");
                    wtr.WriteLine(o.name);
                    wtr.WriteLine(o.scriptName);
                    wtr.WriteLine(o.world_pos.X + " " + o.world_pos.Y + " " + o.world_pos.Z);
                    wtr.WriteLine(o.dir.X + " " + o.dir.Y + " " + o.dir.Z);
                    wtr.WriteLine(o.scale.X + " " + o.scale.Y + " " + o.scale.Z);
                    wtr.WriteLine(o.num_vertices);
                    for (int i = 0; i < o.num_vertices; i++)
                    {
                        wtr.WriteLine(o.vlist_local[i].X + " " + o.vlist_local[i].Y + " " + o.vlist_local[i].Z);
                    }
                    wtr.WriteLine(o.num_polys);
                    for (int i = 0; i < o.num_polys; i++)
                    {
                        wtr.WriteLine(o.plist[i].vert[0] + " " + o.plist[i].vert[1] + " " + o.plist[i].vert[2]);
                    }
                }
                wtrScripts.WriteLine("#include \"" + o.scriptName + "\"");
            }
            wtr.Close();
            wtrScripts.Close();
        }

    }
}