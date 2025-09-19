#include "BlockChain.h"
#include <iostream>
using std::endl;

int BlockChainGetSize(const BlockChain& blockChain){
    return blockChain.size;
}

int BlockChainPersonalBalance(const BlockChain& blockChain, const string& name){
    unsigned int positiveAmount = 0;
    unsigned int negativeAmount = 0;
    Block* temp_block = blockChain.head;
    while(temp_block != nullptr){
        if(temp_block->transaction.receiver == name){
            positiveAmount += temp_block->transaction.value;
        }
        else {
            if(temp_block->transaction.sender == name){
                negativeAmount += temp_block->transaction.value;
            }
        }
        temp_block = temp_block->prev;
    }
    return positiveAmount-negativeAmount;
}

void BlockChainAppendTransaction(
        BlockChain& blockChain,
        unsigned int value,
        const string& sender,
        const string& receiver,
        const string& timestamp
){
    Transaction transaction;
    transaction.value = value;
    transaction.sender = sender;
    transaction.receiver = receiver;
    Block* newBlock = new Block();
    newBlock->transaction = transaction;
    newBlock->timestamp = timestamp;
    newBlock->prev = blockChain.head;
    blockChain.head = newBlock;
    blockChain.size++;
}


void BlockChainAppendTransaction(
        BlockChain& blockChain,
        const Transaction& transaction,
        const string& timestamp
) {
    BlockChainAppendTransaction(blockChain, transaction.value, transaction.sender, transaction.receiver, timestamp);
}


BlockChain BlockChainLoad(ifstream& file) {
    BlockChain tempBlockChain;
    tempBlockChain.head = nullptr;
    tempBlockChain.size = 0;
    unsigned int value;
    string sender, receiver, timeStamp;
    while (file >> sender >> receiver >> value >> timeStamp) {
        BlockChainAppendTransaction(tempBlockChain, value, sender, receiver, timeStamp);
    }
    BlockChain resultChain;
    resultChain.head = nullptr;
    resultChain.size = 0;
    Block* runner = tempBlockChain.head;
    while (runner != nullptr) {
        BlockChainAppendTransaction(resultChain, runner->transaction, runner->timestamp);
        runner = runner->prev;
    }
    destruct(tempBlockChain);
    return resultChain;
}





void BlockChainDump(const BlockChain& blockChain, ofstream& file){
    const Block* runner = blockChain.head;
    file << "BlockChain Info:" << endl;
    int blockNumber = 1;
    while (runner != nullptr) {
        file << blockNumber << "." << endl;
        TransactionDumpInfo(runner->transaction, file);
        file << "Transaction timestamp: " << runner->timestamp << endl;
        runner = runner->prev;
        blockNumber++;
    }
}

void BlockChainDumpHashed(const BlockChain& blockChain, ofstream& file){
    const Block* runner = blockChain.head;
    while (runner != nullptr) {
        if(runner->prev != nullptr){
            file << TransactionHashedMessage(runner->transaction) << endl;
        }
        else {
            file << TransactionHashedMessage(runner->transaction);
        }
        runner = runner->prev;
    }
}


bool BlockChainVerifyFile(const BlockChain& blockChain, std::ifstream& file){
    string line;
    bool result = true;
    const Block* runner = blockChain.head;
    while (getline(file, line)) {
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }
        if (runner == nullptr) {
            return false;
        }
        result = TransactionVerifyHashedMessage(runner->transaction, line);
        if (!result) {
            return false;
        }
        runner = runner->prev; 
    }
    if (runner != nullptr) {
        return false;
    }
    return true;
}

void BlockChainCompress(BlockChain& blockChain){
    if(blockChain.head == nullptr){
        return;
    }

    Block* runner = blockChain.head;
    while (runner != nullptr && runner->prev != nullptr)
    {
        Block* tmp = runner->prev;
        if (tmp->transaction.receiver == runner->transaction.receiver &&
            tmp->transaction.sender == runner->transaction.sender) {
            runner->transaction.value += tmp->transaction.value;
            runner->prev = tmp->prev;
            delete tmp;
        }
        else {
            runner = runner->prev;
        }
    }

}

template<class updateFunction>
void BlockChainTransform(BlockChain& blockChain, updateFunction function) { 
    if(blockChain.head == nullptr){
        return;
    }
    Block* runner = blockChain.head;
    while (runner != nullptr)
    {
        runner->transaction.value = function(runner->transaction.value);
        runner = runner->prev;
    }
}

void destruct(BlockChain& blockChain) {
    Block* current = blockChain.head;
    while (current != nullptr) {
        Block* next = current->prev;
        delete current;
        current = next;
    }
    blockChain.head = nullptr;
    blockChain.size = 0;
}

