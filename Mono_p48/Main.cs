using System;
using System.Collections.Generic;
using System.IO;
using System.Text;
using System.Xml;

namespace cheetara {
	class MainClass {
		static void Main(string[] args) {
			switch (args.Length) {
				case 0:
					// refresh!
					ReadFeeds();
					break;
				case 1:
					// reset!
					File.Delete("guidcache.txt");
					ReadFeeds();
					break;

				case 2:
					// sub or unsub!
					if (args[1] == "") return;

					if (args[0] == "sub") {
						File.AppendAllText("sitelist.txt", args[1] + "\n");
					} else {
						if (File.Exists("sitelist.txt")) {
							string[] sitelist = File.ReadAllLines("sitelist.txt");
							File.Delete("sitelist.txt");

							foreach (string site in sitelist) {
								if (site == args[1]) {
									// aha! this is the site we need to drop; ignore it
								} else {
									File.AppendAllText("sitelist.txt", site + "\n");
								}
							}
						}
						
						
					}

					break;
			}
		}

		public static void ReadFeeds() {
			string[] guidcache;

			if (File.Exists("guidcache.txt")) {
				guidcache = File.ReadAllLines("guidcache.txt");
			} else {
				guidcache = new string[0];
			}

			string[] sitelist;

			if (File.Exists("sitelist.txt")) {
				sitelist = File.ReadAllLines("sitelist.txt");
			} else {
				sitelist = new string[0];
			}
			
			foreach (string site in sitelist) {
				XmlDocument doc = new XmlDocument();
				doc.Load(site);
				
				XmlNodeList items = doc.SelectNodes("//item");
				foreach (XmlNode item in items) {
					bool showthisitem = true;

					foreach (string guid in guidcache) {
						if (guid == item.SelectSingleNode("guid").InnerText) {
							showthisitem = false;
							break;
						}
					}

					if (showthisitem) {
						Console.WriteLine(item.SelectSingleNode("title").InnerText);
						Console.WriteLine("   " + item.SelectSingleNode("description").InnerText);
						Console.WriteLine("");

						File.AppendAllText("guidcache.txt", item.SelectSingleNode("guid").InnerText + "\n");
					}
				}
			}
		}
	}
}
