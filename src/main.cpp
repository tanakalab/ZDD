#include <main.hpp>

int main(int argc, char* argv[])
{
  /* read rules from a file */
  FILE *fp;
  char s[256] = {};

  if (argc != 3 || NULL == (fp = fopen(argv[1], "r"))) {
    printf("File open ERROR!!\n");
    return 1;
  }

  std::vector<std::string> vec;
  char** ss;
  ss = (char**)malloc(6*sizeof(char*));
  for (unsigned i = 0; fscanf(fp, "%s", s) != EOF; ++i) {
    ss[i] = (char*)malloc(sizeof(char)*(strlen(s)+1));
    strcpy(ss[i], s);
    ss[i][4] = '\n';
    std::string str(s);
    vec.push_back(str);
  }

  /* construct a MTZDD */

  ZDD z = ZDD(vec);
  // zdd v = zdd(tt);
  // for (unsigned i = 0; i < 6; ++i)
  //   printf("%s", ss[i]);
  
  /* free memory allocated dynamically */
  fclose(fp);

  for (unsigned i = 0; i < 6; ++i) {
    // printf("free ss[%d]\n", i);
    free(ss[i]);
  }
  free(ss);
  
  return 0;
}
