#include<stdio.h>
#include<stdlib.h>

struct node
{
    int start, end;
    struct node *left, *right;
};

struct node *createNewNode(int start, int end)
{
    struct node *newNode = (struct node*)malloc(sizeof(struct node));
    newNode->start = start;
    newNode->end = end;
    newNode->left = newNode->right = NULL;
    return newNode;

}

struct node *insert(struct node *root, int m, int n, int start, int end)
{
    int mid = (m+n)/2;

    if(root == NULL)
    {
        root = createNewNode(m, n);

        if( m == end || n == start )
        {
            return NULL;
        }

    }

    if(start <= m && end >= n)
    {
        return root;
    }

    if(start <= mid)
    {
        root->left = insert(root->left, m, mid, start, end);
    }

    if(end >= mid)
    {
        root->right = insert(root->right, mid, n, start, end);
    }

    return root;
}

struct node *deleteNode(struct node *root, int m, int n, int start, int end)
{
    if(root != NULL)
    {
        if( m == end || n == start )
        {
            return root;
        }

        if(start <= m && end >= n)
        {
            return NULL;
        }
        int mid = (m+n)/2;

        if(start <= mid)
        {
            root->left = deleteNode(root->left, m, mid, start, end);
        }

        if(end >= mid)
        {
            root->right = deleteNode(root->right, mid, n, start, end);
        }

    }

    return root;
}

void preOrder(struct node *root)
{
    if(root!= NULL)
    {
        printf("( %d, %d) -> ", root->start, root->end);
        preOrder(root->left);
        preOrder(root->right);
    }

}

void inOrder(struct node *root)
{
    if(root!= NULL)
    {
        inOrder(root->left);
        printf("( %d, %d) -> ", root->start, root->end);
        inOrder(root->right);
    }

}

int main()
{

    int n, m, start, end, ch;
    printf("\nEnter the range to construct segment tree...");
    scanf("%d%d", &m, &n);
    struct node *root = NULL;
    while(1)
    {
        printf("\nDynamic Segment Trees...\n1.Insert\n2.Delete\nSelect any 1...");
        scanf("%d", &ch);
        switch(ch)
        {
        case 1:
            printf("Enter the range to insert in the segment tree...");
            scanf("%d%d", &start,&end);

            root = insert(root, m, n, start, end);
            printf("\nPreOrder\n");
            preOrder(root);
            printf("\nInOrder\n");
            inOrder(root);
            break;
        case 2:
            printf("\nEnter the range to delete in the segment tree...");
            scanf("%d%d", &start,&end);
            root = deleteNode(root, m, n, start, end);
            printf("\nPreOrder\n");
            preOrder(root);
            printf("\nInOrder\n");
            inOrder(root);
            break;

        }

    }

}