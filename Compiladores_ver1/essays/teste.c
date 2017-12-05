float x, y;

int main(){
  x = 2;
  y = -2;
  while (y<-1){
    x=y;
    x=x/y;
    x=x/2;
  }
  if (x>3){
    x = 2*y+4;
    y = 7;
  }else{
    y = 5;
    x = 4;
  }
}
