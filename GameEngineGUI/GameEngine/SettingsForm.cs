﻿using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace GameEngine
{

    public partial class SettingsForm : Form
    {
        private String sdkSelected = "DirectX";

        public string SdkSelected { get => sdkSelected; set => sdkSelected = value; }

        public SettingsForm()
        {
            InitializeComponent();
            SdkSelected = "DirectX";
        }

        private void confirmButton_Click(object sender, EventArgs e)
        {
            this.DialogResult = DialogResult.OK;
            this.Close();
        }

        private void rbOpenGL_CheckedChanged(object sender, EventArgs e)
        {
            SdkSelected = "OpenGL";
        }

        private void rbDirectX_CheckedChanged(object sender, EventArgs e)
        {
            SdkSelected = "DirectX";
        }
    }
}
