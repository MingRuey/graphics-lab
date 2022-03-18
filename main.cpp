#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "model/ObjLoader.h"
#include "shader/ShaderLoader.h"
#include "camera/camera.h";

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    // build and compile our shader program
    // ------------------------------------
    // vertex shader
    //auto loader = ShaderLoader("../shader/projection.vert", "../shader/projection.frag");
    auto loader = ShaderLoader("../shader/shaderBlinnPhong.vs", "../shader/shaderBlinnPhong.fs");
    auto lightShader = ShaderLoader("../shader/shaderBlinnPhong.vs", "../shader/shaderBlinnPhong.fs");
    float* objectColor = new float[3];
    objectColor[0] = 1.0f;
    objectColor[1] = 0.5f;
    objectColor[2] = 0.2f;
    
    float* lightColor = new float[3];
    lightColor[0] = 1.0f;
    lightColor[1] = 0.0f;
    lightColor[2] = 1.0f;

    // light data
    //glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
    float lightPos[] = { -2.0f, 2.0f, 2.0f };
    auto camera = Camera(glm::vec3(0.0f, 0.0f, 4.0f));
    //auto view = glm::mat4(1.0f);
    //auto projection = glm::mat4(1.0f);
    auto view = camera.getViewMatrix();
    auto projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    auto model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(20.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(20.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    auto normalMatrix = glm::mat4(1.0f);

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    ObjLoader target = ObjLoader("../model/cube.obj");
    auto vertices = new float[target.faces.size() * 3 * 3 * 2];

    for (int i = 0; i < target.faces.size(); i++) {
        auto face = target.faces[i];
        for (int j = 0; j < 3; j++) {
            fvec3 vertex;
            fvec3 normal;
            switch (j)
            {
            case 0:
                vertex = target.vertices[face.v1 - 1];
                normal = target.normals[face.n1 - 1];
                break;
            case 1:
                vertex = target.vertices[face.v2 - 1];
                normal = target.normals[face.n2 - 1];
                break;
            case 2:
                vertex = target.vertices[face.v3 - 1];
                normal = target.normals[face.n3 - 1];
                break;
            default:
                vertex = target.vertices[face.v1 - 1];
                normal = target.normals[face.n1 - 1];
                break;
            }
            vertices[i * 18 + j * 6] = vertex.x;
            vertices[i * 18 + j * 6 + 1] = vertex.y;
            vertices[i * 18 + j * 6 + 2] = vertex.z;
            vertices[i * 18 + j * 6 + 3] = normal.x;
            vertices[i * 18 + j * 6 + 4] = normal.y;
            vertices[i * 18 + j * 6 + 5] = normal.z;
        }
    }

    // Create Data
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);

    // VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(*vertices)* target.faces.size() * 3 * 3 * 2, vertices, GL_STATIC_DRAW);

    // VAO
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    unsigned int lightCubeVAO;
    glGenVertexArrays(1, &lightCubeVAO);
    glBindVertexArray(lightCubeVAO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // draw our first triangle
        
        loader.use();
        loader.setVec3("objectColor", objectColor);
        loader.setVec3("lightPosition", &lightPos[0]);
        loader.setVec3("vuewPosition", &camera.Position[0]);
        loader.setMat4("projMatrix", &projection[0][0]);
        loader.setMat4("viewMatrix", &view[0][0]);
        loader.setMat4("modelMatrix", &model[0][0]);
        loader.setMat4("normalMatrix", &normalMatrix[0][0]);
        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        glDrawArrays(GL_TRIANGLES, 0, 3*target.faces.size());
        // glBindVertexArray(0); // no need to unbind it every time
        
        lightShader.use();
        lightShader.setVec3("objectColor", lightColor);
        lightShader.setVec3("lightPosition", &lightPos[0]);
        lightShader.setVec3("vuewPosition", &camera.Position[0]);
        lightShader.setMat4("projMatrix", &projection[0][0]);
        lightShader.setMat4("viewMatrix", &view[0][0]);
        auto model2 = glm::mat4(model);
        model2 = glm::translate(model2, glm::vec3(0.0f,1.0f,0.0f));
        model2 = glm::scale(model2, glm::vec3(0.2f));
        lightShader.setMat4("modelMatrix", &model2[0][0]);
        lightShader.setMat4("normalMatrix", &normalMatrix[0][0]);
        glBindVertexArray(lightCubeVAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        glDrawArrays(GL_TRIANGLES, 0, 3*target.faces.size());


        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    loader.remove();

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}
