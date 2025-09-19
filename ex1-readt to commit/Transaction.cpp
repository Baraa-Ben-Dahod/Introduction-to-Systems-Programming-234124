#include "Transaction.h"
#include "Utilities.h"

using std::endl;

void TransactionDumpInfo(const Transaction& transaction, ofstream& file){
    file << "Sender Name: " << transaction.sender << endl;
    file << "Receiver Name: " << transaction.receiver << endl;
    file << "Transaction Value: " << transaction.value << endl;
}

string TransactionHashedMessage(const Transaction& transaction){
    return hash(transaction.value,transaction.sender,transaction.receiver);
}

bool TransactionVerifyHashedMessage(
        const Transaction& transaction,
        string hashedMessage
){
    string message = hash(transaction.value,
    transaction.sender,transaction.receiver);
    return message == hashedMessage;
}