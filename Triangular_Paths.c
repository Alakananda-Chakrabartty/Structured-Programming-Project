// Coded By : Alakananda Chakrabartty
// Student ID : 220206
// CSE Discipline, Khulna University
// This is a code to find out how many triangles are there in a graph and the nodes of them
// N.B : Not more than 10 adjacent nodes can be used in this code

#include<stdio.h>
#include<stdbool.h>

struct Node {
    int nodeid;
    int adjcount;
    int adjs[10];
    int costs[10];
};

// Adding the nodes
int addNode (struct Node * p, int nid, int count) {
    int i = 0, ncount = count;
    for (i = 0; i < count; i++) {
        if (p[i].nodeid == nid) { break; }
    }
    if (i == count) {
        p[i].nodeid = nid;
        p[i].adjcount = 0;
        ncount++;
    }
    return ncount;
}

// Adding the adjacent nodes
void addAdjacent (struct Node *p, int nid1, int nid2, int cost, int count) {
    int i = 0;
    for (i = 0; i < count; i++) {
        if (p[i].nodeid == nid1) {
            int c = p[i].adjcount;
            p[i].adjs[c] = nid2;
            p[i].costs[c] = cost;
            p[i].adjcount = c+1;

            break;
        }
    }
}

// Checking the node ID
int added (int * list, int lcount, int nid) {
    int i = 0;
    for (i = 0; i < lcount; i++) {
        if (list[i] == nid) { return 1; }
    }
    return 0;
}


// Finding the path
void findpath (struct Node * p, int count, int start, int end, int * list, int *clist, int lcount) {
    int index = 0, i = 0;

    if (list[lcount-1] == end) {

        int tcost = 0;
        printf ("\n");
        for (i = 0; i < lcount; i++) {
            printf (" %d ", list[i]);
            tcost += clist[i];
        }
        printf (" cost = %d", tcost);
        return;
    }

    for (i = 0; i < count; i++) {
        if (p[i].nodeid == start) 
        {
            index = i;
            break;
        }
    }

    for (i = 0; i < p[index].adjcount; i++) {
        int a = added (list, lcount, p[index].adjs[i]);
        if (a == 0) {
            list[lcount] = p[index].adjs[i];
            clist[lcount] = p[index].costs[i];
            lcount++;

            findpath (p, count, p[index].adjs[i], end, list, clist, lcount);
            lcount--;
        }
    }
}

// Checking the adjacent node
bool adjacent(struct Node x,struct Node y)
{
    for(int i = 0; i < x.adjcount; i++)
    {
        if(x.adjs[i] == y.nodeid)
            return true;
    }
    return false;
}

int main() {

    struct Node nodes[50],first,second,third;
    int nodecount = 0;
    int n1 = 0, n2 = 0, c = 0;


    while (1) {
        printf ("n1, n2, cost ? ");
        scanf("%d %d %d", &n1, &n2, &c);
        if (n1 == -9 || n2 == -9 || c== -9) {break;}

        nodecount = addNode (nodes, n1, nodecount);
        nodecount = addNode (nodes, n2, nodecount);

        addAdjacent (nodes, n1, n2, c, nodecount);
        addAdjacent (nodes, n2, n1, c, nodecount);
    }

    int count = 0;
    // Checking whether it is a triangle or not
    for(int i = 0; i < nodecount; i++)
    {
        for(int j = i+1; j < nodecount; j++)
        {
            for(int k = j+1; k < nodecount; k++)
            {
                first = nodes[i];
                second = nodes[j];
                third = nodes[k];
                if(adjacent(first,second) && adjacent(second,third) && adjacent(third,first))
                {
                    count++;
                    printf("Yes! It's a triangle and the nodes of this triangle are : %d %d %d\n",first.nodeid,second.nodeid,third.nodeid);
                }
            }
        }
    }
    (count == 0)? printf("There are no triangles in this graph!"): printf("There are %d triangles in this graph!",count);
    
    return 0;
}
