tilemeta * roomtileget(roomtyp * this,tileset * maintiles,ucoord pos) {
	if (this->tiledata[pos[2]][pos[1]][pos[0]] < 0) {
		return &( maintiles[this->swapin->tiledata[pos[2]][pos[1]][pos[0]]] );
		}
	else {
		return &( this->hightiles[this->tiledata[pos[2]][pos[1]][pos[0]] ^ 0x80] );
		}
	}

tilemeta * roomtileget(roomtyp * this,tileset * maintiles,int x,int y,int z) {
	if (this->tiledata[z][y][x] < 0) {
		return &( maintiles[this->swapin->tiledata[z][y][x]] );
		}
	else {
		return &( this->hightiles[this->tiledata[z][y][x] ^ 0x80] );
		}
	}
