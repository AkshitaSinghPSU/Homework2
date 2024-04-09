#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <iostream>

const double air_density = 1.225;
const double lift_coefficient = 0.7;
const double wing_area = 10.0;

double liftEquation(double airspeed) {
    return lift_coefficient * 0.5 * air_density * airspeed * airspeed * wing_area;
}

int main() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(500, 500, "Sine Curve using OpenGL with GLEW and GLFW", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        glBegin(GL_LINES);
        glColor3f(1.0, 1.0, 1.0);
        glVertex2f(-1.0, 0.0);
        glVertex2f(1.0, 0.0);
        glVertex2f(0.0, -1.0);
        glVertex2f(0.0, 1.0);
        glEnd();

        glBegin(GL_LINE_STRIP);
        glColor3f(0.0, 1.0, 0.0);
        double speed = 0.0;
        while (speed <= 100.0) {
            double lift = liftEquation(speed);
            glVertex2f(speed / 100.0, lift / 100.0);
            speed += 0.1;
        }
        glEnd();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
