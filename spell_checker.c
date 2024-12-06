#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h> 

#define MAX_WORDS 10000
#define MAX_WORD_LENGTH 100
#define MAX_LINE_LENGTH 1000

char W[MAX_WORDS][MAX_WORD_LENGTH];
int word_count = 0;

// Function prototypes
void load_lexicon(const char *filename);
int is_similar(const char *word1, const char *word2);
void check(const char *input_file, const char *output_file);
int levenshtein_distance(const char *s1, const char *s2);


int main() {
    const char *lexicon_file = "lexicon.txt";  // File containing lexicon
    const char *input_file = "input.txt";     // File to spell-check
    const char *output_file = "output.txt";   // File to store results

    // Load lexicon into W
    load_lexicon(lexicon_file);

    // Perform spell-check
    check(input_file, output_file);

    printf("Spell-check completed. Results written to '%s'.\n", output_file);
    return 0;
}

// Function to load lexicon into the array W
void load_lexicon(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening lexicon file");
        exit(EXIT_FAILURE);
    }

    char word[MAX_WORD_LENGTH];
    while (fscanf(file, "%s", word) != EOF) {
        strcpy(W[word_count++], word);
    }

    fclose(file);
}

// Function to check if two words are similar
int is_similar(const char *word1, const char *word2) {
    // Consider words similar if their Levenshtein distance is 1 or less
    return levenshtein_distance(word1, word2) <= 1;
}


// Levenshtein distance implementation
int levenshtein_distance(const char *s1, const char *s2) {
    int len1 = strlen(s1);
    int len2 = strlen(s2);
    int dp[len1 + 1][len2 + 1];

    for (int i = 0; i <= len1; i++) {
        for (int j = 0; j <= len2; j++) {
            if (i == 0) {
                dp[i][j] = j;
            } else if (j == 0) {
                dp[i][j] = i;
            } else if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                dp[i][j] = 1 + fmin(dp[i - 1][j - 1], fmin(dp[i - 1][j], dp[i][j - 1]));
            }
        }
    }

    return dp[len1][len2];
}

// Function to perform spell-check
void check(const char *input_file, const char *output_file) {
    FILE *infile = fopen(input_file, "r");
    FILE *outfile = fopen(output_file, "w");
    if (!infile || !outfile) {
        perror("Error opening input/output file");
        exit(EXIT_FAILURE);
    }

    char line[MAX_LINE_LENGTH];
    int line_number = 0;

    while (fgets(line, sizeof(line), infile)) {
        line_number++;
        int column_number = 0;
        char *token = strtok(line, " \t\n");

        while (token) {
            column_number++;
            int found = 0;

            // Check if the word is in the lexicon
            for (int i = 0; i < word_count; i++) {
                if (strcmp(token, W[i]) == 0) {
                    found = 1;
                    break;
                }
            }

            if (!found) {
                // Word is misspelled
                fprintf(outfile, "Incorrect word: '%s' at line %d, column %d\n", token, line_number, column_number);
                fprintf(outfile, "Suggestions:\n");

                // Provide suggestions
                for (int i = 0; i < word_count; i++) {
                    if (is_similar(token, W[i])) {
                        fprintf(outfile, "  - %s\n", W[i]);
                    }
                }
                fprintf(outfile, "\n");
            }

            token = strtok(NULL, " \t\n");
        }
    }

    fclose(infile);
    fclose(outfile);
}