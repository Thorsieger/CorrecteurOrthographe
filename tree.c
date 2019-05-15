#include "tree.h"

//Contruction d'un arbre
void cons_tree(struct node **ptr_tree, wchar_t val)
{
  *ptr_tree = malloc(sizeof(struct node));
  (*ptr_tree)->val = val;
  (*ptr_tree)->fin = 0;
  (*ptr_tree)->nbr_fils = 0;
  (*ptr_tree)->fils = malloc(sizeof(struct node *)); //Tableau de taille 1 de pointeur de noeud
  (*ptr_tree)->fils[0] = NULL;                       //Cette node n'a pas de fils
}

//Initialiation de chaque element du dictionnaire à nul
void mk_empty_tree(dico *Dico)
{
  for (int i = 0; i < Dico->taille; i++)
  {
    Dico->tab_ptr_tree[i] = NULL; //Chaque element du dico est vide
  }
}

//Création d'un dictionnaire pour enregister les 26 lettres de l'alphabet
void init_dico(dico *Dico)
{
  Dico->taille = 26;
  Dico->tab_ptr_tree = malloc(Dico->taille * sizeof(struct node *));
  mk_empty_tree(Dico);
}

//ajout d'un mot dans le dictionnaire dans son arbre (liée à la première lettre du mot)
void add(struct node **tab_ptr_tree, wchar_t val[], int taille, int fl)
{
  if (tab_ptr_tree[fl] == NULL)cons_tree(&(tab_ptr_tree[fl]), val[0] + 97); //si l'arbre n'existe pas on le crée

  Node *noeudtest = tab_ptr_tree[fl];
  for (int i = 1; i < taille; i++)//on va travailler sur toutes les lettres du mot
  {
    int trouve = -1;
    for (int j = 0; j < noeudtest->nbr_fils; j++)//On recherche si la lettre existe déja
    {
      if (noeudtest->fils[j]->val == val[i])trouve = j;
    }
    if (trouve == -1)
    {
      //ajouter lettre
      noeudtest->nbr_fils++;
      noeudtest->fils = realloc(noeudtest->fils, (noeudtest->nbr_fils) * sizeof(struct node *));//On ajoute de la place dans le tableau de fils pour y mettre celui ci
      cons_tree(&(noeudtest->fils[(noeudtest->nbr_fils) - 1]), val[i]);
      trouve = noeudtest->nbr_fils - 1;
    }

    noeudtest = noeudtest->fils[trouve]; //on jump au noeud suivant (lettre existante ou venant d'étre créé)
  }
  noeudtest->fin = 1;//On a terminé le mot, cette lettre est la dernière du mot
}

//Calcul de la taille de la chaine de caractère donnée en paramètre
int size(wchar_t val[])
{
  int cpt = 0;
  while (val != NULL && val[cpt] != '\0')
  {
    cpt++;
  }
  return cpt;
}

//Tous les caractères en majuscules sont mis en minuscule (même ceux avec accent)
void toLowerCase(wchar_t mot[])
{
  for (int i = 0; i < size(mot); i++)
  {
    if ((mot[i] <= 'Z' && mot[i] >= 'A') || (mot[i] >= 192 && mot[i] <= 214) || (mot[i] >= 216 && mot[i] <= 222))mot[i] += 32;
    else if (mot[i] == 138 || mot[i] == 140 || mot[i] == 142)mot[i] += 16;
    else if (mot[i] == 159)mot[i] += 96;
  }
}

//Récupération de la première lettre du mot et découpade de celui ci en fonction des séparateurs
void splitcarac(dico *Dico, wchar_t message[], wchar_t separateur[])
{

  wchar_t *buffer;
  wchar_t *token = wcstok(message, separateur, &buffer);//On découpe le mot selon les séparateurs
  if(token == NULL)return;

  //On récupére l'id de la première lettre dans notre dico
  int first_letter = -1;
  if (token[0] >= 'a' && token[0] <= 'z')
  {
    first_letter = (int)token[0] - 97;
  }
  else
  {
    for (int i = 26; i < Dico->taille; i++)//On recherche si elle existe et qu'elle n'est pas de 'a' à 'z'
    {
      if (Dico->tab_ptr_tree[i]->val == token[0])
      {
        first_letter = i;
        break;
      }
    }
    if (first_letter == -1)//Elle n'exite pas, on l'ajoute
    {
      first_letter = Dico->taille;
      Dico->taille++;
      Dico->tab_ptr_tree = realloc(Dico->tab_ptr_tree, (Dico->taille) * sizeof(struct node *));//On laisse la place pour ajouter une première lettre de mot
      Dico->tab_ptr_tree[first_letter] = NULL;
      cons_tree(&(Dico->tab_ptr_tree[first_letter]), token[0]);
    }
  }

  add(Dico->tab_ptr_tree, token, size(token), first_letter);//On ajoute le mot (jusqu'au séparateur) au dictionnaire
  if (buffer != NULL)splitcarac(Dico, buffer, separateur);//S'il reste des mots à ajouter on recommence
}

//Chargement du dictionnaire
void load_dico(FILE *fp, dico *Dico, wchar_t separateur[])
{
  wchar_t val[3000];//Nombre de caractère max sur une page

  while (fwscanf(fp, L"%ls", val) == 1)
  {
    toLowerCase(val);//Les caractères sont mis en miniscule
    splitcarac(Dico, val, separateur);//On ajoute tous les mots au dictionnaire
  }

  //On peut tester la bonne ou mauvaise terminaison de la lecture
  if (ferror(fp))wprintf(L"ERREUR de lecture\n");
}

//On libère toute la mémoire de chaque arbre
void free_tree(struct node *ptr_tree)
{
  if (ptr_tree == NULL)return;//On a terminé
  if (ptr_tree->nbr_fils == 0)//Le noeud n'a pas de fils on peut libérer la mémoire
  {
    free(ptr_tree->fils);
    return;
  }
  for (int i = (ptr_tree->nbr_fils) - 1; i >= 0; i--)//si le noeud à des fils ré-exécute la fontion
  {
    free_tree(ptr_tree->fils[i]);
    free(ptr_tree->fils[i]);
  }
  free(ptr_tree->fils);
}

//On libére la mémoire du dictionnaire
void free_dico(dico Dico)
{
  for (int i = 0; i < Dico.taille; i++)//On libére chaque arbre
  {
    if (Dico.tab_ptr_tree[i] != NULL)
    {
      free_tree(Dico.tab_ptr_tree[i]);
      free(Dico.tab_ptr_tree[i]);
    }
  }
  free(Dico.tab_ptr_tree);
}

//Recherche dans le dictionnaire d'un mot
int find_mot(dico Dico, wchar_t mot[])
{
  if (mot == NULL)return 0;//Pas de mot

  //Récupération de l'indice du dico correspondant à la première lettre de l'arbre
  int fl = -1;
  if (mot[0] >= 'a' && mot[0] <= 'z')
  {
    fl = (int)mot[0] - 97;
  }
  else
  {
    for (int i = 26; i < Dico.taille; i++)
    {
      if (Dico.tab_ptr_tree[i]->val == mot[0])
      {
        fl = i;
        break;
      }
    }
    if (fl == -1){//Si la première lettre n'a pas été trouvé le mot n'existe pas dans le dico
      wprintf(mot);
      wprintf(L"\n");
      return 1;
    }
  }

  int taille = size(mot);
  if (taille == 1 && Dico.tab_ptr_tree[fl] != NULL)//Mot de 1 lettre et arbre existant
  {
    if (Dico.tab_ptr_tree[fl]->fin == 0){//la lettre n'est pas une lettre de terminaison
      wprintf(mot);
      wprintf(L"\n");
      return 1;
      }else return 0; //vrais
  }
  if (Dico.tab_ptr_tree[fl] == NULL)return 1; //faux

  struct node *ptr_node = Dico.tab_ptr_tree[fl];
  for (int i = 1; i < taille; i++)//On teste toute les lettres du mot
  {
    if (ptr_node->nbr_fils == 0){//Le noeud actuel n'a pas de fils
      wprintf(mot);
      wprintf(L"\n");
      return 1;
    }
    for (int k = 0; k < (ptr_node->nbr_fils); k++)//Onteste tous les fils
    {
      if (ptr_node->fils[k]->val == mot[i])//on trouve la lettre
      {
        ptr_node = ptr_node->fils[k];
        break;
      }
      else if (k + 1 == ptr_node->nbr_fils){//on trouve pas
        wprintf(mot);
        wprintf(L"\n");
        return 1;
      }
    }
  }

  if (ptr_node->fin == 0){//on est à la dernière lettre, on regarde si c'est une lettre terminaison
    wprintf(mot);
    wprintf(L"\n");
    return 1;
  }else return 0;
}

//Test de présence de chaque mot du fichier de l'utilisateur
int find_erreur(dico Dico, FILE *fp, wchar_t separateur[])
{
  wchar_t val[3000];
  int cpt_erreur = 0;

  wprintf(L"Mots non reconnus :\n");

  while (fwscanf(fp, L"%ls", val) == 1)
  {
    toLowerCase(val);//Fichier mit en minuscule
    cpt_erreur += split_text(Dico, val, separateur);//découpage et analyse du texte selon les séparateur
  }

  //On peut tester la bonne ou mauvaise terminaison de la lecture
  if (ferror(fp))wprintf(L"ERREUR de lecture\n");

  return cpt_erreur;
}

//Découpage et analyse du texte selon les séparateur
int split_text(dico Dico, wchar_t message[], wchar_t separateur[])
{
  if (message[0] == 0)return 0;
  wchar_t *buffer;
  wchar_t *token = wcstok(message, separateur, &buffer);//Découpage selon les caractère de séparation
  int err = find_mot(Dico, token);//recherche de la présence du mot dans le dictionnaire
  if (buffer != NULL)err += split_text(Dico, buffer, separateur);

  return err;
}
