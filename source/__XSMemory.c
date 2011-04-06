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
 * @file        __XSMemory.c
 * @copyright   eosgarden 2011 - Jean-David Gadina <macmade@eosgarden.com>
 * @abstract    ...
 */

#include "XS.h"
#include "__XSMemory.h"

/*!
 * @var         __xsmemory_ar_pools
 * @abstract    An array with the auto-release pool objects
 */
XSAutoreleasePool * __xsmemory_ar_pools[ XS_MEMORY_MAX_AR_POOLS ];

/*!
 * @var         __xsmemory_ar_pools_num
 * @abstract    The number of active auto-release pool objects
 */
XSUInteger          __xsmemory_ar_pools_num;

/*!
 * @var         __XSAutoreleasePoolClass
 * @abstract    Runtime class definition
 */
static const XSRuntimeClass __XSAutoreleasePoolClass =
{
    "XSAutoreleasePool",            /* Class name */
    sizeof( XSAutoreleasePool ),    /* Object size */
    NULL,                           /* Constructor */
    __XSAutoreleasePool_Dealloc,    /* Destructor */
    NULL,                           /* Object copy */
    NULL                            /* Object description */
};

/*!
 * @var         __XSAutoreleasePoolTypeID
 * @abstract    Type ID for the runtine class
 */
static XSTypeID __XSAutoreleasePoolTypeID;

/*!
 * @function    __XSAutoreleasePool_Initialize
 * @abstract    Runtime initialization
 * @result      void
 */
void __XSAutoreleasePool_Initialize( void )
{
    __XSAutoreleasePoolTypeID = XSRuntime_RegisterClass( &__XSAutoreleasePoolClass );
}

/*!
 * @function    __XSAutoreleasePool_Alloc
 * @abstract    Object allocator
 * @result      A pointer to the allocated object
 */
XSAutoreleasePool * __XSAutoreleasePool_Alloc( void )
{
    return ( XSAutoreleasePool * )XSRuntime_CreateInstance( __XSAutoreleasePoolTypeID );
}

/*!
 * @function    __XSAutoreleasePool_Dealloc
 * @abstract    Destructor
 * @abstract    A pointer to the object to be destructed
 * @param       object  The object that will be destructed
 * @result      void
 */
void __XSAutoreleasePool_Dealloc( void * object )
{
    __XSMemory_AutoreleasePoolDrain( ( XSAutoreleasePool * )object );
    __xsmemory_ar_pools_num--;
}

/*!
 * @function    __XSMemory_GetCurrentAutoreleasePool
 * @abstract    Gets a pointer to a memory records object from a pointer returned by the XS allocation functions.
 * @result      The auto-release pool object or NULL if no aut-release pool were created
 */
XSAutoreleasePool * __XSMemory_GetCurrentAutoreleasePool( void )
{
    if( __xsmemory_ar_pools_num == 0 )
    {
        return NULL;
    }
    
    return __xsmemory_ar_pools[ __xsmemory_ar_pools_num - 1 ];
}

/*!
 * @function    __XSMemory_AutoreleasePoolDrain
 * @abstract    Releases all objects placed in the auto-release pool.
 * @result      void
 */
void __XSMemory_AutoreleasePoolDrain( XSAutoreleasePool * ap )
{
    size_t i;
    
    for( i = 0; i < ap->num_objects; i++ )
    {
        XSRelease( ap->objects[ i ] );
    }
    
    ap->num_objects = 0;
}

/*!
 * @function    __XSMemory_GetMemoryObject
 * @abstract    Gets the current (top-level) auto-release pool
 * @result      A pointer to the memory record object
 */
__XSMemoryObject * __XSMemory_GetMemoryObject( void * ptr )
{
    __XSMemoryObject * o;
    char             * c;
    
    c  = ( char * )ptr;
    c -= sizeof( __XSMemoryObject );
    o  = ( __XSMemoryObject * )c;
    
    return o;
}
