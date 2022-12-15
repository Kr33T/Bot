#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "Windows.h"
#include "math.h"
#define SIZE_BUFFER 512

int main()
{
	float otvet;
	system("chcp 1251 > nul");
	LPSTR pipeName = "\\\\.\\pipe\\Canal";
	HANDLE hNamedPipe; // дескриптор канала
	DWORD size_buffer = SIZE_BUFFER;
	DWORD size_buf = SIZE_BUFFER; // размер буффера для записи
	DWORD actual_read_bite; // размер реально записано байт;
	DWORD actual_write_bite; // размер реально записано байт;
	LPSTR  buffer = (CHAR*)calloc(size_buffer, sizeof(CHAR));
	BOOL Connection;
	BOOL SuccesRead;
	DWORD bukva = 0;
	DWORD zap = 0, ch = 0; // ЧИСЛА ОТ КЛИЕНТА
	while (TRUE) 
	{
		hNamedPipe = CreateNamedPipeA(
			pipeName, //имя канала
			PIPE_ACCESS_DUPLEX, //режим доступа к каналу (односторонний/двусторонний)
			PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT, //режимы работы канала: передавать сообщения|читать сообщения|ждать
			PIPE_UNLIMITED_INSTANCES, //количество водящих соединений к каналу. в данном случае неограничено
			SIZE_BUFFER, // объем буфера на чтение (байт)
			SIZE_BUFFER, // объем буфера на запись (байт)
			INFINITE, // максимальное время ожидания сообщения
			NULL); //указатель на структуру безопасности

		Connection = ConnectNamedPipe(hNamedPipe, NULL);
		if (Connection = TRUE) 
		{
			printf("Соединение с клиентом установлено успешно!");
			Sleep(1000);
			system("cls");
			SuccesRead = ReadFile(hNamedPipe, buffer, size_buffer, &actual_read_bite, NULL);
			zap = 0; ch = 0, bukva = 0;
			if (SuccesRead == TRUE)
			{
				printf("\n Значение, введенное клиентом: ");
				printf(buffer);
				for (int i = 0; i < strlen(buffer); i++)
				{
					if (buffer[i] == '.') zap++; // количество точек
					if (buffer[i] == '-' || buffer[i] == '1' || buffer[i] == '2' || buffer[i] == '3' || buffer[i] == '4' || buffer[i] == '5' || buffer[i] == '6' || buffer[i] == '7' || buffer[i] == '8' || buffer[i] == '9' || buffer[i] == '0')
					{
						ch++;
					}
					if (buffer[i] >= 'A' && buffer[i] <= 'Z' || buffer[i] >= 'a' && buffer[i] <= 'z' ||
						buffer[i] >= 'А' && buffer[i] <= 'Я' || buffer[i] >= 'а' && buffer[i] <= 'я' ||
						buffer[i] == 'Ё' || buffer[i] == 'ё')
					{
						bukva++;
					}
				}
				if (bukva > 0)
				{
					sprintf(buffer, "Вы ввели букву!");
				}
				if (ch + zap == strlen(buffer) && zap < 2)
				{
					otvet = atof(buffer);
					otvet = pow(otvet, 2);
					printf("\n Квадрат числа - %3.5f\n", otvet);
					sprintf(buffer, "%3.5f", otvet);
				}
				else 
				{
					sprintf(buffer, "%s", "Невозможно возвести в степень\n");
				}
				WriteFile(hNamedPipe, buffer, size_buffer, &actual_read_bite, NULL);
			}
		}
		else 
		{
			printf("Клиент был отключен от сервер\n");
		}
		CloseHandle(hNamedPipe);
	}
}