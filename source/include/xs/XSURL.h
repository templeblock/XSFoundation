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
 * @header      XSURL.h
 * @copyright   eosgarden 2011 - Jean-David Gadina <macmade@eosgarden.com>
 * @abstract    XSURL class functions
 */

#ifndef _XS_URL_H_
#define _XS_URL_H_
#pragma once

#include "XSMacros.h"

XS_EXTERN_C_BEGIN

/*!
 * @typedef     XSTimer
 * @abstract    Opaque type for the XSTree objects
 */
typedef struct __XSURL_Struct * XSURL;

/*!
 * @function    XSTimer_Alloc
 * @abstract    Object allocator
 * @result      The allocated object
 */
XSStatic XSObject XSURL_Alloc( void );

XSObject XSURL_Init( XSObject xsThis );

XSObject XSURL_InitWithString( XSObject xsThis, XSString str );

XSObject XSURL_InitWithCString( XSObject xsThis, char * str );

XSAutoreleased XSString XSURL_GetURL( XSObject xsThis );

void XSURL_SetScheme( XSObject xsThis, XSString scheme );

void XSURL_SetDomain( XSObject xsThis, XSString domain );

void XSURL_SetPort( XSObject xsThis, XSUInteger port );

void XSURL_SetPath( XSObject xsThis, XSString path );

void XSURL_SetQuery( XSObject xsThis, XSString query );

void XSURL_SetFragment( XSObject xsThis, XSString fragment );

XSAutoreleased XSString XSURL_GetScheme( XSObject xsThis );

XSAutoreleased XSString XSURL_GetDomain( XSObject xsThis );

XSUInteger XSURL_GetPort( XSObject xsThis );

XSAutoreleased XSString XSURL_GetPath( XSObject xsThis );

XSAutoreleased XSString XSURL_GetQuery( XSObject xsThis );

XSAutoreleased XSString XSURL_GetFragment( XSObject xsThis );

XS_EXTERN_C_END

#endif /* _XS_URL_H_ */
