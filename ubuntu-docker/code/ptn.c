#define  M       20
#define  Time    10
#define  dt      0.01
#define  dx      0.1
#define  D       0.1

void DHB2(float *T, float *dT, int Dau, int Cuoi)
{
int i;
float c,l,r;
for (  i = Dau ; i < Cuoi ; i++ )
    {
      c = *(T+i);
      l = (i==0)   ? 100.0 : *(T+(i-1));
      r = (i==M-1) ? 25.0  : *(T+(i+1));
      *(dT+i) = D*(r-2*c+l)/(dx*dx);
    }
}

int main()
{
  int i,t, Ntime;
  float *T,*dT;
  T  = (float *) malloc ((M)*sizeof(float));
  dT = (float *) malloc ((M)*sizeof(float));
  KhoiTao(T);
  printf("Gia tri khoi tao:\n");
  DisplayArray(T, M);
  Write2File(T,M);
  Ntime = Time/dt;
  for (t=0;t<Ntime;t++) {
      DHB2(T, dT, 0, M);
      for ( i = 0 ; i < M ; i++ )
            *(T+i) = *(T+i) + dt*(*(dT+i));
      //Write2File(T,M);
  }
  Write2File(T,M);
  printf("Result of C:\n");
  DisplayArray(T, M);
  //getch();
  return 0;
}