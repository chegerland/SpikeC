#ifndef INFO_H
#define INFO_H

#ifdef __cplusplus
extern "C" {
#endif

// from https://github.com/michael-hartmann/caps
void print_spike_build_info(FILE *fp) {
#ifdef GIT_HEAD
  fprintf(fp, "# git head: %s\n", GIT_HEAD);
#endif

#ifdef GIT_BRANCH
  fprintf(fp, "# git branch: %s\n", GIT_BRANCH);
#endif
}

#ifdef __cplusplus
}
#endif

#endif // INFO_H
