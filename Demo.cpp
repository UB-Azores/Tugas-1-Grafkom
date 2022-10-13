#include "Demo.h"
using namespace std;

Demo::Demo() {

}

Demo::~Demo() {
}

void Demo::Init() {
	// build and compile our shader program
	// ------------------------------------
	shaderProgram = BuildShader("vertexShader.vert", "fragmentShader.frag", nullptr);

	BuildColoredCube();

	BuildColoredPlane();

	InitCamera();
	InitPoints();
}

void Demo::DeInit() {
	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteVertexArrays(1, &VAO2);
	glDeleteBuffers(1, &VBO2);
	glDeleteBuffers(1, &EBO2);
}

void Demo::ProcessInput(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}

	/*
	// zoom camera
	// -----------
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
		if (fovy < 90) {
			fovy += 0.01f;
		}
	}

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		if (fovy > 0) {
			fovy -= 0.01f;
		}
	}

// update camera movement 
// -------------
if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
	MoveCamera(CAMERA_SPEED);
}
if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
	MoveCamera(-CAMERA_SPEED);
}

if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
	StrafeCamera(-CAMERA_SPEED);
}

if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
	StrafeCamera(CAMERA_SPEED);
}

if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
	UpCamera(-CAMERA_SPEED);
}

if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
	UpCamera(CAMERA_SPEED);
}


// update camera rotation
// ----------------------
double mouseX, mouseY;
double midX = screenWidth / 2;
double midY = screenHeight / 2;
float angleY = 0.0f;
float angleZ = 0.0f;

// Get mouse position
glfwGetCursorPos(window, &mouseX, &mouseY);
if ((mouseX == midX) && (mouseY == midY)) {
	return;
}

// Set mouse position
glfwSetCursorPos(window, midX, midY);

// Get the direction from the mouse cursor, set a resonable maneuvering speed
angleY = (float)((midX - mouseX)) / 300;
angleZ = (float)((midY - mouseY)) / 200;

// The higher the value is the faster the camera looks around.
viewCamY += angleZ * 2;

// limit the rotation around the x-axis
if ((viewCamY - posCamY) > 8) {
	viewCamY = posCamY + 8;
}
if ((viewCamY - posCamY) < -8) {
	viewCamY = posCamY - 8;
}
RotateCamera(-angleY);
/**/

}

void Demo::Update(double deltaTime) {
	angle += (float)((deltaTime * 1.5f) / 100);

	/*
	if (pindahX <= 1 || pindahX >= 11) {
		speedX *= -1;
	}
	//pindahX += (float)((deltaTime * speedX) / 500);
	//posCamX += (float)((deltaTime * speedX) / 500);

	if (pindahY <= 1 || pindahY >= 4) {
		speedY *= -1;
		if (pindahY >= 4) {
			cubeColor = 1;
			planeColor = 0;
		}
		if (pindahY <= 1) {
			cubeColor = 0;
			planeColor = 1;
		}
	}
	//pindahY += (float)((deltaTime * speedY) / 1000);
	//posCamY += (float)((deltaTime * speedY) / 1000);

	if (pindahZ <= 1 || pindahZ >= 4) {
		speedZ *= -1;
	}
	//pindahZ += (float)((deltaTime * speedZ) / 1000);
	//posCamZ += (float)((deltaTime * speedZ) / 1000);
	*/

	/*
	std::cout << "\n\ni : " << i << "\n";
	std::cout << "j : " << j << "\n\n";
	float laju = 10;
	if (i == totalPoint/4) {
		pTemp += 3;
		while (pindahZ > piZ[pTemp]) {
			pindahZ += (float)((deltaTime * -1) / laju);
		}
		j = 0;
	}
	else if (i == totalPoint/2) {
		pTemp += 3;
		while (pindahX < piX[pTemp]) {
			pindahX += (float)((deltaTime * 1) / laju);
		}
		j = 0;
	}
	else if (i == totalPoint*3/4) {
		pTemp += 3;
		while (pindahZ < piZ[pTemp]) {
			pindahZ += (float)((deltaTime * 1) / laju);
		}
		j = 0;
	}
	else if (i == totalPoint-1) {
		pTemp += 3;
		while (pindahX > piX[pTemp]) {
			pindahX += (float)((deltaTime * -1) / laju);
		}
		j = 0;
	}

	if (i == totalPoint-1) {
		pindahX = piX[0];
		pindahZ = piZ[0];
		pTemp = 0;
		i = -1;
		j = 0;
	}
	else {
		double t = (float)j / totalPoint;
		lineX[i] = ((1 - t) * (1 - t) * piX[pTemp]) + (2 * (1 - t) * t * piX[pTemp + 1]) + (t * t * piX[pTemp + 2]);
		lineZ[i] = ((1 - t) * (1 - t) * piZ[pTemp]) + (2 * (1 - t) * t * piZ[pTemp + 1]) + (t * t * piX[pTemp + 2]);

		while (pindahX < lineX[i]) {
			pindahX += (float)((deltaTime * 1) / laju);
		}
		while (pindahX > lineX[i]) {
			pindahX += (float)((deltaTime * -1) / laju);
		}
		while (pindahZ < lineZ[i]) {
			pindahZ += (float)((deltaTime * 1) / laju);
		}
		while (pindahZ > lineZ[i]) {
			pindahZ += (float)((deltaTime * -1) / laju);
		}
		j += totalPoint/4;
		std::cout << "t : " << t << "\n";
	}
	std::cout << "lineX : " << lineX[i] << "\n";
	std::cout << "lineZ : " << lineZ[i] << "\n";
	std::cout << "piX : " << piX[pTemp] << "\n";
	std::cout << "piZ : " << piZ[pTemp] << "\n";
	std::cout << "pindahX : " << pindahX << "\n";
	std::cout << "pindahZ : " << pindahZ << "\n";

	i++;
	/**/

	/*
	for (i = 0; i < totalPoint; i++) {
		//std::cout << "\n\ni : " << i << "\n\n";
		if (tTemp == 100) {
			tTemp = 0;
		}

		if (i == totalPoint / 4) {
			pTemp += 3;
			lineZ[i] = lineZ[i - 1] - 12;
			lineX[i] = lineX[i - 1];
			//DrawColoredCube(0, lineX[i], 0, lineZ[i], 0.5, 0.5, 0.5);
		}
		else if (i == totalPoint / 2) {
			pTemp += 3;
			lineX[i] = lineX[i - 1] + 12;
			lineZ[i] = lineZ[i - 1];
			//DrawColoredCube(0, lineX[i], 0, lineZ[i], 0.5, 0.5, 0.5);
		}
		else if (i == totalPoint * 3 / 4) {
			pTemp += 3;
			lineZ[i] = lineZ[i - 1] + 12;
			lineX[i] = lineX[i - 1];
			//DrawColoredCube(0, lineX[i], 0, lineZ[i], 0.5, 0.5, 0.5);
		}
		else if (i == totalPoint) {
			pTemp += 3;
			lineX[i] = lineX[i - 1] - 12;
			lineZ[i] = lineZ[i - 1];
			break;
			//DrawColoredCube(0, lineX[i], 0, lineZ[i], 0.5, 0.5, 0.5);
		}
		//std::cout << "t : " << t << "\n";
		t = (float)tTemp / (totalPoint / 4);
		lineX[i] = ((1 - t) * (1 - t) * piX[pTemp]) + (2 * (1 - t) * t * piX[pTemp + 1]) + (t * t * piX[pTemp + 2]);
		lineZ[i] = ((1 - t) * (1 - t) * piZ[pTemp]) + (2 * (1 - t) * t * piZ[pTemp + 1]) + (t * t * piZ[pTemp + 2]);
		tTemp++;
		//DrawColoredCube(0, lineX[i], 0, lineZ[i], 0.5, 0.5, 0.5);

		//std::cout << "lineX : " << lineX[i] << "\n";
		//std::cout << "lineZ : " << lineZ[i] << "\n";
		//std::cout << "piX : " << piX[pTemp] << "\n";
		//std::cout << "piZ : " << piZ[pTemp] << "\n";

	}/**/

	/*if (pindahX != lineX[i] || pindahZ != lineZ[i]) {
		if (pindahX < lineX[i]) {
			pindahX += (float)((deltaTime * 1) / 100);
		}
		else if (pindahX > lineX[i]) {
			pindahX += (float)((deltaTime * -1) / 100);
		}
		else if (pindahZ < lineZ[i]) {
			pindahZ += (float)((deltaTime * 1) / 100);
		}
		else if (pindahZ > lineZ[i]) {
			pindahZ += (float)((deltaTime * -1) / 100);
		}

		i++;
		if (i == totalPoint) {
			i = 0;
		}
	}*/

	/*
	float laju = 100;
	std::cout << "\n\ni : " << i << "\n\n";
	if (i == totalPoint) {
		pindahX = 0;
		//posCamX = 12;
		pindahZ = 0;
		//posCamZ = 0;
		i = 0;
	}

	if (i <= 100) {
		if (pindahX > lineX[i]) {
			pindahX += (float)((deltaTime * -1) / laju);
			//posCamX += (float)((deltaTime * -1) / laju);
		}
		if (pindahZ > lineZ[i]) {
			pindahZ += (float)((deltaTime * -1) / laju);
			//posCamZ += (float)((deltaTime * -1) / laju);
		}
	}
	else if (i > 100 && i <= 200) {
		if (pindahX < lineX[i]) {
			pindahX += (float)((deltaTime * 1) / laju);
			//posCamX += (float)((deltaTime * 1) / laju);
		}
		if (pindahZ > lineZ[i]) {
			pindahZ += (float)((deltaTime * -1) / laju);
			//posCamZ += (float)((deltaTime * -1) / laju);
		}
	}
	else if (i > 200 && i <= 300) {
		if (pindahX < lineX[i]) {
			pindahX += (float)((deltaTime * 1) / laju);
			//posCamX += (float)((deltaTime * 1) / laju);
		}
		if (pindahZ < lineZ[i]) {
			pindahZ += (float)((deltaTime * 1) / laju);
			//posCamZ += (float)((deltaTime * 1) / laju);
		}
	}
	else if (i > 300 && i <= 400) {
		if (pindahX > lineX[i]) {
			pindahX += (float)((deltaTime * -1) / laju);
			//posCamX += (float)((deltaTime * -1) / laju);
		}
		if (pindahZ < lineZ[i]) {
			pindahZ += (float)((deltaTime * 1) / laju);
			//posCamZ += (float)((deltaTime * 1) / laju);
		}
	}
	i++;
	/**/


	/*std::cout << "\n\nj : " << j << "\n";
	std::cout << "pindahX : " << pindahX << "\n";
	std::cout << "pindahZ : " << pindahZ << "\n";
	std::cout << "lineX : " << lineX[j] << "\n";
	std::cout << "lineZ : " << lineZ[j] << "\n";

	if (j == 99) {
		std::cout << "\nini j 100\n";
		while (pindahZ > lineZ[j + 1]) {
			pindahZ += (float)((deltaTime * -1) / 10);
		}
	}
	else if (j == 199) {
		std::cout << "\nini j 200\n";
		while (pindahX < lineX[j + 1]) {
			pindahX += (float)((deltaTime * 1) / 10);
		}
	}
	else if (j == 299) {
		std::cout << "\nini j 300\n";
		while (pindahZ < lineZ[j + 1]) {
			pindahZ += (float)((deltaTime * 1) / 10);
		}
	}
	else if (j == 399) {
		std::cout << "\nini j 400\n";
		while (pindahX > lineX[j + 1]) {
			pindahX += (float)((deltaTime * -1) / 10);
		}
	}*/
	
		pindahX = lineX[j];
		posCamX = pindahX + 15;

		pindahZ = lineZ[j];
		posCamZ = pindahZ;

	j++;
	if (j == totalPoint) {
		pindahX = lineX[0];
		pindahZ = lineZ[0];
		j = 0;
	}
	
}

void Demo::Render() {
	glViewport(0, 0, this->screenWidth, this->screenHeight);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(55.0f/255.0f, 198.0f / 255.0f, 255.0f / 255.0f, 1.0f);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glEnable(GL_DEPTH_TEST);

	// Pass perspective projection matrix
	glm::mat4 projection = glm::perspective(fovy, (GLfloat)this->screenWidth / (GLfloat)this->screenHeight, 0.1f, 100.0f);
	GLint projLoc = glGetUniformLocation(this->shaderProgram, "projection");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

	// LookAt camera (position, target/direction, up)
									  //eyeX,eyeY,eye  centerX,centerY,centerZ,   upX,upY,upZ
	glm::mat4 view = glm::lookAt(glm::vec3(posCamX, posCamY, posCamZ), glm::vec3(pindahX, pindahY, pindahZ), glm::vec3(0, 1, 0));
	//glm::mat4 view = glm::lookAt(glm::vec3(posCamX, posCamY, posCamZ), glm::vec3(viewCamX, viewCamY, viewCamZ), glm::vec3(upCamX, upCamY, upCamZ));
	GLint viewLoc = glGetUniformLocation(this->shaderProgram, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

	// Body
	DrawColoredCube(0, 0, 2, 0, 6, 3, 3);

	// Connector Belakang
	DrawColoredCube(0, 4, 2, 0, 5, 1.5, 1.5);

	// Baling2 Belakang
	DrawColoredCube(1, 6, 1.9, 1, 0.5, 3, 0.5);
	DrawColoredCube(1, 6, 1.9, 1, 3, 0.5, 0.5);

	// Connector Atas
	DrawColoredCube(0, 0, 4, 0, 1, 1.5, 1);

	// Baling2 Atas
	DrawColoredCube(2, 0, 4.7, 0, 12, 0.5, 0.5);
	DrawColoredCube(2, 0, 4.7, 0, 0.5, 0.5, 12);
	/**/

	DrawColoredPlane();

	glDisable(GL_DEPTH_TEST);
}

// Cube and Plane Things
void Demo::BuildColoredCube() {
	// load image into texture memory
	// ------------------------------
	// Load and create a texture 
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height;
	unsigned char* image = SOIL_load_image("army.jpg", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords
		// front
		-0.5, -0.5, 0.5, 0, 0,  // 0
		0.5, -0.5, 0.5, 1, 0,   // 1
		0.5,  0.5, 0.5, 1, 1,   // 2
		-0.5,  0.5, 0.5, 0, 1,  // 3

		// right
		0.5,  0.5,  0.5, 0, 0,  // 4
		0.5,  0.5, -0.5, 1, 0,  // 5
		0.5, -0.5, -0.5, 1, 1,  // 6
		0.5, -0.5,  0.5, 0, 1,  // 7

		// back
		-0.5, -0.5, -0.5, 0, 0, // 8 
		0.5,  -0.5, -0.5, 1, 0, // 9
		0.5,   0.5, -0.5, 1, 1, // 10
		-0.5,  0.5, -0.5, 0, 1, // 11

		// left
		-0.5, -0.5, -0.5, 0, 0, // 12
		-0.5, -0.5,  0.5, 1, 0, // 13
		-0.5,  0.5,  0.5, 1, 1, // 14
		-0.5,  0.5, -0.5, 0, 1, // 15

		// upper
		0.5, 0.5,  0.5, 0, 0,   // 16
		-0.5, 0.5,  0.5, 1, 0,  // 17
		-0.5, 0.5, -0.5, 1, 1,  // 18
		0.5, 0.5, -0.5, 0, 1,   // 19

		// bottom
		-0.5, -0.5, -0.5, 0, 0, // 20
		0.5, -0.5, -0.5, 1, 0,  // 21
		0.5, -0.5,  0.5, 1, 1,  // 22
		-0.5, -0.5,  0.5, 0, 1, // 23
	};

	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  5,  6,  4,  6,  7,   // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22   // bottom
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define texcoord pointer layout 1
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void Demo::DrawColoredCube(int rotate, double positionX, double positionY, double positionZ, double scaleX, double scaleY, double scaleZ)
{
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 0);

	glUniform1i(glGetUniformLocation(this->shaderProgram, "isCube"), cubeColor);

	glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	positionX += pindahX;
	positionY += pindahY;
	positionZ += pindahZ;

	glm::mat4 model;
	model = glm::translate(model, glm::vec3(positionX, positionY, positionZ)); //mengatur posisi

	if (rotate == 1) {
		model = glm::rotate(model, angle, glm::vec3(0, 0, 1)); //baling2 belakang
	}
	else if (rotate == 2) {
		model = glm::rotate(model, angle, glm::vec3(0, 1, 0)); //baling2 atas
	}

	model = glm::scale(model, glm::vec3(scaleX, scaleY, scaleZ)); //mengatur ukuran

	GLint modelLoc = glGetUniformLocation(this->shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void Demo::BuildColoredPlane()
{
	// Load and create a texture 
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height;
	unsigned char* image = SOIL_load_image("grass.jpg", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	// Build geometry
	GLfloat vertices[] = {
		// format position, tex coords
		// bottom
		-50.0, -0.5, -50.0,  0,  0,
		 50.0, -0.5, -50.0, 50,  0,
		 50.0, -0.5,  50.0, 50, 50,
		-50.0, -0.5,  50.0,  0, 50,


	};

	GLuint indices[] = { 0,  2,  1,  0,  3,  2 };

	glGenVertexArrays(1, &VAO2);
	glGenBuffers(1, &VBO2);
	glGenBuffers(1, &EBO2);

	glBindVertexArray(VAO2);

	glBindBuffer(GL_ARRAY_BUFFER, VBO2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO2);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
	// TexCoord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0); // Unbind VAO
}

void Demo::DrawColoredPlane()
{
	glUseProgram(shaderProgram);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glUniform1i(glGetUniformLocation(this->shaderProgram, "ourTexture"), 1);

	glUniform1i(glGetUniformLocation(this->shaderProgram, "isCube"), planeColor);

	glBindVertexArray(VAO2); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	glm::mat4 model;
	GLint modelLoc = glGetUniformLocation(this->shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

// Camera Things
void Demo::InitCamera()
{
	posCamX = 12.0;
	posCamY = 8.0;
	posCamZ = 0.0;
	viewCamX = 0.0;
	viewCamY = 1.0;
	viewCamZ = 1.0;
	upCamX = 0.0;
	upCamY = 1.0;
	upCamZ = 0.0;
	CAMERA_SPEED = 0.01f;
	fovy = 45.0f;
	glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Demo::MoveCamera(float speed)
{
	double x = viewCamX - posCamX;
	double z = viewCamZ - posCamZ;
	// forward positive cameraspeed and backward negative -cameraspeed.
	posCamX = posCamX + x * speed;
	posCamZ = posCamZ + z * speed;
	viewCamX = viewCamX + x * speed;
	viewCamZ = viewCamZ + z * speed;
	//pindahX += x * speed;
	//pindahZ += z * speed;
}

void Demo::StrafeCamera(float speed)
{
	double x = viewCamX - posCamX;
	double z = viewCamZ - posCamZ;
	double orthoX = -z;
	double orthoZ = x;

	// left positive cameraspeed and right negative -cameraspeed.
	posCamX = posCamX + orthoX * speed;
	posCamZ = posCamZ + orthoZ * speed;
	viewCamX = viewCamX + orthoX * speed;
	viewCamZ = viewCamZ + orthoZ * speed;
	//pindahX += orthoX * speed;
	//pindahZ += orthoZ * speed;
}

void Demo::UpCamera(float speed)
{
	double y = viewCamY - posCamY;
	// forward positive cameraspeed and backward negative -cameraspeed.
	posCamY = posCamY + y * speed;
	viewCamY = viewCamY + y * speed;
	//pindahY += y * speed;
}

void Demo::RotateCamera(float speed)
{
	double x = viewCamX - posCamX;
	double z = viewCamZ - posCamZ;
	viewCamZ = (float)(posCamZ + glm::sin(speed) * x + glm::cos(speed) * z);
	viewCamX = (float)(posCamX + glm::cos(speed) * x - glm::sin(speed) * z);
}

// Beziar Curve Things
void Demo::InitPoints() {
	/*float piX[12] = { -6.0f, -10.0f, -10.0f, -10.0f, -10.0f, -6.0f , 6.0f  , 10.0f , 10.0f , 10.0f , 10.0f , 6.0f };
	float piZ[12] = { 10.0f, 10.0f , 6.0f  , -6.0f , -10.0f, -10.0f, -10.0f, -10.0f, -6.0f , 6.0f  , 10.f  , 10.0f };*/

	float piX[12] = { 0.0f, -40.0f, -40.0f, -40.0f, -40.0f, 0.0f , 0.0f  , 40.0f , 40.0f , 40.0f , 40.0f , 0.0f };
	float piZ[12] = { 20.0f, 20.0f , 0.0f  , 0.0f , -20.0f, -20.0f, -20.0f, -20.0f, 0.0f , 0.0f  , 20.f  , 20.0f };

	int tTemp = 0;
	int pTemp = 0;
	double t = 0;
	for (int i = 0; i < totalPoint; i++) {

		//std::cout << "\n\ni : " << i << "\n\n";
		//std::cout << "t : " << t << "\n";
		if (tTemp == 100) {
			tTemp = 0;
		}

		if (i == totalPoint/4 || i == totalPoint/2 || i == totalPoint*3/4 || i == totalPoint) {
			pTemp += 3;
		}
		
		t = (float)tTemp / (totalPoint/4);
		lineX[i] = ((1 - t) * (1 - t) * piX[pTemp]) + (2 * (1 - t) * t * piX[pTemp + 1]) + (t * t * piX[pTemp + 2]);
		lineZ[i] = ((1 - t) * (1 - t) * piZ[pTemp]) + (2 * (1 - t) * t * piZ[pTemp + 1]) + (t * t * piZ[pTemp + 2]);
		tTemp++;

		//std::cout << "lineX : " << lineX[i] << "\n";
		//std::cout << "lineZ : " << lineZ[i] << "\n";
		//std::cout << "piX : " << piX[pTemp] << "\n";
		//std::cout << "piZ : " << piZ[pTemp] << "\n";
	}
}

int main(int argc, char** argv) {
	RenderEngine &app = Demo();
	app.Start("Helipokter gas ngeng", 1280, 720, true, false);
}