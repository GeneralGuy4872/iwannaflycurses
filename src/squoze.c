ushort squoze(char[3] ascii) {
	return squozebit(ascii[0]) + (40 * squozebit(ascii[1])) + (1600 * squozebit(ascii[2]));
	}

uchar squozebit(char ascii) {
	if (ascii <= ' ') {return 0}
	else {
		switch ascii :
			case 'A' :
			case 'a' : return 1;
			case 'B' :
			case 'b' : return 2;
			case 'C' :
			case 'c' : return 3;
			case 'D' :
			case 'd' : return 4;
			case 'E' :
			case 'e' : return 5;
			case 'F' :
			case 'f' : return 6;
			case 'G' :
			case 'g' : return 7;
			case 'H' :
			case 'h' : return 010;
			case 'I' :
			case 'i' : return 011;
			case 'J' :
			case 'j' : return 012;
			case 'K' :
			case 'k' : return 013;
			case 'L' :
			case 'l' : return 014;
			case 'M' :
			case 'm' : return 015;
			case 'N' :
			case 'n' : return 016;
			case 'O' :
			case 'o' : return 017;
			case 'P' :
			case 'p' : return 020;
			case 'Q' :
			case 'q' : return 021;
			case 'R' :
			case 'r' : return 022;
			case 'S' :
			case 's' : return 023;
			case 'T' :
			case 't' : return 024;
			case 'U' :
			case 'u' : return 025;
			case 'V' :
			case 'v' : return 026;
			case 'W' :
			case 'w' : return 027;
			case 'X' :
			case 'x' : return 030;
			case 'Y' :
			case 'y' : return 031;
			case 'Z' :
			case 'z' : return 032;
			case '$' : return 033;
			case '_' :
			case '.' : return 034;
			case '0' : return 036;
			case '1' : return 037;
			case '2' : return 040;
			case '3' : return 041;
			case '4' : return 042;
			case '5' : return 043;
			case '6' : return 044;
			case '7' : return 045;
			case '8' : return 046;
			case '9' : return 047;
			default : return 035;
			}
		}
	}