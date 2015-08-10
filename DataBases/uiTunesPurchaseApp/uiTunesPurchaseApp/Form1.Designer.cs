namespace uiTunesPurchaseApp
{
    partial class PurchaseApp
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
            this.PurchaseType = new System.Windows.Forms.ComboBox();
            this.FirstName_textBox1 = new System.Windows.Forms.TextBox();
            this.LastName_textBox2 = new System.Windows.Forms.TextBox();
            this.Password_textBox3 = new System.Windows.Forms.TextBox();
            this.listBox1 = new System.Windows.Forms.ListBox();
            this.GoToAccount_Button = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.Purchase_Button = new System.Windows.Forms.Button();
            this.listView1 = new System.Windows.Forms.ListView();
            this.LogOut_button = new System.Windows.Forms.Button();
            this.Balance_listView2 = new System.Windows.Forms.ListView();
            this.label4 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // PurchaseType
            // 
            this.PurchaseType.BackColor = System.Drawing.Color.LightCoral;
            this.PurchaseType.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.PurchaseType.FormattingEnabled = true;
            this.PurchaseType.Items.AddRange(new object[] {
            "Albums",
            "Songs"});
            this.PurchaseType.Location = new System.Drawing.Point(254, 44);
            this.PurchaseType.Name = "PurchaseType";
            this.PurchaseType.Size = new System.Drawing.Size(194, 23);
            this.PurchaseType.TabIndex = 0;
            this.PurchaseType.SelectedIndexChanged += new System.EventHandler(this.PurchaseType_SelectedIndexChanged);
            // 
            // FirstName_textBox1
            // 
            this.FirstName_textBox1.BackColor = System.Drawing.Color.MistyRose;
            this.FirstName_textBox1.Location = new System.Drawing.Point(14, 45);
            this.FirstName_textBox1.Name = "FirstName_textBox1";
            this.FirstName_textBox1.Size = new System.Drawing.Size(194, 21);
            this.FirstName_textBox1.TabIndex = 1;
            this.FirstName_textBox1.Text = "Enter FIRST Name";
            this.FirstName_textBox1.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.FirstName_textBox1.Click += new System.EventHandler(this.FirstName_textBox1_Click);
            // 
            // LastName_textBox2
            // 
            this.LastName_textBox2.BackColor = System.Drawing.Color.MistyRose;
            this.LastName_textBox2.Location = new System.Drawing.Point(14, 75);
            this.LastName_textBox2.Name = "LastName_textBox2";
            this.LastName_textBox2.Size = new System.Drawing.Size(194, 21);
            this.LastName_textBox2.TabIndex = 2;
            this.LastName_textBox2.Text = "Enter LAST Name";
            this.LastName_textBox2.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.LastName_textBox2.Click += new System.EventHandler(this.LastName_textBox2_Click);
            // 
            // Password_textBox3
            // 
            this.Password_textBox3.BackColor = System.Drawing.Color.MistyRose;
            this.Password_textBox3.Location = new System.Drawing.Point(14, 105);
            this.Password_textBox3.Name = "Password_textBox3";
            this.Password_textBox3.Size = new System.Drawing.Size(194, 21);
            this.Password_textBox3.TabIndex = 3;
            this.Password_textBox3.Text = "Enter PASSWORD";
            this.Password_textBox3.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.Password_textBox3.Click += new System.EventHandler(this.Password_textBox3_Click);
            this.Password_textBox3.Enter += new System.EventHandler(this.Password_textBox3_Enter);
            // 
            // listBox1
            // 
            this.listBox1.BackColor = System.Drawing.Color.MistyRose;
            this.listBox1.FormattingEnabled = true;
            this.listBox1.HorizontalScrollbar = true;
            this.listBox1.ItemHeight = 15;
            this.listBox1.Location = new System.Drawing.Point(254, 75);
            this.listBox1.Name = "listBox1";
            this.listBox1.Size = new System.Drawing.Size(194, 319);
            this.listBox1.TabIndex = 4;
            this.listBox1.SelectedIndexChanged += new System.EventHandler(this.listBox1_SelectedIndexChanged);
            // 
            // GoToAccount_Button
            // 
            this.GoToAccount_Button.BackColor = System.Drawing.Color.LightCoral;
            this.GoToAccount_Button.Font = new System.Drawing.Font("Arial", 9.75F, ((System.Drawing.FontStyle)((System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Italic))), System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.GoToAccount_Button.Location = new System.Drawing.Point(14, 136);
            this.GoToAccount_Button.Name = "GoToAccount_Button";
            this.GoToAccount_Button.Size = new System.Drawing.Size(195, 27);
            this.GoToAccount_Button.TabIndex = 5;
            this.GoToAccount_Button.Text = "Go To Your Account";
            this.GoToAccount_Button.UseVisualStyleBackColor = false;
            this.GoToAccount_Button.Click += new System.EventHandler(this.GoToAccount_Button_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.BackColor = System.Drawing.Color.Transparent;
            this.label1.Font = new System.Drawing.Font("Arial Black", 14.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.ForeColor = System.Drawing.Color.WhiteSmoke;
            this.label1.Location = new System.Drawing.Point(15, 15);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(60, 27);
            this.label1.TabIndex = 6;
            this.label1.Text = "One.";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.BackColor = System.Drawing.Color.Transparent;
            this.label2.Font = new System.Drawing.Font("Arial Black", 14.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.ForeColor = System.Drawing.Color.WhiteSmoke;
            this.label2.Location = new System.Drawing.Point(249, 15);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(63, 27);
            this.label2.TabIndex = 7;
            this.label2.Text = "Two.";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.BackColor = System.Drawing.Color.Transparent;
            this.label3.Font = new System.Drawing.Font("Arial Black", 14.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label3.ForeColor = System.Drawing.Color.WhiteSmoke;
            this.label3.Location = new System.Drawing.Point(487, 15);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(79, 27);
            this.label3.TabIndex = 8;
            this.label3.Text = "Three.";
            // 
            // Purchase_Button
            // 
            this.Purchase_Button.BackColor = System.Drawing.Color.LightCoral;
            this.Purchase_Button.Enabled = false;
            this.Purchase_Button.Font = new System.Drawing.Font("Arial", 9.75F, ((System.Drawing.FontStyle)((System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Italic))), System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Purchase_Button.Location = new System.Drawing.Point(492, 250);
            this.Purchase_Button.Name = "Purchase_Button";
            this.Purchase_Button.Size = new System.Drawing.Size(195, 27);
            this.Purchase_Button.TabIndex = 9;
            this.Purchase_Button.Text = "PURCHASE";
            this.Purchase_Button.UseVisualStyleBackColor = false;
            this.Purchase_Button.Click += new System.EventHandler(this.Purchase_button2_Click);
            // 
            // listView1
            // 
            this.listView1.BackColor = System.Drawing.Color.MistyRose;
            this.listView1.Location = new System.Drawing.Point(492, 44);
            this.listView1.Name = "listView1";
            this.listView1.Size = new System.Drawing.Size(195, 163);
            this.listView1.TabIndex = 10;
            this.listView1.UseCompatibleStateImageBehavior = false;
            this.listView1.View = System.Windows.Forms.View.List;
            // 
            // LogOut_button
            // 
            this.LogOut_button.BackColor = System.Drawing.Color.Tomato;
            this.LogOut_button.Font = new System.Drawing.Font("Arial", 9.75F, ((System.Drawing.FontStyle)((System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Italic))), System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.LogOut_button.Location = new System.Drawing.Point(492, 283);
            this.LogOut_button.Name = "LogOut_button";
            this.LogOut_button.Size = new System.Drawing.Size(195, 27);
            this.LogOut_button.TabIndex = 11;
            this.LogOut_button.Text = "LOGOUT";
            this.LogOut_button.UseVisualStyleBackColor = false;
            this.LogOut_button.Click += new System.EventHandler(this.LogOut_button_Click);
            // 
            // Balance_listView2
            // 
            this.Balance_listView2.BackColor = System.Drawing.Color.MistyRose;
            this.Balance_listView2.Location = new System.Drawing.Point(585, 214);
            this.Balance_listView2.Name = "Balance_listView2";
            this.Balance_listView2.Size = new System.Drawing.Size(102, 30);
            this.Balance_listView2.TabIndex = 12;
            this.Balance_listView2.UseCompatibleStateImageBehavior = false;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.BackColor = System.Drawing.Color.Transparent;
            this.label4.Font = new System.Drawing.Font("Arial Black", 14.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label4.ForeColor = System.Drawing.Color.WhiteSmoke;
            this.label4.Location = new System.Drawing.Point(487, 217);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(98, 27);
            this.label4.TabIndex = 13;
            this.label4.Text = "Balance";
            // 
            // PurchaseApp
            // 
            this.AllowDrop = true;
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackgroundImage = global::uiTunesPurchaseApp.Properties.Resources.Chrysanthemum;
            this.ClientSize = new System.Drawing.Size(716, 400);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.Balance_listView2);
            this.Controls.Add(this.LogOut_button);
            this.Controls.Add(this.listView1);
            this.Controls.Add(this.Purchase_Button);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.GoToAccount_Button);
            this.Controls.Add(this.listBox1);
            this.Controls.Add(this.Password_textBox3);
            this.Controls.Add(this.LastName_textBox2);
            this.Controls.Add(this.FirstName_textBox1);
            this.Controls.Add(this.PurchaseType);
            this.Font = new System.Drawing.Font("Arial", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.MaximizeBox = false;
            this.Name = "PurchaseApp";
            this.Text = "uiTunes Purchase App";
            this.TransparencyKey = System.Drawing.Color.Silver;
            this.Load += new System.EventHandler(this.PurchaseApp_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ComboBox PurchaseType;
        private System.Windows.Forms.TextBox FirstName_textBox1;
        private System.Windows.Forms.TextBox LastName_textBox2;
        private System.Windows.Forms.TextBox Password_textBox3;
        private System.Windows.Forms.Button GoToAccount_Button;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Button Purchase_Button;
        private System.Windows.Forms.ListView listView1;
        private System.Windows.Forms.ListBox listBox1;
        private System.Windows.Forms.Button LogOut_button;
        private System.Windows.Forms.ListView Balance_listView2;
        private System.Windows.Forms.Label label4;
    }
}

