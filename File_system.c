#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILENAME_LENGTH 50
#define MAX_FILE_CONTENT_LENGTH 1000
#define MAX_FILES 100

struct File {
    char name[MAX_FILENAME_LENGTH];
    char content[MAX_FILE_CONTENT_LENGTH];
    int size;
};

struct FileSystem {
    struct File files[MAX_FILES];
    int num_files;
};

void initFileSystem(struct FileSystem* fs) {
    fs->num_files = 0;
}

int createFile(struct FileSystem* fs, const char* name) {
    if (fs->num_files >= MAX_FILES) {
        return -1; // File system full
    }

    struct File* file = &fs->files[fs->num_files];
    strcpy(file->name, name);
    file->size = 0;
    fs->num_files++;

    return fs->num_files - 1; // Return the index of the created file
}

int findFileIndex(struct FileSystem* fs, const char* name) {
    for (int i = 0; i < fs->num_files; i++) {
        if (strcmp(fs->files[i].name, name) == 0) {
            return i;
        }
    }
    return -1; // File not found
}

void writeFile(struct FileSystem* fs, const char* name, const char* content) {
    int index = findFileIndex(fs, name);
    if (index != -1) {
        struct File* file = &fs->files[index];
        strncpy(file->content, content, MAX_FILE_CONTENT_LENGTH);
        file->size = strlen(content);
    } else {
        printf("File not found: %s\n", name);
    }
}

void readFile(struct FileSystem* fs, const char* name) {
    int index = findFileIndex(fs, name);
    if (index != -1) {
        struct File* file = &fs->files[index];
        printf("File Content:\n%s\n", file->content);
    } else {
        printf("File not found: %s\n", name);
    }
}

void deleteFile(struct FileSystem* fs, const char* name) {
    int index = findFileIndex(fs, name);
    if (index != -1) {
        for (int i = index; i < fs->num_files - 1; i++) {
            fs->files[i] = fs->files[i + 1];
        }
        fs->num_files--;
        printf("File deleted: %s\n", name);
    } else {
        printf("File not found: %s\n", name);
    }
}

int main() {
    struct FileSystem fs;
    initFileSystem(&fs);

    int choice;
    char filename[MAX_FILENAME_LENGTH];
    char filecontent[MAX_FILE_CONTENT_LENGTH];

    printf("Simple File System\n");

    do {
        printf("\nOptions:\n");
        printf("1. Create File\n");
        printf("2. Write to File\n");
        printf("3. Read File\n");
        printf("4. Delete File\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the filename: ");
                scanf("%s", filename);
                int result = createFile(&fs, filename);
                if (result != -1) {
                    printf("File created with index %d\n", result);
                } else {
                    printf("File system is full. Cannot create more files.\n");
                }
                break;
            case 2:
                printf("Enter the filename: ");
                scanf("%s", filename);
                printf("Enter the content (up to %d characters):\n", MAX_FILE_CONTENT_LENGTH);
                scanf(" %[^\n]", filecontent); // Read until newline
                writeFile(&fs, filename, filecontent);
                break;
            case 3:
                printf("Enter the filename: ");
                scanf("%s", filename);
                readFile(&fs, filename);
                break;
            case 4:
                printf("Enter the filename: ");
                scanf("%s", filename);
                deleteFile(&fs, filename);
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 5);

    return 0;
}


