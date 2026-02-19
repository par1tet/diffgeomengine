#include<iostream>
#include<core/classes/visual/MetricGrid.hpp>
#include<core/classes/compute/partical_differentiation.hpp>
#include<cmath>
#include<libs/glad/include/glad/glad.h>
#include<core/utility/createShaderProgram.hpp>
#include<GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>

// TODO: 1. Доделать класс многообразия
// 2. Вынести функции отрисовки
// 3. Добавить силу на многообразии
// 4. Рефактор кода, и сделать номральную архитектуру
// 5. Сделать произвольный клиппинг, что бы работала произвольная метрика

std::vector<glm::vec2> makeThickLine(
    const std::vector<glm::vec2>& points,
    float width)
{
    std::vector<glm::vec2> vertices;

    if(points.size() < 2) return vertices;

    float half = width * 0.5f;

    for(size_t i = 0; i < points.size() - 1; ++i)
    {
        glm::vec2 p0 = points[i];
        glm::vec2 p1 = points[i+1];

        glm::vec2 diff = p1 - p0;

        if(glm::length(diff) < 1e-8f)
            continue;

        glm::vec2 dir = glm::normalize(diff);
        glm::vec2 normal(-dir.y, dir.x);
        glm::vec2 offset = normal * half;

        glm::vec2 A = p0 + offset;
        glm::vec2 B = p0 - offset;
        glm::vec2 C = p1 + offset;
        glm::vec2 D = p1 - offset;

        vertices.push_back(A);
        vertices.push_back(B);
        vertices.push_back(C);

        vertices.push_back(C);
        vertices.push_back(B);
        vertices.push_back(D);
    }

    return vertices;
}

double omega(double x, double y){
    double r2 = x*x + y*y;
    double alpha = 1.4;
    return alpha * exp(-r2);
}

double r(std::vector<double> x){
    double acc = 0;
    for(double c : x){
        acc+=c;
    }
    return acc;
}

double func1(std::vector<double> x){
    return 1.0;
}

double func2(std::vector<double> x){
    return sin(x[0])*sin(x[0]);
}

std::vector<double> embedding(std::vector<double> x_coo){
    std::vector<std::vector<double>> matrix = {
        {1, 0},
        {0, 1}
    };
    int n = x_coo.size();

    std::vector<double> x_dec(n, 0);
    
    for(int i = 0;i != n;i++){
        for(int j = 0;j != n;j++){
            x_dec[i] += x_coo[j] * matrix[i][j];
        }
    }

    x_dec[0] = x_coo[0] * cos(x_coo[1]);
    x_dec[1] = x_coo[0] * sin(x_coo[1]);

    return x_dec;
}

int main(){
    std::vector<std::function<double(const std::vector<double>&)>> funcs = {func1, func2};
    Metric* metric = new Metric(funcs);
    Manifold* manifold = new Manifold(metric);
    MetricGrid* grid = new MetricGrid(manifold);

    double time = 7.f;
    double dx = 0.05f;

    std::vector<Curve> geodesicCurves = grid->computePoints({7,6}, {1.2f, 10 * M_PI/6}, embedding, time, dx, 4, {1,1});

    std::vector<std::vector<glm::vec2>> geodesicCurves_glm;
    geodesicCurves_glm.reserve(geodesicCurves.size());

    for (const auto& layer : geodesicCurves) {
        std::vector<glm::vec2> vecLayer;
        for (const auto& v : layer.points) {
            if (v.size() >= 2) {
                vecLayer.emplace_back(v[0], v[1]);
            }
        }
        geodesicCurves_glm.push_back(vecLayer);
    } 

    std::vector<glm::vec2> thickVertices;

    for(const auto& curve : geodesicCurves_glm)
    {
        auto thick = makeThickLine(curve, 0.03f);

        thickVertices.insert(
            thickVertices.end(),
            thick.begin(),
            thick.end()
        );
    }
    // OpenGL
    
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(800, 800, "Geodesics", NULL, NULL);
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    if (!window){
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Включаем сглаживание точек (опционально)
    glEnable(GL_POINT_SMOOTH);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);

    glm::mat4 projection = 1.f * glm::ortho(-6.f, 6.f,
                                  -6.f, 6.f);

    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER,
             thickVertices.size() * sizeof(glm::vec2),
             thickVertices.data(),
             GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE,
                        sizeof(glm::vec2), (void*)0);
    glEnableVertexAttribArray(0);

    glViewport(0, 0, 800, 800);

    GLuint shaderProgram = createShaderProgram(
        "/home/par1tet/reps/diffgeomengine/src/shaders/vertex_shader.glsl",
        "/home/par1tet/reps/diffgeomengine/src/shaders/fragment_shader.glsl"
    );

    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);

        GLuint colorLoc = glGetUniformLocation(shaderProgram, "color");
        GLuint projLoc  = glGetUniformLocation(shaderProgram, "projection");

        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
        glUniform3f(colorLoc, 1.0f, 1.0f, 1.0f);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER,
                    thickVertices.size() * sizeof(glm::vec2),
                    thickVertices.data(),
                    GL_STATIC_DRAW);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, thickVertices.size());

        glfwSwapBuffers(window);
    }

    //-----------

    delete metric;
    delete manifold;
    return 0;
}
