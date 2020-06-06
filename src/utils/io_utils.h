#ifndef IO_UTILS_H
#define IO_UTILS_H

// in- and output files type
typedef struct {
  const char *input_file;
  const char *output_file;
} files_t;

files_t *create_files(const char *input_file, const char *append);

char *remove_file_ext(const char *file_path);
const char *get_filename_ext(const char *filename);

#endif // IO_UTILS_H
