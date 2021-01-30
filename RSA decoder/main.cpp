#include <iostream>

using namespace std;

struct Equation
{
    long long x, y, r;

    Equation( long long x, long long y, long long r ) : x( x ), y( y ), r( r ) {}

    void subb( Equation & eq, long long quotient )
    {
        x -= eq.x * quotient;
        y -= eq.y * quotient;
        r -= eq.r * quotient;
    }
};

long long reverse_modulo ( long long a, long long b  )
{
    Equation eq1( 1, 0, a ), eq2( 0, 1, b );
    long long quotient;

    while ( eq1.r > 0 )
    {
        if ( eq1.r < eq2.r )
            swap( eq1, eq2 );

        quotient = eq1.r / eq2.r;
        eq1.subb( eq2, quotient );
    }

    if ( eq2.x > 0 )
        return eq2.x;

    return eq2.x + b;
}

unsigned long long modulo_from_square ( unsigned long long a, long long index, long long modulo )
{
    unsigned long long result = 1;

    while ( index > 0 )
    {
        if ( index %2 == 1 )
            result = result * a % modulo;

        a = a * a % modulo;
        index /= 2;
    }

    return result;
}

int main()
{
    ios::sync_with_stdio( false );

    long long public_key, n, fi, private_key, p, q;
    unsigned long long msg;
    unsigned int sets_count;

    cin >> sets_count;

    for ( unsigned int i=0 ; i<sets_count ; i++ )
    {
        cin >> p >> q >> public_key >> msg;

        n = p * q;
        fi = ( p - 1 ) * ( q - 1 );
        private_key = reverse_modulo( public_key, fi );

        cout << modulo_from_square( msg, private_key, n ) << '\n';

    }

    return 0;
}