static int size_width;
static int size_height;
int *global_width =&size_width;
int *global_height =&size_height;

struct RGB {
	float r;
	float g;
	float b;
};

int readBitmap(const char *filename, char vals[][8]) {
	int width, height, padding, bitcount, size;
	unsigned char *data = 0;
	unsigned char info[54] = { 0 };
	FILE *file = fopen(filename, "rb");
	if(!file)
    	return 0;

	fread(info, 1, 54, file);
	width = *(int*)(info + 18);
	height = *(int*)(info + 22);
	size_width = width;
	size_height = height;
	bitcount = *(int*)(info + 28);
	size = ((width * bitcount + 31) / 32) * 4 * height;
	padding = width % 4;
	if(bitcount != 24) //this code works for 24-bit bitmap only
	    goto error;

	data = malloc(size);
	fread(data, 1, size, file);

	int i = 0;

	for(int row = height - 1; row >= 0; row--) {
	    for(int col = 0; col < width; col++) {
    	    int p = (row * width + col) * 3 + row * padding;
			char hex[8];
    	    sprintf(hex, "%02X%02X%02X", data[p + 0], data[p + 1], data[p + 2]);
			strcpy(vals[i], hex);
			i++;
    	}
	}

	error:
    	if(file) fclose(file);
    	if(data) free(data);
    	return 0;
}

float hex2float(char *str, float arr[]) {
	int r, g, b;
	sscanf(str, "%02x%02x%02x", &r, &g, &b);

	arr[0] = r / 255;
	arr[1] = g / 255;
	arr[2] = b / 255;
}

int drawBitmap(struct RGB *rgb, int x, int y) {
	if (!x || !y) {
		return 0;
	}
	glPointSize(1);
	glBegin(GL_POINTS);

	int total = 0;

	for (int i = *global_height; i > 0; i--) {
		for (int j = 0; j < *global_width; j++) {
			glColor3f(rgb[total].b, rgb[total].g, rgb[total].r);
			glVertex3f(x + j, y + i, 0);
			total++;
		}
	}
	glEnd();
}
