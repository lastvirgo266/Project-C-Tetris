#ifndef __BLOCK_STAGE_CONTROL_H__
#define __BLOCK_STAGE_CONTROL_H__

#define GBOARD_WIDTH 10
#define GBOARD_HEIGHT 20

#define GBOARD_ORIGIN_X 4
#define GBOARD_ORIGIN_Y 2

#define TRUE 1
#define FALSE 0

//게임 리셋
void GameReset();

//블록의 시작위치 설정
void InitNewBlockPos(int x, int y);

//시스템 딜레이값
void SysDelay();

//블록 랜덤 생성
void ChooseBlock();

//다음 블록 생성
void NextBlock();

//블록 얻기
int GetCurrentBlockIdx();

//다음블록 얻기
int GetNextBlockIdx();

//블록출력
void ShowBlock(char blockInfo[][4]);

//출력되어 있는 블록 삭제
void DeleteBlock(char blockInfo[][4]);

//블록 한칸 내리기
void BlockDown();

//블록 바꾸기
void ChangeBlock();

//블록이 움직이지 못하는 상황인지 확인
int LeftBlockRock();

//블록이 움직이지 못하는 상황인지 확인
int RightBlockRock();


//블록이 움직이지 못하는 상황인지 확인
int LeftRotateCollision();

//블록이 움직이지 못하는 상황인지 확인
int RightRotateCollision();


//블록 왼쪽 충돌 검사
int LeftBlockCollision();

//블록 오른쪽 충돌 검사
int RightBlockCollision();

//블록 아래쪽 충독 검사
int DownBlockCollision();

//블록이 쌓일수있는지 검사
int BlockStack();

//블록 멈춤
void BlockStop();

//1줄이 완성되면 블록지우고 내리기
void BlockLineComplete();

//게임오버 체크
int GameEndCheck();
#endif