//author: ahmed alhaj
//email : alhaj1@umbc.edu
//proj desctioption: incremental Hashing
//section: Tu/Th 10-11.15





#ifndef _Hash_Table_
#define _Hash_Table_

#include<cstring>
#include<string.h>
#include<cstdlib>
#include<stdio.h>
#include<iostream>
#include<stdexcept>
#include"primes.h"

// x* 4
#define QUADRUPLE(x) ((x<<2))
// x*2
#define DOUBLE(x)   (x<<1)

const int REHASH = 1;
const int NORMAL = 0;












class HashTable{

        public:
		// constructor 
                HashTable(int n =101);
		// copy constructor 
                HashTable(HashTable & other);
		// destructor
                ~HashTable();
		// assigment operator
                const HashTable & operator=(HashTable & rhs);
		// insert(): insert element to the table
                void insert(const char* str);
		// find(): return true if element in the table
                bool find(const char * str );
		// remove(): delete element from the table and set its slot to the delete label
                char* remove(const char * str);
		// insert_element(): allocate memory to the string in its directed table
                void insert_element(char ** container, const char* str, int key);
		// dump(): prints table
                void dump();
		// helper dump(): helps dump() to prints specific table 
                void dump(char ** table, int cap);
		// tigger_cluster_migrate(): checks some codition and and call migrate_cluster()
                void trigger_cluster_migrate(const char * str);
		// clear(): takes specific table and clear it;
                void clear(char ** table, int cap);
		// consalidate_tables(): conbine both table into fat table
                void consalidate_tables(const char *str= NULL);
		// trigger_consalidation() : checks if the table should be combined
                bool trigger_consalidation();
		// migrate_cluster(): transfer cluster to helper table in rehashing mode
                void migrate_cluster(int start_of_cluster, int end_of_cluster);
		// start_of_cluster(): identify and return the start of cluster 
                int start_of_cluster(char** table, int key, int cap);
		// rehashing_probing_pass_threshold(): transpose probing into rehashing mode and moves first cluster to the new table. 
                void rehash_probing_pass_threshold(const char * str, int start_of_cluster, int end_of_cluster=9 );
		// hash_function : calculate the slot based on the hash code
                int hash_function(unsigned int str_value, int cap);
		// hash_code given function
                unsigned int  hash_code(const char *str=NULL);
		// search_for_next empty slot but if pass 10 then it tells me something went wrong.
                int search_next_10(char ** arr , int slot, int cap);
		// search_next_empty same as above but I need it for testing
                int search_next_empty(char ** arr , int slot, int cap);
		// at() return value of the index
                const char* at  (int index, int table=0);
		// return the capacity of the table 
                int tableSize(int table = 0);
		// isRehashing : return the current mode
                bool isRehashing();
		// return the size of table.
		int size(int table = 0);


        private:
                int m_capacity;
                int m_cap1;
                int m_size;
                int MODE;
                static char* const DELETED;
                char **H;
                char **m_table;
                int table_size;

};
#endif

