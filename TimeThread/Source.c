#include <Windows.h>
#include <stdio.h>

HANDLE hThread[4];

int hour = 0;
int minute = 0;
int second = 0;
int milesecond = 0;
int hourPotok = 0;
int minutePotok = 0;
int secondPotok = 0;
int milesecondPotok = 0;

void WorkHours()
{
	while (1)
	{
		second++;
		if (second == 60)
		{
			minute += 1;
			second = 0;
		}
		if (minute == 60)
		{
			minute = 0;
			hour += 1;
		}
		if (hour == 24)
		{
			hour = 0;
		}
		Sleep(1000);
	}
}

void WorkHoursSecondomer()
{
	while (1)
	{
		milesecondPotok++;
		if (milesecondPotok == 10)
		{
			secondPotok++;
			milesecondPotok = 0;
		}
		if (secondPotok == 60)
		{
			minutePotok += 1;
			secondPotok = 0;
		}
		if (minutePotok == 60)
		{
			minutePotok = 0;
			hourPotok += 1;
		}
		if (hourPotok == 24)
		{
			hourPotok = 0;
		}
		Sleep(94);
	}
}

void ShowHours()
{
	while (1)
	{
		unsigned int start_time = clock();
		system("cls");
		printf("%d:%d:%d\n", hour, minute, second);
		unsigned int end_time = clock();
		unsigned int search_time = end_time - start_time;
		Sleep(1000 - search_time);
	}
}

int CheckTime(int hour, int minute, int second) // Проверка на правильность ввода времени
{
	if (hour >= 24 || minute >= 60 || second >= 60 || hour < 0 || minute < 0 || second < 0)
	{
		printf("Указано несуществующее время! Повторите ввод!\n");
		return 1;
	}
	return 0;
}

void ShowHoursMileSecond()
{
	while (1)
	{
		unsigned int start_time = clock();
		system("cls");
		printf("%d:%d:%d:%d\n", hourPotok, minutePotok, secondPotok, milesecondPotok);
		unsigned int end_time = clock();
		unsigned int search_time = end_time - start_time;
		Sleep(94 - search_time);
	}
}



void main()
{
	system("chcp 1251>nul");

	hThread[0] = CreateThread(NULL, 0, WorkHours, NULL, 0, 0);
	hThread[1] = CreateThread(NULL, 0, ShowHours, NULL, 0, 0);

	int command;
	int commandSecundomer = 0;
	
	// Для секундомера
	int hourSec;
	int minuteSec;
	int secondSec;
	int milesecondSec;

	while (1)
	{
		scanf_s("%d", &command);
		switch (command)
		{
		case(1): // Вкл/выкл паузы
			if (ResumeThread(hThread[0]) != 0)
			{
				printf("Пауза выключена\n");
				ResumeThread(hThread[0]);
				ResumeThread(hThread[1]);
			}
			else
			{
				printf("Включена пауза\n");
				SuspendThread(hThread[0]);
				SuspendThread(hThread[1]);
			}
			break;
		case(2): // Установить время
			SuspendThread(hThread[0]);
			SuspendThread(hThread[1]);
			system("cls");
			while (1)
			{
				printf("Введите время:");
				scanf_s("%d%d%d", &hour, &minute, &second);
				if (CheckTime(hour, minute, second) == 0)
				{
					break;
				}
			}
			milesecond = 0;
			system("cls");
			ResumeThread(hThread[0]);
			ResumeThread(hThread[1]);
			break;
		case(3): // Секундомер
			if (commandSecundomer == 0)
			{
				SuspendThread(hThread[1]);
				system("cls");
				printf("Секундомер включен\n");
				hThread[2] = CreateThread(NULL, 0, ShowHoursMileSecond, NULL, 0, 0);
				hThread[3] = CreateThread(NULL, 0, WorkHoursSecondomer, NULL, 0, 0);
				commandSecundomer = 1;
			}
			else
			{
				SuspendThread(hThread[2]);
				SuspendThread(hThread[3]);
				printf("Секундомер выключен\n");
				ResumeThread(hThread[1]);
				commandSecundomer = 0;
			}
			break;
		default: // Иное событие
			CloseHandle(hThread[0]);
			CloseHandle(hThread[1]);
			CloseHandle(hThread[2]);
			CloseHandle(hThread[3]);
			printf("Такого действия не существует!\n");
			return;
			break;
		}
	}
}