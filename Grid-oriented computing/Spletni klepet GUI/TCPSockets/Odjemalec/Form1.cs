using System;
using System.Threading;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Net.Sockets;
using System.Security.Cryptography;

namespace Odjemalec
{
    public partial class Form1 : Form
    {
        public static bool connected = false;
        const int STD_PORT = 1234;
        const string STD_IP = "127.0.0.1";
        const int STD_MSG_SIZE = 1204;
        string USERNAME="";
        string MESSAGE="";
        string RESPONSE = "";
        const string STD_CRYPTO_KEY = "keyCrypto"; //kljuc za kriptiranje
        TcpClient tcpClient = null;

        Thread thClient = null;
        NetworkStream ns = null;

        static string Recieve(NetworkStream ns)
        { //Pridobim podatkovni tok
            try
            {
                byte[] recv = new byte[STD_MSG_SIZE];
                int length = ns.Read(recv, 0, recv.Length);     //Berem iz podatkovnega toka, poskusam prebrati sporocilo, ce vticnice ni, potem ni podatkovnega toka in je NULL
                //Read caka tako dolgo, dokler ne dobi nekega sporocila
                return Encoding.UTF8.GetString(recv, 0, length);
            }
            catch (Exception ex)
            {
                Console.WriteLine("Napaka pri prejemanju!\n" + ex.Message + "\n" + ex.StackTrace);
                return null;
            }
        }   //Pridobim sprocilo

        static void Send(NetworkStream ns, string message)
        {
            try
            {
                byte[] send = Encoding.UTF8.GetBytes(message.ToCharArray(), 0, message.Length);
                ns.Write(send, 0, send.Length);
            }
            catch (Exception ex)
            {
                Console.WriteLine("Napaka pri posiljanju!\n" + ex.Message + "\n" + ex.StackTrace);
            }
        } //Posljem sporocilo

        public static string Decrypt(string message)
        {
            try
            {
                byte[] DecryptedArray = Convert.FromBase64String(message); //pretvorim sporocilo v array
                MD5CryptoServiceProvider MD5Service = new MD5CryptoServiceProvider();   //Ustvarim MD5 Storitev
                                                                                        //MD5 je algoritem za prebavo sporocil, proizvaja 128-bitno zgosceno vrednost -> 128bit hash value

                byte[] CryptoKey = MD5Service.ComputeHash(UTF8Encoding.UTF8.GetBytes(STD_CRYPTO_KEY)); //pretvorim kljuc v array
                                                                                                       //MD5Service.ComputeHash vrne hash array, za podan niz bajtov

                MD5Service.Clear(); //Sprosti vse vire, ki jih uporablja

                //Ustvarim TripleDES storitev
                TripleDESCryptoServiceProvider tDES = new TripleDESCryptoServiceProvider();     //TripleDES je tip enkripcije, ki jo bomo uporabili pri tej nalogi
                tDES.Key = CryptoKey;   //Nastavim skriti kljuc, ki sem ga pridobil zgoraj

                tDES.Mode = CipherMode.ECB; //Nastavim nacin za delovanje simetricnega algoritma, v mojem primeru na ECB
                                            //SO pa se moznosti: CBC -> Default, CFB, CTS, OFB
                tDES.Padding = PaddingMode.PKCS7;

                var Decriptor = tDES.CreateDecryptor(); //Ustvarim simetricni desifrirni objekt

                byte[] rezultatArray = Decriptor.TransformFinalBlock(DecryptedArray, 0, DecryptedArray.Length);

                tDES.Clear(); //Sprosti vse vire, ki jih uporablja
                return UTF8Encoding.UTF8.GetString(rezultatArray); //array pretvorim v string
            }
            catch(Exception ex)
            {
                MessageBox.Show("Napaka pri odjemalcu!");
                return null;
            }

            
        }  //Dekriptiram podatke

        public static string Encrypt(string message)
        {
            byte[] EncryptedArray = UTF8Encoding.UTF8.GetBytes(message);
            MD5CryptoServiceProvider MD5Service = new MD5CryptoServiceProvider();   //Ustvarim MD5 Storitev
                                                                                    //MD5 je algoritem za prebavo sporocil, proizvaja 128-bitno zgosceno vrednost -> 128bit hash value

            byte[] CryptoKey = MD5Service.ComputeHash(UTF8Encoding.UTF8.GetBytes(STD_CRYPTO_KEY)); //pretvorim kljuc v array
            //MD5Service.ComputeHash vrne hash array, za podan niz bajtov

            MD5Service.Clear(); //Sprosti vse vire, ki jih uporablja

            //Ustvarim TripleDES storitev
            TripleDESCryptoServiceProvider tDES = new TripleDESCryptoServiceProvider();     //TripleDES je tip enkripcije, ki jo bomo uporabili pri tej nalogi
            tDES.Key = CryptoKey;   //Nastavim skriti kljuc, ki sem ga pridobil zgoraj

            tDES.Mode = CipherMode.ECB; //Nastavim nacin za delovanje simetricnega algoritma, v mojem primeru na ECB
            //SO pa se moznosti: CBC -> Default, CFB, CTS, OFB
            tDES.Padding = PaddingMode.PKCS7;

            var Encriptor = tDES.CreateEncryptor(); //Ustvarim simetricni sifrirni objekt

            byte[] rezultatArray = Encriptor.TransformFinalBlock(EncryptedArray, 0, EncryptedArray.Length);

            tDES.Clear(); //Sprosti vse vire, ki jih uporablja

            return Convert.ToBase64String(rezultatArray, 0, rezultatArray.Length); //array pretvorim v string
        } //Kriptiram podatke

        public Form1()
        {
            InitializeComponent();
            button2.Enabled = false;
            button3.Enabled = false;

        }
        private void button1_Click(object sender, EventArgs e)
        {
            USERNAME = uporabnikNameInput.Text; //Pridobim ime uporabnika
            if (USERNAME.Length > 0)
            {
                uporabnikNameInput.Enabled = false; //Ne morem sprementii imena
                btnPovezi.Enabled = false;  //Ne morem klikniti gumba za povezat
                button2.Enabled = true; //Lahko kliknem gumb prekini
                button3.Enabled = true; //Lahko kliknem gumb poslji

            }
            try
            {
                tcpClient = new TcpClient();  //Ustvarim nov TcpClient
                tcpClient.Connect(STD_IP, STD_PORT); //Povezem se na streznik
                ns = tcpClient.GetStream();         //Pridobim tok odjemalca
                connected = true;                   //Uporabim pri neskoncnem while loopu
                Send(ns, Encrypt("J" + USERNAME));           //Na streznik posljem sporocilo
                thClient = new Thread(new ParameterizedThreadStart(ConnectClient)); //Zazenem novo nit
                thClient.IsBackground = true;
                try
                {
                    thClient.Start();
                }
                catch (Exception ex)
                {
                    MessageBox.Show("Napaka pri odjemalcu!");
                }
                if (connected == false)
                {
                    thClient.Join();
                }

            }
            catch (Exception ex)
            {
                textBox.Items.Add("Napaka: " + ex.Message + "\n" + ex.StackTrace);
                connected = false;
            }
        } //Povezi btn ---> Povezem se na streznik

        private void ConnectClient(object pClient) //Ko sem povezan na streznik
        {
            while (connected)                       //Neskoncna zanka saj cakam na streznik da poslje sporocilo
            {
              string response = Recieve(ns); //Pridobim sporocilo
               if(response != "")
                   response = Decrypt(response);
                textBox.Invoke(new Action(() => { //Ker dostopam do elementov izven niti
                    try
                    {
                        textBox.Items.Add(response);
                        textBox.TopIndex = textBox.Items.Count - 1;
                    }catch(Exception ex)
                    {
                        MessageBox.Show("Napaka pri odjemalcu!");
                    }
                    }
                ));
            }
        }
       
        private void button3_Click(object sender, EventArgs e)  //Poslji btn ---> Posiljanje sporocil
        {
            MESSAGE = textBox1.Text; //Pridobim kaj je uporabnik napisal
            textBox1.Clear();           //Pocitstim vnosno okno
            if (MESSAGE[0] == '#') //Ce napise #GAMESTART / #GAMESTOP
            {
                Send(ns, Encrypt(MESSAGE)); //Posljem za zacetek igre
            }
            else
            {
                Send(ns, Encrypt("M" + USERNAME + ": " + MESSAGE)); //Posljem kdo posilja in kaj posilja
            }

            
        }
       
        private void button2_Click(object sender, EventArgs e)
        {
            connected = false; //Izklopim neskoncno zanko
            Send(ns, Encrypt("L" + USERNAME)); //Poslje na streznik da se zeli odklopit
            uporabnikNameInput.Enabled = true;
            btnPovezi.Enabled = true; //Lahko spet kliknem gumb povezi
            button2.Enabled = false;   //Ne morem kliknit povezi gumba
            button3.Enabled = false;    //Ne morem kliknit poslji gumba
            uporabnikNameInput.Clear(); //Pocistim input box
            textBox.Items.Clear();
            tcpClient.Close();
            //Application.Exit();         //Zaprem okno uporabnika

        } //Prekini btn ---> Odklop

        private void textBox3_TextChanged(object sender, EventArgs e)
        {

        }

        private void uporabnikNameInput_TextChanged(object sender, EventArgs e)
        {

        }

        private void listBox1_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void textBox_SelectedIndexChanged(object sender, EventArgs e)
        {
           
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {
            
        }

        private void richTextBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void label1_Click(object sender, EventArgs e)
        {

        }
    }
}
