#include "tetris.h"



int main(void) {

	int i, j, CB_type, CB_spin, NB_type, NB_spin;
	int** Crel_coord;	//현재 블럭 상대 좌표
	int** Nrel_coord;	//다음 블럭 상대 좌표
	int* cur;			//현재 블럭의 중심좌표
	int* st;			// 블럭 생성지점
	int* nt;			// 다음블럭 생성지점
	int* temp;			// 임시 중심좌표
	char*** Cscreen;	// 매개변수사용을 위해 게임판을 포인터배열로 선언
	/*char*** Tscreen;*/// 게임판 복사본
	char key;			// 키보드 입력받을 메모리
	clock_t t;
	t = clock();
	srand(time(NULL));
	CB_type = rand() % 7;// 현재블럭 종류 난수생성
	NB_type = rand() % 7;// 다음블럭 종류 난수생성
	CB_spin = rand() % 4;// 현재블럭 회전각 난수생성
	NB_spin = rand() % 4;// 다음블럭 회전각 난수생성

	system("mode con cols=100 lines=40"); //콘솔창 크기


	//게임판 만들기 □■▩▣▨▧▦ (30x30)
	Cscreen = (char***)malloc(sizeof(char**) * 30);
	for (i = 0; i < 30; i++){
		Cscreen[i] = (char**)malloc(sizeof(char*) * 30);
	}
	for (i = 0; i < 30; i++)	// (4<i<24), (6<j<19)
	{
		for (j = 0; j < 30; j++)
		{
			if (i == 25 && j > 5 && j < 20) Cscreen[i][j] = "▩";		// main outline
			else if (j == 6 && i > 3 && i < 25) Cscreen[i][j] = "▩";
			else if (j == 19 && i > 3 && i < 25) Cscreen[i][j] = "▩";
			else if (i == 5 && j > 22 && j < 29) Cscreen[i][j] = "▦";	// next block line
			else if (i == 11 && j > 22 && j < 29) Cscreen[i][j] = "▦";
			else if (j == 23 && i > 4 && i < 12) Cscreen[i][j] = "▦";
			else if (j == 29 && i > 4 && i < 12) Cscreen[i][j] = "▦";
			else Cscreen[i][j] = "　";
		}

	}

	// 블럭 좌표 생성

	Crel_coord = (int**)malloc(sizeof(int*) * 4);// 현재 블럭 상대좌표 메모리 할당(4x2)
	Nrel_coord = (int**)malloc(sizeof(int*) * 4);// 다음 블럭 상대좌표 메모리 할당(4x2)
	for (i = 0; i < 4; i++) {
		Crel_coord[i] = (int*)malloc(sizeof(int) * 2);
		Nrel_coord[i] = (int*)malloc(sizeof(int) * 2);
	}

	cur = (int*)malloc(sizeof(int) * 2);		// 현재 블럭 중심좌표 메모리 할당
	temp = (int*)malloc(sizeof(int) * 2);		// 임시 블럭 중심좌표 메모리 할당
	st = (int*)malloc(sizeof(int) * 2);			// 시작지점 블럭 중심좌표 메모리 할당
	nt = (int*)malloc(sizeof(int) * 2);			// 다음블럭 블럭 생성지점 중심좌표 메모리 할당
	st[0] = 4;
	st[1] = 12;
	cur[0] = st[0];
	cur[1] = st[1];
	nt[0] = 8;
	nt[1] = 26;
	printf("%d %d", CB_type, CB_spin);
	make_block_coord(Crel_coord, CB_type, CB_spin);
	make_block_coord(Nrel_coord, NB_type, 0);
	make_block(Cscreen, Crel_coord, st[0], st[1]);
	make_block(Cscreen, Nrel_coord, nt[0], nt[1]);
	show_screen(Cscreen);
	

	//	게임시작
	/*	※알고리즘
		현재 블럭 삭제→다음 블럭 좌표 생성→삽입 가능여부 판단
		→블럭 생성or삭제→블럭 삽입→행(꽉찼는지 판단 후 삭제)→화면지우고 show_screen
																						*/

	for (;;) {
		if (clock() - t > 400) {	//시간이 경과할때 마다 블럭이 떨어짐
			t = clock();
			del_block(Cscreen, Crel_coord, cur[0], cur[1]);		//현재 좌표의 블럭 삭제
			cur[0] += 1;
			make_block_coord(Crel_coord, CB_type, CB_spin);		//좌표 변경 후 생성
			if (put_block(Cscreen, Crel_coord, cur) ) {			//블럭 삽입 가능여부
				system("cls");
				make_block(Cscreen, Crel_coord, cur[0], cur[1]);//블럭 생성
				
			}
			else {
				cur[0] -= 1;
				system("cls");
				make_block_coord(Crel_coord, CB_type, CB_spin);
				make_block(Cscreen, Crel_coord, cur[0], cur[1]);
				del_row(Cscreen);
				show_screen(Cscreen);
				cur[0] = st[0];										// 다음블럭 게임판으로 생성 작업
				cur[1] = st[1];
				put_coord(Crel_coord, Nrel_coord);
				CB_type = NB_type;
				CB_spin = NB_spin;
				NB_type = rand() % 7;
				del_block(Cscreen, Nrel_coord, nt[0], nt[1]);		// 다음블럭 생성
				make_block_coord(Nrel_coord, NB_type, 0);
				make_block(Cscreen, Nrel_coord, nt[0], nt[1]);
					if (put_block(Cscreen, Crel_coord, st)) {
						system("cls");
						make_block_coord(Crel_coord, CB_type, CB_spin);
						make_block(Cscreen, Crel_coord, cur[0], cur[1]);
						/*del_row(Cscreen);*/
					}
					else {
						system("cls");								// 새로운 블럭 생성 안될 시 게임 종료
						printf("game over\n");
						return 0;
					}	
				system("cls");
				make_block_coord(Crel_coord, CB_type, CB_spin);
				make_block(Cscreen, Crel_coord, cur[0], cur[1]);
				del_row(Cscreen);
			}
			show_screen(Cscreen);
		}
		
		
		
		if (_kbhit()) {		// 키보드 입력시
			key = _getch();

			if (key == -32) {
				key = _getch();
				switch (key) {
				case UP:	// 회전
					del_block(Cscreen, Crel_coord, cur[0], cur[1]);
					CB_spin = B_rotate(CB_spin);
					make_block_coord(Crel_coord, CB_type, CB_spin);
					if (put_block(Cscreen, Crel_coord, cur) == 1) {
						system("cls");
						make_block(Cscreen, Crel_coord, cur[0], cur[1]);
						del_row(Cscreen);
						break;
					}
					else {
						CB_spin = Brev_rotate(CB_spin);
						make_block_coord(Crel_coord, CB_type, CB_spin);
						make_block(Cscreen, Crel_coord, cur[0], cur[1]);
						del_row(Cscreen);
						break;
					}
				case DOWN:	// 아래로 한칸
					del_block(Cscreen, Crel_coord, cur[0], cur[1]);	//삭제
					cur[0] += 1;
					make_block_coord(Crel_coord, CB_type, CB_spin);	//좌표생성
					if (put_block(Cscreen, Crel_coord, cur)) {
						system("cls");
						make_block(Cscreen, Crel_coord, cur[0], cur[1]);
					}
					else
					{
						cur[1] -= 1;
						system("cls");
						make_block(Cscreen, Crel_coord, cur[0], cur[1]);
					}
					del_row(Cscreen);
					break;
				case LEFT:	// 왼쪽으로 한칸
					del_block(Cscreen, Crel_coord, cur[0], cur[1]);
					cur[1] -= 1;
					make_block_coord(Crel_coord, CB_type, CB_spin);
					if (put_block(Cscreen, Crel_coord, cur)) {
						system("cls");
						make_block(Cscreen, Crel_coord, cur[0], cur[1]);
					}
					else
					{
						cur[1] += 1;
						system("cls");
						make_block(Cscreen, Crel_coord, cur[0], cur[1]);
					}
					break;
				case RIGHT:	// 오른쪽으로 한칸
					del_block(Cscreen, Crel_coord, cur[0], cur[1]);
					cur[1] += 1;
					make_block_coord(Crel_coord, CB_type, CB_spin);
					if (put_block(Cscreen, Crel_coord, cur)) {
						system("cls");
						make_block(Cscreen, Crel_coord, cur[0], cur[1]);
					}
					else
					{
						cur[1] -= 1;
						system("cls");
						make_block(Cscreen, Crel_coord, cur[0], cur[1]);
					}
					break;
				}
				show_screen(Cscreen);

			}
		}
		
	}


	return 0;
}




//int key_down(char key) {
//	switch (key) {
//	case UP:
//		return 0;
//	case DOWN:
//		return 1;
//	case LEFT:
//		return 2;
//	case RIGHT:
//		return 3;
//	case SPACEBAR:
//		return 4;
//	case p:
//		return 5;
//	case ESC:
//		return 6;
//
//	}
//}

// 키입력시 중심좌표 입력 > 좌표변경

void move_B(int* cen, char k)
{
	switch (k)
	{
	case LEFT:
		cen[1] -= 1;
		return;
	case DOWN:
		cen[0] += 1;
		return;
	case RIGHT:
		cen[1] += 1;
		return;
	}
}


//화면출력
void show_screen(char*** s) {
	int i, j = 0;
	for (i = 0; i < 30; i++) {
		for (j = 0; j < 30; j++) {
			printf("%s", s[i][j]);
		}
		printf("\n");
	}
	return;
}

// 블럭생성  □■▩▣▨▧▦　


// 블럭 상대좌표 생성
void block_coord_rel(int** coor, int a_R, int a_C, int b_R, int b_C, int c_R, int c_C, int d_R, int d_C) {
	coor[0][0] = a_R;
	coor[0][1] = a_C;
	coor[1][0] = b_R;
	coor[1][1] = b_C;
	coor[2][0] = c_R;
	coor[2][1] = c_C;
	coor[3][0] = d_R;
	coor[3][1] = d_C;
}



// 블럭 종류, 회전(시계방향) 좌표 생성
void make_block_coord(int** coor, int B_type, int B_spin) {

	switch (B_type) {
	case 0:			/*  ■▣■■
								*/
		switch (B_spin) {
		case 0:
			block_coord_rel(coor, 0, 0, 0, 1, 0, 2, 0, -1);
			return;
		case 1:
			block_coord_rel(coor, 0, 0, 1, 0, 2, 0, -1, 0);
			return;
		case 2:
			block_coord_rel(coor, 0, 0, 0, 1, 0, 2, 0, -1);
			return;
		case 3:
			block_coord_rel(coor, 0, 0, 1, 0, 2, 0, -1, 0);
			return;
		}
	case 1:			/*	■▣
						  ■■  */
		switch (B_spin) {
		case 0:
			block_coord_rel(coor, 0, 0, 0, -1, 1, 0, 1, 1);
			return;
		case 1:
			block_coord_rel(coor, 0, 0, 1, 0, 0, 1, -1, 1);
			return;
		case 2:
			block_coord_rel(coor, 0, 0, 0, -1, 1, 0, 1, 1);
			return;
		case 3:
			block_coord_rel(coor, 0, 0, 1, 0, 0, 1, -1, 1);
			return;
		}

	case 2:			/*    ▣■
						■■	*/
		switch (B_spin) {
		case 0:
			block_coord_rel(coor, 0, 0, 0, 1, 1, 0, 1, -1);
			return;
		case 1:
			block_coord_rel(coor, 0, 0, 0, -1, 1, 0, -1, -1);
			return;
		case 2:
			block_coord_rel(coor, 0, 0, 0, 1, 1, 0, 1, -1);
			return;
		case 3:
			block_coord_rel(coor, 0, 0, 0, -1, 1, 0, -1, -1);
			return;
		}

	case 3:			/*    ■■
						  ■■  */
		switch (B_spin) {
		case 0:
			block_coord_rel(coor, 0, 0, -1, 0, 0, 1, -1, 1);
			return;
		case 1:
			block_coord_rel(coor, 0, 0, -1, 0, 0, 1, -1, 1);
			return;
		case 2:
			block_coord_rel(coor, 0, 0, -1, 0, 0, 1, -1, 1);
			return;
		case 3:
			block_coord_rel(coor, 0, 0, -1, 0, 0, 1, -1, 1);
			return;
		}

	case 4:			/*		■
						  ■▣■    */
		switch (B_spin) {
		case 0:
			block_coord_rel(coor, 0, 0, 0, -1, 0, 1, -1, 0);
			return;
		case 1:
			block_coord_rel(coor, 0, 0, -1, 0, 1, 0, 0, 1);
			return;
		case 2:
			block_coord_rel(coor, 0, 0, 0, -1, 0, 1, 1, 0);
			return;
		case 3:
			block_coord_rel(coor, 0, 0, -1, 0, 1, 0, 0, -1);
			return;
		}

	case 5:			/*  ■
						■▣■*/
		switch (B_spin) {
		case 0:
			block_coord_rel(coor, 0, 0, 0, -1, 0, 1, -1, -1);
			return;
		case 1:
			block_coord_rel(coor, 0, 0, 1, 0, -1, 0, -1, 1);
			return;
		case 2:
			block_coord_rel(coor, 0, 0, 0, -1, 0, 1, 1, 1);
			return;
		case 3:
			block_coord_rel(coor, 0, 0, 1, 0, 1, -1, -1, 0);
			return;
		}

	case 6:			/*		■
						■▣■*/
		switch (B_spin) {
		case 0:
			block_coord_rel(coor, 0, 0, 0, -1, 0, 1, -1, 1);
			return;
		case 1:
			block_coord_rel(coor, 0, 0, 1, 0, 1, 1, -1, 0);
			return;
		case 2:
			block_coord_rel(coor, 0, 0, 0, -1, 0, 1, 1, -1);
			return;
		case 3:
			block_coord_rel(coor, 0, 0, 1, 0, -1, 0, -1, -1);
			return;
		}
	}
}
// 1회 회전
int B_rotate(int spin) {
	spin += 1;
	spin = spin % 4;
	return spin;
}
// 1회 역회전
int Brev_rotate(int spin) {
	spin += 3;
	spin = spin % 4;
	return spin;
}
// 1행 위로


// 게임판에 블럭 생성
void make_block(char*** s, int** rel_coor, int M, int N) {

	int i, tempR, tempC;
	for (i = 0; i < 4; i++) {
		tempR = M + rel_coor[i][0];
		tempC = N + rel_coor[i][1];
		s[tempR][tempC] = "■";
	}

}
// 게임판에 블럭 삭제
void del_block(char*** s, int** rel_coor, int M, int N) {
	int i, R, C;
	for (i = 0; i < 4; i++) {
		R = M + rel_coor[i][0];
		C = N + rel_coor[i][1];
		s[R][C] = "　";
	}
}
// 게임판에 블럭 삽입 여부
int put_block(char*** s, int** rel_coor, int* cen) {

	int R, C, i;
	for (i = 0; i < 4; i++) {
		R = cen[0] + rel_coor[i][0] ;
		C = cen[1] + rel_coor[i][1] ;
		if ((C < 7) || (C > 20)) return 0;
		if (s[R][C] != "　") return 0;
		if (R > 24) return 0;
		
	}
	return 1;
}

// 행 완성시 줄 판단 > 삭제

int fin_row(char*** s, int R) {
	int C;

	for (C = 7; C < 20; C++) {
		if (s[R][C] == "　")
			return FALSE;
	}
	return TRUE;
}

void del_row(char*** s) {
	int R, C, t, ceiling = 5;
	for (R = 24; R > ceiling; R--) {
		if (fin_row(s, R)) {
			for (t = R; t > ceiling; t--) {
				for (C = 7; C < 19; C++) {
					s[t][C] = s[t - 1][C];
				}
			}
		}

	}
}
// 좌표 대입
void put_coord(int** c, int** n) {
	int R, C;
	for (R = 0; R < 4; R++) {
		for (C = 0; C < 4; C++) {
			c[R][C] = n[R][C];
		}
	}
	return;
}