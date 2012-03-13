//      Name: testHandler.h
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

#ifndef TESTHANDLER_H
#define TESTHANDLER_H

//////////////////////////////////////////////////////////////////////////
// Include libraries
//////////////////////////////////////////////////////////////////////////

#include <QObject>
#include <map>
#include <QString>

using namespace std;

//////////////////////////////////////////////////////////////////////////
// Include test sources
//////////////////////////////////////////////////////////////////////////

#include "Tests/MemCpyTest/memCpyTest.h"

//////////////////////////////////////////////////////////////////////////

/**
 * @class   TestHandler
 * @brief   Stores tests and their scores, runs available tests
 *
 *   Copyright 2012 Vitaliy Sergienko <visergienko@ukr.net>
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 *   MA 02110-1301, USA.
 */
class TestHandler
{
public:

    /**
     * @brief           Class constructor
     * @param[in]       pSetPercent     pointer to the function that changes test progress percent
     * @return          new class object
     */
    TestHandler(void (*pSetPercent)(int));

    /**
     * @brief           Getting current test score
     * @precondition    current test exists and was executed
     * @return          current test score
     */
    unsigned int getTestScore();

    /**
     * @brief           Getting overall test score
     * @precondition    at least one test exists and was executed
     * @return          overall test score
     */
    unsigned int getOverallScore();

    /**
     * @brief           Getting error code
     * @precondition    test was executed
     * @return          current test error code
     */
    unsigned int getErrorCode(){return errorCode;}

    /**
     * @brief           Getting current test name
     * @precondition    current test exists (was added previously)
     * @return          current test name
     */
    QString getTestName();

    /**
     * @brief           Getting number of tests available
     * @return          number of tests
     */
    unsigned int getTestCount(){return testMap.size();}

    /**
     * @brief           Adding new test
     * @param[in]       s           test name
     * @param[in]       pGetScore   pointer to test function
     */
    void addTest(QString s, unsigned int (*pGetScore)(unsigned int*, void(*pFunc)(int)));

    /**
     * @brief           Executing current test
     * @precondition    current test exists (was added previously)
     * @return          TRUE if current test exists; else FALSE
     */
    bool runTest();

    /**
     * @brief           Switching to next test
     * @precondition    next test exists (was added previously)
     * @return          TRUE if next test exists; else FALSE
     */
    bool nextTest();

    /**
     * @brief           Automatically adds all tests declared in TEST_SET
     * @remark          TEST_SET itself is declared in TestHandler.cpp
     */
    void autoLoadTests();

private:

    map<QString, unsigned (*)(unsigned int*,void(*)(int))> testMap; /**< map storing test names and pointers
                                                                         to corresponding test functions */
    map<QString, unsigned (*)(unsigned int*,void(*)(int))>::iterator testIter; /**< iterator for testMap */

    map<QString, unsigned int> scoreMap; /**< map storing test names and corresponding test results */
    map<QString, unsigned int>::iterator scoreIter; /**< iterator for scoreMap */

    void (*pSetPercentDone)(int); /**< pointer to the function that changes test progress percent */

    unsigned int errorCode; /**< current test error code */
};

#endif // TESTHANDLER_H
