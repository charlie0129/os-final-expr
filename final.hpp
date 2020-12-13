#pragma once
#include <fstream>
#include <thread>
#include "item.hpp"
#include "customer.hpp"
#include<string>
#include<mutex>
#include <semaphore.h>
#define MAX_CUSTOMER 10

#define BLUE_BOLD_TEXT "\033[1;34m"
#define RED_BOLD_TEXT "\033[1;31m"
#define GREEN_BOLD_TEXT "\033[1;32m"
#define REMOVE_TEXT_ATTR "\033[0m"
#define BLUE_LEADING_ARROW "\033[1;34m=> \033[0m"