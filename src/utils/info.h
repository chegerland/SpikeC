#ifndef INFO_H
#define INFO_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * prints the build information of spike to a stream
 * from https://github.com/michael-hartmann/caps
 */
void print_spike_build_info(FILE *stream) {
#ifdef GIT_HEAD
  fprintf(stream, "# git head: %s\n", GIT_HEAD);
#endif

#ifdef GIT_BRANCH
  fprintf(stream, "# git branch: %s\n", GIT_BRANCH);
#endif
}

#ifdef __cplusplus
}
#endif

#endif // INFO_H
