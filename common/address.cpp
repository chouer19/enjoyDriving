#include "common/address.h"
#include "config/config.h"
#include "simdjson/jsonioutil.h"
#include "simdjson/jsonparser.h"

int getAddressTopic(const char *node, char *address, char *topic){

    std::string_view p;
    try {
        p = get_corpus(ADDRESS_CFG_PATH);
    } catch (const std::exception &e) { // caught by reference to base
        std::cout << "Could not load the file " << ADDRESS_CFG_PATH << std::endl;
        return -1;
    }
    ParsedJson pj;
    bool allocok = pj.allocateCapacity(p.size(), 1024);
    if (!allocok) {
        std::cerr << "failed to allocate memory" << std::endl;
        return -2;
    }
    int res = json_parse(p, pj); // do the parsing, return false on error
    aligned_free((void *)p.data());
    if (res) {
        std::cerr << " Parsing failed. " << std::endl;
        return -3;
    }

    ParsedJson::iterator pjh(pj);
    if (!pjh.isOk()) {
        std::cerr << " Could not iterate parsed result. " << std::endl;
        return -4;
    }

    if(!pjh.is_object()){ // now pointing at root {
        std::cerr << " Not any object in the address.json file! " << std::endl;
        return -5;
    }

    pjh.down(); // now pointing at "addresses"
    pjh.next(); // now pointing at content of "addresses", naming that [ ... ] array
    pjh.down(); // now pointint at first content node { of the array
    do{
        if(pjh.down()){ // pointing at "node"
            pjh.next(); // pointing at content of "node", naming node's name
            if(strcmp(pjh.get_string(), node) == 0){
                pjh.next(); // pointing at "address"
                pjh.next(); // pointing at content of address
                sprintf(address,"%s",pjh.get_string());
                //address = pjh.get_string();

                pjh.next(); // pointing at "topic"
                pjh.next(); // pointing at content of topic
                sprintf(topic,"%s",pjh.get_string());
                //topic = pjh.get_string();
                return 1;
            }
            pjh.up();
        }
    }while(pjh.next());

    return -6;
}
