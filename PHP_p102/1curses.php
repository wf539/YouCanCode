<?php
	ncurses_init();
	$screen = ncurses_newwin(0, 0, 0, 0);
	ncurses_wborder($screen, 0,0, 0,0, 0,0, 0,0);
	ncurses_wrefresh($screen);
	ncurses_wgetch($screen);
	ncurses_end();
?>
