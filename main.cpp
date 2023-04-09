#include <iostream>
#include "glew.h"
#include "glfw3.h"
#include "fstream"
#include "sstream"
#include "string"

using namespace std;

struct ShaderProgramSource {
    string vertexSource;
    string fragmentSource;
};

static ShaderProgramSource parseShader(const string& filePath) {

    enum class ShaderType {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    ifstream stream(filePath);
    string line;
    stringstream ss[2];
    ShaderType shaderType = ShaderType::NONE;
    while (getline(stream, line)) {
        if (line.find("#shader") != string::npos) {
            if (line.find("vertex") != string::npos) {
                shaderType = ShaderType::VERTEX;
            } else if (line.find("fragment") != string::npos) {
                shaderType = ShaderType::FRAGMENT;
            }
        } else {
            ss[(int)shaderType]<<line<<'\n';
        }
    }
    return {ss[0].str(), ss[1].str()};
}


static unsigned int compileShader(unsigned int type, const string& source) {
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);
    // todo error handling

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char *)alloca(length * sizeof (char));
        glGetShaderInfoLog(id, length, &length, message);
        cout<<"Fail "<<type<<" Compile:"<<endl;
        cout<<message<<endl;
        glDeleteShader(id);
        return 0;
    }
    return id;
}

static unsigned int CreateShader(const string& vertexShader, const string& fragmentShader) {
    unsigned int program = glCreateProgram();
    unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);
    return program;
}



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


    ShaderProgramSource programSource = parseShader("../res/shaders/BasicShader.shader");
    cout<< "Vertex Shader Source:" <<endl;
    cout<<programSource.vertexSource<<endl;
    cout<< "Fragment Shader Source:"<<endl;
    cout<<programSource.fragmentSource<<endl;

    unsigned int shader = CreateShader(programSource.vertexSource, programSource.fragmentSource);
    glUseProgram(shader);

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
