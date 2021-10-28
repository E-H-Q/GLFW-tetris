// L, S, J, I, Z, O, T

typedef struct {
	int x;
	int y;
	int id;
	int data[4][4];
} piece;

int L[4][4] = {0,0,0,0,
			   0,1,0,0,
			   0,1,0,0,
			   0,1,1,0};

int S[4][4] = {0,0,0,0,
			   0,0,2,2,
			   0,2,2,0,
			   0,0,0,0};

int J[4][4] = {0,0,0,0,
			   0,0,3,0,
			   0,0,3,0,
			   0,3,3,0};

int I[4][4] = {0,4,0,0,
			   0,4,0,0,
			   0,4,0,0,
			   0,4,0,0};

int Z[4][4] = {0,0,0,0,
			   0,5,5,0,
			   0,0,5,5,
			   0,0,0,0};

int O[4][4] = {0,0,0,0,
			   0,6,6,0,
			   0,6,6,0,
			   0,0,0,0};

int T[4][4] = {0,0,0,0,
			   0,0,7,0,
			   0,7,7,7,
			   0,0,0,0};

piece tetrimino(piece tet) { // works, but could be optimized 
	tet.x = 4;
	tet.y = 16;
	int random(int lower, int upper, int count) {
		int i;
		for (i = 0; i < count; i++) {
			int num = (rand() % (upper - lower + 1)) + lower;
			return num;
		}
	}
	int lower = 0, upper = 6, count = 1;
	srand(time(0));
	tet.id = random(lower, upper, count);

	// L, S, J, I, Z, O, T
	// 0, 1, 2, 3, 4, 5, 6
	switch (tet.id) {
		case 0: // L
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					tet.data[i][j] = L[i][j];
				}
			}
			break;
		case 1: // S
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					tet.data[i][j] = S[i][j];
				}
			}
			break;
		case 2: // J
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					tet.data[i][j] = J[i][j];
				}
			}
			break;
		case 3: // I
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					tet.data[i][j] = I[i][j];
				}
			}
			break;
		case 4: // Z
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					tet.data[i][j] = Z[i][j];
				}
			}
			break;
		case 5: // O
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					tet.data[i][j] = O[i][j];
				}
			}
			break;
		case 6: // T
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					tet.data[i][j] = T[i][j];
				}
			}
			break;
	}
	return tet;
}
