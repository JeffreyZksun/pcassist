namespace ET
{
    partial class Form1
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
            this.splitContainer1 = new System.Windows.Forms.SplitContainer();
            this.splitContainer2 = new System.Windows.Forms.SplitContainer();
            this.TitleList = new System.Windows.Forms.ListBox();
            this.exToolContent = new System.Windows.Forms.TextBox();
            this.outputWindow = new System.Windows.Forms.RichTextBox();
            this.textSearchBox = new System.Windows.Forms.TextBox();
            this.splitContainer1.Panel1.SuspendLayout();
            this.splitContainer1.Panel2.SuspendLayout();
            this.splitContainer1.SuspendLayout();
            this.splitContainer2.Panel1.SuspendLayout();
            this.splitContainer2.Panel2.SuspendLayout();
            this.splitContainer2.SuspendLayout();
            this.SuspendLayout();
            // 
            // splitContainer1
            // 
            this.splitContainer1.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.splitContainer1.Location = new System.Drawing.Point(0, 32);
            this.splitContainer1.Name = "splitContainer1";
            this.splitContainer1.Orientation = System.Windows.Forms.Orientation.Horizontal;
            // 
            // splitContainer1.Panel1
            // 
            this.splitContainer1.Panel1.Controls.Add(this.splitContainer2);
            // 
            // splitContainer1.Panel2
            // 
            this.splitContainer1.Panel2.Controls.Add(this.outputWindow);
            this.splitContainer1.Size = new System.Drawing.Size(632, 499);
            this.splitContainer1.SplitterDistance = 360;
            this.splitContainer1.TabIndex = 0;
            // 
            // splitContainer2
            // 
            this.splitContainer2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer2.Location = new System.Drawing.Point(0, 0);
            this.splitContainer2.Name = "splitContainer2";
            // 
            // splitContainer2.Panel1
            // 
            this.splitContainer2.Panel1.Controls.Add(this.TitleList);
            // 
            // splitContainer2.Panel2
            // 
            this.splitContainer2.Panel2.Controls.Add(this.exToolContent);
            this.splitContainer2.Size = new System.Drawing.Size(632, 360);
            this.splitContainer2.SplitterDistance = 210;
            this.splitContainer2.TabIndex = 0;
            // 
            // TitleList
            // 
            this.TitleList.Dock = System.Windows.Forms.DockStyle.Fill;
            this.TitleList.FormattingEnabled = true;
            this.TitleList.Items.AddRange(new object[] {
            "item1",
            "item2"});
            this.TitleList.Location = new System.Drawing.Point(0, 0);
            this.TitleList.Name = "TitleList";
            this.TitleList.Size = new System.Drawing.Size(210, 355);
            this.TitleList.TabIndex = 0;
            this.TitleList.MouseDoubleClick += new System.Windows.Forms.MouseEventHandler(this.listBox1_MouseDoubleClick);
            this.TitleList.SelectedIndexChanged += new System.EventHandler(this.TitleList_SelectedIndexChanged);
            // 
            // exToolContent
            // 
            this.exToolContent.Dock = System.Windows.Forms.DockStyle.Fill;
            this.exToolContent.Location = new System.Drawing.Point(0, 0);
            this.exToolContent.Multiline = true;
            this.exToolContent.Name = "exToolContent";
            this.exToolContent.Size = new System.Drawing.Size(418, 360);
            this.exToolContent.TabIndex = 0;
            // 
            // outputWindow
            // 
            this.outputWindow.Dock = System.Windows.Forms.DockStyle.Fill;
            this.outputWindow.Location = new System.Drawing.Point(0, 0);
            this.outputWindow.Name = "outputWindow";
            this.outputWindow.Size = new System.Drawing.Size(632, 135);
            this.outputWindow.TabIndex = 0;
            this.outputWindow.Text = "";
            // 
            // textSearchBox
            // 
            this.textSearchBox.Location = new System.Drawing.Point(13, 6);
            this.textSearchBox.Name = "textSearchBox";
            this.textSearchBox.Size = new System.Drawing.Size(168, 20);
            this.textSearchBox.TabIndex = 1;
            this.textSearchBox.TextChanged += new System.EventHandler(this.textSearchBox_TextChanged);
            this.textSearchBox.KeyUp += new System.Windows.Forms.KeyEventHandler(this.textSearchBox_KeyUp);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(632, 531);
            this.Controls.Add(this.textSearchBox);
            this.Controls.Add(this.splitContainer1);
            this.Name = "Form1";
            this.Text = "External Tools";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.KeyDown += new System.Windows.Forms.KeyEventHandler(this.Form1_KeyDown);
            this.splitContainer1.Panel1.ResumeLayout(false);
            this.splitContainer1.Panel2.ResumeLayout(false);
            this.splitContainer1.ResumeLayout(false);
            this.splitContainer2.Panel1.ResumeLayout(false);
            this.splitContainer2.Panel2.ResumeLayout(false);
            this.splitContainer2.Panel2.PerformLayout();
            this.splitContainer2.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.SplitContainer splitContainer1;
        private System.Windows.Forms.SplitContainer splitContainer2;
        private System.Windows.Forms.RichTextBox outputWindow;
        private System.Windows.Forms.ListBox TitleList;
        private System.Windows.Forms.TextBox exToolContent;
        private System.Windows.Forms.TextBox textSearchBox;

    }
}

