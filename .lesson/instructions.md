# Instruções  
## Atividade prática de manipulação de arquivos

Com base na atividade de movimentação bancária desenvolvida em sala de aula, vamos implementar um projeto envolvendo a movimentação bancária simples em um banco.

### Requisitos do sistema:
- Disponibilizar todas as funcionalidades em um menu de opções.
- Possibilitar a importação do cadastro de clientes de um arquivo sequencial para o arquivo Binário com as contas.
- Ter a opção de cadastramento de contas incluindo um campo para armazenar o limite de crédito do cliente
- Todas as contas ao serem cadastradas deverão ter um saldo 0 (zero)
- O saldo das contas só poderá ser alterado através de uma - transação de depósito ou saque.
- Cada transação deverá ser armazenada em um arquivo binário.
- O arquivo binário com as transações deverá ter um campo com o número da conta, o tipo de transação e o valor, 
- As transações, saque e depósito,  devem ser sempre com valores positivos
- O sistema deverá ter opções para emitir os seguintes resultados:
	- Relação de contas cadastradas com os respectivos limites
	- Relação de contas com o total de movimentação e saldos
	- Relação de Transações realizadas
	- Emitir extrato de um cliente específico


### Exemplos de saída

```
Relação de contas cadastradas com os limites
--------------------------------------------
Conta   Nome       Sobrenome         Limite
--------------------------------------------
1       Maria      Silva            1000.00
5       Pedro      Borges           5000.00
9       Gabriel    Marques             0.00
-------------------------------------------
```
*Lembre-se que o usuário poderá pedir relatório completo ou apenas dos clientes com saldo credor, devedor ou das  contas com saldo zero*
```
Relação contas com os saldos com movimentação
------------------------------------------------------------------
Conta   Nome       Sobrenome      Depósitos      Saques      Saldo
1       Maria      Silva            4000.00     1000.00    3000.00
5       Pedro      Borges            100.00      800.00     700.00  
9       Gabriel    Marques           500.00      500.00       0.00
------------------------------------------------------------------
```

*Observe que na relação de transações aparece o nome do cliente, que não será gravado no arquivo de transações, o nome do cliente será buscado no arquivo de cadastro de clientes através do código* 
```
Relação de transações 
-----------------------------
Conta Nome     Tipo     Valor
-----------------------------
1     Maria     D     1000.00     
5     Pedro     D      100.00
1     Maria     D     3000.00
5     Pedro     S      200.00
9     Gabriel   D      200.00
1     Maria     S      700.00
9     Gabriel   D      300.00
9     Gabriel   S      100.00
9     Gabriel   S      400.00
1     Maria     S      300.00 
5     Pedro     S      600.00
-----------------------------
```
Lembre de acumular o saldo a cada tanzação
```
Extrato do cliente
Código: 10 
Nome: Maria
Saldo Inicial: 0.00
---------------------------
Tipo     Valor       Saldo
---------------------------
D       1000.00    1000.00 
D       3000.00    4000.00
S        700.00    3300.00
S        300.00    3000.00
---------------------------
Saldo Final        3000.00
---------------------------
```
