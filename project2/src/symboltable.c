#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<math.h>
#include"header.h"

#define TABLE_SIZE	256

symtab * hash_table[TABLE_SIZE];
extern int linenumber;

int HASH(char * str)
{
	int idx=0;
	while(*str)
	{
		idx = idx << 1;
		idx+=*str;
		str++;
	}	
	return (idx & (TABLE_SIZE-1));
}

/*returns the symbol table entry if found else NULL*/

symtab * lookup(char *name)
{
	int hash_key;
	symtab* symptr;
	if(!name)
		return NULL;
	hash_key=HASH(name);
	symptr=hash_table[hash_key];

	while(symptr)
	{
		if(!(strcmp(name,symptr->lexeme)))
			return symptr;
		symptr=symptr->front;
	}
	return NULL;
}


void insertID(char *name)
{
	int hash_key;
	symtab* ptr;
	symtab* symptr=(symtab*)malloc(sizeof(symtab));	
	
	hash_key=HASH(name);
	ptr=hash_table[hash_key];
	
	if(ptr==NULL)
	{
		/*first entry for this hash_key*/
		hash_table[hash_key]=symptr;
		symptr->front=NULL;
		symptr->back=symptr;
	}
	else
	{
		symptr->front=ptr;
		ptr->back=symptr;
		symptr->back=symptr;
		hash_table[hash_key]=symptr;	
	}
	
	strcpy(symptr->lexeme,name);
	symptr->line=linenumber;
	symptr->counter=1;
}

void printSym(symtab* ptr) 
{
	// printf(" Name = %s \n", ptr->lexeme);
	// printf(" References = %d \n", ptr->counter);
	printf("%s\t\t%d \n", ptr->lexeme, ptr->counter);

}

void printSymTab()
{
    int i, j = 0;
	int insert_case, insert_position;
    printf("Frequency of identifiers:\n");
    for (i=0; i<TABLE_SIZE; i++)
    {
        symtab* symptr;
		symptr = hash_table[i];
		while (symptr != NULL)
		{
			symptr=symptr->front;
			j++;
		}
    }
	symtab * temp_hash_table[j];
	j = -1;
	for (i=0; i<TABLE_SIZE; i++)
    {
        symtab* symptr;
		symptr = hash_table[i];
		while (symptr != NULL)
		{
			j++;
			temp_hash_table[j] = symptr;
			symptr=symptr->front;
		}
    }

	// Insertion sorting
	symtab* key;
	for (j = 1; j<sizeof(temp_hash_table)/8; j++)
	{
		key = temp_hash_table[j];
		i = j - 1;
		while((i > -1) && (strcmp(temp_hash_table[i]->lexeme, key->lexeme) > 0))
		{
			temp_hash_table[i+1] = temp_hash_table[i];
			i--;
		}
		temp_hash_table[i+1] = key;
	}
	
	// Print the result after sorting
	for(i = 0; i<sizeof(temp_hash_table)/8; i++)
		printSym(temp_hash_table[i]);
}