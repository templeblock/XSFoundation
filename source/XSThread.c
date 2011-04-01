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
 * @header      XSThread.c
 * @copyright   eosgarden 2011 - Jean-David Gadina <macmade@eosgarden.com>
 * @abstract    ...
 */

#include "XS.h"
#include "__XSThread.h"

/* Prototypes for the private functions */
extern void * __XSThread_Run( void * thread );

/*!
 * @function    XSThread_Detach
 * @abstract    Creates and detaches a thread
 * @param       func    A pointer to the function to run on the thread
 * @param       arg     Argument to pass to the thread function
 * @result      The XSThread instance
 */
XSThreadRef XSThread_Detach( void ( * func )( XSThreadRef thread, void * arg ), void * arg )
{
    pthread_t   t;
    XSUInteger  tid;
    XSThread  * thread;
    
    thread = __XSThread_Alloc();
    thread->func = func;
    thread->arg  = arg;
    
    tid = pthread_create( &t, NULL, __XSThread_Run, ( void * )thread );
    
    if( tid )
    {
        XSRelease( thread );
        
        return NULL;
    }
    
    return ( XSThreadRef )thread;
}

/*!
 * @function    XSThread_GetID
 * @abstract    Gets the thread ID
 * @param       thread  The thread object
 * @result      The thread ID
 */
XSUInteger XSThread_GetID( XSThreadRef thread )
{
    return ( ( XSThread * )thread )->tid;
}