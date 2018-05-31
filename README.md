# Trabalho 1 - OA
#### Indexação e processamento co-sequencial

## Alunos
	Kálley Wilkerson R. Alexandre - 170038050
	André Macedo Prado Valle - 170005950


## Observações

	Os arquivos que foram utilizados para a criação deste
	programa foram provavelmente criados no sistema
	operacional Windows pois uma nova linha é representada
	por '\r\n' e não somente por '\n', como é no Linux, dessa
	forma os arquivos fornecidos para utilização deste
	software devem ter a mesma precedência dos arquivos
	fornecidos para criação deste programa (feitos dentro
	do Windows por exemplo).

	Os arquivos onde estão armazenados os dados estão salvos
	como 'lista1.txt' e 'lista2.txt', se outro arquivo for
	utilizado, além de obedecer o padrão citado acima, também
	deverá ser renomeado para um desses nomes.

	Para garantir mudanças feitas em um arquivo, re-execute
	o programa depois de fazer alterações.
	
## Compilação

	Para compilar o programa, vá até a pasta onde está o
	programa, abra o terminal nela e execute:
	>> make

## Execução

	Para executar o programa, abra o terminal na pasta onde
	está o programa e execute o comando:
	>> ./main

## Arquivos produzidos

   	-> indprimN.ind

	Arquivo com os índices primários da lista 'N' (1 ou 2)
	Contém duas colunas de informação. A primeira com a chave primária
	(Matrícula e nome concatenados) e na segunda o número relativo do
	registro (NRR) em relação ao arquivo de dados.

	-> indsecN.ind

	Arquivo com os índices secundários da lista 'N'
	Contém duas colunas de informação. A primeira com o curso e a segunda
	com a NRR para o primeiro registro do curso no arquivo de de listas 
	invertidas.

	-> lst_invN.txt

	Arquivo com as listas invertidas das chaves secundárias
	da lista 'N'
	Contém duas colunas de informação. Na primeira se encontra a chave
	primária e na segunda o NRR para o próximo registro na lista invertida
	relacionado a um curso.

	-> lista12.txt

	Arquivo com o resultado da operação de merge da lista 1 com a
	lista 2.


## Módulos

	-> lst_prim_inv.c

	Contém as funções de manipulação para lista primária e
	invertida.

	-> lst_sec.c

	Contém as funções de manipulação para listas secundárias

	-> EntradaeSaida.c

	Contém principalmente funções de manipulação de arquivos

	-> PED.c

	Contém funções de manipulação para pilha de espaços
	disponíveis

	-> main.c

	Contém os procedimentos principais do software


## Repositório

	O repositório oficial deste programa pode ser acessado
	pelo link abaixo:
	https://github.com/yellak/TrabalhoOA

