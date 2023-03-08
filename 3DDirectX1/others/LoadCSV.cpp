#include "LoadCSV.h"
#include <stdio.h>
#include<string>
int LoadCSV(int map[MAP_HEIGHT][MAP_WIDTH], const char* FilePath, int LoadStopNumber)
{
	if (map == nullptr)
	{//�Ȃ�������߂�
		return -1;
	}

	for (int y = 0; y < MAP_HEIGHT; y++)
	{
		for (int x = 0; x < MAP_WIDTH; x++)
		{
			// ������
			map[y][x] = 0;
		}
	}

	FILE* fileHandle;
	errno_t err;
	char str[512];
	memset(str, 0, sizeof(str));
	err = fopen_s(&fileHandle, FilePath, "r");
	if (err != 0)
	{
		return err;
	}

	bool isMinus = false;

	for (int y = 0; y < MAP_HEIGHT;)
	{
		bool end = false;
		fgets(str, 512, fileHandle);
		for (int x = 0, i = 0; x < MAP_WIDTH; i++)
		{
			if (str[i] == '\0')
			{
				// �ǂݍ��ݏI��
				fgets(str, 512, fileHandle);
				i = 0;
			}
			else if (str[i] == '\n')
			{
				// ���s
				y++;
				break;
			}
			else if (str[i] == ',')
			{
				// ���̐�����
				x++;
				isMinus = false;
			}
			else if (str[i] == '-')
			{
				isMinus = true;
			}
			else if (str[i] >= '0' && str[i] <= '9')
			{//������2���ȏ�̏���
				map[y][x] *= 10;

				if (isMinus == true)
				{
					map[y][x] -= str[i] - '0';
				}
				else
				{
					map[y][x] += str[i] - '0';
				}

				if (map[y][x] == LoadStopNumber)
				{
					// �q�b�g������A�ǂݍ��݂������I�ɏI������B
					end = true;
					break;
				}
			}
		}
		if (end)
		{
			break;
		}
	}
	fclose(fileHandle);

	return 0;
}
