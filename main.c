#include "tree.h"

int main(int argc, char *argv[])
{
  setlocale(LC_ALL, "");
  
  //Récupération du fichier contenant le dictionnaire
  char fichier[100];
  if (argc == 3) strcpy(fichier, argv[1]);

  FILE *fp = NULL;
  if (argc != 3) wprintf(L"Quel fichier voulez-vous utiliser comme dictionnaire ?\n");
  do
  {
    if (argc != 3) wscanf(L"%s", fichier);
    fp = fopen(fichier, "r");
    if (fp == NULL)
    {
      if (argc == 3)
      {
        wprintf(L"Le fichier n'est pas accessible !\n");
        return 1;
      }
      else wprintf(L"Le fichier n'est pas accessible !\nEntrez un autre nom de fichier :\n");
    }
  } while (fp == NULL);

  //Choix des séparateurs
  wchar_t separateur[] = L",?;.:/!*+\\\"()=«»[]";

  wprintf(L"La liste des séparateurs est : %ls  \nVoulez vous la changer ?[Y]\n", separateur);
  char changer_separateur = ' ';
  wscanf(L" %c", &changer_separateur);
  if (changer_separateur == 'Y' || changer_separateur == 'y')
  {
    do
    {
      wprintf(L"Entrez la nouvelle liste des séparateur :\n");
      wscanf(L"%ls", separateur);
      wprintf(L"La liste des séparateurs :  %ls vous convient ?[Y]\n", separateur);
      wscanf(L" %c", &changer_separateur);
    } while (changer_separateur != 'Y' && changer_separateur != 'y');
  }

  //Chargement du dictionnaire
  dico Dico;
  init_dico(&Dico);
  load_dico(fp, &Dico, separateur);
  fclose(fp);
  wprintf(L"Chargement du dictionnaire effectué!\n\n");

  //Récupération du fichier contenant les mots à tester
  char recommencer = ' ';
  do
  {
    FILE *fp = NULL;
    if (argc != 3) wprintf(L"Quel fichier voulez-vous tester ?\n");
    else strcpy(fichier, argv[2]);
    do
    {
      if (argc != 3) wscanf(L"%s", fichier);
      fp = fopen(fichier, "r");
      if (fp == NULL)
      {
        if (argc == 3)
        {
          wprintf(L"Le fichier n'est pas accessible !\n");
          return 1;
        }
        else wprintf(L"Le fichier n'est pas accessible !\nEntrez un autre nom de fichier :\n");
      }
    } while (fp == NULL);

    //Vérification des mots du fichier
    int result = find_erreur(Dico, fp, separateur);
    wprintf(L"Le fichier testé contient %d mots qui ne sont pas présent dans le dictionnaire.\n", result);
    fclose(fp);

    //Demande si volonté de recommencer
    if (argc != 3){
      wprintf(L"Voulez vous tester un autre fichier ?[Y]\n");
      wscanf(L" %c", &recommencer);
    }else recommencer = ' ';

  } while (recommencer == 'Y' || recommencer == 'y');

  free_dico(Dico); //libérer la mémoire du dictionnaire

  wprintf(L"Fin du programme\n");

  return 0;
}
