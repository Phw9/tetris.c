Making tetris game in C

문제점 : 

1. 아래방향키로 쭉 내리면 뚫고 지나가는 현상
2. for(i=0;i<30;i++){
      for(j=0;j<30;j++){
        if(Cscreen[i][j]!=copyScreen[i][j]){
          Cscreen[i][j]=copyScreen[i][j];
          }
      }
   }
   현재 코드는 system("cls")을 사용해 화면을 지웠다 포인터배열을 불러오는 식인데 위와같은 방법으로 깜빡임 현상을 제거할수 있음.
   혹은 다른 방법이 있는지
