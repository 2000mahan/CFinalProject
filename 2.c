#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
nn->next=NULL;
return nn;

}
struct node *My_list(struct node **list, int number)
{
FILE *fp;
int tmp=number;
char buf[100], issue[200], decision1[200], decision2[200];
int p_d1, d_d1, k_d1, p_d2, d_d2, k_d2;
int static counter=1;
snprintf(buf, sizeof(buf), "c%d.txt", counter);
counter++;
fp=fopen(buf, "r");
fgets(issue, 201, fp);
fgets(decision1, 201, fp);
fscanf(fp, "%d", &p_d1);
fscanf(fp, "%d", &d_d1);
fscanf(fp, "%d", &k_d1);
fgets(decision2, 201, fp);
fgets(decision2, 201, fp);
fscanf(fp, "%d", &p_d2);
fscanf(fp, "%d", &d_d2);
fscanf(fp, "%d", &k_d2);
fclose(fp);
*list=create_node(issue, decision1,p_d1, d_d1, k_d1, decision2, p_d2, d_d2, k_d2);
int static count=0;
count++;
if(count==tmp)
    return 0;
    else

return My_list(&((*list)->next), number);
}

int main()
{
FILE *fp;
int i=0, counter=0;
char**filename;
char buf[10];
struct node *list;
fp=fopen("CHOICES.txt", "r");
if(fp==NULL)
    return 0;
while(fgets(buf, 8, fp)!=NULL)
counter++;
close(fp);
My_list(&list, counter);

}


