<?php
	ncurses_init();
	ncurses_curs_set(0);
	$screen = ncurses_newwin( 0, 0, 0, 0);
	ncurses_wborder($screen, 0,0, 0,0, 0,0, 0,0);

	ncurses_wattron($screen, NCURSES_A_REVERSE);
	ncurses_mvwaddstr($screen, 1, 2, "LXF69 PHP");
	ncurses_wattroff($screen, NCURSES_A_REVERSE);
	
	ncurses_getmaxyx($screen, $row, $col);
	$string = "He thrusts his fists against the posts";
	
	ncurses_wattron($screen, NCURSES_A_BOLD);
	ncurses_mvwaddstr($screen, $row / 2, ($col / 2) - (strlen($string) / 2), $string);
	ncurses_wattr                             ����<<<����                                 ������    