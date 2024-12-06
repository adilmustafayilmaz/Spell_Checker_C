
# SPELL CHECKER IN C

A simple spell checker implementation in C that identifies misspelled words and suggests corrections based on Levenshtein distance.

## Features
- Loads a dictionary/lexicon from a file
- Checks text input against the lexicon
- Identifies misspelled words with line and column numbers
- Suggests similar words based on Levenshtein distance algorithm
- Handles input and output through files

## Requirements

- C compiler (gcc recommended)
- Standard C libraries


## File Structure

- `spell_checker.c` - Main program source code
- `lexicon.txt` - Dictionary file containing valid words
- `input.txt` - Text file to be spell checked
- `output.txt` - Results of spell check will be written here

## How to Use

1. **Compile the program:**

``` gcc -o spell_checker spell_checker.c```

2.  **Run The Program**

```./spell_checker```

3. **Check the output.txt**

``` 
Incorrect word: 'yopu' at line 1, column 3
Suggestions:
  - you

Incorrect word: 'wroung' at line 2, column 3
Suggestions:
  - wrong
```

## Lisans

[MIT](https://choosealicense.com/licenses/mit/)