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
 * @header      XSRuntime.c
 * @copyright   eosgarden 2011 - Jean-David Gadina <macmade@eosgarden.com>
 * @abstract    ...
 */

#include "XS.h"

#define __XS_RUNTIME_CLASS_TABLE_SIZE   1024

#define __XS_RUNTINE_INIT_CHECK         if( __inited == NO ) { fprintf( stderr, "Error: the runtime has not been initialized\n" ); exit( EXIT_FAILURE ); }

static BOOL              __inited = NO;
static XSRuntimeClass ** __class_table;
static size_t            __class_size;
static size_t            __class_count;

void __XSMemoryObject_Initialize( void );
void __XSAutoreleasePool_Initialize( void );
void __XSFile_Initialize( void );
void __XSString_Initialize( void );

void XSRuntime_Initialize( void )
{
    __inited = YES;
    
    __XSAutoreleasePool_Initialize();
    __XSFile_Initialize();
    __XSString_Initialize();
}

XSTypeID XSRuntime_RegisterClass( const XSRuntimeClass * const cls )
{
    __XS_RUNTINE_INIT_CHECK
    
    if( __class_size == 0 )
    {
        if( NULL == ( __class_table = ( XSRuntimeClass ** )calloc( sizeof( XSRuntimeClass * ), __XS_RUNTIME_CLASS_TABLE_SIZE ) ) )
        {
            fprintf( stderr, "Error: unable to allocate the runtime class table!\n" );
            exit( EXIT_FAILURE );
        }
        
        __class_size += __XS_RUNTIME_CLASS_TABLE_SIZE;
    }
    
    if( __class_count == __class_size )
    {
        if( NULL == ( __class_table = ( XSRuntimeClass ** )realloc( __class_table, sizeof( XSRuntimeClass * ) * ( __XS_RUNTIME_CLASS_TABLE_SIZE + __class_size ) ) ) )
        {
            fprintf( stderr, "Error: unable to re-allocate the runtime class table!\n" );
            exit( EXIT_FAILURE );
        }
        
        __class_size += __XS_RUNTIME_CLASS_TABLE_SIZE;
    }
    
    __class_table[ __class_count ] = ( XSRuntimeClass * )cls;
    
    return ++__class_count;
}

XSTypeRef XSRuntime_CreateInstance( XSTypeID typeID, size_t extraBytes )
{
    XSRuntimeBase  * b;
    XSRuntimeClass * cls;
    size_t           size;
    XSTypeRef      * o;
    
    __XS_RUNTINE_INIT_CHECK
    
    if( typeID > __class_count )
    {
        return NULL;
    }
    
    cls    = __class_table[ typeID - 1 ];
    size   = sizeof( cls ) + extraBytes;
    o      = XSAlloc( size, typeID );
    b      = ( XSRuntimeBase * )o;
    b->isa = cls;
    
    return o;
}

const XSRuntimeClass const * XSRuntime_GetClassForTypeID( XSTypeID typeID )
{
    if( typeID > __class_count )
    {
        return NULL;
    }
    
    return ( const XSRuntimeClass const * )__class_table[ typeID - 1 ];
}
