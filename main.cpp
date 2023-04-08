#include <iostream>
#include "glew.h"
#include "glfw3.h"

using namespace std;

int main() {
    cout << "Hello, World!" << endl;

    GLFWwindow* window;

    if (!glfwInit()) {
        return -1;
    }


    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello OpenGL", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    GLenum err = glewInit();
    if (GLEW_OK != err) {
        ::fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    }

    //输出gl版本号
    cout<<glGetString(GL_VERSION)<<endl;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        //画一个简单的三角形
        glBegin(GL_TRIANGLES);
        glVertex2f(-0.5f, -0.5f);
        glVertex2f(0.0f, 0.5f);
        glVertex2f(0.5f, -0.5f);
        glEnd();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();


    return 0;
}
