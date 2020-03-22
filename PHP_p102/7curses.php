<?php
	ncurses_init();
	ncurses_curs_set(0);
	
	$screen = ncurses_newwin( 0, 0, 0, 0);
	ncurses_wborder($screen, 0,0, 0,0, 0,0, 0,0);

	ncurses_wattron($screen, NCURSES_A_BOLD);
	ncurses_mvwaddstr($screen, 1, 2, "LXF69 PHP");
	ncurses_wattroff($screen, NCURSES_A_BOLD);
	
	ncurses_getmaxyx($screen, $row, $col);
	ncurses_refresh();

        $itemselected = 0;
	$items = array("Life", "Love", "Liberty", "Crack Attack");

	ncurses_start_color();
	ncurses_init_pair(1, NCURSES_COLOR_YELLOW, NCURSES_COLOR_BLACK);
	ncurses_init_pair(2, NCURSES_COLOR_RED, NCURSES_COLOR_BLACK);
	ncurses_init_pair(3, NCURSES_COLOR_CYAN, NCURSES_COLOR_BLACK);
	ncurses_init_pair(4, NCURSES_COLOR_MAGENTA, NCURSES_COLOR_BLACK);

	$start = ($row / 2) - (count($items) / 2);

	while (true) {
		foreach($items as $index => $item) {
			if ($index == $itemselected) {
				ncurses_wattron($screen, NCURSES_A_REVERSE);
				ncurses_mvwaddstr($screen, $start + $index, ($col / 2) - (strlen($item) / 2), $item);
				ncurses_wattroff($screen, NCURSES_A_REVERSE);
			} else {
				ncurses_mvwaddstr($screen, $start + $index, ($col / 2) - (strlen($item) / 2), $item);
			}
		}
	
		ncurses_wrefresh($screen);
		$char = ncurses_getch($screen);

		switch ($char) {
			case 13:
				ncurses_beep();
				ncurses_wcolor_set($screen, $itemselected + 1);
				
				break;
			case NCURSES_KEY_UP:
				--$itemselected;
				if ($itemselected == -1) $itemselected = count($items) - 1;
				break;
			case NCURSES_KEY_DOWN:
				++$itemselected;
				if ($itemselected == count($items)) $itemselected = 0;
				break;
			default:
				ncurses_end();
				exit;
		}
	}
?>
