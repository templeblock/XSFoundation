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
 * @file        __XSThread.c
 * @copyright   eosgarden 2011 - Jean-David Gadina <macmade@eosgarden.com>
 * @abstract    ...
 */

#include "XS.h"
#include "__XSThread.h"

/*!
 * @var         __XSThreadClass
 * @abstract    Runtime class definition
 */
static const XSRuntimeClass __XSThreadClass =
{
    "XSThread",         /* Class name */
    NULL,               /* Constructor */
    NULL,               /* Destructor */
    NULL,               /* Object copy */
    NULL                /* Object description */
};

/*!
 * @var         __XSThreadTypeID
 * @abstract    Type ID for the runtine class
 */
static XSTypeID __XSThreadTypeID;

/*!
 * @function    __XSThread_Initialize
 * @abstract    Runtime initialization
 * @result      void
 */
void __XSThread_Initialize( void )
{
    __XSThreadTypeID = XSRuntime_RegisterClass( &__XSThreadClass );
}

/*!
 * @function    __XSThread_Alloc
 * @abstract    Object allocator
 * @result      A pointer to the allocated object
 */
XSThread * __XSThread_Alloc( void )
{
    return ( XSThread * )XSRuntime_CreateInstance( __XSThreadTypeID, sizeof( XSThread ) );
}

/*!
 * @function    __XSThread_Run
 * @abstract    Runs a thread
 * param        A pointer to the thread object (XSThread)
 * @result      Always NULL
 */
void * __XSThread_Run( void * thread )
{
    pthread_t  tid;
    XSThread * _thread;
    
    #ifdef __MACH__
    mach_port_t mid;
    #endif
    
    _thread = ( XSThread * )thread;
    tid     = pthread_self();
    
    #ifdef __MACH__
    mid          = pthread_mach_thread_np( tid );
    _thread->tid = mid;
    #else
    _thread->tid = tid;
    #endif
    
    _thread->func( ( XSThreadRef )thread, _thread->arg );
    
    pthread_exit( NULL );
}