# movies_randomizer

Suggest a random movie from the dataset of PSV(Pipe-Separated Values) files.
<br>
Filenames act as genre, so user can select one to get a suggestion from.
<br>
Records format is the following:
```
{Name}|{Year}|{Duration}
```

# Usage
Two version have been implemented, one with pure C, and a bash script.
<br>
Both can be invocted via the Makefile, or by directly compiling and executing.

## Make usage
### C code
```
% make
```
To include a genre as parameter:
```
% make GENRE={genre}
```

### Bash script
```
% make script
```
To include a genre as parameter:
```
% make script GENRE={genre}
```

## Direct usage
### C code
Compilation:
```
% gcc -o movies_randomizer movies_randomizer.c
```
Execution:
```
% ./movies_randomizer
```

### Bash script
Mark as executable:
```
% chmod a+x movies_randomizer.sh
```
Execution:
```
% ./movies_randomizer.sh
```
