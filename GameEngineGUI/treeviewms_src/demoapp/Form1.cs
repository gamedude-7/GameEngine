using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using System.Data;

namespace demoapp
{
	/// <summary>
	/// Summary description for Form1.
	/// </summary>
	public class Form1 : System.Windows.Forms.Form
	{
		private System.Windows.Forms.Button button1;
		private System.Windows.Forms.ListView listView1;
		private System.Windows.Forms.ImageList imageList1;
		private System.Windows.Forms.Button button2;
		private TreeViewMS.TreeViewMS treeViewMS1;
		private System.ComponentModel.IContainer components;

		public Form1()
		{
			//
			// Required for Windows Form Designer support
			//
			InitializeComponent();

			//
			// TODO: Add any constructor code after InitializeComponent call
			//
		}

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		protected override void Dispose( bool disposing )
		{
			if( disposing )
			{
				if (components != null) 
				{
					components.Dispose();
				}
			}
			base.Dispose( disposing );
		}

		#region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			this.components = new System.ComponentModel.Container();
			System.Resources.ResourceManager resources = new System.Resources.ResourceManager(typeof(Form1));
			this.button1 = new System.Windows.Forms.Button();
			this.listView1 = new System.Windows.Forms.ListView();
			this.imageList1 = new System.Windows.Forms.ImageList(this.components);
			this.button2 = new System.Windows.Forms.Button();
			this.treeViewMS1 = new TreeViewMS.TreeViewMS();
			this.SuspendLayout();
			// 
			// button1
			// 
			this.button1.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
			this.button1.Location = new System.Drawing.Point(232, 32);
			this.button1.Name = "button1";
			this.button1.Size = new System.Drawing.Size(104, 40);
			this.button1.TabIndex = 1;
			this.button1.Text = "-- Add -->";
			this.button1.Click += new System.EventHandler(this.button1_AddNodes);
			// 
			// listView1
			// 
			this.listView1.Location = new System.Drawing.Point(344, 16);
			this.listView1.Name = "listView1";
			this.listView1.Size = new System.Drawing.Size(200, 200);
			this.listView1.SmallImageList = this.imageList1;
			this.listView1.TabIndex = 2;
			this.listView1.View = System.Windows.Forms.View.List;
			// 
			// imageList1
			// 
			this.imageList1.ColorDepth = System.Windows.Forms.ColorDepth.Depth8Bit;
			this.imageList1.ImageSize = new System.Drawing.Size(16, 16);
			this.imageList1.ImageStream = ((System.Windows.Forms.ImageListStreamer)(resources.GetObject("imageList1.ImageStream")));
			this.imageList1.TransparentColor = System.Drawing.Color.White;
			// 
			// button2
			// 
			this.button2.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
			this.button2.Location = new System.Drawing.Point(232, 88);
			this.button2.Name = "button2";
			this.button2.Size = new System.Drawing.Size(104, 40);
			this.button2.TabIndex = 3;
			this.button2.Text = "<-- Remove --";
			this.button2.Click += new System.EventHandler(this.button2_RemoveNodes);
			// 
			// treeViewMS1
			// 
			this.treeViewMS1.ImageList = this.imageList1;
			this.treeViewMS1.Location = new System.Drawing.Point(8, 16);
			this.treeViewMS1.Name = "treeViewMS1";
			this.treeViewMS1.Nodes.AddRange(new System.Windows.Forms.TreeNode[] {
				new System.Windows.Forms.TreeNode("Databases", 0, 0, new System.Windows.Forms.TreeNode[] {
					new System.Windows.Forms.TreeNode("Northwind", 1, 1, new System.Windows.Forms.TreeNode[] {
						new System.Windows.Forms.TreeNode("Customers", 2, 2),
						new System.Windows.Forms.TreeNode("Suppliers", 2, 2),
						new System.Windows.Forms.TreeNode("Orders", 2, 2),
						new System.Windows.Forms.TreeNode("Region", 2, 2),
						new System.Windows.Forms.TreeNode("Procurement", 2, 2)
					}),
					new System.Windows.Forms.TreeNode("Master0", 1, 1, new System.Windows.Forms.TreeNode[] {
						new System.Windows.Forms.TreeNode("Table0", 2, 2),
						new System.Windows.Forms.TreeNode("Table1", 2, 2),
						new System.Windows.Forms.TreeNode("Table2", 2, 2),
						new System.Windows.Forms.TreeNode("Table3", 2, 2)
					})
				})
			});

			this.treeViewMS1.Size = new System.Drawing.Size(216, 200);
			this.treeViewMS1.TabIndex = 4;
			// 
			// Form1
			// 
			this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
			this.ClientSize = new System.Drawing.Size(552, 229);
			this.Controls.AddRange(new System.Windows.Forms.Control[] {
																		  this.treeViewMS1,
																		  this.button2,
																		  this.listView1,
																		  this.button1});
			this.Name = "Form1";
			this.Text = "Demo App (multiple selection treeview)";
			this.ResumeLayout(false);

		}
		#endregion

		/// <summary>
		/// The main entry point for the application.
		/// </summary>
		[STAThread]
		static void Main() 
		{
			Application.Run(new Form1());
		}

		private void button1_AddNodes(object sender, System.EventArgs e)
		{

			// add selected items from treeview to the listview on the right hand side
			foreach (TreeNode n in treeViewMS1.SelectedNodes)
			{
				listView1.Items.Add( n.Text, n.ImageIndex );
			}

		}

		private void button2_RemoveNodes(object sender, System.EventArgs e)
		{
			ListView.SelectedListViewItemCollection selcoll = listView1.SelectedItems;

			while ( selcoll.Count>0 )// warning : sellcoll.Count dynamically updated by listView1.Items.Remove(...)
				listView1.Items.Remove( selcoll[0] );
		}

	}
}
