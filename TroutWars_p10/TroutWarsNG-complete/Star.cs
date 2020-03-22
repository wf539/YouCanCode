using System;

namespace TroutWarsNG {
	class Star {
		public int Type;
		public float X;
		public int Y;

		public Star(int type) {
			X = MainClass.Rand.Next(1024);
			Y = MainClass.Rand.Next(768);
			Type = type;
		}

		public void Update(int elapsed) {
			X -= elapsed * (Type + 1) * 0.1f;

			if (X < 0) {
				X = 1024 + MainClass.Rand.Next(100);
				Y = MainClass.Rand.Next(768);
			}
		}
	}
}
