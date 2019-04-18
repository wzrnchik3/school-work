#include "famTree.h"

// famTree::famTree()
// {
//     for (int i = 0; i < MAX_NODE; i ++)
//         fams[i] = new fnode;
// }

void famTree::insert(int personid, int parent, int marriage)
{
    // insert person and family relationships
    people[personid].pid = personid;
    people[personid].m = marriage;
    people[personid].p = parent;

    // text output with if statements for unknowns
    cout << "Individual " << personid << " has ";
    if (parent == 0)
        cout << "unknown parents";
    else
        cout << "parents " << parent;
    if (marriage == 0)
        cout << " and is not married.\n";
    else
        cout << " and is married in family " << marriage << endl;
    
}

void famTree::family(int famid, int hid, int wid, int cid[], int numC)
{
    // put family data in
    fams[famid].fid = famid;
    fams[famid].h = hid;
    fams[famid].w = wid;
    fams[famid].numChildren = numC;
    if (numC != 0)
        for (int i = 0; i < numC; i++)
            fams[famid].c[i] = cid[i];
    
    // text output
    cout << "Family " << famid << " has husband " << hid << ", wife " << wid
        << ", and children";
    if (numC != 0)
        for (int j = 0; j < numC; j++)
            cout << " " << cid[j];
    else
        cout << " none";
    cout << endl;
}

void famTree::check()
{
    bool cPointer = false;
    for (int i = 1; i < MAX_NODE; i++)
    {
        if (people[i].pid != -1)
        {
            if (people[i].m != 0)
            {
                if (people[i].pid != fams[people[i].m].h && people[i].pid != fams[people[i].m].w)
                {
                    cout << "Individual " << i << " points to marriage family " << people[i].m
                        << " but there is no backpointer.\n";
                }
            }
            if (people[i].p != 0)
            {
                for (int j = 0; j < fams[people[i].p].numChildren; j++)
                    if (fams[people[i].p].c[j] == people[i].pid)
                        cPointer = true;
                if (cPointer = false)
                {
                    cout << "Individual " << i << "points to parent family " << people[i].p
                        << " but there is no backpointer.\n";
                }
            }
        }
    }
    for (int k = 1; k < MAX_CHILDREN; k++)
    {
        if (fams[k].fid != -1)
        {
            if (fams[k].h != 0)
            {
                if (people[fams[k].h].m != k)
                {
                    cout << "Family " << k << " points to husband " << fams[k].h
                        << " but there is no backpointer.\n";
                }
            }
            if (fams[k].w != 0)
            {
                if (people[fams[k].w].m != k)
                {
                    cout << "Family " << k << " points to wife " << fams[k].w
                        << " but there is no backpointer.\n";
                }
            }
            if (fams[k].numChildren != 0)
            {
                for (int it = 0; it < fams[k].numChildren; it++)
                {
                    if (people[fams[k].c[it]].p != k)
                    {
                        cout << "Family " << k << " points to child " << fams[k].c[it]
                            << " but there is no backpointer.\n";
                    }
                }
            }
        }
    }
}

bool famTree::isPQEmpty() { return (pQueue.front == pQueue.rear); }

bool famTree::isFQEmpty() { return (fQueue.front == fQueue.rear); }

int famTree::advance(int index) { return ((index + 1) % MAX_NODE); }

void famTree::insertPQ(int data)
{
    pQueue.contents[pQueue.rear] = data;
    pQueue.rear = advance(pQueue.rear);
}

void famTree::insertFQ(int data)
{
    fQueue.contents[fQueue.rear] = data;
    fQueue.rear = advance(fQueue.rear);
}

int famTree::deletePQ()
{
    int answer = pQueue.contents[pQueue.front];
    if (pQueue.front == pQueue.rear)
        return -1;
    pQueue.front = advance(pQueue.front);
    return answer;
}

int famTree::deleteFQ()
{
    int answer = fQueue.contents[fQueue.front];
    if (fQueue.front == fQueue.rear)
        return -1;
    fQueue.front = advance(fQueue.front);
    return answer;
}

void famTree::resetQ()
{
    pQueue.front = 0;
    pQueue.rear = 0;
    fQueue.front = 0;
    fQueue.rear = 0;
    for (int i = 0; i < MAX_NODE; i++)
    {
        pQueue.contents[i] = 0;
        fQueue.contents[i] = 0;
    }
}

void famTree::printRelate(int fPath[], int pPath[], int start, int end)
{
	int newfpath[MAX_NODE], newppath[MAX_NODE], fct = 0, pct = 0, ct = 0, currPerson = end;

	for (int f = 0; f < MAX_NODE; f++) { 
		newfpath[f] = 0;
		newppath[f] = 0;
	}
	for (int j = 0; j < MAX_NODE; j++) {
		if (people[currPerson].m == fPath[j] && fPath[j] != 0) { 
			newfpath[fct] = fPath[j];
			fct += 1;
		}
		if (people[currPerson].p == fPath[j] && fPath[j] != 0) { 
			newfpath[fct] = fPath[j];
			fct += 1;
		}
		if (fams[people[currPerson].p].w == pPath[j] && pPath[j] != 0) { 
			newppath[pct] = pPath[j];
			pct += 1;
		}
		if (fams[people[currPerson].p].h == pPath[j] && pPath[j] != 0) { 
			newppath[pct] = pPath[j];
			pct += 1;
		}
		for (int n = 0; n < MAX_CHILDREN; n++) {	
			if (fams[people[currPerson].p].c[n] == pPath[j] && pPath[j] != 0) { 
				newppath[pct] = pPath[j];
				pct += 1;
			}
		}
		if (fams[people[currPerson].m].w == pPath[j] && pPath[j] != 0) { 
			newppath[pct] = pPath[j];
			pct += 1;
		}
		if (fams[people[currPerson].m].h == pPath[j] && pPath[j] != 0) {
			newppath[pct] = pPath[j];
			pct += 1;
		}
		for (int n = 0; n < MAX_CHILDREN; n++) {
			if (fams[people[currPerson].p].w == pPath[j] && pPath[j] != 0) {
				newppath[pct] = pPath[j];
				pct += 1;
			}
		}
		if (newppath[ct] != 0) { 
			currPerson = newppath[ct];
			ct += 1;
		}

	}
	cout << "Individual " << start; 
	for (int i = 0; i < fct; i++) {
		if (i > 0) { 
			if (newfpath[i] != newfpath[i-1] && newfpath != 0)
				cout << " Family " << newfpath[i];
		}
		else
			cout << " Family " << newfpath[i]; 
		if (i <= fct - 1 && newppath[i] != 0) { 
			cout << " Individual " << newppath[i]; 
		}
	
	}

	cout << " Individual " << end << endl; 
}

void famTree::relate(int start, int end)
{
    int pPlace = 0, fPlace = 0, pCount = 0, fCount = 0, pPath[MAX_NODE], fPath[MAX_NODE];
    bool pVisited[MAX_NODE], fVisited[MAX_NODE];
    for (int i = 0; i < MAX_NODE; i++) 
    {
        pVisited[i] = false;
        fVisited[i] = false;
        fPath[i] = 0;
        pPath[i] = 0;
    }
    pVisited[start] = true;
    fVisited[people[start].m] = true;
    fVisited[people[start].p] = true;
    insertPQ(start);
    insertFQ(people[start].m);
    insertFQ(people[start].p);
    while (!isPQEmpty() || !isFQEmpty())
    {
        pPlace = deletePQ();
        fPlace = deleteFQ();
        if (pPlace > 0)
        {
            if (people[pPlace].m != 0 && !fVisited[people[pPlace].m])
            {
                fVisited[people[pPlace].m] = true;
                insertFQ(people[pPlace].m);
                pPath[pCount] = pPlace;
                pCount += 1;
            }
            if (people[pPlace].p != 0 && !fVisited[people[pPlace].p])
            {
                fVisited[people[pPlace].p] = true;
                insertFQ(people[pPlace].p);
                pPath[pCount] = pPlace;
                pCount += 1;
            }
        }
        if (fPlace > 0)
        {
            if (fams[fPlace].w != 0 && !pVisited[fams[fPlace].w])
            {
                pVisited[fams[fPlace].w] = true;
                insertPQ(fams[fPlace].w);
                fPath[fCount] = fPlace;
                fCount += 1;
                if (fams[fPlace].w == end)
                {
                    printRelate(fPath, pPath, start, end);
                    return;
                }
            }
            if (fams[fPlace].h != 0 && !pVisited[fams[fPlace].h])
            {
                pVisited[fams[fPlace].h] = true;
                insertPQ(fams[fPlace].h);
                fPath[fCount] = fPlace;
                fCount += 1;
                if (fams[fPlace].h == end)
                {
                    printRelate(fPath, pPath, start, end);
                    return;
                }
            }
            for (int i = 0; i < MAX_CHILDREN; i++)
            {
                if (fams[fPlace].c[i] != 0 && !pVisited[fams[fPlace].c[i]])
                {
                    pVisited[fams[fPlace].c[i]] = true;
                    insertPQ(fams[fPlace].c[i]);
                    if (fPath[fCount] != fPlace)
                    {
                        fPath[fCount] = fPlace;
                        fCount += 1;
                    }
                    if (fams[fPlace].c[i] == end)
                    {
                        printRelate(fPath, pPath, start, end);
                        return;
                    }
                }
            }
        }
    }
    cout << "Individuals " << start << " and " << end << " are not connected\n";
}