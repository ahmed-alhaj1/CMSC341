#include"HashTable.h"
#include <unistd.h>
//I am trynna comment but it already 10 clock
//the code is poorly written because I really did not understand the proj description
//so I sort the synthize the rule from the test_files.
// there is one case in proj description that not being addressed in remove and find but it address only in insert which is when the rehash sequence grow to long then consalidate that why test4 will have some issue. 


// constructor

HashTable::HashTable(int n){
	printf("I am at the constructor \n");
	m_size = 0;
	table_size= 1;
	m_capacity = n;
	MODE = NORMAL;
	H = (char** ) malloc(m_capacity * sizeof(char * ));

	for(int i=0; i< m_capacity ; i++){
		H[i] = NULL;
		}
}

//destructor :: deos not wrok fine I dont know but messes up when consaldtion() invoked 

HashTable::~HashTable(){
	
	if(m_size > 0){
		clear(H, m_capacity);
	}
	if(table_size > 1 ){
		clear(m_table , m_cap1);
	}
	

}

// copy constructor
//
HashTable::HashTable(HashTable & other ){
	if(this != &other){
		m_capacity = other.m_capacity ;	
		m_size = other.m_size ;
		m_cap1 = other.m_cap1;
		table_size = other.table_size;
		MODE = other.MODE;

		          H = (char**) malloc(m_capacity * sizeof(char *));

                        for(int i = 0; i < m_capacity ; i++ ){
                                if(other.H[i] == NULL){
                                        H[i] = NULL;
                                }else if(other.H[i] == DELETED){
                                        H[i] = DELETED;
                                }else{
                                        H[i] = (char*)malloc(strlen(other.H[i])+1);
                                        strcpy(H[i], other.H[i]);
                                        //printf("H[%d] = %s \n" ,i, H[i] );
                                }
                        }
                if(m_cap1 > 0 && MODE == REHASH){
                        m_table = (char**)malloc(m_cap1 * sizeof(char*));
                        //printf("dealing with rehash mode \n");
                        for(int i = 0; i < m_cap1; i++){
                                if(other.m_table[i] == NULL ){
                                        m_table[i] = NULL;
                                }else if(other.m_table[i] == DELETED ){
                                        m_table[i] = DELETED;
                                }else{
                                        m_table[i] = (char*)malloc(strlen(other.m_table[i])+1);
                                        strcpy(m_table[i], other.m_table[i]);
                                        //printf("m_table[%d] = %s \n", i, m_table[i]);
                                }

                        }
                }
        }
}
		

// assigment operator

const HashTable & HashTable::operator=(HashTable & rhs){
    if(this != & rhs){	
	//clear memory
	for(int i = 0 ; i < m_capacity; i++ ){
                free(H[i]);
	}
        free(H);
        for(int i= 0 ; i< m_cap1; i++){
		free(m_table[i]);
                }
        free(m_table);
                m_capacity = rhs.m_capacity ;
                m_size = rhs.m_size ;
                m_cap1 = rhs.m_cap1;
                table_size = rhs.table_size;
                MODE = rhs.MODE;
	//allocate and copy 
                H = (char**) malloc(m_capacity * sizeof(char *));

                        for(int i = 0; i < m_capacity ; i++ ){
                                if(rhs.H[i] == NULL){
                                        H[i] = NULL;
                                }else if(rhs.H[i] == DELETED){
                                        H[i] = DELETED;
                                }else{
                                        H[i] = (char*)malloc(strlen(rhs.H[i])+1);
                                        strcpy(H[i], rhs.H[i]);
                                }
                        }
                if(m_cap1 > 0 && MODE == REHASH){
                        m_table = (char**)malloc(m_cap1 * sizeof(char*));
                        for(int i = 0; i < m_cap1; i++){
                                if(rhs.m_table[i] == NULL ){
                                        m_table[i] = NULL;
                                }else if(rhs.m_table[i] == DELETED ){
                                        m_table[i] = DELETED;
                                }else{
                                        m_table[i] = (char*)malloc(strlen(rhs.m_table[i])+1);
                                        strcpy(m_table[i], rhs.m_table[i]);
                                }

                        }
                }

      }
}

			

// constant label
char* const HashTable::DELETED = (char * )&DELETED;


// clear() clear specified tables
void HashTable::clear(char ** table, int cap){
	for(int i =0;i<cap ;i++){
		
			
		if(table[i] != NULL && table[i] != DELETED  ){
			free(table[i]);
		}
		//table[i] = NULL;
	}
	free(table);
	table = NULL;

}
void HashTable::dump(){
	printf("------------------- table#1 ------------------- table_size = %d  size = %d \n", m_capacity , m_size );
	dump(H, m_capacity);
	if(MODE == REHASH){
		printf("------------------- table#2------------------- table_size = %d  size = %d \n", m_cap1 , table_size );

	dump(m_table, m_cap1);
	}
}
void HashTable::dump( char** table, int cap){
	for(int i = 0 ; i < cap ; i++){
		if(table[i] == DELETED ){
			printf("H[%d] = DELETED \n", i);

		}else if( table[i] != NULL){
			printf("H[%d] = %s (%d)\n", i, table[i], hash_function(hash_code(table[i]), cap));
		}else{
			printf("H[%d] = \t\n",i );
		}
	}

}

void HashTable::rehash_probing_pass_threshold(const char* str, int start_of_cluster, int end_of_cluster){
	int tot_size = m_size + table_size ;
	m_cap1 = QUADRUPLE(tot_size);
	m_cap1 = roundUpPrime(m_cap1);
	m_table = (char**)malloc(m_cap1 *sizeof(char *));
	for(int i = 0 ; i < m_cap1; i++){
		m_table[i] = NULL;
	}

	int ratio = (start_of_cluster > end_of_cluster) ? ((m_capacity-start_of_cluster) + end_of_cluster ) : (end_of_cluster - start_of_cluster);
	for(int i = 0, j= start_of_cluster; i <ratio ;  i++, j = (j+1) % m_capacity){
		int slot = search_next_empty(m_table,hash_function(hash_code(H[j]), m_cap1), m_cap1);
	
		insert_element(m_table, H[j], slot);
		
		free(H[j]);
		H[j]= NULL;
		table_size++;
		m_size--;
	}
	if(str != NULL && str != DELETED){
		table_size++;
		insert_element(m_table, str, search_next_empty(m_table, hash_function(hash_code(str), m_cap1),m_cap1));
}



}
//########################################################
void HashTable::migrate_cluster(int start_of_cluster, int end_of_cluster){
	int slot;
	int ratio = (start_of_cluster > end_of_cluster) ? ((m_capacity-start_of_cluster) + end_of_cluster ) : (end_of_cluster - start_of_cluster);
	for(int i = 0, j= start_of_cluster; i <ratio ;  i++, j = (j+1) % m_capacity){
		if(H[j] != DELETED && H[j] != NULL){
			slot = search_next_empty(m_table,hash_function(hash_code(H[j]), m_cap1), m_cap1);

			insert_element(m_table, H[j], slot);
				free(H[j]);
				H[j]= NULL;
				table_size++;
				m_size--;

	
		}
		
	}


}
//############################################################

void HashTable::consalidate_tables(const char *str){
	if(m_size == 0 ){
		clear(H, m_capacity);
		H = m_table;
		m_size = table_size;
		m_capacity = m_cap1;
		m_cap1 = 0;
		table_size = 1;
		MODE = NORMAL;
		return ;
	
	}
	int old_cap = m_capacity, old_size = m_size ; 
	m_capacity  = QUADRUPLE((m_size+table_size));
	m_capacity = roundUpPrime(m_capacity);
	m_size = 0;
	char **table = (char**)malloc(m_capacity *sizeof(char*));

	for(int i = 0  ; i < m_capacity ; i++){
		table[i] = NULL;
	}
	if(old_size > 0 ){
	for(int i =0; i < old_cap ; i++){
		if(H[i] != NULL && H[i] != DELETED){
			
			int str_value = hash_code(H[i]);
			int key = search_next_10(table, hash_function( str_value, m_capacity ), m_capacity );
			if(key != m_capacity){
				printf("H[%d] = %s \n", i, H[i]);
				insert_element(table, H[i], key);
				free(H[i]);
				H[i] = NULL;
				old_size--;
				m_size++;
		
			}else{
			printf("ther is some error \n");
			}
	
		}
	}

	}
	if(table_size > 1 && MODE == REHASH){
		for(int i = 0 ; i < m_cap1;i++ ){
			if(m_table[i] != NULL && m_table[i] != DELETED ){
				int st_value = hash_function(hash_code(m_table[i]), m_capacity);
				int key = search_next_10(table, st_value ,m_capacity);
				insert_element(table, m_table[i], key);
				free(m_table[i]);
				m_table[i] = NULL;
				m_size++;
				table_size--;

			}
		}
	}
	if(str != NULL){
	int pre_key = hash_function(hash_code(str), m_capacity); 
	int nkey = search_next_10(table, pre_key, m_capacity);
	insert_element(table, str, nkey);
		m_size++;
	}
	free(H);
	free(m_table);
	table_size = 1;
	H = table;

	MODE = NORMAL;
}
//#####################################################################
int HashTable::search_next_empty(char ** arr, int slot, int cap){
	int max_shift = cap;
	for(int i = 0, j = slot; i < max_shift; i++, j =((j+1) % cap)){
			if(arr[j] == NULL || arr[j] == DELETED){

				return j;
			}

	}
	return cap;
}

//#############################################################3
int HashTable::search_next_10(char ** arr, int slot, int cap){
	int max_shift = 9;
	for(int i = 0, j = slot; i < max_shift; i++, j =((j+1) % cap)){
			if(arr[j] == NULL || arr[j] == DELETED ){
				return j;
			}
	}
	return cap;
}
//#########################################################

bool HashTable::trigger_consalidation(){
	if(MODE == REHASH ){
		float max_load = 0.5, min_percent = 0.03;
		float load_factor, min_size ;

		load_factor  = ((float)table_size / (float)m_cap1 ) ;
		min_size = ((float)m_size / ((float)m_size+ (float)table_size));
		return ( load_factor > max_load ||  min_size < min_percent  ) ? true : false; 

	}
	return false;
}
///##########################################################

char* HashTable::remove(const char *str){
	if(!!trigger_consalidation()) {
		//printf("there is consalidation heppening \n");
		consalidate_tables();
}
		
	//printf("I am at remove str = %s \n", str);
	unsigned int key = hash_function(hash_code(str), m_capacity);
	if(m_size > 0 ){
		//printf("I am at normal mode \n");
		if(H[key] == NULL && MODE == NORMAL) return NULL;
		for(int i =0, j = key ; i < 10 ; i++, j = (j+1) % m_capacity ){
			if(i > 9 && MODE == NORMAL ){
					rehash_probing_pass_threshold(str=NULL,hash_function(hash_code(str), m_capacity), hash_function(hash_code(str),m_capacity)+9);

			}
			if(H[j] != NULL && H[j] != DELETED ){
			
				if(strcmp(str, H[j]) == 0  ){
					char elem[strlen(H[j])] ;
					strcpy(elem, H[j]);
					free(H[j]);

					H[j] = DELETED;

					m_size--;
					return elem ;
			
				}
			}
		}
	}
	if(MODE == REHASH & table_size > 1){
		//printf("I am at rehash mode \n");
		trigger_cluster_migrate(str);
		int keyx = hash_function(hash_code(str), m_cap1);

		for(int i = 0 , j = keyx; i < m_cap1; i++, (j+1)%m_cap1 ){	
			if(m_table[j] != NULL && m_table[j] != DELETED ){
				if(strcmp(str, m_table[j]) ==0){
					char elem[strlen(m_table[j])];
					strcpy(elem, m_table[j]);
					free(m_table[j]);
					m_table[j] = DELETED;
					table_size--;
				
				return elem;
				
				}
			}	
		
	}
	}
	//printf("return null\n");
	return NULL;


}
//##################################################################
void HashTable::insert_element(char ** container, const char * str, int key ){
	container[key] = (char* )malloc(strlen(str)+1);
	strcpy(container[key], str);

}
//###########################################################
int HashTable::hash_function(unsigned int str_value, int cap ){
	return (str_value % cap) ;
}
//###########################################################
unsigned int HashTable::hash_code(const char *str){
	unsigned int value = 0;
	const unsigned int thirtyThree =33;
	int i = 0;
	while(str[i] != '\0'){
		value = value * thirtyThree + str[i];
		i++;
	}
	return value ;
}
//######################################################

int HashTable::start_of_cluster(char** table , int key, int cap){
	for(int i = 0, j = key; i < cap ; i++ , j = (j-1)% cap ){
		if(table[j] == NULL){
			return 1+j;
		}
	}
}
//######################################################
bool HashTable::find(const char * str){
	if(!!trigger_consalidation() && MODE == REHASH ) consalidate_tables();
		
	int key  = hash_function(hash_code(str), m_capacity);
	if(MODE == NORMAL){
		for(int i = 0, j= key ; i < m_capacity ; i++, j = (j+1) % m_capacity ){

			if(H[key] ==NULL && key < 9) return false;
			if(H[j] != NULL ){
				if(strcmp(H[j], str) == 0){
				if(i > 10){
				rehash_probing_pass_threshold(str,hash_function(hash_code(str), m_capacity), hash_function(hash_code(str),m_capacity)+9);
				MODE = REHASH;
	
				}
				return  true ;
				}
			}	
			}
		}else{
			int keyx  = hash_function(hash_code(str), m_cap1);
			trigger_cluster_migrate(str);
			for(int i = 0 , j= key ; i < m_cap1 ; i++, j = (j+1) % m_cap1 )					{		


				keyx  = hash_function(hash_code(str), m_cap1);
				if( (H[key] == NULL || H[key] == DELETED )  && (m_table[keyx] == NULL || m_table[keyx] == DELETED )) return false;
				if( j < m_capacity ){
					if(H[j] != NULL ){
						if(strcmp(H[j], str) == 0){
							return  true ;
						}
					}
				}
				if(m_table[j] != NULL){
					if(strcmp(m_table[j], str) == 0){
						return true;
						}
		
					}

				}	
			}	

	return false;
}



//###########################################################
//###########################################################
void  HashTable::insert(const char *str){
	if(!!trigger_consalidation()) consalidate_tables();
	if(MODE == NORMAL){
		int key = search_next_10(H, hash_function(hash_code(str), m_capacity), m_capacity);
		if(key == m_capacity ){
			MODE = REHASH;
			rehash_probing_pass_threshold(str,hash_function(hash_code(str), m_capacity), hash_function(hash_code(str),m_capacity)+9);
				return;
			
		}
	

		key = search_next_10(H, hash_function(hash_code(str), m_capacity), m_capacity);
		m_size++;
		insert_element(H, str, key);
	}else{
		trigger_cluster_migrate(str);
		int init_key  = hash_function(hash_code(str), m_cap1);
		int key = search_next_empty(m_table, init_key , m_cap1);
		if((key - init_key) > 9 ){
			consalidate_tables(str);
			return ;
			}
		if(key == m_cap1) throw std::out_of_range("something went wrong int insert hrehash mode ");
		//printf("key = %d \n", key);
		table_size++;
		insert_element(m_table, str, key);

	}
}



//################################################################
//################################################################

void HashTable::trigger_cluster_migrate(const char *str){
		//printf("m_size = %d , table_size %d \n", m_size , table_size);
	int start_cluster = start_of_cluster(H, hash_function(hash_code(str),m_capacity),m_capacity);
	int end_cluster = search_next_empty(H, hash_function(hash_code(str), m_capacity), m_capacity);
	unsigned int ratio = (start_cluster > end_cluster )? (start_cluster - end_cluster) : (end_cluster - start_cluster) ;
		//printf("start_cluster = %d end_of_cluster = %d  (end-start ) = %d \n" , start_cluster ,end_cluster, ratio);

		if( ratio > 1 ){
			//printf("trigger migrate cluster  \n");
			migrate_cluster(start_cluster, end_cluster);
			}
			

}

bool HashTable::isRehashing(){

	return MODE;

}


int HashTable::tableSize(int table ){
	return (table == 0 ) ? m_capacity : m_cap1;
}

int HashTable::size(int table){
	return (table == 0 )? m_size : table_size-1;

}

const char* HashTable::at(int index, int table){
	return (table == 0)? H[index] : m_table[index];
}
