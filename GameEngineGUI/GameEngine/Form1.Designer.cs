namespace GameEngine
{
 
    partial class Form1
    {
        //[DllImport("user32.dll")]
        //public static extern int SendMessage(IntPtr hwnd,
        //[MarshalAs(UnmanagedType.U4)] int Msg, int wParam,
        //[MarshalAs(System.Runtime.InteropServices.UnmanagedType.LPStr)] string
        //lParam);

        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code


        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.containerControl1 = new System.Windows.Forms.ContainerControl();
            this.mainSplitContainer = new System.Windows.Forms.SplitContainer();
            this.splitContainer1 = new System.Windows.Forms.SplitContainer();
            this.contextMenuStrip1 = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.loadModelToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.splitContainer2 = new System.Windows.Forms.SplitContainer();
            this.toolStrip1 = new System.Windows.Forms.ToolStrip();
            this.tsbMove = new System.Windows.Forms.ToolStripButton();
            this.tsbRotate = new System.Windows.Forms.ToolStripButton();
            this.tsbScale = new System.Windows.Forms.ToolStripButton();
            this.tsbSelect = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.tsbCube = new System.Windows.Forms.ToolStripButton();
            this.toolStripSeparator2 = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripButton1 = new System.Windows.Forms.ToolStripButton();
            this.cameraButton = new System.Windows.Forms.ToolStripButton();
            this.colorButton = new System.Windows.Forms.ToolStripButton();
            this.imageList1 = new System.Windows.Forms.ImageList(this.components);
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.newToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.openToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.saveToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.saveFileDialog1 = new System.Windows.Forms.SaveFileDialog();
            this.openFileDialog1 = new System.Windows.Forms.OpenFileDialog();
            this.statusStrip = new System.Windows.Forms.StatusStrip();
            this.toolStripStatusLabel1 = new System.Windows.Forms.ToolStripStatusLabel();
            this.toolStripStatusLabel2 = new System.Windows.Forms.ToolStripStatusLabel();
            this.toolStripStatusLabel3 = new System.Windows.Forms.ToolStripStatusLabel();
            this.treeView1 = new TreeViewMS.TreeViewMS();
            this.frontLabel = new System.Windows.Forms.Label();
            this.topLabel = new System.Windows.Forms.Label();
            this.sideLabel = new System.Windows.Forms.Label();
            this.perspectiveLabel = new System.Windows.Forms.Label();
            this.propertyGrid1 = new System.Windows.Forms.PropertyGrid();
            this.propertyGroupBox = new System.Windows.Forms.GroupBox();
            this.valueTextBox = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.nameTextBox = new System.Windows.Forms.TextBox();
            this.NameLabel = new System.Windows.Forms.Label();
            this.ChangeButton = new System.Windows.Forms.Button();
            this.colorDialog1 = new System.Windows.Forms.ColorDialog();
            this.containerControl1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.mainSplitContainer)).BeginInit();
            this.mainSplitContainer.Panel1.SuspendLayout();
            this.mainSplitContainer.Panel2.SuspendLayout();
            this.mainSplitContainer.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).BeginInit();
            this.splitContainer1.SuspendLayout();
            this.contextMenuStrip1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer2)).BeginInit();
            this.splitContainer2.SuspendLayout();
            this.toolStrip1.SuspendLayout();
            this.menuStrip1.SuspendLayout();
            this.statusStrip.SuspendLayout();
            this.propertyGroupBox.SuspendLayout();
            this.SuspendLayout();
            // 
            // containerControl1
            // 
            this.containerControl1.BackColor = System.Drawing.SystemColors.ControlDark;
            this.containerControl1.Controls.Add(this.mainSplitContainer);
            this.containerControl1.Location = new System.Drawing.Point(275, 71);
            this.containerControl1.Name = "containerControl1";
            this.containerControl1.Size = new System.Drawing.Size(965, 801);
            this.containerControl1.TabIndex = 5;
            this.containerControl1.Text = "containerControl1";
            this.containerControl1.Paint += new System.Windows.Forms.PaintEventHandler(this.containerControl1_Paint);
            // 
            // mainSplitContainer
            // 
            this.mainSplitContainer.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.mainSplitContainer.Dock = System.Windows.Forms.DockStyle.Fill;
            this.mainSplitContainer.Location = new System.Drawing.Point(0, 0);
            this.mainSplitContainer.Name = "mainSplitContainer";
            // 
            // mainSplitContainer.Panel1
            // 
            this.mainSplitContainer.Panel1.Controls.Add(this.splitContainer1);
            // 
            // mainSplitContainer.Panel2
            // 
            this.mainSplitContainer.Panel2.Controls.Add(this.splitContainer2);
            this.mainSplitContainer.Size = new System.Drawing.Size(965, 801);
            this.mainSplitContainer.SplitterDistance = 476;
            this.mainSplitContainer.TabIndex = 0;
            // 
            // splitContainer1
            // 
            this.splitContainer1.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.splitContainer1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer1.Location = new System.Drawing.Point(0, 0);
            this.splitContainer1.Name = "splitContainer1";
            this.splitContainer1.Orientation = System.Windows.Forms.Orientation.Horizontal;
            // 
            // splitContainer1.Panel1
            // 
            this.splitContainer1.Panel1.ContextMenuStrip = this.contextMenuStrip1;
            this.splitContainer1.Panel1.Paint += new System.Windows.Forms.PaintEventHandler(this.splitContainer1_Panel1_Paint);
            this.splitContainer1.Panel1.MouseDown += new System.Windows.Forms.MouseEventHandler(this.splitContainer1_Panel1_MouseDown);
            this.splitContainer1.Panel1.MouseEnter += new System.EventHandler(this.splitContainer1_Panel1_MouseEnter);
            this.splitContainer1.Panel1.MouseMove += new System.Windows.Forms.MouseEventHandler(this.splitContainer1_Panel1_MouseMove);
            this.splitContainer1.Panel1.MouseUp += new System.Windows.Forms.MouseEventHandler(this.splitContainer1_Panel1_MouseUp);
            this.splitContainer1.Panel1.MouseWheel += new System.Windows.Forms.MouseEventHandler(this.splitContainer1_Panel1_MouseWheel);
            // 
            // splitContainer1.Panel2
            // 
            this.splitContainer1.Panel2.ContextMenuStrip = this.contextMenuStrip1;
            this.splitContainer1.Panel2.Paint += new System.Windows.Forms.PaintEventHandler(this.splitContainer1_Panel2_Paint);
            this.splitContainer1.Panel2.MouseDown += new System.Windows.Forms.MouseEventHandler(this.splitContainer1_Panel2_MouseDown);
            this.splitContainer1.Panel2.MouseEnter += new System.EventHandler(this.splitContainer1_Panel2_MouseEnter);
            this.splitContainer1.Panel2.MouseMove += new System.Windows.Forms.MouseEventHandler(this.splitContainer1_Panel2_MouseMove);
            this.splitContainer1.Panel2.MouseUp += new System.Windows.Forms.MouseEventHandler(this.splitContainer1_Panel2_MouseUp);
            this.splitContainer1.Panel2.MouseWheel += new System.Windows.Forms.MouseEventHandler(this.splitContainer1_Panel2_MouseWheel);
            this.splitContainer1.Size = new System.Drawing.Size(476, 801);
            this.splitContainer1.SplitterDistance = 400;
            this.splitContainer1.TabIndex = 0;
            // 
            // contextMenuStrip1
            // 
            this.contextMenuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.loadModelToolStripMenuItem});
            this.contextMenuStrip1.Name = "contextMenuStrip1";
            this.contextMenuStrip1.Size = new System.Drawing.Size(138, 26);
            // 
            // loadModelToolStripMenuItem
            // 
            this.loadModelToolStripMenuItem.Name = "loadModelToolStripMenuItem";
            this.loadModelToolStripMenuItem.Size = new System.Drawing.Size(137, 22);
            this.loadModelToolStripMenuItem.Text = "Load Model";
            this.loadModelToolStripMenuItem.Click += new System.EventHandler(this.loadModelToolStripMenuItem_Click);
            // 
            // splitContainer2
            // 
            this.splitContainer2.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.splitContainer2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer2.Location = new System.Drawing.Point(0, 0);
            this.splitContainer2.Name = "splitContainer2";
            this.splitContainer2.Orientation = System.Windows.Forms.Orientation.Horizontal;
            // 
            // splitContainer2.Panel1
            // 
            this.splitContainer2.Panel1.ContextMenuStrip = this.contextMenuStrip1;
            this.splitContainer2.Panel1.Paint += new System.Windows.Forms.PaintEventHandler(this.splitContainer2_Panel1_Paint);
            this.splitContainer2.Panel1.MouseDown += new System.Windows.Forms.MouseEventHandler(this.splitContainer2_Panel1_MouseDown);
            this.splitContainer2.Panel1.MouseEnter += new System.EventHandler(this.splitContainer2_Panel1_MouseEnter);
            this.splitContainer2.Panel1.MouseMove += new System.Windows.Forms.MouseEventHandler(this.splitContainer2_Panel1_MouseMove);
            this.splitContainer2.Panel1.MouseUp += new System.Windows.Forms.MouseEventHandler(this.splitContainer2_Panel1_MouseUp);
            this.splitContainer2.Panel1.MouseWheel += new System.Windows.Forms.MouseEventHandler(this.splitContainer2_Panel1_MouseWheel);
            // 
            // splitContainer2.Panel2
            // 
            this.splitContainer2.Panel2.Paint += new System.Windows.Forms.PaintEventHandler(this.splitContainer2_Panel2_Paint);
            this.splitContainer2.Panel2.Enter += new System.EventHandler(this.splitContainer2_Panel2_Enter);
            this.splitContainer2.Panel2.MouseDown += new System.Windows.Forms.MouseEventHandler(this.splitContainer2_Panel2_MouseDown);
            this.splitContainer2.Panel2.MouseEnter += new System.EventHandler(this.splitContainer2_Panel2_MouseEnter);
            this.splitContainer2.Panel2.MouseLeave += new System.EventHandler(this.splitContainer2_Panel2_MouseLeave);
            this.splitContainer2.Panel2.MouseHover += new System.EventHandler(this.splitContainer2_Panel2_MouseHover);
            this.splitContainer2.Panel2.MouseMove += new System.Windows.Forms.MouseEventHandler(this.splitContainer2_Panel2_MouseMove);
            this.splitContainer2.Panel2.MouseUp += new System.Windows.Forms.MouseEventHandler(this.splitContainer2_Panel2_MouseUp);
            this.splitContainer2.Panel2.MouseWheel += new System.Windows.Forms.MouseEventHandler(this.splitContainer2_Panel2_MouseWheel);
            this.splitContainer2.Size = new System.Drawing.Size(485, 801);
            this.splitContainer2.SplitterDistance = 400;
            this.splitContainer2.TabIndex = 0;
            // 
            // toolStrip1
            // 
            this.toolStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.tsbMove,
            this.tsbRotate,
            this.tsbScale,
            this.tsbSelect,
            this.toolStripSeparator1,
            this.tsbCube,
            this.toolStripSeparator2,
            this.toolStripButton1,
            this.cameraButton,
            this.colorButton});
            this.toolStrip1.Location = new System.Drawing.Point(0, 24);
            this.toolStrip1.Name = "toolStrip1";
            this.toolStrip1.Size = new System.Drawing.Size(1605, 25);
            this.toolStrip1.TabIndex = 6;
            this.toolStrip1.Text = "toolStrip1";
            this.toolStrip1.ItemClicked += new System.Windows.Forms.ToolStripItemClickedEventHandler(this.toolStrip1_ItemClicked);
            // 
            // tsbMove
            // 
            this.tsbMove.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.tsbMove.Image = ((System.Drawing.Image)(resources.GetObject("tsbMove.Image")));
            this.tsbMove.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.tsbMove.Name = "tsbMove";
            this.tsbMove.Size = new System.Drawing.Size(23, 22);
            this.tsbMove.Text = "toolStripButton1";
            this.tsbMove.ToolTipText = "move";
            // 
            // tsbRotate
            // 
            this.tsbRotate.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.tsbRotate.Image = ((System.Drawing.Image)(resources.GetObject("tsbRotate.Image")));
            this.tsbRotate.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.tsbRotate.Name = "tsbRotate";
            this.tsbRotate.Size = new System.Drawing.Size(23, 22);
            this.tsbRotate.Text = "toolStripButton2";
            this.tsbRotate.ToolTipText = "Rotate";
            // 
            // tsbScale
            // 
            this.tsbScale.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.tsbScale.Image = ((System.Drawing.Image)(resources.GetObject("tsbScale.Image")));
            this.tsbScale.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.tsbScale.Name = "tsbScale";
            this.tsbScale.Size = new System.Drawing.Size(23, 22);
            this.tsbScale.Text = "toolStripButton3";
            this.tsbScale.ToolTipText = "Scale";
            // 
            // tsbSelect
            // 
            this.tsbSelect.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.tsbSelect.Image = ((System.Drawing.Image)(resources.GetObject("tsbSelect.Image")));
            this.tsbSelect.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.tsbSelect.Name = "tsbSelect";
            this.tsbSelect.Size = new System.Drawing.Size(23, 22);
            this.tsbSelect.Text = "toolStripButton1";
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(6, 25);
            // 
            // tsbCube
            // 
            this.tsbCube.Checked = true;
            this.tsbCube.CheckState = System.Windows.Forms.CheckState.Checked;
            this.tsbCube.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.tsbCube.Image = ((System.Drawing.Image)(resources.GetObject("tsbCube.Image")));
            this.tsbCube.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.tsbCube.Name = "tsbCube";
            this.tsbCube.Size = new System.Drawing.Size(23, 22);
            this.tsbCube.Text = "toolStripButton1";
            // 
            // toolStripSeparator2
            // 
            this.toolStripSeparator2.Name = "toolStripSeparator2";
            this.toolStripSeparator2.Size = new System.Drawing.Size(6, 25);
            // 
            // toolStripButton1
            // 
            this.toolStripButton1.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.toolStripButton1.Image = ((System.Drawing.Image)(resources.GetObject("toolStripButton1.Image")));
            this.toolStripButton1.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.toolStripButton1.Name = "toolStripButton1";
            this.toolStripButton1.Size = new System.Drawing.Size(23, 22);
            this.toolStripButton1.Text = "toolStripButton1";
            this.toolStripButton1.Click += new System.EventHandler(this.toolStripButton1_Click);
            // 
            // cameraButton
            // 
            this.cameraButton.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.cameraButton.Image = ((System.Drawing.Image)(resources.GetObject("cameraButton.Image")));
            this.cameraButton.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.cameraButton.Name = "cameraButton";
            this.cameraButton.Size = new System.Drawing.Size(23, 22);
            this.cameraButton.Text = "toolStripButton2";
            this.cameraButton.Click += new System.EventHandler(this.cameraButton_Click);
            // 
            // colorButton
            // 
            this.colorButton.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.colorButton.Image = ((System.Drawing.Image)(resources.GetObject("colorButton.Image")));
            this.colorButton.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.colorButton.Name = "colorButton";
            this.colorButton.Size = new System.Drawing.Size(23, 22);
            this.colorButton.Text = "toolStripButton2";
            this.colorButton.Click += new System.EventHandler(this.colorButton_Click);
            // 
            // imageList1
            // 
            this.imageList1.ColorDepth = System.Windows.Forms.ColorDepth.Depth8Bit;
            this.imageList1.ImageSize = new System.Drawing.Size(16, 16);
            this.imageList1.TransparentColor = System.Drawing.Color.Transparent;
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(1605, 24);
            this.menuStrip1.TabIndex = 7;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // fileToolStripMenuItem
            // 
            this.fileToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.newToolStripMenuItem,
            this.openToolStripMenuItem,
            this.saveToolStripMenuItem});
            this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
            this.fileToolStripMenuItem.Size = new System.Drawing.Size(37, 20);
            this.fileToolStripMenuItem.Text = "&File";
            // 
            // newToolStripMenuItem
            // 
            this.newToolStripMenuItem.Name = "newToolStripMenuItem";
            this.newToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            this.newToolStripMenuItem.Text = "&New";
            this.newToolStripMenuItem.Click += new System.EventHandler(this.newToolStripMenuItem_Click);
            // 
            // openToolStripMenuItem
            // 
            this.openToolStripMenuItem.Name = "openToolStripMenuItem";
            this.openToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            this.openToolStripMenuItem.Text = "&Open";
            this.openToolStripMenuItem.Click += new System.EventHandler(this.openToolStripMenuItem_Click);
            // 
            // saveToolStripMenuItem
            // 
            this.saveToolStripMenuItem.Name = "saveToolStripMenuItem";
            this.saveToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            this.saveToolStripMenuItem.Text = "&Save";
            this.saveToolStripMenuItem.Click += new System.EventHandler(this.saveToolStripMenuItem_Click);
            // 
            // openFileDialog1
            // 
            this.openFileDialog1.FileName = "openFileDialog1";
            // 
            // statusStrip
            // 
            this.statusStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripStatusLabel1,
            this.toolStripStatusLabel2,
            this.toolStripStatusLabel3});
            this.statusStrip.Location = new System.Drawing.Point(0, 904);
            this.statusStrip.Name = "statusStrip";
            this.statusStrip.Size = new System.Drawing.Size(1605, 22);
            this.statusStrip.TabIndex = 9;
            this.statusStrip.Text = "statusStrip1";
            // 
            // toolStripStatusLabel1
            // 
            this.toolStripStatusLabel1.Name = "toolStripStatusLabel1";
            this.toolStripStatusLabel1.Size = new System.Drawing.Size(118, 17);
            this.toolStripStatusLabel1.Text = "toolStripStatusLabel1";
            // 
            // toolStripStatusLabel2
            // 
            this.toolStripStatusLabel2.Name = "toolStripStatusLabel2";
            this.toolStripStatusLabel2.Size = new System.Drawing.Size(118, 17);
            this.toolStripStatusLabel2.Text = "toolStripStatusLabel2";
            // 
            // toolStripStatusLabel3
            // 
            this.toolStripStatusLabel3.Name = "toolStripStatusLabel3";
            this.toolStripStatusLabel3.Size = new System.Drawing.Size(118, 17);
            this.toolStripStatusLabel3.Text = "toolStripStatusLabel3";
            // 
            // treeView1
            // 
            this.treeView1.ImageIndex = 0;
            this.treeView1.ImageList = this.imageList1;
            this.treeView1.Location = new System.Drawing.Point(12, 71);
            this.treeView1.Name = "treeView1";
            this.treeView1.SelectedImageIndex = 0;
            this.treeView1.SelectedNodes = ((System.Collections.ArrayList)(resources.GetObject("treeView1.SelectedNodes")));
            this.treeView1.Size = new System.Drawing.Size(241, 801);
            this.treeView1.TabIndex = 11;
            this.treeView1.NodeMouseClick += new System.Windows.Forms.TreeNodeMouseClickEventHandler(this.treeView1_NodeMouseClick);
            this.treeView1.KeyDown += new System.Windows.Forms.KeyEventHandler(this.treeView1_KeyDown);
            // 
            // frontLabel
            // 
            this.frontLabel.AutoSize = true;
            this.frontLabel.Location = new System.Drawing.Point(272, 53);
            this.frontLabel.Name = "frontLabel";
            this.frontLabel.Size = new System.Drawing.Size(31, 13);
            this.frontLabel.TabIndex = 12;
            this.frontLabel.Text = "Front";
            // 
            // topLabel
            // 
            this.topLabel.AutoSize = true;
            this.topLabel.Location = new System.Drawing.Point(752, 53);
            this.topLabel.Name = "topLabel";
            this.topLabel.Size = new System.Drawing.Size(26, 13);
            this.topLabel.TabIndex = 13;
            this.topLabel.Text = "Top";
            // 
            // sideLabel
            // 
            this.sideLabel.AutoSize = true;
            this.sideLabel.Location = new System.Drawing.Point(137, 875);
            this.sideLabel.Name = "sideLabel";
            this.sideLabel.Size = new System.Drawing.Size(28, 13);
            this.sideLabel.TabIndex = 14;
            this.sideLabel.Text = "Side";
            // 
            // perspectiveLabel
            // 
            this.perspectiveLabel.AutoSize = true;
            this.perspectiveLabel.Location = new System.Drawing.Point(614, 875);
            this.perspectiveLabel.Name = "perspectiveLabel";
            this.perspectiveLabel.Size = new System.Drawing.Size(63, 13);
            this.perspectiveLabel.TabIndex = 15;
            this.perspectiveLabel.Text = "Perspective";
            // 
            // propertyGrid1
            // 
            this.propertyGrid1.Location = new System.Drawing.Point(1262, 71);
            this.propertyGrid1.Name = "propertyGrid1";
            this.propertyGrid1.Size = new System.Drawing.Size(318, 712);
            this.propertyGrid1.TabIndex = 16;
            this.propertyGrid1.PropertyValueChanged += new System.Windows.Forms.PropertyValueChangedEventHandler(this.propertyGrid1_PropertyValueChanged);
            this.propertyGrid1.SelectedGridItemChanged += new System.Windows.Forms.SelectedGridItemChangedEventHandler(this.propertyGrid1_SelectedGridItemChanged);
            this.propertyGrid1.MouseClick += new System.Windows.Forms.MouseEventHandler(this.propertyGrid1_MouseClick);
            // 
            // propertyGroupBox
            // 
            this.propertyGroupBox.Controls.Add(this.valueTextBox);
            this.propertyGroupBox.Controls.Add(this.label1);
            this.propertyGroupBox.Controls.Add(this.nameTextBox);
            this.propertyGroupBox.Controls.Add(this.NameLabel);
            this.propertyGroupBox.Controls.Add(this.ChangeButton);
            this.propertyGroupBox.Location = new System.Drawing.Point(1262, 789);
            this.propertyGroupBox.Name = "propertyGroupBox";
            this.propertyGroupBox.Size = new System.Drawing.Size(316, 112);
            this.propertyGroupBox.TabIndex = 17;
            this.propertyGroupBox.TabStop = false;
            this.propertyGroupBox.Text = "Property";
            // 
            // valueTextBox
            // 
            this.valueTextBox.Location = new System.Drawing.Point(48, 53);
            this.valueTextBox.Name = "valueTextBox";
            this.valueTextBox.Size = new System.Drawing.Size(149, 20);
            this.valueTextBox.TabIndex = 4;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(7, 56);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(34, 13);
            this.label1.TabIndex = 3;
            this.label1.Text = "Value";
            // 
            // nameTextBox
            // 
            this.nameTextBox.Enabled = false;
            this.nameTextBox.Location = new System.Drawing.Point(48, 17);
            this.nameTextBox.Name = "nameTextBox";
            this.nameTextBox.Size = new System.Drawing.Size(149, 20);
            this.nameTextBox.TabIndex = 2;
            // 
            // NameLabel
            // 
            this.NameLabel.AutoSize = true;
            this.NameLabel.Location = new System.Drawing.Point(7, 20);
            this.NameLabel.Name = "NameLabel";
            this.NameLabel.Size = new System.Drawing.Size(35, 13);
            this.NameLabel.TabIndex = 1;
            this.NameLabel.Text = "Name";
            // 
            // ChangeButton
            // 
            this.ChangeButton.Location = new System.Drawing.Point(6, 83);
            this.ChangeButton.Name = "ChangeButton";
            this.ChangeButton.Size = new System.Drawing.Size(75, 23);
            this.ChangeButton.TabIndex = 0;
            this.ChangeButton.Text = "Change";
            this.ChangeButton.UseVisualStyleBackColor = true;
            this.ChangeButton.Click += new System.EventHandler(this.ChangeButton_Click);
            // 
            // label5
            // 
            //this.label5.AutoSize = true;
            //this.label5.Location = new System.Drawing.Point(1103, 71);
            //this.label5.Name = "label5";
            //this.label5.Size = new System.Drawing.Size(35, 13);
            //this.label5.TabIndex = 16;
            //this.label5.Text = "Name";
            // 
            // OpenScriptButton
            // 
            //this.OpenScriptButton.Location = new System.Drawing.Point(1106, 113);
            //this.OpenScriptButton.Name = "OpenScriptButton";
            //this.OpenScriptButton.Size = new System.Drawing.Size(75, 23);
            //this.OpenScriptButton.TabIndex = 17;
            //this.OpenScriptButton.Text = "Open Script";
            //this.OpenScriptButton.UseVisualStyleBackColor = true;
            //this.OpenScriptButton.Click += new System.EventHandler(this.OpenScriptButton_Click);
            // 
            // NameTextBox
            // 
            //this.NameTextBox.Location = new System.Drawing.Point(1106, 87);
            //this.NameTextBox.Name = "NameTextBox";
            //this.NameTextBox.Size = new System.Drawing.Size(100, 20);
            //this.NameTextBox.TabIndex = 18;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1605, 926);
            this.Controls.Add(this.propertyGroupBox);
            this.Controls.Add(this.propertyGrid1);
            this.Controls.Add(this.perspectiveLabel);
            this.Controls.Add(this.sideLabel);
            this.Controls.Add(this.topLabel);
            this.Controls.Add(this.frontLabel);
            this.Controls.Add(this.treeView1);
            this.Controls.Add(this.statusStrip);
            this.Controls.Add(this.toolStrip1);
            this.Controls.Add(this.menuStrip1);
            this.Controls.Add(this.containerControl1);
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.ResizeEnd += new System.EventHandler(this.Form1_ResizeEnd);
            this.containerControl1.ResumeLayout(false);
            this.mainSplitContainer.Panel1.ResumeLayout(false);
            this.mainSplitContainer.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.mainSplitContainer)).EndInit();
            this.mainSplitContainer.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).EndInit();
            this.splitContainer1.ResumeLayout(false);
            this.contextMenuStrip1.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer2)).EndInit();
            this.splitContainer2.ResumeLayout(false);
            this.toolStrip1.ResumeLayout(false);
            this.toolStrip1.PerformLayout();
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.statusStrip.ResumeLayout(false);
            this.statusStrip.PerformLayout();
            this.propertyGroupBox.ResumeLayout(false);
            this.propertyGroupBox.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ContainerControl containerControl1;
        private System.Windows.Forms.SplitContainer mainSplitContainer;
        private System.Windows.Forms.SplitContainer splitContainer1;
        private System.Windows.Forms.SplitContainer splitContainer2;
        private System.Windows.Forms.ToolStrip toolStrip1;
        private System.Windows.Forms.ToolStripButton tsbMove;
        private System.Windows.Forms.ToolStripButton tsbRotate;
        private System.Windows.Forms.ToolStripButton tsbScale;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
        private System.Windows.Forms.ImageList imageList1;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem newToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem openToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem saveToolStripMenuItem;
        private System.Windows.Forms.SaveFileDialog saveFileDialog1;
        private System.Windows.Forms.OpenFileDialog openFileDialog1;
        private System.Windows.Forms.ToolStripButton tsbSelect;
        private System.Windows.Forms.ToolStripButton tsbCube;
        private System.Windows.Forms.StatusStrip statusStrip;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabel1;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabel2;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabel3;
        private System.Windows.Forms.ToolStripButton toolStripButton1;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator2;
        private System.Windows.Forms.ContextMenuStrip contextMenuStrip1;
        private System.Windows.Forms.ToolStripMenuItem loadModelToolStripMenuItem;
        private TreeViewMS.TreeViewMS treeView1;
        private System.Windows.Forms.Label frontLabel;
        private System.Windows.Forms.Label topLabel;
        private System.Windows.Forms.Label sideLabel;
        private System.Windows.Forms.Label perspectiveLabel;
        private System.Windows.Forms.ToolStripButton cameraButton;
        private System.Windows.Forms.PropertyGrid propertyGrid1;
        private System.Windows.Forms.GroupBox propertyGroupBox;
        private System.Windows.Forms.Button ChangeButton;
        private System.Windows.Forms.TextBox valueTextBox;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox nameTextBox;
        private System.Windows.Forms.Label NameLabel;
        private System.Windows.Forms.ToolStripButton colorButton;
        private System.Windows.Forms.ColorDialog colorDialog1;
    }

    
     

}

