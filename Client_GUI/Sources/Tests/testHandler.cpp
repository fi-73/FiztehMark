//      Name: testHandler.cpp
//
//      Description: class that gives an interface to run test
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

#include "testHandler.h"
#include <iostream>

TestHandler::TestHandler(void (*pSetPercent)(int))
{
    testIter = testMap.begin();
    scoreIter = scoreMap.begin();
    pSetPercentDone = pSetPercent;
    errorCode = 0;
}

unsigned int TestHandler::getTestScore()
{
    if(scoreIter != scoreMap.end())
        return scoreIter->second;
    else
        return 0;
}

QString TestHandler::getTestName()
{
    if(testIter != testMap.end())
        return testIter->first;
    else
        return "";
}

bool TestHandler::runTest()
{
    if(testMap.empty() || testIter == testMap.end())
    {
        return false;
    }
    unsigned int score = 0;
    errorCode = testIter->second(&score,pSetPercentDone);
    scoreIter->second = score;
    if(errorCode)
    {
        scoreIter->second = 0;
    }
    return true;
}

bool TestHandler::nextTest()
{
    if(testMap.empty() || testIter == testMap.end())
    {
        return false;
    }
    testIter++;
    scoreIter++;
    if(testIter == testMap.end())
        return false;
    return true;
}

void TestHandler::addTest(QString name,unsigned int (*pGetScore)(unsigned int*, void(*pFunc)(int)))
{
    testMap[name] = pGetScore;
    scoreMap[name] = 0;
    testIter = testMap.begin();
    scoreIter = scoreMap.begin();
}
