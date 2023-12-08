#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main() 
{
    const char *filename = "example.txt";
    int file_descriptor;

    // Open the file in read-only mode
    file_descriptor = open(filename, O_RDONLY);

    if (file_descriptor == -1) 
    {
        perror("Error opening file");
        return 1;
    }

    // Print the file descriptor
    printf("app: File opened successfully. File Descriptor: %d\n", file_descriptor);

    // Close the file
    if (close(file_descriptor) == -1) 
    {
        perror("Error closing file");
        return 1;
    }

    return 0;
}