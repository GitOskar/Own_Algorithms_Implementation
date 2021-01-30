#include <iostream>

using namespace std;

struct Person
{
    string surname;
    unsigned x;
};


void insert_sort (Person* arr, unsigned int size)
{
    int j, k;
    Person tmp;
    for ( unsigned i=1 ; i<size ; i++ )
    {
        if ( arr[i].x > arr[i-1].x || ( arr[i].x == arr[i-1].x && arr[i].surname < arr[i-1].surname ))
        {
            tmp = arr[i];

            for ( j=i-1 ; ( j>=0 ) && ( arr[j].x < tmp.x )  ; j-- )
                    arr[j+1] = arr[j];

            for ( k=j ; ( k>=0 ) && arr[k].x == tmp.x && arr[k].surname > tmp.surname ; k-- )
                    arr[k+1] = arr[k];

            arr[k+1] = tmp;
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);

    unsigned t;
    cin >> t;

    unsigned p, n;

    unsigned long long time;

    Person* arr;


    for ( unsigned i=0 ; i < t ; i++ )
    {
        cin >> n >> p;
        time = n;
        arr = new Person[n];

        for ( unsigned i=0 ; i<n ; i++)
            cin >> arr[i].surname >> arr[i].x;

        insert_sort( arr, n );

        for ( unsigned i=0 ; i<p ; i++ )
        {
            cout << arr[i].surname << " ";
            time += arr[i].x*i;
        }

        for ( unsigned i=p ; i<n ; i++ )
            time += arr[i].x*i;

        cout << endl << time % 1000003 << endl;

        delete [] arr;
    }
    return 0;
}