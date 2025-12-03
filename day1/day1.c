#include <stdio.h>
#include <stdlib.h>

int rotateR(int actLock, int rotation){
	printf("actLock : %d, Rotation de %d vers la droite\n", actLock, rotation);
	actLock += rotation;
	actLock = actLock%100;
	return actLock;
}

int rotateL(int actLock, int rotation){
	printf("actLock : %d, Rotation de %d vers la gauche\n", actLock, rotation);
	actLock -= rotation;
	actLock = actLock %100;
	return actLock;
}

int main(int argc, char* argv[]){
	if(argc != 3){
		printf("You forgot the sequence file for %s\n", argv[0]);
		return 1;
	}
	int actLock = 50;
	int cpt0 = 0;
	FILE* seq = fopen(argv[1], "r");
	if(seq == NULL){
		perror("fopen");
		return 1;
	}
	int cptChar = 0;
	char buf[1024];
	size_t sz;
	int nbLignes = 1;
	while ((sz = fread(buf, 1, 1024, seq)) > 0) {
		for(size_t i = 0 ; i < sz ; i++){
			if(buf[i] == '\n'){
				nbLignes++;
			}
		}
		cptChar += sz;
	}
	fclose(seq);
	char** tab = (char **)malloc(nbLignes * sizeof(char*));
	for(int i = 0 ; i < nbLignes ; i++){
		tab[i] = (char*)calloc(5, sizeof(char));
	}
	int i = 0;
	int posTab = 0;
	FILE* seq2 = fopen(argv[2], "r");;
	while ((sz = fread(buf, 1, 1024, seq2)) > 0) {
		for(size_t j = 0 ; j < sz ; j++){
			if(buf[j] == '\n' || buf[j] == '\r'){
				tab[i][posTab]='\0';
				i++;
				posTab = 0;
			}else{
				tab[i][posTab] = buf[j];
				posTab++;	
			}
		}
	}
	for(i = 0 ; i < nbLignes ; i++){
		if(tab[i][0] == 'R'){
			printf("R%d\n",atoi(&tab[i][1]));
			actLock = rotateR(actLock, atoi(&tab[i][1]));
			if(actLock == 0)cpt0++;
		}
		if(tab[i][0] == 'L'){
			printf("L%d\n",atoi(&tab[i][1]));
			actLock = rotateL(actLock, atoi(&tab[i][1]));
			if(actLock == 0)cpt0++;
		}
	}
	printf("%d\n", cpt0);
	
}
