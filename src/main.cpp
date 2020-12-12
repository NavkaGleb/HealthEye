#include "Application/Application.hpp"

int main() {
    Hey::Application application(1920, 1080, "SFML + ImGui = <3");
    application.Run();

    return 0;
}