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
 * @header      XSApplicationArgument.c
 * @copyright   eosgarden 2011 - Jean-David Gadina <macmade@eosgarden.com>
 * @abstract    Implementation for the XSApplicationArgument class
 */

#include "XS.h"
#include "__XSApplicationArgument.h"

extern XSClassID __XSApplicationArgumentClassID;

XSStatic XSApplicationArgument XSApplicationArgument_Alloc( void )
{
    return ( XSObject )XSRuntime_CreateInstance( __XSApplicationArgumentClassID );
}

XSApplicationArgument XSApplicationArgument_Init( XSApplicationArgument xsThis, const char * name, XSApplicationArgumentType type, const char * help )
{
    __XSApplicationArgument * arg;
    
    arg           = ( __XSApplicationArgument * )xsThis;
    arg->name     = name;
    arg->type     = type;
    arg->uint_val = 0;
    arg->int_val  = 0;
    arg->str_val  = NULL;
    arg->flag_val = NO;
    arg->help     = help;
    
    return ( XSApplicationArgument )arg;
}

const char * XSApplicationArgument_GetName( XSApplicationArgument xsThis )
{
    return ( ( __XSApplicationArgument * )xsThis )->name;
}

const char * XSApplicationArgument_GetHelp( XSApplicationArgument xsThis )
{
    return ( ( __XSApplicationArgument * )xsThis )->help;
}

XSApplicationArgumentType XSApplicationArgument_GetType( XSApplicationArgument xsThis )
{
    return ( ( __XSApplicationArgument * )xsThis )->type;
}

void XSApplicationArgument_SetFlag( XSApplicationArgument xsThis )
{
    __XSApplicationArgument * _arg;
    
    _arg           = ( __XSApplicationArgument * )xsThis;
    _arg->flag_val = YES;
}

void XSApplicationArgument_SetIntegerValue( XSApplicationArgument xsThis, XSInteger value )
{
    __XSApplicationArgument * _arg;
    
    _arg          = ( __XSApplicationArgument * )xsThis;
    _arg->int_val = value;
}

void XSApplicationArgument_SetUnsignedIntegerValue( XSApplicationArgument xsThis, XSUInteger value )
{
    __XSApplicationArgument * _arg;
    
    _arg           = ( __XSApplicationArgument * )xsThis;
    _arg->uint_val = value;
}

void XSApplicationArgument_SetStringValue( XSApplicationArgument xsThis, const char * value )
{
    __XSApplicationArgument * _arg;
    
    _arg          = ( __XSApplicationArgument * )xsThis;
    _arg->str_val = value;
}

void XSApplicationArgument_SetFloatValue( XSApplicationArgument xsThis, XSFloat value )
{
    __XSApplicationArgument * _arg;
    
    _arg            = ( __XSApplicationArgument * )xsThis;
    _arg->float_val = value;
}

BOOL XSApplicationArgument_GetFlag( XSApplicationArgument xsThis )
{
    __XSApplicationArgument * _arg;
    
    _arg = ( __XSApplicationArgument * )xsThis;
    
    return _arg->flag_val;
}

XSInteger XSApplicationArgument_GetIntegerValue( XSApplicationArgument xsThis )
{
    __XSApplicationArgument * _arg;
    
    _arg = ( __XSApplicationArgument * )xsThis;
    
    return _arg->int_val;
}

XSUInteger XSApplicationArgument_GetUnsignedIntegerValue( XSApplicationArgument xsThis )
{
    __XSApplicationArgument * _arg;
    
    _arg = ( __XSApplicationArgument * )xsThis;
    
    return _arg->uint_val;
}

const char * XSApplicationArgument_GetStringValue( XSApplicationArgument xsThis )
{
    __XSApplicationArgument * _arg;
    
    _arg = ( __XSApplicationArgument * )xsThis;
    
    return _arg->str_val;
}

XSFloat XSApplicationArgument_GetFloatValue( XSApplicationArgument xsThis )
{
    __XSApplicationArgument * _arg;
    
    _arg = ( __XSApplicationArgument * )xsThis;
    
    return _arg->float_val;
}
