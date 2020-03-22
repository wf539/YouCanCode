using SdlDotNet.Graphics;
using System;
using System.Drawing;

namespace TroutWarsNG
{
	enum GameState { INTRO, MAINMENU, PLAYING }

	class MainClass
	{
		static public Random Rand = new Random();

		static void Main(string[] args)
		{
			TroutWars Game = new TroutWars();
		}

		static public Surface LoadImage(string image)
		{
			Surface sfc = new Surface(image);
			sfc.TransparentColor = Color.Magenta;
			sfc.Transparent = true;

			return sfc;
		}
	}
}