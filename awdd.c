#include <stdio.h>
#include <unistd.h>

void clearScreen() {
    printf("\033[H\033[J"); // ANSI escape code to clear the screen
    fflush(stdout);
}

// Function to display a frame (you can replace this with your image or ASCII art frames)
void displayFrame() {
    // Display a simple frame (replace this with your frame)
    printf(" ____\n");
    printf("|    |\n");
    printf("|    O\n");
    printf("|   /|\\\n");
    printf("|   / \\\n");
    printf("|______\n");
}

int main() {
    // Modify this loop to display your frames in sequence
    int frameCount = 100; // Number of frames or duration of animation

    for (int i = 0; i < frameCount; i++) {
        // clearScreen(); // Clear the screen before displaying the next frame
        displayFrame(); // Display the frame
        usleep(100000); // Delay between frames (adjust for desired speed)
    }

    return 0;
}
