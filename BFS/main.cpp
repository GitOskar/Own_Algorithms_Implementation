#include<iostream>
#include <queue>
using namespace std;
struct Coordinates
{
    int i, j;
};

class Graph
{
    int height, width, MAX, shortest_way;
    char** map;
    int **cams, **visited;
    Coordinates start_cord, end_cord;

public:
    Graph();
    void find_shortest_way();
};

Graph::Graph()
{
    cin >> height >> width;
    MAX = height * width;
    map = new char* [height];
    cams = new int* [height];
    visited = new int* [height];
    for (int i=0 ; i<height ; i++)
    {
        map[i] = new char[width];
        cams[i] = new int[width];
        visited[i] = new int[width];
        cin >> map[i];
        for (int j=0 ; j<width ; j++)
        {
            if ( map[i][j] == 'S' )
            {
                start_cord.i = i;
                start_cord.j = j;
            }
            if ( map[i][j] == 'X' )
            {
                end_cord.i = i;
                end_cord.j = j;
            }

            cams[i][j] = MAX;
            visited[i][j] = MAX;
        }
    }

    shortest_way = MAX-1;

}
void Graph::find_shortest_way()
{
    map[start_cord.i][start_cord.j] = '#';
    visited[start_cord.i][start_cord.j] = 0;
    cams[start_cord.i][start_cord.j] = 0;

    queue<Coordinates> q;

    q.push(start_cord);

    Coordinates tmp;

    while ( !q.empty() )
    {
        tmp = q.front();
        q.pop();

        if ( map[tmp.i][tmp.j] == 'X' )
            shortest_way = visited[tmp.i][tmp.j];

        else if ( visited[tmp.i][tmp.j] < shortest_way )
        {
        if ( tmp.i-1 >= 0 )
            if ( map[tmp.i-1][tmp.j] != '#' )
                if ( ( visited[tmp.i-1][tmp.j] > visited[tmp.i][tmp.j]+1 ) || ( visited[tmp.i-1][tmp.j] == visited[tmp.i][tmp.j]+1 && cams[tmp.i-1][tmp.j] > cams[tmp.i][tmp.j] ) )
                {
                    if ( visited[tmp.i-1][tmp.j] == MAX )
                        q.push( { tmp.i-1, tmp.j } );
                    if ( map[tmp.i-1][tmp.j] == 'M' )
                        cams[tmp.i-1][tmp.j] = cams[tmp.i][tmp.j] + 1;
                    else
                        cams[tmp.i-1][tmp.j] = cams[tmp.i][tmp.j];
                    visited[tmp.i-1][tmp.j] = visited[tmp.i][tmp.j]+1;
                }

        if ( tmp.i+1 < height )
            if ( map[tmp.i+1][tmp.j] != '#' )
                if ( ( visited[tmp.i+1][tmp.j] > visited[tmp.i][tmp.j]+1 ) || ( visited[tmp.i+1][tmp.j] == visited[tmp.i][tmp.j]+1 && cams[tmp.i+1][tmp.j] > cams[tmp.i][tmp.j] ) )
                {
                    if ( visited[tmp.i+1][tmp.j] == MAX )
                        q.push( { tmp.i+1, tmp.j } );

                    if ( map[tmp.i+1][tmp.j] == 'M' )
                        cams[tmp.i+1][tmp.j] = cams[tmp.i][tmp.j] + 1;
                    else
                        cams[tmp.i+1][tmp.j] = cams[tmp.i][tmp.j];
                    visited[tmp.i+1][tmp.j] = visited[tmp.i][tmp.j]+1;

                }

        if ( tmp.j-1 >= 0 )
            if ( map[tmp.i][tmp.j-1] != '#' )
                if ( ( visited[tmp.i][tmp.j-1] > visited[tmp.i][tmp.j]+1 ) || ( visited[tmp.i][tmp.j-1] == visited[tmp.i][tmp.j]+1 && cams[tmp.i][tmp.j-1] > cams[tmp.i][tmp.j] ) )
                {
                    if ( visited[tmp.i][tmp.j-1] == MAX )
                        q.push( { tmp.i, tmp.j-1 } );
                    if ( map[tmp.i][tmp.j-1] == 'M' )
                        cams[tmp.i][tmp.j-1] = cams[tmp.i][tmp.j] + 1;
                    else
                        cams[tmp.i][tmp.j-1] = cams[tmp.i][tmp.j];
                    visited[tmp.i][tmp.j-1] = visited[tmp.i][tmp.j]+1;
                }

        if ( tmp.j+1 < width )
            if ( map[tmp.i][tmp.j+1] != '#' )
                if ( ( visited[tmp.i][tmp.j+1] > visited[tmp.i][tmp.j]+1 ) || ( visited[tmp.i][tmp.j+1] == visited[tmp.i][tmp.j]+1 && cams[tmp.i][tmp.j+1] > cams[tmp.i][tmp.j] ) )
                {
                    if (visited[tmp.i][tmp.j+1] == MAX)
                        q.push( { tmp.i, tmp.j+1 } );
                    if ( map[tmp.i][tmp.j+1] == 'M' )
                        cams[tmp.i][tmp.j+1] = cams[tmp.i][tmp.j] + 1;
                    else
                        cams[tmp.i][tmp.j+1] = cams[tmp.i][tmp.j];
                    visited[tmp.i][tmp.j+1] = visited[tmp.i][tmp.j]+1;
                }
        }
    }
    cout << visited[end_cord.i][end_cord.j] << " " << cams[end_cord.i][end_cord.j];
}

int main()
{
    ios::sync_with_stdio(false);

    Graph graph;

    graph.find_shortest_way();

    return 0;
}