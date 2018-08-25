#include"TetrisMenu.h"
#include"KeyCurControl.h"
#include"common.h"

int main(){
	int choice;

	while (1){
		printf("-------------------테트리스 세상에 오신걸 환영합니다.-----------------\n");
		printf("------------------------------메뉴를 선택해주세요---------------------\n");
		printf("1. 게임 스타트\n");
		printf("2. 게임 종료\n");
		printf(" ▶ 입력 : ");
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
			printf("잘못된 선택입니다.");
			break;
		}

		system("cls");
		SetCurrentCursorPos(0, 0);
	}

	return 0;
}

