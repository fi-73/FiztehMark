//      Name: memCpyTest.cpp
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

////////////////////////////////////////////////////////////////////////
/// Include libraries

#include "memCpyTest.h"

using namespace std;

////////////////////////////////////////////////////////////////////////
///Functions

/**
 *@brief		Memory blocks copying test
 * 
 * @param[in]	srcBuf			memory buffer to copy from
 * @param[in]	dstBuf			memory buffer to copy to
 * @param[in]	bufLen			memory buffer length (same for srcBuf & dstBuf)
 * @param[in]	memBlockSize	size of memory block
 * @param[in]	iters			number of test iterations
 * @param[out]	score			test score
 * @return 		NO_ERROR or relevant error code
 */
UINT32 memCpyTest(UINT8 *srcBuf, UINT8 *dstBuf, UINT32 bufLen, UINT32 memBlockSize, UINT32 iters, double *score)
{
	if(!srcBuf || !dstBuf || !bufLen || !iters || !memBlockSize)
	{
		return ERROR_PARAM_INVALID;
	}
	
    long double time1, time2;
    UINT32 i;
        
	time1 = clock();
	for(i = 0; i < iters; i++)
	{
		for(UINT32 j = 0; j < bufLen; j += memBlockSize)
		{				
			memcpy(dstBuf + j, srcBuf + j, memBlockSize);
        }
	}
	time2 = clock() - time1;   
	
	//time in microseconds
    time1 = (time2 * 1000000.0) / CLOCKS_PER_SEC;
	if(!time1)
	{
		cerr << endl << "WARNING: " << "memTest: too fast procedure, try greater parameter values";
		//time1++;
		return ERROR_TEST_INVALID;
	}
	
	//amount of bytes that were copied per one microsecond
    *score = ((double)bufLen * (double)iters) / (double)time1;
	
    return NO_ERROR;
}

/**
 *@brief		Getting overall memTest score
 * 
 * @param[out]	score			final test score
 * @return 		NO_ERROR or relevant error code
 */
UINT32 getMemCpyTestScore(UINT32 *score, void (*pRetPercent)(int))
{
	///memory allocation
    UINT8 *memSrcBuf = NULL, *memDstBuf = NULL;
    memSrcBuf = new UINT8[MEMORY_AMOUNT];
    memDstBuf = new UINT8[MEMORY_AMOUNT];
    if(!memSrcBuf || !memDstBuf)
    {
        cerr << endl << "ERROR: " << "memory allocation failed";
        if(!memSrcBuf)
        {
            delete [] memSrcBuf;
        }
        if(!memDstBuf)
        {
            delete [] memDstBuf;
        }
        return ERROR_MEMORY_ALLOC;
    }
    
    ///initializing buffer values
    memset(memSrcBuf, 0xF1, MEMORY_AMOUNT);
    memset(memDstBuf, 0x00, MEMORY_AMOUNT);
    
    ///memory copying speed test
    double score1, score2, score3;

    ///percents complete
    int percent = 0;
    pRetPercent(percent);
    
    //test return value
    UINT32 ret = NO_ERROR;
    
    {          
        ///small blocks
        {
            ret = memCpyTest(memSrcBuf, memDstBuf, MEMORY_AMOUNT, SMALL_MEM_BLOCK_SIZE, SMALL_BLOCK_ITERS, &score1);
			if(ret != NO_ERROR)
			{
				delete [] memSrcBuf;
				delete [] memDstBuf;
				cerr << endl << "ERROR: " << "memTest failed";
				return ret;
			}
			//cout << "Score: " << score1 << " points" << endl;
			
			//comparing source and destination memory buffers
			if(memcmp(memDstBuf, memSrcBuf, MEMORY_AMOUNT))
			{
				delete [] memSrcBuf;
				delete [] memDstBuf;
				cerr << endl << "ERROR: " << "small memory blocks copying test";
				cerr << endl << "MESSAGE: " << "Memory copy failed. Destination and source buffers differ";
				return ERROR_MEMORY_COPY;
				
			}
			memset(memDstBuf, 0x00, MEMORY_AMOUNT);
            percent += 33;
            pRetPercent(percent);
		}
        
        ///medium blocks
        {
            ret = memCpyTest(memSrcBuf, memDstBuf, MEMORY_AMOUNT, MEDIUM_MEM_BLOCK_SIZE, MEDIUM_BLOCK_ITERS, &score2);
			if(ret != NO_ERROR)
			{
				delete [] memSrcBuf;
				delete [] memDstBuf;
				cerr << endl << "ERROR: " << "memTest failed";
				return ret;
			}
			//cout << "Score: " << score2 << " points" << endl;
			
			//comparing source and destination memory buffers
			if(memcmp(memDstBuf, memSrcBuf, MEMORY_AMOUNT))
			{
				delete [] memSrcBuf;
				delete [] memDstBuf;
				cerr << endl << "ERROR: " << "medium memory blocks copying test";
				cerr << endl << "MESSAGE: " << "Memory copy failed. Destination and source buffers differ";
				return ERROR_MEMORY_COPY;
				
			}
			memset(memDstBuf, 0x00, MEMORY_AMOUNT);
            percent += 33;
            pRetPercent(percent);
		}
        
        ///big blocks
        {
            ret = memCpyTest(memSrcBuf, memDstBuf, MEMORY_AMOUNT, BIG_MEM_BLOCK_SIZE, BIG_BLOCK_ITERS, &score3);
			if(ret != NO_ERROR)
			{
				delete [] memSrcBuf;
				delete [] memDstBuf;
				cerr << endl << "ERROR: " << "memTest failed";
				return ret;
			}
			//cout << "Score: " << score3 << " points" << endl;
			
			//comparing source and destination memory buffers
			if(memcmp(memDstBuf, memSrcBuf, MEMORY_AMOUNT))
			{
				delete [] memSrcBuf;
				delete [] memDstBuf;
				cerr << endl << "ERROR: " << "big memory blocks copying test";
				cerr << endl << "MESSAGE: " << "Memory copy failed. Destination and source buffers differ";
				return ERROR_MEMORY_COPY;
				
			}
			memset(memDstBuf, 0x00, MEMORY_AMOUNT);
			memset(memSrcBuf, 0x00, MEMORY_AMOUNT);
            percent += 33;
            pRetPercent(percent);
		}
    }
    
    ///getting final score
    *score = round((score1 + score2 + score3) / 3.0);
    //cout << "Final score: " << *score << " points" << endl;
    
    ///memory deallocation
    if(!memSrcBuf)
    {
        delete [] memSrcBuf;
    }
    if(!memDstBuf)
    {
        delete [] memDstBuf;
    }
    
    return NO_ERROR;
}

////////////////////////////////////////////////////////////////////////
