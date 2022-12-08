using System;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Windows.Forms;

namespace TCPSockets {
    public partial class Form1 : Form {
        /************
         * Spremenljivke
         * 
         * 
         * **********/
        // odjemalec/strežnik
        TcpClient client = null;
        TcpListener listener = null;
        IPAddress ip = null;
        int port = 1337;

        // niti
        Thread thClient = null;
        Thread thListener = null;
        
        // podatkovni tok
        NetworkStream dataStream = null;
        

        public Form1() {
            InitializeComponent();
        }

        /*************
         * Strežnik (listener)
         * 
         * ***********/
        private void button1_Click(object sender, EventArgs e) {
            // IP & port
            ip = IPAddress.Parse(textBox1.Text);
            port = Convert.ToInt32(textBox2.Text);

            // nit => sicer vmesnik blokira, ko kličemo AcceptTcpClient()
            thListener = new Thread(new ThreadStart(ListenForConnections));
            thListener.IsBackground = true;
            thListener.Start();
        }

        // ListenForConnections posluša na vratih in sprejema nove odjemalce
        // Ko odjemalca sprejme, obdela njegovo sporočilo
        private void ListenForConnections() {
            listener = new TcpListener(ip, port);
            listener.Start();

            // neskončna zanka, če želimo prejemati več sporočil
            // neskončna zanka zato, ker ne moremo vedeti koliko sporočil bomo prejeli
            while (true) {
                try {
                    client = listener.AcceptTcpClient();    // ta funkcija blokira nit dokler se odjemalec ne poveže (ne pošlje sporočila)

                    // pridobivanje sporočila iz podatkovnega toka
                    dataStream = client.GetStream();    // dobimo podatkovni tok odjemalca in beremo podatke iz njega

                    byte[] message = new byte[1024];
                    dataStream.Read(message, 0, message.Length);
                    dataStream.Close();

                    string strMessage = Encoding.UTF8.GetString(message);
                    MessageBox.Show("Strežnik: Dobil sem sporočilo: " + strMessage);
                }
                // obdelovanje izjem => ko ustavljamo strežnik prožimo izjemo
                catch (Exception ex) {
                    thListener.Join();  // enostavno zaključimo nit z .Join() in ne .Abort()!!!
                }
            }
        }

        // ustavljanje strežnika
        private void button3_Click(object sender, EventArgs e) {
            if (client != null && client.Connected) client.Close(); // če imamo povezanega odjemalca, ta klic proži izjemo v while(true)...
            listener.Stop(); // če nimamo povezanega odjemalca, ta klic proži izjemo v while(true)...
        }

        /**********
         * Odjemalec (client)
         * 
         * ********/
        private void button2_Click(object sender, EventArgs e) {
            ip = IPAddress.Parse(textBox1.Text);
            port = Convert.ToInt32(textBox2.Text);

            // ustvarimo novo povezavo na strežnik v ločeni niti
            // kot parameter si pošljemo TcpClient objekt, da celotno povezavo izvedemo v drugi niti
            // na tak način bi lahko izvedli več simultanih povezav na isti strežnik (recimo za pošiljanje več datotek hkrati, ali pa tudi za izvedbo DDoS napada)
            client = new TcpClient();
            thClient = new Thread(new ParameterizedThreadStart(SendPacket));
            thClient.IsBackground = true;
            thClient.Start(client);
        }

        // nit za pošiljanje sporočila
        private void SendPacket(object pClient) {
            string message = textBox3.Text;

            // spet try-catch blok, da polovimo napake (recimo strežnik offline)
            try {
                client = (TcpClient)pClient; // samo type cast parametra
                client.Connect(ip, port);    // dejanska povezava s strežnikom

                dataStream = client.GetStream(); // pridobivanje podatkovnega toka in pisanje vanj
                byte[] strMessage = Encoding.UTF8.GetBytes(message);
                dataStream.Write(strMessage, 0, strMessage.Length);
                dataStream.Close(); // vedno, VEDNO!!! zapiramo podatkovne toke...
                client.Close();     // ...kot tudi zapremo povezavo, ko smo končali
            }
            // če je bila napaka, jo lahko na uporabniku prijazen način obdelamo
            catch (Exception ex) {
                MessageBox.Show("Odjemalec: Pošiljanje ni bilo uspešno!");
            }
        }
    }
}
