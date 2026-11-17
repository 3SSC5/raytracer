#include <fstream>
#include <iostream>
#define MAX_VALUE 255
#define WIDTH 256
#define HEIGHT 256

int main() {
    std::ofstream file("gradient.ppm"); // making the file containing gradient
    if (!file.is_open()) {
        std::cout << "Error creating file";
        return 1;
    }

    // generating the ppm header
    file << "P3\n";
    file << WIDTH << " " << HEIGHT << "\n";
    file << MAX_VALUE << "\n";

    for (int i = 1; i <= HEIGHT; i++) {
        for (int j = 1; j <= WIDTH; j++) {
            double gradient_height = (double) i / HEIGHT;
            double gradient_width = (double) j / WIDTH;
            int red = gradient_height * MAX_VALUE;
            int blue = gradient_width * MAX_VALUE;

            file << red << " " << 0 << " " << blue << " ";
        }

        file << "\n";
    }

    file.close();

    return 0;
}