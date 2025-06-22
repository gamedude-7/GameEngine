namespace GameEngine
{
    partial class SettingsForm
    {
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
            this.confirmButton = new System.Windows.Forms.Button();
            this.sdkRadioGroup = new System.Windows.Forms.GroupBox();
            this.rbDirectX = new System.Windows.Forms.RadioButton();
            this.rbOpenGL = new System.Windows.Forms.RadioButton();
            this.sdkRadioGroup.SuspendLayout();
            this.SuspendLayout();
            // 
            // confirmButton
            // 
            this.confirmButton.Location = new System.Drawing.Point(708, 403);
            this.confirmButton.Name = "confirmButton";
            this.confirmButton.Size = new System.Drawing.Size(75, 23);
            this.confirmButton.TabIndex = 0;
            this.confirmButton.Text = "Confirm";
            this.confirmButton.UseVisualStyleBackColor = true;
            this.confirmButton.Click += new System.EventHandler(this.confirmButton_Click);
            // 
            // sdkRadioGroup
            // 
            this.sdkRadioGroup.Controls.Add(this.rbOpenGL);
            this.sdkRadioGroup.Controls.Add(this.rbDirectX);
            this.sdkRadioGroup.Location = new System.Drawing.Point(56, 41);
            this.sdkRadioGroup.Name = "sdkRadioGroup";
            this.sdkRadioGroup.Size = new System.Drawing.Size(200, 100);
            this.sdkRadioGroup.TabIndex = 1;
            this.sdkRadioGroup.TabStop = false;
            this.sdkRadioGroup.Text = "SDK";
            // 
            // rbDirectX
            // 
            this.rbDirectX.AutoSize = true;
            this.rbDirectX.Location = new System.Drawing.Point(7, 20);
            this.rbDirectX.Name = "rbDirectX";
            this.rbDirectX.Size = new System.Drawing.Size(60, 17);
            this.rbDirectX.TabIndex = 0;
            this.rbDirectX.TabStop = true;
            this.rbDirectX.Text = "DirectX";
            this.rbDirectX.UseVisualStyleBackColor = true;
            this.rbDirectX.CheckedChanged += new System.EventHandler(this.rbDirectX_CheckedChanged);
            // 
            // rbOpenGL
            // 
            this.rbOpenGL.AutoSize = true;
            this.rbOpenGL.Location = new System.Drawing.Point(100, 20);
            this.rbOpenGL.Name = "rbOpenGL";
            this.rbOpenGL.Size = new System.Drawing.Size(65, 17);
            this.rbOpenGL.TabIndex = 1;
            this.rbOpenGL.TabStop = true;
            this.rbOpenGL.Text = "OpenGL";
            this.rbOpenGL.UseVisualStyleBackColor = true;
            this.rbOpenGL.CheckedChanged += new System.EventHandler(this.rbOpenGL_CheckedChanged);
            // 
            // SettingsForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.sdkRadioGroup);
            this.Controls.Add(this.confirmButton);
            this.Name = "SettingsForm";
            this.Text = "SettingsForm";
            this.sdkRadioGroup.ResumeLayout(false);
            this.sdkRadioGroup.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button confirmButton;
        private System.Windows.Forms.GroupBox sdkRadioGroup;
        private System.Windows.Forms.RadioButton rbDirectX;
        private System.Windows.Forms.RadioButton rbOpenGL;
    }
}