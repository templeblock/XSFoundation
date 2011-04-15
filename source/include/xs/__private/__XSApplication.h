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
 * @header      __XSApplication.h
 * @copyright   eosgarden 2011 - Jean-David Gadina <macmade@eosgarden.com>
 * @abstract    Private XSApplication class definitions
 */

#ifndef ___XS_APPLICATION_H_
#define ___XS_APPLICATION_H_
#pragma once

#include "../XSMacros.h"

XS_EXTERN_C_BEGIN

#include "XS.h"

/*!
 * @typdef      __XSApplication
 * @abastract   XSApplication class
 * @field       __class     Runtime class
 */
typedef struct __XSApplication_Struct
{
    XSRuntimeClass          __class;
    int                     argc;
    const char           ** argv;
    const char            * executable;
    XSApplicationArgument * args;
    XSUInteger              arg_count;
    XSUInteger              arg_alloc;
}
__XSApplication;

/*!
 * @function    __XSApplication_Initialize
 * @abstract    Runtime initialization
 * @result      void
 */
void __XSApplication_Initialize( void );

/*!
 * @function    __XSApplication_Construct
 * @abstract    Constructor
 * @param       object  A pointer to the object
 * @result      void
 */
void __XSApplication_Construct( void * object );
 
 /*!
 * @function    __XSApplication_Destruct
 * @abstract    Destructor
 * @param       object  A pointer to the object
 * @result      void
 */
void __XSApplication_Destruct( void * object );

/*!
 * @function    __XSApplication_ProcessArguments
 * @abstract    Processes the command line arguments
 * @param       app     The application object
 * @result      void
 */
void __XSApplication_ProcessArguments( __XSApplication * app );

XS_EXTERN_C_END

#endif /* ___XS_APPLICATION_H_ */
