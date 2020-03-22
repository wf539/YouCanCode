using SdlDotNet.Graphics;
using System;
using System.Drawing;

namespace TroutWarsNG
{
	public class Enemy
	{
		public Surface sfcEnemy;
		
		public float X;
		public float Y;
		
		public Enemy()
		{
			sfcEnemy = MainClass.LoadImage("content/fish.bmp");
		}
		
		public void Update(int elapsed) {
			X -= elapsed * 0.6f;
		}
		
		public void Render(Surface screen) {
			screen.Blit(sfcEnemy, new Point(Convert.ToInt32(X), Convert.ToInt32(Y)));
		}
	}
}
