void ERRORGRAPHIC(int sig, uchar iter, ...) {
BREAKCURSES
printf("\033[91;103m *┐  \033[22;0m");printf("\033[1;91m Error!\033[21;22;24;0m\n");
printf("\033[91;103m ▗█▖ \033[22;0m\n");
printf("\033[91;103m ███ \033[22;0m");printf("\033[1;91m File: %s",__FILE__\033[21;22;24;0m\n");
printf("\033[91;103m ▝█▘ \033[22;0m");printf("\033[1;91m Line: %i",__LINE__\033[21;22;24;0m\n");
va_list argv;
va_start(argv,iter);
{
for (;iter;iter--) {
	size_t typ = va_arg(argv,int);
	switch typ : {
		case 0 :
			char* format = va_arg(argv,char*);
			fprintf(stderr,format);
			break;
		case sizeof(int8_t) :
			char* format = va_arg(argv,char*);
			int8_t foo = va_arg(argv,int8_t);
			fprintf(stderr,format,foo);
			break;
		case sizeof(int16_t) : 
			char* format = va_arg(argv,char*);
			int16_t foo = va_arg(argv,int16_t);
			fprintf(stderr,format,foo);
			break;
		case sizeof(int32_t) :
			char* format = va_arg(argv,char*);
			int32_t foo = va_arg(argv,int32_t);
			fprintf(stderr,format,foo);
			break;
		case sizeof(int64_t) :
			char* format = va_arg(argv,char*);
			int64_t foo = va_arg(argv,int64_t);
			fprintf(stderr,format,foo);
			break;
		default :	
			char* format = va_arg(argv,char*);
			intptr_t foo = va_arg(argv,intptr_t);
			fprintf(stderr,format,foo);
			break;
		}
	}
va_end(argv);
if (sig) {
	raise(sig);
	}
getchar();
FIXCURSES
END
