int square(int x, int y, int size) {
	glBegin(GL_TRIANGLES);
	glVertex3f(x, y, 0.0);
	glVertex3f(x + size, y, 0.0);
	glVertex3f(x, y + size, 0.0); // end of tri 1
	glVertex3f(x + size, y + size, 0.0);
	glVertex3f(x, y + size, 0.0);
	glVertex3f(x + size, y, 0.0); // end of tri 2
	glEnd();
}

int rect(int x, int y, int x2, int y2) {
	// x, y: top left of rectangle
	// x2, y2: bottom right of rectangle
	glBegin(GL_LINES);
	//top
	glVertex3f(x, y, 0.0);
	glVertex3f(x2, y, 0.0);
	//right
	glVertex3f(x2, y, 0.0);
	glVertex3f(x2, y2, 0.0);
	//bottom
	glVertex3f(x2, y2, 0.0);
	glVertex3f(x, y2, 0.0);
	//left
	glVertex3f(x, y2, 0.0);
	glVertex3f(x, y, 0.0);
	glEnd();
}
