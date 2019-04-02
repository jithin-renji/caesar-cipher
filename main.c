/*
 *
 *      File: main.c
 * 
 *      Program to encrypt and decrypt
 *      a given string or file using
 *      Caesar cipher
 * 
 *      Copyright (C) 2019 Jithin Renji
 * 
 *      This program is free software: you can redistribute it and/or modify
 *      it under the terms of the GNU General Public License as published by
 *      the Free Software Foundation, either version 3 of the License, or
 *      (at your option) any later version.
 *      
 *      This program is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *      GNU General Public License for more details.
 * 
 *      You should have received a copy of the GNU General Public License
 *      along with this program.  If not, see <https://www.gnu.org/licenses/>. 
 *
 */

/* For getopt_long() */
#include <getopt.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ENCRYPT     1
#define DECRYPT     0

/* 
    Size for different buffers
    in the program
*/
#define BUF_SIZE    2048

int option_index = 0;

/* Long options */
static struct option long_options[] = {
    {"encrypt",     no_argument,        0, 'e'},
    {"decrypt",     no_argument,        0, 'd'},
    {"file",        required_argument,  0, 'f'},
    {"help",        no_argument,        0, 'h'},
    {"out",         required_argument,  0, 'o'},
    {"input",       no_argument,        0, 'I'},
    {"version",     no_argument,        0, 'V'},
    {0,             0,                  0,  0}
};

static char ret_str[BUF_SIZE] = "";

/* Print usage message */
void usage(char* prog_name);

/* Print version information */
void version(void);

/* Caesar cipher function */
void caesar(char* str, int shift_size, int encr_decr, int print);

/* Apply Caesar cipher on a file */
void caesar_f(char* fname, char* ofname, int shift_size, int encr_decr);

int main (int argc, char** argv)
{
    if (argc < 2) {
        fprintf(stderr, "%s: Not enough arguments!\n", argv[0]);
        fprintf(stderr, "Try '%s --help'\n", argv[0]);        
    } else {

        int opt;
        /* To encrypt or not */
        int encrypt = 0;

        /* To decrypt or not */
        int decrypt = 0;

        /* File name provided or not */
        int fname_provided = 0;

        /* Usage message or not */
        int help = 0;

        /* Provided file name */
        char fname[FILENAME_MAX];

        /* Provided output file name */
        char ofname[FILENAME_MAX] = "";

	    /* Input from stdin or not */
	    int in_from_stdin = 0;

        while ((opt = getopt_long(argc, argv, "edf:ho:IV", long_options, &option_index)) != -1) {
            switch (opt){
            case 'e':
                encrypt = 1;
                break;

            case 'd':
                decrypt = 1;
                break;

            case 'f':
                fname_provided = 1;
                strcpy(fname, optarg);
                break;

            case 'h':
                usage(argv[0]);
                help = 1;
                break;

            case 'o':
                strcpy(ofname, optarg);
                break;

	        case 'I':
		        in_from_stdin = 1;
                break;

            case 'V':
                version();

            default:
                exit(EXIT_FAILURE);
            }
        }
        if (help == 1);
        else if (encrypt == 1 && decrypt == 1) {
            fprintf(stderr, "Error: Cannot encrypt and decrypt at the same time\n");
        }
        else if (encrypt == 0 && decrypt == 0 && help == 0) {
            fprintf(stderr, "Error: Don't know whether to encrypt or decrypt\n");
            exit(EXIT_FAILURE);
        } else if (fname_provided) {
            if(argv[optind] == NULL) {
                fprintf(stderr, "Error: Shift size not provided\n");
                exit(EXIT_FAILURE);
            } else {
                if (encrypt == 1)
                    caesar_f(fname, ofname, atoi(argv[optind]), ENCRYPT);
                else
                    caesar_f(fname, ofname, atoi(argv[optind]), DECRYPT);
            }
        } else if (in_from_stdin == 1) {
            if (argv[optind] == NULL) {
                fprintf(stderr, "Error: Shift size not provided\n");
            } else{
                char input[BUF_SIZE];
                
                while (fgets(input, BUF_SIZE, stdin)) {
                    input[strlen(input) - 1] = '\0';

                    if (encrypt == 1)
                        caesar(input, atoi(argv[optind]), ENCRYPT, 1);
                    else
                        caesar(input, atoi(argv[optind]), DECRYPT, 1);
                }
            }
	    } else if ((encrypt == 1) ^ (decrypt == 1)){
            if (argv[optind] == NULL) {
                fprintf(stderr, "Error: No text provided\n");
                exit(EXIT_FAILURE);
            } else if (argv[optind + 1] == NULL) {
                fprintf(stderr, "Error: Shift size not provided\n");
                exit(EXIT_FAILURE);
            } else {
                if (encrypt == 1)
                    caesar(argv[optind], atoi(argv[optind + 1]), ENCRYPT, 1);
                else
                    caesar(argv[optind], atoi(argv[optind + 1]), DECRYPT, 1);
            }
        }
    }

    return 0;
}

void usage (char* prog_name)
{
    printf("Usage: %s <-e | -d> -f <file name> [-o <output file name>] <shift size>\n", prog_name);
    printf("       %s <-e | -d> <plain text> <shift size>\n", prog_name);
    printf("       %s <-e | -d> -I <shift size>\n", prog_name);

    printf("Options:\n");
    printf("\t-e, --encrypt\t\tEncrypt plain text\n");
    printf("\t-d, --decrypt\t\tDecrypt Caesar cipher text\n");
    printf("\t-I, --input\t\tTake input from stdin\n");
    printf("\t-f, --file <file name>\tEncrypt/Decrypt given file\n\n");
    printf("\t-o, --out <file name>\tName of the output file in which\n\
                                the encrypted/decrypted file is going\n\
                                to be stored\n\n");
    printf("\t-h, --help\t\tShow this help message\n");
    printf("\t-V, --version\t\tShow version information\n");
}

void version (void)
{
    printf("caesar 1.1\n");
    printf("Copyright (C) 2019 Jithin Renji.\n");
    printf("License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>.\n");
    printf("This is free software: you are free to change and redistribute it.\n");
    printf("There is NO WARRANTY, to the extent permitted by law.\n\n");

    printf("Written by Jithin Renji.\n");
}

void caesar (char* str, int shift_size, int encr_decr, int print)
{
    if (encr_decr == ENCRYPT) {
        char cipher[2048];
        int i = 0;

        while (i < strlen(str)) {
            cipher[i] = str[i] + shift_size;
            i += 1;
        }

        /* 
            strlen() does not include the null byte.
            We have to add it ourselves. 
        */
        cipher[i] = '\0';
        
        if (print == 1)
            printf("%s\n", cipher);

        strcpy(ret_str, cipher);
    } else {
        char decr_str[2048];
        int i = 0;

        while (i < strlen(str)) {
            decr_str[i] = str[i] - shift_size;
            i += 1;
        }

        /* 
            strlen() does not include the null byte.
            We have to add it ourselves. 
        */
        decr_str[i] = '\0';

        if (print == 1)
            printf("%s\n", decr_str);

        strcpy(ret_str, decr_str);
    }
}

void caesar_f (char* fname, char* ofname, int shift_size, int encr_decr)
{
    /* Stream to handle input file */
    FILE* in_file = fopen(fname, "r");

    /* Using default file name or not */
    int default_file_name = 0;
    
    /* Output file name */
    char ofname_default[FILENAME_MAX];

    if (in_file == NULL) {
	    char msg[BUF_SIZE];
	    strcpy(msg, "caesar: cannot open ");
	    strcat(msg, "'");
	    strcat(msg, fname);
	    strcat(msg, "'");

	    perror(msg);

	    exit(EXIT_FAILURE);
    }

    if (encr_decr == ENCRYPT) {
        if (strcmp(ofname, "") == 0) {
            strcpy(ofname_default, fname);
            strcat(ofname_default, "_encr"); 

            default_file_name = 1;       
        } else {
            strcpy(ofname_default, ofname);
        }

        FILE* out_file = fopen(ofname_default, "w");
        char line[BUF_SIZE];

        while (fgets(line, BUF_SIZE, in_file)) {
            char encr_line[BUF_SIZE];
            
            caesar(line, shift_size, ENCRYPT, 0);
            strcpy(encr_line, ret_str);

            fprintf(out_file, "%s", encr_line);
            strcpy(ret_str, "");
        }

        fclose(out_file);
        printf("Done!\n");

    } else if (encr_decr == DECRYPT) {
        if (strcmp(ofname, "") == 0) {
            strcpy(ofname_default, fname);
            strcat(ofname_default, "_decr");

            default_file_name = 1;      
        } else {
            strcpy(ofname_default, ofname);
        }

        FILE* out_file = fopen(ofname_default, "w");
        char line[BUF_SIZE];

        while (fgets(line, BUF_SIZE, in_file)) {
            char decr_line[BUF_SIZE];
            
            caesar(line, shift_size, DECRYPT, 0);
            strcpy(decr_line, ret_str);

            fprintf(out_file, "%s", decr_line);
            strcpy(ret_str, "");
        }

        fclose(out_file);
        printf("Done!\n");
    }

    if (default_file_name == 1)
        printf("Output file: %s\n", ofname_default);
}
