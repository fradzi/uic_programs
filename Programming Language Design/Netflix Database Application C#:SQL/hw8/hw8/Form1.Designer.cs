namespace hw8
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
            this.displayListBox = new System.Windows.Forms.ListBox();
            this.textBox2 = new System.Windows.Forms.TextBox();
            this.textBox3 = new System.Windows.Forms.TextBox();
            this.textBox4 = new System.Windows.Forms.TextBox();
            this.textBox5 = new System.Windows.Forms.TextBox();
            this.getAllmovies = new System.Windows.Forms.Button();
            this.getReviews = new System.Windows.Forms.Button();
            this.nMoviesAvgRating = new System.Windows.Forms.Button();
            this.nMoviesNumReviews = new System.Windows.Forms.Button();
            this.nUsersByReviews = new System.Windows.Forms.Button();
            this.avgRating = new System.Windows.Forms.Button();
            this.eachRating = new System.Windows.Forms.Button();
            this.insertMovie = new System.Windows.Forms.Button();
            this.insertReviews = new System.Windows.Forms.Button();
            this.panel1 = new System.Windows.Forms.Panel();
            this.panel2 = new System.Windows.Forms.Panel();
            this.panel3 = new System.Windows.Forms.Panel();
            this.panel4 = new System.Windows.Forms.Panel();
            this.label1 = new System.Windows.Forms.Label();
            this.trackBar1 = new System.Windows.Forms.TrackBar();
            this.panel1.SuspendLayout();
            this.panel2.SuspendLayout();
            this.panel3.SuspendLayout();
            this.panel4.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.trackBar1)).BeginInit();
            this.SuspendLayout();
            // 
            // displayListBox
            // 
            this.displayListBox.BackColor = System.Drawing.Color.GhostWhite;
            this.displayListBox.Font = new System.Drawing.Font("Arial", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.displayListBox.FormattingEnabled = true;
            this.displayListBox.HorizontalScrollbar = true;
            this.displayListBox.ItemHeight = 17;
            this.displayListBox.Location = new System.Drawing.Point(12, 12);
            this.displayListBox.Name = "displayListBox";
            this.displayListBox.Size = new System.Drawing.Size(324, 429);
            this.displayListBox.TabIndex = 1;
            // 
            // textBox2
            // 
            this.textBox2.Font = new System.Drawing.Font("Arial", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.textBox2.Location = new System.Drawing.Point(172, 13);
            this.textBox2.Multiline = true;
            this.textBox2.Name = "textBox2";
            this.textBox2.Size = new System.Drawing.Size(164, 45);
            this.textBox2.TabIndex = 3;
            // 
            // textBox3
            // 
            this.textBox3.Font = new System.Drawing.Font("Arial", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.textBox3.Location = new System.Drawing.Point(172, 27);
            this.textBox3.Multiline = true;
            this.textBox3.Name = "textBox3";
            this.textBox3.Size = new System.Drawing.Size(164, 45);
            this.textBox3.TabIndex = 4;
            // 
            // textBox4
            // 
            this.textBox4.Font = new System.Drawing.Font("Arial", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.textBox4.Location = new System.Drawing.Point(12, 51);
            this.textBox4.Name = "textBox4";
            this.textBox4.Size = new System.Drawing.Size(131, 25);
            this.textBox4.TabIndex = 5;
            // 
            // textBox5
            // 
            this.textBox5.Location = new System.Drawing.Point(13, 41);
            this.textBox5.Name = "textBox5";
            this.textBox5.Size = new System.Drawing.Size(131, 20);
            this.textBox5.TabIndex = 6;
            // 
            // getAllmovies
            // 
            this.getAllmovies.Font = new System.Drawing.Font("Arial", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.getAllmovies.Location = new System.Drawing.Point(13, 12);
            this.getAllmovies.Name = "getAllmovies";
            this.getAllmovies.Size = new System.Drawing.Size(323, 23);
            this.getAllmovies.TabIndex = 7;
            this.getAllmovies.Text = "Get All Movies";
            this.getAllmovies.UseVisualStyleBackColor = true;
            this.getAllmovies.Click += new System.EventHandler(this.getAllmovies_Click);
            // 
            // getReviews
            // 
            this.getReviews.Font = new System.Drawing.Font("Arial", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.getReviews.Location = new System.Drawing.Point(167, 41);
            this.getReviews.Name = "getReviews";
            this.getReviews.Size = new System.Drawing.Size(169, 23);
            this.getReviews.TabIndex = 8;
            this.getReviews.Text = "Get Reviews";
            this.getReviews.UseVisualStyleBackColor = true;
            this.getReviews.Click += new System.EventHandler(this.getReviews_Click);
            // 
            // nMoviesAvgRating
            // 
            this.nMoviesAvgRating.Font = new System.Drawing.Font("Arial", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.nMoviesAvgRating.Location = new System.Drawing.Point(167, 13);
            this.nMoviesAvgRating.Name = "nMoviesAvgRating";
            this.nMoviesAvgRating.Size = new System.Drawing.Size(169, 32);
            this.nMoviesAvgRating.TabIndex = 9;
            this.nMoviesAvgRating.Text = "Top N Movies by Avg Rating";
            this.nMoviesAvgRating.UseVisualStyleBackColor = true;
            this.nMoviesAvgRating.Click += new System.EventHandler(this.nMoviesAvgRating_Click);
            // 
            // nMoviesNumReviews
            // 
            this.nMoviesNumReviews.Font = new System.Drawing.Font("Arial", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.nMoviesNumReviews.Location = new System.Drawing.Point(167, 51);
            this.nMoviesNumReviews.Name = "nMoviesNumReviews";
            this.nMoviesNumReviews.Size = new System.Drawing.Size(169, 32);
            this.nMoviesNumReviews.TabIndex = 10;
            this.nMoviesNumReviews.Text = "Top N Movies by Num Reviews";
            this.nMoviesNumReviews.UseVisualStyleBackColor = true;
            this.nMoviesNumReviews.Click += new System.EventHandler(this.nMoviesNumReviews_Click);
            // 
            // nUsersByReviews
            // 
            this.nUsersByReviews.Font = new System.Drawing.Font("Arial", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.nUsersByReviews.Location = new System.Drawing.Point(167, 89);
            this.nUsersByReviews.Name = "nUsersByReviews";
            this.nUsersByReviews.Size = new System.Drawing.Size(169, 32);
            this.nUsersByReviews.TabIndex = 11;
            this.nUsersByReviews.Text = "Top N Users by Reviews Submitted";
            this.nUsersByReviews.UseVisualStyleBackColor = true;
            this.nUsersByReviews.Click += new System.EventHandler(this.nUsersByReviews_Click);
            // 
            // avgRating
            // 
            this.avgRating.Font = new System.Drawing.Font("Arial", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.avgRating.Location = new System.Drawing.Point(13, 13);
            this.avgRating.Name = "avgRating";
            this.avgRating.Size = new System.Drawing.Size(118, 32);
            this.avgRating.TabIndex = 12;
            this.avgRating.Text = "Average Rating";
            this.avgRating.UseVisualStyleBackColor = true;
            this.avgRating.Click += new System.EventHandler(this.avgRating_Click);
            // 
            // eachRating
            // 
            this.eachRating.Font = new System.Drawing.Font("Arial", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.eachRating.Location = new System.Drawing.Point(12, 55);
            this.eachRating.Name = "eachRating";
            this.eachRating.Size = new System.Drawing.Size(119, 32);
            this.eachRating.TabIndex = 13;
            this.eachRating.Text = "Each Rating ";
            this.eachRating.UseVisualStyleBackColor = true;
            this.eachRating.Click += new System.EventHandler(this.eachRating_Click);
            // 
            // insertMovie
            // 
            this.insertMovie.Font = new System.Drawing.Font("Arial", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.insertMovie.Location = new System.Drawing.Point(13, 13);
            this.insertMovie.Name = "insertMovie";
            this.insertMovie.Size = new System.Drawing.Size(118, 32);
            this.insertMovie.TabIndex = 14;
            this.insertMovie.Text = "Insert Movie";
            this.insertMovie.UseVisualStyleBackColor = true;
            this.insertMovie.Click += new System.EventHandler(this.insertMovie_Click);
            // 
            // insertReviews
            // 
            this.insertReviews.Font = new System.Drawing.Font("Arial", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.insertReviews.Location = new System.Drawing.Point(13, 55);
            this.insertReviews.Name = "insertReviews";
            this.insertReviews.Size = new System.Drawing.Size(118, 32);
            this.insertReviews.TabIndex = 15;
            this.insertReviews.Text = "Insert Review";
            this.insertReviews.UseVisualStyleBackColor = true;
            this.insertReviews.Click += new System.EventHandler(this.insertReviews_Click);
            // 
            // panel1
            // 
            this.panel1.BackColor = System.Drawing.Color.LightSteelBlue;
            this.panel1.Controls.Add(this.getAllmovies);
            this.panel1.Controls.Add(this.textBox5);
            this.panel1.Controls.Add(this.getReviews);
            this.panel1.Location = new System.Drawing.Point(342, 12);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(351, 75);
            this.panel1.TabIndex = 16;
            // 
            // panel2
            // 
            this.panel2.BackColor = System.Drawing.Color.LightSteelBlue;
            this.panel2.Controls.Add(this.nUsersByReviews);
            this.panel2.Controls.Add(this.textBox4);
            this.panel2.Controls.Add(this.nMoviesNumReviews);
            this.panel2.Controls.Add(this.nMoviesAvgRating);
            this.panel2.Location = new System.Drawing.Point(343, 93);
            this.panel2.Name = "panel2";
            this.panel2.Size = new System.Drawing.Size(351, 134);
            this.panel2.TabIndex = 17;
            // 
            // panel3
            // 
            this.panel3.BackColor = System.Drawing.Color.LightSteelBlue;
            this.panel3.Controls.Add(this.eachRating);
            this.panel3.Controls.Add(this.textBox3);
            this.panel3.Controls.Add(this.avgRating);
            this.panel3.Location = new System.Drawing.Point(343, 233);
            this.panel3.Name = "panel3";
            this.panel3.Size = new System.Drawing.Size(351, 101);
            this.panel3.TabIndex = 18;
            // 
            // panel4
            // 
            this.panel4.BackColor = System.Drawing.Color.LightSteelBlue;
            this.panel4.Controls.Add(this.label1);
            this.panel4.Controls.Add(this.trackBar1);
            this.panel4.Controls.Add(this.insertReviews);
            this.panel4.Controls.Add(this.insertMovie);
            this.panel4.Controls.Add(this.textBox2);
            this.panel4.Location = new System.Drawing.Point(343, 340);
            this.panel4.Name = "panel4";
            this.panel4.Size = new System.Drawing.Size(351, 101);
            this.panel4.TabIndex = 19;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Arial", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(312, 64);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(17, 18);
            this.label1.TabIndex = 17;
            this.label1.Text = "1";
            // 
            // trackBar1
            // 
            this.trackBar1.Location = new System.Drawing.Point(171, 64);
            this.trackBar1.Maximum = 5;
            this.trackBar1.Minimum = 1;
            this.trackBar1.Name = "trackBar1";
            this.trackBar1.Size = new System.Drawing.Size(135, 45);
            this.trackBar1.TabIndex = 5;
            this.trackBar1.Value = 1;
            this.trackBar1.Scroll += new System.EventHandler(this.trackBar1_Scroll);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.Lavender;
            this.ClientSize = new System.Drawing.Size(706, 456);
            this.Controls.Add(this.displayListBox);
            this.Controls.Add(this.panel1);
            this.Controls.Add(this.panel2);
            this.Controls.Add(this.panel3);
            this.Controls.Add(this.panel4);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.Fixed3D;
            this.MaximizeBox = false;
            this.Name = "Form1";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Netflix Analysis";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            this.panel2.ResumeLayout(false);
            this.panel2.PerformLayout();
            this.panel3.ResumeLayout(false);
            this.panel3.PerformLayout();
            this.panel4.ResumeLayout(false);
            this.panel4.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.trackBar1)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.ListBox displayListBox;
        private System.Windows.Forms.TextBox textBox2;
        private System.Windows.Forms.TextBox textBox3;
        private System.Windows.Forms.TextBox textBox4;
        private System.Windows.Forms.TextBox textBox5;
        private System.Windows.Forms.Button getAllmovies;
        private System.Windows.Forms.Button getReviews;
        private System.Windows.Forms.Button nMoviesAvgRating;
        private System.Windows.Forms.Button nMoviesNumReviews;
        private System.Windows.Forms.Button nUsersByReviews;
        private System.Windows.Forms.Button avgRating;
        private System.Windows.Forms.Button eachRating;
        private System.Windows.Forms.Button insertMovie;
        private System.Windows.Forms.Button insertReviews;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Panel panel2;
        private System.Windows.Forms.Panel panel3;
        private System.Windows.Forms.Panel panel4;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TrackBar trackBar1;
    }
}

