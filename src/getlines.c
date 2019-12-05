struct singlestringlistyp * singlegetline (char * path) {
FILE * openfile = fopen(path,"r");
char[BUFFERMAX] buffer;
struct singlestringlsityp * head;
struct singlestringlistyp * prev;
struct singlestringlistyp * this;
if (fgets(buffer,BUFFERMAX-1,openfile) != NULL) {
	head = malloc(sizeof(struct singlestringlistyp));
	head->next = NULL;
	head->lineno = 1;
	head->text = calloc(strlen(buffer) + 1,sizeof(char));
	prev = head;
	for (int n = 2;fgets(buffer,BUFFERMAX - 1,openfile) != NULL;n++) {
		this = malloc(sizeof(struct singlestringlistyp));
		prev->next = this;
		this->next = NULL;
		this->lineno = n;
		this->text = calloc(strlen(buffer) + 1,sizeof(char));
		prev = this;
		}
	return head;
	}
else {
	return NULL;
	}
}

char ** singlegetlinearray (char * path,ushort nlines,ushort * skip) {
char ** output = calloc(nlines,sizeof(char *));
struct singlestringlistyp * line = singlegetline(path);
int nextskip = 0;
int x = 0;
if skip != NULL {
	while ((x < nlines) && (line != NULL) && (skip[nextskip] != 0)) {
		if (line->lineno != skip[nextskip]) {
			output[x] = line->text;
			}
		else {
			nextskip++;
			}
		line = line->next;
		x++;}
	}
while ((x < nlines) && (line != NULL)) {
	output[x] = line->text;
	line = line->next;
	x++;}
return output;
}

