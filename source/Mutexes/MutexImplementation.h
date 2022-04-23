/**
 * @file MutexImplementation.h
 * @author Ricardo Alejos (ricardoalejos20@gmail.com)
 * @brief 
 *      Provides means to create concrete implementations of the Mutex
 *      interface.
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef _MUTEXES_MUTEX_IMPLEMENTATION_H_
#define _MUTEXES_MUTEX_IMPLEMENTATION_H_

#include "Mutexes/Mutex.h"

struct MutexInterface {
    MutexErrorCode (*take)(Mutex * mutex);
    MutexErrorCode (*release)(Mutex * mutex);
};

struct MutexStructure {
    /**
     * @brief Points to a concrete and invariant implementation of the Mutex
     * interface.
     */
    struct MutexInterface const * implementationInterface;

    /**
     * @brief Contains the address of the structure holding the private members
     * of the Mutex implementation.
     */
    Mutex * instanceData;
};

#endif
