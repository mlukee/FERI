using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;

namespace FenParse.Models
{
    /// <summary>
    /// Contains data about the board state.
    /// </summary>
    public class BoardStateData
    {
        #region Fields
        /// <summary>
        /// The color of the active player.
        /// </summary>
        public string ActivePlayerColor = String.Empty;

        /// <summary>
        /// The square which is currently available for "en passant" capture ('-' if a square is not available).  
        /// </summary>
        public string EnPassantSquare { get; set; }

        /// <summary>
        /// A list of ranks (reversed; from rank #8 to rank #1)
        /// </summary>
        public string[][] Ranks = new string[8][];

        /// <summary>
        /// White's kingside castling availability.
        /// </summary>
        public bool WhiteCanKingsideCastle { get; set; }

        /// <summary>
        /// White's queenside castling availability.
        /// </summary>
        public bool WhiteCanQueensideCastle { get; set; }

        /// <summary>
        /// Black's kingside castling availability.
        /// </summary>
        public bool BlackCanKingsideCastle { get; set; }

        /// <summary>
        /// Black's queenside castling availability.
        /// </summary>
        public bool BlackCanQueensideCastle { get; set; }

        /// <summary>
        /// The game's halfmove counter, used to determine a draw.
        /// </summary>
        public int HalfMoveCounter { get; set; }

        /// <summary>
        /// The game's move number.
        /// </summary>
        public int FullMoveNumber { get; set; }

        #endregion

        #region Methods
        /// <summary>
        /// Parses a FEN substring containing piece placement data into a matrix of ranks.
        /// </summary>
        /// <param name="piecePlacementString"></param>
        /// <returns></returns>
        private void ParseRanks(string piecePlacementString)
        {
            string[] piecePlacementRanksArray = piecePlacementString.Split('/');

            for (int i = 0; i < piecePlacementRanksArray.Length; i++) 
            {
                piecePlacementRanksArray[i] = SanitizeRank(piecePlacementRanksArray[i]);
            }

            for (int i = 0; i < piecePlacementRanksArray.Length; i++)
            {
                string[] allRanks = Array.ConvertAll(piecePlacementRanksArray[i].ToCharArray(), x => x.ToString());
                string[] newRank = new string[8];

                for (int j = 0; j < allRanks.Length; j++)
                {
                    string thisSquare = allRanks[j];

                    int n;
                    if (int.TryParse(thisSquare, out n))
                    {
                        int nullSquareCount = int.Parse(thisSquare);

                        for (int k = 0; k < nullSquareCount; k++)
                        {
                            newRank[j] = String.Empty;
                        }
                    }
                    else
                    {
                        newRank[j] = thisSquare;
                    }
                }

                Ranks[i] = newRank;
            }
        }

        /// <summary>
        /// Sanitizes a rank string by replacing instances of integers with same-length blank substrings.
        /// </summary>
        /// <returns></returns>
        private string SanitizeRank(string rank)
        {
            Regex r = new Regex(@"[\d]+");
            Match m = r.Match(rank);

            while (m.Success)
            {
                StringBuilder sb = new StringBuilder(rank);

                int index = m.Index;
                int nullSquareCount = int.Parse(m.Value);
                string newSubstring = String.Empty;

                for (int j = 0; j < nullSquareCount; j++)
                {
                    newSubstring += " ";
                }

                sb.Remove(index, 1);
                sb.Insert(index, newSubstring);
                rank = sb.ToString();
                m = r.Match(rank);
            }

            return rank;
        }

        /// <summary>
        /// Parses a FEN substring containing active player data.
        /// </summary>
        /// <param name="activeColorSubstring"></param>
        /// <returns></returns>
        private void ParseActiveColor(string activeColorSubstring)
        {
            if (activeColorSubstring.ToLower() == "b")
            {
                ActivePlayerColor = Constants.ActivePlayerColor.Black;
            }
            else if (activeColorSubstring.ToLower() == "w")
            {
                ActivePlayerColor = Constants.ActivePlayerColor.White;
            }
        }

        /// <summary>
        /// Parses a FEN substring containing black's and white's queenside/kingside castling availability.
        /// </summary>
        /// <param name="castlingAvailabilityString"></param>
        private void ParseCastlingAvailability(string castlingAvailabilityString)
        {
            BlackCanKingsideCastle = false;
            BlackCanQueensideCastle = false;
            WhiteCanKingsideCastle = false;
            WhiteCanQueensideCastle = false;

            if (castlingAvailabilityString == "-")
            {
                return; // nobody can castle
            }
            else
            {
                if (castlingAvailabilityString.Contains("K"))
                {
                    WhiteCanKingsideCastle = true;
                }

                if (castlingAvailabilityString.Contains("k"))
                {
                    BlackCanKingsideCastle = true;
                }

                if (castlingAvailabilityString.Contains("Q"))
                {
                    WhiteCanQueensideCastle = true;
                }

                if (castlingAvailabilityString.Contains("q"))
                {
                    BlackCanQueensideCastle = true;
                }
            }
        }

        /// <summary>
        /// Parses a FEN substring containing data about the potentially eligible en-passant square.
        /// </summary>
        /// <param name="enPassantSquareString"></param>
        private void ParseEnPassantSquare(string enPassantSquareString)
        {
            if (enPassantSquareString == "-")
            {
                EnPassantSquare = String.Empty;
            }
            else if (!String.IsNullOrEmpty(enPassantSquareString))
            {
                EnPassantSquare = enPassantSquareString;
            }
        }

        /// <summary>
        /// Parses a FEN substring containing data about the halfmove counter.
        /// </summary>
        /// <param name="halfmoveClockString"></param>
        private void ParseHalfMoveCounter(string halfmoveClockString)
        {
            HalfMoveCounter = int.Parse(halfmoveClockString);
        }

        /// <summary>
        /// Parses a FEN substring containing data about the move number.
        /// </summary>
        /// <param name="fullmoveNumberString"></param>
        private void ParseFullmoveNumber(string fullmoveNumberString)
        {
            FullMoveNumber = int.Parse(fullmoveNumberString);
        }

        /// <summary>
        /// Prints a graphical representation of the board state to the console.
        /// </summary>
        public string ToConsole()
        {
            string response = String.Empty;
            response +="\n-----------------\n";

            for (int i = 0; i < 8; i++)
            {
                string[] currentRank = Ranks[i];

                response+=
                      "|" + currentRank[0] + "|" + currentRank[1] + "|" + currentRank[2] + "|" + currentRank[3]
                    + "|" + currentRank[4] + "|" + currentRank[5] + "|" + currentRank[6] + "|" + currentRank[7] + "|" + "\n";
                response += "-----------------\n";
            }

            response += "\n";
            response += "Na vrsti je: " + this.ActivePlayerColor + ".\n\n";
            response += "Moznosti rokade\n";

            if (this.WhiteCanKingsideCastle && this.WhiteCanQueensideCastle)
            {
                response += "Beli - kraljeva in damina stran\n";
            }
            else if (this.WhiteCanKingsideCastle)
            {
                response += "Beli - kraljeva stran\n";
            }
            else if (this.WhiteCanQueensideCastle)
            {
                response += "Beli - damina stran\n";
            }
            else
            {
                response += "Beli - nobeden\n";
            }

            if (this.BlackCanKingsideCastle && this.BlackCanQueensideCastle)
            {
                response += "Crni - kraljeva in damina stran\n";
            }
            else if (this.BlackCanKingsideCastle)
            {
                response += "Crni - kraljeva stran\n";
            }
            else if (this.BlackCanQueensideCastle)
            {
                response += "Crni - damina stran\n";
            }
            else
            {
                response += "Crni - nobeden\n";
            }

            response += "\nMoznost en passant: ";

            if (String.IsNullOrEmpty(this.EnPassantSquare))
            {
                response += "Noben\n";
            }
            else
            {
                response += this.EnPassantSquare + "\n";
            }

            response += "Stevilo polpotez: ";
            if (this.HalfMoveCounter != null)
            {
                response += this.HalfMoveCounter + "\n";
            }

            response += "Stevilka trenutne poteze: ";

            if (this.FullMoveNumber != null)
            {
                response += this.FullMoveNumber.ToString() + "\n";
            }

            return response;
        }

        #endregion

        #region Construtors
        public BoardStateData() { }

        public BoardStateData(string piecePlacementString, string activeColorString, string castlingAvailabilityString,
                string enPassantSquareString, string halfmoveClockString, string fullmoveNumberString)
        {
            ParseRanks(piecePlacementString);
            ParseActiveColor(activeColorString);
            ParseCastlingAvailability(castlingAvailabilityString);
            ParseEnPassantSquare(enPassantSquareString);
            ParseHalfMoveCounter(halfmoveClockString);
            ParseFullmoveNumber(fullmoveNumberString);
        }

        #endregion
    }
}
