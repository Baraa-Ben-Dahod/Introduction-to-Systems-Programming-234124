#include "BlockChain.h"
#include "Utilities.h"
#include <iostream>
#include <cstring>
#define NUM_OP 4
using std::cout;
using std::endl;

int main(int argc, char** argv){
    if(argc != NUM_OP){
        cout << getErrorMessage();
        return 0;
    }
    const char* op = argv[1];
    const char* source = argv[2];
    const char* target = argv[3];

    std::ifstream sourceFile(source);
    BlockChain currentBlockChain = BlockChainLoad(sourceFile);

    if(std::strcmp(op, "verify") == 0){
        std::ifstream targetFile(target);
        bool result = BlockChainVerifyFile(currentBlockChain, targetFile);
        cout << (result ? "Verification passed" : "Verification failed") << endl;
    } else if (std::strcmp(op, "format") == 0) {
        std::ofstream targetFile(target);
        BlockChainDump(currentBlockChain, targetFile);
    } else if (std::strcmp(op, "hash") == 0) {
        std::ofstream targetFile(target);
        BlockChainDumpHashed(currentBlockChain, targetFile);
    } else if (std::strcmp(op, "compress") == 0) {
        std::ofstream targetFile(target);
        BlockChainCompress(currentBlockChain);
        BlockChainDump(currentBlockChain, targetFile);
    } else {
        // Unknown operation -> print usage
        cout << getErrorMessage();
    }

    destruct(currentBlockChain);
    return 0;
}
