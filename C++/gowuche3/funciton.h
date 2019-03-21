#ifndef FUNCITON_H
#define FUNCITON_H
#include "commoditymanager.h"
#include <string>
char menu();
// To get the function
void judge(char c, commoditymanager &cm);
// add commodity
void doaddcommodity(commoditymanager &cm);
// to show the commodities
void showallcommodity(commoditymanager &cm);
// to delete one commodity
void removecommodity(commoditymanager &cm);
// to output the check out
void docheckout(const commoditymanager &cm);
// to show one commodity
void doshowcommodity(const commoditymanager &cm);
// File handlers
void readFromFile(const std::string &filename, commoditymanager &cm);
bool writefile(std::string filename, commoditymanager &cm);

#endif // FUNCITON_H
