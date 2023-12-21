/* Define as constantes, os tipos de dados e os protótipos de funções do filesystem.
*/
#pragma once

#define FALSE 0
#define TRUE 1
#define ERROR_OPEN_FILE -1
#define ERROR_CREATE_FILE -2
#define ERROR_CLOSE_FILE -3
#define ERROR_WRITE_FILE -4
#define ERROR_DELETE_FILE -5
#define ERROR_READ_FILE -6
#define END_OF_FILE -7

// Número máximo de caracteres no nome do arquivo.
#define FILE_NAME_SIZE 128

// Comprimento da hora de criação do arquivo no formato hh:mm:ss.
#define HOUR_SIZE 9

// Tamanho do bloco lógico em bytes.
#define LOGICAL_BLOCK_SIZE 4

// Número máximo de arquivos do disco virtual.
#define NUMBER_OF_FILES_OF_DISK 1024

// Número máximo de discos virtuais que podem ser criados.
#define NUMBER_OF_DISKS 26

#define SIZE_NUMERIC 4

#define SIZE_STRING 1

// Representação descritiva dos tipos de dados que um arquivo pode armazenar.
#define TYPE_NUMERIC "Numérico"
#define TYPE_TEXT "Texto"

#define PROMPT " fs> "

#define DELIMITATOR " "

#define SIZE_COMMAND 2

#define COMMAND_SIZE 1000

#define SIZE_FILE_NAME 100

#define SIZE_FILE_LINE 200

#define FILE_OPEN "r"

#define INVALID_COMMAND "\n Comando inválido!\n"

#define CD "cd"
#define CA "ca"
#define AA "aa"
#define EA "ea"
#define LA "la"
#define FA "fa"
#define DA "da"
#define LD "ld"
#define FD "fd"
#define ET "et"
#define EF "ef"
#define IA "ia"

#define CD_NUMBER 1
#define CA_NUMBER 2
#define AA_NUMBER 3
#define EA_NUMBER 4
#define LA_NUMBER 5
#define FA_NUMBER 6
#define DA_NUMBER 7
#define LD_NUMBER 8
#define FD_NUMBER 9
#define ET_NUMBER 10
#define EF_NUMBER 11
#define IA_NUMBER 12

// Código UTF-8 do caractere A maiúsculo.
#define CHARACTER_CODE_A 0x41

// Código UTF-8 do caractere Z maiúsculo.
#define CHARACTER_CODE_Z 0x5A

// Indica que o disco virtual deve ser criado.
#define MODE_CREATE_DISK 0

// Indica que o disco virtual previamente criado pode ser acessado.
#define MODE_GET_DISK 1

// Indica a remoção de um disco virtual.
#define MODE_REMOVE_DISK 2

// Representa os tipos de dados que um arquivo pode armazenar. Os tipos são numérico (inteiro ou real) e string.
typedef enum
{
	NUMERIC,
	STRING
} FileType;

// Tamanho representado como um inteiro sem sinal.
typedef unsigned int Size;

// O descritor de arquivo é usado para identificar um arquivo no sistema de arquivos.
typedef unsigned short FileDescriptor;

// Identificação do arquivo.
typedef struct
{
	/* Descritor de arquivo usado para identificar o arquivo no sistema de arquivos.
	   ATENÇÃO: Deve ser gerado um código único de identificação para cada arquivo do sistema de arquivos.
	*/
	FileDescriptor fileDescriptor;

	// Nome do arquivo.
	char name[FILE_NAME_SIZE];

} FileIdentification;

// Atributos do arquivo.
typedef struct
{
	unsigned char open;

	// Nome e descritor do arquivo.
	FileIdentification fileIdentification;

	// Data de criação do arquivo no formato hh:mm:ss.
	char hour[HOUR_SIZE];

	// Tamanho do arquivo em bytes.
	Size size;

	// Número de blocos lógicos do arquivo.
	Size clusters;

	// Conteúdo do arquivo.
	void *content;

	// Representa o tipo de dado do conteúdo do arquivo.
	FileType type;

} File;

// Atributos do disco.
typedef struct
{
	// Capacidade máxima de armazenamento em bytes do disco.
	Size capacity;

	// Espaço ocupado do disco.
	Size usedSpace;

	// Espaço livre do disco.
	Size freeSpace;

	// Número total de blocos lógicos, ocupados e livres.
	Size totalClusters;

	// Número de blocos lógicos ocupados do disco.
	Size occupiedClusters;

	// Número de blocos lógicos livres do disco.
	Size availableClusters;

} Disk;

// Atributos do disco virtual.
typedef struct
{
	// Dados do disco.
	Disk disk;

	// Número de arquivos do disco.
	Size numberOfFiles;

	// A tabela de alocação de arquivos é usada para armazenar todos os arquivos do disco.
	File fileAllocationTable[NUMBER_OF_FILES_OF_DISK];

} VirtualDisk;

// Informações sobre o disco virtual.
typedef struct
{
	// Letra de identificação do disco virtual.
	char diskID;

	// Dados do disco virtual.
	VirtualDisk virtualdisk;

} DiskInformation;

// Relação de discos do sistema de arquivos.
typedef struct
{
	// Letra de identificação de todos os discos do sistema de arquivos.
	char diskID[NUMBER_OF_DISKS];

	unsigned char numberOfDisks;

	// Nome e descritor de cada arquivo armazenado em cada disco do sistema de arquivos.
	FileIdentification *fileIdentification[NUMBER_OF_DISKS][NUMBER_OF_FILES_OF_DISK];

} SystemDisks;

// Verifica se o comando existe
int verifyCommand(char *command);

// Exibe o prompt
char *showPrompt();

// Valida os dados digitados e se for válido cria o disco
int cd(char *command);

// Valida os dados digitados e se for válido cria um arquivo
int ca(char *command);

// Valida os dados digitados e se for válido abre o arquivo
int aa(char *command);

// Valida os dados digitados e se for válido escreve os dados no arquivo
int ea(char *command);

// Valida os dados digitados e se for válido lê o arquivo
int la(char *command);

// Valida os dados digitados e se for válido fecha o arquivo
int fa(char *command);

// Valida os dados digitados e se for válido exclui o arquivo
int da(char *command);

// Valida os dados digitados e se for válido exibe os dados do disco
int ld(char *command);

// Valida os dados digitados e se for válido formata o disco
int fd(char *command);

// Valida os dados digitados e se for válido exibe o tamanho e a quantidade de blocos do arquivo
int et(char *command);

// Valida os dados digitados e se for válido tenta importar os dados
int ia(char *command);

/**
	Obtém a identificação do disco virtual onde o arquivo está armazenado.

	@param fileDescripton identificação do arquivo;
	@param systemDisks relação de discos do sistema de arquivos.

	@return a letra de identificação do disco, por exemplo C, D, E, etc., onde o arquivo está armazenado.
 */
char getDiskID(FileDescriptor fileDescriptor, SystemDisks systemDisks);

/**
   Cria um disco virtual.

   @param size especifica a capacidade máxima de armazenamento em bytes do disco;
   @param diskID letra de identificação do disco, por exemplo C, D, E, etc.

   @return um ponteiro para a estrutura de armazenamento criada para o disco, se ocorrer erro retorna NULL.
*/
VirtualDisk *createDisk(char diskID, Size size);

// Exibe um relatório
void showReport(DiskInformation diskInformation);

/**
   Formata logicamente o disco virtual apagando todo o conteúdo de sua tabela de alocação de arquivos, consequentemente
   apagando todo os arquivos do disco. Reinicializa os dados da estrutura do disco. Toda a memória alocada dinamicamente
   para armazenar a estrutura do disco e de seus arquivos devem ser liberadas, ou seja, devolvidas ao sistema operacional.

   @param diskID letra de identificação do disco, por exemplo C, D, E, etc.

   @return TRUE em caso de sucesso, caso contrário, FALSE.
*/
int format(char diskID);

/**
   Cria um arquivo para leitura e escrita no disco.

   @param diskID letra de identificação do disco, por exemplo C, D, E, etc;
   @param fileName nome do arquivo.

   @return um inteiro que representa o descritor de arquivo ou ERROR_CREATE_FILE se o arquivo não pode ser criado.
 */
int create(char diskID, const char *fileName);

/**
   Abre um arquivo para leitura e escrita.

   @param fileDescripton identificação do arquivo.

   @return TRUE se o arquivo foi aberto e ERROR_OPEN_FILE se ocorrer algum erro, por exemplo, o arquivo não existe.
*/
int open(FileDescriptor fileDescriptor);

/**
	Escreve os dados no arquivo.

	NOTA: O bloco lógico é a unidade básica de alocação de espaço (memória) no disco, portanto sempre que uma escrita é feita no
		  disco deve-se escrever no mínimo um bloco lógico de tamanho definido em LOGICAL_BLOCK_SIZE. Sendo assim, quando
		  o usuário solicita que seja escrito um número inteiro de 4 bytes (valor de LOGICAL_BLOCK_SIZE), usa-se um bloco lógico para
		  armazená-lo no arquivo, mas quando é escrito a string "Férias!", usa-se 2 blocos lógicos. Como essa string possui 7 caracteres e cada
		  caractere (char) ocupa 1 byte de memória, ela precisa de 7 bytes de memória. No entanto, como cada bloco lógico possui 4 bytes,
		  a string exige 2 blocos lógicos (8 bytes) para ser armazenada no disco, logo deve-se escrever dois blocos.

	@param buffer ponteiro para o primeiro dado do buffer a ser escrito no arquivo;
	@param size tamanho de cada dado;
	@param number o número de dados a serem escritos no arquivo;
	@param fileDescripton identificação do arquivo.

	@return o número de bytes escritos em caso de sucesso ou ERROR_WRITE_FILE se ocorrer algum erro.
			Se size ou number for zero, a função retorna ERROR_WRITE_FILE e a operação não é executada.
*/
int write(const void *buffer, Size size, Size number, FileDescriptor fileDescriptor);

/**
	Lê os dados do arquivo.

	NOTA: O bloco lógico é a unidade básica de alocação de espaço (memória) no disco, portanto sempre que uma leitura é feita no
		  disco deve-se ler no mínimo um bloco lógico de tamanho definido em LOGICAL_BLOCK_SIZE. Sendo assim, quando
		  o usuário solicita que seja lido um número inteiro de 4 bytes (valor de LOGICAL_BLOCK_SIZE), lê-se um bloco lógico para
		  recuperá-lo do arquivo, mas quando é lido a string "Férias!", lê-se 2 blocos lógicos. Como essa string possui 7 caracteres e cada
		  caractere (char) ocupa 1 byte de memória, ela precisa de 7 bytes de memória. No entanto, como cada bloco lógico possui 4 bytes,
		  a string exige 2 blocos lógicos (8 bytes) para ser armazenada no disco, logo deve-se ler os dois blocos.

	@param buffer ponteiro para o buffer onde os dados lidos são armazenados;
	@param size tamanho de cada dado;
	@param number o número de dados a serem lidos do arquivo;
	@param fileDescripton identificação do arquivo.

	@return o número de bytes lidos em caso de sucesso ou ERROR_READ_FILE se ocorrer algum erro ou
			END_OF_FILE se for feito uma tentativa de ler além do fim do arquivo.
			Se size ou number for zero, a função retorna ERROR_READ_FILE e a operação não é executada.
*/
int read(void *buffer, Size size, Size number, FileDescriptor fileDescriptor);

/**
   Fecha o arquivo.

   @param fileDescripton identificação do arquivo.

   @return TRUE se a operação for bem sucedida ou ERROR_CLOSE_FILE se não conseguir fechar o arquivo.
*/
int close(FileDescriptor fileDescriptor);

/**
   Apaga o arquivo do disco.

   @param fileDescripton identificação do arquivo.

   @return TRUE se a operação for bem sucedida ou ERROR_DELETE_FILE se não conseguir excluir o arquivo do disco virtual.
*/
int erase(FileDescriptor fileDescriptor);

/**
   Obtém um relatório com as seguintes informações:

   - Dados do Arquivo
   --------------------
   1. nome;
   2. tipo;
   3. tamanho em bytes;
   4. número de blocos lógicos;
   5. hora de criação.

   - Dados do Disco
   ------------------
   1. número de arquivos;
   2. a capacidade de armazenamento;
   3. o espaço ocupado do disco;
   4. o espaço livre do disco;
   5. o número total de blocos lógicos;
   6. o número de blocos lógicos ocupados;
   7. o número de blocos lógicos livres.

   Os dados devem ser obtidos para cada arquivo do disco.

   @param diskID letra de identificação do disco, por exemplo C, D, E, etc.

   @return o conteúdo do relatório em caso de sucesso ou NULL se ocorrer um erro.
*/
DiskInformation *getDiskInformation(char diskID);

// Obtém o número do descritor de arquivo
FileDescriptor getNumberFileDescriptor();

// Exibe o tamanho e a quantidade de blocos de um arquivo
int showSizeFile(FileDescriptor fileDescriptor);

// Importa um arquivo
int import(const char diskId, const char *fileName);

/**
   Cria ou obtém o endereço da estrutura de armazenamento do disco.

   @param diskID letra de identificação do disco, por exemplo C, D, E, etc;
   @param mode informa o modo de acesso ao disco virtual, os valores válidos são: MODE_CREATE_DISK e MODE_GET_DISK 1.

   Se mode for MODE_CREATE_DISK e a letra de identificação do drive for válida, a função cria o disco e retorna um ponteiro para sua estrutura de armazenamento.
   Se mode for MODE_GET_DISK e a letra de identificação do drive for válida, a função obtém o ponteiro para a estrutura de armazenamento do disco previamente criada.

   @return NULL se ocorrer algum erro na criação ou no acesso ao disco, ou se a identificação do drive for inválida.
*/
VirtualDisk *getVirtualDisk(char diskID, char mode);

// Obtém os dados que serão salvos no buffer
Size getDataWrite(char *command, char *buffer, const char *fileName, const char number);

// Realoca o tamanho de um buffer
void reallocateBuffer(char **buffer, const Size sizeBuffer);

// Limpa o vetor de arquivos no "System Disks" 
void cleanFileIdentification(unsigned char position, SystemDisks *systemDisks, const Size numberOfFiles);

// Obtém o tamanho de um arquivo
Size getSizeFile(FileDescriptor fd);

// Obtém o tamanho do "content" se o arquivo for numérico
Size getNumericSizeFile(FileDescriptor fd);

// Obtém a posição de um arquivo no disco virtual com determinado descritor de arquivo
unsigned short getPositionFile(FileDescriptor fd, VirtualDisk *virtualDisk);

// Obtém a posição do disco no "SystemDisks"
unsigned char getPositionDisk(char diskId, const SystemDisks systemDisks);

// Obtém o endereço do "System Disks"
SystemDisks *getSystemDisks();

// Obtém a hora atual
char *getCurrentTime();

// Obtém o descritor de arquivo de um arquivo
int getDescriptorFile(const char drive, const char *fileName);

// Obtém o tipo do arquivo
FileType getTypeFile(const char diskId, const Size fd);

// Verifica se a string possui dígitos
int verifyDigit(const char *command);

// Exibe uma mensagem
void showMessage(const char *message);

// Abre um arquivo, mode é o modo de abertura
FILE *openFile(const char *path, const char *mode);

// Limpa o buffer do teclado
void clearBuffer();

// Limpa a string com o tamanho especificado em size
void cleanString(char *string, unsigned short size);

// Remove o "\n" do final das strings
void removeEnter(char *string);
