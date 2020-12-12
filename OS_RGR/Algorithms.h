#pragma once
#include <iostream>
#include <list>
#include "Page.h"
#include "CircularList.h"

void secondChanceAlgorithm(const std::list<size_t>& referenced, size_t bufferSize);

void clockAlgorithm(const std::list<size_t>& referenced, size_t bufferSize);