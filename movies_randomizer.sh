#!/bin/bash
# --------------------------------------------------------------------------
#
# This script suggest a random movie from the dataset of tsv files.
#
# Author: Aggelos Stamatiou, January 2023
#
# This source code is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This software is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this source code. If not, see <http://www.gnu.org/licenses/>.
# --------------------------------------------------------------------------

DATASET_DIR="dataset"

# Parse genre argument
genre=$1
if [ -z "$1" ]; then
    genre="all"
fi

# Retrieve available genres
genres=$(ls $DATASET_DIR -1 | sed -e 's/\.tsv$//')

# If requested genre is all we search for suggestion
if [ "$genre" = "all" ]; then
    echo "Suggesting a movie from genre: $genre"
    # TODO: add sugestion call here
    exit
fi

# Otherwise check if we have requested gender
for g in $genres; do
    if [ "$genre" = "$g" ]; then
        echo "Suggesting a movie from genre: $genre"
        # TODO: add sugestion call here
        exit
    fi
done

# Genre not found
echo "Requested genre $genre not found."
echo "Available genres:"
for g in $genres; do
    echo "    $g"
done
