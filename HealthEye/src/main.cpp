#include "Application/Application.hpp"

int main() {
    Hey::Application application(1080, 720, "SFML + ImGui = <3");
    application.Run();

    return 0;
}