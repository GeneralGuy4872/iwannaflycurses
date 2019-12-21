save__void(void * this,size_t size,size_t n,char * parentdir)
	FILE * swapfile;
	int len = strlen(parentdir) + 9;
	char fullname[len];
	strcpy(fullname,parentdir);
	strcat(fullname,"this.dat");
	strcat(fullname,ext);
	swapfile = fopen(fullname,"wb+");
	fwrite(this,size,n,swapfile);
	fflush(swapfile);
	fclose(swapfile);
	END

save__objid_switch(objid key,void * value,char * dir) {
	switch key:
		case POTION_FLAG : save__potiontyp(value,dir);break;
		case READ_FLAG : save__readtyp(value,dir);break;
		case CONLANG_FLAG : save__conlangtyp(value,dir);break;
		case SPELL_FLAG : save__spelltyp(value,dir);break;
		case GEM_FLAG : save__gemstonetyp(value,dir);break;
		case TRAP_FLAG : save__traptyp(value,dir);break;
		case WARP_FLAG : save__warptyp(value,dir);break;
		case SUBWARP_FLAG : save__subwarptyp(value,dir);break;
		case CHEST_FLAG : save__chestyp(value,dir);break;
		case DOOR_FLAG : save__doortyp(value,dir);break;
		case LOCK_FLAG : save__locktyp(value,dir);break;
		case MONEY_FLAG : save__moneytyp(value,dir);break;
		case SPAWN_FLAG : save__spawntyp(value,dir);break;
		case SIGN_FLAG : save__signtyp(value,dir);break;
		default : break;
	}

save__langlistele(langlistele * this,char * parentdir) {
	save__void(this,sizeof(struct langlistele),1,parentdir);
	if (this->next != NULL) {
		int len = strlen(parentdir) + 6;
		char directory[len];
		strcpy(directory,parentdir);
		strcat(directory,"next/");
		save__langlistele(this->next,directory);
		}
	END
	
save__spellistele(spellistele * this,char * parentdir) {
	save__void(this,sizeof(struct spellistele),1,parentdir);
	if (this->next != NULL) {
		int len = strlen(parentdir) + 6;
		char directory[len];
		strcpy(directory,parentdir);
		strcat(directory,"next/");
		save__langlistele(this->next,directory);
		}
	END

save__heldobjtyp(heldobjtyp * this,char * parentdir) {
	save__void(this,sizeof(struct heldobjtyp),1,parentdir);
	if (this->data != NULL) {
		char * subdirname = "data/";
		int len = strlen(directory) + strlen(subdirname) + 1;
		char subdirectory[len];
		strcpy(subdirectory,directory);
		strcat(subdirectory,subdirname);
		save__objid_switch(this->type,this->data,subdirectory);
		}
	if (this->next != NULL) {
		int len = strlen(parentdir) + 6;
		char directory[len];
		strcpy(directory,parentdir);
		strcat(directory,"next/");
		save__heldobjtyp(this->next,directory);
		}
	END

save__armtyp(armtyp * this,char * parentdir);
	save__void(this,sizeof(struct armtyp),1,parentdir);
	if (this->next != NULL) {
		int len = strlen(parentdir) + 6;
		char directory[len];
		strcpy(directory,parentdir);
		strcat(directory,"next/");
		save__armtyp(this->next,directory);
		}
	END

save__legtyp(legtyp * this,char * parentdir);
	save__void(this,sizeof(struct legtyp),1,parentdir);
	if (this->next != NULL) {
		int len = strlen(parentdir) + 6;
		char directory[len];
		strcpy(directory,parentdir);
		strcat(directory,"next/");
		save__legtyp(this->next,directory);
		}
	END

save__playertyp(playertyp * this,char * parentdir) {
	int length = strlen(parentdir) + strlen(this->name);
	char[length + 1] directory;
	strcpy(directory,parentdir);
	strcat(directory,this->name);
	save__void(this,sizeof(struct playertyp),1,directory,"dat");
	if (this->helm.data != NULL) {
		char * subdirname = "helm_data/";
		int len = strlen(directory) + strlen(subdirname) + 1;
		char subdirectory[len];
		strcpy(subdirectory,directory);
		strcat(subdirectory,subdirname);
		save__objid_switch(this->helm.type,this->helm.data,subdirectory);
		}
	if (this->lang_ptr != NULL) {
		char * subdirname = "lang_ptr/";
		int len = strlen(directory) + strlen(subdirname) + 1;
		char subdirectory[len];
		strcpy(subdirectory,directory);
		strcat(subdirectory,subdirname);
		save__langlistele(this->lang_ptr,subdirectory);
		}
	if (this->spell_ptr != NULL) {
		char * subdirname = "spell_ptr/";
		int len = strlen(directory) + strlen(subdirname) + 1;
		char subdirectory[len];
		strcpy(subdirectory,directory);
		strcat(subdirectory,subdirname);
		save__spellistele(this->spell_ptr,subdirectory);
		}
	if (this->bag_ptr != NULL) {
		char * subdirname = "bag_ptr/";
		int len = strlen(directory) + strlen(subdirname) + 1;
		char subdirectory[len];
		strcpy(subdirectory,directory);
		strcat(subdirectory,subdirname);
		save__heldobjtyp(this->bag_ptr,subdirectory);
		}
	if (this->arms != NULL) {
		char * subdirname = "arms/";
		int len = strlen(directory) + strlen(subdirname) + 1;
		char subdirectory[len];
		strcpy(subdirectory,directory);
		strcat(subdirectory,subdirname);
		save__armtyp(this->arms,subdirectory);
		}
	if (this->legs != NULL) {
		char * subdirname = "legs/";
		int len = strlen(directory) + strlen(subdirname) + 1;
		char subdirectory[len];
		strcpy(subdirectory,directory);
		strcat(subdirectory,subdirname);
		save__legtyp(this->legs,subdirectory);
		}
	END

/*----------*/

loadblock(void * this,size_t size,size_t n,char * parentdir,char * filename)
	FILE * swapfile;
	int len = strlen(parentdir) + strlen(filename);
	char fullname[len + 1];
	strcpy(fullname,parentdir);
	strcat(fullname,filename);
	swapfile = fopen(fullname,"rb");
	fread(this,size,n,swapfile);
	fflush(swapfile);
	fclose(swapfile);
	}