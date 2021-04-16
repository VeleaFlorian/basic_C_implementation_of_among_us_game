#include "utils.h"

void* (* Abilities[4])(void* x) = {RotateMatrix, DecodeString, InvertArray, KillPlayer};

char *fromEnumtoString(PlayerRoles playerRole)
{
	char *str = calloc(MAX_LEN_STR_ATR, sizeof(char));
	switch(playerRole)
	{
		case Rotator:
			str = strcpy(str, "Rotator");
			break;
		case Decoder:
			str = strcpy(str, "Decoder");
			break;
		case Invertor:
			str = strcpy(str, "Invertor");
			break;
		case Impostor:
			str = strcpy(str, "Impostor");
			break;
	}
	return str;
}


void *RotateMatrix(void *input)
{
	int *n;
	n = input;
	char a[*n + 1][*n + 1][*n + 1];
	char b[10], c[10], d[10], *e = calloc(MAX_LEN_STR_OUT,(sizeof(char)));
	int i, j;

	for (i = 1; i <= *n; i++ ) {
		for (j = 1; j <= *n; j++) {
			sprintf(b, "%d", j);
			sprintf(c, "%d", i);
			strcat(c, b);
			strcpy(a[i -1][j - 1], c);
			} 
 		}

	for (i = 0; i < *n; i++) {
		for (j = 0; j < *n; j++) {
			if (i >= j) {
			strcpy(d, a[i][j]);
			memmove(a[i][j], a[j][i], strlen(a[i][j]));
			strcpy(a[j][i], d);
			}
		}
	}

	for (i = 0; i < *n; i++) {
		for (j = 0; j < (*n / 2); j++) {
			strcpy(d,a[i][j]);
			strcpy(a[i][j], a[i][*n - j -1]);
			strcpy(a[i][*n - j - 1], d);
		}
	}	

    for (int k = 0; k < *n; k++ ) {
		for (int l = 0; l < *n; l++) {
			strcat(e, a[k][l]);
			if (k == (*n - 1) && l == (*n - 1))
			b[0] = '0';
			else
			strcat(e, " ");
			} 
		if(k < (*n - 1)) {
			strcat(e, "\n");
		}		
 	}

	return e;
}


void *DecodeString(void *input)
{
	char *e;
	e = input;
	char *x;
	char *y = calloc(1000, sizeof(char));
	x = strtok(e,"_");
   int s = 0;

   while (x != NULL) {
	   s = s + atoi(x);
	   x = strtok(NULL, "_");
   }
   sprintf(y, "%d", s);

	return y;
}


void *InvertArray(void *input)
{
	int *n = input;
	char c[100] = "";
	char * a = NULL;
	a = calloc(MAX_LEN_STR_OUT,sizeof(char));

	if (n[0] % 2 == 1) {
		for (int i = n[0]; i > 0; i--) {
			sprintf(c,"%d",n[i]);
			strcat(a, c);
			if(i > 1)
			strcat(a, " ");
		}
	}

	else {
		for (int  i = 1; i < n[0]; i = i + 2) {
			sprintf(c, "%d", n[i + 1]);
			strcat(a, c);
			strcat(a, " ");
			sprintf(c, "%d", n[i]);
			strcat(a, c);
			strcat(a, " ");
		}
	}
	
	return a;
}


Player *allocPlayer()
{	Player *p1 = (Player *)malloc(sizeof(Player));
	(*p1).name = malloc(MAX_LEN_STR_ATR * sizeof(char));
	(*p1).color = malloc(MAX_LEN_STR_ATR * sizeof(char));
	(*p1).hat = malloc(MAX_LEN_STR_ATR * sizeof(char));
	(*p1).alive = 1; 
	(*p1).indexOfLocation = 0;

	return p1;	
}


Game *allocGame()
{
	Game *g1 = (Game *)malloc(sizeof(Game));
	(*g1).name = malloc(MAX_LEN_STR_ATR * sizeof(char));
	
	return g1;
}


Player *ReadPlayer(FILE *inputFile)
{
	char role[100];
	Player *p1 = allocPlayer();

	fscanf(inputFile, "%s", (*p1).name);
	fscanf(inputFile, "%s", (*p1).color);
	fscanf(inputFile, "%s", (*p1).hat);
	fscanf(inputFile, "%d\n", &(*p1).numberOfLocations);
	
	(*p1).locations = (Location *)malloc(sizeof(Location) * (*p1).numberOfLocations);
	
	for (int i = 0; i < (*p1).numberOfLocations; i++) {
		fscanf(inputFile, "(%d,%d) ", &(*p1).locations[i].x, &(*p1).locations[i].y);
	}

	(*p1).playerRole = Impostor;
	fscanf(inputFile, "%s", role);

	if (strcoll(role, "Rotator") == 0) {
		(*p1).playerRole = Rotator;
		(*p1).ability = Abilities[(*p1).playerRole];
	} else if (strcoll(role, "Decoder") == 0) {
		(*p1).playerRole = Decoder;
		(*p1).ability = Abilities[(*p1).playerRole];
	} else if (strcoll(role, "Invertor") == 0) {
		(*p1).playerRole = Invertor;
		(*p1).ability = Abilities[(*p1).playerRole];
	} else {
		(*p1).ability = Abilities[(*p1).playerRole];
	}
	
	return p1;
}


Game *ReadGame(FILE *inputFile)
{
	Game *game = allocGame();

	fscanf(inputFile, "%s" , (*game).name);
	fscanf(inputFile, "%d", &(*game).killRange);
	fscanf(inputFile, "%d", &(*game).numberOfCrewmates);

	(*game).crewmates = (Player **)malloc(sizeof(Player) * (*game).numberOfCrewmates);

	for (int i = 0; i < (*game).numberOfCrewmates; i++) {
		 (*game).crewmates[i] = ReadPlayer(inputFile);
	}

	(*game).impostor = ReadPlayer(inputFile);

	return game;
}


void WritePlayer(Player *player, FILE *outputFile)
{
	char *role = malloc(sizeof(char) * 10);
	
	if ((*player).playerRole == 0) {
		strcpy(role,"Rotator");
	}

	if ((*player).playerRole == 1) {
		strcpy(role,"Decoder");
	}

	if ((*player).playerRole == 2) {
		strcpy(role,"Invertor");
	}

	if ((*player).playerRole == 3) {
		strcpy(role,"Impostor");
	}
	
	fprintf(outputFile, "Player %s with color %s, hat %s and role %s has entered the game.\n", (*player).name, (*player).color, (*player).hat, role);
	fprintf(outputFile, "Player's locations:");
	
	for (int i = 0; i < (*player).numberOfLocations; i++) {
		fprintf(outputFile, " (%d,%d)", (*player).locations[i].x, (*player).locations[i].y);
	}

	if ((*player).playerRole != 3){
		fprintf(outputFile, "\n");
	}

	free(role);

}


void WriteGame(Game *game, FILE *outputFile)
{
	fprintf(outputFile, "Game %s has just started!\n", (*game).name);
	fprintf(outputFile, "	Game options:\n");
	fprintf(outputFile, "Kill Range: %d\n", (*game).killRange);
	fprintf(outputFile, "Number of crewmates: %d", (*game).numberOfCrewmates);
	fprintf(outputFile, "\n\n");
	fprintf(outputFile, "	Crewmates:\n");

	for (int i = 0; i < (*game).numberOfCrewmates; i++) {
		WritePlayer((*game).crewmates[i], outputFile);
	}

	fprintf(outputFile, "\n");
	fprintf(outputFile, "	Impostor:\n");
	WritePlayer((*game).impostor, outputFile);

}


void *KillPlayer(void *input)
{
	Game *game = input;

	int LowestDinstance = -1;
	int stock_crewmate = -1;
	int stock_indexoflocation = -1;
	char *str = calloc(100,sizeof(char));
	char *LowestDinstance_str = malloc(sizeof(char) * 10);

	for (int i = 0; i < (*game).numberOfCrewmates; i++) {
		float crewmate_x, crewmate_y, impostor_x, impostor_y;

		crewmate_x = (*game).crewmates[i]->locations[(*game).crewmates[i]->indexOfLocation].x;
		crewmate_y = (*game).crewmates[i]->locations[(*game).crewmates[i]->indexOfLocation].y;
		impostor_x = (*game).impostor->locations[(*game).impostor->indexOfLocation].x;
		impostor_y = (*game).impostor->locations[(*game).impostor->indexOfLocation].y;

		int modul_x = fabs(crewmate_x - impostor_x);
		int modul_y = fabs(crewmate_y - impostor_y);

		if ((modul_x + modul_y) <= (*game).killRange && (*game).crewmates[i]->alive == 1) {
			if ((*game).crewmates[i]->indexOfLocation > stock_indexoflocation) {
				LowestDinstance = modul_x + modul_y;
				stock_crewmate = i;
				stock_indexoflocation = (*game).crewmates[i]->indexOfLocation;
			}
		}
		if ((modul_x + modul_y) <= LowestDinstance && stock_crewmate < i && (*game).crewmates[i]->alive == 1) {
			if ((*game).crewmates[i]->indexOfLocation >= stock_indexoflocation) {
				LowestDinstance = modul_x + modul_y;
				stock_crewmate = i;
				stock_indexoflocation = (*game).crewmates[i]->indexOfLocation;
			}
		}
	}

	if(LowestDinstance >= 0)
		(*game).crewmates[stock_crewmate]->alive = 0;

	if(LowestDinstance >= 0) {
		strcat( str, "Impostor ");
		strcat( str, (*game).impostor->name);
		strcat( str, " has just killed crewmate ");
		strcat(str, (*game).crewmates[stock_crewmate]->name);
		strcat(str, " from distance ");
		sprintf(LowestDinstance_str, "%d", LowestDinstance);
		strcat(str, LowestDinstance_str);
		strcat(str, ".");
	} else {
		strcat( str, "Impostor ");
		strcat( str, (*game).impostor->name);
		strcat( str, " couldn't kill anybody.");
	}

	free(LowestDinstance_str);
	
	return str;
}


void CalcuateNextCycleOfGame(Game *game, FILE *outputFile, void **inputMatrix)
{
	for (int i = 0; i < (*game).numberOfCrewmates; i++) {
		if ((*game).crewmates[i]->alive == 0) {
			fprintf(outputFile, "Crewmate %s is dead.\n", (*game).crewmates[i]->name);
		} else {
			fprintf(outputFile, "Crewmate %s went to location ", (*game).crewmates[i]->name);

			(*game).crewmates[i]->indexOfLocation++;

			if ((*game).crewmates[i]->indexOfLocation == ((*game).crewmates[i]->numberOfLocations )) {
				(*game).crewmates[i]->indexOfLocation = 0;
			}

			fprintf(outputFile, "(%d,%d).\n", (*game).crewmates[i]->locations[(*game).crewmates[i]->indexOfLocation].x, (*game).crewmates[i]->locations[(*game).crewmates[i]->indexOfLocation].y);
			fprintf(outputFile, "Crewmate %s's output:\n", (*game).crewmates[i]->name);

			if ((*game).crewmates[i]->playerRole == 0) {
				char *output = RotateMatrix(inputMatrix[i]);

				fprintf(outputFile, "%s\n", output);
				free(output);
			}

			if ((*game).crewmates[i]->playerRole == 1) {
				char *output = DecodeString(inputMatrix[i]);

				fprintf(outputFile, "%s\n", output);
				free(output);
			}

			if ((*game).crewmates[i]->playerRole == 2) {
				char *output = InvertArray(inputMatrix[i]);

				fprintf(outputFile, "%s\n", output);
				free(output);
			}
		}
	}

	fprintf(outputFile, "Impostor %s went to location ", (*game).impostor->name);

	(*game).impostor->indexOfLocation++;

	if ((*game).impostor->indexOfLocation == ((*game).impostor->numberOfLocations)) {
		(*game).impostor->indexOfLocation = 0;
	}

	fprintf(outputFile, "(%d,%d).\n", (*game).impostor->locations[(*game).impostor->indexOfLocation].x, (*game).impostor->locations[(*game).impostor->indexOfLocation].y);
	fprintf(outputFile, "Impostor %s's output:\n", (*game).impostor->name);

	char *output = KillPlayer(game);

	fprintf(outputFile, "%s\n", output);
	free(output);

}


void FreePlayer(Player *player)
{
	free((*player).name);
	free((*player).hat);
	free((*player).color);
	free((*player).locations);
	free(player);

}


void FreeGame(Game *game)
{
	free((*game).name);

	for (int i = 0; i < (*game).numberOfCrewmates; i++) {
		FreePlayer((*game).crewmates[i]);
	}

	free((*game).crewmates);
	FreePlayer((*game).impostor);
	free(game);

}