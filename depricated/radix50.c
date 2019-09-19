//unused

uchar radixoutput(input)
char input
{
switch (input) {
	case 'A' :; case 'a' : return 01; break;
	case 'B' :; case 'b' : return 02; break;
	case 'C' :; case 'c' : return 03; break;
	case 'D' :; case 'd' : return 04; break;
	case 'E' :; case 'e' : return 05; break;
	case 'F' :; case 'f' : return 06; break;
	case 'G' :; case 'g' : return 07; break;
	case 'H' :; case 'h' : return 010; break;
	case 'I' :; case 'i' : return 011; break;
	case 'J' :; case 'j' : return 012; break;
	case 'K' :; case 'k' : return 013; break;
	case 'L' :; case 'l' : return 014; break;
	case 'M' :; case 'm' : return 015; break;
	case 'N' :; case 'n' : return 016; break;
	case 'O' :; case 'o' : return 017; break;
	case 'P' :; case 'p' : return 020; break;
	case 'Q' :; case 'q' : return 021; break;
	case 'R' :; case 'r' : return 022; break;
	case 'S' :; case 's' : return 023; break;
	case 'T' :; case 't' : return 024; break;
	case 'U' :; case 'u' : return 025; break;
	case 'V' :; case 'v' : return 026; break;
	case 'W' :; case 'w' : return 027; break;
	case 'X' :; case 'x' : return 030; break;
	case 'Y' :; case 'y' : return 031; break;
	case 'Z' :; case 'z' : return 032; break;
	case '$' : return 033; break;
	case '.' : return 034; break;
	case '%' : return 035; break;
	case '0' : return 036; break;
	case '1' : return 037; break;
	case '2' : return 040; break;
	case '3' : return 041; break;
	case '4' : return 042; break;
	case '5' : return 043; break;
	case '6' : return 044; break;
	case '7' : return 045; break;
	case '8' : return 046; break;
	case '9' : return 047; break;
	default : return 0; break;
	}
}

char16_t squoze(string)
char string[3]
{
uchar char1 = radixoutput(string[0])
uchar char2 = radixoutput(string[1])
uchar char3 = radixoutput(string[2])
return (char1*1600)+(char2*40)+char3
}

char radixtoascii(radix50)
uchar radix50
{
switch (radix50) {
	case 0 : return ' ';
	case 01 : return 'A';
	case 02 : return 'B';
	case 03 : return 'C';
	case 04 : return 'D';
	case 05 : return 'E';
	case 06 : return 'F';
	case 07 : return 'G';
	case 010 : return 'H';
	case 011 : return 'I';
	case 012 : return 'J';
	case 013 : return 'K';
	case 014 : return 'L';
	case 015 : return 'M';
	case 016 : return 'N';
	case 017 : return 'O';
	case 020 : return 'P';
	case 021 : return 'Q';
	case 022 : return 'R';
	case 023 : return 'S';
	case 024 : return 'T';
	case 025 : return 'U';
	case 026 : return 'V';
	case 027 : return 'W';
	case 030 : return 'X';
	case 031 : return 'Y';
	case 032 : return 'Z';
	case 033 : return '$';
	case 034 : return '.';
	case 035 : return '%';
	case 036 : return '0';
	case 037 : return '1';
	case 040 : return '2';
	case 041 : return '3';
	case 042 : return '4';
	case 043 : return '5';
	case 044 : return '6';
	case 045 : return '7';
	case 046 : return '8';
	case 047 : return '9';
	default : return ' ';
	}
}

char* unsquoze(squozed,symbol1,symbol2,symbol3)
char16_t squozed
char symbol1 symbol2 symbol3
{
static char* output = "   "
if (squozed > 63999) {
	output[0] = '?'
	output[1] = '?'
	output[2] = '?'
	return output
	}
tmp = div(squozed,1600)
uchar char1 = tmp.quot
tmp = div(div.rem,40)
uchar char2 = tmp.quot
uchar char3 = tmp.rem
output[0] = radixtoascii(char1)
output[1] = radixtoascii(char2)
output[2] = radixtoascii(char3)
}