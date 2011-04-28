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
 * @file        XSRuntime.h
 * @brief       Runtime functions
 * @author      Jean-David Gadina <macmade@eosgarden.com>
 */

#ifndef _XS_RUNTIME_H_
#define _XS_RUNTIME_H_
#pragma once

#include "XSMacros.h"

XS_EXTERN_C_BEGIN

#include "XS.h"

/*!
 * @brief       Initialize the XSFoundation runtime.
 * @details     Do not call this function. Use the XSFOUNDATION_START()
 *              macro instead.
 * @result      void
 */
void XSRuntime_Initialize( void );

/*!
 * @brief       Finilization the XSFoundation runtime.
 * @details     Do not call this function. Use the XSFOUNDATION_END()
 *              macro instead.
 * @result      void
 */
void XSRuntime_Finalize( void );

/*!
 * @brief       Registers a class for the runtime
 * @details     All runtime classes needs to be registered before the runtime
 *              can use them and create instances.
 *              This function needs to be called once per class,
 *              ie using pthread_once().
 * @param       cls     The class information structure to register
 * @result      The runtime type ID for the class
 */
XSClassID XSRuntime_NewClass( const XSClassInfos * const cls );

/*!
 * @brief       Initializes a new instance of a class
 * @param       cls     The class structure
 * @result      The allocated instance
 */
XSObject XSRuntime_CreateInstanceOfClass( XSClass cls );

/*!
 * @brief       Initializes a new instance of a class with a specific name
 * @param       name    The name of the class
 * @result      The allocated instance
 */
XSObject XSRuntime_CreateInstanceOfClassWithName( const char * name );

/*!
 * @brief       Initializes a new instance of a registered class
 * @param       classID The type ID
 * @result      The allocated instance
 */
XSObject XSRuntime_CreateInstance( XSClassID classID );

/*!
 * @brief       Gets an object's description
 * @param       ptr     The pointer to the object
 * @result      The object's description
 */
const char * XSRuntime_ObjectDescription( void * ptr );

/*!
 * @brief       Checks whether a pointer is an object instance
 * @param       ptr     The pointer to check
 * @result      True if the pointer represents an instance, otherwise false
 */
BOOL XSRuntime_IsInstance( void * ptr );

/*!
 * @brief       Gets the class structure for a specific type ID
 * @param       classID The class ID
 * @result      The class corresponding to the type ID
 */
XSClass XSRuntime_GetClassForClassID( XSClassID classID );

/*!
 * @brief       Gets the type ID for a specific class
 * @param       cls     The class
 * @result      The class ID of the class
 */
XSClassID XSRuntime_GetClassIDForClass( XSClass cls );

/*!
 * @brief       Gets the class for an object
 * @param       object  The object
 * @result      The object's class
 */
XSClass XSRuntime_GetClassForObject( XSObject object );

/*!
 * @brief       Gets the class type ID for an object
 * @param       object  The object
 * @result      The class ID for the object
 */
XSClassID XSRuntime_GetTypeIDForObject( XSObject object );

/*!
 * @brief       Gets the class name for an object
 * @param       classID The class ID
 * @result      The name of the class
 */
const char * XSRuntime_GetClassNameForClassID( XSClassID classID );

/*!
 * @brief       Gets the class name for an object
 * @param       cls     The class
 * @result      The name of the class
 */
const char * XSRuntime_GetClassNameForClass( XSClass cls );

/*!
 * @brief       Gets the class name for an object
 * @param       object  The object
 * @result      The name of the class
 */
const char * XSRuntime_GetClassNameForObject( XSObject object );

/*!
 * @brief       Checks whether an object is an instance of a class
 * @param       object  The object
 * @param       cls     The class
 * @result      True if the object is an instance of the class, otherwise false
 */
BOOL XSRuntime_IsInstanceOfClass( XSObject object, XSClass cls );

/*!
 * @brief       Checks whether an object is an instance of a class name
 * @param       object  The object
 * @param       name    The name of the class
 * @result      True if the object is an instance of the class name, otherwise false
 */
BOOL XSRuntime_IsInstanceOfClassName( XSObject object, const char * name );
    
XS_EXTERN_C_END

#endif /* _XS_RUNTIME_H_ */
