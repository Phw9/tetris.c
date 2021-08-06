#include "tetris.h"



int main(void) {

	int i, j, CB_type, CB_spin, NB_type, NB_spin;
	int** Crel_coord;	//���� �� ��� ��ǥ
	int** Nrel_coord;	//���� �� ��� ��ǥ
	int* cur;			//���� ���� �߽���ǥ
	int* st;			// �� ��������
	int* nt;			// ������ ��������
	int* temp;			// �ӽ� �߽���ǥ
	char*** Cscreen;	// �Ű���������� ���� �������� �����͹迭�� ����
	/*char*** Tscreen;*/// ������ ���纻
	char key;			// Ű���� �Է¹��� �޸�
	clock_t t;
	t = clock();
	srand(time(NULL));
	CB_type = rand() % 7;// ����� ���� ��������
	NB_type = rand() % 7;// ������ ���� ��������
	CB_spin = rand() % 4;// ����� ȸ���� ��������
	NB_spin = rand() % 4;// ������ ȸ���� ��������

	system("mode con cols=100 lines=40"); //�ܼ�â ũ��


	//������ ����� ���̢âɢʢ� (30x30)
	Cscreen = (char***)malloc(sizeof(char**) * 30);
	for (i = 0; i < 30; i++){
		Cscreen[i] = (char**)malloc(sizeof(char*) * 30);
	}
	for (i = 0; i < 30; i++)	// (4<i<24), (6<j<19)
	{
		for (j = 0; j < 30; j++)
		{
			if (i == 25 && j > 5 && j < 20) Cscreen[i][j] = "��";		// main outline
			else if (j == 6 && i > 3 && i < 25) Cscreen[i][j] = "��";
			else if (j == 19 && i > 3 && i < 25) Cscreen[i][j] = "��";
			else if (i == 5 && j > 22 && j < 29) Cscreen[i][j] = "��";	// next block line
			else if (i == 11 && j > 22 && j < 29) Cscreen[i][j] = "��";
			else if (j == 23 && i > 4 && i < 12) Cscreen[i][j] = "��";
			else if (j == 29 && i > 4 && i < 12) Cscreen[i][j] = "��";
			else Cscreen[i][j] = "��";
		}

	}

	// �� ��ǥ ����

	Crel_coord = (int**)malloc(sizeof(int*) * 4);// ���� �� �����ǥ �޸� �Ҵ�(4x2)
	Nrel_coord = (int**)malloc(sizeof(int*) * 4);// ���� �� �����ǥ �޸� �Ҵ�(4x2)
	for (i = 0; i < 4; i++) {
		Crel_coord[i] = (int*)malloc(sizeof(int) * 2);
		Nrel_coord[i] = (int*)malloc(sizeof(int) * 2);
	}

	cur = (int*)malloc(sizeof(int) * 2);		// ���� �� �߽���ǥ �޸� �Ҵ�
	temp = (int*)malloc(sizeof(int) * 2);		// �ӽ� �� �߽���ǥ �޸� �Ҵ�
	st = (int*)malloc(sizeof(int) * 2);			// �������� �� �߽���ǥ �޸� �Ҵ�
	nt = (int*)malloc(sizeof(int) * 2);			// ������ �� �������� �߽���ǥ �޸� �Ҵ�
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
	

	//	���ӽ���
	/*	�ؾ˰���
		���� �� ��������� �� ��ǥ ��������� ���ɿ��� �Ǵ�
		��� ����or������� ���ԡ���(��á���� �Ǵ� �� ����)��ȭ������� show_screen
																						*/

	for (;;) {
		if (clock() - t > 400) {	//�ð��� ����Ҷ� ���� ���� ������
			t = clock();
			del_block(Cscreen, Crel_coord, cur[0], cur[1]);		//���� ��ǥ�� �� ����
			cur[0] += 1;
			make_block_coord(Crel_coord, CB_type, CB_spin);		//��ǥ ���� �� ����
			if (put_block(Cscreen, Crel_coord, cur) ) {			//�� ���� ���ɿ���
				system("cls");
				make_block(Cscreen, Crel_coord, cur[0], cur[1]);//�� ����
				
			}
			else {
				cur[0] -= 1;
				system("cls");
				make_block_coord(Crel_coord, CB_type, CB_spin);
				make_block(Cscreen, Crel_coord, cur[0], cur[1]);
				del_row(Cscreen);
				show_screen(Cscreen);
				cur[0] = st[0];										// ������ ���������� ���� �۾�
				cur[1] = st[1];
				put_coord(Crel_coord, Nrel_coord);
				CB_type = NB_type;
				CB_spin = NB_spin;
				NB_type = rand() % 7;
				del_block(Cscreen, Nrel_coord, nt[0], nt[1]);		// ������ ����
				make_block_coord(Nrel_coord, NB_type, 0);
				make_block(Cscreen, Nrel_coord, nt[0], nt[1]);
					if (put_block(Cscreen, Crel_coord, st)) {
						system("cls");
						make_block_coord(Crel_coord, CB_type, CB_spin);
						make_block(Cscreen, Crel_coord, cur[0], cur[1]);
						/*del_row(Cscreen);*/
					}
					else {
						system("cls");								// ���ο� �� ���� �ȵ� �� ���� ����
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
		
		
		
		if (_kbhit()) {		// Ű���� �Է½�
			key = _getch();

			if (key == -32) {
				key = _getch();
				switch (key) {
				case UP:	// ȸ��
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
				case DOWN:	// �Ʒ��� ��ĭ
					del_block(Cscreen, Crel_coord, cur[0], cur[1]);	//����
					cur[0] += 1;
					make_block_coord(Crel_coord, CB_type, CB_spin);	//��ǥ����
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
				case LEFT:	// �������� ��ĭ
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
				case RIGHT:	// ���������� ��ĭ
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

// Ű�Է½� �߽���ǥ �Է� > ��ǥ����

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


//ȭ�����
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

// ������  ���̢âɢʢˡ�


// �� �����ǥ ����
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



// �� ����, ȸ��(�ð����) ��ǥ ����
void make_block_coord(int** coor, int B_type, int B_spin) {

	switch (B_type) {
	case 0:			/*  ��á��
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
	case 1:			/*	���
						  ���  */
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

	case 2:			/*    �á�
						���	*/
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

	case 3:			/*    ���
						  ���  */
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

	case 4:			/*		��
						  ��á�    */
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

	case 5:			/*  ��
						��á�*/
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

	case 6:			/*		��
						��á�*/
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
// 1ȸ ȸ��
int B_rotate(int spin) {
	spin += 1;
	spin = spin % 4;
	return spin;
}
// 1ȸ ��ȸ��
int Brev_rotate(int spin) {
	spin += 3;
	spin = spin % 4;
	return spin;
}
// 1�� ����


// �����ǿ� �� ����
void make_block(char*** s, int** rel_coor, int M, int N) {

	int i, tempR, tempC;
	for (i = 0; i < 4; i++) {
		tempR = M + rel_coor[i][0];
		tempC = N + rel_coor[i][1];
		s[tempR][tempC] = "��";
	}

}
// �����ǿ� �� ����
void del_block(char*** s, int** rel_coor, int M, int N) {
	int i, R, C;
	for (i = 0; i < 4; i++) {
		R = M + rel_coor[i][0];
		C = N + rel_coor[i][1];
		s[R][C] = "��";
	}
}
// �����ǿ� �� ���� ����
int put_block(char*** s, int** rel_coor, int* cen) {

	int R, C, i;
	for (i = 0; i < 4; i++) {
		R = cen[0] + rel_coor[i][0] ;
		C = cen[1] + rel_coor[i][1] ;
		if ((C < 7) || (C > 20)) return 0;
		if (s[R][C] != "��") return 0;
		if (R > 24) return 0;
		
	}
	return 1;
}

// �� �ϼ��� �� �Ǵ� > ����

int fin_row(char*** s, int R) {
	int C;

	for (C = 7; C < 20; C++) {
		if (s[R][C] == "��")
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
// ��ǥ ����
void put_coord(int** c, int** n) {
	int R, C;
	for (R = 0; R < 4; R++) {
		for (C = 0; C < 4; C++) {
			c[R][C] = n[R][C];
		}
	}
	return;
}