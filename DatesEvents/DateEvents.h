#include "Date.h"

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm> 
#include <map>
#include <sstream> //stream string
using namespace std;

#pragma once


class DatesEvents
{
public:

	//Äîáàâëåíèå ñîáûòèÿ äëÿ îïðåäåëåííîé äàòû
	void AddDateEvent(Date&_date, string event, string path);

	//Óäàëåíèå îäíîãî ñîáûòèÿ ó âûáðàííîé äàòû
	void DeletEventDate(Date&_date, string& event, string path);

	//Óäàëåíèå âûáðàííîé äàòû âìåñòå ñî âñåìè ñîáûòèÿìè
	void DeleteDate(Date&_date, string path);

	//Ïîèñê äàòû è âûâîä âñåõ å¸ ñîáûòèé (çàðàíåå îòñîðòèðîâûâàííûõ)
	void findDateEvents(const Date& _date);
	
	//Çàãðóçêà äàííûõ èç ôàéëà â ñëîâàðü
	void LoadDataFileInMap(const string& path);

	//Îáíîâèòü ïîðÿäîê äàò è ñîáûòèé ôàéëà â ñîîòâåòñòâèè ñî ñëîâàðåì
	void UpdateTextFile(const string& path);
	
private:
	map<Date, vector<string>> DateEvents;
};
