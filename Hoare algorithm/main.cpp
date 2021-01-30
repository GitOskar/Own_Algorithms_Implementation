#include <iostream>

using namespace std;

struct Country
{
    unsigned int id, value;
};

unsigned int find_the_lowest ( Country *arr, unsigned int begin, unsigned int end )
{
    unsigned int tmp = arr[ begin ].id;

    for ( unsigned int i=begin+1 ; i<= end ; i++ )
        if ( tmp > arr[i].id )
            tmp = arr[i].id;

    return tmp;
}

unsigned int partition( Country *arr, unsigned int begin, unsigned int end )
{
    unsigned int pivot = rand() % ( end - begin + 1 ) + begin;

    swap( arr[ begin ], arr[ pivot ] );

    unsigned int tmp=begin;

    for ( unsigned int i=begin+1 ; i<=end ; i++ )
        if ( arr[ i ].value <= arr[ begin ].value )
            swap( arr[ ++tmp ],  arr[i] );

    swap( arr[ begin ], arr[ tmp ] );

    return tmp;
}

unsigned int partition_for_equal( Country *arr, unsigned int begin, unsigned int end )
{
    unsigned int pivot = rand() % ( end - begin + 1 ) + begin;

    swap( arr[ end ], arr[ end ] );

    unsigned int tmp=end;

    int beg = begin;

    for ( int i=end-1 ; i>=beg ; i-- )
        if ( arr[ i ].value == arr[ end ].value )
            swap( arr[ --tmp ],  arr[i] );

    swap( arr[ end ], arr[ tmp ] );

    return tmp;
}

unsigned int quick_select ( Country *arr, unsigned int begin, unsigned int end, unsigned int k )
{
    unsigned last_element_of_list_b = partition( arr, begin, end );

    if ( last_element_of_list_b < k )
        return quick_select( arr, last_element_of_list_b+1, end, k );

    unsigned int first_element_of_list_b = partition_for_equal( arr, begin, last_element_of_list_b );

    if ( k < first_element_of_list_b )
        return quick_select( arr, begin, first_element_of_list_b-1, k );

    return find_the_lowest( arr, first_element_of_list_b, last_element_of_list_b );

}

int main()
{
    ios::sync_with_stdio( false );

    unsigned int country_count, questions_count, number;

    cin >> country_count;

    Country* arr = new Country[ country_count ];

    for ( unsigned int i=0 ; i<country_count ; i++ )
        cin >> arr[i].id >> arr[i].value;

    cin >> questions_count;

    for ( unsigned int i=0 ; i<questions_count ; i++ )
    {
        cin >> number;
        cout << quick_select( arr, 0, country_count-1, number-1 ) << endl;
    }

    return 0;
}