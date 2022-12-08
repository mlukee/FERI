namespace Odjemalec
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
            this.components = new System.ComponentModel.Container();
            this.btnPovezi = new System.Windows.Forms.Button();
            this.contextMenuStrip1 = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.eventLog1 = new System.Diagnostics.EventLog();
            this.UporabnikLabel = new System.Windows.Forms.Label();
            this.uporabnikNameInput = new System.Windows.Forms.TextBox();
            this.button2 = new System.Windows.Forms.Button();
            this.label2 = new System.Windows.Forms.Label();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.button3 = new System.Windows.Forms.Button();
            this.textBox = new System.Windows.Forms.ListBox();
            ((System.ComponentModel.ISupportInitialize)(this.eventLog1)).BeginInit();
            this.SuspendLayout();
            // 
            // btnPovezi
            // 
            this.btnPovezi.Location = new System.Drawing.Point(186, 17);
            this.btnPovezi.Name = "btnPovezi";
            this.btnPovezi.Size = new System.Drawing.Size(75, 23);
            this.btnPovezi.TabIndex = 1;
            this.btnPovezi.Text = "Poveži";
            this.btnPovezi.UseVisualStyleBackColor = true;
            this.btnPovezi.Click += new System.EventHandler(this.button1_Click);
            // 
            // contextMenuStrip1
            // 
            this.contextMenuStrip1.Name = "contextMenuStrip1";
            this.contextMenuStrip1.Size = new System.Drawing.Size(61, 4);
            // 
            // eventLog1
            // 
            this.eventLog1.SynchronizingObject = this;
            // 
            // UporabnikLabel
            // 
            this.UporabnikLabel.AutoSize = true;
            this.UporabnikLabel.Location = new System.Drawing.Point(12, 22);
            this.UporabnikLabel.Name = "UporabnikLabel";
            this.UporabnikLabel.Size = new System.Drawing.Size(62, 13);
            this.UporabnikLabel.TabIndex = 4;
            this.UporabnikLabel.Text = "Uporabnik: ";
            this.UporabnikLabel.Click += new System.EventHandler(this.label1_Click);
            // 
            // uporabnikNameInput
            // 
            this.uporabnikNameInput.Location = new System.Drawing.Point(80, 19);
            this.uporabnikNameInput.Name = "uporabnikNameInput";
            this.uporabnikNameInput.Size = new System.Drawing.Size(100, 20);
            this.uporabnikNameInput.TabIndex = 5;
            this.uporabnikNameInput.TextChanged += new System.EventHandler(this.uporabnikNameInput_TextChanged);
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(412, 16);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(75, 23);
            this.button2.TabIndex = 6;
            this.button2.Text = "Prekini";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(9, 303);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(54, 13);
            this.label2.TabIndex = 8;
            this.label2.Text = "Sporočilo:";
            // 
            // textBox1
            // 
            this.textBox1.Location = new System.Drawing.Point(66, 300);
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new System.Drawing.Size(340, 20);
            this.textBox1.TabIndex = 9;
            this.textBox1.TextChanged += new System.EventHandler(this.textBox1_TextChanged);
            // 
            // button3
            // 
            this.button3.Location = new System.Drawing.Point(412, 298);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(75, 23);
            this.button3.TabIndex = 10;
            this.button3.Text = "Pošlji";
            this.button3.UseVisualStyleBackColor = true;
            this.button3.Click += new System.EventHandler(this.button3_Click);
            // 
            // textBox
            // 
            this.textBox.FormattingEnabled = true;
            this.textBox.Location = new System.Drawing.Point(12, 45);
            this.textBox.Name = "textBox";
            this.textBox.Size = new System.Drawing.Size(475, 238);
            this.textBox.TabIndex = 11;
            this.textBox.SelectedIndexChanged += new System.EventHandler(this.textBox_SelectedIndexChanged);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(499, 333);
            this.Controls.Add(this.textBox);
            this.Controls.Add(this.button3);
            this.Controls.Add(this.textBox1);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.uporabnikNameInput);
            this.Controls.Add(this.UporabnikLabel);
            this.Controls.Add(this.btnPovezi);
            this.Name = "Form1";
            this.Text = "Form1";
            ((System.ComponentModel.ISupportInitialize)(this.eventLog1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.Button btnPovezi;
        private System.Windows.Forms.ContextMenuStrip contextMenuStrip1;
        private System.Diagnostics.EventLog eventLog1;
        private System.Windows.Forms.Label UporabnikLabel;
        private System.Windows.Forms.TextBox uporabnikNameInput;
        private System.Windows.Forms.Button button3;
        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.ListBox textBox;
    }
}

