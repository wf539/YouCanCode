using SdlDotNet.Graphics;
using System;
using System.Drawing;

namespace TroutWarsNG
{
	public class Laser
	{
		public Surface sfcLaser;
		
		public float X;
		public float Y;
		
		public Laser()
		{
			sfcLaser = MainClass.LoadImage("content/laser.bmp");
		}
		
		public void Update(int elapsed) {
			X += elapsed * 1.0f;
		}
		
		public void Render(Surface screen) {
			screen.Blit(sfcLaser, new Point(Convert.ToInt32(X), Convert.ToInt32(Y)));
		}
	}
}
