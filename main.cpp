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


    unsigned int buffer;
    //生成一个顶点缓冲区，buffer为其ID
    glGenBuffers(1, &buffer);
    //绑定对应ID的缓冲区，指明buffer类型
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    //定义三角形顶点数据
    float positions[6] = {
        -0.5f, -0.5f,
        0.0f, 0.5f,
        0.5f, -0.5f
    };
    //定义缓冲区大小
    glBufferData(GL_ARRAY_BUFFER,  6 * sizeof(float), positions, GL_STATIC_DRAW);

    //告诉openGL如何布局  目前这个例子中的一个vertex只包含一个属性，就是坐标
    //对一个vertex进行布局  首先开启属性，当前例子中只有坐标
    glEnableVertexAttribArray(0);
    //0 vertex中第一个属性的index， 2：该属性的维度， GL_FLOAT: 数据类型， false：是否归一化
    //stride步长  0：属性对象指针
    glVertexAttribPointer(0, 2, GL_FLOAT, false, 2 * sizeof(float ), 0);


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();


    return 0;
}

//画一个简单的三角形 使用老的opengl接口
//        glBegin(GL_TRIANGLES);
//        glVertex2f(-0.5f, -0.5f);
//        glVertex2f(0.0f, 0.5f);
//        glVertex2f(0.5f, -0.5f);
//        glEnd();
