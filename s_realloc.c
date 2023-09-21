#include "shell.h"

/**
* setMemory - fills memory with a constant byte
* @memoryBlock: the pointer to the memory area
* @byteValue: the byte to fill *memoryBlock with
* @byteCount: the amount of bytes to be filled
* Return: (memoryBlock) a pointer to the memory area memoryBlock
*/
char *setMemory(char *memoryBlock, char byteValue, unsigned int byteCount)
{
unsigned int i;
for (i = 0; i < byteCount; i++)
{
memoryBlock[i] = byteValue;
}
return (memoryBlock);
}

/**
* freeStringArray - frees a string array
* @stringArray: string array to be freed
*/
void freeStringArray(char **stringArray)
{
char **array = stringArray;
if (!stringArray)
return;
while (*stringArray)
free(*stringArray++);
free(array);
}

/**
* customRealloc - reallocates a block of memory
* @previousBlock: pointer to the previous malloc'ed block
* @oldSize: byte size of the previous block
* @newSize: byte size of the new block
*
* Return: pointer to the reallocated block
*/
void *customRealloc(void *previousBlock, unsigned int oldSize, unsigned int newSize)
{
char *newBlock;
if (!previousBlock)
return (malloc(newSize));
if (!newSize)
return (free(previousBlock), NULL);
if (newSize == oldSize)
return (previousBlock);
newBlock = malloc(newSize);
if (!newBlock)
return (NULL);
oldSize = oldSize < newSize ? oldSize : newSize;
while (oldSize--)
newBlock[oldSize] = ((char *)previousBlock)[oldSize];
free(previousBlock);
return (newBlock);
}

