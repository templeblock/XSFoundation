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
 * @header      XSFile.h
 * @copyright   eosgarden 2011 - Jean-David Gadina <macmade@eosgarden.com>
 * @abstract    XSFile class functions
 */

#ifndef _XS_FILE_H_
#define _XS_FILE_H_
#pragma once

#include "XSMacros.h"

XS_EXTERN_C_BEGIN

/*!
 * @typedef     XSFile
 * @abstract    Opaque type for the XSFile objects
 */
typedef struct __XSFile_Struct * XSFile;

/*!
 * @typedef     XSFileOpenMode
 * @abstract    Open modes for XSFile
 * @description A specific mode can be ORed with XSFileOpenModeText
 *              XSFileOpenModeBinary to specify if working with text or binary
 *              files
 * @field       XSFileOpenModeText          Text mode
 * @field       XSFileOpenModeBinary        Binary mode
 * @field       XSFileOpenModeRead          "r" - Text reading
 * @field       XSFileOpenModeWrite         "w" - Text writing
 * @field       XSFileOpenModeAppend        "a" - Text append
 * @field       XSFileOpenModeApendAtEnd    "a+" - Text append, reading, and writing at end
 * @field       XSFileOpenModeUpdate        "r+" - Text update (reading and writing)
 * @field       XSFileOpenModeUpdateDiscard "w+" - Text update discarding previous content (if any)
 */
typedef enum
{
    XSFileOpenModeText          = 0x00,
    XSFileOpenModeBinary        = 0x01,
    XSFileOpenModeRead          = 0x02,
    XSFileOpenModeWrite         = 0x04,
    XSFileOpenModeAppend        = 0x06,
    XSFileOpenModeApendAtEnd    = 0x08,
    XSFileOpenModeUpdate        = 0x0A,
    XSFileOpenModeUpdateDiscard = 0x0E
}
XSFileOpenMode;

/*!
 * @typedef     XSFileSeekPosition
 * @abstract    Origin position for the file seek operations
 * @field       XSFileSeekPositionCurent    Current position
 * @field       XSFileSeekPositionStart     Start of the file
 * @field       XSFileSeekPositionEnd       End of the file
 * @field       XSFileOpenModeReadSet       Specific position
 */
typedef enum
{
    XSFileSeekPositionCurent = SEEK_CUR,
    XSFileSeekPositionStart  = 0,
    XSFileSeekPositionEnd    = SEEK_END,
    XSFileOpenModeReadSet    = SEEK_SET
}
XSFileSeekPosition;

/*!
 * @var         XSStdin
 * @abstract    XSFile object representing stdin
 */
extern XSFile XSStdin;

/*!
 * @var         XSStdout
 * @abstract    XSFile object representing stdout
 */
extern XSFile XSStdout;

/*!
 * @var         XSStderr
 * @abstract    XSFile object representing stderr
 */
extern XSFile XSStderr;

/*!
 * @function    XSFile_Alloc
 * @abstract    Object allocator
 * @result      The allocated object
 */
XSStatic XSObject XSFile_Alloc( void );

/*!
 * @function    XSFile_Init
 * @abstract    Initialize a file object
 * @param       xsThis  The file object
 * @result      A pointer to the file object
 */
XSFile XSFile_Init( XSFile xsThis );

/*!
 * @abstract    Creates an XSFile instance and opens the represented file.
 * @description This function may return NULL if the represented file has not
 *              been opened.
 * @param       filename    The name of the file
 * @param       openMode    The file open mode (see XSFileOpenMode)
 * @result      The instance of XSFile
 */
XSStatic XSFile XSFile_Open( const char * filename, XSFileOpenMode openMode );

/*!
 * @function    
 * @abstract    Flushes the file stream stream
 * @param       xsThis    The file object
 * @result      Zero on success or EOF on error
 */
XSInteger XSFile_Flush( XSFile xsThis );

/*!
 * @function    XSFile_Close
 * @abstract    Closes the file stream (after flushing, if output stream)
 * @discussion  You're still responsible to release the file object after
 *              calling this function.
 * @param       xsThis    The file object
 * @result      EOF on error, zero otherwise.
 */
XSInteger XSFile_Close( XSFile xsThis );

/*!
 * @function    XSFile_Printf
 * @abstract    Converts (according to format format) and writes output to the file
 * @param       xsThis    The file object
 * @result      The number of characters written, or negative value on error
 */
XSInteger XSFile_Printf( XSFile xsThis, const char * format, ... ) FORMAT_ATTRIBUTE( printf, 2, 0 );

/*!
 * @function    XSFile_VPrintf
 * @abstract    Equivalent to fprintf with variable argument list replaced by arg.
 * @param       xsThis  The file object
 * @param       arg     The variable arguments list
 * @result      The number of characters written, or negative value on error
 */
XSInteger XSFile_VPrintf( XSFile xsThis, const char * format, va_list arg ) FORMAT_ATTRIBUTE( printf, 2, 0 );

/*!
 * @function    XSFile_Getc
 * @abstract    Returns the next character from the file.
 * @param       xsThis    The file object
 * @result      The character or EOF on error
 */
XSInteger XSFile_Getc( XSFile xsThis );

/*!
 * @function    XSFile_Putc
 * @abstract    Writes a character to the file
 * @param       xsThis    The file object
 * @param       c       The character to write
 * @result      The character or EOF on error
 */
XSInteger XSFile_Putc( XSFile xsThis, XSInteger c );

/*!
 * @function    XSFile_Puts
 * @abstract    Writes a C string to the file
 * @param       xsThis    The file object
 * @result      Non-negative on success or EOF on error.
 */
XSInteger XSFile_Puts( XSFile xsThis, const char * s );

/*!
 * @function    XSFile_Read
 * @abstract    Reads from the file
 * @param       xsThis    The file object
 * @param       ptr     A pointer to the memory location in which the data will be placed.
 * @param       xsThis    The size of the objects to read
 * @param       xsThis    The number of objects to read
 * @result      The number of objects read
 */
size_t XSFile_Read( XSFile xsThis, void * ptr, size_t size, size_t nobj );

/*!
 * @function    XSFile_Write
 * @abstract    Writes to the file
 * @param       xsThis    The file object
 * @param       ptr     The data to write
 * @param       xsThis    The size of the objects to write
 * @param       xsThis    The number of objects to write
 * @result      The number of objects written
 */
size_t XSFile_Write( XSFile xsThis, const void * ptr, size_t size, size_t nobj );

/*!
 * @function    XSFile_Seek
 * @abstract    Sets file position for the file and clears end-of-file indicator
 * @description For a binary stream, file position is set to offset bytes from
 *              the position indicated by origin: beginning of file for
 *              SEEK_SET, current position for SEEK_CUR, or end of file for
 *              SEEK_END. Behaviour is similar for a text stream, but offset
 *              must be zero or, for SEEK_SET only, a value returned by ftell.
 * @param       xsThis    The file object
 * @param       origin  The seek origin (see XSFileSeekPosition)
 * @result      Non-zero on error.
 */
XSInteger XSFile_Seek( XSFile xsThis, XSInteger offset, XSFileSeekPosition origin );

/*!
 * @function    XSFile_Tell
 * @abstract    Gets the current file position
 * @param       xsThis    The file object
 * @result      The position or -1 on error
 */
XSInteger XSFile_Tell( XSFile xsThis );

/*!
 * @function    XSFile_Rewind
 * @abstract    Rewinds to the beginning of the file and clears the error indicators
 * return       void
 */
void XSFile_Rewind( XSFile xsThis );

/*!
 * @function    XSFile_GetPos
 * @abstract    Stores the current file position
 * @param       xsThis    The file object
 * @param       ptr     A pointer where tos store the file position
 * @result      Non-zero on error
 */
XSInteger XSFile_GetPos( XSFile xsThis, fpos_t * ptr );

/*!
 * @function    XSFile_SetPos
 * @abstract    Sets the current file position
 * @param       xsThis    The file object
 * @param       ptr     The file position
 * @result      Non-zero on error
 */
XSInteger XSFile_SetPos( XSFile xsThis, const fpos_t * ptr );

/*!
 * @function    XSFile_ClearErr
 * @abstract    Clears end-of-file and error indicators
 * @param       xsThis    The file object
 * @result      void
 */
void XSFile_ClearErr( XSFile xsThis );

/*!
 * @function    XSFile_EndOfFile
 * @abstract    Checks for the end of the file
 * @param       xsThis    The file object
 * @result      Non-zero if end-of-file indicator is set
 */
XSInteger XSFile_EndOfFile( XSFile xsThis );

/*!
 * @function    XSFile_Error
 * @abstract    Checks for the error indicator
 * @param       xsThis    The file object
 * @result      Non-zero if error indicator is set
 */
XSInteger XSFile_Error( XSFile xsThis );

/*!
 * @function    XSFile_Filename
 * @abstract    Gets the filename
 * @param       xsThis    The file object
 * @result      The name of the file
 */
const char * XSFile_Filename( XSFile xsThis );

/*!
 * @function    XSFile_OpenMode
 * @abstract    Gets the file's open mode
 * @param       xsThis    The file object
 * @result      The file's open mode
 */
const char * XSFile_OpenMode( XSFile xsThis );

/*!
 * @function    XSFile_IsReadable
 * @abstract    Checks if the file is readable 
 * @param       xsThis    The file object
 * @result      true if the file is readable, otherwise false
 */
BOOL XSFile_IsReadable( XSFile xsThis );

/*!
 * @function    XSFile_IsWriteable
 * @abstract    Checks if the file is writeable 
 * @param       xsThis    The file object
 * @result      true if the file is writeable, otherwise false
 */
BOOL XSFile_IsWriteable( XSFile xsThis );

/*!
 * @function    XSFile_Copy
 * @abstract    Copies the file to another destination
 * @param       xsThis    The file object
 * @result      True if the file was copeid, otherwise false
 */
BOOL XSFile_Copy( XSFile xsThis, char * new_name );

/*!
 * @function    XSFile_GetBit
 * @abstract    Gets the next bit in the file
 * @param       xsThis    The file object
 * @result      
 */
XSInteger XSFile_GetBit( XSFile xsThis );

/*!
 * @function    XSFile_PutBit
 * @abstract    Writes a bit in the file
 * @param       xsThis    The file object
 * @result      
 */
XSInteger XSFile_PutBit( XSFile xsThis, uint8_t bit );

/*!
 * @function    XSFile_GetBits
 * @abstract    Gets bits from the file
 * @param       xsThis    The file object
 * @result      
 */
XSInteger XSFile_GetBits( XSFile xsThis, XSUInteger count );

/*!
 * @function    XSFile_PutBits
 * @abstract    Write bits to the file
 * @param       xsThis    The file object
 * @result      
 */
XSInteger XSFile_PutBits( XSFile xsThis, uint64_t bits, XSUInteger count );

/*!
 * @function    XSFile_DeviceID
 * @abstract    Gets the device ID of the file
 * @param       xsThis    The file object
 * @result      The file's device ID
 */
dev_t XSFile_DeviceID( XSFile xsThis );

/*!
 * @function    XSFile_SerialNumber
 * @abstract    Gets the serial number of the file
 * @param       xsThis    The file object
 * @result      The file's serial number
 */
ino_t XSFile_SerialNumber( XSFile xsThis );

/*!
 * @function    XSFile_NumberOfLinks
 * @abstract    Gets the number of links to the file
 * @param       xsThis    The file object
 * @result      The number of links to the file
 */
nlink_t XSFile_NumberOfLinks( XSFile xsThis );

/*!
 * @function    XSFile_UID
 * @abstract    Gets the file's user ID
 * @param       xsThis    The file object
 * @result      the file's user ID
 */
uid_t XSFile_UID( XSFile xsThis );

/*!
 * @function    XSFile_GID
 * @abstract    Gets the file's group ID
 * @param       xsThis    The file object
 * @result      The file's group ID
 */
gid_t XSFile_GID( XSFile xsThis );

/*!
 * @function    XSFile_Size
 * @abstract    Gets the file size in bytes
 * @param       xsThis    The file object
 * @result      The file size in bytes
 */
size_t XSFile_Size( XSFile xsThis );

/*!
 * @function    XSFile_HumanReadableSize
 * @abstract    Gets an human readable size for the size
 * @param       xsThis      The file object
 * @param       unit        A buffer to store the size unit
 * @result      The human readable size
 */
XSFloat XSFile_HumanReadableSize( XSFile xsThis, char unit[] );

/*!
 * @function    XSFile_AccessTime
 * @abstract    Gets the file's access time
 * @param       xsThis    The file object
 * @result      The file's access time
 */
time_t XSFile_AccessTime( XSFile xsThis );

/*!
 * @function    XSFile_ModifictaionTime
 * @abstract    Gets the file's modification time
 * @param       xsThis    The file object
 * @result      The file's modification time
 */
time_t XSFile_ModifictaionTime( XSFile xsThis );

/*!
 * @function    XSFile_CreationTime
 * @abstract    Gets the file's creation time
 * @param       xsThis    The file object
 * @result      The file's creation time
 */
time_t XSFile_CreationTime( XSFile xsThis );

/*!
 * @function    XSFile_IsBlockDevice
 * @abstract    Checks if the file is a block device
 * @param       xsThis    The file object
 * @result      YES is the file is a block device, otherwise NO
 */
BOOL XSFile_IsBlockDevice( XSFile xsThis );

/*!
 * @function    XSFile_IsCharacterDevice
 * @abstract    Checks if the file is a character device
 * @param       xsThis    The file object
 * @result      YES is the file is a character device otherwise NO
 */
BOOL XSFile_IsCharacterDevice( XSFile xsThis );

/*!
 * @function    XSFile_IsFIFO
 * @abstract    Checks if the file is a FIFO
 * @param       xsThis    The file object
 * @result      YES is the file is a FIFO otherwise NO
 */
BOOL XSFile_IsFIFO( XSFile xsThis );

/*!
 * @function    XSFile_IsRegularFile
 * @abstract    Checks if the file is a regular file
 * @param       xsThis    The file object
 * @result      YES is the file is a regular file otherwise NO
 */
BOOL XSFile_IsRegularFile( XSFile xsThis );

/*!
 * @function    XSFile_IsLink
 * @abstract    Checks if the file is a link
 * @param       xsThis    The file object
 * @result      YES is the file is a link otherwise NO
 */
BOOL XSFile_IsLink( XSFile xsThis );

/*!
 * @function    XSFile_IsSocket
 * @abstract    Checks if the file is a socket
 * @param       xsThis    The file object
 * @result      YES is the file is a socket otherwise NO
 */
BOOL XSFile_IsSocket( XSFile xsThis );

/*!
 * @function    XSFile_IsUserReadable
 * @abstract    Checks if the file is readable for the user
 * @param       xsThis    The file object
 * @result      YES is the file is readable for the user, otherwise NO
 */
BOOL XSFile_IsUserReadable( XSFile xsThis );

/*!
 * @function    XSFile_IsUserWriteable
 * @abstract    Checks if the file is writeable for the user
 * @param       xsThis    The file object
 * @result      YES is the file is writeable for the user, otherwise NO
 */
BOOL XSFile_IsUserWriteable( XSFile xsThis );

/*!
 * @function    XSFile_ISUserExecutable
 * @abstract    Checks if the file is executable for the user
 * @param       xsThis    The file object
 * @result      YES is the file is executable for the user, otherwise NO
 */
BOOL XSFile_ISUserExecutable( XSFile xsThis );

/*!
 * @function    XSFile_IsGroupReadable
 * @abstract    Checks if the file is readable for the group
 * @param       xsThis    The file object
 * @result      YES is the file is readable for the group, otherwise NO
 */
BOOL XSFile_IsGroupReadable( XSFile xsThis );

/*!
 * @function    XSFile_IsGroupWriteable
 * @abstract    Checks if the file is writable for the group
 * @param       xsThis    The file object
 * @result      YES is the file is writable for the group, otherwise NO
 */
BOOL XSFile_IsGroupWriteable( XSFile xsThis );

/*!
 * @function    XSFile_IsGroupExecutable
 * @abstract    Checks if the file is executable for the group
 * @param       xsThis    The file object
 * @result      YES is the file is executable for the group, otherwise NO
 */
BOOL XSFile_IsGroupExecutable( XSFile xsThis );

/*!
 * @function    XSFile_IsWorldReadable
 * @abstract    Checks if the file is readable for the world
 * @param       xsThis    The file object
 * @result      YES is the file is readable for the world, otherwise NO
 */
BOOL XSFile_IsWorldReadable( XSFile xsThis );

/*!
 * @function    XSFile_IsWorldWriteable
 * @abstract    Checks if the file is writeable for the world
 * @param       xsThis    The file object
 * @result      YES is the file is writeable for the world, otherwise NO
 */
BOOL XSFile_IsWorldWriteable( XSFile xsThis );

/*!
 * @function    XSFile_IsWorldExecutable
 * @abstract    Checks if the file is executable for the world
 * @param       xsThis    The file object
 * @result      YES is the file is executable for the world, otherwise NO
 */
BOOL XSFile_IsWorldExecutable( XSFile xsThis );

/*!
 * @function    XSFile_HasSUID
 * @abstract    Checks if the file has the SUID bit set
 * @param       xsThis    The file object
 * @result      True if the SUID bit is set, otherwise false
 */
BOOL XSFile_HasSUID( XSFile xsThis );

/*!
 * @function    XSFile_HasSGID
 * @abstract    Checks if the file has the SGID bit set
 * @param       xsThis    The file object
 * @result      True if the SGID bit is set, otherwise false
 */
BOOL XSFile_HasSGID( XSFile xsThis );

XS_EXTERN_C_END

#endif /* _XS_FILE_H_ */
