#include <main.hpp>

int main(int argc, char* argv[])
{
  /* read rules from a file */
  FILE *fp;
  char s[256] = {};
  if (4 != argc) { 
    printf("./zdd <rule list> <hash size> <operation cache size>\n");
    exit(1);
  }

  if (NULL == (fp = fopen(argv[1], "r"))) {
    printf("File open ERROR!!\n");
    exit(1);
  }

  std::vector<std::string> vec;
  // char** ss;
  // ss = (char**)malloc(6*sizeof(char*));
  for (unsigned i = 0; fscanf(fp, "%s", s) != EOF; ++i) {
    // ss[i] = (char*)malloc(sizeof(char)*(strlen(s)+1));
    // strcpy(ss[i], s);
    // ss[i][4] = '\n';
    std::string str(s);
    vec.push_back(str);
  }

  /* construct a MTZDD */

  ZDD z = ZDD(vec, atoi(argv[2]), atoi(argv[3]));
  // z.print();


  /* print */

  for (int i = 0; i < (int)vec.size(); ++i) {
    std::list<std::string> h = z.getMatchHeaders(i+1);
    printf("R[%d] matches: \n", i+1);
    for (auto it : h) { std::cout << it << std::endl; }
  }

  // for (int i = 1; (unsigned)i <= vec.size(); ++i)
  //   printf("A number of paths to %d = %d\n", i, z.count(i));
  std::cout << "A number of nodes = " << z.getNumberOfNodes() << std::endl;

  fclose(fp);  

  return 0;
}
