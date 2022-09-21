#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#define MAX 29

typedef struct date
{
	int day, month, year;	//Dia, Mes e Ano do espetaculo
	int hour, minute;		//Hora e Minuto de come�o do espetaculo
	int duration;			//Dura�ao do espetaculo	
	char time[2];			//AM ou PM

}DATE;

typedef struct reservation
{
	int code;				//Codigo da reserva que nos d� acesso para modificar
	int row, chair;			//Qual a fila e cadeira que reservou
	char pay[2];			//Se efetou ou nao pagamento
	char name[20];			//Nome do cliente
	bool exist;				//Condicao que nos diz que no array, a posicao em que estamos a trabalhar esta ocupada
	bool paid;				//Saber se a reserva esta paga ou nao
}RESERVATION;
typedef struct show
{
	float price;				  //Pre�o do bilhete do espetaculo
	int code;					  //Codigo do espetaculo que nos da acesso para modificar, remover e criar reserva
	char title[15], genre[15];	  //Titulo e genero do espetaculo
	RESERVATION reservation[MAX];  //Estrutura relativamente �s reservas com um maximo 29
	DATE date;					  //Condicao que leva � estrutura DATE para mais detalhes sobre o espetaculo
	bool exist;					  //Condi�ao que nos diz que no array, esta posicao esta ocupada

}SHOW;

typedef struct room
{
	int code, rows, chairs; //Codigo que da acesso para adicionar espetaculos na sala, numero de filas e cadeiras
	char locality_name[20]; //Nome da localidade
	SHOW show[MAX];			//Estrutura relativamente aos espetaculos com um maximo de 29
	bool exist;				//Condi�ao que nos diz que no array, esta posicao esta ocupada

}ROOM;


//--------------------------------------------------------Fun�ao Inicializa�ao-------------------------------------------------------------------------

void inicialization(ROOM* p)
{

	for (int i = 0; i < MAX; i++)
	{
		for (int j = 0; j < MAX; j++)
		{
			for (int c = 0; c < MAX; c++)
			{
				p[i].exist = false;
				p[i].show[j].exist = false;
				p[i].show[j].reservation[c].paid = false;								//Apenas � preciso colocar todos as condi�oes de bool a false
				p[i].show[j].reservation[c].exist = false;
			}
		}
	}

}

//-----------------------------------------------------Adicionar sala-----------------------------------------------------------------------------------

void add_new_room(ROOM* p)
{
	int i = 0;

	while (p[i].exist == true)
	{
		i++;										//Procurar uma posi�ao no vetor que esteja vazia
	}


	do
	{
		printf("\nWhere is the new room located? ");
		fseek(stdin, 0, 2);
		gets(p[i].locality_name);

	} while ((strcmp(p[i].locality_name, " ") == 0) || (strcmp(p[i].locality_name, "\n") == 0) || (strcmp(p[i].locality_name, "") == 0));

	do
	{
		printf("\nHow many rows does the room has? ");
		scanf("%d", &p[i].rows);

	} while (p[i].rows < 0);

	do
	{
		printf("\nHow many chairs does the row has? ");
		scanf("%d", &p[i].chairs);


	} while (p[i].chairs < 0);


	p[i].exist = true;

	p[i].code = i + 1;

}

//---------------------------------------------------------------Listagem das salas--------------------------------------------------------------------

void rooms_list(ROOM* p)
{
	for (int i = 0; i < MAX; i++)
	{
		if (p[i].exist == true)																					//Procura todos as salas que existam
		{
			printf("\n%d\t    %s\t      %d     %d\n", p[i].code, p[i].locality_name, p[i].rows, p[i].chairs);	//Print da informa�ao da sala
		}
	}
}

//----------------------------------------------------------------------Remover sala-------------------------------------------------------------------

void remove_room(ROOM* p)
{
	int room_code;

	printf("\nWhat is the room's code you desire to remove?");
	scanf("%d", &room_code);

	for (int i = 0; i < MAX; i++)
	{
		for (int j = 0; j < MAX; j++)
		{
			for (int c = 0; c < MAX; c++)
			{
				if (p[i].code == room_code)									//Procura ate encontrar o codigo da sala que se quer remover
				{
					p[i].locality_name[0] = '\0';
					p[i].exist = false;
					p[i].chairs = 0;
					p[i].rows = 0;
					p[i].code = 0;
					p[i].show[j].exist = false;
					p[i].show[j].reservation[c].exist = false;



				}
			}
		}
	}
}


//-----------------------------------------------------Adicionar espetaculo----------------------------------------------------------------------------

void add_new_show(ROOM* p)
{
	int room_code;

	printf("\nWhat is the room's code you desire to alocate the show?");
	scanf("%d", &room_code);

	int i = 0, j = 0;

	while (p[i].code != room_code && p[i].exist == true && i < MAX)						//Encontra a posicao do vetor ate que seja igual 
	{
		i++;

	}

	if (p[i].exist == false && p[i].code == 0)
	{
		while (p[i].code != room_code && p[i].exist == false && i < MAX)				//Condi�ao que corrige um erro na adicao de espetaculos																					
		{																				//depois da remo�ao da primeira sala
			i++;

		}
	}


	while (p[i].show[j].exist == true && j < MAX)										//Encontra a posicao do vetor ate que seja igual 																						
	{																					//ao codigo do espetaculo e que o espetaculo exista
		j++;
	}


	if (p[i].code == room_code && p[i].show[j].exist == false && p[i].exist == true && i < MAX && j < MAX)		//Se o codigo da sala for igual 
	{																											//ao codigo do utilizador																								
		do                                                                                                      //a sala existir e
		{                                                                                                       //e a posicao do vetor do espetaculo
			printf("\nWhat is the show's title? ");																//estiver livre pede as informa�oes 
			fseek(stdin, 0, 2);
			gets(p[i].show[j].title);

		} while (strcmp(p[i].show[j].title, "") == 0 || (strcmp(p[i].show[j].title, "\n") == 0) || (strcmp(p[i].show[j].title, " ") == 0));

		do
		{
			printf("\nWhat is the show's genre? ");
			fseek(stdin, 0, 2);
			gets(p[i].show[j].genre);

		} while (strcmp(p[i].show[j].genre, "") == 0 || (strcmp(p[i].show[j].genre, "\n") == 0) || (strcmp(p[i].show[j].genre, " ") == 0));

		do
		{
			printf("\nInsert the year show: ");
			scanf("%d", &p[i].show[j].date.year);


			printf("\nInsert the month: ");
			scanf("%d", &p[i].show[j].date.month);


			if (p[i].show[j].date.year % 400 == 0 || (p[i].show[j].date.year % 4 == 0 && p[i].show[j].date.year % 100 != 0))
			{
				if (p[i].show[j].date.month == 1 || p[i].show[j].date.month == 3 || p[i].show[j].date.month == 5 ||
					p[i].show[j].date.month == 7 || p[i].show[j].date.month == 8 || p[i].show[j].date.month == 10 || p[i].show[j].date.month == 12)
				{

					do
					{
						printf("\nInsert the day: ");
						scanf("%d", &p[i].show[j].date.day);

					} while (p[i].show[j].date.day > 31 || p[i].show[j].date.day < 1);
				}

				else if (p[i].show[j].date.month == 4 || p[i].show[j].date.month == 6 || p[i].show[j].date.month == 9 ||
					p[i].show[j].date.month == 11)
				{
					do
					{
						printf("\nInsert the day: ");
						scanf("%d", &p[i].show[j].date.day);


					} while (p[i].show[j].date.day > 30 && p[i].show[j].date.day < 1);
				}

				else if (p[i].show[j].date.month == 2)
				{
					do
					{
						printf("\nInsert the day: ");
						scanf("%d", &p[i].show[j].date.day);

					} while (p[i].show[j].date.day < 1 || p[i].show[j].date.day > 29);

				}


			}

			else
			{
				if (p[i].show[j].date.month == 1 || p[i].show[j].date.month == 3 || p[i].show[j].date.month == 5 ||
					p[i].show[j].date.month == 7 || p[i].show[j].date.month == 8 || p[i].show[j].date.month == 10 || p[i].show[j].date.month == 12)
				{
					do
					{
						printf("\nInsert the day: ");
						scanf("%d", &p[i].show[j].date.day);

					} while (p[i].show[j].date.day > 31 || p[i].show[j].date.day < 1);
				}
				else if (p[i].show[j].date.month == 4 || p[i].show[j].date.month == 6 || p[i].show[j].date.month == 9 ||
					p[i].show[j].date.month == 11)
				{
					do
					{
						printf("\nInsert the day: ");
						scanf("%d", &p[i].show[j].date.day);


					} while (p[i].show[j].date.day > 30 && p[i].show[j].date.day < 1);

				}

				else if (p[i].show[j].date.month == 2)
				{
					do
					{
						printf("\nInsert the day: ");
						scanf("%d", &p[i].show[j].date.day);

					} while (p[i].show[j].date.day < 1 || p[i].show[j].date.day > 28);
				}

			}

		} while (p[i].show[j].date.month > 12 || p[i].show[j].date.month < 1 || p[i].show[j].date.year < 2022);









		do
		{
			printf("\nWhat is the ticket's price? ");
			scanf("%f", &p[i].show[j].price);

		} while (p[i].show[j].price < 0);

		do
		{
			printf("\nWhen does the show start? \nExample:10:00 AM\n");
			scanf("%d %d %s", &p[i].show[j].date.hour, &p[i].show[j].date.minute, p[i].show[j].date.time);


		} while (p[i].show[j].date.hour > 12 || p[i].show[j].date.hour < 0 || p[i].show[j].date.minute > 59 || p[i].show[j].date.minute < 0
			|| strcmp(p[i].show[j].date.time, "AM") && strcmp(p[i].show[j].date.time, "PM"));


		do
		{
			printf("\nWhat is the show's duration in minutes? ");
			scanf("%d", &p[i].show[j].date.duration);

		} while (p[i].show[j].date.duration < 0);


		p[i].show[j].code = j + 1;

		p[i].show[j].exist = true;

	}
	else
	{
		printf("\nIts not possible to add show\n");
	}


}

//--------------------------------------------------------------------Remover um espetaculo-----------------------------------------------------------

void remove_show(ROOM* p)
{
	int room_code, show_code;

	printf("\nWhat is the room's code and the show's code you desire to remove? ");
	scanf("%d %d", &room_code, &show_code);

	for (int i = 0; i < MAX; i++)
	{
		for (int j = 0; j < MAX; j++)
		{
			if (p[i].code == room_code && p[i].show[j].code == show_code)
			{
				p[i].show[j].exist = false;
			}
		}
	}
}

//---------------------------------------------------------------Mudar o titulo do espetaculo---------------------------------------------------------

void change_title(ROOM* p)
{
	int i = 0, j = 0;

	int room_code, show_code;


	printf("\nWhat is the room's code and the show's code you desire to modify the title? ");
	scanf("%d %d", &room_code, &show_code);


	while (p[i].code != room_code && i < MAX)
	{
		i++;

	}

	while (p[i].show[j].code != show_code && j < MAX)
	{
		j++;
	}

	if (p[i].code == room_code && p[i].exist == true && p[i].show[j].exist == true && p[i].show[j].code == show_code)
	{

		do
		{
			printf("\nWhat is the show's title?");
			fseek(stdin, 0, 2);
			gets(p[i].show[j].title);

		} while (strcmp(p[i].show[j].title, "") == 0 || (strcmp(p[i].show[j].title, "\n") == 0) || (strcmp(p[i].show[j].title, " ") == 0));

	}
}

//----------------------------------------------------------------------Mudar o genero do espetaculo---------------------------------------------------

void change_genre(ROOM* p)
{
	int i = 0, j = 0;

	int room_code, show_code;


	printf("\nWhat is the room's code and the show's code you desire to modify the genre? ");
	scanf("%d %d", &room_code, &show_code);


	while (p[i].code != room_code && i < MAX)
	{
		i++;

	}

	while (p[i].show[j].code != show_code && j < MAX)
	{
		j++;
	}

	if (p[i].code == room_code && p[i].exist == true && p[i].show[j].exist == true && p[i].show[j].code == show_code)
	{
		do
		{
			printf("\nWhat is the show's genre?");
			fseek(stdin, 0, 2);
			gets(p[i].show[j].genre);

		} while (strcmp(p[i].show[j].genre, "") == 0 || (strcmp(p[i].show[j].genre, "\n") == 0) || (strcmp(p[i].show[j].genre, " ") == 0));
	}

}

//-----------------------------------------------------------------------Mudar a data de um espatulo---------------------------------------------------

void change_date(ROOM* p)
{
	int i = 0, j = 0;

	int room_code, show_code;


	printf("\nWhat is the room's code and the show's code you desire to modify the date? ");
	scanf("%d %d", &room_code, &show_code);


	while (p[i].code != room_code && i < MAX)
	{
		i++;

	}

	while (p[i].show[j].code != show_code && j < MAX)
	{
		j++;
	}


	do
	{
		printf("\nInsert the year show: ");
		scanf("%d", &p[i].show[j].date.year);


		printf("\nInsert the month: ");
		scanf("%d", &p[i].show[j].date.month);


		if (p[i].show[j].date.year % 400 == 0 || (p[i].show[j].date.year % 4 == 0 && p[i].show[j].date.year % 100 != 0))
		{
			if (p[i].show[j].date.month == 1 || p[i].show[j].date.month == 3 || p[i].show[j].date.month == 5 ||
				p[i].show[j].date.month == 7 || p[i].show[j].date.month == 8 || p[i].show[j].date.month == 10 || p[i].show[j].date.month == 12)
			{

				do
				{
					printf("\nInsert the day: ");
					scanf("%d", &p[i].show[j].date.day);

				} while (p[i].show[j].date.day > 31 || p[i].show[j].date.day < 1);
			}

			else if (p[i].show[j].date.month == 4 || p[i].show[j].date.month == 6 || p[i].show[j].date.month == 9 ||
				p[i].show[j].date.month == 11)
			{
				do
				{
					printf("\nInsert the day: ");
					scanf("%d", &p[i].show[j].date.day);


				} while (p[i].show[j].date.day > 30 && p[i].show[j].date.day < 1);
			}

			else if (p[i].show[j].date.month == 2)
			{
				do
				{
					printf("\nInsert the day: ");
					scanf("%d", &p[i].show[j].date.day);

				} while (p[i].show[j].date.day < 1 || p[i].show[j].date.day > 29);

			}


		}

		else
		{
			if (p[i].show[j].date.month == 1 || p[i].show[j].date.month == 3 || p[i].show[j].date.month == 5 ||
				p[i].show[j].date.month == 7 || p[i].show[j].date.month == 8 || p[i].show[j].date.month == 10 || p[i].show[j].date.month == 12)
			{
				do
				{
					printf("\nInsert the day: ");
					scanf("%d", &p[i].show[j].date.day);

				} while (p[i].show[j].date.day > 31 || p[i].show[j].date.day < 1);
			}
			else if (p[i].show[j].date.month == 4 || p[i].show[j].date.month == 6 || p[i].show[j].date.month == 9 ||
				p[i].show[j].date.month == 11)
			{
				do
				{
					printf("\nInsert the day: ");
					scanf("%d", &p[i].show[j].date.day);


				} while (p[i].show[j].date.day > 30 && p[i].show[j].date.day < 1);

			}

			else if (p[i].show[j].date.month == 2)
			{
				do
				{
					printf("\nInsert the day: ");
					scanf("%d", &p[i].show[j].date.day);

				} while (p[i].show[j].date.day < 1 || p[i].show[j].date.day > 28);
			}

		}

	} while (p[i].show[j].date.month > 12 || p[i].show[j].date.month < 1 || p[i].show[j].date.year < 2022);

}
//-----------------------------------------------------------Mudar o pre�o de um espetaculo--------------------------------------------------------------
void change_price(ROOM* p)
{

	int i = 0, j = 0;

	int room_code, show_code;


	printf("\nWhat is the room's code and the show's code you desire to modify the price? ");
	scanf("%d %d", &room_code, &show_code);


	while (p[i].code != room_code && i < MAX)
	{
		i++;

	}

	while (p[i].show[j].code != show_code && j < MAX)
	{
		j++;
	}

	if (p[i].code == room_code && p[i].exist == true && p[i].show[j].exist == true && p[i].show[j].code == show_code)
	{
		do
		{
			printf("\nWhat is the ticket's price? ");
			scanf("%f", &p[i].show[j].price);

		} while (p[i].show[j].price < 0);
	}
}

//--------------------------------------------------------Mudar a hora de um espetaculo----------------------------------------------------------------

void change_hour(ROOM* p)
{
	int i = 0, j = 0;

	int room_code, show_code;


	printf("\nWhat is the room's code and the show's code you desire to modify the price? ");
	scanf("%d %d", &room_code, &show_code);


	while (p[i].code != room_code && i < MAX)
	{
		i++;

	}

	while (p[i].show[j].code != show_code && j < MAX)
	{
		j++;
	}

	if (p[i].code == room_code && p[i].exist == true && p[i].show[j].exist == true && p[i].show[j].code == show_code)
	{
		do
		{
			printf("\nWhen does the show start? \nExample:10:00 AM\n");
			scanf("%d %d %s", &p[i].show[j].date.hour, &p[i].show[j].date.minute, p[i].show[j].date.time);


		} while (p[i].show[j].date.hour > 12 || p[i].show[j].date.hour < 0 || p[i].show[j].date.minute > 59 || p[i].show[j].date.minute < 0
			|| strcmp(p[i].show[j].date.time, "AM") && strcmp(p[i].show[j].date.time, "PM"));

	}
}

//---------------------------------------------------------------------------Mudar a dura�ao de um espetaculo-----------------------------------------

void change_duration(ROOM* p)
{
	int i = 0, j = 0;

	int room_code, show_code;


	printf("\nWhat is the room's code and the show's code you desire to modify the price? ");
	scanf("%d %d", &room_code, &show_code);


	while (p[i].code != room_code && i < MAX)
	{
		i++;

	}

	while (p[i].show[j].code != show_code && j < MAX)
	{
		j++;
	}

	if (p[i].code == room_code && p[i].exist == true && p[i].show[j].exist == true && p[i].show[j].code == show_code)
	{
		do
		{
			printf("\nWhat is the show's duration in minutes? ");
			scanf("%d", &p[i].show[j].date.duration);

		} while (p[i].show[j].date.duration < 0);
	}
}

//----------------------------------------------------------------------------Mudar um espetaculo-----------------------------------------------------

void change_show(ROOM* p)
{

	int i = 0, j = 0;

	int option;

	do
	{
		printf("0 - Exit\n");
		printf("1 - Change Title\n");
		printf("2 - Change Genre\n");
		printf("3 - Change Date\n");
		printf("4 - Change Price\n");
		printf("5 - Change Hour\n");
		printf("6 - Change Duration\n");
		printf("\nWhat operation you desire to execute? ");
		scanf("%d", &option);


		switch (option)
		{
		case 0:break;
		case 1:change_title(p); break;
		case 2:change_genre(p); break;
		case 3:change_date(p); break;
		case 4:change_price(p); break;
		case 5:change_hour(p); break;
		case 6:change_duration(p); break;
		default:printf("\nOperation not found"); break;
		}

	} while (option != 0);

}

//----------------------------------------------------------------Listagem dos espetaculos------------------------------------------------------------

void shows_list(ROOM* p)
{
	for (int i = 0; i < MAX; i++)
	{
		for (int j = 0; j < MAX; j++)
		{
			if (p[i].show[j].exist == true)
			{
				printf("\n%d\t\t%d\t\t%s\t\t%s\t\t%d   %d     %d\t%.2f\t%d : %d  %s\t%d\n", p[i].code, p[i].show[j].code,
					p[i].show[j].title, p[i].show[j].genre, p[i].show[j].date.day, p[i].show[j].date.month, p[i].show[j].date.year,
					p[i].show[j].price, p[i].show[j].date.hour, p[i].show[j].date.minute, p[i].show[j].date.time, p[i].show[j].date.duration);
			}
		}
	}
}

//---------------------------------------------Adicionar uma reserva numa dada sala num dado espataculo-----------------------------------------------

void add_new_reservation(ROOM* p)
{
	int i = 0, j = 0, c = 0, room_code, show_code;
	int row, chair;


	printf("\nWhat is the room's code and show's code you desire to make a reservation? ");

	scanf("%d %d", &room_code, &show_code);

	printf("\nWhat is the row and the chair you desire to reserve? ");
	scanf("%d %d", &row, &chair);



	while (p[i].code != room_code && i < MAX)
	{
		i++;
	}

	if (row > p[i].rows || chair > p[i].chairs)
	{
		printf("\nIts not possible to make a reservation\n"); //Ver se o lugar ou a fila que quer reservar � superior ao numero de lugares ou filas da sala
		return 0;
	}

	while (p[i].show[j].code != show_code && p[i].show[j].exist == false && j < MAX)
	{
		j++;

	}

	while (p[i].show[j].reservation[c].exist == true && c < MAX)
	{
		c++;
	}

	for (int a = 0; a < MAX; a++)
	{
		if (row == p[i].show[j].reservation[a].row && chair == p[i].show[j].reservation[a].chair)
		{
			printf("\nThat place is ocupied\n");														//Procura todos os valores dentro do array
																										//Se encontrar uma reserva com a mesma
			return 0;																					//Fila e cadeira, sai da funcao
		}

	}


	if (p[i].exist == true && p[i].code == room_code && p[i].show[j].exist == true &&
		p[i].show[j].code == show_code && p[i].show[j].reservation[c].exist == false && i < MAX && j < MAX && c < MAX)
	{

		do
		{
			printf("\nWhat is the name of the client? ");
			scanf("%s", &p[i].show[j].reservation[c].name);

		} while (strcmp(p[i].show[j].reservation[c].name, "") == 0 || strcmp(p[i].show[j].reservation[c].name, "\n") == 0
			|| (strcmp(p[i].show[j].reservation[c].name, " ") == 0));


		do
		{

			printf("\nDid the client paid? (Y|N) ");
			scanf("%s", &p[i].show[j].reservation[c].pay);

			if (strcmp(p[i].show[j].reservation[c].pay, "Y") == 0)
			{
				p[i].show[j].reservation[c].paid = true;
			}
			else
			{
				p[i].show[j].reservation[c].paid = false;
			}

		} while (strcmp(p[i].show[j].reservation[c].pay, "Y") && strcmp(p[i].show[j].reservation[c].pay, "N"));



		p[i].show[j].reservation[c].exist = true;
		p[i].show[j].reservation[c].code = c + 1;
		p[i].show[j].reservation[c].row = row;
		p[i].show[j].reservation[c].chair = chair;

	}
	else
	{
		printf("\nIts not possible to make a reservation\n");
	}


}
//-------------------------------------------------------------------------Remover uma reserva---------------------------------------------------------
void remove_reservation(ROOM* p)
{

	int room_code, show_code, reservation_code;

	printf("\nWhat is the room's code, the show's code and the reservation's code you desire to remove? ");
	scanf("%d %d %d", &room_code, &show_code, &reservation_code);



	for (int i = 0; i < MAX; i++)
	{
		for (int j = 0; j < MAX; j++)
		{
			for (int c = 0; c < MAX; c++)
			{
				if (p[i].code == room_code && p[i].show[j].code == show_code && p[i].show[j].reservation[c].code == reservation_code)
				{
					p[i].show[j].reservation[c].exist = false;
				}
			}
		}
	}
}
//-----------------------------------------------------------------------Mudar o lugar da reserva-----------------------------------------------------
void change_row_chair(ROOM* p)
{
	int room_code, show_code, reservation_code;
	int i = 0, j = 0, c = 0;
	int row, chair;


	printf("\nWhat is the room's code, the show's code and the reservation's code you desire to modify the row or chair? ");
	scanf("%d %d %d", &room_code, &show_code, &reservation_code);

	printf("What is the row and the chair? ");
	scanf("%d %d", &row, &chair);

	while (p[i].code != room_code && i < MAX)
	{
		i++;

	}

	while (p[i].show[j].code != show_code && j < MAX)
	{
		j++;
	}

	while (p[i].show[j].reservation[c].code != reservation_code && c < MAX)
	{
		c++;
	}

	for (int a = 0; a < MAX; a++)
	{
		if (row == p[i].show[j].reservation[a].row && chair == p[i].show[j].reservation[a].chair)
		{
			printf("\nThat place is ocupied\n");														//Procura todos os valores dentro do array
																										//Se encontrar uma reserva com a mesma
			return 0;																					//Fila e cadeira, sai da funcao
		}

	}


	if (p[i].exist == true && p[i].show[j].exist == true && p[i].show[j].reservation[c].exist == true)
	{

		if (row > p[i].rows || chair > p[i].chairs || row < 0 || chair < 0)
		{
			printf("\nIt is not possible to modify the reservation\n");				//Ver se o lugar ou a fila que quer 
																					//reservar � superior ao numero de lugares ou filas da sala
			return 0;
		}
		else
		{
			p[i].show[j].reservation[c].row = row;
			p[i].show[j].reservation[c].chair = chair;
		}

	}
}

//---------------------------------------------------Mudar o nome de quem reservou o lugar------------------------------------------------------------
void change_reservation_name(ROOM* p)
{
	int room_code, show_code, reservation_code;
	int i = 0, j = 0, c = 0;



	printf("\nWhat is the room's code, the show's code and the reservation's code you desire to modify the client's name? ");
	scanf("%d %d %d", &room_code, &show_code, &reservation_code);

	while (p[i].code != room_code && i < MAX)
	{
		i++;

	}

	while (p[i].show[j].code != show_code && j < MAX)
	{
		j++;
	}

	while (p[i].show[j].reservation[c].code != reservation_code && c < MAX)
	{
		c++;
	}

	if (p[i].exist == true && p[i].show[j].exist == true && p[i].show[j].reservation[c].exist == true)
	{
		do
		{
			printf("\nWhat is the name of the client? ");
			scanf("%s", &p[i].show[j].reservation[c].name);

		} while (strcmp(p[i].show[j].reservation[c].name, "") == 0 || strcmp(p[i].show[j].reservation[c].name, "\n") == 0
			|| (strcmp(p[i].show[j].reservation[c].name, " ") == 0));
	}
}
//-------------------------------------------------------Mudar o pagamento de uma reserva(dizer sim ou nao)-------------------------------------------
void change_reservation_payment(ROOM* p)
{
	int room_code, show_code, reservation_code;
	int i = 0, j = 0, c = 0;



	printf("\nWhat is the room's code, the show's code and the reservation's code you desire to modify the payment? ");
	scanf("%d %d %d", &room_code, &show_code, &reservation_code);

	while (p[i].code != room_code && i < MAX)
	{
		i++;

	}

	while (p[i].show[j].code != show_code && j < MAX)
	{
		j++;
	}

	while (p[i].show[j].reservation[c].code != reservation_code && c < MAX)
	{
		c++;
	}

	if (p[i].exist == true && p[i].show[j].exist == true && p[i].show[j].reservation[c].exist == true)
	{
		do
		{

			printf("\nDid the client paid? (Y|N)");
			scanf("%s", &p[i].show[j].reservation[c].pay);

			if (strcmp(p[i].show[j].reservation[c].pay, "Y") == 0)
			{
				p[i].show[j].reservation[c].paid = true;
			}
			else
			{
				p[i].show[j].reservation[c].paid = false;
			}

		} while (strcmp(p[i].show[j].reservation[c].pay, "Y") && strcmp(p[i].show[j].reservation[c].pay, "N"));
	}

}
//--------------------------------------------------------------Altera�ao de uma reserva--------------------------------------------------------------
void change_reservation(ROOM* p)
{

	int option;


	do
	{
		printf("0 - Exit\n");
		printf("1 - Change Row and Chair\n");
		printf("2 - Change Name\n");
		printf("3 - Change Payment\n");
		printf("\nWhat operation you desire to execute? \n");
		scanf("%d", &option);

		switch (option)
		{
		case 0:break;
		case 1:change_row_chair(p); break;
		case 2:change_reservation_name(p); break;
		case 3:change_reservation_payment(p); break;
		default:printf("\nOperation not found\n"); break;

		}

	} while (option != 0);





}
//---------------------------------------------------------------Listagem das reservas----------------------------------------------------------------

void reservation_list(ROOM* p)
{
	for (int i = 0; i < MAX; i++)
	{
		for (int j = 0; j < MAX; j++)
		{
			for (int c = 0; c < MAX; c++)
			{
				if (p[i].show[j].reservation[c].exist == true)
				{
					printf("\n%d\t    %d\t\t%d\t\t     %s\t\t\t%d\t%d\t%s\n", p[i].code, p[i].show[j].code, p[i].show[j].reservation[c].code,
						p[i].show[j].reservation[c].name, p[i].show[j].reservation[c].row,
						p[i].show[j].reservation[c].chair, p[i].show[j].reservation[c].pay);
				}
			}
		}
	}
}
//------------------------------------------Lucro de um determinado espetaculo numa determinada sala-----------------------------------------------
void room_profit(ROOM* p)
{
	int a = 0;

	int i = 0, j = 0;

	int room_code, show_code;

	printf("\nWhat is the room's code and show's code you desire to see the profit? ");

	scanf("%d %d", &room_code, &show_code);



	while (p[i].code != room_code && i < MAX)
	{
		i++;

	}

	while (p[i].show[j].code != show_code && j < MAX)
	{
		j++;
	}

	for (int c = 0; c < MAX; c++)
	{
		if (p[i].show[j].reservation[c].exist == true)
		{
			a += 1; //Ver quantas reservas existem
		}
	}


	printf("\nThe show's profit is: %.2f\n", a * p[i].show[j].price);


}

//-----------------------------Filtro de pesquisa sobre todos os espetaculos alocados na mesma localidade (mesmo em salas diferentes)---------------------------

void shows_locality_search(ROOM* p)
{
	char locality_name[20];

	printf("\nWhat is the name of the locality you desire to search the shows? ");
	scanf("%s", locality_name);

	printf("\nRoom_Code\tShow_Code\tTitle\tGenre\tDay / Month / Year\tPrice\tHour Minute\tDuration\n");

	for (int i = 0; i < MAX; i++)
	{
		for (int j = 0; j < MAX; j++)
		{
			if (strcmp(p[i].locality_name, locality_name) == 0 && p[i].show[j].exist == true)
			{

				printf("\n%d\t\t%d\t\t%s\t\t%s\t\t%d   %d     %d\t%.2f\t%d : %d  %s\t%d\n", p[i].code, p[i].show[j].code,
					p[i].show[j].title, p[i].show[j].genre, p[i].show[j].date.day, p[i].show[j].date.month, p[i].show[j].date.year,
					p[i].show[j].price, p[i].show[j].date.hour, p[i].show[j].date.minute, p[i].show[j].date.time, p[i].show[j].date.duration);
			}
		}
	}

	printf("\n\n");
}

//-----------------------------Filtro de pesquisa sobre todos os espetaculos com pre�o menor ou igual a um determinado pre�o------------------------------

void price_search(ROOM* p)
{
	float price;

	printf("\nWhat is max price to search?");
	scanf("%f", &price);

	printf("\nRoom_Code\tShow_Code\tTitle\tGenre\tDay / Month / Year\tPrice\tHour Minute\tDuration\n");
	for (int i = 0; i < MAX; i++)
	{
		for (int j = 0; j < MAX; j++)
		{
			if (p[i].show[j].price <= price && p[i].show[j].exist == true)
			{

				printf("\n%d\t\t%d\t\t%s\t\t%s\t\t%d   %d     %d\t%.2f\t%d : %d  %s\t%d\n", p[i].code, p[i].show[j].code,
					p[i].show[j].title, p[i].show[j].genre, p[i].show[j].date.day, p[i].show[j].date.month, p[i].show[j].date.year,
					p[i].show[j].price, p[i].show[j].date.hour, p[i].show[j].date.minute, p[i].show[j].date.time, p[i].show[j].date.duration);


			}
		}
	}

	printf("\n\n");
}

//--------------------------------Filtro de pesquisa sobre todos os espetaculos a acorrer numa determinada data----------------------------------------

void shows_date_search(ROOM* p)
{


	int day, month, year;


	printf(" What is the day, month and year from the show you desire to check? ");
	scanf("%d %d %d", &day, &month, &year);

	printf("\nRoom_Code\tShow_Code\tTitle\tGenre\tPrice\tHour Minute\tDuration\n");

	for (int i = 0; i < MAX; i++)
	{
		for (int j = 0; j < MAX; j++)
		{
			if (day == p[i].show[j].date.day && month == p[i].show[j].date.month && year == p[i].show[j].date.year)
			{
				printf("%d %d\t%s\t%s\t%.2f\t%d     %d  %s\t%d\n", p[i].code, p[i].show[j].code, p[i].show[j].title, p[i].show[j].genre, p[i].show[j].price,
					p[i].show[j].date.hour, p[i].show[j].date.minute, p[i].show[j].date.time, p[i].show[j].date.duration);

			}
		}
	}

	printf("\n\n");
}

//--------------------------------Filtro de pesquisa sobre quem pagou numa determinada sala num determinado espetaculo---------------------------------

void paid_search(ROOM* p)
{

	int i = 0, j = 0;

	int room_code, show_code;


	printf("\nWhat is the room's code and show's code you desire to see the paid reservations? ");

	scanf("%d %d", &room_code, &show_code);


	while (p[i].code != room_code)
	{
		i++;
	}

	while (p[i].show[j].code != show_code)
	{
		j++;
	}

	printf("\n\nName\tRow   Chair\n");

	for (int c = 0; c < MAX; c++)
	{
		if (p[i].show[j].reservation[c].paid == true)
		{

			printf("%s\t%d     %d\n", p[i].show[j].reservation[c].name, p[i].show[j].reservation[c].row, p[i].show[j].reservation[c].chair);
		}
	}

	printf("\n\n");
}
//---------------------------------------------------------------------Pesquisa por filtros------------------------------------------------------
void search(ROOM* p)
{
	int option;

	do
	{
		printf("0 - Exit\n");
		printf("1 - Search by localiy\n");
		printf("2 - Show's price\n");
		printf("3 - Show's date\n");
		printf("4 - Paid reservation\n");
		printf("\nWhich operation do you want to execute?");
		scanf("%d", &option);

		switch (option)
		{
		case 0:break;
		case 1:shows_locality_search(p); break;
		case 2:price_search(p); break;
		case 3:shows_date_search(p); break;
		case 4:paid_search(p); break;
		default:printf("\nOperation not found\n");
		}

	} while (option != 0);
}

//-------------------------------------------------------------Guardar em ficheiro binario-----------------------------------------------------
void save_to_bin(ROOM* p)
{
	FILE* f;
	f = fopen("Rooms.dat", "wb"); //gravar em ficheiro binario

	if (f == NULL)
	{
		fprintf(stderr, "\nIt is not possible to open the file");
	}
	else
	{

		fwrite(p, sizeof(ROOM), MAX, f);
		

		fclose(f);
	}
}

//--------------------------------------------------------------Ler ficheiro binario---------------------------------------------------------

void read_bin(ROOM* p)
{
	FILE* f;
	f = fopen("Rooms.dat", "rb"); //ler  ficheiro binario

	if (f == NULL)
	{
		fprintf(stderr, "\nIt is not possible to open the file");
	}
	else
	{

		fread(p, sizeof(ROOM), MAX, f);
		fclose(f);
	}

}

//--------------------------------------------------------------Guardar em ficheiro de texto-----------------------------------------------

void save_to_txt(ROOM* p)
{
	FILE* f;

	if ((f = fopen("Rooms.txt", "w+")) == NULL) //gravar em ficheiro texto)
	{
		fprintf(stderr, "\nIts not possible to open the file");
	}

	else
	{


		fprintf(f, "Code     Locality     Rows     Chairs\n"); //Indica��o do que cada valor � no file

		for (int i = 0; i < MAX; i++)
		{
			if (p[i].exist == true)
			{

				fprintf(f, "%d        %s\t      %d\t       %d\n", p[i].code, p[i].locality_name, p[i].rows, p[i].chairs); //Print dos valores das salas
																														  //nos files	
			}
		}


		fprintf(f, "\nRoom_Code\tShow_Code\tTitle\t\tGenre\t\tDay  /  Month  /  Year\t\tPrice\t\tHour : Minute\tDuration\n");//Indica��o do que
																															//cada valor � no file

		for (int i = 0; i < MAX; i++)
		{
			for (int j = 0; j < MAX; j++)
			{
				if (p[i].show[j].exist == true)
				{

					fprintf(f, "%d\t\t%d\t\t%s\t\t%s\t\t%d    /  %d      /  %d\t\t%.2f\t\t%d    : %d  %s\t%d\n", p[i].code, p[i].show[j].code,
						p[i].show[j].title, p[i].show[j].genre, p[i].show[j].date.day, p[i].show[j].date.month, p[i].show[j].date.year,
						p[i].show[j].price, p[i].show[j].date.hour, p[i].show[j].date.minute, p[i].show[j].date.time, p[i].show[j].date.duration);
					//Print dos valores dos espetaculos nos files
				}
			}
		}

		fprintf(f, "\nRoom_code\tShow_code\tReservation_code\tName\tRow\tChair\tPayment");//Indica��o do que cada valor � no file

		for (int i = 0; i < MAX; i++)
		{
			for (int j = 0; j < MAX; j++)
			{
				for (int c = 0; c < MAX; c++)
				{
					if (p[i].show[j].reservation[c].exist == true)
					{

						fprintf(f, "\n%d\t\t%d\t\t%d\t\t\t%s\t%d\t%d\t%s", p[i].code, p[i].show[j].code, p[i].show[j].reservation[c].code,
							p[i].show[j].reservation[c].name, p[i].show[j].reservation[c].row,//Print dos valores nos files
							p[i].show[j].reservation[c].chair, p[i].show[j].reservation[c].pay);
					}
				}
			}
		}


		fclose(f);
	}
}

//--------------------------------------------------------------Fun�ao main---------------------------------------------------------------------------

void main()
{
	ROOM p[MAX];

	int option;

	inicialization(p);

	do
	{
		printf("\n\n\tMENU****\n");
		printf("0 - Exit\n");
		printf("-------------------\n");
		printf("<1> - New room\n");
		printf("<2> - Remove room\n");
		printf("<3> - Check rooms list\n");
		printf("-------------------\n");
		printf("<4> - New show\n");
		printf("<5> - Modify show\n");
		printf("<6> - Remove show\n");
		printf("<7> - Shows list\n");
		printf("-------------------\n");
		printf("<8> - New reservation\n");
		printf("<9> - Modify reservation\n");
		printf("<10> - Remove reservation\n");
		printf("<11> - Reservations list\n");
		printf("-------------------\n");
		printf("<12> - Show profit\n");
		printf("<13> - Read previous data\n");
		printf("<14> - Search\n");
		printf("\nWhich operation do you want to execute:");
		scanf("%d", &option);


		switch (option)
		{
		case 0:save_to_bin(p); save_to_txt(p); printf("\nEnd of execution\n"); break;
		case 1:add_new_room(p); break;
		case 2:remove_room(p); break;
		case 3:printf("\nRoom_Code   Locality  Rows Chairs\n");
			rooms_list(p); break;
		case 4:add_new_show(p); break;
		case 5:change_show(p); break;
		case 6:remove_show(p); break;
		case 7:printf("\nRoom_Code\tShow_code\tTile\t\tGenre\t\tDay/Month/Year\tPrice\tHour   \t\tDuration\n");
			shows_list(p); break;
		case 8:add_new_reservation(p); break;
		case 9:change_reservation(p); break;
		case 10:remove_reservation(p); break;
		case 11:printf("\nRoom_Code   Show_Code   Reservation_Code    Name\t\tRow     Chair\tPayment\n");
			reservation_list(p); break;
		case 12:room_profit(p); break;
		case 13:read_bin(p); break;
		case 14:search(p); break;
		default:printf("\nOperation not found...\n");
		}

		system("pause");

	} while (option != 0);

}