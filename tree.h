#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>
#include <string.h>

typedef struct node {
	wchar_t val;
        int fin;
        int nbr_fils;
	struct node** fils;
}Node, *PtNode, *Tree;

typedef struct dico {
        struct node** tab_ptr_tree;
        int taille;
}dico;

void cons_tree(struct node **, wchar_t);

void mk_empty_tree(dico*);

void init_dico(dico*);

void add(struct node **, wchar_t* ,int ,int);

int size(wchar_t*);

void toLowerCase(wchar_t*);

void splitcarac(dico*,wchar_t*,wchar_t*);

void load_dico(FILE *, dico*,wchar_t*);

void free_tree(struct node *);

void free_dico(dico);

int find_erreur(dico,FILE*,wchar_t*);

int find_mot(dico,wchar_t*);

int split_text(dico,wchar_t*,wchar_t*);