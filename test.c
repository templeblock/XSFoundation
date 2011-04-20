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
 * @header      test.c
 * @copyright   eosgarden 2011 - Jean-David Gadina <macmade@eosgarden.com>
 * @abstract    ...
 */


#include <stdlib.h>
#include <stdio.h>
#include "XS.h"

void thread_test( XSThread thread, XSObject arg );
void thread_test( XSThread thread, XSObject arg )
{
    XSString str;
    
    str = ( XSString )arg;
    
    XSLog( "Log message from thread #%lu: $@", XSThread_GetID( thread ), str );
}

void timer_test( XSTimer timer );
void timer_test( XSTimer timer )
{
    static XSUInteger i = 0;
    
    XSLog( "Timer called: %i", ++i );
    
    if( i == 5 )
    {
        XSTimer_Invalidate( timer );
    }
}

void notification_test( XSNotification notification );
void notification_test( XSNotification notification )
{
    XSLog
    (
        "Received notification \"%s\" with object: $@",
        XSString_CString( XSNotification_GetName( notification ) ),
        XSNotification_GetObject( notification )
    );
}

XSMain( argc, argv )
{
    unsigned int  i;
    XSInteger     arg_int;
    XSUInteger    arg_uint;
    XSString      arg_str;
    XSFloat       arg_float;
    char       ** test;
    XSApplication app;
    XSString      str1;
    XSString      str2;
    XSString      str3;
    XSArray       arr;
    XSTimer       timer;
    XSData        data;
    XSDictionary  dict;
    XSNumber      num;
    XSURL         url;
    XSHost        host;
    XSURLRequest  request;
    
    app  = XSApplication_Start( argc, ( const char ** )argv );
    
    XSApplication_RegisterArgument( app, "--test",    XSApplicationArgumentTypeFlag,    "A test flag" );
    XSApplication_RegisterArgument( app, "--int",     XSApplicationArgumentTypeInteger, "A test integer" );
    XSApplication_RegisterArgument( app, "--string",  XSApplicationArgumentTypeString,  "A test string" );
    XSApplication_RegisterArgument( app, "--float",   XSApplicationArgumentTypeFloat,   "A test float" );
    XSApplication_RegisterArgument( app, "--uint",    XSApplicationArgumentTypeUnsignedInteger, NULL );
    
    XSApplication_PrintHelp( app, "A test application for the XSFoundation" );
    
    if( XSApplication_GetFlag( app, "--test" ) )
    {
        XSLog( "Has flag argument: test" );
    }
    
    if( ( arg_int = XSApplication_GetInteger( app, "--int" ) ) )
    {
        XSLog( "Has int argument: %i", arg_int );
    }
    
    if( ( arg_uint = XSApplication_GetUnsignedInteger( app, "--uint" ) ) )
    {
        XSLog( "Has uint argument: %u", arg_uint );
    }
    
    if( ( arg_str = XSApplication_GetString( app, "--string" ) ) )
    {
        XSLog( "Has string argument: $@", arg_str );
    }
    
    if( ( arg_float = XSApplication_GetFloat( app, "--float" ) ) )
    {
        XSLog( "Has float argument: %f", arg_float );
    }
    
    test = XSAutoAlloc( 5 * sizeof( char * ) );
    
    for( i = 0; i < 5; i++ )
    {
        test[ i ] = XSAutoAlloc( 2 );
    }
    
    str1    = XSSTR( "hello, world" );
    str2    = XSString_SubstringFromIndex( str1, 5 );
    str3    = XSCopy( str2 );
    arr     = XSArray_InitWithValues( XSArray_Alloc(), str1, str2, str3, NULL );
    data    = XSData_InitWithBytes( XSData_Alloc(), ( UInt8 * )"hello, world", 12 );
    dict    = XSDictionary_InitWithKeysAndValues( XSDictionary_Alloc(), XSSTR( "test-1" ), str1, XSSTR( "test-2" ), str2, NULL );
    num     = XSNumber_InitWithShort( XSNumber_Alloc(), 0x0303 );
    url     = XSURL_InitWithCString( XSURL_Alloc(), "http://www.eosgarden.com:80/en/contact/?test=1#test" );
    host    = XSHost_InitWithURL( XSHost_Alloc(), url );
    request = XSURLRequest_InitWithURL( XSURLRequest_Alloc(), url );
    
    XSLog( "Memory hash: %s", XSHash( test ) );
    XSLog( "Object hash: %s", XSHash( str1 ) );
    XSLog( "%s%s%s", XSString_CString( str1 ), XSString_CString( str2 ), XSString_CString( str3 ) );
    XSLog( "hello, universe: %i $@ %i $@ %i", 42, str1, 43, app, 44 );
    XSLog( "Array value 0: $@", XSArray_ValueAtIndex( arr, 0 ) );
    XSLog( "$@", XSString_StringByAppendingString( str1, str2 ) );
    XSLog( "$@", arr );
    XSLog( "$@", XSAutorelease( XSRuntime_CreateInstanceOfClassWithName( "XSString" ) ) );
    XSString_AppendCString( str1, " (and universe)" );
    XSLog( "$@", str1 );
    XSLog( "MD5 Hash: $@", XSString_MD5Hash( str1 ) );
    XSLog( "$@", data );
    XSLog( "$@", dict );
    XSLog( "$@", num );
    XSLog( "0x%02x", XSNumber_GetChar( num ) );
    XSLog( "$@", url );
    XSLog( "$@", host );
    
    XSNotificationCenter_AddObserver( XSNotificationCenter_DefaultCenter(), ( XSObject )str1, XSSTR( "TestNotification" ), notification_test );
    XSNotificationCenter_PostNotification( XSNotificationCenter_DefaultCenter(), ( XSObject )str1, XSSTR( "TestNotification" ) );
    
    XSThread_Detach( thread_test, NULL );
    XSThread_Detach( thread_test, str1 );
    
    timer = XSTimer_Init( XSTimer_Alloc(), timer_test, 100 );
    
    XSTimer_RunOnce( timer );
    XSTimer_RunAndRepeat( timer );
    
    XSURLRequest_Start( request );
    
    XSRelease( timer );
    XSRelease( arr );
    XSRelease( str3 );
    XSRelease( data );
    XSRelease( dict );
    XSRelease( num );
    XSRelease( url );
    XSRelease( host );
    XSRelease( request );
    
    return EXIT_SUCCESS;
}
