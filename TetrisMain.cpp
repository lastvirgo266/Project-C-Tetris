#include"TetrisMenu.h"
#include"KeyCurControl.h"
#include"common.h"

int main(){
	int choice;

	while (1){
		printf("-------------------��Ʈ���� ���� ���Ű� ȯ���մϴ�.-----------------\n");
		printf("------------------------------�޴��� �������ּ���---------------------\n");
		printf("1. ���� ��ŸƮ\n");
		printf("2. ���� ����\n");
		printf(" �� �Է� : ");
		scanf("%d", &choice);
		fflush(stdin);

		if (choice == 2)
			return 0;

		switch (choice){
		case 1:
			system("cls");
			GameStart();
			break;
		
		default:
			printf("�߸��� �����Դϴ�.");
			break;
		}

		system("cls");
		SetCurrentCursorPos(0, 0);
	}

	return 0;
}

