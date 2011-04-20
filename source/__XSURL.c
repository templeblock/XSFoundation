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
 * @file        __XSURL.c
 * @copyright   eosgarden 2011 - Jean-David Gadina <macmade@eosgarden.com>
 * @abstract    Private implementation for the XSURL class
 */

#include "XS.h"
#include "__XSURL.h"

/*!
 * @var         __XSURLClass
 * @abstract    Runtime class definition
 */
static const XSClassInfos __XSURLClass =
{
    "XSURL",                /* Class name */
    sizeof( __XSURL ),      /* Object size */
    NULL,                   /* Constructor */
    __XSURL_Destruct,       /* Destructor */
    XSURL_Init,             /* Default initializer */
    NULL,                   /* Object copy */
    __XSURL_ToString,       /* Object description */
    __XSURL_Equals          /* Object comparison */
};

/*!
 * @var         __XSURLClassID
 * @abstract    Type ID for the runtine class
 */
XSClassID __XSURLClassID;

void __XSURL_Initialize( void )
{
    __XSURLClassID = XSRuntime_RegisterClass( &__XSURLClass );
}

void __XSURL_Destruct( XSObject object )
{
    __XSURL * url;
    
    url = ( __XSURL * )object;
    
    XSRelease( url->scheme );
    XSRelease( url->domain );
    XSRelease( url->path );
    XSRelease( url->query );
    XSRelease( url->fragment );
}

XSString __XSURL_ToString( XSObject object )
{
    return XSURL_GetURL( object );
}

BOOL __XSURL_Equals( XSObject object1, XSObject object2 )
{
    if( XSString_IsEqualToString( XSURL_GetURL( object1 ), XSURL_GetURL( object2 ) ) )
    {
        return YES;
    }
    
    return NO;
}