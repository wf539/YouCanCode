using System.IO;
using System;

namespace Snarf
{
	class Snarf
	{
		public static void Main(string[] args)
		{
			if (args.Length == 0) {
				Console.WriteLine("Creating file index cache...");			
				string[] files = Directory.GetFiles("/home/paul", "*.txt", SearchOption.AllDirectories);
				File.WriteAllLines("filecache.snarf", files);
				Console.WriteLine("File index cache created!");
			} else {
				Console.WriteLine("Searching for '" + args[0] + "':");
				string[] cache = File.ReadAllLines("filecache.                             ����<<<����                                 ������                                                          �����������  �����������������������������  ���                    ���                                                          �����������                       ����������������������� 