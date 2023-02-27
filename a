//#include "estruturas.c"
#include <stdio.h>

unsigned int primaryOption(void);
void newAccount(FILE *fPtr);
void editAccount(FILE *fPtr);
void deleteAccount(FILE *fPtr);
void initializeProgram(FILE *fPtr);
void printClients(FILE *fPtr);
void importAccounts(FILE *fPtr);
void effectTransaction(FILE *fPtr);
void printTransactions(FILE *fPtr, FILE *fTra);

int main(void) {
  FILE *file;
  FILE *tra;

  if (((file = fopen("contas.dat", "rb+")) == NULL) ||
      ((tra = fopen("transaction.dat", "rb+")) == NULL)) {

    puts("Impossível abrir o arquivo!!\n");

  } else {
    initializeProgram(file);
    puts("\nBEM VINDO AO SISTEMA DLBANK...");

    unsigned int option; // opção do usuário
    while ((option = primaryOption()) != 10) {
      switch (option) {
      case 1:
        importAccounts(file);
        break;
      case 2:
        newAccount(file);
        break;
      case 3:
        editAccount(file);
        break;
      case 4:
        deleteAccount(file);
        break;
      case 5:
        effectTransaction(file);
        break;
      case 6:
        printClients(file);
        break;
      case 7:

        break;
      case 8:
        printTransactions(file, tra);
        break;
      case 9:

        break;
      default:
        puts("Opção Inválida..");
        break;
      }
    }
    fclose(file);
  }
}

void effectTransaction(FILE *fPtr) {
  FILE *arqTransaction;

  if ((arqTransaction = fopen("transaction.dat", "rb+")) == NULL) {
    puts("\nARQUIVO DE TRANSAÇÃO COM PROBLEMA!!\n");
  } else {
    puts("Digite o número da conta: ");
    unsigned int code;
    scanf("%d", &code);

    fseek(fPtr, (code - 1) * sizeof(struct clientData), SEEK_SET);
    struct clientData client;
    fread(&client, sizeof(struct clientData), 1, fPtr);

    if (client.accCode == 0) {
      puts("\nConta Inexistente!!\n");
    } else {
      struct transactionData transaction = {client.accCode, "", 0.0};
      puts("\nDigite o tipo de transação (D ou C) e o valor: ");
      scanf("%c%lf", &transaction.typeTransaction, &transaction.value);

      fwrite(&transaction, sizeof(struct transactionData), 1, arqTransaction);
    }
  }
}

void printTransactions(FILE *fPtr, FILE *fTra) {
  FILE *transactions;

  if (((transactions = fopen("transactions.txt", "w")) == NULL) ||
      ((fPtr = fopen("contas.dat", "rb+")) == NULL) ||
      ((fTra = fopen("transaction.dat", "rb+")) == NULL)) {
    puts("IMPOSSIVEL ABRIR ARQUIVO!!");
  } else {
    rewind(transactions);
    fprintf(transactions, "Relação de Transações\n");
    fprintf(transactions, "-------------------------------------------\n");
    fprintf(transactions, "Conta    Nome        Tipo      Valor\n");
    fprintf(transactions, "-------------------------------------------\n");

    char name[15];
    struct clientData client;
    struct transactionData traData;

    while (!feof(fTra)) {
      fread(&traData, sizeof(struct transactionData), 1, fTra);
      while (!feof(fPtr)) {
        fseek(fPtr, (traData.accCode - 1) * sizeof(struct clientData),
              SEEK_SET);
        fread(&client, sizeof(struct clientData), 1, fPtr);

        fprintf(transactions, "%-6d%-16s%-11c%10.2f\n", traData.accCode,
                client.accName, traData.typeTransaction, traData.value);
      }
    }
    fprintf(transactions, "-------------------------------------------\n");

    fclose(transactions);
  }
}

void printClients(FILE *fPtr) {
  FILE *clients;

  if (((clients = fopen("relacaoClientes.txt", "w")) == NULL) ||
      (fPtr = fopen("contas.dat", "rb+")) == NULL) {

    puts("IMPOSSIVEL ABRIR ARQUIVO!!");

  } else {
    rewind(clients);
    fprintf(clients, "Relação de Clientes\n");
    fprintf(clients, "-------------------------------------------\n");
    fprintf(clients, "Conta    Nome        Sobrenome      Limite\n");
    fprintf(clients, "-------------------------------------------\n");

    struct clientData client;

    while (!feof(fPtr)) {
      fread(&client, sizeof(struct clientData), 1, fPtr);
      if (client.accCode != 0) {
        fprintf(clients, "%-6d%-16s%-11s%10.2f\n", client.accCode,
                client.accName, client.accLastName, client.limit);
      }
    }
    fprintf(clients, "-------------------------------------------\n");

    fclose(clients);
  }
}

void initializeProgram(FILE *fPtr) {
  // if ((fPtr = fopen("contas.dat", "rb+")) == NULL) {
  //  puts("Arquivo não pode ser aberto.");
  //} else {

  struct clientData flagClient = {0, ".", ".", 0.0, 0.0};

  for (unsigned int i = 1; i <= 100; ++i) {
    // fseek(fPtr, sizeof(struct clienteConta), SEEK_SET);
    fwrite(&flagClient, sizeof(struct clientData), 1, fPtr);
  }
  fclose(fPtr);
}
//}

void importAccounts(FILE *fPtr) {
  FILE *clients;

  char arqName[1000];
  puts("\nDigite o nome do arquivo a ser importado: ");
  scanf("%s", arqName);
  if (((clients = fopen(arqName, "r")) == NULL) ||
      (fPtr = fopen("contas.dat", "rb+")) == NULL) {
    puts("ARQUIVO INEXISTENTE!!");
  } else {

    struct clientData client = {0, "", "", 0.0, 0.0};

    // fscanf(clients, "%6d%16s%11s%lf", &client.accCode, client.accName,
    // client.accLastName, &client.limit);

    while (!feof(clients)) {
      fscanf(clients, "%6d%16s%11s%lf", &client.accCode, client.accName,
             client.accLastName, &client.limit);

      // printf("%6d%16s%11s%10.2lf\n", client.accCode, client.accName,
      //     client.accLastName, client.limit);

      fseek(fPtr, (client.accCode - 1) * sizeof(struct clientData), SEEK_SET);
      fwrite(&client, sizeof(struct clientData), 1, fPtr);
    }
    printf("%s", "\nTODAS AS CONTAS FORAM IMPORTADAS COM SUCESSO!!\n");
    fclose(clients);
  }
}

void newAccount(FILE *fPtr) {
  if ((fPtr = fopen("contas.dat", "rb+")) == NULL) {
    puts("ARQUIVO INEXISTENTE!!");
  } else {

    printf("%s", "Digite o número da conta: ");
    unsigned int accCode;
    scanf("%d", &accCode);
    fseek(fPtr, (accCode - 1) * sizeof(struct clientData), SEEK_SET);

    struct clientData client = {0, "", "", 0.0, 0.0};
    fread(&client, sizeof(struct clientData), 1, fPtr);
    printf("\n%d %s %s %lf %lf\n", client.accCode, client.accName,
           client.accLastName, client.limit, client.accBalance);

    if (client.accCode != 0) {
      puts("Esta conta já existe, escolha outro código\n");
    }

    else { // Cria registro
      printf("%s", "Digite o nome, sobrenome e limite:\n ");
      scanf("%14s%9s%lf", client.accName, client.accLastName, &client.limit);
      client.accCode = accCode;
      printf("\n%d %s %s %lf %lf\n", client.accCode, client.accName,
             client.accLastName, client.limit, client.accBalance);
      // fseek(fPtr, (client.accCode - 1) * sizeof(struct clientData),
      // SEEK_SET);
      // insere
      fwrite(&client, sizeof(struct clientData), 1, fPtr);
    }
  }
}

void editAccount(FILE *fPtr) {
  unsigned int account;
  puts("Digite o código da conta a ser editada: ");
  scanf("%d", &account);
  fseek(fPtr, (account - 1) * sizeof(struct clientData), SEEK_SET);
  struct clientData client = {0, "", "", 0.0, 0.0};
  fread(&client, sizeof(struct clientData), 1, fPtr);
  if (client.accCode == 0) {
    printf("Conta Inexistente!!");
  } else { // altera
    printf("%-6d%-16s%-11s%10.2f%10.2f\n\n", client.accCode, client.accName,
           client.accLastName, client.limit, client.accBalance);

    printf("%s",
           "Coloque os novos dados desta conta: \n(Nome Sobrenome Limite)\n?");

    scanf("%14s%9s%lf", client.accName, client.accLastName, &client.limit);
    printf("\n%-6d%-16s%-11s%10.2lf%10.2lf\n\n", client.accCode, client.accName,
           client.accLastName, client.limit, client.accBalance);

    /*
    double tranzacao; // tranzacao amount
    scanf("%lf", &tranzacao);
    cliente.saldo += tranzacao; // update record saldo

    printf("%-6d%-16s%-11s%10.2f\n", cliente.acctNum, cliente.nome,
           cliente.sobrenome, cliente.saldo);
    */

    // move ponteiro para a posição
    fseek(fPtr, (account - 1) * sizeof(struct clientData), SEEK_SET);
    // atualiza
    fwrite(&client, sizeof(struct clientData), 1, fPtr);
  }
}

void deleteAccount(FILE *fPtr) {
  // obtendo conta para apagar
  printf("%s", "Digite o código da conta a ser deletada:\n ");
  unsigned int accNum;
  scanf("%d", &accNum);
  // movimenta o ponteiro para o registro específico
  fseek(fPtr, (accNum - 1) * sizeof(struct clientData), SEEK_SET);
  struct clientData client; // stores record read from file
  // lê registro do arquivo
  fread(&client, sizeof(struct clientData), 1, fPtr);
  if (client.accCode == 0) {
    puts("Conta Inexistente em nosso Banco de Dados...");
  } else { // delete record
    fseek(fPtr, (accNum - 1) * sizeof(struct clientData), SEEK_SET);
    struct clientData clientCleared = {0, "", "", 0.0, 0.0};
    // altera
    fwrite(&clientCleared, sizeof(struct clientData), 1, fPtr);
  }
}

unsigned int primaryOption(void) {
  unsigned int option;
  // variable to store user's opcao   printf("%s", "\nEntre com a opção\n"

  puts("\nSelecione sua opção:\n");
  printf("|--------------------------------------|\n"
         "| 1 - Importar Contas...               |\n"
         "| 2 - Adicionar uma conta..            |\n"
         "| 3 - Alterar registro de conta..      |\n"
         "| 4 - Apagar uma conta..               |\n"
         "| 5 - Efetuar Transação...             |\n"
         "| 6 - Relação Clientes                 |\n"
         "| 7 - Relação Completa                 |\n"
         "| 8 - Relação Transações               |\n"
         "| 9 - Extrato                          |\n"
         "| 10 - Sair do Programa                |\n"
         "|--------------------------------------|\nOpção: ");
  scanf("%u", &option); // receive opcao from user
  return option;
}