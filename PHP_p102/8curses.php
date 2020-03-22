<?php
	ncurses_init();
	ncurses_curs_set(0);

	ncurses_start_color();
	ncurses_init_pair(1, NCURSES_COLOR_GREEN, NCURSES_COLOR_BLACK);

	$screen = ncurses_newwin( 0, 0, 0, 0);

	ncurses_getmaxyx($screen, $row, $col);
	ncurses_wcolor_set($screen, 1);

	$chains = array();
	$letters = array_merge(range(0,9), range("A","Z"), array("@", "!", "$", "%", "&", "#"));

	function createchain() {
		GLOBAL $row, $col, $chains, $letters;
		
		$newchain = array();
		$newchain["row"] = 0;
		$newchain["col"] = rand(0, $col);
		
		$newchain["letters"] = array_rand($letters, rand(4,7));
		$chains[] = $newchain;
	}

	function movechains() {
		GLOBAL $chains, $letters, $row;

		foreach($chains as &$chain) {
			++$chain["row"];
			array_unshift($chain["letters"], array_rand($letters));
			array_pop($chain["letters"]);
		}
	}

	while (true) {	
		movechains();
		createchain();
		
		foreach ($chains as $chain) {
			foreach($chain["letters"] as $index => $letter) {
				if ($index == 0) {
					ncurses_wcolor_set($screen, 0);
					ncurses_wattron($screen, NCURSES_A_BOLD);
					ncurses_mvwaddstr($screen, $chain["row"] - $index, $chain["col"], $letters[$letter]);
					ncurses_wattroff($screen, NCURSES_A_BOLD);
				} else {
					ncurses_wcolor_set($screen, 1);
					if ($index == 1) {
						ncurses_wattron($screen, NCURSES_A_BOLD);
						ncurses_mvwaddstr($screen, $chain["row"] - $index, $chain["col"], $letters[$letter]);
						ncurses_wattroff($screen, NCURSES_A_BOLD);
					} else {
						ncurses_mvwaddstr($screen, $chain["row"] - $index, $chain["col"], $letters[$letter]);
					}
				}
			}

			ncurses_mvwaddstr($screen, $chain["row"] - $index - 1, $chain["col"], " ");
		}
	
		ncurses_wrefresh($screen);

		usleep(200000);
	}
?>
