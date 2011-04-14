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
 * @header      XSSet.h
 * @copyright   eosgarden 2011 - Jean-David Gadina <macmade@eosgarden.com>
 * @abstract    ...
 */

#ifndef _XS_SET_H_
#define _XS_SET_H_
#pragma once

#include "XSMacros.h"

XS_EXTERN_C_BEGIN

/*!
 * @typedef     XSSet
 * @abstract    Opaque type for the XSSet objects
 */
typedef struct XSSet * XSSet;

/*!
 * @function    XSSet_Alloc
 * @abstract    Object allocator
 * @result      The allocated object
 */
XSStatic XSSet XSSet_Alloc( void );

XSSet XSSet_Init( XSSet xsThis );

XSSet XSSet_InitWithCapacity( XSSet xsThis, XSUInteger capacity );

XSSet XSSet_InitWithValues( XSSet xsThis, void * value1, ... );

XSUInteger XSSet_Count( XSSet xsThis );

BOOL XSSet_ContainsValue( XSSet xsThis, void * value );

void XSSet_AddValue( XSSet xsThis, void * value );

void XSSet_RemoveValue( XSSet xsThis, void * value );

void XSSet_ReplaceValue( XSSet xsThis, void * valueOld, void * valueNew );

/*!
 * @function    XSSet_Index
 * @abstract    Gets the current set index
 * @param       xsThis  The set object
 * @result      The current set index
 */
XSUInteger XSSet_Index( XSSet xsThis );

/*!
 * @function    XSSet_Current
 * @abstract    Gets the current set value
 * @param       xsThis  The set object
 * @result      The current set value
 */
void * XSSet_Current( XSSet xsThis );

/*!
 * @function    XSSet_Next
 * @abstract    Increases the internal value pointer and returns the value
 * @param       xsThis  The set object
 * @result      The set value
 */
void * XSSet_Next( XSSet xsThis );

/*!
 * @function    XSSet_Previous
 * @abstract    Decrease the internal value pointer and returns the value
 * @param       xsThis  The set object
 * @result      The set value
 */
void * XSSet_Previous( XSSet xsThis );

/*!
 * @function    XSSet_Rewind
 * @abstract    Sets the internal value pointer to the first value in the set
 * @param       xsThis  The set object
 * @result      void
 */
void XSSet_Rewind( XSSet xsThis );

XS_EXTERN_C_END

#endif /* _XS_SET_H_ */
