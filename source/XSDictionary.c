/*******************************************************************************
 * Copyright (c) 2011, Jean-David Gadina <macmade@eosgarden.com>
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
 
/* $Id$ */

/*!
 * @header      XSDictionary.c
 * @copyright   eosgarden 2011 - Jean-David Gadina <macmade@eosgarden.com>
 * @abstract    ...
 */

#include "XS.h"
#include "__XSDictionary.h"

extern XSClassID __XSDictionaryClassID;

XSStatic XSDictionary XSDictionary_Alloc( void )
{
    return ( XSDictionary )XSRuntime_CreateInstance( __XSDictionaryClassID );
}

XSDictionary XSDictionary_Init( XSDictionary xsThis )
{
    return XSDictionary_InitWithCapacity( xsThis, ( XSUInteger )XSDICTIONARY_DEFAULT_CAPACITY );
}

XSDictionary XSDictionary_InitWithCapacity( XSDictionary xsThis, XSUInteger capacity )
{
    void          ** store;
    XSString       * keys;
    __XSDictionary * dict;
    
    if( NULL == ( store = ( void ** )XSAlloc( capacity * sizeof( void * ) ) ) )
    {
        return NULL;
    }
    
    if( NULL == ( keys = ( XSString * )XSAlloc( capacity * sizeof( XSString ) ) ) )
    {
        XSRelease( store );
        return NULL;
    }
    
    dict           = ( __XSDictionary * )xsThis;
    dict->values   = store;
    dict->keys     = keys;
    dict->capacity = capacity;
    dict->count    = 0;
    
    return ( XSDictionary )dict;
}

XSDictionary XSDictionary_InitWithKeysAndValues( XSDictionary xsThis, XSString key1, void * value1, ... )
{
    XSString key;
    void   * value;
    va_list  args;
    
    if( value1 == NULL || key1 == NULL )
    {
        return xsThis;
    }
    
    XSDictionary_Init( xsThis );
    XSDictionary_SetValueForKey( xsThis, value1, key1 );
    va_start( args, value1 );
    
    while( NULL != ( key = va_arg( args, XSString ) ) )
    {
        value = va_arg( args, void * );
        
        if( value == NULL )
        {
            return xsThis;
        }
        
        XSDictionary_SetValueForKey( xsThis, value, key );
    }
    
    va_end( args );
    
    return xsThis;
}

XSUInteger XSDictionary_Count( XSDictionary xsThis )
{
    return ( ( __XSDictionary * )xsThis )->count;
}

XSAutoreleased XSArray XSDictionary_Keys( XSDictionary xsThis )
{
    __XSDictionary * _dict;
    XSArray          array;
    XSUInteger       i;
    
    _dict = ( __XSDictionary * )xsThis;
    array = XSArray_InitWithCapacity( XSArray_Alloc(), _dict->count );
    
    for( i = 0; i < _dict->count; i++ )
    {
        XSArray_AppendValue( array, _dict->keys[ i ] );
    }
    
    return XSAutorelease( array );
}

XSAutoreleased XSArray XSDictionary_Values( XSDictionary xsThis )
{
    __XSDictionary * _dict;
    XSArray          array;
    XSUInteger       i;
    
    _dict = ( __XSDictionary * )xsThis;
    array = XSArray_InitWithCapacity( XSArray_Alloc(), _dict->count );
    
    for( i = 0; i < _dict->count; i++ )
    {
        XSArray_AppendValue( array, _dict->values[ i ] );
    }
    
    return XSAutorelease( array );
}

void * XSDictionary_ValueForKey( XSDictionary xsThis, XSString key )
{
    __XSDictionary * _dict;
    XSUInteger       i;
    
    _dict = ( __XSDictionary * )xsThis;
    
    for( i = 0; i < _dict->count; i++ )
    {
        if( XSString_IsEqualToString( key, _dict->keys[ i ] ) )
        {
            return _dict->values[ i ];
        }
    }
    
    return NULL;
}

void XSDictionary_SetValueForKey( XSDictionary xsThis, void * value, XSString key )
{
    ( void )xsThis;
    ( void )value;
    ( void )key;
}

void * XSDictionary_RemoveValueForKey( XSDictionary xsThis, void * value, XSString key )
{
    ( void )xsThis;
    ( void )value;
    ( void )key;
    
    return NULL;
}

BOOL XSDictionary_ContainsValue( XSDictionary xsThis, void * value )
{
    ( void )xsThis;
    ( void )value;
    
    return NO;
}
