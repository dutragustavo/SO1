#include <stdio.h>

/* grid size = 9x9 */
#define SIZE 9

int grid[SIZE][SIZE];
int err_counter;

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

int check_row(int row_id){
	for (int i = 0; i < SIZE; ++i)
	{
		for (int j = i + 1; j < SIZE; ++j)
		{
			if(grid[row_id][i] == grid[row_id][j])
				return i;
		}
	}
	return -1;
}

void validate_rows(){
	int ret;
	for(int row_id = 0; row_id < SIZE; ++row_id){
		ret = check_row(row_id);
		if(ret >= 0){
			err_counter++;
			printf("Erro na linha %d coluna %d", row_id, ret);
		}
	}
}

int check_column(int column_id){
	for (int i = 0; i < SIZE; ++i)
	{
		for (int j = i + 1; j < SIZE; ++j)
		{
			if(grid[j][column_id] == grid[i][column_id])
				return i;
		}
	}
	return -1;
}

void validate_columns(){
	int ret;
	for(int column_id = 0; column_id < SIZE; ++column_id){
		ret = check_column(column_id);
		if(ret >= 0){
			err_counter++;
			printf("Erro na linha %d coluna %d\n", ret, column_id);
		}
	}
}



int main(int argc, char *argv[]) {

	if(argc != 2) {
		printf("Erro: informe o arquivo de entrada!\nUso: %s <arquivo de entrada>\n\n", argv[0]);
		return 1;
	}

	/* Le o grid do arquivo, armazena na matriz grid e imprime */
	if(!load_grid(argv[1])){
		printf("Erro no carregamento do quebra-cabeça\n");
		return 1;
	}

	err_counter = 0;

	validate_columns();
	validate_rows();
	check_grid();
	printf("Erros encontrados: %d\n", err_counter);
	return 0;
}
