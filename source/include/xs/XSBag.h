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
 * @header      XSBag.h
 * @copyright   eosgarden 2011 - Jean-David Gadina <macmade@eosgarden.com>
 * @abstract    XSBag class functions
 */

#ifndef _XS_BAG_H_
#define _XS_BAG_H_
#pragma once

#include "XSMacros.h"

XS_EXTERN_C_BEGIN

/*!
 * @typedef     XSBag
 * @abstract    Opaque type for the XSBag objects
 */
typedef struct __XSBag_Struct * XSBag;

/*!
 * @function    XSBag_Alloc
 * @abstract    Object allocator
 * @result      The allocated object
 */
XSStatic XSObject XSBag_Alloc( void );

/*!
 * @function    XSBag_Init
 * @abstract    Creates an empty bag
 * @param       xsThis  The bag object
 * @result      The bag object
 */
XSObject XSBag_Init( XSObject xsThis );

/*!
 * @function    XSBag_InitWithCapacity
 * @abstract    Creates an empty bag with an initial capacity
 * @param       xsThis      The bag object
 * @param       capacity    The initial capacityThe bag object
 * @result      The bag object
 */
XSBag XSBag_InitWithCapacity( XSBag xsThis, XSUInteger capacity );

/*!
 * @function    XSBag_InitWithValues
 * @abstract    Creates a bag with values
 * @param       xsThis      The bag object
 * @param       value1      The first value
 * @param       ...         Other values, terminated by a NULL fence
 * @result      The bag object
 */
XSBag XSBag_InitWithValues( XSBag xsThis, XSObject value1, ... );

/*!
 * @function    XSBag_Count
 * @abstract    Gets the number of values in the bag
 * @param       xsThis  The bag object
 * @result      The number of values
 */
XSUInteger XSBag_Count( XSBag xsThis );

/*!
 * @function    XSBag_ContainsValue
 * @abstract    Checks if a bag contains a value
 * @param       xsThis  The bag object
 * @param       xsThis  The value to check
 * @result      True if the bag contains the value, otherwise false
 */
BOOL XSBag_ContainsValue( XSBag xsThis, XSObject value );

/*!
 * @function    XSBag_AddValue
 * @abstract    Adds a value in the bag
 * @description The new value will be retained
 * @param       xsThis  The bag object
 * @param       xsThis  The value to add
 * @result      void
 */
void XSBag_AddValue( XSBag xsThis, XSObject value );

/*!
 * @function    XSBag_RemoveValue
 * @abstract    Removes a value in the bag
 * @description The removed value will be released
 * @param       xsThis  The bag object
 * @param       xsThis  The value to remove
 * @result      void
 */
void XSBag_RemoveValue( XSBag xsThis, XSObject value );

/*!
 * @function    XSBag_ReplaceValue
 * @abstract    Replaces a value in the bag
 * @description The old value will be released, and the new will be retained
 * @param       xsThis      The bag object
 * @param       valueOld    The value to replace
 * @param       valueNew    The new value
 * @result      void
 */
void XSBag_ReplaceValue( XSBag xsThis, XSObject valueOld, XSObject valueNew );

/*!
 * @function    XSBag_Index
 * @abstract    Gets the current bag index
 * @param       xsThis  The bag object
 * @result      The current bag index
 */
XSUInteger XSBag_Index( XSBag xsThis );

/*!
 * @function    XSBag_Current
 * @abstract    Gets the current bag value
 * @param       xsThis  The bag object
 * @result      The current bag value
 */
XSAutoreleased XSObject XSBag_Current( XSBag xsThis );

/*!
 * @function    XSBag_Next
 * @abstract    Increases the internal value pointer and returns the value
 * @param       xsThis  The bag object
 * @result      The bag value
 */
XSAutoreleased XSObject XSBag_Next( XSBag xsThis );

/*!
 * @function    XSBag_Previous
 * @abstract    Decrease the internal value pointer and returns the value
 * @param       xsThis  The bag object
 * @result      The bag value
 */
XSAutoreleased XSObject XSBag_Previous( XSBag xsThis );

/*!
 * @function    XSBag_Rewind
 * @abstract    Bags the internal value pointer to the first value in the bag
 * @param       xsThis  The bag object
 * @result      void
 */
void XSBag_Rewind( XSBag xsThis );

XS_EXTERN_C_END

#endif /* _XS_BAG_H_ */
