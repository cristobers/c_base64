#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>

#define true 1
#define false 0

// a bit of warning, this is not a very good implementation of a map,
// this will be slow in comparison to an actual map. But considering that this
// only runs once, and spits out a character, it works well enough
typedef struct {
    char* key;      // string keys
    char data;      // single character as data
    void* next;     // pointer to next link
} Link;

Link* create_link(char* key, char data) {
    Link* temp;
    temp = malloc(sizeof(Link));
    temp->key  = key;
    temp->data = data;
    temp->next = NULL;
    return temp;
}

Link* insert_link(Link* root, char* key, char data) {
    Link* temp = NULL;
    if (root->next == NULL) {
        temp = create_link(key, data);
        root->next = temp;
    } else {
        root->next = insert_link(root->next, key, data);
    }
    return root;
}

char find(Link* root, char* key) {
    if (root->next == NULL && root->key != key) {
        return '~';     // <--  error character
    } else {
        if (strcmp(root->key, key) != 0) {
            return find(root->next, key);
        }
        return root->data;
    }
}

Link* initialise() {
    Link* root;
    root = create_link("000000", 'A');
    root = insert_link(root, "000001", 'B');
    root = insert_link(root, "000010", 'C');
    root = insert_link(root, "000011", 'D');
    root = insert_link(root, "000100", 'E');
    root = insert_link(root, "000101", 'F');
    root = insert_link(root, "000110", 'G');
    root = insert_link(root, "000111", 'H');
    root = insert_link(root, "001000", 'I');
    root = insert_link(root, "001001", 'J');
    root = insert_link(root, "001010", 'K');
    root = insert_link(root, "001011", 'L');
    root = insert_link(root, "001100", 'M');
    root = insert_link(root, "001101", 'N');
    root = insert_link(root, "001110", 'O');
    root = insert_link(root, "001111", 'P');
    root = insert_link(root, "010000", 'Q');
    root = insert_link(root, "010001", 'R');
    root = insert_link(root, "010010", 'S');
    root = insert_link(root, "010011", 'T');
    root = insert_link(root, "010100", 'U');
    root = insert_link(root, "010101", 'V');
    root = insert_link(root, "010110", 'W');
    root = insert_link(root, "010111", 'X');
    root = insert_link(root, "011000", 'Y');
    root = insert_link(root, "011001", 'Z');
    root = insert_link(root, "011010", 'a');
    root = insert_link(root, "011011", 'b');
    root = insert_link(root, "011100", 'c');
    root = insert_link(root, "011101", 'd');
    root = insert_link(root, "011110", 'e');
    root = insert_link(root, "011111", 'f');
    root = insert_link(root, "100000", 'g');
    root = insert_link(root, "100001", 'h');
    root = insert_link(root, "100010", 'i');
    root = insert_link(root, "100011", 'j');
    root = insert_link(root, "100100", 'k');
    root = insert_link(root, "100101", 'l');
    root = insert_link(root, "100110", 'm');
    root = insert_link(root, "100111", 'n');
    root = insert_link(root, "101000", 'o');
    root = insert_link(root, "101001", 'p');
    root = insert_link(root, "101010", 'q');
    root = insert_link(root, "101011", 'r');
    root = insert_link(root, "101100", 's');
    root = insert_link(root, "101101", 't');
    root = insert_link(root, "101110", 'u');
    root = insert_link(root, "101111", 'v');
    root = insert_link(root, "110000", 'w');
    root = insert_link(root, "110001", 'x');
    root = insert_link(root, "110010", 'y');
    root = insert_link(root, "110011", 'z');
    root = insert_link(root, "110100", '0');
    root = insert_link(root, "110101", '1');
    root = insert_link(root, "110110", '2');
    root = insert_link(root, "110111", '3');
    root = insert_link(root, "111000", '4');
    root = insert_link(root, "111001", '5');
    root = insert_link(root, "111010", '6');
    root = insert_link(root, "111011", '7');
    root = insert_link(root, "111100", '8');
    root = insert_link(root, "111101", '9');
    root = insert_link(root, "111110", '+');
    root = insert_link(root, "111111", '/');
    return root;
}

int character_as_int(char c) {
    return (int)c;
}

/*
 * Converts from an integer to an 8 bit binary number.
 */
void int_to_binary(int n, char* temp) {
    int d = 0;
    int m = 0;
    for (int j = 0; j < 8; ++j) {
        d = n >> 1;     /* div by 2 */
        m = (n % 2);    /* get remainder */
        n = d;          /* update n */
        temp[7 - j] = (char)(m + '0');
    }
    temp[8] = '\0';
}

/*
 * Turns our char into an 8-bit binary string,
 * modifies the temp pointer.
 */
char* convert(char c, char* temp) {
    // assuming c is [A-Z a-z 0-9 +/=]
    int_to_binary(character_as_int(c), temp);
    return temp;
}

int incorrect_inputs(int argv) {
    if (argv != 2)
        return true;
    return false;
}

const char* input_to_binary(char* input) {
    int index = 0;
    int char_count = strlen(input);
    // allocate memory for size of 
    // 8 * amount of characters
    char* binary = malloc(sizeof(char) * (7 * char_count) + 1);
    // for every character in our input
    for (int input_index = 0; input_index < (int)strlen(input); ++input_index) {
        // allocate memory for a new binary number
        char* temp = malloc(8 * sizeof(char));
        // convert our current character to binary
        const char* curr = convert(input[input_index], temp); 
        // for every character in our current converted binary
        for (int j = 0; j < (int)strlen(curr); ++j) {
            // append each character to the malloc'd memory
            binary[index] = curr[j];
            // increment the binary string index
            index++;
        }
    }
    binary[index] = '\0';
    return binary;
}

char sextet_to_char(char* sextet, Link* root) {
    char found = '~';
    if ((found = find(root, sextet)) == '~') {
        // something's gone wrong when trying to use a sextet to find a character
        // and there's no entry for that given sextet, this shouldn't happen.
        printf("Couldn't find a sextet that matches a character in our dictionary.\n");
        printf("input sextet: %s\n", sextet);
        exit(-1);
    } else {
        return found;
    }
}

int binary_to_sextets(const char* binary, char** output) {
    /*
     * Consume tokens from binary, if we hit 6 then append that
     * If we get less than 6 and hit the end, append those left over ones.
     */
    int binary_index  = 0;
    // this is also our string index, strings are (6 chars + 1 nullbyte)
    int sextet_count  = 0;
    // overall loop
    while (binary_index < (int)strlen(binary)) {
        char* new_string = (char*)malloc(7 * sizeof(char));
        if (new_string == NULL) {
            printf("Malloc failed\n");
            return -1;
        }
        output[sextet_count] = new_string;
        // inner loop consumes tokens to try and make a sextet
        // if we reach the end of binary, append what we have and return
        for (int i = 0; i < 6; ++i) {
            output[sextet_count][i] = binary[binary_index];
            binary_index++;
        }
        sextet_count++;
    }
    // fill out final entry with 0's
    if (strlen(output[sextet_count-1]) < 6) {
        // count forward until we hit \0
        int i = 0;
        while(output[sextet_count-1][i] != '\0') {
            i++;
        }
        // null found
        for (int j = i; j < 6; ++j) {
            output[sextet_count-1][j] = '0';
        }
    }
    return sextet_count;
}

int we_need_encoding(char* input) {
    assert(strlen(input) > 0);
    // not a mult of 3, we need encoding, otherwise we dont
    if (strlen(input) % 3 == 0) {
        return false;
    }
    return true;
}

void apply_padding(char* input, int sextet_count) {
    if (we_need_encoding(input)) {
        int i = 0;
        while( (i + sextet_count) % 4 != 0 ) {
            assert(i <= 2);
            printf("=");
            ++i;
        }
    }
}

int main(int argv, char** argc) {
    if (incorrect_inputs(argv)) {
        printf("useage: ./base64 <input string>\n");
        return -1;
    }

    Link* map;
    map = initialise();
    char* input = argc[1];

    if (strlen(input) < 1)
        return -1;

    const char* binary = input_to_binary(input);

    char** sextets;
    long arg_max = sysconf(_SC_ARG_MAX);
    // resize this malloc after we know how many sextets we have
    if (arg_max == -1) {
        sextets = (char**)malloc(8192 * sizeof(char*));
    } else {
        sextets = (char**)malloc(arg_max * sizeof(char*));
    }

    if (sextets == NULL) {
        printf("Failed to malloc array of strings for sextets\n");
        return -1;
    }

    int sextet_count = binary_to_sextets(binary, sextets);
    if (sextet_count == -1) {
        return -1;
    }

    if (realloc(sextets, sextet_count * sizeof(char*)) == NULL) {
        printf("Failed to realloc sextet buffer.\n");
        return -1;
    }

    for (int i = 0; i < sextet_count; ++i) {
        printf("%c", sextet_to_char(sextets[i], map));
    }

    apply_padding(input, sextet_count);
    printf("\n");

    // we actually want to free all of the sextets in the big sextet pointer
    for (int i = 0; i <= sextet_count; ++i) {
       free(sextets[i]);
    }

    // then free the top-level pointer
    free(sextets);
    return 0;
}
