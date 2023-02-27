#include <stdio.h>

struct clientAcc {
  unsigned int accNum;
  char name[15];
  char lastName[15];
  double saldo;
  double depositos;
  double saques;
  double limite;
}; 

struct transacoesAcc {
  unsigned int acctNum;
  char tipo;
  double valor;
  double saldo;
};

unsigned int escolha(void);
void novoRegistro(FILE *fPtr);
void relacaoClientes(FILE *rPtr);
void fazerMovimentacao(FILE *rPtr, FILE *movPtr);
void relacaoSaldo(FILE *rPtr);
void extrato(FILE *rPtr, FILE *extratoPtr);
void relacaoTransacao(FILE *rPtr, FILE *transacaoPtr);
void importClient(FILE *fPtr);

int main(void){
  FILE *contasDatPtr;
  FILE *movimentacaoPtr;
  
  if (((contasDatPtr = fopen("contas.dat", "rb+")) == NULL) ||
       (movimentacaoPtr = fopen("movimentacao.dat", "rb+")) == NULL){
    puts("Arquivo inexistente!");
  } else {
    unsigned int opcao;

    while ((opcao = escolha()) != 0){
      switch (opcao){
        case 1:
          novoRegistro(contasDatPtr);
          break;
        case 2:
          fazerMovimentacao(contasDatPtr, movimentacaoPtr);
          break;
        case 3:
          extrato(contasDatPtr, movimentacaoPtr);
          break;
        case 4:
          relacaoClientes(contasDatPtr);
          break;
        case 5:
          relacaoSaldo(contasDatPtr);
          break;
        case 6:
          relacaoTransacao(contasDatPtr, movimentacaoPtr);
          break;
        case 7:
          importClient(contasDatPtr);
          break;
      }
    }
  }
}

void novoRegistro(FILE *fPtr){
  unsigned int accNum;
  printf("%s", "Digite o numero da conta (1 - 100): ");
  scanf("%u", &accNum);
  // ^^ - Conta a ser inserida
  fseek(fPtr, (accNum - 1) * sizeof(struct clientAcc), SEEK_SET); // seta na conta que esta sendo adicionada
  struct clientAcc blankClient = {0, "", "", 0, 0, 0, 0};
  fread(&blankClient, sizeof(struct clientAcc), 1, fPtr);
  if(blankClient.accNum != 0){
    printf("Conta #%d ja existente", blankClient.accNum);
  } else {
    printf("%s", "Entre com nome, sobrenome, limite\n > ");
    scanf("%14s%14s%lf", blankClient.name, blankClient.lastName, &blankClient.limite);
    blankClient.accNum = accNum;
    fseek(fPtr, (accNum - 1) * sizeof(struct clientAcc), SEEK_SET); // seta na conta que esta sendo adicionada
    fwrite(&blankClient, sizeof(struct clientAcc), 1, fPtr);
  }
}

void fazerMovimentacao(FILE *fPtr, FILE *moviPtr){
  unsigned int accNum;
  printf("Conta para fazer a movimentacao (1 - 100): ");
  scanf("%d", &accNum);
  struct clientAcc blankClient = {0, "", "", 0, 0, 0, 0};
  struct transacoesAcc blankTransacao = {0,' ', 0, 0};
  fread(&blankTransacao, sizeof(struct transacoesAcc), 1, moviPtr);
  fseek(fPtr, (accNum - 1) * sizeof(struct clientAcc), SEEK_SET);
  fread(&blankClient, sizeof(struct clientAcc), 1, fPtr);
  if (blankClient.accNum == 0){
    printf("Conta #%d sem registro!\n", accNum); 
  } else {
    printf("%s", "Qual tipo de transacao?\n");
    printf("%s", "(1) Deposito ou (2) Saque: ");
    int op;
    scanf("%d", &op);
    double limiteT = blankClient.saldo + blankClient.limite;
    printf("%-6d%-16s%-16s%10.2f%10.2f\n", blankClient.accNum, blankClient.name, blankClient.lastName, blankClient.saldo, limiteT);
    blankTransacao.acctNum = blankClient.accNum;
    printf("%s", "Digite o quanto a ser movimentado: ");
    double tranzacao;
    scanf("%lf", &tranzacao);
    
    if(op == 1){
      blankClient.saldo += tranzacao;
      blankClient.depositos += tranzacao;
      blankTransacao.tipo = 'D';
      blankTransacao.valor = tranzacao;
      blankTransacao.saldo = blankClient.saldo;
    } else if (op == 2){
      double limite;
      limite = (blankClient.saldo - tranzacao) + blankClient.limite;
      if(limite < 0){
        printf("\nLimite nao disponivel!\n\n");
        return;
      }
      blankClient.saldo -= tranzacao;
      blankClient.saques -= tranzacao;
      blankTransacao.tipo = 'S';
      blankTransacao.valor = tranzacao;
      blankTransacao.saldo = blankClient.saldo;
    } else {
      printf("Opcao invalida\n");
      return;
    }
  fseek(fPtr, (accNum - 1) * sizeof(struct clientAcc), SEEK_SET);
  fwrite(&blankClient, sizeof(struct clientAcc), 1, fPtr);
  fwrite(&blankTransacao, sizeof(struct transacoesAcc), 1, moviPtr);
  }
}

void extrato(FILE *rPtr, FILE *extratoPtr){
  FILE *txtPtr;
  txtPtr = fopen("painel.txt", "w");
  rewind(rPtr);
  rewind(extratoPtr);
  int opcao;
  printf("%s", "Digite a conta a ser consultada: ");
  scanf("%d", &opcao);
  printf("%d\n", opcao);
  
  while(!feof(rPtr)) {
    struct clientAcc blankClient = {0, "", "", 0, 0, 0, 0};
    struct clientAcc saveClient = {0, "", "", 0, 0, 0, 0};
    fread(&blankClient, sizeof(struct clientAcc), 1, rPtr);
    if (blankClient.accNum == opcao){
      fprintf(txtPtr, "----------------------------------\n");
      fprintf(txtPtr, "Extrato do Cliente\n"
                      "Codigo: %d\n"
                      "Nome: %-14s\n"
                      "Saldo Inicial: 0.00\n"
                      "----------------------------------\n"
                      "%6s%14s%14s\n", blankClient.accNum, blankClient.name, "Tipo", "Valor", "Saldo");
      fprintf(txtPtr, "----------------------------------\n");
    }
  }

  double saldoFinal;
  while(!feof(extratoPtr)){
    struct transacoesAcc blankTransacao = {0, ' ', 0, 0};
    fread(&blankTransacao, sizeof(struct transacoesAcc), 1, extratoPtr);
    if (blankTransacao.acctNum == opcao){
      fprintf(txtPtr, "%6c%14.2lf%14.2lf\n", blankTransacao.tipo, blankTransacao.valor, blankTransacao.saldo);
      saldoFinal = blankTransacao.saldo;
    }
  }
  fprintf(txtPtr, "----------------------------------\n");
  fprintf(txtPtr, "Saldo Final %22.2lf\n", saldoFinal);
  fprintf(txtPtr, "----------------------------------\n");
  fclose(txtPtr);

}

void relacaoClientes(FILE *rPtr){
  FILE *txtPtr;
  txtPtr = fopen("painel.txt", "w");
  rewind(rPtr);
  fprintf(txtPtr, "--------------------------------------------------------------------\n");
  fprintf(txtPtr, "%-6s%-16s%-16s%10s\n", "Conta", "Nome", "Sobrenome", "Limite");
  while(!feof(rPtr)){
    struct clientAcc blankClient = {0, "", "", 0, 0, 0, 0};
    int result = fread(&blankClient, sizeof(struct clientAcc), 1, rPtr);
    if (result != 0 && blankClient.accNum != 0){
      fprintf(txtPtr, "%5d %-16s%-16s%10.2lf\n", blankClient.accNum, blankClient.name, blankClient.lastName, blankClient.limite);
    }
  }
  fprintf(txtPtr, "--------------------------------------------------------------------\n");
  fclose(txtPtr);
}

void relacaoSaldo(FILE *rPtr){
  FILE *txtPtr;
  txtPtr = fopen("painel.txt", "w");
  rewind(rPtr); // como só vai imprimir, deve-se voltar para o comeco
  fprintf(txtPtr, "--------------------------------------------------------------------\n");
  fprintf(txtPtr, "%-6s%-16s%-16s%10s%10s%10s\n", "Conta", "Nome", "Sobrenome", "Depositos", "Saques", "Saldo");
  while(!feof(rPtr)){
    struct clientAcc blankClient = {0, "", "", 0, 0, 0, 0};
    int result = fread(&blankClient, sizeof(struct clientAcc), 1, rPtr);
    if (result != 0 && blankClient.accNum != 0){
      fprintf(txtPtr, "%5d %-16s%-16s%10.2lf%10.2lf%10.2lf\n", blankClient.accNum, blankClient.name, blankClient.lastName, blankClient.depositos, blankClient.saques, blankClient.saldo);
    }
  }
  fprintf(txtPtr, "--------------------------------------------------------------------\n");
  fclose(txtPtr);
}

void relacaoTransacao(FILE *rPtr, FILE *transacaoPtr){
  FILE *txtPtr;
  txtPtr = fopen("painel.txt", "w");
  rewind(rPtr);
  rewind(transacaoPtr);
  while(!feof(transacaoPtr)){
    struct transacoesAcc blankTransacao = {0, ' ', 0, 0};
    fread(&blankTransacao, sizeof(struct transacoesAcc), 1, transacaoPtr);
    struct clientAcc blankClient = {0, "", "", 0, 0, 0, 0};
    fseek(rPtr, (blankTransacao.acctNum - 1) * sizeof(struct clientAcc), SEEK_SET);
    fread(&blankClient, sizeof(struct transacoesAcc), 1, rPtr);
    fprintf(txtPtr, "%4d%14s%6c%14.2lf\n", blankTransacao.acctNum, blankClient.name, blankTransacao.tipo, blankTransacao.valor);
    }
  fclose(txtPtr);
}

void importClient(FILE *fPtr){
  FILE *contasPtr;

  contasPtr = fopen("contas.txt", "r");
  rewind(contasPtr);
  struct clientAcc blankClient = {0, "", "", 0, 0, 0, 0};
  fscanf(contasPtr, "%d%s%s%lf", &blankClient.accNum, blankClient.name, blankClient.lastName, &blankClient.limite);
  printf("\n\n%d %s %s %lf\n\n", blankClient.accNum, blankClient.name, blankClient.lastName, blankClient.limite);

  while(!feof(contasPtr)){
    struct clientAcc blankClientArq = {0, "", "", 0, 0, 0, 0};
    fseek(fPtr, (blankClient.accNum - 1) * sizeof(struct clientAcc), SEEK_SET); // seta na conta que esta sendo adicionada
    fread(&blankClientArq, sizeof(struct clientAcc), 1, fPtr);

    if(blankClientArq.accNum != 0){
      printf("Conta #%d ja existente\n", blankClient.accNum);
    } else {
      fseek(fPtr, (blankClient.accNum - 1) * sizeof(struct clientAcc), SEEK_SET); // seta na conta que esta sendo adicionada
      fwrite(&blankClient, sizeof(struct clientAcc), 1, fPtr);
    }
    // struct clientAcc blankClient = {0, "", "", 0, 0, 0, 0};
    fscanf(contasPtr, "%d%s%s%lf", &blankClient.accNum, blankClient.name, blankClient.lastName, &blankClient.limite);

  }
  fclose(contasPtr);
}

unsigned int escolha(void) {
  unsigned int opcao;
  printf("*-* --------------------------------- *-*\n"
         "*-* 1 - Adicionar uma conta           *-*\n"
         "*-* 2 - Fazer uma movimentacao        *-*\n"
         "*-* 3 - Extrato                       *-*\n"
         "*-* 4 - Relacao de clientes           *-*\n"
         "*-* 5 - Relacao saldo e movimentacao  *-*\n"
         "*-* 6 - Relacao de transacoes         *-*\n"
         "*-* 7 - Importar do contas.txt        *-*\n"
         "*-* 0 - SAIR                          *-*\n"
         "*-* --------------------------------- *-*\n");
  printf("Opcao: ");
  scanf("%u", &opcao);
  return opcao;
}
