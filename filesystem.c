#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <locale.h>
#include "filesystem.h"

// Inicia o programa
int filesystem()
{
   setlocale(LC_ALL, "portuguese");
   setlocale(LC_NUMERIC, "");

   while (TRUE)
   {
      char *command = showPrompt();
      removeEnter(command);
      int option = verifyCommand(command);

      switch (option)
      {
      case CD_NUMBER:
         if (!cd(command))
            showMessage(INVALID_COMMAND);
         break;

      case CA_NUMBER:
         if (!ca(command))
            showMessage(INVALID_COMMAND);
         break;

      case AA_NUMBER:
         if (!aa(command))
            showMessage(INVALID_COMMAND);
         break;

      case EA_NUMBER:
         if (!ea(command))
            showMessage(INVALID_COMMAND);
         break;

      case LA_NUMBER:
         if (!la(command))
            showMessage(INVALID_COMMAND);
         break;

      case FA_NUMBER:
         if (!fa(command))
            showMessage(INVALID_COMMAND);
         break;

      case DA_NUMBER:
         if (!da(command))
            showMessage(INVALID_COMMAND);
         break;

      case LD_NUMBER:
         if (!ld(command))
            showMessage(INVALID_COMMAND);
         break;

      case FD_NUMBER:
         if (!fd(command))
            showMessage(INVALID_COMMAND);
         break;

      case ET_NUMBER:
         if (!et(command))
            showMessage(INVALID_COMMAND);
         break;

      case EF_NUMBER:
         goto exit;

      case IA_NUMBER:
         if (!ia(command))
            showMessage(INVALID_COMMAND);
         break;
      }
   }
exit:;

   return EXIT_SUCCESS;
}

// Verifica se o comando existe
int verifyCommand(char *command)
{
   if (strlen(command) <= 1)
      return FALSE;

   if (strncmp(command, CD, SIZE_COMMAND) == 0)
      return CD_NUMBER;

   if (strncmp(command, CA, SIZE_COMMAND) == 0)
      return CA_NUMBER;

   if (strncmp(command, AA, SIZE_COMMAND) == 0)
      return AA_NUMBER;

   if (strncmp(command, EA, SIZE_COMMAND) == 0)
      return EA_NUMBER;

   if (strncmp(command, LA, SIZE_COMMAND) == 0)
      return LA_NUMBER;

   if (strncmp(command, FA, SIZE_COMMAND) == 0)
      return FA_NUMBER;

   if (strncmp(command, DA, SIZE_COMMAND) == 0)
      return DA_NUMBER;

   if (strncmp(command, LD, SIZE_COMMAND) == 0)
      return LD_NUMBER;

   if (strncmp(command, FD, SIZE_COMMAND) == 0)
      return FD_NUMBER;

   if (strncmp(command, ET, SIZE_COMMAND) == 0)
      return ET_NUMBER;

   if (strncmp(command, EF, SIZE_COMMAND) == 0)
      return EF_NUMBER;

   if (strncmp(command, IA, SIZE_COMMAND) == 0)
      return IA_NUMBER;
}

// Exibe o prompt
char *showPrompt()
{
   char *command = (char *)malloc(COMMAND_SIZE * sizeof(char));

   printf("\n%s", PROMPT);
   fgets(command, COMMAND_SIZE, stdin);

   return command;
}

// Valida os dados digitados e se for válido cria o disco
int cd(char *command)
{
   int i = 0;
   unsigned int size;
   char diskId;
   char *aux;
   VirtualDisk *virtualDisk;

   if (strlen(command) < 6)
      return FALSE;

   char *token = strtok(command, DELIMITATOR);

   while (token != NULL)
   {
      if (i > 2)
         return FALSE;

      if (i == 1)
      {
         if (strlen(token) == 1 && !verifyDigit(token))
         {
            diskId = toupper(token[0]);
            if (getVirtualDisk(diskId, MODE_GET_DISK) != NULL)
            {
               showMessage("\n Unidade já existe!\n");
               return -1;
            }
         }

         else
            return FALSE;
      }

      if (i == 2)
      {
         strcpy(aux, token);
         if (verifyDigit(aux))
            size = atol(aux);

         else
            return FALSE;
      }

      token = strtok(NULL, DELIMITATOR);
      i++;
   }

   virtualDisk = createDisk(diskId, size);

   if (virtualDisk == NULL)
   {
      showMessage("\n Erro na criação do disco\n");
      return -1;
   }

   showMessage("\n Disco criado com sucesso!\n");

   return TRUE;
}

// Valida os dados digitados e se for válido cria um arquivo
int ca(char *command)
{
   int i = 0;
   char filename[FILE_NAME_SIZE];
   char diskId;
   char *aux;

   if (strlen(command) < 6)
      return FALSE;

   char *token = strtok(command, DELIMITATOR);

   while (token != NULL)
   {
      if (i > 2)
         return FALSE;

      if (i == 1)
      {
         if (strlen(token) == 1 && !verifyDigit(token))
         {
            diskId = toupper(token[0]);
            if (getVirtualDisk(diskId, MODE_GET_DISK) == NULL)
            {
               showMessage("\n Unidade não existe!\n");
               return -1;
            }
         }

         else
            return FALSE;
      }

      if (i == 2)
      {
         strcpy(filename, token);
         if (getDescriptorFile(diskId, filename) != -1)
         {
            showMessage("\n Arquivo não existe!\n");
            return -1;
         }
      }

      token = strtok(NULL, DELIMITATOR);
      i++;
   }

   create(diskId, filename);

   printf("\n Arquivo criado com sucesso!\n");

   return TRUE;
}

// Valida os dados digitados e se for válido abre o arquivo
int aa(char *command)
{
   int i = 0;
   char filename[FILE_NAME_SIZE];
   char diskId;
   char *aux;
   unsigned int fd;

   if (strlen(command) < 6)
      return FALSE;

   char *token = strtok(command, DELIMITATOR);

   while (token != NULL)
   {
      if (i > 2)
         return FALSE;

      if (i == 1)
      {
         if (strlen(token) == 1 && !verifyDigit(token))
         {
            diskId = toupper(token[0]);
            if (getVirtualDisk(diskId, MODE_GET_DISK) == NULL)
            {
               printf("\n Unidade não existe!\n");
               return -1;
            }
         }

         else
            return FALSE;
      }

      if (i == 2)
      {
         strcpy(filename, token);
         fd = getDescriptorFile(diskId, filename);

         if (fd == -1)
         {
            printf("\n Arquivo não existe!\n");
            return -1;
         }
      }

      token = strtok(NULL, DELIMITATOR);
      i++;
   }

   open(fd);

   showMessage("\n Arquivo aberto!\n");

   return TRUE;
}

// Valida os dados digitados e se for válido escreve os dados no arquivo
int ea(char *command)
{
   int i = 0;
   char filename[FILE_NAME_SIZE];
   char diskId;
   char *aux;
   char buffer[COMMAND_SIZE];
   char data[COMMAND_SIZE];
   unsigned int fd;
   Size quantityOfData;
   Size sizeData;

   if (strlen(command) < 6)
      return FALSE;

   strcpy(data, command);

   char *token = strtok(command, DELIMITATOR);

   while (token != NULL)
   {
      if (i == 3)
      {
         if (verifyDigit(token))
         {
            sizeData = SIZE_NUMERIC;

            quantityOfData = getDataWrite(data, buffer, filename, TRUE);
            break;
         }

         else
         {
            sizeData = SIZE_STRING;

            quantityOfData = getDataWrite(data, buffer, filename, FALSE);
            break;
         }
      }

      if (i == 1)
      {
         if (strlen(token) == 1 && !verifyDigit(token))
         {
            diskId = toupper(token[0]);
            if (getVirtualDisk(diskId, MODE_GET_DISK) == NULL)
            {
               printf("\n Unidade não existe!\n");
               return -1;
            }
         }

         else
            return 0;
      }

      if (i == 2)
      {
         strcpy(filename, token);
         fd = getDescriptorFile(diskId, filename);

         if (fd == -1)
         {
            printf("\n Arquivo não existe");
            return -1;
         }
      }

      token = strtok(NULL, DELIMITATOR);
      i++;
   }

   if (write(buffer, sizeData, quantityOfData, fd) == TRUE)
   {
      showMessage("\n Escrita no arquivo realizada!\n");

      return TRUE;
   }

   return ERROR_WRITE_FILE;
}

// Valida os dados digitados e se for válido lê o arquivo
int la(char *command)
{
   int i = 0;
   char filename[FILE_NAME_SIZE];
   char diskId;
   char *aux;
   Size fd;
   char *buffer;
   Size sizeBuffer;
   FileType fileType;

   if (strlen(command) < 6)
      return FALSE;

   char *token = strtok(command, DELIMITATOR);

   while (token != NULL)
   {
      if (i > 2)
         return FALSE;

      if (i == 1)
      {
         if (strlen(token) == 1 && !verifyDigit(token))
         {
            diskId = toupper(token[0]);
            if (getVirtualDisk(diskId, MODE_GET_DISK) == NULL)
            {
               printf("\n Unidade não existe!\n");
               return 0;
            }
         }

         else
            return FALSE;
      }

      if (i == 2)
      {
         strcpy(filename, token);
         fd = getDescriptorFile(diskId, filename);

         if (fd == -1)
         {
            printf("\n Arquivo não existe!");
            return 0;
         }
      }

      token = strtok(NULL, DELIMITATOR);
      i++;
   }

   fileType = getTypeFile(diskId, fd);

   if (fileType == STRING)
      sizeBuffer = getSizeFile(fd) + 1;

   else
      sizeBuffer = getNumericSizeFile(fd) + 1;

   buffer = (char *)malloc(sizeBuffer * sizeof(char));

   cleanString(buffer, sizeBuffer);

   if (read(buffer, STRING, sizeBuffer, fd) == TRUE)
      showMessage(buffer);

   else
      showMessage("\nErro na leitura do arquivo!\n");

   free(buffer);

   return TRUE;
}

// Valida os dados digitados e se for válido fecha o arquivo
int fa(char *command)
{
   int i = 0;
   char filename[FILE_NAME_SIZE];
   char diskId;
   char *aux;
   unsigned int fd;

   if (strlen(command) < 6)
      return FALSE;

   char *token = strtok(command, DELIMITATOR);

   while (token != NULL)
   {
      if (i > 2)
         return FALSE;

      if (i == 1)
      {
         if (strlen(token) == 1 && !verifyDigit(token))
         {
            diskId = toupper(token[0]);
            if (getVirtualDisk(diskId, MODE_GET_DISK) == NULL)
            {
               printf("\n Unidade não existe!\n");
               return -1;
            }
         }

         else
            return FALSE;
      }

      if (i == 2)
      {
         strcpy(filename, token);
         fd = getDescriptorFile(diskId, filename);

         if (fd == -1)
         {
            printf("\n Arquivo não existe!\n");
            return -1;
         }
      }

      token = strtok(NULL, DELIMITATOR);
      i++;
   }

   close(fd);

   showMessage("\n Arquivo fechado\n");

   return TRUE;
}

// Valida os dados digitados e se for válido exclui o arquivo
int da(char *command)
{
   int i = 0;
   char filename[FILE_NAME_SIZE];
   char diskId;
   char *aux;
   unsigned int fd;

   if (strlen(command) < 6)
      return FALSE;

   char *token = strtok(command, DELIMITATOR);

   while (token != NULL)
   {
      if (i > 2)
         return FALSE;

      if (i == 1)
      {
         if (strlen(token) == 1 && !verifyDigit(token))
         {
            diskId = toupper(token[0]);
            if (getVirtualDisk(diskId, MODE_GET_DISK) == NULL)
            {
               printf("\n Unidade não existe!\n");
               return -1;
            }
         }

         else
            return FALSE;
      }

      if (i == 2)
      {
         strcpy(filename, token);
         fd = getDescriptorFile(diskId, filename);

         if (fd == -1)
         {
            printf("\n Arquivo não existe!");
            return -1;
         }
      }

      token = strtok(NULL, DELIMITATOR);
      i++;
   }

   if (erase(fd))
   {
      showMessage("\n Arquivo excluído!\n");

      return TRUE;
   }

   return ERROR_DELETE_FILE;
}

// Valida os dados digitados e se for válido exibe os dados do disco
int ld(char *command)
{
   int i = 0;
   char diskId;
   char *aux;
   DiskInformation *diskInformation;

   if (strlen(command) < 4)
      return FALSE;

   char *token = strtok(command, DELIMITATOR);

   while (token != NULL)
   {
      if (i > 1)
         return FALSE;

      if (i == 1)
      {
         if (strlen(token) == 1 && !verifyDigit(token))
         {
            diskId = toupper(token[0]);
            if (getVirtualDisk(diskId, MODE_GET_DISK) == NULL)
            {
               showMessage("\n Unidade não existe!\n");
               return -1;
            }
         }
         else
            return FALSE;
      }

      token = strtok(NULL, DELIMITATOR);
      i++;
   }

   diskInformation = getDiskInformation(diskId);

   if (diskInformation != NULL)
   {
      showReport(*diskInformation);
      return TRUE;
   }

   return FALSE;
}

// Valida os dados digitados e se for válido formata o disco
int fd(char *command)
{
   int i = 0;
   char diskId;
   char *aux;
   VirtualDisk *virtualDisk;

   if (strlen(command) < 4)
      return FALSE;

   char *token = strtok(command, DELIMITATOR);

   while (token != NULL)
   {
      if (i > 1)
         return FALSE;

      if (i == 1)
      {
         if (strlen(token) == 1 && !verifyDigit(token))
         {
            diskId = toupper(token[0]);
            if (getVirtualDisk(diskId, MODE_GET_DISK) == NULL)
            {
               printf("\n Unidade não existe!\n");
               return -1;
            }
         }

         else
            return FALSE;
      }

      token = strtok(NULL, DELIMITATOR);
      i++;
   }

   if (format(diskId) == TRUE)
      showMessage("\n Disco formatado com sucesso!\n");

   return TRUE;
}

// Valida os dados digitados e se for válido exibe o tamanho e a quantidade de blocos do arquivo
int et(char *command)
{
   int i = 0;
   char filename[FILE_NAME_SIZE];
   char diskId;
   char *aux;
   unsigned int fd;

   if (strlen(command) < 6)
      return FALSE;

   char *token = strtok(command, DELIMITATOR);

   while (token != NULL)
   {
      if (i > 2)
         return FALSE;

      if (i == 1)
      {
         if (strlen(token) == 1 && !verifyDigit(token))
         {
            diskId = toupper(token[0]);
            if (getVirtualDisk(diskId, MODE_GET_DISK) == NULL)
            {
               printf("\n Unidade não existe!\n");
               return -1;
            }
         }

         else
            return FALSE;
      }

      if (i == 2)
      {
         strcpy(filename, token);
         fd = getDescriptorFile(diskId, filename);

         if (fd == -1)
         {
            printf("\n Arquivo não existe!\n");
            return -1;
         }
      }

      token = strtok(NULL, DELIMITATOR);
      i++;
   }

   showSizeFile(fd);

   return TRUE;
}

// Valida os dados digitados e se for válido tenta importar os dados
int ia(char *command)
{
   int i = 0;
   char diskId;
   char *aux;
   char path[SIZE_FILE_NAME];

   cleanString(path, SIZE_FILE_NAME);

   if (strlen(command) < 4)
      return FALSE;

   char *token = strtok(command, DELIMITATOR);

   while (token != NULL)
   {
      if (i > 2)
         return FALSE;

      if (i == 2)
         strcpy(path, token);

      if (i == 1)
      {
         if (strlen(token) == 1 && !verifyDigit(token))
         {
            diskId = toupper(token[0]);
            if (getVirtualDisk(diskId, MODE_GET_DISK) == NULL)
            {
               showMessage("\n Unidade não existe!\n");
               return -1;
            }
         }
         else
            return FALSE;
      }

      token = strtok(NULL, DELIMITATOR);
      i++;
   }

   if (path[strlen(path) - 1] == '/')
   {
      showMessage("\n Não é possível abrir um diretório!\n");
      return -1;
   }

   if (import(diskId, path) == TRUE)
   {
      showMessage("\n Arquivo importado com sucesso!\n");

      return TRUE;
   }

   return -1;
}

/**
   Cria um disco virtual.

   @param size especifica a capacidade máxima de armazenamento em bytes do disco;
   @param diskID letra de identificação do disco, por exemplo C, D, E, etc.

   @return um ponteiro para a estrutura de armazenamento criada para o disco, se ocorrer erro retorna NULL.
*/
VirtualDisk *createDisk(char diskID, Size size)
{
   VirtualDisk *virtualDisk = getVirtualDisk(diskID, MODE_CREATE_DISK);
   SystemDisks *systemDisks = getSystemDisks();

   virtualDisk->numberOfFiles = 0;
   virtualDisk->disk.capacity = size;
   virtualDisk->disk.freeSpace = size;
   virtualDisk->disk.usedSpace = 0;
   virtualDisk->disk.totalClusters = size / LOGICAL_BLOCK_SIZE;
   virtualDisk->disk.occupiedClusters = 0;
   virtualDisk->disk.availableClusters = virtualDisk->disk.totalClusters;
   systemDisks->diskID[systemDisks->numberOfDisks] = diskID;
   systemDisks->numberOfDisks++;

   return virtualDisk;
}

/**
   Cria um arquivo para leitura e escrita no disco.

   @param diskID letra de identificação do disco, por exemplo C, D, E, etc;
   @param fileName nome do arquivo.

   @return um inteiro que representa o descritor de arquivo ou ERROR_CREATE_FILE se o arquivo não pode ser criado.
 */
int create(char diskID, const char *fileName)
{
   VirtualDisk *virtualDisk = getVirtualDisk(diskID, MODE_GET_DISK);
   SystemDisks *systemDisks = getSystemDisks();
   unsigned char position;
   FileDescriptor fd = getNumberFileDescriptor();
   File file;
   file.fileIdentification.fileDescriptor = fd;
   strcpy(file.fileIdentification.name, fileName);
   file.size = 0;
   file.content = NULL;
   file.clusters = 0;
   file.open = 0;
   strcpy(file.hour, getCurrentTime());

   position = getPositionDisk(diskID, *systemDisks);

   systemDisks->fileIdentification[position][virtualDisk->numberOfFiles] = (FileIdentification *)malloc(sizeof(FileIdentification));

   systemDisks->fileIdentification[position][virtualDisk->numberOfFiles]->fileDescriptor = file.fileIdentification.fileDescriptor;
   strcpy(systemDisks->fileIdentification[position][virtualDisk->numberOfFiles]->name, file.fileIdentification.name);

   virtualDisk->fileAllocationTable[virtualDisk->numberOfFiles] = file;
   virtualDisk->numberOfFiles++;

   return fd;
}

/**
   Abre um arquivo para leitura e escrita.

   @param fileDescripton identificação do arquivo.

   @return TRUE se o arquivo foi aberto e ERROR_OPEN_FILE se ocorrer algum erro, por exemplo, o arquivo não existe.
*/
int open(FileDescriptor fileDescriptor)
{
   SystemDisks systemDisks = *getSystemDisks();
   VirtualDisk *virtualDisk = getVirtualDisk(getDiskID(fileDescriptor, systemDisks), MODE_GET_DISK);

   unsigned short position = getPositionFile(fileDescriptor, virtualDisk);

   virtualDisk->fileAllocationTable[position].open = 1;

   return TRUE;
}

/**
   Obtém a identificação do disco virtual onde o arquivo está armazenado.

   @param fileDescripton identificação do arquivo;
   @param systemDisks relação de discos do sistema de arquivos.

   @return a letra de identificação do disco, por exemplo C, D, E, etc., onde o arquivo está armazenado.
 */
char getDiskID(FileDescriptor fileDescriptor, SystemDisks systemDisks)
{
   VirtualDisk *virtualDisk;

   for (int i = 0; i < systemDisks.numberOfDisks; i++)
   {
      virtualDisk = getVirtualDisk(systemDisks.diskID[i], MODE_GET_DISK);

      for (int j = 0; j < virtualDisk->numberOfFiles; j++)
         if (virtualDisk->fileAllocationTable[j].fileIdentification.fileDescriptor == fileDescriptor)
            return systemDisks.diskID[i];
   }

   return FALSE;
}

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
int write(const void *buffer, Size size, Size number, FileDescriptor fileDescriptor)
{
   SystemDisks systemDisks = *getSystemDisks();
   char diskId = getDiskID(fileDescriptor, systemDisks);
   VirtualDisk *virtualDisk = getVirtualDisk(diskId, MODE_GET_DISK);

   unsigned short position = getPositionFile(fileDescriptor, virtualDisk);
   unsigned char isNumeric = size == SIZE_NUMERIC ? TRUE : FALSE;
   File *file = &virtualDisk->fileAllocationTable[position];

   if (file->open == 0)
   {
      showMessage("\n Arquivo fechado");
      ERROR_WRITE_FILE;
   }

   if (number == 0 || size == 0)
   {
      showMessage("\n Nada a ser escrito no arquivo!\n");
      return ERROR_WRITE_FILE;
   }

   if ((number * size) > virtualDisk->disk.freeSpace)
   {
      printf("\n O disco %c atingiu sua capacidade máxima de armazenamento de %'d bytes.\n", diskId, virtualDisk->disk.capacity);
      return ERROR_WRITE_FILE;
   }

   virtualDisk->disk.usedSpace -= file->size;

   file->size += (number * size);
   file->clusters = (file->size / LOGICAL_BLOCK_SIZE) + 1;

   if (verifyDigit((char *)buffer))
   {
      size = STRING;
      number = strlen(buffer) + 1;
   }

   // Obtém o novo tamanho do file.content verificando se é a primeira inserção
   Size newSize = (file->content == NULL) ? 0 : file->size;
   newSize += (number * size) + 1;

   void *newContent = malloc(newSize);

   cleanString(newContent, newSize);

   // Concatena as strings
   if (file->content != NULL)
   {
      newContent = file->content;
      strcat(file->content, buffer);
   }

   else
   {
      strcat(newContent, buffer);
      file->content = newContent;
   }

   strcat(file->content, "\n");

   if (isNumeric)
      file->clusters = (file->size / LOGICAL_BLOCK_SIZE);

   else
      file->clusters = (file->size / LOGICAL_BLOCK_SIZE) + 1;

   if (size == SIZE_NUMERIC)
      file->type = NUMERIC;

   else
      file->type = STRING;

   virtualDisk->disk.usedSpace += file->size;
   virtualDisk->disk.freeSpace = virtualDisk->disk.capacity - virtualDisk->disk.usedSpace;
   virtualDisk->disk.availableClusters = (virtualDisk->disk.freeSpace / LOGICAL_BLOCK_SIZE) + 1;
   virtualDisk->disk.occupiedClusters = (virtualDisk->disk.usedSpace / LOGICAL_BLOCK_SIZE) + 1;
}

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
int read(void *buffer, Size size, Size number, FileDescriptor fileDescriptor)
{
   SystemDisks systemDisks = *getSystemDisks();
   VirtualDisk *virtualDisk = getVirtualDisk(getDiskID(fileDescriptor, systemDisks), MODE_GET_DISK);

   unsigned short position = getPositionFile(fileDescriptor, virtualDisk);

   File *file = &virtualDisk->fileAllocationTable[position];

   if (file->open == 0)
   {
      showMessage("\n Arquivo fechado");
      ERROR_READ_FILE;
   }

   if (number == 0 || size == 0)
      return ERROR_READ_FILE;

   // Obtém o conteúdo de "content" se não for nulo
   if (file->content != NULL)
   {
      size_t contentSize = strlen((char *)file->content);

      strcat(buffer, file->content);

      return TRUE;
   }

   return ERROR_READ_FILE;
}

/**
   Fecha o arquivo.

   @param fileDescripton identificação do arquivo.

   @return TRUE se a operação for bem sucedida ou ERROR_CLOSE_FILE se não conseguir fechar o arquivo.
*/
int close(FileDescriptor fileDescriptor)
{
   SystemDisks systemDisks = *getSystemDisks();
   VirtualDisk *virtualDisk = getVirtualDisk(getDiskID(fileDescriptor, systemDisks), MODE_GET_DISK);

   unsigned short position = getPositionFile(fileDescriptor, virtualDisk);

   virtualDisk->fileAllocationTable[position].open = 0;

   return TRUE;
}

/**
   Apaga o arquivo do disco.

   @param fileDescripton identificação do arquivo.

   @return TRUE se a operação for bem sucedida ou ERROR_DELETE_FILE se não conseguir excluir o arquivo do disco virtual.
*/
int erase(FileDescriptor fileDescriptor)
{
   char confirm;
   SystemDisks systemDisks = *getSystemDisks();
   char diskId = getDiskID(fileDescriptor, systemDisks);
   VirtualDisk *virtualDisk = getVirtualDisk(diskId, MODE_GET_DISK);

   unsigned short position = getPositionFile(fileDescriptor, virtualDisk);

   if (virtualDisk->fileAllocationTable[position].open == 1)
   {
      showMessage("\n Não é possível excluir um arquivo aberto!");

      return ERROR_DELETE_FILE;
   }

   showMessage("\n Confirmar exclusão [S ou N] ?\n");

   confirm = getchar();

   clearBuffer();

   if (toupper(confirm) == 'N')
   {
      showMessage(" Exclusão cancelada");

      return ERROR_DELETE_FILE;
   }

   unsigned char positionDisk = getPositionDisk(diskId, systemDisks);
   File file = virtualDisk->fileAllocationTable[position];

   virtualDisk->disk.freeSpace += file.size;
   virtualDisk->disk.usedSpace -= file.size;
   virtualDisk->disk.availableClusters = (virtualDisk->disk.freeSpace / LOGICAL_BLOCK_SIZE);
   virtualDisk->disk.occupiedClusters = virtualDisk->disk.totalClusters - virtualDisk->disk.availableClusters;

   virtualDisk->numberOfFiles--;

   virtualDisk->fileAllocationTable[position] = virtualDisk->fileAllocationTable[virtualDisk->numberOfFiles];

   systemDisks.fileIdentification[positionDisk][position] = systemDisks.fileIdentification[positionDisk][virtualDisk->numberOfFiles];

   return TRUE;
}

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
DiskInformation *getDiskInformation(char diskID)
{
   DiskInformation *diskInformation = (DiskInformation *)malloc(sizeof(DiskInformation));

   VirtualDisk *virtualDisk = getVirtualDisk(diskID, MODE_GET_DISK);

   if (virtualDisk == NULL)
      return NULL;

   diskInformation->diskID = diskID;
   diskInformation->virtualdisk = *virtualDisk;

   return diskInformation;
}

// Exibe um relatório
void showReport(DiskInformation diskInformation)
{
   printf("\n Disco %c\n", diskInformation.diskID);
   printf("\n  Nome\t\t\tTipo\t\tHora\t\tTamaho\t\tBlocos");

   for (int i = 0; i < diskInformation.virtualdisk.numberOfFiles; i++)
   {
      File file = diskInformation.virtualdisk.fileAllocationTable[i];
      printf("\n  %s\t\t%s\t\t%s\t%'d bytes\t%'d", file.fileIdentification.name, file.type == NUMERIC ? "Numérico" : "Texto", file.hour, file.size, file.clusters);
   }

   printf("\n\n Número de arquivos: %'d\n", diskInformation.virtualdisk.numberOfFiles);
   printf("\n Capacidade do disco: %'d bytes", diskInformation.virtualdisk.disk.capacity);
   printf("\n Espaço ocupado: %'d bytes", diskInformation.virtualdisk.disk.usedSpace);
   printf("\n Espaço livre: %'d bytes\n", diskInformation.virtualdisk.disk.freeSpace);
   printf("\n Total de blocos lógicos: %'d", diskInformation.virtualdisk.disk.totalClusters);
   printf("\n Blocos lógicos ocupados: %'d", diskInformation.virtualdisk.disk.occupiedClusters);
   printf("\n Blocos lógicos livres: %'d\n", diskInformation.virtualdisk.disk.availableClusters);
}

/**
   Formata logicamente o disco virtual apagando todo o conteúdo de sua tabela de alocação de arquivos, consequentemente
   apagando todo os arquivos do disco. Reinicializa os dados da estrutura do disco. Toda a memória alocada dinamicamente
   para armazenar a estrutura do disco e de seus arquivos devem ser liberadas, ou seja, devolvidas ao sistema operacional.

   @param diskID letra de identificação do disco, por exemplo C, D, E, etc.

   @return TRUE em caso de sucesso, caso contrário, FALSE.
*/
int format(char diskID)
{
   char confirm;
   VirtualDisk *virtualDisk = getVirtualDisk(diskID, MODE_GET_DISK);
   SystemDisks *systemDisks = getSystemDisks();
   unsigned char position;

   if (virtualDisk == NULL)
   {
      showMessage("\n Disco virtual não existe!\n");
      return FALSE;
   }

   showMessage("\n Todos os dados serão excluídos, confirma a formatação [S ou N] ?\n");

   confirm = getchar();

   clearBuffer();

   if (toupper(confirm) == 'N')
   {
      showMessage("\n Formatação cancelada!\n");

      return FALSE;
   }

   position = getPositionDisk(diskID, *systemDisks);

   systemDisks->numberOfDisks--;

   if (position > 0)
      systemDisks->diskID[position] = systemDisks->diskID[systemDisks->numberOfDisks];

   cleanFileIdentification(position, systemDisks, virtualDisk->numberOfFiles);

   getVirtualDisk(diskID, MODE_REMOVE_DISK);

   return TRUE;
}

// Exibe o tamanho e a quantidade de blocos de um arquivo
int showSizeFile(FileDescriptor fileDescriptor)
{
   SystemDisks systemDisks = *getSystemDisks();
   VirtualDisk *virtualDisk = getVirtualDisk(getDiskID(fileDescriptor, systemDisks), MODE_GET_DISK);

   unsigned short position = getPositionFile(fileDescriptor, virtualDisk);

   printf("\n Tamanho = %'d bytes", virtualDisk->fileAllocationTable[position].size);
   printf("\n Blocos = %'d\n", virtualDisk->fileAllocationTable[position].clusters);

   return TRUE;
}

// Importa um arquivo
int import(const char diskId, const char *path)
{
   char *buffer = NULL;
   char fileLine[SIZE_FILE_LINE];
   char *fileName;
   Size fd;
   Size sizeBuffer = 0;
   VirtualDisk *virtualDisk = getVirtualDisk(diskId, MODE_GET_DISK);

   FILE *file = openFile(path, FILE_OPEN);

   if (file == NULL)
   {
      showMessage("\n Não foi possível abrir o arquivo!\n");
      return ERROR_OPEN_FILE;
   }

   cleanString(fileLine, SIZE_FILE_LINE);

   while (fgets(fileLine, sizeof(SIZE_FILE_LINE), file) != NULL)
   {
      sizeBuffer += strlen(fileLine) + 1;

      reallocateBuffer(&buffer, sizeBuffer);

      strcat(buffer, fileLine);

      cleanString(fileLine, SIZE_FILE_LINE);
   }

   fileName = strrchr(path, '/');

   if (virtualDisk->disk.freeSpace < sizeBuffer)
   {
      printf("\n O disco %c atingiu sua capacidade máxima de armazenamento de %'d bytes.\n", diskId, virtualDisk->disk.capacity);
      return FALSE;
   }

   if (fileName != NULL)
   {
      fileName++;
      fd = create(diskId, fileName);
   }

   else
      fd = create(diskId, path);

   open(fd);

   write(buffer, SIZE_STRING, sizeBuffer, fd);

   close(fd);

   fclose(file);

   free(buffer);

   return TRUE;
}

/**
   Cria ou obtém o endereço da estrutura de armazenamento do disco.

   @param diskID letra de identificação do disco, por exemplo C, D, E, etc;
   @param mode informa o modo de acesso ao disco virtual, os valores válidos são: MODE_CREATE_DISK e MODE_GET_DISK 1.

   Se mode for MODE_CREATE_DISK e a letra de identificação do drive for válida, a função cria o disco e retorna um ponteiro para sua estrutura de armazenamento.
   Se mode for MODE_GET_DISK e a letra de identificação do drive for válida, a função obtém o ponteiro para a estrutura de armazenamento do disco previamente criada.

   @return NULL se ocorrer algum erro na criação ou no acesso ao disco ou se a identificação do drive for inválida.
*/
VirtualDisk *getVirtualDisk(char drive, char mode)
{
   static VirtualDisk *virtualDisk[NUMBER_OF_DISKS];
   static unsigned char currentNumberOfDisks = 0;
   unsigned char indexOfDisk;

   if (drive >= CHARACTER_CODE_A && drive <= CHARACTER_CODE_Z && currentNumberOfDisks < NUMBER_OF_DISKS)
   {
      indexOfDisk = toupper(drive) - CHARACTER_CODE_A;

      switch (mode)
      {
      case MODE_CREATE_DISK:
         virtualDisk[indexOfDisk] = (VirtualDisk *)calloc(1, sizeof(VirtualDisk));
         currentNumberOfDisks++;

         return virtualDisk[indexOfDisk] != NULL ? virtualDisk[indexOfDisk] : NULL;

      case MODE_GET_DISK:
         return virtualDisk[indexOfDisk] != NULL ? virtualDisk[indexOfDisk] : NULL;

      case MODE_REMOVE_DISK:
         if (virtualDisk[indexOfDisk] != NULL)
         {
            free(virtualDisk[indexOfDisk]);
            virtualDisk[indexOfDisk] = NULL;
            currentNumberOfDisks--;
         }

         return NULL;
      }
   }
   return NULL;
}

// Obtém o endereço do "System Disks"
SystemDisks *getSystemDisks()
{
   static SystemDisks *systemDisks;
   static char firstCall = 1;

   if (firstCall == 1)
   {
      systemDisks = (SystemDisks *)malloc(sizeof(SystemDisks));

      systemDisks->numberOfDisks = 0;

      firstCall = 0;
   }

   return systemDisks;
}

// Obtém o número do descritor de arquivo
FileDescriptor getNumberFileDescriptor()
{
   static FileDescriptor fileDescriptor = 0;

   return fileDescriptor++;
}

// Obtém os dados que serão salvos no buffer
Size getDataWrite(char *command, char *buffer, const char *fileName, const char number)
{
   int quantityOfData = 0;
   char *token = strtok(command, DELIMITATOR);

   cleanString(buffer, COMMAND_SIZE);

   while (token != NULL)
   {
      if (strcmp(token, fileName) == 0)
      {
         if (number)
            token = strtok(NULL, " ");

         else
            token = strtok(NULL, "");

         break;
      }
      token = strtok(NULL, DELIMITATOR);
   }

   if (number)
   {
      strcpy(buffer, token);

      quantityOfData++;

      while (token != NULL)
      {
         token = strtok(NULL, DELIMITATOR);

         if (token == NULL)
            break;

         strcat(buffer, " ");
         strcat(buffer, token);

         quantityOfData++;
      }
   }

   else
   {
      strcpy(buffer, token);

      quantityOfData = strlen(token);
   }

   return quantityOfData;
}

// Realoca o tamanho de um buffer
void reallocateBuffer(char **buffer, const Size sizeBuffer)
{
   *buffer = (char *)realloc(*buffer, sizeBuffer * sizeof(char));
}

// Limpa o vetor de arquivos no "System Disks"
void cleanFileIdentification(unsigned char position, SystemDisks *systemDisks, const Size numberOfFiles)
{
   for (size_t i = 0; i < numberOfFiles; i++)
      free(systemDisks->fileIdentification[position][i]);
}

// Obtém o tamanho de um arquivo
Size getSizeFile(FileDescriptor fd)
{
   SystemDisks systemDisks = *getSystemDisks();
   VirtualDisk *virtualDisk = getVirtualDisk(getDiskID(fd, systemDisks), MODE_GET_DISK);

   unsigned short position = getPositionFile(fd, virtualDisk);

   return virtualDisk->fileAllocationTable[position].size;
}

// Obtém o tamanho do "content" se o arquivo for numérico
Size getNumericSizeFile(FileDescriptor fd)
{
   SystemDisks systemDisks = *getSystemDisks();
   VirtualDisk *virtualDisk = getVirtualDisk(getDiskID(fd, systemDisks), MODE_GET_DISK);

   unsigned short position = getPositionFile(fd, virtualDisk);
   Size sizeFile;

   void *content = virtualDisk->fileAllocationTable[position].content;

   if (content == NULL)
      return 0;

   sizeFile = strlen((char *)content);

   return sizeFile;
}

// Obtém a posição de um arquivo no disco virtual com determinado descritor de arquivo
unsigned short getPositionFile(FileDescriptor fd, VirtualDisk *virtualDisk)
{
   for (int i = 0; i < virtualDisk->numberOfFiles; i++)
      if (virtualDisk->fileAllocationTable[i].fileIdentification.fileDescriptor == fd)
         return i;
}

// Obtém a posição do disco no "SystemDisks"
unsigned char getPositionDisk(char diskId, const SystemDisks systemDisks)
{
   for (int i = 0; i < systemDisks.numberOfDisks; i++)
      if (systemDisks.diskID[i] == diskId)
         return i;

   return -1;
}

// Obtém o descritor de arquivo de um arquivo
int getDescriptorFile(const char drive, const char *fileName)
{
   VirtualDisk *virtualDisk = getVirtualDisk(drive, MODE_GET_DISK);

   for (int i = 0; i < virtualDisk->numberOfFiles; i++)
   {
      if (strcmp(fileName, virtualDisk->fileAllocationTable[i].fileIdentification.name) == 0)
         return virtualDisk->fileAllocationTable[i].fileIdentification.fileDescriptor;
   }

   return -1;
}

// Obtém o tipo do arquivo
FileType getTypeFile(const char diskId, const Size fd)
{
   VirtualDisk *virtualDisk = getVirtualDisk(diskId, MODE_GET_DISK);

   for (int i = 0; i < virtualDisk->numberOfFiles; i++)
   {
      if (virtualDisk->fileAllocationTable[i].fileIdentification.fileDescriptor == fd)
         return virtualDisk->fileAllocationTable[i].type;
   }

   return 0;
}

// Verifica se a string possui dígitos
int verifyDigit(const char *command)
{
   for (int i = 0; i < strlen(command); i++)
   {
      if (!isdigit(command[i]))
         return 0;
   }

   return 1;
}

// Obtém a hora atual
char *getCurrentTime()
{
   time_t currentTime;
   struct tm *localTime;
   char *timeString = (char *)malloc(HOUR_SIZE * sizeof(char));

   time(&currentTime);
   localTime = localtime(&currentTime);

   sprintf(timeString, "%02d:%02d:%02d", localTime->tm_hour, localTime->tm_min, localTime->tm_sec);

   return timeString;
}

// Exibe uma mensagem
void showMessage(const char *message)
{
   printf("%s", message);
}

// Abre um arquivo, mode é o modo de abertura
FILE *openFile(const char *path, const char *mode)
{
   return fopen(path, mode);
}

// Limpa o buffer do teclado
void clearBuffer()
{
   int c;
   while ((c = getchar()) != '\n' && c != EOF)
      ;
}

// Limpa a string com o tamanho especificado em size
void cleanString(char *string, unsigned short size)
{
   memset(string, '\0', size);
}

// Remove o "\n" do final das strings
void removeEnter(char *string)
{
   int index = 0;

   while (string[index] != '\0')
   {
      if (string[index] == '\n')
      {
         string[index] = '\0';

         break;
      }

      index++;
   }
}

int main()
{
   return filesystem();
}