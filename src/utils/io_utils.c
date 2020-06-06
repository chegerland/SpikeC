#include "io_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// create files struct from given input file and appendix
files_t *create_files(const char *input_file, const char *append) {

  // check that input file has .ini extension
  const char *input_file_ext = get_filename_ext(input_file);
  if (strcmp(input_file_ext, "ini") != 0) {
    printf("Input file must have file extension .ini!\n");
    exit(-1);
  }

  // check if input file exists
  if (access(input_file, F_OK) == -1) {
    printf("Input file %s does not exist!\n", input_file);
    exit(-1);
  }

  // create output file name
  char *output_file = remove_file_ext(input_file);
  output_file = realloc(output_file, strlen(output_file) + strlen(append) + 6);
  strcat(output_file, append);
  strcat(output_file, ".csv");

  // create file struct
  files_t *files = malloc(sizeof(files_t));
  files->input_file = input_file;
  files->output_file = output_file;

  return files;
}

//! from https://stackoverflow.com/a/2736841
char *remove_file_ext(const char *file_path) {
  char *retStr = NULL, *lastExt = NULL;
  if (file_path == NULL)
    return NULL;
  if ((retStr = malloc(strlen(file_path) + 1)) == NULL)
    return NULL;
  strcpy(retStr, file_path);
  lastExt = strrchr(retStr, '.');
  if (lastExt != NULL)
    *lastExt = '\0';
  return retStr;
}

//! from https://stackoverflow.com/a/5309508
const char *get_filename_ext(const char *filename) {
  const char *dot = strrchr(filename, '.');
  if (!dot || dot == filename)
    return "";
  return dot + 1;
}
