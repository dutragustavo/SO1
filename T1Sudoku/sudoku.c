#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

/* grid size = 9x9 */
#define SIZE 9


int grid[SIZE][SIZE];
int err_counter;
pthread_mutex_t counter_mutex;

/* Funcao que le um grid do arquivo "filename" e o armazena em uma matriz */
int load_grid(char *filename) {
	FILE *input_file = fopen(filename, "r");

	if (input_file != NULL) {
		for(int i = 0; i < SIZE; i++)
			for(int j = 0; j < SIZE; j++)
				fscanf(input_file, "%d", &grid[i][j]);
		fclose(input_file);
		return 1;
	}

	return 0;
}


//soma dos elementos de 1 a 9 == 45 
int check_row(int row_id){
	int sum = 0;
	for (int i = 0; i < SIZE; i++)
	{
		sum += grid[row_id][i];
	}
	return (sum == 45);
}

int check_column(int column_id){
	int sum = 0;
	for (int i = 0; i < SIZE; i++)
	{
		sum += grid[i][column_id];
	}
	return (sum == 45);
}

int check_region(int region_index){
	int row_index = (region_index / 3) * 3;
	int column_index = (region_index % 3) * 3;

	int sum = 0;
	for (int i = row_index; i < row_index + 3; i++)
	{
		for (int j = column_index; j < column_index + 3; j++)
		{
			sum += grid[i][j];
		}
	}

	return (sum == 45);
}

void increment_counter(){
	pthread_mutex_lock(&counter_mutex);
	err_counter++;
	pthread_mutex_unlock(&counter_mutex);	
}

pthread_mutex_t work_mutex;
//1 - nenhuma thread fez a verificação do elemento desse indice
//0 - esse indice ja foi verificado
int work_map[3][9];

void* do_work(void* _index){
	int index = (int)_index;
	int valid = 1;
	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 9; j++)
		{
			pthread_mutex_lock(&work_mutex);
			if(work_map[i][j] == 0){
				pthread_mutex_unlock(&work_mutex);
				continue;
			}

			work_map[i][j] = 0;
			pthread_mutex_unlock(&work_mutex);
			switch(i){
				case 0: 
						valid = check_row(j); 
						if(!valid){
							increment_counter();
							printf("Thread %d: erro na linha %d\n", index, j);
						}
						break;
				
				case 1: 
						valid = check_column(j); 
						if(!valid){
							increment_counter();
							printf("Thread %d: erro na coluna %d\n", index, j);
						}
						break;
				
				case 2: 
						valid = check_region(j); 
						if(!valid){
							increment_counter();
							printf("Thread %d: erro na região %d\n", index, j);
						}
						break;
			}		
		}
	}
}

int main(int argc, char *argv[]) {

	if(argc < 2) {
		printf("Erro: informe o arquivo de entrada!\nUso: %s <arquivo de entrada>\n\n", argv[0]);
		return 1;
	}

	int num_threads = 1;
	if(argv[2]){
		num_threads = atoi(argv[2]);
	}

	if(num_threads < 1){ //atoi pode falhar
		num_threads = 1;
	}

	/* Le o grid do arquivo, armazena na matriz grid e imprime */
	if(!load_grid(argv[1])){
		printf("Erro no carregamento do quebra-cabeça\n");
		return 1;
	}

	pthread_mutex_init(&counter_mutex, NULL);
	err_counter = 0;

	pthread_mutex_init(&work_mutex, NULL);
	memset(work_map, 1, sizeof(work_map[0][0]) * 3 * 9);

	pthread_t threads[num_threads];
	for (int i = 0; i < num_threads; i++)
	{
		pthread_create(&threads[i], NULL, do_work, (void*)i);
	}

	for (int i = 0; i < num_threads; i++)
	{
		pthread_join(threads[i], NULL);
	}

	printf("Erros encontrados: %d\n", err_counter);
	return 0;
}
