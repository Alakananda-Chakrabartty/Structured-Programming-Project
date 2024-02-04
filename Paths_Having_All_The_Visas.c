// Coded By : Alakananda Chakrabartty
// Student ID : 220206
// CSE Discipline, Khulna University
// This is a code to check whether a passenger have all the visas to reach a definite country
// N.B : Not more than 10 adjacent nodes can be used in this code


#include <stdio.h>
int total = 0;
int visa[50]={0};
struct Node
{
    int nodeid;
    int adjcount;
    int adjs[10];
    int costs[10];
};
// Adding the nodes
int addNode (struct Node * p, int nid, int count)
{
    int i =0, ncount = count;
    for (i=0; i<count; i++)
    {
        if (p[i].nodeid == nid)
        {
            break;
        }
    }
    if (i == count)
    {
        p[i].nodeid = nid;
        p[i].adjcount = 0;
        ncount++;
    }
    return ncount;
}
//Adding the adjacent nodes 
void addAdjacent (struct Node *p, int nid1, int nid2, int cost, int count)
{
    int i =0, index;
    for (i=0; i < count; i++)
    {
        if (p[i].nodeid == nid1)
        {
            int c = p[i].adjcount;
            p[i].adjs[c] = nid2;
            p[i].costs[c] = cost;
            p[i].adjcount = c+1;

            break;
        }
    }
}

// Checking the node ID
int added (int * list, int lcount, int nid)
{
    int i =0;
    for (i=0; i<lcount; i++)
    {
        if (list[i] == nid)
        {
            return 1;
        }
    }
    return 0;
}

// Finding the path
void findpath (struct Node * p, int count, int start, int end, int * list, int *clist, int lcount)
{
    int index = 0, i=0;


    //Checking if list contains the end node
    if (list[lcount-1] == end)
    {
        int notPossible = 0 ;
        for (int k = 1; k<lcount; k++)
        {
            int flag = 0;
            for(int j = 0; j < total; j++)
            {
                if(list[k] == visa[j])
                {
                    flag = 1;
                    break;
                }
            }
            if(flag == 0)
            {
                notPossible = 1;
                break;
            }
        }
        printf ("\n");
        if(notPossible == 0)
        {
            int tcost = 0;
            for (i=0; i<lcount; i++)
            {
                printf (" %d ", list[i]);
                tcost += clist[i];
            }
            printf (" cost = %d", tcost);

        }
        return;

    }
    
    // Finding the starting node 
    for (i=0; i<count; i++)
    {
        if (p[i].nodeid == start)
        {
            index = i;
            break;
        }
    }

    for (i=0; i<p[index].adjcount; i++)
    {
        int a = added (list, lcount, p[index].adjs[i]);
        if (a == 0)
        {
            list[lcount] = p[index].adjs[i];
            clist[lcount] = p[index].costs[i];
            lcount++;

            findpath (p, count, p[index].adjs[i], end, list, clist, lcount);
            lcount--;
        }
    }
}


int main()
{

    struct Node nodes[50];
    int nodecount = 0;
    int n1=0, n2=0, c = 0;

    while (1)
    {
        printf ("n1, n2, cost ? ");
        scanf("%d %d %d", &n1, &n2, &c);
        if (n1 == -9 || n2 == -9 || c== -9)
        {
            break;
        }
        nodecount = addNode (&nodes[0], n1, nodecount);
        nodecount = addNode (&nodes[0], n2, nodecount);

        addAdjacent (&nodes[0], n1, n2, c, nodecount);
        addAdjacent (&nodes[0], n2, n1, c, nodecount);
    }

    int start, end;
    printf ("start, end ? ");
    scanf ("%d %d", &start, &end );
    printf("Enter the list of Visas : \n");
    int visa_No;

    // Taking the inputs of visa
    while(1)
    {
        scanf("%d",&visa_No);
        if(visa_No == -9)
            break;
        visa[total]=visa_No;
        total++;
    }
    int list[50], clist[50], lcount = 0;
    list[0] = start;
    clist[0] = 0;
    lcount = 1;

    findpath (nodes, nodecount, start, end,list, clist, lcount);

    return 0;
}
