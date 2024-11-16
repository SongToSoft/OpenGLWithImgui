#include <GLFW/glfw3.h>

#include <vector>
#include <Windows.h>
#include <imgui/imgui.h>

#include <imguiTestWindow.h>

const char* glsl_version = "#version 130";

void InitImgui(GLFWwindow* window, const char* glsl_version)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    //ImGuiIO& io = ImGui::GetIO();
    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
}

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Open GL Window", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    ImguiTestWindow imguiTestWindow;

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    InitImgui(window, glsl_version);

    std::vector<GLfloat> triangleColor = { 0.80f, 0.3f, 0.02f };

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glClearColor(0.10f, 0.20f, 0.30f, 1.00f);
        //glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBegin(GL_TRIANGLES);
        glColor3f(triangleColor[0], triangleColor[1], triangleColor[2]);
        glVertex3f(0, 1, 0);
        glVertex3f(-1, -1, 0);
        glVertex3f(1, -1, 0);
        glEnd();

        imguiTestWindow.Render(triangleColor);

        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}