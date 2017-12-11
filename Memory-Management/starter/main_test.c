/**
  * ECE254 Linux Dynamic Memory Management Lab
  * @file: main_test.c
  * @brief: The main file to write tests of memory allocation algorithms
  */ 

/* includes */
/* system provided header files. You may add more */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <error.h>

/* non-system provided header files. 
   Do not include more user-defined header files here
 */
#include "mem.h"

int bf_allocate_deallocate_works()
{
	if(best_fit_memory_init(4096)) {
        perror("Fail to create a chunck of memory");
        return -1;
    }
    
	//allocate
	void* _110_bf = best_fit_alloc(110);
	void* _220_bf = best_fit_alloc(220);
	void* _330_bf = best_fit_alloc(330);
	void* _440_bf = best_fit_alloc(440);
	void* _550_bf = best_fit_alloc(550);

	//deallocate
	best_fit_dealloc(_110_bf);
	best_fit_dealloc(_220_bf);
	best_fit_dealloc(_330_bf);
	best_fit_dealloc(_440_bf);
	best_fit_dealloc(_550_bf);

	//alloacte agian
	void* _150_bf = best_fit_alloc(150);
	void* _250_bf = best_fit_alloc(250);
	void* _350_bf = best_fit_alloc(350);
	void* _450_bf = best_fit_alloc(450);
	void* _650_bf = best_fit_alloc(650);

	//deallocate
	best_fit_dealloc(_150_bf);
	best_fit_dealloc(_250_bf);
	best_fit_dealloc(_350_bf);
	best_fit_dealloc(_450_bf);
	best_fit_dealloc(_650_bf);

	return 0;
}

int wf_allocate_deallocate_works()
{
	if(worst_fit_memory_init(2048)) {
		perror("Fail to create a chunck of memory");
		return -1;
	}
	
	//allocate
	void* _110_wf = worst_fit_alloc(110);
	void* _220_wf = worst_fit_alloc(220);
	void* _330_wf = worst_fit_alloc(330);
	void* _440_wf = worst_fit_alloc(440);
	void* _550_wf = worst_fit_alloc(550);
	
	//deallocate
	worst_fit_dealloc(_110_wf);
	worst_fit_dealloc(_220_wf);
	worst_fit_dealloc(_330_wf);
	worst_fit_dealloc(_440_wf);
	worst_fit_dealloc(_550_wf);

	//allocate again
	void* _150_wf = worst_fit_alloc(150);
	void* _250_wf = worst_fit_alloc(250);
	void* _350_wf = worst_fit_alloc(250);
	void* _450_wf = worst_fit_alloc(450);
	void* _650_wf = worst_fit_alloc(650);

	//deallocate 
	worst_fit_dealloc(_150_wf);
	worst_fit_dealloc(_250_wf);
	worst_fit_dealloc(_350_wf);
	worst_fit_dealloc(_450_wf);
	worst_fit_dealloc(_650_wf);
	return 0;
}

int bf_find_block_test(){
	if(best_fit_memory_init(4096)) {
		perror("Fail to create a chunck of memory");
		return -1;
	}
	
	void* _110_bf = best_fit_alloc(110);
	void* _220_bf = best_fit_alloc(220);
	void* _330_bf = best_fit_alloc(330);
	void* _440_bf = best_fit_alloc(440);
	void* _550_bf = best_fit_alloc(550);
	
	//to deallocate without coalescence
	best_fit_dealloc(_220_bf);
	best_fit_dealloc(_440_bf);

	//should be alloacted in the 220 block and split this node
	//and assigned number should be rounded to 8
	void* _6_bf = best_fit_alloc(6);
	
	//deallocate all, should have one node now
	best_fit_dealloc(_110_bf);
	best_fit_dealloc(_330_bf);
	best_fit_dealloc(_550_bf);
	best_fit_dealloc(_6_bf);
	
	return 0;
}

int wf_find_block_test(){
	if(worst_fit_memory_init(2048)) {
		perror("Fail to create a chunck of memory");
		return -1;
	}
	
	
	void* _110_wf = worst_fit_alloc(110);
	void* _220_wf = worst_fit_alloc(220);
	void* _330_wf = worst_fit_alloc(330);
	void* _440_wf = worst_fit_alloc(440);
	void* _550_wf = worst_fit_alloc(550);
	
	//to deallocate without coalescence
	worst_fit_dealloc(_220_wf);
	worst_fit_dealloc(_440_wf);
	
	//should be alloacted in the last block and split this node
	//number should be rounded to 8
	void* _6_wf = worst_fit_alloc(6);

	
	//deallocate all, should have one node now
	worst_fit_dealloc(_110_wf);
	worst_fit_dealloc(_330_wf);
	worst_fit_dealloc(_550_wf);
	worst_fit_dealloc(_6_wf);

	return 0;
}

int bf_coalesce_test(){
	if(best_fit_memory_init(4096)) {
		perror("Fail to create a chunck of memory");
		return -1;
	}
	
	void* _110_bf = best_fit_alloc(110);
	void* _220_bf = best_fit_alloc(220);
	void* _330_bf = best_fit_alloc(330);
	void* _440_bf = best_fit_alloc(440);
	void* _550_bf = best_fit_alloc(550);
	
	/*middle node*/
	//coalesce previous
	best_fit_dealloc(_220_bf);
	best_fit_dealloc(_330_bf);

	//revert changes
	_220_bf = best_fit_alloc(220);
	_330_bf = best_fit_alloc(330);

	//coalesce nest
	best_fit_dealloc(_330_bf);
	best_fit_dealloc(_220_bf);

	//revert changes
	_220_bf = best_fit_alloc(220);
	_330_bf = best_fit_alloc(330);

	//coalesce previous and next
	best_fit_dealloc(_220_bf);
	best_fit_dealloc(_440_bf);
	best_fit_dealloc(_330_bf);

	//revert changes
	_220_bf = best_fit_alloc(220);
	_330_bf = best_fit_alloc(330);
	_440_bf = best_fit_alloc(440);

	/*last node*/
	//coalesce previous
	best_fit_dealloc(_440_bf);
	best_fit_dealloc(_550_bf);

	//revert changes
	_440_bf = best_fit_alloc(440);
	_550_bf = best_fit_alloc(550);

	//coalesce next
	best_fit_dealloc(_550_bf);
	best_fit_dealloc(_440_bf);
    
	//revert changes
	_440_bf = best_fit_alloc(440);
	_550_bf = best_fit_alloc(550);


	//deallocate all
	best_fit_dealloc(_110_bf);
	best_fit_dealloc(_220_bf);
	best_fit_dealloc(_330_bf);
	best_fit_dealloc(_440_bf);
	best_fit_dealloc(_550_bf);
	
	return 0;
}

int wf_coalesce_test(){
	if(worst_fit_memory_init(2048)) {
		perror("Fail to create a chunck of memory");
		return -1;
	}
	
	void* _110_wf = worst_fit_alloc(110);
	void* _220_wf = worst_fit_alloc(220);
	void* _330_wf = worst_fit_alloc(330);
	void* _440_wf = worst_fit_alloc(440);
	void* _550_wf = worst_fit_alloc(550);

	
	/*middle node*/
	//coalesce previous
	worst_fit_dealloc(_220_wf);
	worst_fit_dealloc(_330_wf);

	//revert changes
	_220_wf = worst_fit_alloc(220);
	_330_wf = worst_fit_alloc(330);

	//coalesce nest
	worst_fit_dealloc(_330_wf);
	worst_fit_dealloc(_220_wf);

	//revert changes
	_220_wf = worst_fit_alloc(220);
	_330_wf = worst_fit_alloc(330);

	//coalesce previous and next
	worst_fit_dealloc(_220_wf);
	worst_fit_dealloc(_440_wf);
	worst_fit_dealloc(_330_wf);

	//revert changes
	_220_wf = worst_fit_alloc(220);
	_330_wf = worst_fit_alloc(330);
	_440_wf = worst_fit_alloc(440);
	

	/*last node*/
	//coalesce previous
	worst_fit_dealloc(_440_wf);
	worst_fit_dealloc(_550_wf);
    
	//revert changes
	_440_wf = worst_fit_alloc(440);
	_550_wf = worst_fit_alloc(550);
    
	//coalesce next
	worst_fit_dealloc(_550_wf);
	worst_fit_dealloc(_440_wf);
    
	//revert changes
	_440_wf = worst_fit_alloc(440);
	_550_wf = worst_fit_alloc(550);


	//deallocate all
	worst_fit_dealloc(_110_wf);
	worst_fit_dealloc(_220_wf);
	worst_fit_dealloc(_330_wf);
	worst_fit_dealloc(_440_wf);
	worst_fit_dealloc(_550_wf);

	return 0;
}


int bf_allocate_loop() {
	
	if(best_fit_memory_init(1500)) {
		perror("Fail to create a chunck of memory");
		return -1;
	}
	
    for(;;)
	{
		
		void* _50_st = best_fit_alloc(50);
		if (!_50_st)
			break;
		
		void* _150_nd = best_fit_alloc(150);
		if (!_150_nd)
			break;
		
		void* _250_rd = best_fit_alloc(250);
		if (!_250_rd)
			break;
		
		void* _350_th = best_fit_alloc(350);
		if (!_350_th)
			break;
        
		best_fit_dealloc(_250_rd );
		best_fit_dealloc(_150_nd );

	}

    int i = 0;
	for(i = 100; i <= 400; i += 100) {
		printf("External Fragmentation(s) with size less than %d bytes : %d\n", i, best_fit_count_extfrag(i));
	}
	return 0;
}

int bf_allocate() {
    
    if(best_fit_memory_init(3000)) {
        perror("Fail to create a chunck of memory");
        return -1;
    }
    
    int rand1 = rand() % 512 + 1;
    int rand2 = rand() % 512 + 1;
    int rand3 = rand() % 512 + 1;
    int rand4 = rand() % 512 + 1;
    int rand5 = rand() % 512 + 1;
    int rand6 = rand() % 512 + 1;
    int rand7 = rand() % 512 + 1;
    int rand8 = rand() % 512 + 1;
    
    for(;;)
    {
        
        void* chuck1 = best_fit_alloc(rand1);
        if (!chuck1)
            break;
        
        void* chuck2 = best_fit_alloc(rand2);
        if (!chuck2)
            break;
        
        void* chuck3 = best_fit_alloc(rand3);
        if (!chuck3)
            break;
        
        void* chuck4 = best_fit_alloc(rand4);
        if (!chuck4)
            break;
        
        void* chuck5 = best_fit_alloc(rand5);
        if (!chuck5)
            break;
        
        void* chuck6 = best_fit_alloc(rand6);
        if (!chuck6)
            break;
        
        void* chuck7 = best_fit_alloc(rand7);
        if (!chuck7)
            break;
        
        void* chuck8 = best_fit_alloc(rand8);
        if (!chuck8)
            break;
        
        best_fit_dealloc(chuck3);
        best_fit_dealloc(chuck2);
        best_fit_dealloc(chuck6);
        best_fit_dealloc(chuck7);
        
    }
    int i = 0;
    for(i = 100; i <= 600; i += 100) {
        printf("%d, ", best_fit_count_extfrag(i));
    }
    printf("\n");
    return 0;
}
void bf_extfrag_test(){

    int counter = 0;
    while(counter < 10){
        bf_allocate();
        counter++;
    }
}



int wf_allocate_loop() {
	
	if(worst_fit_memory_init(1500)) {
		perror("Fail to create a chunck of memory");
		return -1;
	}
	
	
    for(;;)
	{
		
		void* _50_st = worst_fit_alloc(50);
		if (!_50_st)
			break;
		
		void* _150_nd = worst_fit_alloc(150);
		if (!_150_nd)
			break;
		
		void* _250_rd = worst_fit_alloc(250);
		if (!_250_rd)
			break;
		
		void* _350_th = worst_fit_alloc(350);
		if (!_350_th)
			break;

		worst_fit_dealloc(_250_rd);
		worst_fit_dealloc(_150_nd);
	}

    int i = 0;
	for(i = 100; i <= 400; i += 100) {
		printf("External Fragmentation(s) with size less than %d bytes : %d\n", i, worst_fit_count_extfrag(i));
	}
	return 0;
}

int wf_allocate() {
    
    if(worst_fit_memory_init(3000)) {
        perror("Fail to create a chunck of memory");
        return -1;
    }
    
    int rand1 = rand() % 512 + 1;
    int rand2 = rand() % 512 + 1;
    int rand3 = rand() % 512 + 1;
    int rand4 = rand() % 512 + 1;
    int rand5 = rand() % 512 + 1;
    int rand6 = rand() % 512 + 1;
    int rand7 = rand() % 512 + 1;
    int rand8 = rand() % 512 + 1;
    
    for(;;)
    {
        
        void* chuck1 = worst_fit_alloc(rand1);
        if (!chuck1)
            break;
        
        void* chuck2 = worst_fit_alloc(rand2);
        if (!chuck2)
            break;
        
        void* chuck3 = worst_fit_alloc(rand3);
        if (!chuck3)
            break;
        
        void* chuck4 = worst_fit_alloc(rand4);
        if (!chuck4)
            break;
        
        void* chuck5 = worst_fit_alloc(rand5);
        if (!chuck5)
            break;
        
        void* chuck6 = worst_fit_alloc(rand6);
        if (!chuck6)
            break;
        
        void* chuck7 = worst_fit_alloc(rand7);
        if (!chuck7)
            break;
        
        void* chuck8 = worst_fit_alloc(rand8);
        if (!chuck8)
            break;
        
        worst_fit_dealloc(chuck3);
        worst_fit_dealloc(chuck2);
        worst_fit_dealloc(chuck6);
        worst_fit_dealloc(chuck7);
        
    }
    int i = 0;
    for(i = 100; i <= 600; i += 100 ){
        printf("%d, ", worst_fit_count_extfrag(i));
    }
    printf("\n");
    return 0;
}
void wf_extfrag_test(){
    int counter = 0;
    while(counter < 10){
        wf_allocate();
        counter++;
    }
}



int main(int argc, char *argv[]){
    
	int algo = 0; // default algorithm to test is best fit
	int test_case = 0;
    
    srand(time(NULL));

	if (argc != 3) {
		fprintf(stderr, "Usage: %s <0/1>. 0 for best fit and 1 for worst fit \n", argv[0]);
		exit (1);
	} else if (!strcmp(argv[1], "1") || !strcmp(argv[1], "0")) {
		algo = atoi(argv[1]);
		test_case = atoi(argv[2]);
	} else {
		fprintf(stderr, "Invalid argument, please specify 0 or 1\n");
		exit(1);
	}
		
    
	if ( algo == 0 ) {
		
		switch(test_case){
			case 0:
				bf_allocate_deallocate_works();
				break;
			case 1:
                bf_find_block_test();
				break;
			case 2:
				bf_coalesce_test();
				break;
			case 3:
				bf_allocate_loop();
				break;
            case 4:
                bf_extfrag_test();
                break;
		}

	} else if ( algo == 1 ) {
		
		switch(test_case){
			case 0:
				wf_allocate_deallocate_works();
				break;
			case 1:
				wf_find_block_test();
				break;
			case 2:
				wf_coalesce_test();
				break;
			case 3:
				wf_allocate_loop();
                break;
            case 4:
                wf_extfrag_test();
                break;

		}

	} else {
		fprintf(stderr, "Should not reach here!\n");
		exit(1);
	}

	
	return 0;
}
