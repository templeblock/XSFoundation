/*******************************************************************************
 * Copyright (c) 2010, Jean-David Gadina <macmade@eosgarden.com>
 * Distributed under the Boost Software License, Version 1.0.
 * 
 * Boost Software License - Version 1.0 - August 17th, 2003
 * 
 * Permission is hereby granted, free of charge, to any person or organization
 * obtaining a copy of the software and accompanying documentation covered by
 * this license (the "Software") to use, reproduce, display, distribute,
 * execute, and transmit the Software, and to prepare derivative works of the
 * Software, and to permit third-parties to whom the Software is furnished to
 * do so, all subject to the following:
 * 
 * The copyright notices in the Software and this entire statement, including
 * the above license grant, this restriction and the following disclaimer,
 * must be included in all copies of the Software, in whole or in part, and
 * all derivative works of the Software, unless such copies or derivative
 * works are solely in the form of machine-executable object code generated by
 * a source language processor.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
 * SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
 * FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 ******************************************************************************/

/* $Id */

/*!
 * @file        
 * @copyright   eosgarden 2011 - Jean-David Gadina <macmade@eosgarden.com>
 * @abstract    
 */

#include "XS.h"

static char __stdc_string_hex_chars[] =
{
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
    'A', 'B', 'C', 'D', 'E', 'F'
};

static void __xs_std_str_reverse( char s[] );
static void __xs_std_str_reverse( char s[] )
{
    int i;
    int j;
    char c;
    
    j = strlen( s ) - 1;
    
    for( i = 0; i < j; i++ )
    {
        c      = s[ i ];
        s[ i ] = s[ j ];
        s[ j ] = c;
        
        j--;
    }
}

void itoa( int n, char s[], int radix )
{
    unsigned int i;
    int          sign;
    
    if( radix > 16 )
    {
        radix = 16;
    }
    else if( radix < 2 )
    {
        radix = 10;
    }
    
    if( ( sign = n ) < 0 )
    {
        n = -n;
    }
    
    i = 0;
    
    do
    {
        s[ i++ ] = __stdc_string_hex_chars[ n % radix ];
    }
    while( ( n /= radix ) > 0 );
    
    if( sign < 0 )
    {
        s[ i++ ] = '-';
    }
    
    s[ i ] = '\0';
    
    __xs_std_str_reverse( s );
}

void utoa( unsigned int n, char s[], int radix )
{
    unsigned int i;
    
    if( radix > 16 )
    {
        radix = 16;
    }
    else if( radix < 2 )
    {
        radix = 10;
    }
    
    i = 0;
    
    do
    {
        s[ i++ ] = __stdc_string_hex_chars[ n % radix ];
    }
    while( ( n /= radix ) > 0 );
    
    s[ i ] = '\0';
    
    __xs_std_str_reverse( s );
}

char * strrstr( char *s1, char * s2 )
{
    char * ss1;
    char * sss1;
    char * sss2;

    if( *( s2 ) == '\0' )
    {
        return s1;
    }
    
    ss1 = s1 + strlen( s1 );
    
    while( ss1 != s1 )
    {
        --ss1;
        
        for( sss1 = ss1, sss2 = s2; ; )
        {
            if( *( sss1++ ) != *( sss2++ ) )
            {
                break;
            }
            else if ( * sss2 == '\0' )
            {
                return ss1;
            }
        }
    }
    
    return NULL;
}
