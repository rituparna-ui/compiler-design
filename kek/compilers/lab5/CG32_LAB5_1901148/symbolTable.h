#include <stdlib.h>


typedef struct symboltable
{
  char *name;    
  char *type;         
  struct symboltable *next;
} symboltable;




symboltable *sym_table ;

symboltable *insert ();
symboltable *search ();

symboltable * insert ( char *sym_name, char *sym_type )
{
    
    symboltable *ptr;
    ptr = (symboltable *) malloc (sizeof(symboltable));
    ptr->name = strdup(sym_name);
    ptr->type = strdup(sym_type);
    ptr->next = (symboltable *)sym_table;
    sym_table = ptr;
    return ptr; 
}
symboltable * search ( char *sym_name )
{
    symboltable *ptr=sym_table;
    while(ptr!=NULL){
        if (strcmp (ptr->name,sym_name) == 0)
            return ptr;
        ptr = (symboltable *)ptr->next;
    }
    //for (ptr = sym_table; ptr != (symtable *) 0; ptr = (symtable *)ptr->next)
        
    return 0;
}
