using SdlDotNet.Graphics;
using SdlDotNet.Input;
using System;
using System.Drawing;

namespace TroutWarsNG {
	class Player {
		Surface sfcPlayer;

		public float X;
		public float Y;

		public Player() {
			sfcPlayer = MainClass.LoadImage("content/spaceship.bmp");
		}

		public void Update(int elapsed) {
			if (Keyboard.IsKeyPressed(Key.UpArrow)) {
				Y -= elapsed * 0.5f;
			}

			if (Keyboard.IsKeyPressed(Key.DownArrow)) {
				Y += elapsed * 0.5f;
			}

			if (Keyboard.IsKeyPress                             ����<<<����                                 ������                                                          �����������  �����������������������������  ���                    ���                                                          �����������                       �����������������������                                                          ??>>>>>??                                 ?????????????????=====?                      