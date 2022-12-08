using System;
using System.Net.Sockets;
using System.Security.Cryptography;
using System.Text;

namespace TCPSockets
{

    static class Program
    {
        #region Konstante
        const int STD_PORT = 1234;          //standardni port
        const string STD_IP = "127.0.0.1";  //standardni IP -> localhost
        const int STD_MSG_SIZE = 1024;      //velikost paketa -> 1kB
        const int STD_HEAD_LEN = 1;         //glava velikosti 1 -> ena crka
        const string STD_CRYPTO_KEY = "keyCrypto";

        static bool run = true;             //neskoncna while zanka
        #endregion //Enake kot pri Strezniku

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
        }           //Funkcija za pridobitev podatkov iz streznika

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
        } //Funkcija za posiljanje podatkov na streznik

        static void Help()
        {
            Console.WriteLine("Ukazi:");
            Console.WriteLine("A -> Posljes pozdrav");
            Console.WriteLine("B -> Trenutni cas");
            Console.WriteLine("C -> Direktorij");
            Console.WriteLine("D -> Sporocilo, ki ga je pravkar prejel");
            Console.WriteLine("E -> Sistemske informacije(ime racunalnika in verzija OS");
            Console.WriteLine("F -> Obdelava in lep izpis Forsyth-Edwards notacije (FEN) ");
            Console.WriteLine("G -> sifriranje sporočila s TripleDES algoritmom");
            Console.WriteLine("q -> Quit\n");
        } //Funkcija, katera izpise katere ukaze imam na voljo

        public static string Decrypt(string message)
        {
            //Pomagal sem si z: https://www.codeguru.com/csharp/triple-des-encryption-and-decryption-in-c/
            byte[] DecryptedArray = Convert.FromBase64String(message); //Sporocilo pretvorim v array
            MD5CryptoServiceProvider MD5Service = new MD5CryptoServiceProvider(); //ustvarim MD5 Storitev
            //MD5 je algoritem za prebavo sporocil, proizvaja 128-bitno zgosceno vrednost -> 128bit hash value
            byte[] CryptoKey = MD5Service.ComputeHash(UTF8Encoding.UTF8.GetBytes(STD_CRYPTO_KEY)); //pretvorim kljuc v array
            //MD5Service.ComputeHash vrne hash array, za podan niz bajtov

            MD5Service.Clear(); //Sprosti vse vire, ki jih uporablja

            //Ustvarim TripleDES storitev
            TripleDESCryptoServiceProvider tDES = new TripleDESCryptoServiceProvider(); //TripleDES je tip enkripcije, ki jo bomo uporabili pri tej nalogi
            
            tDES.Key = CryptoKey; //Nastavim skriti kljuc, ki sem ga pridobil zgoraj

            tDES.Mode = CipherMode.ECB; //Nastavim nacin za delovanje simetricnega algoritma, v mojem primeru na ECB
            //SO pa se moznosti: CBC -> Default, CFB, CTS, OFB

            tDES.Padding = PaddingMode.PKCS7;

            var Decriptor = tDES.CreateDecryptor(); //Ustvarim simetricni desifrirni objekt

            byte[] rezultatArray = Decriptor.TransformFinalBlock(DecryptedArray, 0, DecryptedArray.Length);

            tDES.Clear(); //Sprosti vse vire, ki jih uporablja

            return UTF8Encoding.UTF8.GetString(rezultatArray); //kodiranje UTF-8 znakov UNICODE
        }
        static void Main()
        {
            Console.WriteLine("Odjemalec");
            while (run) //Neskoncna zanka, da lahko vpisujem vec ukazov
            {
                Help(); //Izpis pomoci za ukaze
                Console.Write("\nVnesi ukaz: ");
                string cmd = Console.ReadLine();

                if (cmd == "q") break;  //Ce je ukaz q se odjemalec odklopi

                try
                {
                    TcpClient client = new TcpClient();
                    client.Connect(STD_IP, STD_PORT);

                    NetworkStream ns = client.GetStream();
                    Send(ns, cmd);
                    string response = Recieve(ns);      //Cakamo na odgovor

                    if (cmd[0] == 'G')
                    {
                        response += " => " + Decrypt(response); //Pridobim sifrirano sporocilo in ga hkrati desifriram
                    }

                    Console.WriteLine("Streznik vraca:\n" + response);
                }
                catch (Exception ex)
                {
                    Console.WriteLine("Napaka: " + ex.Message + "\n" + ex.StackTrace); //Ce pride do napake jo izpisem
                }
            }
            Console.WriteLine("Pritisni poljubno tipko za zakljucek programa...");
            Console.ReadKey();
        }
    }
}
