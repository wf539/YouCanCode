<?php
	ncurses_init();
	ncurses_curs_set(0);

	ncurses_start_color();
	ncurses_init_pair(1, NCURSES_COLOR_RED, NCURSES_COLOR_BLACK);
	ncurses_init_pair(2, NCURSES_COLOR_GREEN, NCURSES_COLOR_BLACK);
	ncurses_init_pair(3, NCURSES_COLOR_YELLOW, NCURSES_COLOR_BLACK);
	ncurses_init_pair(4, NCURSES_COLOR_BLUE, NCURSES_COLOR_BLACK);
	ncurses_init_pair(5, NCURSES_COLOR_CYAN, NCURSES_COLOR_BLACK);
	ncurses_init_pair(6, NCURSES_COLOR_MAGENTA, NCURSES_COLOR_BLACK);

	$screen = ncurses_newwin( 0, 0, 0, 0);
	ncurses_getmaxyx($screen, $row, $col);

	# create two windows, split into two with some space
	$winleft = ncurses_newwin($row, $col / 2 - 1, 0, 0);
	$winright = ncurses_newwin($row, $col / 2 - 1, 0, $col / 2);

	# print the title
	ncurses_wattron($screen, NCURSES_A_REVERSE);
	ncurses_mvwaddstr($screen, 1, 2, "LXF69 PHP");
	ncurses_wattroff($screen, NCURSES_A_REVERSE);
	
	$string = "He thrusts his fists against the posts";
	
	ncurses_wattron($screen, NCURSES_A_BOLD);

	# these values are divided by two so they work for half
	# the screen size. These co-ordinates are relative to the
	# window itself, so 0 is the far left-hand side of the
	# left window, and also the far left-hand side of the
	# right window.
	$startrow = ($row / 2) - 3;
	$startcol = ($col / 2) - 3 - (strlen($string) / 2);

	for ($i = 1; $i <= 6; ++$i) {
		# this isn't really necessary, but there's no harm
		ncurses_wcolor_set($screen, $i);

		# this splits the printing evenly between two windows
		if ($i % 2) {
			ncurses_wcolor_set($winleft, $i);
			ncurses_mvwaddstr($winleft, $startrow + $i, 0, $string);
		} else {
			ncurses_wcolor_set($winright, $i);
			ncurses_mvwaddstr($winright, $startrow + $i, 0, $string);
		}
	}
	
	ncurses_wattroff($screen, NCURSES_A_BOLD);

	# refresh all windows - important!
	ncurses_wrefresh($screen);
	ncurses_wrefresh($winleft);
	ncurses_wrefresh($winright);
	ncurses_wgetch($screen);
	ncurses_end();
?>
