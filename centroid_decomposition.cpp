// C++ program for centroid decomposition of Tree
#include <bits/stdc++.h>
using namespace std;
#define MAXN 200005
vector<int> tree[MAXN];
vector<int> centroidTree[MAXN];
bool centroidMarked[MAXN];

/* method to add edge between to nodes of the undirected tree */
void addEdge(int u, int v)
{
	tree[u].push_back(v);
	tree[v].push_back(u);
}
/* method to setup subtree sizes and nodes in current tree */
void DFS(int src, bool visited[], int subtree_size[], int* n)
{
	visited[src] = true;
	/* increase count of nodes visited */
	*n += 1;
	/* initialize subtree size for current node*/
	subtree_size[src] = 1;
	vector<int>::iterator it;
	/* recur on non-visited and non-centroid neighbours */
	for (it = tree[src].begin(); it!=tree[src].end(); it++)
		if (!visited[*it] && !centroidMarked[*it])
		{
			DFS(*it, visited, subtree_size, n);
			subtree_size[src]+=subtree_size[*it];
		}
}
int getCentroid(int src, bool visited[], int subtree_size[], int n)
{
	/* assume the current node to be centroid */
	bool is_centroid = true;
	/* mark it as visited */
	visited[src] = true;
	/* track heaviest child of node, to use in case node is
	not centroid */
	int heaviest_child = 0;
	vector<int>::iterator it;
	/* iterate over all adjacent nodes which are children
	(not visited) and not marked as centroid to some
	subtree */
	for (it = tree[src].begin(); it!=tree[src].end(); it++)
		if (!visited[*it] && !centroidMarked[*it])
		{
			/* If any adjacent node has more than n/2 nodes,
			* current node cannot be centroid */
			if (subtree_size[*it]>n/2)
				is_centroid=false;

			/* update heaviest child */
			if (heaviest_child==0 ||
				subtree_size[*it]>subtree_size[heaviest_child])
				heaviest_child = *it;
		}
	/* if current node is a centroid */
	if (is_centroid && n-subtree_size[src]<=n/2)
		return src;
	/* else recur on heaviest child */
	return getCentroid(heaviest_child, visited, subtree_size, n);
}
/* function to get the centroid of tree rooted at src.
* tree may be the original one or may belong to the forest */
int getCentroid(int src)
{
	bool visited[MAXN];
	int subtree_size[MAXN];
	/* initialize auxiliary arrays */
	memset(visited, false, sizeof visited);
	memset(subtree_size, 0, sizeof subtree_size);
	/* variable to hold number of nodes in the current tree */
	int n = 0;
	/* DFS to set up subtree sizes and nodes in current tree */
	DFS(src, visited, subtree_size, &n);
	for (int i=1; i<MAXN; i++)visited[i] = false;
	int centroid = getCentroid(src, visited, subtree_size, n);
	centroidMarked[centroid]=true;
	return centroid;
}
vector<int>v1;
/* function to generate centroid tree of tree rooted at src */
int decomposeTree(int root)
{
	//printf("decomposeTree(%d)\n", root);
	/* get centroid for current tree */
	int cend_tree = getCentroid(root);
	v1.push_back(cend_tree);
	return 0;
	// vector<int>::iterator it;
	// /* for every node adjacent to the found centroid
	// * and not already marked as centroid */
	// for (it=tree[cend_tree].begin(); it!=tree[cend_tree].end(); it++)
	// {
	// 	if (!centroidMarked[*it])
	// 	{
	// 		/* decompose subtree rooted at adjacent node */
	// 		int cend_subtree = decomposeTree(*it);

	// 		/* add edge between tree centroid and centroid of subtree */
	// 		centroidTree[cend_tree].push_back(cend_subtree);
	// 		centroidTree[cend_subtree].push_back(cend_tree);
	// 	}
	// }

	// /* return centroid of tree */
	// return cend_tree;
}
int main()
{
	int n;
	cin>>n;
	vector<int> v(n+1);
	for(int i=0;i<n-1;i++){
		int a,b;cin>>a>>b;
		addEdge(a,b);
	}
	decomposeTree(1);
	cout<<v1[0];
	return 0;
}
