//      Name: memCpyTest.h
//
//      Description: memory copying speed test
//      
//      Copyright 2012 Vitaliy Sergienko <visergienko@ukr.net>
//      
//      This program is free software; you can redistribute it and/or modify
//      it under the terms of the GNU General Public License as published by
//      the Free Software Foundation; either version 2 of the License, or
//      (at your option) any later version.
//      
//      This program is distributed in the hope that it will be useful,
//      but WITHOUT ANY WARRANTY; without even the implied warranty of
//      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//      GNU General Public License for more details.
//      
//      You should have received a copy of the GNU General Public License
//      along with this program; if not, write to the Free Software
//      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
//      MA 02110-1301, USA.
//          

#ifndef _MEMCPYTEST_H_
#define _MEMCPYTEST_H_

////////////////////////////////////////////////////////////////////////
/// Include libraries

#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <math.h>
#include <time.h>

using namespace std;

////////////////////////////////////////////////////////////////////////
/// Definitions

//----------------------------------------------------------------------
//Error codes

#define NO_ERROR	        	0
#define ERROR_MEMORY_ALLOC		1
#define ERROR_MEMORY_COPY		2
#define ERROR_PARAM_INVALID		3
#define ERROR_TEST_INVALID		4

//----------------------------------------------------------------------
//Constants

#define KB_BYTE_NUMBER          (1024) /* size of kilobyte in bytes */
#define MB_BYTE_NUMBER          (1024 * KB_BYTE_NUMBER) /* size of megabyte in bytes */
#define MEMORY_AMOUNT           (128 * MB_BYTE_NUMBER) /* amount of memory to be allocated, in bytes */
#define SMALL_MEM_BLOCK_SIZE    (1 * KB_BYTE_NUMBER) /* size of small memory block size */
#define MEDIUM_MEM_BLOCK_SIZE   (64 * KB_BYTE_NUMBER) /* size of medium memory block size */
#define BIG_MEM_BLOCK_SIZE      (4 * MB_BYTE_NUMBER) /* size of big memory block size */

#define SMALL_BLOCK_ITERS       (100) /* memcpy iterations count for small memory block size */
#define MEDIUM_BLOCK_ITERS      (100) /* memcpy iterations count for medium memory block size */
#define BIG_BLOCK_ITERS         (100) /* memcpy iterations count for big memory block size */

//----------------------------------------------------------------------
//Data types

typedef signed char             INT8;
typedef unsigned char           UINT8;
typedef unsigned int            UINT32;

////////////////////////////////////////////////////////////////////////
///Functions

/**
 *@brief		Memory blocks copying test
 * 
 * @param[in]	srcBuf              memory buffer to copy from
 * @param[in]	dstBuf              memory buffer to copy to
 * @param[in]	bufLen              memory buffer length (same for srcBuf & dstBuf)
 * @param[in]	memBlockSize        size of memory block
 * @param[in]	iters               number of test iterations
 * @param[out]	score               test score
 * @return 		NO_ERROR or relevant error code
 */
UINT32 memCpyTest(UINT8 *srcBuf, UINT8 *dstBuf, UINT32 bufLen,
                  UINT32 memBlockSize, UINT32 iters, double *score);

/**
 *@brief		Getting overall memTest score
 * 
 * @param[out]	score               final test score
 * @param[out]	pRetPercent(int)    callback: test completion percent
 * @return 		NO_ERROR or relevant error code
 */
UINT32 getMemCpyTestScore(UINT32 *score, void (*pRetPercent)(int));

////////////////////////////////////////////////////////////////////////

#endif /* _MEMCPYTEST_H_ */
