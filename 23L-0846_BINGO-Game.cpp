
/*  Author
	  3. M Basim Irfan (23L-0846)*/

#include<iostream>
#include<fstream>
#include<iomanip>
#include<cstring>
#include<chrono>
#include<string>
#include<ctime>
#include<cstdio>

using namespace std;
using namespace std::chrono;
// Global variables
int cont_g_counter = 0;
int total_game_counter = 0;
bool cont_flag = false;
int p1_game_won = 0, p2_game_won = 0;
int arr1[30][30]; // Player 1 Table
int arr2[30][30]; // Player 2 Table
int t_size = 30; // Table size
int p1_score = 0, p2_score = 0;
char p1_name[1000], p2_name[1000];
int game_ID;
char high_p_names[10][50] = { {"x"},{"x"},{"x"},{"x"},{"x"}, {"x"},{"x"},{"x"},{"x"},{"x"} };
int high_p_score[10] = { 0 };
int p_turn = 0;
// Function Prototypes. 
void new_game();
void game_options();
//void random_table(int (&a)[30][30],int size);
void win_loose_message(char a[], char b[], int k);
bool p1_game();
bool p2_game();

void win_loose_message(char p_win_name[], char p_loss_name[], int p_game_won)
{

	
	system("CLS");
	cout << "\n\n YOO HOO ! " << p_win_name << " Won " << endl << endl;
	cout << "\n\n Alas! " << p_loss_name << " better luck next time." << endl << endl;

	fstream game_history;
	game_history.open("game_history.txt", ios::app);
	game_history << setw(10) << left << game_ID << setw(2) << " " << setw(30) << left << p_win_name << setw(2) << " " << setw(30) << left << p_loss_name << endl;
	game_history.close();

	fstream high_score;
	high_score.open("high_scores.txt", ios::in);

	char ch;

	if (high_score.peek() != 0)
	{
		for (int i = 0; i < 10 && (high_score.eof() == 0); i++)
		{
			char str[30];
			int scr;
			if (high_score.eof() == 0)
			{
				high_score >> str;
				high_score >> scr;
				int v = 0;
				for (v = 0; v < strlen(str); v++)
				{
					high_p_names[i][v] = str[v];
				}
				high_p_names[i][v] = '\0';

				high_p_score[i] = scr;
			}
		}
	}
	high_score.close();



	int i = 0;
	bool flag0 = false;
	bool name_found = false;

	flag0 = true;
	for (int k = 0; k < 10; k++)  // checking if the winning player is already in the High score list.
	{
		flag0 = true;
		for (int l = 0; l < strlen(p_win_name); l++)
		{
			if (high_p_names[k][l] == p_win_name[l])
			{

			}
			else
			{
				flag0 = false;
				break;
			}
		}
		if (flag0)
		{
			name_found = true;
			high_p_score[k]++;
			break;
		}
	}

	if (name_found == false)
	{
		flag0 = false;
		i = 0;
		for (i = 0; i < 10; i++) // if table empty then adding new name
		{
			if (high_p_score[i] == 0)
			{
				flag0 = true;
				high_p_score[i] = p_game_won;
				break;
			}
		}
		if (flag0)
		{
			int j = 0;
			for (j = 0; j < strlen(p_win_name); j++)
				high_p_names[i][j] = p_win_name[j];

			high_p_names[i][j] = '\0';
		}
		else
		{
			int min = high_p_score[0];
			int min_score_location = 0;
			for (int k = 0; k < 10; k++) //no empty slot therfore replacing current winner name with minimum score player
			{
				if (min > high_p_score[k])
				{
					min = high_p_score[k];
					min_score_location = k;
				}
			}
			if (high_p_score[min_score_location] <= p_game_won)
			{
				high_p_score[min_score_location] = p_game_won;
				int j = 0;
				for (j = 0; j < strlen(p_win_name); j++)
				{
					high_p_names[min_score_location][j] = p_win_name[j];
				}
				high_p_names[min_score_location][j] = '\0';

			}
		}
	}
	//Sorting in descending order
	for (int i = 0; i < 10; i++)
	{
		for (int j = i + 1; j < 10; j++)
		{
			if (high_p_score[i] < high_p_score[j])
			{
				int temp = high_p_score[i];
				high_p_score[i] = high_p_score[j];
				high_p_score[j] = temp;

				int k = 0;
				char ctemp[30];
				int size = strlen(high_p_names[i]);
				for (; k <= size; k++)
				{
					ctemp[k] = high_p_names[i][k];
				}
				size = strlen(high_p_names[j]);
				for (k = 0; k <= size; k++)
				{
					high_p_names[i][k] = high_p_names[j][k];
				}
				size = strlen(ctemp);
				for (k = 0; k <= size; k++)
				{
					high_p_names[j][k] = ctemp[k];
				}
			}
		}
	}

	high_score.open("high_scores.txt", ios::out);
	for (int i = 0; i < 10; i++)
	{
		if (i != 0)
		{
			high_score << endl;
		}
		high_score << setw(30) << left << high_p_names[i] << setw(2) << " " << setw(5) << left << high_p_score[i];
	}
	high_score.close();


	
}

void continue_game_process()
{
	int turn = p_turn;  
	bool p_exit = false;
	if (turn == 1)              // If Player 1 turn is first
	{
		while (true)
		{
			p1_score = 0; p2_score = 0;

			p_exit = p1_game();  // This function enters value from Player 1 and update the table of both players by replacing entered value by zero.
			if (p_exit == true)
			{
				break;
			}
			system("color 0e");
			if (p1_score >= 5)
			{
				p1_game_won++;
				win_loose_message(p1_name, p2_name, p1_game_won);
				break;
			}
			if (p2_score >= 5)
			{
				p2_game_won++;
				win_loose_message(p2_name, p1_name, p2_game_won);
				break;
			}

			p1_score = 0; p2_score = 0;

			p_exit = p2_game();  // This function enters value from Player 2 and update the table of both players by replacing entered value by zero.
			if (p_exit == true)
			{
				break;
			}
			system("color 0e");
			if (p2_score >= 5)
			{
				p2_game_won++;
				win_loose_message(p2_name, p1_name, p2_game_won);
				break;
			}
			if (p1_score >= 5)
			{
				p1_game_won++;
				win_loose_message(p1_name, p2_name, p1_game_won);
				break;
			}
			system("CLS");
		}
	}
	if (turn == 2)                      // If Player 2 turn is first
	{
		while (true)
		{
			p1_score = 0; p2_score = 0;

			p_exit = p2_game();  // This function enters value from Player 2 and update the table of both players by replacing entered value by zero.
			if (p_exit == true)
			{
				break;
			}
			system("color 0e");
			if (p2_score >= 5)
			{
				p2_game_won++;
				win_loose_message(p2_name, p1_name, p2_game_won);
				break;
			}
			if (p1_score >= 5)
			{
				p1_game_won++;
				win_loose_message(p1_name, p2_name, p1_game_won);
				break;
			}
			system("CLS");
			p1_score = 0; p2_score = 0;

			p_exit = p1_game();  // This function enters value from Player 1 and update the table of both players by replacing entered value by zero.
			if (p_exit == true)
			{
				break;
			}
			system("color 0e");
			if (p1_score >= 5)
			{
				p1_game_won++;
				win_loose_message(p1_name, p2_name, p1_game_won);
				break;
			}
			if (p2_score >= 5)
			{
				p2_game_won++;
				win_loose_message(p2_name, p1_name, p2_game_won);
				break;
			}
			cout << endl << endl;
			system("CLS");
		}
	}
	cont_flag = false;
	cout << endl;
	
}

void continue_game()
{
	fstream resume_game;
	resume_game.open("resume_game.txt", ios::in);

	resume_game >> game_ID ;
	resume_game >> t_size;
	resume_game >> p1_name ;
	resume_game >> p2_name ;
	resume_game >> p_turn  ;
	for (int i = 0; i < t_size; i++)
	{
		for (int j = 0; j < t_size; j++)
		{
			resume_game >> arr1[i][j];
		}
	}
	for (int i = 0; i < t_size; i++)
	{
		for (int j = 0; j < t_size; j++)
		{
			resume_game >> arr2[i][j];
		}
	}
	
	resume_game.close();
	remove("resume_game.txt");
}

void resume_game(int p_turn)
{
	fstream resume_game;
   resume_game.open("resume_game.txt", ios::out);

   resume_game << game_ID << endl;
   resume_game << t_size << endl;
   resume_game << p1_name << endl;
   resume_game << p2_name << endl;
   resume_game << p_turn << endl;

	for (int i = 0; i < t_size; i++)
	{
		for (int j = 0; j < t_size; j++)
		{
			resume_game << arr1[i][j] << " ";
		}
		resume_game << endl;
	}
	resume_game << endl << endl;
	for (int i = 0; i < t_size; i++)
	{
		for (int j = 0; j < t_size; j++)
		{
			resume_game << arr2[i][j] << " ";
		}
		resume_game << endl;
	}

	resume_game.close();

}

void display_history()
{
	fstream history;
	history.open("game_history.txt", ios::in);
	int num; string str1, str2;

	for (int i = 0; i < 42; i++) { cout << " "; }; cout << "GAME HISTORY"; cout << endl << endl;

	cout << setw(10) << left << "GAME_ID" << setw(2) << " " << setw(30) << left << "WINNER NAME" << setw(2) << " " << setw(30) << left << "LOSSER NAME" << endl << endl;
	while (history.eof() == 0)
	{
		history >> num;
		history >> str1;
		history>> str2;
		if (history.eof() == 0)
		{
			cout << setw(10) << left << num << setw(2) << " " << setw(30) << left << str1 << setw(2) << " " << setw(30) << left << str2 << endl;
		}
	}
	history.close();
	cout << endl << endl;
}

void display_high_scores()
{
	fstream high_score; high_score.open("high_scores.txt", ios::in);
	string name; int score;
	bool history_flag = true;
	for (int i = 0; i < 48; i++) { cout << " "; }; cout << "HALL OF FAME"; cout << endl << endl;
	cout << setw(30) << left << "NAMES" << setw(2) << " " << setw(5) << left << "SCORES" << endl << endl;

	while (high_score.eof() == 0)
	{
		high_score >> name; high_score >> score;

		if (high_score.eof() == 0)
		{
			if (score != 0)
			{
				history_flag = false;
				cout << setw(30) << left << name << setw(2) << " " << setw(5) << left << score << endl;
			}
		}
	}
	//high_score.clear();
	high_score.close();
	cout << endl << endl;
	if (history_flag)
	{
		system("cls");
		cout << endl << endl;  for (int i = 0; i < 48; i++) { cout << " "; }; cout << "HALL OF FAME"; cout << endl << endl;
		cout << " NO Players currently in HALL OF FAME" << endl << endl;
	}
}

void display_instructions()
{
	system("color 0d");
	fstream instructions; instructions.open("game_instructions.txt", ios::in);

	string line;
	while (getline(instructions, line)) {
		cout << line << endl;
	}
	instructions.close();
	cout << endl << endl;
}

// Function to replace number with zero. 
bool replace_number(int arr[][30], int t_size, int num)
{
	for (int i = 0; i < t_size; i++)
	{
		for (int j = 0; j < t_size; j++)
		{
			if (num == 0)
			{
				return false;
			}
			if (arr[i][j] == num)
			{
				arr[i][j] = 0;
				return  true;
				break;
			}
		}
	}
}
// Function to Count number of (zero) rows.
void row_check(int t_size)
{
	int p1_num, p2_num, p1_score_flag = 1, p2_score_flag = 1, p1_flag = 1, p2_flag = 1;

	for (int i = 0; i < t_size; i++)
	{
		for (int j = 0; j < t_size; j++)
		{
			if (arr1[i][j] == 0 && p1_flag)
			{
			}
			else
			{
				p1_score_flag = 0;
				p1_flag = 0;
			};
			if (arr2[i][j] == 0 && p2_flag)
			{
			}
			else
			{
				p2_score_flag = 0;
				p2_flag = 0;
			}
		}
		// Checking scores.
		if (p1_score_flag)
		{
			p1_score++;
		}
		if (p2_score_flag)
		{
			p2_score++;
		}
		p1_score_flag = 1;
		p2_score_flag = 1;
		p1_flag = 1;
		p2_flag = 1;
	}
}
// Function to Count number of (zero) columns.
void column_check(int t_size)
{
	int p1_num, p2_num, p1_score_flag = 1, p2_score_flag = 1, p1_flag = 1, p2_flag = 1;

	for (int j = 0; j < t_size; j++)
	{
		for (int i = 0; i < t_size; i++)
		{
			if (arr1[i][j] == 0 && p1_flag)
			{
			}
			else
			{
				p1_score_flag = 0;
				p1_flag = 0;
			};
			if (arr2[i][j] == 0 && p2_flag)
			{
			}
			else
			{
				p2_score_flag = 0;
				p2_flag = 0;
			}
		}
		// Checking scores.
		if (p1_score_flag)
		{
			p1_score++;
		}
		if (p2_score_flag)
		{
			p2_score++;
		}
		p1_score_flag = 1;
		p2_score_flag = 1;
		p1_flag = 1;
		p2_flag = 1;
	}
}
// Function to check Main diagonal of (zero).
void main_diagonal_check(int t_size)
{
	int p1_num, p2_num, p1_score_flag = 1, p2_score_flag = 1, p1_flag = 1, p2_flag = 1;

	for (int i = 0, j = 0; i < t_size && j < t_size; i++, j++)
	{
		if (arr1[i][j] == 0 && p1_flag)
		{
		}
		else
		{
			p1_score_flag = 0;
			p1_flag = 0;
		};
		if (arr2[i][j] == 0 && p2_flag)
		{
		}
		else
		{
			p2_score_flag = 0;
			p2_flag = 0;
		}
	}
	// Checking scores.
	if (p1_score_flag)
	{
		p1_score++;
	}
	if (p2_score_flag)
	{
		p2_score++;
	}
}
// Function to check Secondary diagonal of (zero).
void secondary_diagonal_check(int t_size)
{
	int p1_num, p2_num, p1_score_flag = 1, p2_score_flag = 1, p1_flag = 1, p2_flag = 1;

	for (int i = 0, j = t_size - 1; i < t_size && j >= 0; i++, j--)
	{
		if (arr1[i][j] == 0 && p1_flag)
		{
		}
		else
		{
			p1_score_flag = 0;
			p1_flag = 0;
		};
		if (arr2[i][j] == 0 && p2_flag)
		{
		}
		else
		{
			p2_score_flag = 0;
			p2_flag = 0;
		}
	}
	// Checking scores
	if (p1_score_flag)
	{
		p1_score++;
	}
	if (p2_score_flag)
	{
		p2_score++;
	}
}
// Function to display Table.
void table_display(int arr[][30], int t_size)
{
	cout << endl;
	for (int i = 0; i < t_size; i++)
	{
		for (int b = 0; b < 50 - ((t_size)+10); b++)
		{
			cout << " ";
		}

		for (int j = 0; j < t_size; j++)
		{
			if (arr[i][j] <= 9 && arr[i][j] >= 0)
			{
				cout << "|  " << arr[i][j] << "| ";
			}
			else if (arr[i][j] <= 99 && arr[i][j] >= 10)
			{
				cout << "| " << arr[i][j] << "| ";
			}
			else
			{
				cout << "|" << arr[i][j] << "| ";
			}
		}
		cout << endl << endl;
	}
}
// Function to display winning && losing message.

// Generate tables
void random_table(int arr[30][30], int t_size)
{
	bool unique = false;
	int temp, flag = 1;
	for (int a = 0; a < t_size; a++)
	{
		for (int b = 0; b < t_size; b++)
		{
			flag = 1;
			if (a == 0 && b == 0)
			{
				arr[a][b] = (rand() % (t_size * t_size)) + 1;
				continue;
			}
			int new_number = (rand() % (t_size * t_size)) + 1;
			while (unique == false && flag)
			{
				for (int c = 0; c < t_size && flag; c++)
				{
					for (int d = 0; d < t_size && flag; d++)
					{
						if (c == a && d == b)
						{
							flag = 0;
						}
						if (arr[c][d] == new_number)
						{
							new_number = (rand() % (t_size * t_size)) + 1;
							c = -1;
							break;
						}
					}
				}
				unique = true;
			}
			arr[a][b] = new_number;
			unique = false;
		}
	}
}
// Generating Main Menu.
void game_options()
{
	for (int a = 0; a < 55; a++)
	{
		cout << " ";
	}
	cout << "BINGO" << endl << endl << endl << endl;
	for (int a = 0; a < 50; a++)
	{
		cout << " ";
	}
	cout << "1: New Game" << endl << endl;
	for (int a = 0; a < 50; a++)
	{
		cout << " ";
	}
	cout << "2: Continue Game" << endl << endl;
	for (int a = 0; a < 50; a++)
	{
		cout << " ";
	}
	cout << "3: Game History" << endl << endl;
	for (int a = 0; a < 50; a++)
	{
		cout << " ";
	}
	cout << "4: High Scores" << endl << endl;
	for (int a = 0; a < 50; a++)
	{
		cout << " ";
	}
	cout << "5: How to Play ?" << endl << endl;
	for (int a = 0; a < 50; a++)
	{
		cout << " ";
	}
	cout << "6: Exit" << endl << endl;
}
// Main Menu.
void main_menu()
{
	game_options();
	bool exit = false;int game_counter = 0;
	while (exit != true)
	{
		system("color 0c");
		int dec = -1, counterx = 0;
		int counterj = 0;
		if (game_counter > 0)
		{
			system("CLS");	game_options();
		}

		while (dec != 1 && dec != 2 && dec != 3 && dec != 4 && dec != 5 && dec!=6)
		{
			counterx++;
			if (counterx > 1)
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');system("CLS");
				game_options();
				cout << endl << endl;
				cout << "\n\n\aPlease enter values from 1-5.\n\n";
			}
			cout << "Enter your choice (1-5) : ";cin >> dec;
		}
		game_counter++;
		fstream c_resume_game;
		switch (dec)
		{
		case 1:
			system("CLS");
			srand(time(0));
			game_ID = 999 + rand() % (9999 - 999 + 1); // Generating Random Game ID
			new_game();
			system("pause");
			break;

		case 2:
			system("CLS");
			c_resume_game.open("resume_game.txt", ios::in);
			
			if (c_resume_game.is_open())
			{
				c_resume_game.close();
				continue_game();
				continue_game_process();
			}
			else
			{
				system("cls");  cout << endl << endl;   for (int i = 0; i < 48; i++) { cout << " "; }; cout << "NO PREVIOUS game to CONTINUE.";
			}
			cout << endl << endl;
			system("pause");
		
			break;

		case 3:
			system("CLS"); cout << endl << endl;
			display_history(); system("pause");
			break;

		case 4:
			system("CLS"); cout << endl << endl;
			display_high_scores(); system("pause");
			break;

		case 5:
			system("CLS");
			cout << endl << endl;
			display_instructions();
			system("pause"); system("cls"); system("color 0e");
			break;

		case 6:
			system("CLS");exit = true;
			break;
		}
	}
	cout << endl << endl;
}
// This function generates and Game ID for player 1, generates a Table, takes input and Check game requirements. 
bool p1_game()
{
	cout << endl << endl;
	cout << "Game ID : " << game_ID << endl; cout << endl << endl;
	system("color 0A");
	int p1_num, p2_num, p1_score_flag = 1, p2_score_flag = 1, p1_flag = 1, p2_flag = 1;
	bool p1_num_valid = false, p2_num_valid = false;

	p1_score = 0;p2_score = 0;

	table_display(arr1, t_size); cout << endl;

	p1_num = -1;
	int p1_counter = 0;
	while (p1_num_valid != true)
	{
		p1_score = 0;
		p1_counter++;
		if (p1_counter > 1)
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			system("CLS");
			cout << endl << endl << "Game ID : " << game_ID << endl << endl << endl;

			table_display(arr1, t_size);

			cout << "\n\n\aInvalid input.\nAgain enter number.\n\n";
		}
		cout << p1_name << " select any number from the card (except zero)  or enter -99 to discontinue game : ";
		cin >> p1_num;
		if (p1_num ==-99)
		{
			resume_game(1);
			return true;
			break;
		}
		cout << endl;
		p1_num_valid = replace_number(arr1, t_size, p1_num);
	}
	p1_num_valid = replace_number(arr2, t_size, p1_num);
	// These functions checks the requirement of Bingo Game.
	row_check(t_size);
	column_check(t_size);
	main_diagonal_check(t_size);
	secondary_diagonal_check(t_size);

	system("CLS");
	return false;
}
// This function generates and Game ID for player 2, generates a Table, takes input and Check game requirements. 
bool p2_game()
{
	int p1_num, p2_num, p1_score_flag = 1, p2_score_flag = 1, p1_flag = 1, p2_flag = 1;
	bool p1_num_valid = false, p2_num_valid = false;

	system("CLS");
	cout << endl << endl;
	cout << "Game ID : " << game_ID << endl;
	system("color 0B");
	cout << endl << endl;
	p1_score = 0; p2_score = 0;
	
	table_display(arr2, t_size);

	cout << endl;
	p2_num = -1;
	int p2_counter = 0;
	while (p2_num_valid != true)
	{
		p2_score = 0;
		p2_counter++;
		if (p2_counter > 1)
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			system("CLS");
			cout << endl << endl << "Game ID : " << game_ID << endl << endl << endl;

			table_display(arr2, t_size);

			cout << "\n\n\aInvalid input.\nAgain enter number.\n\n";
		}
		cout << p2_name << " select any number from the card (except zero) or enter -99 to discontinue game : ";
		cin >> p2_num;
		if (p2_num == -99)
		{
			resume_game(2);
			return true;
		}
		cout << endl;
		p2_num_valid = replace_number(arr2, t_size, p2_num);
	}
	p2_num_valid = replace_number(arr1, t_size, p2_num);
	// These functions checks the requirement of Bingo Game.
	row_check(t_size);
	column_check(t_size);
	main_diagonal_check(t_size);
	secondary_diagonal_check(t_size);

	system("cls");
	return false;
}

// This function decides and switches turns between the players.
void new_game()
{
	system("color 0e");
	cout << endl;
	int temp_arr[30][30];
	temp_arr[5][5];
	int  ans=0, t_counter = 0;
	t_size = -4;
	while (t_size < 5 || t_size > 25)
	{
		t_counter++;
		if (t_counter > 1)
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			system("CLS");
			cout << "\n\n\a Invalid input. Range is (5-25).\n\n";
		}
		cout << " For Example : if you enter 5, the table will be of size 5x5." << endl << endl;
		srand(time(0));
		random_table(temp_arr, 5);
		table_display(temp_arr, 5);
		cout << endl << endl;
		cout << " Enter the size of table (5-25) : ";
		cin >> t_size;
	}
	t_counter = 0;
	cout << endl << endl;

	arr1[t_size][t_size];
	arr2[t_size][t_size];

	system("CLS");
	cout << endl << endl << "EXAMPLES for names : m_basim , umer_karamat , umer_mujahid" << endl << endl;
	srand(time(0));
	random_table(arr1, t_size);    // Player 1 Table generation
	random_table(arr2, t_size);    // Player 2 Table generation
	bool name_flag = false; int name_counter = 0;
	cout << endl << endl;
	cin.ignore();
	while (name_flag==false)
	{
		name_counter++;
		if (name_counter > 1) { system("cls"); cout << endl << endl << "EXAMPLES for names : m_basim , umer_karamat , umer_mujahid" << endl << endl; cout << "\a\n\n Name cannot contain spaces.\n\n"; }
		name_flag = true;
		cout << " Enter the name of Player 1 : ";        // Player 1 name 
		cin.getline(p1_name, 1000);
		int i = 0;
		while (i < strlen(p1_name))
		{
			if (p1_name[i] == 32)
			{
				name_flag = false;	break;
			}
			i++;
		}
	}
	cout << endl << endl;
	name_flag = false; name_counter = 0;
	while (name_flag == false)
	{
		name_counter++;
		if (name_counter > 1) { system("cls"); cout << endl << endl << "EXAMPLES for names : m_basim , umer_karamat , umer_mujahid" << endl << endl; cout << "\a\n\n Name cannot contain spaces.\n\n"; }
		name_flag = true;
		cout << " Enter the name of Player 2 : ";        // Player 2 name 
		cin.getline(p2_name, 1000);
		int i = 0;
		while (i < strlen(p2_name))
		{
			if (p2_name[i] == 32)
			{
				name_flag = false;	break;
			}
			i++;
		}
	}
	system("CLS");
	int turn = (rand() % 2) + 1;  // Random turn Calculator.
	bool p_exit = false;
	if (turn == 1)              // If Player 1 turn is first
	{
		while (true)
		{
			p1_score = 0;p2_score = 0;

			p_exit=p1_game();  // This function enters value from Player 1 and update the table of both players by replacing entered value by zero.
			if (p_exit == true)
			{
				break;
			}
			system("color 0e");
			if (p1_score >= 5)
			{
				p1_game_won++;
				win_loose_message(p1_name, p2_name, p1_game_won);
				break;
			}
			if (p2_score >= 5)
			{
				p2_game_won++;
				win_loose_message(p2_name, p1_name, p2_game_won);
				break;
			}

			p1_score = 0;p2_score = 0;

			p_exit = p2_game();  // This function enters value from Player 2 and update the table of both players by replacing entered value by zero.
			if (p_exit == true)
			{
				break;
			}     
			system("color 0e");
			if (p2_score >= 5)
			{
				p2_game_won++;
				win_loose_message(p2_name, p1_name, p2_game_won);
				break;
			}
			if (p1_score >= 5)
			{
				p1_game_won++;
				win_loose_message(p1_name, p2_name, p1_game_won);
				break;
			}
		}
	}
	if (turn == 2)                      // If Player 2 turn is first
	{
		while (true)
		{
			p1_score = 0;p2_score = 0;

			p_exit = p2_game();  // This function enters value from Player 2 and update the table of both players by replacing entered value by zero.
			if (p_exit == true)
			{
				break;
			}            
			system("color 0e");
			if (p2_score >= 5)
			{
				p2_game_won++;
				win_loose_message(p2_name, p1_name, p2_game_won);
				break;
			}
			if (p1_score >= 5)
			{
				p1_game_won++;
				win_loose_message(p1_name, p2_name, p1_game_won);
				break;
			}
			system("CLS");
			p1_score = 0;p2_score = 0;

			p_exit = p1_game();  // This function enters value from Player 1 and update the table of both players by replacing entered value by zero.
			if (p_exit == true)
			{
				break;
			}
			system("color 0e");
			if (p1_score >= 5)
			{
				p1_game_won++;
				win_loose_message(p1_name, p2_name, p1_game_won);
				break;
			}
			if (p2_score >= 5)
			{
				p2_game_won++;
				win_loose_message(p2_name, p1_name, p2_game_won);
				break;
			}
			cout << endl << endl;
		}
	}
	
	cout << endl;
}

int main()
{
	
	system("color 04");

	main_menu();
	system("pause");

	return 0;

}
