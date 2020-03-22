using SdlDotNet;
using SdlDotNet.Core;
using SdlDotNet.Graphics;
using SdlDotNet.Input;
using System;
using System.Collections.Generic;
using System.Drawing;

namespace TroutWarsNG {
	class TroutWars {
		GameState State = GameState.PLAYING;
		
		Surface sfcScreen;

		Starfield TheStarfield;
		Player ThePlayer;
		List<Laser> Lasers = new List<Laser>();
		List<Enemy> Enemies = new List<Enemy>();
		
		int LastEnemyCreation;
		int EnemyCreationSpeed = 2500;
		
		public TroutWars() {
			sfcScreen = Video.SetVideoMode(1024, 768);
			Video.WindowCaption = "Trout Wars NG";
			
			TheStarfield = new Starfield();
			ThePlayer = new Player();
			
			Events.Tick += new EventHandler<TickEventArgs>(Tick);
			Events.Quit += new EventHandler<QuitEventArgs>(Quit);
			Events.KeyboardDown += new EventHandler<KeyboardEventArgs>(KeyDown);
			Events.Run();
		}
		
		void KeyDown(object sender, KeyboardEventArgs e) {
			if (e.Key == Key.Space) {
				FireLaser();
			}
		}
		
		void FireLaser() {
			Laser laser = new Laser();
			laser.X = ThePlayer.X + 40;
			laser.Y = ThePlayer.Y + 28;
			Lasers.Add(laser);
		}

		void Quit(object sender, QuitEventArgs e) {
			Events.QuitApplication();
		}

		void Tick(object sender, TickEventArgs e) {
			Update(e.TicksElapsed);
			Render();
			
			if (LastEnemyCreation + EnemyCreationSpeed < Timer.TicksElapsed) {
				CreateEnemy();
			}
		}
		
		void CreateEnemy() {
			Enemy enemy = new Enemy();
			enemy.X = 1024;
			enemy.Y = MainClass.Rand.Next(720);
			Enemies.Add(enemy);
			LastEnemyCreation = Timer.TicksElapsed;
			EnemyCreationSpeed -= 50;
		}

		void Update(int elapsed) {
			ThePlayer.Update(elapsed);

			for (int i = Lasers.Count - 1; i >= 0; i = i - 1) {
				Lasers[i].Update(elapsed);
				if (Lasers[i].X > 1024) {
					Lasers.RemoveAt(i);
					continue;
				}
				
				for (int j = Enemies.Count - 1; j >= 0; j = j - 1) {
					Rectangle laser = new Rectangle(Convert.ToInt32(Lasers[i].X), Convert.ToInt32(Lasers[i].Y), Lasers[i].sfcLaser.Width, Lasers[i].sfcLaser.Height);
					Rectangle enemy = new Rectangle(Convert.ToInt32(Enemies[j].X)  , Convert.ToInt32(Enemies[j].Y), Enemies[j].sfcEnemy.Width, Enemies[j].sfcEnemy.Height);
					
					if (laser.IntersectsWith(enemy)) {
						Enemies.RemoveAt(j);
						Lasers.RemoveAt(i);
						break;
					}				
				}
 			}
			
			foreach(Enemy enemy in Enemies) {
				enemy.Update(elapsed);
			}
			
			TheStarfield.Update(elapsed);
		}

		void Render() {
			sfcScreen.Fill(Color.Black);

			TheStarfield.Render(sfcScreen);
			
			foreach(Laser laser in Lasers) {
				laser.Render(sfcScreen);
			}		
			
			foreach(Enemy enemy in Enemies) {
				enemy.Render(sfcScreen);
			}
			
			ThePlayer.Render(sfcScreen);	

			sfcScreen.Update();
		}
	}
}
