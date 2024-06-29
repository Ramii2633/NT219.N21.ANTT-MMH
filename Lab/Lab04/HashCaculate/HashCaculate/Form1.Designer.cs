namespace HashCaculate
{
    partial class Form1
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
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
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            comboBoxType = new ComboBox();
            btnOpenfile = new Button();
            tbMD5 = new TextBox();
            tbSHA1 = new TextBox();
            tbSHA3 = new TextBox();
            btnCalculate = new Button();
            cbMD5 = new CheckBox();
            cbSHA1 = new CheckBox();
            cbSHA3 = new CheckBox();
            label1 = new Label();
            label2 = new Label();
            tbdata = new TextBox();
            SuspendLayout();
            // 
            // comboBoxType
            // 
            comboBoxType.AllowDrop = true;
            comboBoxType.Font = new Font("Segoe UI", 10.2F, FontStyle.Regular, GraphicsUnit.Point);
            comboBoxType.FormattingEnabled = true;
            comboBoxType.Items.AddRange(new object[] { "Text", "Hex", "File" });
            comboBoxType.Location = new Point(29, 53);
            comboBoxType.Margin = new Padding(4, 3, 4, 3);
            comboBoxType.Name = "comboBoxType";
            comboBoxType.Size = new Size(150, 36);
            comboBoxType.TabIndex = 0;
            comboBoxType.SelectedIndexChanged += comboBoxType_SelectedIndexChanged;
            // 
            // btnOpenfile
            // 
            btnOpenfile.Location = new Point(899, 48);
            btnOpenfile.Margin = new Padding(4, 3, 4, 3);
            btnOpenfile.Name = "btnOpenfile";
            btnOpenfile.Size = new Size(94, 44);
            btnOpenfile.TabIndex = 2;
            btnOpenfile.Text = "Open";
            btnOpenfile.UseVisualStyleBackColor = true;
            btnOpenfile.Click += btnOpenfile_Click;
            // 
            // tbMD5
            // 
            tbMD5.Location = new Point(142, 149);
            tbMD5.Margin = new Padding(5, 6, 5, 6);
            tbMD5.Multiline = true;
            tbMD5.Name = "tbMD5";
            tbMD5.ReadOnly = true;
            tbMD5.Size = new Size(800, 50);
            tbMD5.TabIndex = 3;
            // 
            // tbSHA1
            // 
            tbSHA1.Location = new Point(148, 282);
            tbSHA1.Margin = new Padding(5, 6, 5, 6);
            tbSHA1.Multiline = true;
            tbSHA1.Name = "tbSHA1";
            tbSHA1.ReadOnly = true;
            tbSHA1.Size = new Size(800, 50);
            tbSHA1.TabIndex = 4;
            // 
            // tbSHA3
            // 
            tbSHA3.Location = new Point(148, 414);
            tbSHA3.Margin = new Padding(5, 6, 5, 6);
            tbSHA3.Multiline = true;
            tbSHA3.Name = "tbSHA3";
            tbSHA3.ReadOnly = true;
            tbSHA3.Size = new Size(800, 50);
            tbSHA3.TabIndex = 5;
            // 
            // btnCalculate
            // 
            btnCalculate.BackColor = Color.Silver;
            btnCalculate.Font = new Font("Segoe UI", 12F, FontStyle.Bold, GraphicsUnit.Point);
            btnCalculate.Location = new Point(398, 524);
            btnCalculate.Margin = new Padding(5, 6, 5, 6);
            btnCalculate.Name = "btnCalculate";
            btnCalculate.Size = new Size(245, 73);
            btnCalculate.TabIndex = 6;
            btnCalculate.Text = "CALCULATE";
            btnCalculate.UseVisualStyleBackColor = false;
            btnCalculate.Click += btnCalculate_Click;
            // 
            // cbMD5
            // 
            cbMD5.AutoSize = true;
            cbMD5.Location = new Point(20, 159);
            cbMD5.Margin = new Padding(5, 6, 5, 6);
            cbMD5.Name = "cbMD5";
            cbMD5.Size = new Size(81, 29);
            cbMD5.TabIndex = 7;
            cbMD5.Text = "MD5:";
            cbMD5.UseVisualStyleBackColor = true;
            cbMD5.CheckedChanged += cbMD5_CheckedChanged;
            // 
            // cbSHA1
            // 
            cbSHA1.AutoSize = true;
            cbSHA1.Location = new Point(20, 292);
            cbSHA1.Margin = new Padding(5, 6, 5, 6);
            cbSHA1.Name = "cbSHA1";
            cbSHA1.Size = new Size(87, 29);
            cbSHA1.TabIndex = 8;
            cbSHA1.Text = "SHA1:";
            cbSHA1.UseVisualStyleBackColor = true;
            cbSHA1.CheckedChanged += cbSHA1_CheckedChanged;
            // 
            // cbSHA3
            // 
            cbSHA3.AutoSize = true;
            cbSHA3.Location = new Point(20, 425);
            cbSHA3.Margin = new Padding(5, 6, 5, 6);
            cbSHA3.Name = "cbSHA3";
            cbSHA3.Size = new Size(124, 29);
            cbSHA3.TabIndex = 9;
            cbSHA3.Text = "SHA3-256:";
            cbSHA3.UseVisualStyleBackColor = true;
            cbSHA3.CheckedChanged += cbSHA3_CheckedChanged;
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Location = new Point(29, 25);
            label1.Margin = new Padding(5, 0, 5, 0);
            label1.Name = "label1";
            label1.Size = new Size(111, 25);
            label1.TabIndex = 10;
            label1.Text = "Data Format";
            // 
            // label2
            // 
            label2.AutoSize = true;
            label2.Location = new Point(186, 25);
            label2.Margin = new Padding(5, 0, 5, 0);
            label2.Name = "label2";
            label2.Size = new Size(49, 25);
            label2.TabIndex = 11;
            label2.Text = "Data";
            // 
            // tbdata
            // 
            tbdata.Font = new Font("Segoe UI", 10.2F, FontStyle.Regular, GraphicsUnit.Point);
            tbdata.Location = new Point(186, 54);
            tbdata.Margin = new Padding(4, 3, 4, 3);
            tbdata.Multiline = true;
            tbdata.Name = "tbdata";
            tbdata.Size = new Size(703, 31);
            tbdata.TabIndex = 1;
            // 
            // Form1
            // 
            AutoScaleDimensions = new SizeF(10F, 25F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(1000, 622);
            Controls.Add(label2);
            Controls.Add(label1);
            Controls.Add(cbSHA3);
            Controls.Add(cbSHA1);
            Controls.Add(cbMD5);
            Controls.Add(btnCalculate);
            Controls.Add(tbSHA3);
            Controls.Add(tbSHA1);
            Controls.Add(tbMD5);
            Controls.Add(btnOpenfile);
            Controls.Add(tbdata);
            Controls.Add(comboBoxType);
            Margin = new Padding(4, 3, 4, 3);
            Name = "Form1";
            Text = "Hash Calculate";
            Load += Form1_Load;
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private System.Windows.Forms.ComboBox comboBoxType;
        private System.Windows.Forms.Button btnOpenfile;
        private System.Windows.Forms.TextBox tbMD5;
        private System.Windows.Forms.TextBox tbSHA1;
        private System.Windows.Forms.TextBox tbSHA3;
        private System.Windows.Forms.Button btnCalculate;
        private System.Windows.Forms.CheckBox cbMD5;
        private System.Windows.Forms.CheckBox cbSHA1;
        private System.Windows.Forms.CheckBox cbSHA3;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private TextBox tbdata;
    }
}