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
 * @file        __XSString.c
 * @copyright   eosgarden 2011 - Jean-David Gadina <macmade@eosgarden.com>
 * @abstract    ...
 */

#include "XS.h"
#include "__XSString.h"

/*!
 * @var         __XSStringClass
 * @abstract    Runtime class definition
 */
static const XSRuntimeClass __XSStringClass =
{
    "XSString",             /* Class name */
    NULL,                   /* Constructor */
    __XSString_Dealloc,     /* Destructor */
    __XSString_Copy,        /* Object copy */
    __XSString_Description  /* Object description */
};

/*!
 * @var         __XSStringTypeID
 * @abstract    Type ID for the runtine class
 */
static XSTypeID __XSStringTypeID;

/*!
 * @function    __XSString_Initialize
 * @abstract    Runtime initialization
 * @result      void
 */
void __XSString_Initialize( void )
{
    __XSStringTypeID = XSRuntime_RegisterClass( &__XSStringClass );
}

/*!
 * @function    __XSString_Alloc
 * @abstract    Object allocator
 * @result      A pointer to the allocated object
 */
XSString * __XSString_Alloc( void )
{
    return ( XSString * )XSRuntime_CreateInstance( __XSStringTypeID, sizeof( XSString ) );
}

/*!
 * @function    __XSString_Dealloc
 * @abstract    Destructor
 * @param       object  A pointer to the object
 * @result      void
 */
void __XSString_Dealloc( void * object )
{
    XSString * str;
    
    str = ( XSString * )object;
    
    XSRelease( str->str );
}

/*!
 * @function    __XSString_Copy
 * @abstract    Object copy
 * @param       object  A pointer to the object
 * @result      void
 */
void __XSString_Copy( void * source, void * destination )
{
    XSString * str;
    
    ( void )source;
    
    str = ( XSString * )destination;
    
    XSRetain( str->str );
}

/*!
 * @function    __XSString_Description
 * @abstract    Object description
 * @param       object  A pointer to the object
 * @result      The object's description
 */
XSStringRef __XSString_Description( void * object )
{
    return ( XSStringRef )object;
}
