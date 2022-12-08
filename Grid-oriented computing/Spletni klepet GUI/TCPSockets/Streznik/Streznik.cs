using System;
using System.Threading;
using System.Net;
using System.Net.Sockets;
using System.Security.Cryptography;
using System.Text;

namespace Server
{
    class Streznik
    {
        #region Konstante
        static Thread thListener;
        static TcpListener listener = null;
        static TcpClient client = null;
        static NetworkStream ns = null;

        const int STD_PORT = 1234;          //standardni port
        const string STD_IP = "127.0.0.1";  //standardni IP -> localhost
        const int STD_MSG_SIZE = 1024;      //velikost paketa -> 1kB
        const int STD_HEAD_LEN = 1;         //glava velikosti 1 -> ena crka
        const string STD_CRYPTO_KEY = "keyCrypto"; //kljuc za kriptiranje

        
        static List<(NetworkStream, string)> clients = new List<(NetworkStream, string)>();  //polje pridruzenih odjemalcev
        static List<int> rezultati = new List<int>();                                       //polje za shranjevanje rezultatov odjemalcev pri igri
        static List<string> besede = new List<string> {"modem", "utf8", "wifi", "bluetooth", "router", "povezava"}; //besede za igro

        static bool run = true;             //zastavica za neskoncno while zanko
        static bool playGame = false;
        static int index = 0; //Index random besede
        static string randWord = "";


        #endregion

        //Prejemanje
        public static string Recieve(NetworkStream ns)
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
        }
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
        }

        public static void BroadCast(string message)
        {
            foreach(var client in clients)              //Sprehodim se cez polje pridruzenih odjemalcev
            {
                Send(client.Item1, message);            //Vskakemu odjemalcu posljem sporocilo
            }
        }

        public static void ClientDisconnect(NetworkStream ns, string message)
        {
            foreach(var client in clients)          //Sprehodim se cez polje pridruzenih odjemalcev
            {
                if(client.Item1 == ns)              //Odjemalec ki se zeli odklopiti
                {
                    clients.Remove(client);//odjemalca odstranim iz polja odjemalcev
                    BroadCast(Encrypt($"{message} je zapustil klepet."));    //izpisem kdo je zapustil klepet
                                                                 
                    client.Item1.Close();                           //Zaprem povezavo z odjemalcem
                    thListener.Join();                              //Zdruzim nit z glavno nitjo
                }
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

        public static string Decrypt(string message)
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

        static void Main(string[] args)
        {

            listener = new TcpListener(IPAddress.Parse(STD_IP), STD_PORT); //instanciram TCPListener z IP-jem in PORT-om
            listener.Start();                                               //Zazenem streznik, kateri zacne poslusati za odjemalce
            Console.WriteLine("Streznik\nPoslusam na naslovu " + STD_IP + ": " + STD_PORT.ToString());
            while (true)
            {
                try {
                   
                    TcpClient client = listener.AcceptTcpClient();  //Sprejmem povezavo z odjemalcem
                    Console.WriteLine("Sprejel novo povezavo...");
                    NetworkStream ns = client.GetStream();              //Pridobim podatkovni tok
                    thListener = new Thread(() => ParseRequest(ns));     //Ustvarim novo nit in klicem funkcijo za parsanje sporocila
                   // thListener.IsBackground = true;
                    thListener.Start();                                     //Zazenem nit

                }
                catch(Exception ex)
                {
                   thListener.Join();
                }
            }
        } //Main funckija

        private static string getRandomWord() //Funkcija, s katero izberem nakljucno besedo za igranje igre
        {
            var random = new Random();
            index = random.Next(0, besede.Count);  //izberem besedo iz polja besed med 0 in stevilom besed v polju
            string randomWord = besede[index];    //shranim besedo
            string returnRandomWord = "";
            for(int i = 0; i < randomWord.Length; i++)  //Vsako drugo crko besede spremenim v _
            {
                if (i % 2 == 0)
                    returnRandomWord+= "_";
                else returnRandomWord+= randomWord[i];
            }

            return returnRandomWord;  //Vrnem skrito besedo
        }

        private static int getPlayer(NetworkStream ns)  // Funkcija s katero pridobim index igralca
        {
            for(int i = 0; i< clients.Count; i++)
            {
                if (clients[i].Item1 == ns) return i;
            }
            return -1;
        }

        private static void startGame(NetworkStream ns, string zacetnik = "")  //Funkcija s katero zacnem igro
        {
            string kdoJeZacel = "";
            if (zacetnik == "")
            {
                foreach (var client in clients)  //Pridobim kdo je zacel igro
                {
                    if (client.Item1 == ns)
                    {
                        kdoJeZacel = client.Item2;
                    }
                }
            } else kdoJeZacel = zacetnik;
            BroadCast(Encrypt(kdoJeZacel + " je zacel igro ugibanja besed!"));
            randWord = getRandomWord();                 //Izberem nakljucno besedo
            BroadCast(Encrypt("Ugani besedo: " + randWord));
        }

        private static void playingGame(string guess, int player)
        {
            string uganil = "";
            if (guess == besede[index])   //Ce igralec ugane skrito besedo
            { 
                rezultati[player] += 1;  //Igralec pridobi tocko
                
                BroadCast(Encrypt(clients[player].Item2 + " je uganil besedo in dobil 1 tocko! Cestitke!")); //Posljem vsem sporocilo
                BroadCast(Encrypt("Rezultati: "));
                System.Threading.Thread.Sleep(150);
                for (int i = 0; i< clients.Count; i++)
                {
                    BroadCast(Encrypt(clients[i].Item2 + " - " + rezultati[i]));  //Izpisem tocke posameznega odjemalca
                    System.Threading.Thread.Sleep(150);
                }
                                
                startGame(ns, clients[player].Item2);
               // playGame = false;  //Ce je uganil besedo, zakljucim igro
            }
            else
            {
                BroadCast(Encrypt("Napacen poskus " + clients[player].Item2 + ": " + guess)); //Ce ni uganil izpisem
                BroadCast(Encrypt("Ugani besedo: " + randWord));
            }
        }

        private static void ParseRequest(NetworkStream ns, string message="")  //Pridobim sporocilo
        {
            try
            {
                if (message == "") //Ko prvic klicem receive
                {
                  //  message = Recieve(ns); //Pridobim celotno sporocilo od odjemalca
                    message = Decrypt(Recieve(ns));
                }
                       
                    string response = "";
                if (message != "" && message != null)
                {
                    string head = message[0].ToString(); //Pogledam ali je J -> join, M -> message ali # -> igra
                    string body = "";
                    if (message.Length > 1) body = message.Substring(STD_HEAD_LEN, message.Length - 1); //v body shranem telo sporocila

                    if (playGame) //Ce odjemalci igrajo igro
                    {
                        Console.WriteLine("RECV: " + message);
                        if (message == "#GAMESTOP") //Ce zelijo igro zaustavit
                        {
                            string kdoJeKoncal = "";
                            foreach (var client in clients) //Kdo zeli zaustavit
                            {
                                if (client.Item1 == ns)
                                {
                                    kdoJeKoncal = client.Item2;
                                }
                            }
                            playGame = false;
                            BroadCast(Encrypt(kdoJeKoncal+" je koncal igro."));
                        }
                        else
                        {
                            body = message.Substring(message.IndexOf(' ') + 1); //Beseda ki jo poda uporabnik
                            playingGame(body, getPlayer(ns));                   //Pogledam ce je uganil ali ne
                            return; //Da ne grem v switch in se enkrat posljem sporocila ki ga je poslal
                        }
                    }

                    switch (head)
                    {
                        case "J": //Ce se uporabnik zeli pridruzit
                            Console.WriteLine("RECV: " + message);
                            response = "Pripravljen na spletni klepet (" + STD_IP + ":" + STD_PORT + ")...\n";
                            clients.Add((ns, body));  //Odjemalca dodam v polje odjemalcev
                            rezultati.Add(0);           //Rezultat mu nastavim na 0

                            Send(ns, Encrypt(response)); //Posljem uporabniku "Pripravljen na spletni klepet....."
                            BroadCast(Encrypt(body + " se je pridruzil klepetu!")); //Vsem ostalim posljem

                            break;
                        case "M": //Ce je uporabnik poslal navadno sporocilo
                            Console.WriteLine("RECV: " + message);
                            response = body.Substring(STD_HEAD_LEN, body.Length - 1); //Pridobim kaj je poslal
                            BroadCast(Encrypt(body)); //Posljem vsem uporabnikom
                            break;
                        case "L": //Ce uporabnik zapusti klepet
                            Console.WriteLine("RECV: " + message); //Izpisem na streznik
                            Console.WriteLine("Odjemalec se je odklopil.\n");
                            ClientDisconnect(ns, body); //Klicem funkcijo katera odstrani uporabnika in poslje vsem da se je uporabnik odklopil
                            break;
                        case "#":       //Ce zelijo igrati igro
                            Console.WriteLine("RECV: " + message);
                            if (message == "#GAMESTART") //Startam igro
                            {
                                playGame = true;
                                startGame(ns);
                            }
                            break;

                    }
                }
                }
                catch (Exception ex)
                {
                   thListener.Join();
                   client.Close();
                }
            while (true)//Poslusam oz cakam na nova sporocila
            {
                try
                {
                    string newMessage = Decrypt(Recieve(ns));
                    ParseRequest(ns, newMessage);
                }catch (Exception ex)
                {
                    Console.WriteLine(ex.ToString());
                }
               
            }
                       
        }
    }
}