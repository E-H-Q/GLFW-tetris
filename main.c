// GLFW TETRIS: made by EHQ
#include <stdio.h>
#include <time.h>
#include <GLFW/glfw3.h>
#include <GL/glut.h>
#include <string.h>

#include "pieces.h"
#include "draw.c"
#include "bmp.c"

#define SIZE 30 // size of the "blocks", (used for tetriminoes and window + board sizing)
#define WINDOW_WIDTH (18 * SIZE)
#define WINDOW_HEIGHT (24 * SIZE)
#define bmp_size (WINDOW_WIDTH * WINDOW_HEIGHT)

float delay = 1; // time delay in seconds
int score = 0;

int render(int board[10][20], piece new, struct RGB *rgb) {
	// clears the screen
	glClearColor ( 0.0f, 0.0f, 0.0f, 0.0f );
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// draw border around the board area
	rect(1, 0, 10 * SIZE, 20 * SIZE);

	// draw the board
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 20; j++) {
			if (board[i][j] == 1) {
				square(i * SIZE, j * SIZE, SIZE);
			} else {
				continue;
			}
		}
	}
	// draw the tetrimino
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (new.data[i][j] == 1) {
				square(i * SIZE + (new.x * SIZE), j * SIZE + (new.y * SIZE), SIZE);
			} else {
				continue;
			}
		}
	}
	// draw the bitmap
	drawBitmap(rgb, 1, 600);
}

int rotateRight(int matrix[4][4]) {
	// transpose array
	for(int i = 0; i < 4; i++) {
		for(int j = i; j < 4; j++) {
			int temp = matrix[i][j];
			matrix[i][j] = matrix[j][i];
			matrix[j][i] = temp;
		}
	}
	// reverse every row
	// haha wtf is going on here
	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < 4 / 2; j++) {
			int temp = matrix[i][j];
			matrix[i][j] = matrix[i][4-1-j];
			matrix[i][4-1-j] = temp;
		}
	}
}

int line (int board[10][20]) {
	int filled;
	for (int row = 0; row < 20; row++) {
		filled = 1; // true
		for (int col = 0; col < 10; col++) {
			if (board[col][row] == 0) {
				filled = 0; // false
			}
		}
		if (filled == 1) {
			// line is filled !!!!
			for (int i = 0; i < 10; i++) {
				for (int j = row; j < 20 - 1; j++) {
					board[i][j] = board[i][j+1];
				}
			}

			score = score + 100; // score increase
			printf("SCORE: %d\n", score);

			if (score % 1000 == 0) {
				printf("SPEED: %f\n", delay);
				delay = delay - 0.1;
			}

		} else {
			continue;
		}
	}
}

int check(int board[10][20], piece temp) {
	for (int i = 0; i < 4; i++) { // collison detection
		for (int j = 0; j < 4; j++) {
			if (temp.data[i][j] == 1 && board[temp.x + i][temp.y + j] != 0) {
				return 0;
			}
			if (temp.data[i][j] == 1 && (temp.x + i >= 10 || temp.x + i < 0 || temp.y + j >= 20 || temp.y + j < 0)) {
				return 0;
			}
		}
	}
	return 1;
}

int merge(int board[10][20], piece new) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (new.data[i][j] == 1) {
				board[new.x + i][new.y + j] = new.data[i][j];
			}
		}
	}
}

int copy (int dest[4][4], int src[4][4]) {
	for (int i = 0; i < 4; i++) { 
		for (int j = 0; j < 4; j++) {
			dest[i][j] = src[i][j];
		}
	}
}

int main() {
	// Initialize the library
	if (!glfwInit()) {
		return -1;
	}
	// Define the window
	GLFWwindow* window;
	// Create a windowed mode window & its OpenGL context
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE); //window decoration
	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Tetris", NULL, NULL);
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	// set up view
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, WINDOW_WIDTH, 0.0, WINDOW_HEIGHT, 0.0, 1.0); // creates the canvas

	if (!window) {
		glfwTerminate();
		return -1;
	}
	// "focuses" the window
	glfwMakeContextCurrent(window);

	// game stuff starts here
	int board[10][20];
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 20; j++) {
			board[i][j] = 0;
		}
	}

	piece new;
	new = tetrimino(new); // fills out "new.data"
	rotateRight(new.data); // needs to be rotated right away for some reason

	// input handling
	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
		if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS || (key == GLFW_KEY_RIGHT && action == GLFW_REPEAT)) {
			piece temp;
			temp.x = new.x + 1;
			temp.y = new.y;
			copy(temp.data, new.data); // copy array from "new" to "temp"
			if (check(board, temp)) {
				new.x++;
			} else {
				new.x = new.x;
			}
		}
		if (key == GLFW_KEY_LEFT && action == GLFW_PRESS || (key == GLFW_KEY_LEFT && action == GLFW_REPEAT)) {
			piece temp;
			temp.x = new.x - 1;
			temp.y = new.y;
			copy(temp.data, new.data); // copy array from "new" to "temp"
			if (check(board, temp)) {
				new.x--;
			} else {
				new.x = new.x;
			}
		}
		if (key == GLFW_KEY_DOWN && action == GLFW_PRESS || (key == GLFW_KEY_DOWN && action == GLFW_REPEAT)) {
			piece temp;
			temp.x = new.x;
			temp.y = new.y - 1;
			copy(temp.data, new.data); // copy array from "new" to "temp"
			if (check(board, temp)) {
				new.y--;
			} else {
				//puts("collide");
				merge(board, new);

				//line(board);

				for (int i = 0; i < 4; i++) { // clears "new.data" to make another tetrimino
					for (int j = 0; j < 4; j++) {
						new.data[i][j] = 0;
					}
				}
				new = tetrimino(new); // fills out "new.data"
				rotateRight(new.data); // needs to be rotated right away for some reason
				new.y = new.y;
			}
		}
		if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
			piece temp;
			temp.x = new.x;
			temp.y = new.y;
			copy(temp.data, new.data); // copy array from "new" to "temp"
			rotateRight(temp.data);
			if (check(board, temp)) {
				rotateRight(new.data);
			}
		}
	}
	glfwSetKeyCallback(window, key_callback);

	char vals[bmp_size][8];
	readBitmap("image.bmp", vals);
	struct RGB *rgb = malloc(bmp_size*sizeof(struct RGB));
	for (int i = 0; i < bmp_size; i++) {
		float arr[3];
		hex2float(vals[i], arr);
		rgb[i].r = arr[0];	
		rgb[i].g = arr[1];	
		rgb[i].b = arr[2];	
	}

	float time = delay;
	float previous = glfwGetTime();

	// MAIN LOOP
	while (!glfwWindowShouldClose(window)) {
		line(board); // checks for filled lines
		// clock
		float now = glfwGetTime();
		float delta = now - previous;
		previous = now;
		time -= delta;
		if (time <= 0.f) {
			time = delay; // needs to be reset on keypress too(?)
			// hacky re-used code but whatevah man take it easy :^)
			piece temp;
			temp.x = new.x;
			temp.y = new.y - 1;
			copy(temp.data, new.data); // copy array from "new" to "temp"
			if (check(board, temp)) {
				new.y--;
			} else {
				//puts("collide");
				merge(board, new);

				for (int i = 0; i < 4; i++) { // clears "new.data" to make another tetrimino
					for (int j = 0; j < 4; j++) {
						new.data[i][j] = 0;
					}
				}
				new = tetrimino(new); // fills out "new.data"
				rotateRight(new.data); // needs to be rotated right away for some reason
				new.y = new.y;
			}
		}

		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) { // ESC -> EXIT
			glfwSetWindowShouldClose(window, 1);
		}

		// Render
		render(board, new, rgb);

		// Swap front & back buffers
		glfwSwapBuffers(window);

		// Poll for and process events
		glfwPollEvents();
		//glfwWaitEvents();
	}
	glfwTerminate();

	return 0;
}
