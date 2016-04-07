// Kontenery
#include <vector>	// Tablica
#include <set>		// Zbiór
#include <map>		// Słownik

// Adaptery
#include <queue>	// Kolejka
#include <stack>	// Stos

#include <iostream>
#include <stdio.h>

#include "Slav.h"

#define REPORT_ADAPTERS showMeAdapterSizes(queueOfSlavs,stackOfSlavs)
#define REPORT_CONTAINERS showMeContainerSizes(vectorOfSlavs,setOfSlavs,mapOfSlavs)

using namespace std;

void showMeContainerSizes(vector <Slav *>, set <Slav *>, map <Slav *, Slav*>);
void showMeAdapterSizes(queue <Slav *>, stack <Slav *>);

void containers(Slav *, int);
void adapters(Slav *, int);

int main(int argc, char const *argv[])
{
	int n = 2 * atoi(argv[1]);
	Slav *slavs = new Slav[n];
	cout << "# Generated Slavs" << endl;
	for (int i = 0; i < n; ++i)
		cout << slavs[i].description() << endl;

	containers(slavs, n);
	adapters(slavs, n);

	delete [] slavs;
}

void containers(Slav * slavs, int n)
{
	vector <Slav *> vectorOfSlavs;
	set <Slav *> setOfSlavs;
	map <Slav *, Slav *> mapOfSlavs;
	
	printf("# Containers\n");
	REPORT_CONTAINERS;
	printf("## vector\n");

	// Umieść Słowian w losowej kolejności w wektorze.
	
	vectorOfSlavs.push_back(slavs);
	for(int i=0;i<n;i++)
	{
		vectorOfSlavs.insert(vectorOfSlavs.begin()+rand() % vectorOfSlavs.size(),(slavs+i));
	}
	vectorOfSlavs.pop_back();


	// Wykorzystując iterator i funkcję description(), wyświetl wszystkich Słowian w wektorze
	
	vector<Slav *>::iterator it_vec=vectorOfSlavs.begin();
	for(;it_vec!=vectorOfSlavs.end();cout<<(**it_vec++).description()<<"\n");

	REPORT_CONTAINERS;
	printf("## set\n");

	// Przenieś wszystkich Słowian z wektoru do zbioru.
	
	for(int i=0;i<n;i++)
	{
		setOfSlavs.insert(vectorOfSlavs[i]);
		vectorOfSlavs.pop_back();
	}
	REPORT_CONTAINERS;
	printf("## map\n");

	// Stwórz słownik tworzący pary Słowian, z tych znajdujących się w zbiorze, czyszcząc zbiór
	
	for(set<Slav*>::iterator it_set=setOfSlavs.begin();it_set!=setOfSlavs.end();)
	{
		mapOfSlavs[*it_set]=*(++it_set);
		setOfSlavs.erase(--it_set);
		it_set++;
		setOfSlavs.erase(it_set++);
	}


	// Wykorzystując iterator, wyświetl wszystkie pary Słowian
	
	for(map<Slav*,Slav*>::iterator it_map=mapOfSlavs.begin();it_map!=mapOfSlavs.end();it_map++)
		cout<<it_map->first->description()<<"\t"<<it_map->second->description()<<"\n";
	REPORT_CONTAINERS;


	map<Sex,vector<Slav*>> mapBySex;
	for(int i=0;i<n;i++)
	{
		slavs[i].sex()==male ? mapBySex[male].push_back(slavs+i):
							mapBySex[female].push_back(slavs+i); 
	}

	cout<<"\n\n\nMen:\n";
	for(int i=0;i<mapBySex[male].size();i++)
	{
		cout<<mapBySex[male][i]->description()<<"\n";
	}

	cout<<"\n\n\nWomen:\n";
	for(int i=0;i<mapBySex[female].size();i++)
	{
		cout<<mapBySex[female][i]->description()<<"\n";
	}
}

void adapters(Slav * slavs, int n)
{
	queue <Slav *> queueOfSlavs;
	stack <Slav *> stackOfSlavs;

	printf("# Adapters\n");
	REPORT_ADAPTERS;
	printf("## queue\n");

	// Umieść Słowian w kolejce.
	
	for(int i=0;i<n;i++)
		queueOfSlavs.push(slavs+i);

	REPORT_ADAPTERS;

	printf("## stack\n");
	// Przenieś Słowian z kolejki do stosu.

	while(!queueOfSlavs.empty())
	{
		stackOfSlavs.push(queueOfSlavs.front());
		queueOfSlavs.pop();
	}

	REPORT_ADAPTERS;

	// Wyświetl Słowian zdejmowanych ze stosu.

	while(!stackOfSlavs.empty())
	{
		cout<<stackOfSlavs.top()->description()<<"\n";
		stackOfSlavs.pop();
	}

	REPORT_ADAPTERS;
}

void showMeContainerSizes(vector <Slav *> vector, set <Slav *> set, map <Slav *, Slav*> map)
{
	printf("[vector_size = %lu, set_size = %lu, map_size = %lu, existingSlavs = %i]\n",
		vector.size(),
		set.size(),
		map.size(),
		Slav::counter());
}

void showMeAdapterSizes(queue <Slav *> queue, stack <Slav *> stack)
{
	printf("[queue_size = %lu, stack_size = %lu, existingSlavs = %i]\n",
		queue.size(),
		stack.size(),
		Slav::counter());

}
