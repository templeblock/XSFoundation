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
 * @file        XSApplicationArgument.h
 * @brief       XSApplicationArgument class functions
 * @author      Jean-David Gadina <macmade@eosgarden.com>
 */

#ifndef _XS_APPLICATION_ARGUMENT_H_
#define _XS_APPLICATION_ARGUMENT_H_
#pragma once

#include "XSMacros.h"

XS_EXTERN_C_BEGIN

/*!
 * @typedef     XSApplicationArgument
 * @brief       Opaque type for the XSApplicationArgument objects
 */
typedef struct __XSApplicationArgument_Struct * XSApplicationArgument;

/*!
 * @enum        XSApplicationArgumentType
 * @brief       Command line argument types          
 */
typedef enum
{
    XSApplicationArgumentTypeFlag            = 0x00,    /*! Flag type (no value) */
    XSApplicationArgumentTypeInteger         = 0x01,    /*! Integer type */
    XSApplicationArgumentTypeUnsignedInteger = 0x02,    /*! Unsigned integer type */
    XSApplicationArgumentTypeString          = 0x03,    /*! String type (char pointer) */
    XSApplicationArgumentTypeFloat           = 0x04     /*! Float type */
}
XSApplicationArgumentType;

/*!
 * @brief       Object allocator
 * @result      The allocated object
 */
XSStatic XSApplicationArgument XSApplicationArgument_Alloc( void );

/*!
 * @brief       Initializes a CLI argument object
 * @param       xsThis  The argument object
 * @param       name    The name of the CLI argument, including dashes (- or --)
 * @param       type    The type of the CLI argument
 * @param       help    The help text (pass NULL if none)
 * @result      The argument object
 */
XSObject XSApplicationArgument_Init( XSApplicationArgument xsThis, const char * name, XSApplicationArgumentType type, const char * help );

/*!
 * @brief       Gets the name of the CLI argument
 * @param       xsThis  The argument object
 * @result      The name of the argument object
 */
const char * XSApplicationArgument_GetName( XSApplicationArgument xsThis );

/*!
 * @brief       Gets the help text of the CLI argument
 * @param       xsThis  The argument object
 * @result      The help text of the argument object
 */
const char * XSApplicationArgument_GetHelp( XSApplicationArgument xsThis );

/*!
 * @brief       Gets the type of the CLI argument
 * @param       xsThis  The argument object
 * @result      The type of the argument object
 */
XSApplicationArgumentType XSApplicationArgument_GetType( XSApplicationArgument xsThis );

/*!
 * @brief       Sets the flag to 'on' for the argument
 * @param       xsThis  The argument object
 * @result      void
 */
void XSApplicationArgument_SetFlag( XSApplicationArgument xsThis );

/*!
 * @brief       Sets the integer value for the argument
 * @param       xsThis  The argument object
 * @param       value   ...
 * @result      void
 */
void XSApplicationArgument_SetIntegerValue( XSApplicationArgument xsThis, XSInteger value );

/*!
 * @brief       Sets the unsigned integer value for the argument
 * @param       xsThis  The argument object
 * @param       value   ...
 * @result      void
 */
void XSApplicationArgument_SetUnsignedIntegerValue( XSApplicationArgument xsThis, XSUInteger value );

/*!
 * @brief       Sets the string value for the argument
 * @param       xsThis  The argument object
 * @param       value   ...
 * @result      void
 */
void XSApplicationArgument_SetStringValue( XSApplicationArgument xsThis, const char * value );

/*!
 * @brief       Sets the float value for the argument
 * @param       xsThis  The argument object
 * @param       value   ...
 * @result      void
 */
void XSApplicationArgument_SetFloatValue( XSApplicationArgument xsThis, XSFloat value );

/*!
 * @brief       Gets the flag state for the argument
 * @param       xsThis  The argument object
 * @result      A boolean value indicating if the flag is set
 */
BOOL XSApplicationArgument_GetFlag( XSApplicationArgument xsThis );

/*!
 * @brief       Gets the integer value for the argument
 * @param       xsThis  The argument object
 * @result      The argument's integer value
 */
XSInteger XSApplicationArgument_GetIntegerValue( XSApplicationArgument xsThis );

/*!
 * @brief       Gets the unsigned integer value for the argument
 * @param       xsThis  The argument object
 * @result      The argumen'ts unsigned integer value
 */
XSUInteger XSApplicationArgument_GetUnsignedIntegerValue( XSApplicationArgument xsThis );

/*!
 * @brief       Gets the string value for the argument
 * @param       xsThis  The argument object
 * @result      The argument's string value
 */
const char * XSApplicationArgument_GetStringValue( XSApplicationArgument xsThis );

/*!
 * @brief       Gets the float value for the argument
 * @param       xsThis  The argument object
 * @result      The argument's float value
 */
XSFloat XSApplicationArgument_GetFloatValue( XSApplicationArgument xsThis );

XS_EXTERN_C_END

#endif /* _XS_APPLICATION_ARGUMENT_H_ */
