<?php
	ncurses_init();
	$screen = ncurses_newwin( 0, 0, 0, 0);
	ncurses_wborder($screen, 0,0, 0,0, 0,0, 0,0);

	ncurses_getmaxyx($screen, $row, $col);
	$string = "He thrusts his fists against the posts";
	
	ncurses_mvwaddstr($screen, $row / 2, ($col / 2) - (strlen($string) / 2), $string);
	ncurses_wrefresh($screen);
	ncurses_wgetch($screen);
	ncurses_end();
?>
