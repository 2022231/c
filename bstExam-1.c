#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node
{
    char name[100], roll[100];
    float cgpa;
    int rank;
    struct node *left, *right;
};

int nodes = 0;

void inorder(struct node *root)
{
    if(root != NULL)
    {
        inorder(root->left);
        printf("%s ( %.2f ) ->", root->name, root->cgpa);
        inorder(root->right);
    }
}

void rank(struct node *root)
{
    if(root != NULL)
    {
        rank(root->left);
        printf("%s ( %.2f - %d) ->", root->name, root->cgpa, nodes--);
        rank(root->right);
    }
}


void display(struct node *root)
{
    printf("\nInorder traversal...\n");
    inorder(root);
}

struct node *newNode(char *name, char *roll, float cgpa)
{
    struct node *temp = (struct node*)malloc(sizeof(struct node));
    temp->cgpa = cgpa;
    strcpy(temp->name, name);
    strcpy(temp->roll, roll);
    temp->left = temp->right = NULL;
    return temp;
}


struct node *insertNode(struct node *node, char *name, char *roll, float cgpa)
{
    if(node == NULL) return newNode(name, roll, cgpa);
    if(cgpa < node->cgpa)
        node->left = insertNode(node->left, name, roll, cgpa);
    else
        node->right = insertNode(node->right, name, roll, cgpa);
    return node;

}

void nodeNumbers(struct node *root)
{
    if(root!= NULL)
    {
        nodeNumbers(root->left);
        nodes++;
        nodeNumbers(root->right);
    }

}
int main()
{
    int choice, option;
    char name[100], roll[100];
    float cgpa;
    struct node *root = NULL;
    do
    {
        printf("\nBST\n1.Insert\n2.Rank..");
        scanf("%d",&option);
        switch(option)
        {
        case 1:
        {

            printf("Enter name...");
            scanf("%s",name);
            printf("Enter roll no..");
            scanf("%s",roll);
            printf("Enter cgpa...");
            scanf("%f",&cgpa);
            root = insertNode(root, name, roll, cgpa);
            display(root);
            break;
        }
        case 2:
        {
            nodeNumbers(root);
            rank(root);
            break;
        }


        }
        printf("\nPress 1 to continue else 0...");
        scanf("%d",&choice);
    }
    while(choice);
}
