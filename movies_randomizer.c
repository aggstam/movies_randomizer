// -------------------------------------------------------------
//
// This program suggest a random movie from the dataset of PSV(Pipe-Separated Values) files.
//
// Author: Aggelos Stamatiou, January 2023
//
// This source code is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This software is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this source code. If not, see <http://www.gnu.org/licenses/>.
// --------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <time.h>

#define DATASET_DIR "dataset"

// Read dataset folder to retrieve available genres
char** available_genres(size_t* elements) {
    char** genres = (char**)malloc(sizeof(char*));
    DIR* dataset_dir = opendir(DATASET_DIR);
    struct dirent *entry;

    // Check if we could open the directory
    if (dataset_dir == NULL) {
        printf("Error: Failed to open dataset directory: %s\n", strerror(errno));
        return genres;
    }

    // Iterate through files
    while (entry = readdir(dataset_dir)){
        // Ignore ., .. and non .psv files
        if (!strcmp(entry->d_name, ".")) {
            continue;
        }
        if (!strcmp(entry->d_name, "..")) {
            continue;
        }
        int len = strlen(entry->d_name);
        if ((len < 4) || (strcmp(&(entry->d_name[len - 4]), ".psv") != 0)) {
            continue;
        }

        // Copy file name
        genres[*elements] = malloc(strlen(entry->d_name) - 4);
        strcpy(genres[*elements], entry->d_name);
        // Remove extension
        genres[*elements][len - 4] = '\0';
        *elements += 1;
    }

    return genres;
}

// Auxillary function to randomly select a record from
// provided .psv file
void suggest(char* genre) {
    // Generating file path
    char path[1024];
    strcat(path, DATASET_DIR);
    strcat(path, "/");
    strcat(path, genre);
    strcat(path, ".psv");
    printf("Openning file: %s\n", path);

    // Open file
    FILE* file = fopen(path, "r");
    if (file == NULL) {
        printf("Error: Failed to open file: %s\n", strerror(errno));
        fclose(file);
    }

    // Retrieve records
    char** records = (char**)malloc(sizeof(char*));
    int elements = 0;
    size_t buff_size = 1024;
    char buffer[buff_size];
    while (fgets(buffer, buff_size, file) != NULL) {
        records[elements] = malloc(buff_size);
        strcpy(records[elements], buffer);
        elements++;
    }

    // Generate suggestion
    char* suggestion = records[rand() % elements];

    // Parse suggestion
    char** parsed = (char**)malloc(sizeof(char*));
    char* part = strtok(suggestion, "|");
    int index = 0;
    while (part != NULL) {
        parsed[index] = malloc(buff_size);
        strcpy(parsed[index], part);
        part = strtok(NULL, "|");
        index++;
    }

    // Print information
    printf("Name: %s\n", parsed[0]);
    printf("Year: %s\n", parsed[1]);
    printf("Duration: %s", parsed[2]);

    // Free memory
    free(records);
}

int main(int argc, char** argv) {
    // Parse genre argument
    char* genre = argv[1];
    if ((genre != NULL) && (genre[0] == '\0')) {
        genre = "all";
    }

    // Retrieve available genres
    size_t elements = 0;
    char** genres = available_genres(&elements);
    if (elements == 0) {
        printf("No genres were found, terminating.");
        free(genres);
        return 0;
    }
    
    // Seed random
    srand(time(NULL));

    // If requested genre is all we search for suggestion
    // from a randomly selected genre
    if (strcmp("all", genre) == 0) {
        genre = genres[rand() % elements];
        printf("Suggesting a movie from randomly selected genre: %s\n", genre);
        suggest(genre);
        free(genres);
        return 0;
    }

    // Otherwise check if we have requested gender
    int i = 0;
    for (i; i < elements; i++) {
        if (strcmp(genres[i], genre) == 0) {
            printf("Suggesting a movie from genre: %s\n", genre);
            suggest(genre);
            free(genres);
            return 0;
        }
    }

    // Genre not found
    printf("Requested genre %s not found.\n", genre);
    printf("Available genres:\n");
    for (i = 0; i < elements; i++) {
        printf("\t%s\n", genres[i]);
    }
    
    free(genres);
    return 0;
}
