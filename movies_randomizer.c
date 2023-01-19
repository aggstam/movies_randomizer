// -------------------------------------------------------------
//
// This program suggest a random movie from the dataset of tsv files.
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

#define DATASET_DIR "dataset"

// Read dataset folder to retrieve available genres
char** available_genres() {
    char** genres = (char**)malloc(sizeof(char*));
    DIR* dataset_dir = opendir(DATASET_DIR);
    struct dirent *entry;

    // Check if we could open the directory
    if (dataset_dir == NULL) {
        printf("Error: Failed to open dataset directory: %s\n", strerror(errno));
        genres[0] = NULL;
        return genres;
    }

    // Iterate through files
    int i = 0;
    while (entry = readdir(dataset_dir)){
        // Ignore ., .. and non .tsv files
        if (!strcmp(entry->d_name, ".")) {
            continue;
        }
        if (!strcmp(entry->d_name, "..")) {
            continue;
        }
        int len = strlen(entry->d_name);
        if ((len < 4) || (strcmp(&(entry->d_name[len - 4]), ".tsv") != 0)) {
            continue;
        }

        // Copy file name
        genres[i] = malloc(strlen(entry->d_name) - 4);
        strcpy(genres[i], entry->d_name);
        // Remove extension
        genres[i][len - 4] = '\0';
        i++;
    }
    genres[i] = NULL;

    return genres;
}

int main(int argc, char** argv) {
    // Parse genre argument
    char* genre = argv[1];
    if ((genre != NULL) && (genre[0] == '\0')) {
        genre = "all";
    }

    // Retrieve available genres
    char** genres = available_genres();
    if (genres[0] == NULL) {
        printf("No genres were found, terminating.");
        free(genres);
        return 0;
    }

    // If requested genre is all we search for suggestion
    if (strcmp("all", genre) == 0) {
        printf("Suggesting a movie from genre: %s\n", genre);
        // TODO: add sugestion call here
        free(genres);
        return 0;
    }

    // Otherwise check if we have requested gender
    int i = 0;
    while (1) {
	    if (genres[i] == NULL) {
	        break;
	    }
	    if (strcmp(genres[i], genre) == 0) {
	        printf("Suggesting a movie from genre: %s\n", genre);
	        // TODO: add sugestion call here
	        free(genres);
            return 0;
	    }
	    i++;
	}

	// Genre not found
	printf("Requested genre %s not found.\n", genre);
	printf("Available genres:\n");
	i = 0;
	while (1) {
	    if (genres[i] == NULL) {
	        break;
	    }
	    printf("\t%s\n", genres[i]);
	    i++;
	}
    
    free(genres);
    return 0;
}
