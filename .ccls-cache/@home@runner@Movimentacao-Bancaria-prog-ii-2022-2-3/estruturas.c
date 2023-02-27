struct clientData {
  unsigned int accCode;
  char accName[15];
  char accLastName[10];
  double limit;
  double accBalance;
};

struct transactionData {
  unsigned int accCode;
  char typeTransaction;
  double value;
};