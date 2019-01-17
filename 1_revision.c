#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//CREATING LINKED LIST//
struct node{
char issue[200];
char decision1[200];
int people_decision1;
int darbar_decision1;
int khazaneh_decision1;
char decision2[200];
int people_decision2;
int darbar_decision2;
int khazaneh_decision2;
struct node* next;
};
struct node *create_node(char issue[200], char decision1[200], int people_decision1, int darbar_decision1, int khazaneh_decision1,char decision2[200], int people_decision2, int darbar_decision2, int khazaneh_decision2)
{
struct node *nn;
nn=(struct node*)malloc(sizeof(struct node));
strcpy(nn->issue, issue);
strcpy(nn->decision1, decision1);
nn->people_decision1=people_decision1;
nn->darbar_decision1=darbar_decision1;
nn->khazaneh_decision1=khazaneh_decision1;
strcpy(nn->decision2, decision2);
nn->people_decision2=people_decision2;
nn->darbar_decision2=darbar_decision2;
nn->khazaneh_decision2=khazaneh_decision2;


return nn;


}

int main()
{



}
