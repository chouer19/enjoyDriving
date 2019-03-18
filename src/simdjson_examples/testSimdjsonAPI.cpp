#include <iostream>
#ifndef _MSC_VER
#include <unistd.h>
#endif
#include "simdjson/jsonioutil.h"
#include "simdjson/jsonparser.h"
#include "config.h"

using namespace std;

void compute_dump(ParsedJson::iterator &pjh) {
  if (pjh.is_object()) {
    std::cout << "{";
    if (pjh.down()) {
      pjh.print(std::cout); // must be a string
      std::cout << ":";
      pjh.next();
      compute_dump(pjh); // let us recurse
      while (pjh.next()) {
        std::cout << ",";
        pjh.print(std::cout);
        std::cout << ":";
        pjh.next();
        compute_dump(pjh); // let us recurse
      }
      pjh.up();
    }
    std::cout << "}";
  } else if (pjh.is_array()) {
    std::cout << "[";
    if (pjh.down()) {
      compute_dump(pjh); // let us recurse
      while (pjh.next()) {
        std::cout << ",";
        compute_dump(pjh); // let us recurse
      }
      pjh.up();
    }
    std::cout << "]";
  } else {
    pjh.print(std::cout); // just print the lone value
  }
}

int main(int argc, char *argv[]) {
    std::cout << "address file path is : " << ADDRESS_CFG_PATH << std::endl;
    std::string_view p;
    // load file and check if exist
    try {
        p = get_corpus(ADDRESS_CFG_PATH);
    } catch (const std::exception &e) { // caught by reference to base
        std::cout << "Could not load the file " << ADDRESS_CFG_PATH << std::endl;
        return EXIT_FAILURE;
    }
    ParsedJson pj;
    bool allocok = pj.allocateCapacity(p.size(), 1024);
    if (!allocok) {
        std::cerr << "failed to allocate memory" << std::endl;
        return EXIT_FAILURE;
    }
    int res = json_parse(p, pj); // do the parsing, return false on error
    aligned_free((void *)p.data());
    if (res) {
        std::cerr << " Parsing failed. " << std::endl;
        return EXIT_FAILURE;
    }
    ParsedJson::iterator pjh(pj);
    if (!pjh.isOk()) {
        std::cerr << " Could not iterate parsed result. " << std::endl;
        return EXIT_FAILURE;
    }
    if (pjh.is_object()){
        if(pjh.down()){
            pjh.print(std::cout);
            std::cout << std::endl;
        }
        pjh.next();
        if(pjh.is_array()){
            std::cout << "is_array is True\n";
        }
    }
    //compute_dump(pjh);
    std::cout << "\n";
    return EXIT_SUCCESS;
}
