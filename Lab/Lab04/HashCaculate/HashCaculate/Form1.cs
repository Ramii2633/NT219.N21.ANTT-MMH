using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Security.Cryptography;
using HashLib;
using static HashLib.HashFactory.Crypto;
using Org.BouncyCastle.Utilities.Encoders;


namespace HashCaculate
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        string md5_output;
        string sha1_output;
        string sha256_output;


        private void btnCalculate_Click(object sender, EventArgs e)
        {
            string input = tbdata.Text;
            switch (comboBoxType.Text.ToString())
            {
                case "Text":
                    md5_output = TextMd5Hash(input);
                    sha1_output = TextSHA1Hash(input);
                    sha256_output = TextSha256Hash(input);
                    break;
                case "Hex":
                    
                    md5_output = HexMd5Hash(ConvertHex(tbdata.Text.Trim().ToUpper()));
                    sha1_output = HexSHA1Hash(ConvertHex(tbdata.Text.Trim().ToUpper()));
                    sha256_output = HexSha256Hash(ConvertHex(tbdata.Text.Trim().ToUpper()));
                    break;
                case "File":
                    //
                    break;
            }
            if (cbMD5.Checked)
                tbMD5.Text = md5_output;
            if (cbSHA1.Checked)
                tbSHA1.Text = sha1_output;
            if (cbSHA3.Checked)
                tbSHA3.Text = sha256_output;
        }

        public static string TextMd5Hash(string message)
        {
            using (MD5 md5 = MD5.Create())
            {
                byte[] input = Encoding.UTF8.GetBytes(message);
                byte[] hash = md5.ComputeHash(input);

                StringBuilder sb = new StringBuilder();
                for (int i = 0; i < hash.Length; i++)
                {
                    sb.Append(hash[i].ToString("X2")); // print in hexadecimal format
                }
                return sb.ToString().ToLower();
            }
        }

        private static int GetHex(char hex)
        {
            return hex <= '9' ? hex - '0' : hex - 'A' + 10;
        }

        private static byte[] ConvertHex(string hex)
        {
           
            if (hex.Length % 2 is not 0)
                throw new ArgumentException("The hexadecimal data cannot have an odd number of digits!");

            var size = hex.Length / 2;
            var result = new byte[size];

            var input = 0;
            for (var i = 0; i < size; ++i)
                result[i] = (byte)((GetHex(hex[input++]) << 4) + GetHex(hex[input++]));

            return result;
        }

        public static string HexMd5Hash(byte[] data)
        {
            var md5 = MD5.Create();
            var bytes = md5.ComputeHash(data);
            var builder = new StringBuilder();
            foreach (var b in bytes)
                builder.Append(b.ToString("x2"));
            return builder.ToString();
        }

        static string TextSHA1Hash(string message)
        {
            using (SHA1Managed sha1 = new SHA1Managed())
            {
                var hash = sha1.ComputeHash(Encoding.UTF8.GetBytes(message));
                var sb = new StringBuilder(hash.Length * 2);

                foreach (byte b in hash)
                {
                    sb.Append(b.ToString("X2"));
                }

                return sb.ToString().ToLower();
            }
        }

        public static string HexSHA1Hash(byte[] data)
        {
            var sha1 = SHA1.Create();
            var bytes = sha1.ComputeHash(data);
            var builder = new StringBuilder();
            foreach (var b in bytes)
                builder.Append(b.ToString("x2"));
            return builder.ToString();
        }

        static string TextSha256Hash(string message)
        {
            var hashAlgorithm = new Org.BouncyCastle.Crypto.Digests.Sha3Digest(256);
            byte[] input = Encoding.ASCII.GetBytes(message);

            hashAlgorithm.BlockUpdate(input, 0, input.Length);

            byte[] result = new byte[32]; // 256 / 8 = 32
            hashAlgorithm.DoFinal(result, 0);

            string hashString = BitConverter.ToString(result);
            hashString = hashString.Replace("-", "").ToLowerInvariant();

            return hashString;
        }

        public static string HexSha256Hash(byte[] data)
        {
            // Tính toán giá trị SHA-3-256 của mảng byte
            var hashAlgorithm = new Org.BouncyCastle.Crypto.Digests.Sha3Digest(256);
            hashAlgorithm.BlockUpdate(data, 0, data.Length);

            byte[] result = new byte[32]; // 256 / 8 = 32
            hashAlgorithm.DoFinal(result, 0);

            // Chuyển đổi mảng byte kết quả thành chuỗi hex
            string hashString = BitConverter.ToString(result);
            hashString = hashString.Replace("-", "").ToLowerInvariant();

            return hashString;
        }


        private void btnOpenfile_Click(object sender, EventArgs e)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            openFileDialog.Filter = "All files (*.*)|*.*"; // show all files

            if (openFileDialog.ShowDialog() == DialogResult.OK)
            {
                string filePath = openFileDialog.FileName;
                tbdata.Text = filePath;
                // Initialize hashing algorithms
                MD5 md5 = MD5.Create();
                SHA1 sha1 = SHA1.Create();
                //SHA256 sha256 = SHA256.Create();
                var sha3 = new Org.BouncyCastle.Crypto.Digests.Sha3Digest(256);
                // Open the file and create a buffer to read data
                using (FileStream stream = new FileStream(filePath, FileMode.Open, FileAccess.Read))
                {
                    byte[] buffer = new byte[4096];
                    int bytesRead;

                    // Read the file in chunks and update the hash values
                    while ((bytesRead = stream.Read(buffer, 0, buffer.Length)) > 0)
                    {
                        md5.TransformBlock(buffer, 0, bytesRead, null, 0);
                        sha1.TransformBlock(buffer, 0, bytesRead, null, 0);
                        //sha256.TransformBlock(buffer, 0, bytesRead, null, 0);
                        sha3.BlockUpdate(buffer, 0, bytesRead);
                    }

                    // Finalize the hash values
                    md5.TransformFinalBlock(buffer, 0, 0);
                    sha1.TransformFinalBlock(buffer, 0, 0);
                    byte[] result = new byte[32]; // 256 / 8 = 32
                    sha3.DoFinal(result, 0);

                    // Convert the hash values to strings and display them
                    if (cbMD5.Checked)
                        tbMD5.Text = BitConverter.ToString(md5.Hash).Replace("-", "").ToLowerInvariant();
                    if (cbSHA1.Checked)
                        tbSHA1.Text = BitConverter.ToString(sha1.Hash).Replace("-", "").ToLowerInvariant();
                    if (cbSHA3.Checked)
                        tbSHA3.Text = BitConverter.ToString(result).Replace("-", "").ToLowerInvariant();
                }
            }
        }


        private void comboBoxType_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (comboBoxType.Text.ToString() == "File")
            {
                btnOpenfile.Enabled = true;
                tbdata.Enabled = false;
            }
            else
                tbdata.Enabled = true;

        }

        private void Form1_Load(object sender, EventArgs e)
        {

            btnOpenfile.Enabled = false;
        }

        private void cbMD5_CheckedChanged(object sender, EventArgs e)
        {
            tbMD5.Visible = cbMD5.Checked;
        }

        private void cbSHA1_CheckedChanged(object sender, EventArgs e)
        {
            tbSHA1.Visible = cbSHA1.Checked;
        }

        private void cbSHA3_CheckedChanged(object sender, EventArgs e)
        {
            tbSHA3.Visible = cbSHA3.Checked;
        }
    }
}