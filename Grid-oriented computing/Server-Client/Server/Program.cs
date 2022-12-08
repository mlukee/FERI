using System;
using System.Net;
using System.Net.Sockets;
using System.Security.Cryptography;
using System.Text;
using FenParse;

namespace Server
{
    class Program
    {
        #region Konstante
        const int STD_PORT = 1234;          //standardni port
        const string STD_IP = "127.0.0.1";  //standardni IP -> localhost
        const int STD_MSG_SIZE = 1024;      //velikost paketa -> 1kB
        const int STD_HEAD_LEN = 1;         //glava velikosti 1 -> ena crka
        const string STD_CRYPTO_KEY = "keyCrypto";

        static bool run = true;             //neskoncna while zanka
        #endregion

        //Prejemanje
        static string Recieve(NetworkStream ns){ //Pridobim podatkovni tok
            try
            {
                byte[] recv = new byte[STD_MSG_SIZE];
                int length = ns.Read(recv, 0, recv.Length);     //Berem iz podatkovnega toka, poskusam prebrati sporocilo, ce vticnice ni, potem ni podatkovnega toka in je NULL
                //Read caka tako dolgo, dokler ne dobi nekega sporocila
                return Encoding.UTF8.GetString(recv, 0, length);
            }
            catch(Exception ex)
            {
                Console.WriteLine("Napaka pri prejemanju!\n" + ex.Message + "\n" + ex.StackTrace);
                return null;
            }
        }
        static void Send(NetworkStream ns, string message)
        {
            try
            {
                byte[] send = Encoding.UTF8.GetBytes(message.ToCharArray(), 0, message.Length);
                ns.Write(send, 0, send.Length);                
            }
            catch(Exception ex)
            {
                Console.WriteLine("Napaka pri posiljanju!\n" + ex.Message + "\n" + ex.StackTrace);
            }
        }

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
        }
        static void Main(string[] args)
        {
            TcpListener listener = new TcpListener(IPAddress.Parse(STD_IP), STD_PORT); //instanciram TCPListener z IP-jem in PORT-om
            listener.Start();                                                          //V metodi Start se klice Socket, Bind in Listen

            Console.WriteLine("Streznik\nPoslusam na naslovu " + STD_IP + ": " + STD_PORT.ToString());
            while (run) { //Run je na TRUE -> neskoncna zanka
                using (TcpClient client = listener.AcceptTcpClient())
                using (NetworkStream ns = client.GetStream()) { //GetStream() dobim podatkovni tok do odjemalca
                    Console.WriteLine("Odjemalec se je povezal (" + client.Client.RemoteEndPoint.ToString() + ")"); //RemoteEndPoint -> pridobim IP odjemalca

                    string message = Recieve(ns);

                    Console.WriteLine("Dobil sem sporocilo: " + message);
                    string response = "";
                    
                    #region Protokol
                    string head = message[0].ToString();
                    string body = "";
                    if (message.Length > 1) body = message.Substring(STD_HEAD_LEN, message.Length - 1);

                    switch (head)
                    {
                        case "A": //Pozdrav
                            response = "Pozdravljen " + client.Client.RemoteEndPoint.ToString();
                            break;
                        case "B": //Trenutni cas
                            response = "Trenutni cas je: " + DateTime.Now.ToString("dd. MM. yyyy, H:mm");
                            break;
                        case "C": //Direktorij
                            response = Environment.CurrentDirectory;
                            break;
                        case "D": //Sporocilo ki sem ga prejel
                            response = message.Substring(1, message.Length - 1).ToString();
                            break;
                        case "E": //Sistemske informacije
                            response = "Ime racunalnika: " + Environment.MachineName + "\nVerzija OS: " + Environment.OSVersion.ToString();
                            break;
                        case "F": //obdelava in lep izpis Forsyth-Edwards notacije (FEN) 
                            try
                            {
                                message = message.Remove(0, 1); //odstranim glavo -> F
                                /*https://github.com/alexqfredrickson/FenParser */
                                var parser = new FenParser(message);
                                response += parser.BoardStateData.ToConsole();
                            }
                            catch(Exception ex)
                            {
                                Console.WriteLine("NAPAKA! " + ex.Message + "\n");
                                response = "NAPAKA! " + ex.Message + "\n";
                            }                            
                            break;
                        case "G": //Sifriranje
                            message = message.Remove(0, 1); //odstranim glavo -> G
                            response = Encrypt(message);
                            break;
                    }
                    #endregion

                    Send(ns, response); //Spremenljivko reponse posljemo na podatkovni tok
                    Console.WriteLine("Odgovoril sem: " + response);
                }
                Console.WriteLine("Odjemalec se je odklopil.\n");
            }
            listener.Stop();        //vgasnemo vticnico streznika
            Console.WriteLine("Streznik je ustavljen.");
            Console.ReadKey();
        }
    }
}
