lightningfractal (int x,int y) {
	for (int n = 1;;n *= 2) {
		for (int i = 0;i < n;i++) {
			int a = y - i;
			int b = x + n + i;
			if (a < 0) {return 0;}
			else if (!((a >= MAX_Y) || (b < 0) || (b >= MAX_X))) {
				mvaddch(a,b,'/' | COLOR_PAIR(COLOR_CYAN) | A_BOLD);
				}
			}
		for (int i = 0;i < n;i++) {
			int a = y - (n + i);
			int b = x + ((2n - 1) - i);
			if (a < 0) {return 0;}
			else if (!((a >= MAX_Y) || (b < 0) || (b >= MAX_X))) {
				mvaddch(a,b,'\\' | COLOR_PAIR(COLOR_CYAN) | A_BOLD);
			}
		for (int i = 0;i < n;i++) {
			int a = y - (n + i);
			int b = x + i;
			if (a < 0) {return -1;}
			if (!((a >= MAX_Y) || (b < 0) || (b >= MAX_X))) {
				mvaddch(a,b,'/' | COLOR_PAIR(COLOR_CYAN) | A_BOLD);
				}
			}
		x -= 2n;
		y -= n;
		if (y < 0) {return -1;}
		}