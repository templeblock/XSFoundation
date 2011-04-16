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
 * @abstract    Implementation of the runtime functions
 */

#include "XS.h"
#include "__XSMemory.h"
#include "__XSMemoryDebug.h"

/*!
 * define       __XS_RUNTIME_CLASS_TABLE_SIZE
 * @abstract    Default allocation size for the runtime class table
 */
#define __XS_RUNTIME_CLASS_TABLE_SIZE   1024

/*!
 * define       __XS_RUNTINE_INIT_CHECK
 * @abstract    Checks if the runtime has been initialized
 * @description This macro will produce a fatal error if the runtime has not been initialized.
 */
#define __XS_RUNTINE_INIT_CHECK         if( __inited == NO ) { XSFatalError( "Error: the runtime has not been initialized\n" ) }

/*!
 * @var         __inited
 * @abstract    Whether the XSFoundation runtime has been initialized
 */
static BOOL __inited = NO;

/*!
 * @var         __class_table
 * @abstract    The runtime class table
 */
static XSClassInfos ** __class_table;

/*!
 * @var         __class_size
 * @abstract    The allocated size of the runtime class table
 */
static size_t __class_size;

/*!
 * @var         __class_count
 * @abstract    The number of registered classes in the runtime class table
 */
static size_t __class_count;

/* Prototypes for the initialization of the core runtime classes */
void __XSMemoryObject_Initialize( void );
void __XSApplication_Initialize( void );
void __XSApplicationArgument_Initialize( void );
void __XSArray_Initialize( void );
void __XSBag_Initialize( void );
void __XSBool_Initialize( void );
void __XSColor_Initialize( void );
void __XSData_Initialize( void );
void __XSDictionary_Initialize( void );
void __XSError_Initialize( void );
void __XSFile_Initialize( void );
void __XSLock_Initialize( void );
void __XSNull_Initialize( void );
void __XSNotification_Initialize( void );
void __XSNotificationCenter_Initialize( void );
void __XSNumber_Initialize( void );
void __XSSet_Initialize( void );
void __XSString_Initialize( void );
void __XSThread_Initialize( void );
void __XSTimer_Initialize( void );

void XSRuntime_Initialize( void )
{
    __inited = YES;
    
    atexit( __XSMemoryDebug_Finalize );
    atexit( XSApplication_Exit );
    atexit( XSRuntime_Finalize );
    
    __XSMemoryDebug_InstallSignalHandlers();
    
    __XSAutoreleasePool_Initialize();
    __XSArray_Initialize();
    __XSApplication_Initialize();
    __XSApplicationArgument_Initialize();
    __XSBag_Initialize();
    __XSBool_Initialize();
    __XSColor_Initialize();
    __XSData_Initialize();
    __XSDictionary_Initialize();
    __XSError_Initialize();
    __XSFile_Initialize();
    __XSLock_Initialize();
    __XSNotification_Initialize();
    __XSNotificationCenter_Initialize();
    __XSNull_Initialize();
    __XSNumber_Initialize();
    __XSSet_Initialize();
    __XSString_Initialize();
    __XSThread_Initialize();
    __XSTimer_Initialize();
}

void XSRuntime_Finalize( void )
{
    __inited = NO;
    
    XSRelease( __class_table );
}

XSClassID XSRuntime_RegisterClass( const XSClassInfos * const cls )
{
    __XS_RUNTINE_INIT_CHECK
    
    if( __class_size == 0 )
    {
        if( NULL == ( __class_table = ( XSClassInfos ** )XSAlloc( sizeof( XSClassInfos * ) * __XS_RUNTIME_CLASS_TABLE_SIZE ) ) )
        {
            fprintf( stderr, "Error: unable to allocate the runtime class table!\n" );
            exit( EXIT_FAILURE );
        }
        
        __class_size += __XS_RUNTIME_CLASS_TABLE_SIZE;
    }
    
    if( __class_count == __class_size )
    {
        if( NULL == ( __class_table = ( XSClassInfos ** )XSRealloc( __class_table, sizeof( XSClassInfos * ) * ( __XS_RUNTIME_CLASS_TABLE_SIZE + __class_size ) ) ) )
        {
            fprintf( stderr, "Error: unable to re-allocate the runtime class table!\n" );
            exit( EXIT_FAILURE );
        }
        
        __class_size += __XS_RUNTIME_CLASS_TABLE_SIZE;
    }
    
    __class_table[ __class_count ] = ( XSClassInfos * )cls;
    
    return ++__class_count;
}

XSObject XSRuntime_CreateInstance( XSClassID typeID )
{
    XSRuntimeClass * b;
    XSClassInfos   * cls;
    size_t           size;
    XSObject         o;
    
    __XS_RUNTINE_INIT_CHECK
    
    if( typeID > __class_count )
    {
        return NULL;
    }
    
    cls           = __class_table[ typeID - 1 ];
    size          = sizeof( cls ) + cls->instanceSize;
    o             = XSAlloc( size, typeID );
    b             = ( XSRuntimeClass * )o;
    b->classInfos = cls;
    
    return o;
}

XSObject XSRuntime_CreateInstanceOfClass( const XSClassInfos * const cls )
{
    XSClassID classID;
    
    classID = XSRuntime_GetClassIDForClass( ( XSClass )cls );
    
    if( classID == 0 )
    {
        return NULL;
    }
    
    return XSRuntime_CreateInstance( classID );
}

XSObject XSRuntime_CreateInstanceOfClassWithName( const char * name )
{
    size_t         i;
    XSObject       o;
    XSClassInfos * cls;
    
    for( i = 0; i < __class_count; i++ )
    {
        cls = __class_table[ i ];
        
        if( strcmp( cls->className, name ) == 0 )
        {
            o = XSRuntime_CreateInstance( i + 1 );
            
            if( cls->init != NULL )
            {
                return cls->init( o );
            }
        }
    }
    
    return NULL;
}

const char * XSRuntime_ObjectDescription( void * ptr )
{
    XSString           description;
    XSString           str;
    __XSMemoryObject * o;
    XSClassInfos     * cls;
    
    if( ptr == NULL )
    {
        return "<XSObject: nil>";
    }
    
    if( XSRuntime_IsInstance( ptr ) == NO )
    {
        return "<XSNotAnObject>";
    }
    
    o   = __XSMemory_GetMemoryObject( ptr );
    cls = ( XSClassInfos * )XSRuntime_GetClassForClassID( o->classID );
    str = XSAutorelease( XSString_Init( XSString_Alloc() ) );
    
    XSString_AppendFormat( str, ( char * )"<%s: %p>", cls->className, ptr );
    
    if( cls->toString != NULL )
    {
        description = cls->toString( ptr );
        XSString_AppendFormat( str, ( char * )" [ %s ]", XSString_CString( description ) );
    }
    
    return XSString_CString( str );
}

BOOL XSRuntime_IsInstance( void * ptr )
{
    __XSMemoryObject * o;
    
    o = __XSMemory_GetMemoryObject( ptr );
    
    if( o->classID > 0 && XSRuntime_GetClassForClassID( o->classID ) != NULL )
    {
        return YES;
    }
    
    return NO;
}

XSClass XSRuntime_GetClassForClassID( XSClassID classID )
{
    if( classID > __class_count )
    {
        return NULL;
    }
    
    return ( XSClass )__class_table[ classID - 1 ];
}

XSClassID XSRuntime_GetClassIDForClass( XSClass cls )
{
    XSUInteger       i;
    XSClassInfos * _cls;
    
    _cls = ( XSClassInfos * )cls;
    
    for( i = 0; i < __class_count; i++ )
    {
        if( __class_table[ i ] == _cls )
        {
            return i + 1;
        }
    }
    
    return 0;
}

XSClass XSRuntime_GetClassForObject( XSObject object )
{
    if( XSRuntime_IsInstance( object ) == NO )
    {
        return NULL;
    }
    
    return ( ( XSRuntimeClass * )object )->classInfos;
}

XSClassID XSRuntime_GetTypeIDForObject( XSObject object )
{
    if( XSRuntime_IsInstance( object ) == NO )
    {
        return 0;
    }
    
    return XSRuntime_GetClassIDForClass( XSRuntime_GetClassForObject( object ) );
}

const char * XSRuntime_GetClassNameForClassID( XSClassID classID )
{
    if( classID == 0 || classID > __class_count )
    {
        return "N/A";
    }
    
    return __class_table[ classID - 1 ]->className;
}

const char * XSRuntime_GetClassNameForClass( XSClass cls )
{
    XSClassInfos * _cls;
    
    _cls = ( XSClassInfos * )cls;
    
    return _cls->className;
}

const char * XSRuntime_GetClassNameForObject( XSObject object )
{
    if( XSRuntime_IsInstance( object ) == NO )
    {
        return NULL;
    }
    
    return ( ( XSRuntimeClass * )object )->classInfos->className;
}

BOOL XSRuntime_IsInstanceOfClass( XSObject object, XSClass cls )
{
    if( XSRuntime_IsInstance( object ) == NO )
    {
        return NO;
    }
    
    if( ( ( XSRuntimeClass * )object )->classInfos == cls )
    {
        return YES;
    }
    
    return NO;
}

BOOL XSRuntime_IsInstanceOfClassName( XSObject object, const char * name )
{
    if( XSRuntime_IsInstance( object ) == NO )
    {
        return NO;
    }
    
    if( strcmp( ( ( XSRuntimeClass * )object )->classInfos->className, name ) == 0 )
    {
        return YES;
    }
    
    return NO;
}