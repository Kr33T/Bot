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
	HANDLE hNamedPipe; // ���������� ������
	DWORD size_buffer = SIZE_BUFFER;
	DWORD size_buf = SIZE_BUFFER; // ������ ������� ��� ������
	DWORD actual_read_bite; // ������ ������� �������� ����;
	DWORD actual_write_bite; // ������ ������� �������� ����;
	LPSTR  buffer = (CHAR*)calloc(size_buffer, sizeof(CHAR));
	BOOL Connection;
	BOOL SuccesRead;
	DWORD bukva = 0;
	DWORD zap = 0, ch = 0; // ����� �� �������
	while (TRUE) 
	{
		hNamedPipe = CreateNamedPipeA(
			pipeName, //��� ������
			PIPE_ACCESS_DUPLEX, //����� ������� � ������ (�������������/������������)
			PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT, //������ ������ ������: ���������� ���������|������ ���������|�����
			PIPE_UNLIMITED_INSTANCES, //���������� ������� ���������� � ������. � ������ ������ ������������
			SIZE_BUFFER, // ����� ������ �� ������ (����)
			SIZE_BUFFER, // ����� ������ �� ������ (����)
			INFINITE, // ������������ ����� �������� ���������
			NULL); //��������� �� ��������� ������������

		Connection = ConnectNamedPipe(hNamedPipe, NULL);
		if (Connection = TRUE) 
		{
			printf("���������� � �������� ����������� �������!");
			Sleep(1000);
			system("cls");
			SuccesRead = ReadFile(hNamedPipe, buffer, size_buffer, &actual_read_bite, NULL);
			zap = 0; ch = 0, bukva = 0;
			if (SuccesRead == TRUE)
			{
				printf("\n ��������, ��������� ��������: ");
				printf(buffer);
				for (int i = 0; i < strlen(buffer); i++)
				{
					if (buffer[i] == '.') zap++; // ���������� �����
					if (buffer[i] == '-' || buffer[i] == '1' || buffer[i] == '2' || buffer[i] == '3' || buffer[i] == '4' || buffer[i] == '5' || buffer[i] == '6' || buffer[i] == '7' || buffer[i] == '8' || buffer[i] == '9' || buffer[i] == '0')
					{
						ch++;
					}
					if (buffer[i] >= 'A' && buffer[i] <= 'Z' || buffer[i] >= 'a' && buffer[i] <= 'z' ||
						buffer[i] >= '�' && buffer[i] <= '�' || buffer[i] >= '�' && buffer[i] <= '�' ||
						buffer[i] == '�' || buffer[i] == '�')
					{
						bukva++;
					}
				}
				if (bukva > 0)
				{
					sprintf(buffer, "�� ����� �����!");
				}
				if (ch + zap == strlen(buffer) && zap < 2)
				{
					otvet = atof(buffer);
					otvet = pow(otvet, 2);
					printf("\n ������� ����� - %3.5f\n", otvet);
					sprintf(buffer, "%3.5f", otvet);
				}
				else 
				{
					sprintf(buffer, "%s", "���������� �������� � �������\n");
				}
				WriteFile(hNamedPipe, buffer, size_buffer, &actual_read_bite, NULL);
			}
		}
		else 
		{
			printf("������ ��� �������� �� ������\n");
		}
		CloseHandle(hNamedPipe);
	}
}